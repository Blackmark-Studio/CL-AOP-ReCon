string CitySharp2Greeting()
{
	if (pchar.sex == "woman")
	{
		return StringFromKey("ForAll_dialog_1", pchar.name);
	}
	else
	{
		return StringFromKey("ForAll_dialog_2");
	}
}

string BrothelSharp1()
{
	if (pchar.sex == "woman")
	{
		return StringFromKey("ForAll_dialog_3", pchar.name);
	}
	else
	{
		return StringFromKey("ForAll_dialog_4");
	}
}

string NewDeckSharpNoMoneyPhrase()
{
	if (pchar.sex == "woman")
	{
		return StringFromKey("ForAll_dialog_5", pchar.name);
	}
	else
	{
		return StringFromKey("ForAll_dialog_6");
	}
}

string DeckSharp8Greeting()
{
	if (pchar.sex == "woman")
	{
		return StringFromKey("ForAll_dialog_7", pchar.name);
	}
	else
	{
		return StringFromKey("ForAll_dialog_8");
	}
}

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, forName;
	string sTemp, sGem, sTitle, sGroup;
	int iTemp, i, Scl, Rank;
	int iSmallPearl, iBigPearl;
	float Mft;
	string sNPCidx;    // evganat - генераторы
	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = StringFromKey("ForAll_dialog_9");
			link.l1 = StringFromKey("ForAll_dialog_10");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//--------------------------- линейка ГПК --------------------------------
		//заказчик устранения всех нищих
		case "Begin_PoorKill":
			dialog.text = StringFromKey("ForAll_dialog_11");
			link.l1 = StringFromKey("ForAll_dialog_12");
			link.l1.go = "Begin_PoorKill_1";

			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
			RemoveMapQuestMark(npchar.city + "_town", "ISS_PoorsMurder");
		break;

		case "Begin_PoorKill_close":
			dialog.text = StringFromKey("ForAll_dialog_13");
			link.l1 = "...";
			link.l1.go = "Exit";
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			ChangeCharacterReputation(pchar, 10);
			pchar.questTemp.LSC = "PoorIsGood";
			SetQuestHeader("ISS_PoorsMurder");
			AddQuestRecord("ISS_PoorsMurder", "12");
			AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("ым", "ой"));
		break;

		case "Begin_PoorKill_1":
			dialog.text = StringFromKey("ForAll_dialog_14");
			link.l1 = StringFromKey("ForAll_dialog_15");
			link.l1.go = "Begin_PoorKill_2";
		break;
		case "Begin_PoorKill_2":
			dialog.text = StringFromKey("ForAll_dialog_16", GetFullName(npchar), GetFullName(pchar));
			link.l1 = StringFromKey("ForAll_dialog_17");
			link.l1.go = "Begin_PoorKill_3";
		break;
		case "Begin_PoorKill_3":
			dialog.text = StringFromKey("ForAll_dialog_18");
			link.l1 = StringFromKey("ForAll_dialog_19");
			link.l1.go = "Begin_PoorKill_4";
		break;
		case "Begin_PoorKill_4":
			dialog.text = StringFromKey("ForAll_dialog_20", pchar);
			link.l1 = StringFromKey("ForAll_dialog_21", pchar);
			link.l1.go = "Begin_PoorKill_5";
		break;
		case "Begin_PoorKill_5":
			dialog.text = StringFromKey("ForAll_dialog_22");
			link.l1 = StringFromKey("ForAll_dialog_23");
			link.l1.go = "Begin_PoorKill_6";
		break;
		case "Begin_PoorKill_6":
			dialog.text = StringFromKey("ForAll_dialog_24");
			link.l1 = StringFromKey("ForAll_dialog_25");
			link.l1.go = "Begin_PoorKill_7";
			link.l2 = StringFromKey("ForAll_dialog_26", pchar);
			link.l2.go = "Begin_PoorKill_close";
		break;
		case "Begin_PoorKill_7":
			dialog.text = StringFromKey("ForAll_dialog_27", pchar);
			link.l1 = StringFromKey("ForAll_dialog_28");
			link.l1.go = "Begin_PoorKill_8";
		break;
		case "Begin_PoorKill_8":
			dialog.text = StringFromKey("ForAll_dialog_29");
			link.l1 = StringFromKey("ForAll_dialog_30");
			link.l1.go = "Begin_PoorKill_9";
		break;
		case "Begin_PoorKill_9":
			dialog.text = StringFromKey("ForAll_dialog_31");
			link.l1 = StringFromKey("ForAll_dialog_32", pchar);
			link.l1.go = "Begin_PoorKill_10";
		break;
		case "Begin_PoorKill_10":
			dialog.text = StringFromKey("ForAll_dialog_33");
			link.l1 = StringFromKey("ForAll_dialog_34");
			link.l1.go = "Begin_PoorKill_11";
		break;
		case "Begin_PoorKill_11":
			dialog.text = StringFromKey("ForAll_dialog_35");
			link.l1 = StringFromKey("ForAll_dialog_36");
			link.l1.go = "Begin_PoorKill_12";
		break;
		case "Begin_PoorKill_12":
			dialog.text = StringFromKey("ForAll_dialog_37");
			link.l1 = StringFromKey("ForAll_dialog_38");
			link.l1.go = "Begin_PoorKill_13";
		break;
		case "Begin_PoorKill_13":
			dialog.text = StringFromKey("ForAll_dialog_39");
			link.l1 = StringFromKey("ForAll_dialog_40");
			link.l1.go = "Begin_PoorKill_14";
		break;
		case "Begin_PoorKill_14":
			SetQuestHeader("ISS_PoorsMurder");
			AddQuestRecord("ISS_PoorsMurder", "1");
			AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("ISS_PoorsMurder", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			pchar.quest.ISS_Murder1.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder1.win_condition.l1.character = "SentJons_Poorman";
			pchar.quest.ISS_Murder1.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder2.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder2.win_condition.l1.character = "Bridgetown_Poorman";
			pchar.quest.ISS_Murder2.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder3.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder3.win_condition.l1.character = "Beliz_Poorman";
			pchar.quest.ISS_Murder3.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder4.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder4.win_condition.l1.character = "Caracas_Poorman";
			pchar.quest.ISS_Murder4.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder5.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder5.win_condition.l1.character = "Cartahena_Poorman";
			pchar.quest.ISS_Murder5.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder6.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder6.win_condition.l1.character = "Cumana_Poorman";
			pchar.quest.ISS_Murder6.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder7.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder7.win_condition.l1.character = "BasTer_Poorman";
			pchar.quest.ISS_Murder7.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder8.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder8.win_condition.l1.character = "Havana_Poorman";
			pchar.quest.ISS_Murder8.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder9.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder9.win_condition.l1.character = "PortRoyal_Poorman";
			pchar.quest.ISS_Murder9.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder10.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder10.win_condition.l1.character = "FortFrance_Poorman";
			pchar.quest.ISS_Murder10.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder11.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder11.win_condition.l1.character = "Charles_Poorman";
			pchar.quest.ISS_Murder11.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder12.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder12.win_condition.l1.character = "PortoBello_Poorman";
			pchar.quest.ISS_Murder12.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder13.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder13.win_condition.l1.character = "PortPax_Poorman";
			pchar.quest.ISS_Murder13.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder14.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder14.win_condition.l1.character = "Santiago_Poorman";
			pchar.quest.ISS_Murder14.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder15.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder15.win_condition.l1.character = "Marigo_Poorman";
			pchar.quest.ISS_Murder15.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder16.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder16.win_condition.l1.character = "Tortuga_Poorman";
			pchar.quest.ISS_Murder16.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder17.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder17.win_condition.l1.character = "PortSpein_Poorman";
			pchar.quest.ISS_Murder17.function = "ISS_MurderSignExecute";
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.LSC = "SignOnPoorMurder";
			pchar.questTemp.LSC.killCost = 17; //счетчик убитых нищих на декремент
			pchar.questTemp.LSC.usurerId = npchar.city + "_usurer"; //флаг на депозит у ростовщика
			ISS_PoorsMurder_Poorman_AddQuestMarks();

			LAi_SetActorTypeNoGroup(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "gate_back", "none", "", "", "CanFightCurLocation", -1);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			chrDisableReloadToLocation = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//воришка ключа
		case "GiveKeyMan":
			RemoveLandQuestMark_Main(CharacterFromID("Villemstad_tavernkeeper"), "ISS_PoorsMurder");

			dialog.text = StringFromKey("ForAll_dialog_41");
			link.l1 = StringFromKey("ForAll_dialog_42");
			link.l1.go = "GiveKeyMan_1";
		break;
		case "GiveKeyMan_1":
			dialog.text = StringFromKey("ForAll_dialog_43", pchar);
			link.l1 = StringFromKey("ForAll_dialog_44", GetFullName(pchar));
			link.l1.go = "GiveKeyMan_2";
		break;
		case "GiveKeyMan_2":
			dialog.text = StringFromKey("ForAll_dialog_45", GetFullName(pchar));
			link.l1 = StringFromKey("ForAll_dialog_46");
			link.l1.go = "GiveKeyMan_3";
		break;
		case "GiveKeyMan_3":
			dialog.text = StringFromKey("ForAll_dialog_47", pchar);
			link.l1 = StringFromKey("ForAll_dialog_48");
			link.l1.go = "GiveKeyMan_4";
		break;
		case "GiveKeyMan_4":
			dialog.text = StringFromKey("ForAll_dialog_49");
			link.l1 = StringFromKey("ForAll_dialog_50");
			link.l1.go = "GiveKeyMan_5";
		break;
		case "GiveKeyMan_5":
			dialog.text = StringFromKey("ForAll_dialog_51", pchar);
			link.l1 = StringFromKey("ForAll_dialog_52");
			link.l1.go = "GiveKeyMan_6";
		break;
		case "GiveKeyMan_6":
			dialog.text = StringFromKey("ForAll_dialog_53");
			link.l1 = StringFromKey("ForAll_dialog_54");
			link.l1.go = "GiveKeyMan_7";
		break;
		case "GiveKeyMan_7":
			npchar.quest.price = sti(pchar.rank) * 500 * MOD_SKILL_ENEMY_RATE;
			if (sti(npchar.quest.price) <= sti(pchar.money))
			{
				dialog.text = StringFromKey("ForAll_dialog_55", FindMoneyString(sti(npchar.quest.price)));
				link.l1 = StringFromKey("ForAll_dialog_56");
				link.l1.go = "GiveKeyMan_10";
			}
			else
			{
				dialog.text = StringFromKey("ForAll_dialog_57", pchar);
				link.l1 = StringFromKey("ForAll_dialog_58");
				link.l1.go = "GiveKeyMan_8";
			}
		break;
		case "GiveKeyMan_8":
			dialog.text = StringFromKey("ForAll_dialog_59", pchar);
			link.l1 = StringFromKey("ForAll_dialog_60");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toMasterKeysNoMoney";
			NextDiag.TempNode = "GiveKeyMan_NoMoney";
		break;
		case "GiveKeyMan_NoMoney":
			if (sti(npchar.quest.price) <= sti(pchar.money))
			{
				dialog.text = StringFromKey("ForAll_dialog_61", FindMoneyString(sti(npchar.quest.price)));
				link.l1 = StringFromKey("ForAll_dialog_62");
				link.l1.go = "GiveKeyMan_10";
			}
			else
			{
				dialog.text = StringFromKey("ForAll_dialog_63", pchar);
				link.l1 = StringFromKey("ForAll_dialog_64");
				link.l1.go = "exit";
			}
		break;
		case "GiveKeyMan_10":
			dialog.text = StringFromKey("ForAll_dialog_65", pchar);
			link.l1 = StringFromKey("ForAll_dialog_66");
			link.l1.go = "GiveKeyMan_11";
		break;
		case "GiveKeyMan_11":
			dialog.text = StringFromKey("ForAll_dialog_67", pchar);
			link.l1 = StringFromKey("ForAll_dialog_68");
			link.l1.go = "GiveKeyMan_12";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
		break;
		case "GiveKeyMan_12":
			dialog.text = StringFromKey("ForAll_dialog_69");
			link.l1 = StringFromKey("ForAll_dialog_70");
			link.l1.go = "exit";
			SetTimerFunction("LSC_openMasterHouse", 0, 0, 2);
			LocatorReloadEnterDisable("Villemstad_town", "houseSp5", true);
			npchar.location = "none";
			AddQuestRecord("ISS_PoorsMurder", "6");
			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");

			// возможность забрать ранее отданные предателю деньги
			sld = CharacterFromID("GiveKeyMan");
			sld.dialog.currentnode = "PortmansCap_inDeck_over";
			AddMoneyToCharacter(sld, sti(npchar.quest.price));
			sld.SaveItemsForDead = true;
		break;

		case "GiveKeyManInside":
			dialog.text = StringFromKey("ForAll_dialog_71");
			link.l1 = StringFromKey("ForAll_dialog_72");
			link.l1.go = "GiveKeyManInside_1";
			if (GetCharacterSPECIAL(pchar, "Charisma") == 10) link.l1.go = "GiveKeyManInside_4";
			npchar.lifeDay = 0;
		break;
		case "GiveKeyManInside_1":
			dialog.text = StringFromKey("ForAll_dialog_73");
			link.l1 = StringFromKey("ForAll_dialog_74");
			link.l1.go = "GiveKeyManInside_2";
		break;
		case "GiveKeyManInside_2":
			dialog.text = StringFromKey("ForAll_dialog_75", pchar);
			link.l1 = StringFromKey("ForAll_dialog_76");
			link.l1.go = "GiveKeyManInside_3";
		break;
		case "GiveKeyManInside_3":
			dialog.text = StringFromKey("ForAll_dialog_77");
			link.l1 = StringFromKey("ForAll_dialog_78");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_enterSoldiers");

			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
		break;
		case "GiveKeyManInside_4":
			dialog.text = StringFromKey("ForAll_dialog_79");
			link.l1 = StringFromKey("ForAll_dialog_80");
			link.l1.go = "exit";
			LAi_SetPlayerType(pchar);
			pchar.questTemp.LSC = "CanFoundStuvesantKey";
			LAi_CharacterDisableDialog(npchar);
			LAi_SetCitizenType(npchar);
			AddDialogExitQuest("OpenTheDoors");

			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
		break;
		//арестовывающий офицер
		case "MK_HollOfficer":
			dialog.text = StringFromKey("ForAll_dialog_81");
			link.l1 = StringFromKey("ForAll_dialog_82");
			link.l1.go = "MK_HollOfficer_1";
		break;
		case "MK_HollOfficer_1":
			dialog.text = StringFromKey("ForAll_dialog_83");
			link.l1 = StringFromKey("ForAll_dialog_84", pchar);
			link.l1.go = "MK_HollOfficer_2";
		break;
		case "MK_HollOfficer_2":
			LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_houseSp5")], false);
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//заказчик нищих в Мариго
		case "PKInMarigo":
			dialog.text = StringFromKey("ForAll_dialog_85");
			link.l1 = StringFromKey("ForAll_dialog_86");
			link.l1.go = "PKInMarigo_1";
		break;
		case "PKInMarigo_1":
			dialog.text = StringFromKey("ForAll_dialog_87");
			link.l1 = StringFromKey("ForAll_dialog_88");
			link.l1.go = "PKInMarigo_2";
		break;
		case "PKInMarigo_2":
			dialog.text = StringFromKey("ForAll_dialog_89");
			link.l1 = StringFromKey("ForAll_dialog_90");
			link.l1.go = "PKInMarigo_3";
		break;
		case "PKInMarigo_3":
			dialog.text = StringFromKey("ForAll_dialog_91");
			link.l1 = StringFromKey("ForAll_dialog_92");
			link.l1.go = "PKInMarigo_4";
		break;
		case "PKInMarigo_4":
			dialog.text = StringFromKey("ForAll_dialog_93");
			link.l1 = StringFromKey("ForAll_dialog_94");
			link.l1.go = "PKInMarigo_5";
		break;
		case "PKInMarigo_5":
			dialog.text = StringFromKey("ForAll_dialog_95");
			link.l1 = StringFromKey("ForAll_dialog_96");
			link.l1.go = "PKInMarigo_6";
		break;
		case "PKInMarigo_6":
			dialog.text = StringFromKey("ForAll_dialog_97");
			link.l1 = StringFromKey("ForAll_dialog_98");
			link.l1.go = "PKInMarigo_7";
		break;
		case "PKInMarigo_7":
			dialog.text = StringFromKey("ForAll_dialog_99");
			link.l1 = StringFromKey("ForAll_dialog_100");
			link.l1.go = "PKInMarigo_8";
		break;
		case "PKInMarigo_8":
			dialog.text = StringFromKey("ForAll_dialog_101");
			link.l1 = StringFromKey("ForAll_dialog_102");
			link.l1.go = "PKInMarigo_9";
		break;
		case "PKInMarigo_9":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_group_Attack(npchar, pchar);
			pchar.quest.PQ8_afterFight.win_condition.l1 = "NPC_Death";
			pchar.quest.PQ8_afterFight.win_condition.l1.character = "PoorKillSponsor";
			pchar.quest.PQ8_afterFight.win_condition = "OpenTheDoors";
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//мент в Протекторе
		case "LSCQuestMent":
			dialog.text = StringFromKey("ForAll_dialog_103");
			link.l1 = StringFromKey("ForAll_dialog_104");
			link.l1.go = "LSCQuestMent_1";
		break;
		case "LSCQuestMent_1":
			dialog.text = StringFromKey("ForAll_dialog_105");
			link.l1 = StringFromKey("ForAll_dialog_106");
			link.l1.go = "LSCQuestMent_2";
		break;
		case "LSCQuestMent_2":
			dialog.text = StringFromKey("ForAll_dialog_107");
			link.l1 = StringFromKey("ForAll_dialog_108");
			link.l1.go = "LSCQuestMent_3";
		break;
		case "LSCQuestMent_3":
			dialog.text = StringFromKey("ForAll_dialog_109");
			link.l1 = StringFromKey("ForAll_dialog_110");
			link.l1.go = "LSCQuestMent_4";
		break;
		case "LSCQuestMent_4":
			AddQuestRecord("ISS_MainLine", "10");
			pchar.questTemp.LSC = "afterFightInProtector";
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetWarriorTypeNoGroup(npchar);
			sld = characterFromId("AndreLabor");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddLandQuestMark_Main(CharacterFromID("LSCBarmen"), "ISS_MainLine");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//одиночный нарвал, которого надо замочить
		case "LSCQuestNarval":
			dialog.text = StringFromKey("ForAll_dialog_111");
			link.l1 = StringFromKey("ForAll_dialog_112");
			link.l1.go = "LSCQuestNarval_1";
		break;
		case "LSCQuestNarval_1":
			dialog.text = StringFromKey("ForAll_dialog_113", pchar);
			link.l1 = StringFromKey("ForAll_dialog_114");
			link.l1.go = "LSCQuestNarval_2";
		break;
		case "LSCQuestNarval_2":
			dialog.text = StringFromKey("ForAll_dialog_115", pchar);
			link.l1 = StringFromKey("ForAll_dialog_116");
			link.l1.go = "LSCQuestNarval_3";
		break;
		case "LSCQuestNarval_3":
			AddQuestRecord("ISS_MainLine", "12");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ся", "ась"));
			pchar.questTemp.LSC = "toAdmNarvalRing";
			RemoveLandQuestMark_Main(CharacterFromID("PedroHurtado"), "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("LSCBarmen"), "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("LSCMayor"), "ISS_MainLine");
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//--------------------------- дача шебеки Синяя Птица --------------------------------
		//капитан шебеки Синяя Птица
		case "BlueBirdCapitain":
			dialog.text = StringFromKey("ForAll_dialog_117", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("ForAll_dialog_118", pchar);
			link.l1.go = "BlueBirdCapitain_1";
		break;
		case "BlueBirdCapitain_1":
			dialog.text = StringFromKey("ForAll_dialog_119", pchar);
			link.l1 = StringFromKey("ForAll_dialog_120", pchar);
			link.l1.go = "BlueBirdCapitain_2";
		break;
		case "BlueBirdCapitain_2":
			dialog.text = StringFromKey("ForAll_dialog_121");
			link.l1 = StringFromKey("ForAll_dialog_122");
			link.l1.go = "BlueBirdCapitain_3";
		break;
		case "BlueBirdCapitain_3":
			dialog.text = StringFromKey("ForAll_dialog_123", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("ForAll_dialog_124");
			link.l1.go = "BlueBirdCapitain_4";
		break;
		case "BlueBirdCapitain_4":
			dialog.text = StringFromKey("ForAll_dialog_125", pchar);
			link.l1 = StringFromKey("ForAll_dialog_126");
			link.l1.go = "BlueBirdCapitain_5";
		break;
		case "BlueBirdCapitain_5":
			dialog.text = StringFromKey("ForAll_dialog_127");
			link.l1 = StringFromKey("ForAll_dialog_128", pchar);
			link.l1.go = "BlueBirdCapitain_6";
		break;
		case "BlueBirdCapitain_6":
			dialog.text = StringFromKey("ForAll_dialog_129", GetFullName(pchar));
			link.l1 = StringFromKey("ForAll_dialog_130");
			link.l1.go = "BlueBirdCapitain_7";
		break;
		case "BlueBirdCapitain_7":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//капитаны флейтов торговцев
		case "BlueBirdTrader":
			dialog.text = StringFromKey("ForAll_dialog_131");
			link.l1 = StringFromKey("ForAll_dialog_132");
			link.l1.go = "BlueBirdTrader_1";
		break;
		case "BlueBirdTrader_1":
			dialog.text = StringFromKey("ForAll_dialog_133");
			link.l1 = StringFromKey("ForAll_dialog_134", GetFullName(pchar));
			link.l1.go = "BlueBirdTrader_2";
		break;
		case "BlueBirdTrader_2":
			dialog.text = StringFromKey("ForAll_dialog_135");
			link.l1 = StringFromKey("ForAll_dialog_136");
			link.l1.go = "BlueBirdTrader_3";
		break;
		case "BlueBirdTrader_3":
			QuestAboardCabinDialogNotBattle();
			DialogExit();
		break;
		//--------------------------- жемчужный промысел, Шарп --------------------------------
		//капитан Шарп, первый базар на палубе
		case "DeckSharp":    //на палубе
			dialog.text = StringFromKey("ForAll_dialog_137", pchar);
			link.l1 = StringFromKey("ForAll_dialog_138", pchar);
			link.l1.go = "DeckSharp_1";
			npchar.quest.meeting = true;
			RemoveLandQuestmarkToFantoms_Main("Citizen", "SharpPearl");
			RemoveLandQuestmarkToFantoms_Main("Commoner", "SharpPearl");
			//блокировка генератора, если взят грабеж от Моргана
			if (pchar.questTemp.piratesLine == "PearlQ4_toTerks")
			{
				dialog.text = StringFromKey("ForAll_dialog_139", pchar);
				link.l1 = StringFromKey("ForAll_dialog_140");
				link.l1.go = "exit";
				NextDiag.TempNode = "DeckSharp_overBad";
				pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
				pchar.questTemp.Sharp.brothelChance = 1; //первый базар должен быть не в борделе
				// DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal"); - Зачем было тереть
				AddQuestRecord("SharpPearl", "13");
				CloseQuestHeader("SharpPearl");
			}
		break;
		case "DeckSharp_1":
			dialog.text = StringFromKey("ForAll_dialog_141", pchar);
			link.l1 = StringFromKey("ForAll_dialog_142");
			link.l1.go = "DeckSharp_2";
		break;
		case "DeckSharp_2":
			dialog.text = StringFromKey("ForAll_dialog_143");
			link.l1 = StringFromKey("ForAll_dialog_144", pchar);
			link.l1.go = "DeckSharp_3";
		break;
		case "DeckSharp_3":
			dialog.text = StringFromKey("ForAll_dialog_145");
			link.l1 = StringFromKey("ForAll_dialog_146");
			link.l1.go = "DeckSharp_4";
		break;
		case "DeckSharp_4":
			dialog.text = StringFromKey("ForAll_dialog_147");
			link.l1 = StringFromKey("ForAll_dialog_148");
			link.l1.go = "DeckSharp_5";
		break;
		case "DeckSharp_5":
			dialog.text = StringFromKey("ForAll_dialog_149", pchar);
			link.l1 = StringFromKey("ForAll_dialog_150");
			link.l1.go = "DeckSharp_5_1";
		break;
		case "DeckSharp_5_1":
			dialog.text = StringFromKey("ForAll_dialog_151", pchar);
			link.l1 = StringFromKey("ForAll_dialog_152");
			link.l1.go = "DeckSharp_5_2";
		break;
		case "DeckSharp_5_2":
			dialog.text = StringFromKey("ForAll_dialog_153", pchar);
			link.l1 = StringFromKey("ForAll_dialog_154", pchar);
			link.l1.go = "DeckSharp_6";
		break;
		case "DeckSharp_5_3":
			dialog.text = StringFromKey("ForAll_dialog_155", pchar);
			link.l1 = StringFromKey("ForAll_dialog_156", pchar);
			link.l1.go = "DeckSharp_6";
		break;
		case "DeckSharp_6":
			if (GetCompanionQuantity(PChar) == COMPANION_MAX)
			{
				NextDiag.TempNode = "DeckSharp_5_3";
				Dialog.Text = StringFromKey("ForAll_dialog_157", pchar);
				link.l1 = StringFromKey("ForAll_dialog_160", RandPhraseSimple(
							StringFromKey("ForAll_dialog_158"),
							StringFromKey("ForAll_dialog_159")));
				link.l1.go = "Exit";
			}
			else
			{
				GetPerlShore(); //где промысел ведется
				pchar.questTemp.Sharp.PearlAreal.terms = 14; //для первого раза увеличим сроки
				sTemp = "";
				if (CheckAttribute(pchar, "questTemp.Sharp.PearlAreal.add")) sTemp = pchar.questTemp.Sharp.PearlAreal.add;
				dialog.text = StringFromKey("ForAll_dialog_161", XI_ConvertString(pchar.questTemp.Sharp.PearlAreal + "Pre"), GetConvertStr(pchar.questTemp.Sharp.PearlAreal.Shore, "LocLables.txt"), sTemp, FindDaysString(sti(pchar.questTemp.Sharp.PearlAreal.terms))); //TODO: заменить на падеж
				link.l1 = StringFromKey("ForAll_dialog_162", pchar);
				link.l1.go = "DeckSharp_7";
			}
		break;
		case "DeckSharp_7":
			dialog.text = StringFromKey("ForAll_dialog_165", RandPhraseSimple(
						StringFromKey("ForAll_dialog_163", pchar),
						StringFromKey("ForAll_dialog_164", pchar)));
			link.l1 = StringFromKey("ForAll_dialog_166", pchar);
			link.l1.go = "DeckSharp_8";
		break;
		case "DeckSharp_8":
			dialog.text = StringFromKey("ForAll_dialog_169", RandPhraseSimple(
						StringFromKey("ForAll_dialog_167", pchar),
						StringFromKey("ForAll_dialog_168", DeckSharp8Greeting())));
			link.l1 = StringFromKey("ForAll_dialog_170", pchar);
			link.l1.go = "DeckSharp_8exit";
		break;
		case "DeckSharp_8exit":
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Sharp.PearlAreal.add")) sTemp = pchar.questTemp.Sharp.PearlAreal.add;
			NextDiag.TempNode = "DeckSharp_over";
			npchar.DeckDialogNode = "NewDeckSharp"; //новая нода на палубу
			pchar.questTemp.Sharp = "toPearl"; //флаг квеста - на промысел!!!
			AddQuestRecord("SharpPearl", "5");
			AddQuestUserData("SharpPearl", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("SharpPearl", "sSex1", GetSexPhrase(StringFromKey("SexPhrase_3"), StringFromKey("SexPhrase_4")));
			AddQuestUserData("SharpPearl", "iDay", FindDaysString(sti(pchar.questTemp.Sharp.PearlAreal.terms)));
			AddQuestUserData("SharpPearl", "sAreal", XI_ConvertString(pchar.questTemp.Sharp.PearlAreal + "Pre"));
			AddQuestUserData("SharpPearl", "sTarget", GetConvertStr(pchar.questTemp.Sharp.PearlAreal.Shore, "LocLables.txt") + sTemp);
			pchar.quest.SeaPearl_FirstTime_login.win_condition.l1 = "location";
			pchar.quest.SeaPearl_FirstTime_login.win_condition.l1.location = pchar.questTemp.Sharp.PearlAreal.Island;
			pchar.quest.SeaPearl_FirstTime_login.function = "SeaPearl_FirstTime_login";
			SetTimerFunction("SeaPearl_FirstTime_Late", 0, 0, sti(pchar.questTemp.Sharp.PearlAreal.terms));
			if (pchar.location != "Deck_Near_Ship")
			{
				LAi_SetActorTypeNoGroup(npchar);
				LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "OpenTheDoors", 15.0);
			}
			// Удаляем Шарпа с карты
			Map_ReleaseQuestEncounter(NPChar.id);
			//			group_DeleteGroup("Sharp_Group");
			// Таскаем за собой
			SetCompanionIndex(PChar, -1, sti(NPChar.index));
			SetCharacterRemovable(NPChar, false);
			SetBaseShipData(NPChar);
			ShipOverhaul(NPChar);
			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");

			RemoveLandQuestmark_Main(npchar, "SharpPearl");

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// Первый раз - не успели, или поймали мало жемчужин
		case "SharpPearlFirst_Late":
			chrDisableReloadToLocation = false;
			LAi_LockFightMode(pchar, false);
			Dialog.Text = StringFromKey("ForAll_dialog_171", pchar);
			link.l1 = PCharRepPhrase(
						StringFromKey("ForAll_dialog_172"),
						StringFromKey("ForAll_dialog_175", RandPhraseSimple(
								StringFromKey("ForAll_dialog_173"),
								StringFromKey("ForAll_dialog_174"))));
			link.l1.go = "Exit_SharpPearlFirst_Late";
		break;
		case "Exit_SharpPearlFirst_Late":
			pchar.questTemp.Sharp = "sharpFirstPearlFail";
			pchar.questTemp.Sharp.PearlFirstTimeIsFail = true;
			DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
			NextDiag.TempNode = "DeckSharp_overBad";
			NextDiag.CurrentNode = NextDiag.TempNode;
			RemoveCharacterCompanion(PChar, NPChar);
			AddQuestRecord("SharpPearl", "17");
			AddLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl_SeekSpy", "");
			AddMapQuestMark_Major("Shore9", "SharpPearl_SeekSpy", "");
			AddMapQuestMark_Major("Shore55", "SharpPearl_SeekSpy", "");

			if (pchar.location != "Ship_deck")
			{
				LAi_SetActorTypeNoGroup(npchar);
				LAi_ActorRunToLocation(npchar, "reload", "reload1", "", "", "", "OpenTheDoors", 15.0);
			}
			else
			{
				LAi_SetWarriorType(NPChar);
				PChar.quest.Munity = "Deads";
				DoQuestCheckDelay("Exit_Sea", 1.0);
			}

			DialogExit();
		break;
		// Первый раз - успех и дальнейшая дележка
		case "SharpPearlFirst_Success":
			iSmallPearl = 0;
			iBigPearl = 0;
			ConvertPinctadaToPearlItems(pchar, &iSmallPearl, &iBigPearl);
			ItemTakeEx(pchar, "jewelry12,jewelry11", "" + iSmallPearl + "," + iBigPearl);
			pchar.questTemp.Sharp.PearlAreal.SmallPearlQty = iSmallPearl;
			pchar.questTemp.Sharp.PearlAreal.BigPearlQty = iBigPearl;

			pchar.questTemp.Sharp.PearlAreal.SmallPearlQty.Part = MakeInt(sti(pchar.questTemp.Sharp.PearlAreal.SmallPearlQty) / 5);
			pchar.questTemp.Sharp.PearlAreal.BigPearlQty.Part = MakeInt(sti(pchar.questTemp.Sharp.PearlAreal.BigPearlQty) / 5);
			Dialog.Text = StringFromKey("ForAll_dialog_176", pchar, pchar.questTemp.Sharp.PearlAreal.SmallPearlQty, pchar.questTemp.Sharp.PearlAreal.BigPearlQty, pchar.questTemp.Sharp.PearlAreal.SmallPearlQty.Part, pchar.questTemp.Sharp.PearlAreal.BigPearlQty.Part);
			link.l1 = StringFromKey("ForAll_dialog_177", pchar);
			link.l1.go = "SharpPearlFirst_Success_1";
		break;
		case "SharpPearlFirst_Success_1":
			Dialog.Text = StringFromKey("ForAll_dialog_178", pchar);
			link.l1 = StringFromKey("ForAll_dialog_179");
			link.l1.go = "SharpPearlFirst_Success_2_Pay";
			link.l2 = StringFromKey("ForAll_dialog_180");
			link.l2.go = "SharpPearlFirst_Success_2_NotPay";
		break;
		case "SharpPearlFirst_Success_2_Pay":
			Dialog.Text = StringFromKey("ForAll_dialog_181", GetFullName(PChar));
			link.l1 = StringFromKey("ForAll_dialog_182");
			link.l1.go = "Exit_SharpPearlFirst_Success_Pay";
		break;
		case "SharpPearlFirst_Success_2_NotPay":
			Dialog.Text = StringFromKey("ForAll_dialog_183");
			link.l1 = StringFromKey("ForAll_dialog_184");
			link.l1.go = "Exit_SharpPearlFirst_Success_NotPay";
		break;
		case "Exit_SharpPearlFirst_Success_Pay":
			AddQuestRecord("SharpPearl", "18");
			AddQuestUserData("SharpPearl", "sSex", GetSexPhrase("", "а"));
			pchar.questTemp.Sharp = "grantMeRevenge";
			AddLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl_SeekSpy", "");
			AddMapQuestMark_Major("Shore9", "SharpPearl_SeekSpy", "");
			AddMapQuestMark_Major("Shore55", "SharpPearl_SeekSpy", "");

			RemoveCharacterCompanion(PChar, NPChar);
			DoQuestFunctionDelay("SeaPearl_FirstTime_SharpTakePearls", 0.0);

			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "", "", "", "OpenTheDoors", 15.0);

			DialogExit();
		break;
		case "Exit_SharpPearlFirst_Success_NotPay":
			pchar.questTemp.Sharp = "FirstPearlNotPay";
			RemoveCharacterCompanion(PChar, NPChar);

			SeaPearl_FirstTime_SharpDuel();

			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "", "", "", "OpenTheDoors", 15.0);

			DialogExit();
		break;
		//капитан Шарп, последующие разговоры на палубе
		case "NewDeckSharp":
			dialog.text = StringFromKey("ForAll_dialog_185", pchar);
			link.l1 = StringFromKey("ForAll_dialog_186");
			link.l1.go = "NewDeckSharp_1";
			//блокировка генератора, если взят грабеж от Моргана
			if (pchar.questTemp.piratesLine == "PearlQ4_toTerks")
			{
				dialog.text = StringFromKey("ForAll_dialog_187", pchar);
				link.l1 = StringFromKey("ForAll_dialog_188");
				link.l1.go = "exit";
				NextDiag.TempNode = "DeckSharp_overBad";
				pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
				pchar.questTemp.Sharp.brothelChance = rand(10);
				// DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
				AddQuestRecord("SharpPearl", "13");
				CloseQuestHeader("SharpPearl");
			}
		break;
		case "NewDeckSharp_1":
			dialog.text = StringFromKey("ForAll_dialog_189", pchar);
			link.l1 = StringFromKey("ForAll_dialog_190");
			link.l1.go = "NewDeckSharp_2";
		break;
		case "NewDeckSharp_2":
			if (and(pchar.questTemp.Sharp.SeekSpy == "alwaysKnow" || pchar.questTemp.Sharp.SeekSpy == "over", !CheckAttribute(pchar, "questTemp.Sharp.SeekSpy.NewAgentPlanted")))
			{
				dialog.text = StringFromKey("ForAll_dialog_191", pchar);
				link.l1 = StringFromKey("ForAll_dialog_192");
				link.l1.go = "NewDeckSharp_2exit";
			}
			else
			{
				dialog.text = StringFromKey("ForAll_dialog_193", pchar);
				link.l1 = StringFromKey("ForAll_dialog_194");
				link.l1.go = "NewDeckSharp_3";
			}
		break;
		case "NewDeckSharp_2exit":
			CloseQuestHeader("SharpPearl");
			NextDiag.TempNode = "DeckSharp_noWork";
			pchar.questTemp.Sharp = "over";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			if (pchar.location != "Deck_Near_Ship")
			{
				LAi_SetActorTypeNoGroup(npchar);
				LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 15.0);
			}
		break;
		case "NewDeckSharp_3":
			dialog.text = StringFromKey("ForAll_dialog_195", pchar);
			link.l1 = StringFromKey("ForAll_dialog_196");
			link.l1.go = "NewDeckSharp_4";
		break;
		case "NewDeckSharp_4":
			dialog.text = StringFromKey("ForAll_dialog_197", FindMoneyString(sti(pchar.questTemp.Sharp.price)));
			link.l1 = StringFromKey("ForAll_dialog_198");
			link.l1.go = "NewDeckSharp_noMoney";
			if (sti(pchar.money) >= sti(pchar.questTemp.Sharp.price))
			{
				link.l2 = StringFromKey("ForAll_dialog_199", pchar);
				link.l2.go = "NewDeckSharp_GiveMoney";
			}
		break;

		case "NewDeckSharp_GiveMoney":
			dialog.text = StringFromKey("ForAll_dialog_200", pchar);
			link.l1 = StringFromKey("ForAll_dialog_201");
			link.l1.go = "NewDeckSharp_8";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Sharp.price));
		break;
		case "NewDeckSharp_noMoney":
			if ((sti(pchar.questTemp.Sharp.price) * 10) < sti(pchar.money)) //TODO было бы неплохо добавить влияние Обаяния куда-то сюда.
			{
				if (pchar.location == "Deck_Near_Ship")
				{
					dialog.text = StringFromKey("ForAll_dialog_202", pchar, pchar.name);
					link.l1 = StringFromKey("ForAll_dialog_203", pchar);
				}
				else
				{
					dialog.text = StringFromKey("ForAll_dialog_204", pchar, pchar.name);
					link.l1 = StringFromKey("ForAll_dialog_205");
				}
				link.l1.go = "NewDeckSharp_5";
			}
			else
			{
				if (sti(pchar.questTemp.Sharp.price.evil))
				{
					//Шарп не в настроении
					dialog.text = StringFromKey("ForAll_dialog_206", pchar);
					link.l1 = StringFromKey("ForAll_dialog_207", pchar);
					link.l1.go = "NewDeckSharp_7";
					if (sti(pchar.money) >= sti(pchar.questTemp.Sharp.price))
					{
						link.l2 = StringFromKey("ForAll_dialog_208");
						link.l2.go = "NewDeckSharp_GiveMoney";
					}
				}
				else
				{
					dialog.text = StringFromKey("ForAll_dialog_209");
					link.l1 = StringFromKey("ForAll_dialog_210");
					link.l1.go = "NewDeckSharp_8";
				}
			}
		break;
		case "NewDeckSharp_5":
			dialog.text = StringFromKey("ForAll_dialog_211", pchar, pchar.name);
			link.l1 = StringFromKey("ForAll_dialog_212");
			link.l1.go = "NewDeckSharp_6";
			link.l2 = StringFromKey("ForAll_dialog_213");
			link.l2.go = "NewDeckSharp_7";
		break;
		case "NewDeckSharp_6":
			dialog.text = StringFromKey("ForAll_dialog_214", pchar);
			link.l1 = StringFromKey("ForAll_dialog_215");
			link.l1.go = "NewDeckSharp_8";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Sharp.price));
		break;
		case "NewDeckSharp_7":
			dialog.text = StringFromKey("ForAll_dialog_216");
			link.l1 = StringFromKey("ForAll_dialog_217");
			link.l1.go = "NewDeckSharp_7exit";
		break;
		case "NewDeckSharp_7exit":
			AddQuestRecord("SharpPearl", "10");
			CloseQuestHeader("SharpPearl");
			pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
			pchar.questTemp.Sharp.brothelChance = rand(10);
			NextDiag.TempNode = "DeckSharp_overBad";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			if (pchar.location != "Deck_Near_Ship")
			{
				LAi_SetActorTypeNoGroup(npchar);
				LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "OpenTheDoors", 15.0);
			}
		break;
		case "NewDeckSharp_8":
			GetPerlShore(); //где промысел ведется
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Sharp.PearlAreal.add")) sTemp = pchar.questTemp.Sharp.PearlAreal.add;
			dialog.text = StringFromKey("ForAll_dialog_218", XI_ConvertString(pchar.questTemp.Sharp.PearlAreal + "Pre"), GetConvertStr(pchar.questTemp.Sharp.PearlAreal.Shore, "LocLables.txt"), sTemp, FindDaysString(sti(pchar.questTemp.Sharp.PearlAreal.terms))); //TODO: заменить на падеж
			link.l1 = StringFromKey("ForAll_dialog_219", pchar);
			link.l1.go = "NewDeckSharp_9";
		break;
		case "NewDeckSharp_9":
			dialog.text = StringFromKey("ForAll_dialog_222", RandPhraseSimple(
						StringFromKey("ForAll_dialog_220", pchar),
						StringFromKey("ForAll_dialog_221", pchar)));
			link.l1 = StringFromKey("ForAll_dialog_223", pchar);
			link.l1.go = "NewDeckSharp_9exit";
		break;
		case "NewDeckSharp_9exit":
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Sharp.PearlAreal.add")) sTemp = pchar.questTemp.Sharp.PearlAreal.add;
			NextDiag.TempNode = "DeckSharp_over";
			npchar.DeckDialogNode = "NewDeckSharp"; //новая нода на палубу
			pchar.questTemp.Sharp = "toPearl"; //флаг квеста - на промысел!!!
			AddQuestRecord("SharpPearl", "5");
			AddQuestUserData("SharpPearl", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("SharpPearl", "sSex1", GetSexPhrase(StringFromKey("SexPhrase_3"), StringFromKey("SexPhrase_4")));
			AddQuestUserData("SharpPearl", "iDay", FindDaysString(sti(pchar.questTemp.Sharp.PearlAreal.terms)));
			AddQuestUserData("SharpPearl", "sAreal", XI_ConvertString(pchar.questTemp.Sharp.PearlAreal + "Pre"));
			AddQuestUserData("SharpPearl", "sTarget", GetConvertStr(pchar.questTemp.Sharp.PearlAreal.Shore, "LocLables.txt") + sTemp);
			pchar.quest.SeaPearl_login.win_condition.l1 = "location";
			pchar.quest.SeaPearl_login.win_condition.l1.location = pchar.questTemp.Sharp.PearlAreal.Island;
			pchar.quest.SeaPearl_login.function = "SeaPearl_login";
			SetTimerFunction("SeaPearl_Late", 0, 0, sti(pchar.questTemp.Sharp.PearlAreal.terms));
			if (pchar.location != "Deck_Near_Ship")
			{
				LAi_SetActorTypeNoGroup(npchar);
				LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "OpenTheDoors", 15.0);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "DeckSharp_over":
			dialog.text = StringFromKey("ForAll_dialog_224", pchar);
			link.l1 = StringFromKey("ForAll_dialog_225");
			link.l1.go = "exit";
		break;
		case "DeckSharp_overBad":
			dialog.text = StringFromKey("ForAll_dialog_226");
			link.l1 = StringFromKey("ForAll_dialog_227");
			link.l1.go = "exit";
		break;
		case "DeckSharp_noWork":
			dialog.text = StringFromKey("ForAll_dialog_228", pchar);
			link.l1 = StringFromKey("ForAll_dialog_229");
			link.l1.go = "exit";
			CloseQuestHeader("SharpPearl");
		break;
		//капитан Шарп, первый разговор в городе на улице
		case "CitySharp":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = StringFromKey("ForAll_dialog_230", pchar.lastname);
				link.l1 = StringFromKey("ForAll_dialog_231", pchar);
				link.l1.go = "CitySharp_1";
				npchar.quest.meeting = true;
			}
			else
			{
				dialog.text = StringFromKey("ForAll_dialog_232", pchar, GetFullName(pchar));
				link.l1 = StringFromKey("ForAll_dialog_233", pchar);
				link.l1.go = "CitySharp_2";
			}
		break;

		case "CitySharp_1":
			dialog.text = StringFromKey("ForAll_dialog_234");
			link.l1 = StringFromKey("ForAll_dialog_235", pchar);
			link.l1.go = "DeckSharp_2";
			//блокировка генератора, если взят грабеж от Моргана
			if (pchar.questTemp.piratesLine == "PearlQ4_toTerks")
			{
				dialog.text = StringFromKey("ForAll_dialog_236", pchar);
				link.l1 = StringFromKey("ForAll_dialog_237");
				link.l1.go = "exit";
				NextDiag.TempNode = "DeckSharp_overBad";
				pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
				pchar.questTemp.Sharp.brothelChance = 1; //первый базар должен быть не в борделе
				// DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
				AddQuestRecord("SharpPearl", "13");
				CloseQuestHeader("SharpPearl");
			}
		break;
		case "CitySharp_2":
			dialog.text = StringFromKey("ForAll_dialog_238", pchar, pchar.name);
			link.l1 = StringFromKey("ForAll_dialog_239", pchar);
			link.l1.go = "CitySharp_3";
			//блокировка генератора, если взят грабеж от Моргана
			if (pchar.questTemp.piratesLine == "PearlQ4_toTerks")
			{
				dialog.text = StringFromKey("ForAll_dialog_240", pchar);
				link.l1 = StringFromKey("ForAll_dialog_241");
				link.l1.go = "exit";
				NextDiag.TempNode = "DeckSharp_overBad";
				pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
				pchar.questTemp.Sharp.brothelChance = rand(10);
				// DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
				AddQuestRecord("SharpPearl", "13");
				CloseQuestHeader("SharpPearl");
			}
		break;
		case "CitySharp_3":
			dialog.text = StringFromKey("ForAll_dialog_242", pchar);
			link.l1 = StringFromKey("ForAll_dialog_243", pchar);
			link.l1.go = "NewDeckSharp_2";
		break;
		//капитан Шарп в борделе
		case "BrothelSharp":
			dialog.text = StringFromKey("ForAll_dialog_244", pchar, pchar.name);
			link.l1 = StringFromKey("ForAll_dialog_245", pchar);
			link.l1.go = "BrothelSharp_1";
			chrDisableReloadToLocation = false;
			//блокировка генератора, если взят грабеж от Моргана
			if (pchar.questTemp.piratesLine == "PearlQ4_toTerks")
			{
				dialog.text = StringFromKey("ForAll_dialog_246", pchar);
				link.l1 = StringFromKey("ForAll_dialog_247");
				link.l1.go = "exit";
				NextDiag.TempNode = "DeckSharp_overBad";
				pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
				pchar.questTemp.Sharp.brothelChance = rand(10);
				// DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
				AddQuestRecord("SharpPearl", "13");
				CloseQuestHeader("SharpPearl");
			}
		break;
		case "BrothelSharp_1":
			dialog.text = StringFromKey("ForAll_dialog_248", pchar);
			link.l1 = StringFromKey("ForAll_dialog_249");
			link.l1.go = "NewDeckSharp_2";
		break;
		//Эмилио Гарсиа. в бухте Сан-Хуна дель Норте
		case "SharpSeekSpy_Emi":
			dialog.text = StringFromKey("ForAll_dialog_250");
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharpSeekSpy_caveDialog");
			RemoveLandQuestmark_Main(npchar, "SharpPearl_SeekSpy");
		break;
		case "SharpSeekSpy_fri":
			dialog.text = StringFromKey("ForAll_dialog_251", GetFullName(pchar));
			link.l1 = StringFromKey("ForAll_dialog_252", sTemp);
			link.l1.go = "SharpSeekSpy_fri_1";
		break;
		case "SharpSeekSpy_fri_1":
			dialog.text = StringFromKey("ForAll_dialog_253");
			link.l1 = StringFromKey("ForAll_dialog_254", pchar);
			link.l1.go = "SharpSeekSpy_fri_2";
		break;
		case "SharpSeekSpy_fri_2":
			dialog.text = StringFromKey("ForAll_dialog_255");
			link.l1 = StringFromKey("ForAll_dialog_256", pchar);
			link.l1.go = "SharpSeekSpy_fri_3";
		break;
		case "SharpSeekSpy_fri_3":
			dialog.text = StringFromKey("ForAll_dialog_257");
			link.l1 = StringFromKey("ForAll_dialog_258", pchar);
			link.l1.go = "SharpSeekSpy_fri_4";
		break;
		case "SharpSeekSpy_fri_4":
			dialog.text = StringFromKey("ForAll_dialog_259");
			link.l1 = StringFromKey("ForAll_dialog_260");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharpSeekSpy_caveDialog_2");
		break;
		case "SharpSeekSpy_Emi_1":
			dialog.text = StringFromKey("ForAll_dialog_261", pchar);
			link.l1 = StringFromKey("ForAll_dialog_262");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharpSeekSpy_caveDialog_3");
		break;
		// Шарп. После убийства информатора
		case "Sharp_Encounter_1":
			dialog.text = StringFromKey("ForAll_dialog_263", GetFullName(pchar));
			link.l1 = StringFromKey("ForAll_dialog_264");
			link.l1.go = "Sharp_Encounter_2";
		break;
		case "Sharp_Encounter_2":
			dialog.text = StringFromKey("ForAll_dialog_265");
			link.l1 = StringFromKey("ForAll_dialog_266");
			link.l1.go = "Sharp_Encounter_3";
		break;
		case "Sharp_Encounter_3":
			dialog.text = StringFromKey("ForAll_dialog_267", pchar);
			sTemp = StringFromKey("ForAll_dialog_268", pchar);
			link.l1 = StringFromKey("ForAll_dialog_269", sTemp);
			link.l1.go = "Sharp_Encounter_Duel";
			link.l2 = StringFromKey("ForAll_dialog_270", pchar, sTemp);
			link.l2.go = "Sharp_Encounter_TryNegotiation";
		break;
		case "Sharp_Encounter_Duel":
			dialog.text = StringFromKey("ForAll_dialog_271");
			link.l1 = "...";
			link.l1.go = "Exit_Sharp_Encounter_Duel";
		break;
		case "Exit_Sharp_Encounter_Duel":
			NextDiag.TempNode = "DeckSharp_overBad";
			NextDiag.CurrentNode = NextDiag.TempNode;

			pchar.questTemp.Sharp = "sharpRevengeToFight";
			RemoveLandQuestmark_Main(npchar, "SharpPearl");

			AddDialogExitQuestFunction("SeaPearl_SharpRevenge_AfterFailureNegotiation");

			DialogExit();
		break;
		case "Sharp_Encounter_TryNegotiation":
		//			if (GetCharacterSPECIAL(pchar, SPECIAL_C) >= 7)
			if (PlayerRPGCheck_SPECIAL(SPECIAL_C, 7))
			{
				dialog.text = StringFromKey("ForAll_dialog_272");
				link.l1 = StringFromKey("ForAll_dialog_273");
				link.l1.go = "Exit_Sharp_Encounter_NegotiationSuccess";
			}
			else
			{
				dialog.text = StringFromKey("ForAll_dialog_274");
				link.l1 = StringFromKey("ForAll_dialog_275");
				link.l1.go = "Exit_Sharp_Encounter_Duel";
			}
		break;
		case "Exit_Sharp_Encounter_NegotiationSuccess":
			NextDiag.TempNode = "Sharp_Encounter_KnowYouGood";
			NextDiag.CurrentNode = NextDiag.TempNode;

			pchar.questTemp.Sharp = "sharpWaitNewAgent";
			RemoveLandQuestmark_Main(npchar, "SharpPearl");

			AddDialogExitQuestFunction("SeaPearl_SharpRevenge_NegotiationSuccessContinue");

			DialogExit();
		break;
		case "Sharp_Encounter_KnowYouGood":
			NextDiag.TempNode = "DeckSharp_overBad";
			NextDiag.CurrentNode = NextDiag.TempNode;

			dialog.text = StringFromKey("ForAll_dialog_276");
			link.l1 = StringFromKey("ForAll_dialog_277");
			link.l1.go = "Exit_Sharp_Encounter_KnowYouGood";
		break;
		case "Exit_Sharp_Encounter_KnowYouGood":
			AddDialogExitQuestFunction("SeaPearl_SharpRevenge_AfterSuccessNegotiation");

			DialogExit();
		break;
		// Шарп сдается в последний момент
		case "Sharp_Encounter_AboardCabin":
			dialog.text = StringFromKey("ForAll_dialog_278");
			link.l1 = StringFromKey("ForAll_dialog_279");
			link.l1.go = "Sharp_Encounter_AboardCabin_1";
		break;
		case "Sharp_Encounter_AboardCabin_1":
			dialog.text = StringFromKey("ForAll_dialog_280");
			link.l1 = StringFromKey("ForAll_dialog_281");
			link.l1.go = "Exit_Sharp_Encounter_AboardCabin";
		break;
		case "Exit_Sharp_Encounter_AboardCabin":
			pchar.questTemp.Sharp = "sharpPrisoner";

			QuestAboardCabinDialogQuestSurrender();
			DialogExit();
		break;
		// Шарп пленник - разговоры в трюме
		case "Sharp_Prisoner":
			sTemp = StringFromKey("ForAll_dialog_282", pchar);

			dialog.text = NPCStringReactionRepeat(
				StringFromKey("ForAll_dialog_283", GetFullName(pchar)), sTemp, sTemp, sTemp, "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = StringFromKey("ForAll_dialog_284");
			link.l1.go = "Sharp_Prisoner_BetraySpain";
			link.l2 = StringFromKey("ForAll_dialog_285");
			link.l2.go = "Sharp_Prisoner_Bargain";
			link.l3 = StringFromKey("ForAll_dialog_286");
			link.l3.go = "Exit_Sharp_Prisoner_Kill";
			link.l4 = StringFromKey("ForAll_dialog_287");
			link.l4.go = "Exit_Sharp_Prisoner";
		break;
		case "Sharp_Prisoner_SecondTime":
			dialog.text = StringFromKey("ForAll_dialog_288");
			if (!CheckAttribute(&TEV, "Sharp_Prisoner_DialogChoosen.BetraySpain") && !CheckAttribute(&TEV, "Sharp_Prisoner_DialogChoosen.Bargain"))
			{
				link.l1 = StringFromKey("ForAll_dialog_289");
				link.l1.go = "Sharp_Prisoner_BetraySpain";
			}
			if (!CheckAttribute(&TEV, "Sharp_Prisoner_DialogChoosen.Bargain"))
			{
				link.l2 = StringFromKey("ForAll_dialog_290");
				link.l2.go = "Sharp_Prisoner_Bargain";

				link.l3 = StringFromKey("ForAll_dialog_291");
				link.l3.go = "Exit_Sharp_Prisoner_Kill";
			}
			link.l4 = StringFromKey("ForAll_dialog_292", pchar);
			link.l4.go = "Exit_Sharp_Prisoner";
		break;
		case "Sharp_Prisoner_BetraySpain":
			pchar.quest.SeaPearl_SharpPrisoner_ForgotSpeaking.over = "yes";
			TEV.Sharp_Prisoner_DialogChoosen.BetraySpain = true;
			RemoveLandQuestmark_Main(npchar, "SharpPearl");

			NextDiag.TempNode = "Sharp_Prisoner_SecondTime";
			NextDiag.CurrentNode = NextDiag.TempNode;

			dialog.text = StringFromKey("ForAll_dialog_293");
			link.l1 = StringFromKey("ForAll_dialog_294");
			link.l1.go = "Exit_Sharp_Prisoner_BetraySpain";
		break;
		case "Exit_Sharp_Prisoner_BetraySpain":
			DialogExit();
		break;
		case "Sharp_Prisoner_Bargain":
			pchar.quest.SeaPearl_SharpPrisoner_ForgotSpeaking.over = "yes";
			TEV.Sharp_Prisoner_DialogChoosen.Bargain = true;
			NextDiag.TempNode = "Sharp_Prisoner_AfterBatter";
			NextDiag.CurrentNode = NextDiag.TempNode;

			sTemp = StringFromKey("ForAll_dialog_295");
			dialog.text = StringFromKey("ForAll_dialog_296", pchar, sTemp);

			sTemp = StringFromKey("ForAll_dialog_297");
			if (pchar.sex == "man")
			{
				link.l1 = sTemp;
				link.l1.go = "Exit_Sharp_Prisoner_Batter";
			}
			else
			{
				link.l1 = StringFromKey("ForAll_dialog_298", sTemp);
				link.l1.go = "Exit_Sharp_Prisoner_BatterCallBoatswain";
			}

			RemoveLandQuestmark_Main(npchar, "SharpPearl");
		break;
		case "Exit_Sharp_Prisoner_Batter":
			AddDialogExitQuestFunction("SeaPearl_SharpPrisoner_StartBatter");
			DialogExit();
		break;
		case "Exit_Sharp_Prisoner_BatterCallBoatswain":
			TEV.Sharp_Prisoner_DialogChoosen.Bargain = true;

			AddDialogExitQuestFunction("SeaPearl_SharpPrisoner_StartBatterCallBoatswain");
			DialogExit();
		break;
		case "Sharp_Prisoner_StartBatterByBoatswain":
			dialog.text = StringFromKey("ForAll_dialog_299");

			link.l1 = StringFromKey("ForAll_dialog_300");
			link.l1.go = "Sharp_Prisoner_StartBatterByBoatswain_1";
		break;
		case "Sharp_Prisoner_StartBatterByBoatswain_1":
			dialog.text = StringFromKey("ForAll_dialog_301");

			link.l1 = "...";
			link.l1.go = "Exit_Sharp_Prisoner_StartBatterByBoatswain";
		break;
		case "Exit_Sharp_Prisoner_StartBatterByBoatswain":
			AddDialogExitQuestFunction("SeaPearl_SharpPrisoner_StartBatterByBoatswain");
			DialogExit();
		break;
		// case "Sharp_Prisoner_Kill":
		// dialog.text = "Шарпа пускают по доске.";

		// link.l1 = "...";
		// link.l1.go = "Exit_Sharp_Prisoner_Kill";
		// break;
		case "Exit_Sharp_Prisoner_Kill":
			pchar.quest.SeaPearl_SharpPrisoner_ForgotSpeaking.over = "yes";
			RemoveLandQuestmark_Main(npchar, "SharpPearl");

			AddDialogExitQuestFunction("SeaPearl_SharpPrisoner_KillSharp");
			DialogExit();
		break;
		case "Exit_Sharp_Prisoner":
			DialogExit();
		break;
		case "Sharp_Prisoner_AfterBatter":
			LAi_LockFightMode(pchar, false);
			dialog.text = StringFromKey("ForAll_dialog_302");
			link.l1 = StringFromKey("ForAll_dialog_303");
			link.l1.go = "Sharp_Prisoner_AfterBatter_1";
		break;
		case "Sharp_Prisoner_AfterBatter_1":
		// неподалёку от мыса Исабела
			dialog.text = StringFromKey("ForAll_dialog_304", XI_ConvertString("Shore32" + "Gen"));
			link.l1 = StringFromKey("ForAll_dialog_305");
			link.l1.go = "Exit_Sharp_Prisoner_AfterBatter";
		break;
		case "Exit_Sharp_Prisoner_AfterBatter":
			NextDiag.TempNode = "Sharp_Prisoner_SecondTime";
			NextDiag.CurrentNode = NextDiag.TempNode;

			AddDialogExitQuestFunction("SeaPearl_SharpPrisoner_AfterBatter_DialogExit");
			DialogExit();
		break;
		// диалог Шарпа в тайнике, момент освобождения
		case "SharpPrisoner_NearGrot":
			dialog.text = StringFromKey("ForAll_dialog_306");
			link.l1 = StringFromKey("ForAll_dialog_307");
			link.l1.go = "Exit_SharpPrisoner_NearGrot";
		break;
		case "Exit_SharpPrisoner_NearGrot":
			AddDialogExitQuestFunction("SeaPearl_SharpPrisoner_GiveFree_RunToGrot");
			DialogExit();
		break;
		case "SharpPrisoner_InPlace":
			dialog.text = StringFromKey("ForAll_dialog_308");
			link.l1 = StringFromKey("ForAll_dialog_309");
			link.l1.go = "Exit_SharpPrisoner_InPlace";
		break;
		case "Exit_SharpPrisoner_InPlace":
			NextDiag.TempNode = "SharpPrisoner_NearChest";
			NextDiag.CurrentNode = NextDiag.TempNode;

			AddDialogExitQuestFunction("SeaPearl_SharpPrisoner_GiveFree_TeleportToChest");
			DialogExit();
		break;
		case "SharpPrisoner_NearChest":
			dialog.text = StringFromKey("ForAll_dialog_310");
			link.l1 = StringFromKey("ForAll_dialog_311");
			link.l1.go = "Exit_SharpPrisoner_NearChest";
		break;
		case "Exit_SharpPrisoner_NearChest":
			NextDiag.TempNode = "SharpPrisoner_GiveFree";
			NextDiag.CurrentNode = NextDiag.TempNode;

			AddDialogExitQuestFunction("SeaPearl_SharpPrisoner_GiveFree_TeleportToRest");
			DialogExit();
		break;
		case "SharpPrisoner_GiveFree":
			dialog.text = StringFromKey("ForAll_dialog_312");
			link.l1 = StringFromKey("ForAll_dialog_313");
			link.l1.go = "SharpPrisoner_GiveFree_1";

			AddMoneyToCharacter(pchar, 50000);
			// сокровища выдадим позже - чтобы избежать перегруза
			LogSound_WithNotify(StringFromKey("InfoMessages_197"), "Important_item", "ICollection");
		break;
		case "SharpPrisoner_GiveFree_1":
			dialog.text = StringFromKey("ForAll_dialog_314");

			link.l1 = StringFromKey("ForAll_dialog_315");
			link.l1.go = "Exit_SharpPrisoner_GiveFree_ReleaseSharp";

			link.l2 = StringFromKey("ForAll_dialog_316");
			link.l2.go = "SharpPrisoner_GiveFree_HireSharp";

		break;
		case "Exit_SharpPrisoner_GiveFree_ReleaseSharp":
			LAi_SetActorType(NPChar);
			LAi_SetPlayerType(pchar);
			LAi_ActorRunToLocation(NPChar, "reload", LAi_FindNearestLocator2NPC(NPChar, "reload"), "none", "", "", "OpenTheDoors", -1.0);

			SeaPearl_SharpPrisoner_AddTreasureItems();
			AddDialogExitQuest("SeaPearl_SharpPrisoner_GiveFree_ReleaseSharp");
			RemoveLandQuestmark_Main(npchar, "SharpPearl");
			DialogExit();
		break;
		case "SharpPrisoner_GiveFree_HireSharp":
			dialog.text = StringFromKey("ForAll_dialog_317", pchar);
			link.l1 = StringFromKey("ForAll_dialog_318");
			link.l1.go = "Exit_SharpPrisoner_GiveFree_ReleaseSharp";

			if (PlayerRPGCheck_SPECIAL(SPECIAL_C, 9) && PlayerRPGCheck_Skill(SKILL_LEADERSHIP, 50, false))
			{
				if (!isMainCharacterPatented() || sti(Items[sti(pchar.EquipedPatentId)].Nation) != SPAIN)
				{
					dialog.text = StringFromKey("ForAll_dialog_319", pchar);
					link.l1 = StringFromKey("ForAll_dialog_320", pchar);
					link.l1.go = "SharpPrisoner_GiveFree_HireSharp_1";
				}
				else
				{
					Notification(StringFromKey("InfoMessages_243"), "spahunter");
				}
			}
		break;
		case "SharpPrisoner_GiveFree_HireSharp_1":
			dialog.text = StringFromKey("ForAll_dialog_321");
			link.l1 = StringFromKey("ForAll_dialog_322");
			link.l1.go = "Exit_SharpPrisoner_GiveFree_HireSharp";
		break;
		case "Exit_SharpPrisoner_GiveFree_HireSharp":
			AddMoneyToCharacter(pchar, -50000);

			LAi_SetActorType(NPChar);
			LAi_SetPlayerType(pchar);
			LAi_SetRolyPoly(npchar, true); //неваляха
			LAi_ActorRunToLocation(NPChar, "reload", LAi_FindNearestLocator2NPC(NPChar, "reload"), "none", "", "", "OpenTheDoors", -1.0);

			SeaPearl_SharpPrisoner_AddTreasureItems();
			AddDialogExitQuest("SeaPearl_SharpPrisoner_GiveFree_HireSharp");
			RemoveLandQuestmark_Main(npchar, "SharpPearl");
			DialogExit();
		break;
		//--------------------------- квест официантки --------------------------------
		//грабитель
		case "WaitressBerglar":
			LAi_LockFightMode(pchar, false);
			dialog.text = StringFromKey("ForAll_dialog_323");
			link.l1 = StringFromKey("ForAll_dialog_324");
			link.l1.go = "WaitressBerglar_1";
		break;
		case "WaitressBerglar_1":
			dialog.text = StringFromKey("ForAll_dialog_325");
			link.l1 = StringFromKey("ForAll_dialog_326", pchar.questTemp.different.FackWaitress.Name);
			link.l1.go = "WaitressBerglar_2";
		break;
		case "WaitressBerglar_2":
			dialog.text = StringFromKey("ForAll_dialog_327");
			link.l1 = StringFromKey("ForAll_dialog_328");
			link.l1.go = "WaitressBerglar_fight";
			link.l2 = StringFromKey("ForAll_dialog_329");
			link.l2.go = "WaitressBerglar_take";
		break;
		case "WaitressBerglar_take":
			dialog.text = StringFromKey("ForAll_dialog_330");
			link.l1 = StringFromKey("ForAll_dialog_331");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_outRoom");
		break;
		case "WaitressBerglar_fight":
			dialog.text = StringFromKey("ForAll_dialog_332");
			link.l1 = StringFromKey("ForAll_dialog_333");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fight");
		break;
		//официантка
		case "Waitress":
			LAi_LockFightMode(pchar, false);
			dialog.text = StringFromKey("ForAll_dialog_334");
			link.l1 = StringFromKey("ForAll_dialog_335");
			link.l1.go = "Waitress_1";
		break;
		case "Waitress_1":
			dialog.text = StringFromKey("ForAll_dialog_336");
			link.l1 = StringFromKey("ForAll_dialog_337");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fack");
		break;
		//--------------------------- догнать кэпа, потерявшего судовой журнал --------------------------------
		//встретил в городе
		case "PortmansCap":
			dialog.text = StringFromKey("ForAll_dialog_338", GetFullName(npchar), GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Acc")), npchar.Ship.name);
			link.l1 = StringFromKey("ForAll_dialog_339", pchar);
			link.l1.go = "PortmansCap_1";
		break;
		case "PortmansCap_1":
			dialog.text = StringFromKey("ForAll_dialog_340", pchar);
			link.l1 = StringFromKey("ForAll_dialog_341", pchar, XI_ConvertString("Colony" + npchar.quest.firstCity + "Gen"));
			link.l1.go = "PortmansCap_2";
		break;
		case "PortmansCap_2":
			dialog.text = StringFromKey("ForAll_dialog_342");
			link.l1 = StringFromKey("ForAll_dialog_343");
			link.l1.go = "PortmansCap_3";
		break;
		case "PortmansCap_3":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = StringFromKey("ForAll_dialog_344", FindMoneyString(sti(npchar.quest.money)));
				link.l1 = StringFromKey("ForAll_dialog_345");
				link.l1.go = "PortmansCap_4";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = StringFromKey("ForAll_dialog_346", FindMoneyString(sti(npchar.quest.money)));
					link.l1 = StringFromKey("ForAll_dialog_347");
					link.l1.go = "PortmansCap_4";
				}
				else
				{
					dialog.text = StringFromKey("ForAll_dialog_348");
					link.l1 = StringFromKey("ForAll_dialog_349", pchar);
					link.l1.go = "PortmansCap_5";
				}
			}
		break;
		case "PortmansCap_4":
			dialog.text = StringFromKey("ForAll_dialog_350", pchar);
			link.l1 = StringFromKey("ForAll_dialog_351");
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Pre"));
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12 + drand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
			AddCharacterExpToSkill(pchar, "Repair", makeint(400 / sti(npchar.quest.stepsQty)));
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			ChangeCharacterReputation(pchar, 2);
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
			RemoveLandQuestMark_Gen(npchar, "PortmansBook_Delivery");
		break;
		case "PortmansCap_5":
			dialog.text = StringFromKey("ForAll_dialog_352", pchar);
			link.l1 = StringFromKey("ForAll_dialog_353");
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Pre"));
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
			AddCharacterExpToSkill(pchar, "Repair", makeint(200 / sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
			RemoveLandQuestMark_Gen(npchar, "PortmansBook_Delivery");
		break;
		//догнал в море
		case "PortmansCap_inDeck":
			if (isBadReputation(pchar, 20))
			{
				dialog.text = StringFromKey("ForAll_dialog_354");
				link.l1 = StringFromKey("ForAll_dialog_355", pchar);
			}
			else
			{
				dialog.text = StringFromKey("ForAll_dialog_356");
				link.l1 = StringFromKey("ForAll_dialog_357", pchar);
			}
			link.l1.go = "PortmansCap_inDeck_1";
		break;
		case "PortmansCap_inDeck_1":
			dialog.text = StringFromKey("ForAll_dialog_358");
			link.l1 = StringFromKey("ForAll_dialog_359", pchar, XI_ConvertString("Colony" + npchar.quest.firstCity + "Gen"));
			link.l1.go = "PortmansCap_inDeck_2";
		break;
		case "PortmansCap_inDeck_2":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = StringFromKey("ForAll_dialog_360");
				link.l1 = StringFromKey("ForAll_dialog_361");
				link.l1.go = "PortmansCap_inDeck_3";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = StringFromKey("ForAll_dialog_362", pchar);
					link.l1 = StringFromKey("ForAll_dialog_363");
					link.l1.go = "PortmansCap_inDeck_3";
				}
				else
				{
					dialog.text = StringFromKey("ForAll_dialog_364", pchar);
					link.l1 = StringFromKey("ForAll_dialog_365");
					link.l1.go = "PortmansCap_inDeck_5";
				}
			}
		break;
		case "PortmansCap_inDeck_3":
			dialog.text = StringFromKey("ForAll_dialog_366", FindMoneyString(sti(npchar.quest.money)));
			link.l1 = StringFromKey("ForAll_dialog_367");
			link.l1.go = "PortmansCap_inDeck_4";
		break;
		case "PortmansCap_inDeck_4":
			dialog.text = StringFromKey("ForAll_dialog_368", pchar);
			link.l1 = StringFromKey("ForAll_dialog_369");
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12 + drand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
			AddCharacterExpToSkill(pchar, "Sailing", makeint(400 / sti(npchar.quest.stepsQty)));
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			ChangeCharacterReputation(pchar, 5);
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
			RemoveLandQuestMark_Gen(npchar, "PortmansBook_Delivery");
		break;
		case "PortmansCap_inDeck_5":
			dialog.text = StringFromKey("ForAll_dialog_370", pchar);
			link.l1 = StringFromKey("ForAll_dialog_371", pchar);
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
			AddCharacterExpToSkill(pchar, "Sailing", makeint(200 / sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
			RemoveLandQuestMark_Gen(npchar, "PortmansBook_Delivery");
		break;
		case "PortmansCap_inDeck_over":
			dialog.text = StringFromKey("ForAll_dialog_372");
			link.l1 = StringFromKey("ForAll_dialog_373");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//--------------------------- розыск украденного корабля --------------------------------
		case "SeekCap_inDeck":
			dialog.text = StringFromKey("ForAll_dialog_374");
			link.l1 = StringFromKey("ForAll_dialog_375", pchar);
			link.l1.go = "SeekCap_inDeck_1";
		break;
		case "SeekCap_inDeck_1":
			dialog.text = StringFromKey("ForAll_dialog_376");
			link.l1 = StringFromKey("ForAll_dialog_377");
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
			sld = characterFromId(npchar.quest.cribCity + "_PortMan");
			sTitle = sld.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "4");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName)));
		break;
		case "SeekCap_inDeck_over":
			dialog.text = StringFromKey("ForAll_dialog_378");
			link.l1 = StringFromKey("ForAll_dialog_379");
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
		break;
		//абордаж
		case "SeekCap":
			dialog.text = StringFromKey("ForAll_dialog_380", pchar);
			link.l1 = StringFromKey("ForAll_dialog_381", pchar);
			link.l1.go = "SeekCap_1";
		break;
		case "SeekCap_1":
			dialog.text = StringFromKey("ForAll_dialog_382");
			link.l1 = StringFromKey("ForAll_dialog_383", pchar);
			link.l1.go = "SeekCap_2";
		break;
		case "SeekCap_2":
			dialog.text = StringFromKey("ForAll_dialog_384");
			link.l1 = StringFromKey("ForAll_dialog_385");
			link.l1.go = "SeekCap_3";
		break;
		case "SeekCap_3":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//--------------------------- ночное бдение в церкви --------------------------------
		case "ChurchBerglar":
			dialog.text = StringFromKey("ForAll_dialog_386");
			link.l1 = StringFromKey("ForAll_dialog_387");
			link.l1.go = "ChurchBerglar_1";
		break;
		case "ChurchBerglar_1":
			dialog.text = StringFromKey("ForAll_dialog_388");
			link.l1 = StringFromKey("ForAll_dialog_389");
			link.l1.go = "ChurchBerglar_2";
		break;
		case "ChurchBerglar_2":
			dialog.text = StringFromKey("ForAll_dialog_390", pchar);
			link.l1 = StringFromKey("ForAll_dialog_391");
			link.l1.go = "ChurchBerglar_fight";
		break;
		case "ChurchBerglar_fight":
			LAi_LocationFightDisable(&locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "CannotFightCurLocation");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//-------------------------------------------поисковый генератор горожан--------------------------------------
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//========= квесты дворян ===========
		case "SCQ_Nobleman":
			dialog.text = StringFromKey("ForAll_dialog_392", GetAddress_Form(NPChar), GetFullName(npchar));
			link.l1 = StringFromKey("ForAll_dialog_395", RandPhraseSimple(
						StringFromKey("ForAll_dialog_393"),
						StringFromKey("ForAll_dialog_394")));
			link.l1.go = "SCQ_exit";
			link.l2 = StringFromKey("ForAll_dialog_396");
			link.l2.go = "SCQ_Nobleman_1";
		break;

		case "SCQ_Nobleman_1":
			switch (sti(npchar.quest.SeekCap.numQuest))
			{
				case 0: //вариант А
					if (sti(pchar.reputation) < 35)
					{
						PlayerRPGCheck_Reputation_NotifyPass(false, false);
						dialog.text = StringFromKey("ForAll_dialog_397", SelectNB_battleText());
						link.l1 = StringFromKey("ForAll_dialog_401", LinkRandPhrase(
									StringFromKey("ForAll_dialog_398"),
									StringFromKey("ForAll_dialog_399"),
									StringFromKey("ForAll_dialog_400")));
						link.l1.go = "SCQ_NM_battle";
					}
					else //вариант В
					{
						PlayerRPGCheck_Reputation_NotifyPass(false, true);
						SelectNB_prisonerText(npchar);
						dialog.text = StringFromKey("ForAll_dialog_402", npchar.quest.text);
						link.l1 = StringFromKey("ForAll_dialog_406", LinkRandPhrase(
									StringFromKey("ForAll_dialog_403"),
									StringFromKey("ForAll_dialog_404"),
									StringFromKey("ForAll_dialog_405")));
						link.l1.go = "SCQ_NM_prisoner";
					}
				break;

				case 1: //вариант С
					SelectNB_peaceText(npchar);
					dialog.text = StringFromKey("ForAll_dialog_407", npchar.quest.text);
					link.l1 = StringFromKey("ForAll_dialog_408", pchar);
					link.l1.go = "SCQ_NM_peace";
				break;
			}
		break;

		case "SCQ_NM_battle": //вариант А
			dialog.text = StringFromKey("ForAll_dialog_409");
			link.l1 = StringFromKey("ForAll_dialog_410");
			link.l1.go = "SCQ_NM_battle_1";
		break;

		case "SCQ_NM_battle_1":
			npchar.quest.SeekCap = "NM_battle"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, rand(HOLLAND)); //любая нация кроме пиратов
			dialog.text = StringFromKey("ForAll_dialog_411", npchar.quest.SeekCap.capName, GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Pre")), npchar.quest.SeekCap.shipName, XI_ConvertString("Colony" + npchar.quest.Qcity), FindMoneyString(sti(npchar.quest.money)));
			link.l1 = StringFromKey("ForAll_dialog_412");
			link.l1.go = "SCQ_NM_battle_2";
			link.l2 = StringFromKey("ForAll_dialog_413", pchar);
			link.l2.go = "SCQ_exit_clear";
		break;

		case "SCQ_NM_battle_2":
			dialog.text = StringFromKey("ForAll_dialog_414");
			link.l1 = StringFromKey("ForAll_dialog_415", pchar);
			link.l1.go = "SCQ_NM_battle_3";
		break;

		case "SCQ_NM_battle_3":
			dialog.text = StringFromKey("ForAll_dialog_416");
			link.l1 = StringFromKey("ForAll_dialog_417");
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 8.0, 10.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";

			npchar.location = npchar.city + "_church"; //TODO: мб посадим его? как в Nobleman.c
			npchar.location.locator = "goto2";

			pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_battle";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_battle", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony" + npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Pre")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;

		case "SCQ_NM_prisoner": //вариант В
			dialog.text = StringFromKey("ForAll_dialog_418");
			link.l1 = StringFromKey("ForAll_dialog_419");
			link.l1.go = "SCQ_NM_prisoner_1";
		break;

		case "SCQ_NM_prisoner_1":
			npchar.quest.SeekCap = "NM_prisoner"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, rand(HOLLAND)); //любая нация кроме пиратов
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = sti(npchar.nation);
			forName.sex = "man";
			forName.name = GenerateRandomName(sti(npchar.nation), "man");
			dialog.text = StringFromKey("ForAll_dialog_420", npchar.quest.SeekCap.name, GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Pre")), npchar.quest.SeekCap.shipName, npchar.quest.SeekCap.capName, XI_ConvertString("Colony" + npchar.quest.Qcity), FindMoneyString(sti(npchar.quest.money)));
			link.l1 = StringFromKey("ForAll_dialog_421");
			link.l1.go = "SCQ_NM_prisoner_2";
			link.l2 = StringFromKey("ForAll_dialog_422", pchar);
			link.l2.go = "SCQ_exit_clear";
		break;

		case "SCQ_NM_prisoner_2":
			dialog.text = StringFromKey("ForAll_dialog_423");
			link.l1 = StringFromKey("ForAll_dialog_424", pchar);
			link.l1.go = "SCQ_NM_prisoner_3";
		break;

		case "SCQ_NM_prisoner_3":
			dialog.text = StringFromKey("ForAll_dialog_425");
			link.l1 = StringFromKey("ForAll_dialog_426");
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 8.0, 10.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";

			npchar.location = npchar.city + "_church"; //TODO: мб посадим его? как в Nobleman.c
			npchar.location.locator = "goto2";

			pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_prisoner";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_prisoner", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony" + npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Pre")));
			AddQuestUserData(sTitle, "sName1", npchar.quest.SeekCap.name);
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;

		case "SCQ_NM_peace": //вариант С
			dialog.text = StringFromKey("ForAll_dialog_427");
			link.l1 = StringFromKey("ForAll_dialog_428");
			link.l1.go = "SCQ_NM_peace_1";
		break;

		case "SCQ_NM_peace_1":
			npchar.quest.SeekCap = "NM_peace"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation)); //нация = нации квестодателя
			dialog.text = StringFromKey("ForAll_dialog_429", npchar.quest.SeekCap.capName, GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Pre")), npchar.quest.SeekCap.shipName, XI_ConvertString("Colony" + npchar.quest.Qcity), FindMoneyString(sti(npchar.quest.money)));
			link.l1 = StringFromKey("ForAll_dialog_430");
			link.l1.go = "SCQ_NM_peace_2";
			link.l2 = StringFromKey("ForAll_dialog_431", pchar);
			link.l2.go = "SCQ_exit_clear";
		break;

		case "SCQ_NM_peace_2":
			dialog.text = StringFromKey("ForAll_dialog_432");
			link.l1 = StringFromKey("ForAll_dialog_433", pchar);
			link.l1.go = "SCQ_NM_peace_3";
		break;

		case "SCQ_NM_peace_3":
			dialog.text = StringFromKey("ForAll_dialog_434");
			link.l1 = StringFromKey("ForAll_dialog_435");
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 18.0, 20.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";

			npchar.location = npchar.city + "_church"; //TODO: мб посадим его? как в Nobleman.c
			npchar.location.locator = "goto2";

			pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_peace";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_peace", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony" + npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Pre")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;

		//--> разговор на суше, вариант А
		case "NM_battleCap":
			dialog.text = StringFromKey("ForAll_dialog_436", pchar);
			link.l1 = StringFromKey("ForAll_dialog_437", GetFullName(npchar));
			link.l1.go = "NM_battleCap_1";
		break;

		case "NM_battleCap_1":
			dialog.text = StringFromKey("ForAll_dialog_438");
			link.l1 = StringFromKey("ForAll_dialog_439", GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]));
			link.l1.go = "NM_battleCap_2";
			link.l2 = StringFromKey("ForAll_dialog_440", pchar);
			link.l2.go = "NM_battleCap_4";
		break;

		case "NM_battleCap_2":
			dialog.text = StringFromKey("ForAll_dialog_441", pchar);
			link.l1 = StringFromKey("ForAll_dialog_442");
			link.l1.go = "NM_battleCap_exit";
			link.l2 = StringFromKey("ForAll_dialog_443");
			link.l2.go = "NM_battleCap_3";
		break;

		case "NM_battleCap_3":
			dialog.text = StringFromKey("ForAll_dialog_444");
			link.l1 = StringFromKey("ForAll_dialog_445");
			link.l1.go = "NM_battleCap_fight";
		break;

		case "NM_battleCap_4":
			dialog.text = StringFromKey("ForAll_dialog_446");
			link.l1 = StringFromKey("ForAll_dialog_447");
			link.l1.go = "NM_battleCap_exit";
		break;

		case "NM_battleCap_exit":
			DialogExit();
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			RemoveLandQuestMark_Gen(npchar, "SeekCitizCap");
		break;

		case "NM_battleCap_fight":
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			RemoveLandQuestMark_Gen(npchar, "SeekCitizCap");
		break;

		//--> разговор на суше и палубе одинаковый, вариант В
		case "NM_prisonerCap":
			dialog.text = StringFromKey("ForAll_dialog_448", pchar);
			link.l1 = StringFromKey("ForAll_dialog_449", GetFullName(npchar));
			link.l1.go = "NM_prisonerCap_1";
		break;

		case "NM_prisonerCap_1":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			dialog.text = StringFromKey("ForAll_dialog_450");
			link.l1 = StringFromKey("ForAll_dialog_451", sld.quest.SeekCap.name);
			link.l1.go = "NM_prisonerCap_2";
		break;

		case "NM_prisonerCap_2":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			dialog.text = StringFromKey("ForAll_dialog_452");
			link.l1 = StringFromKey("ForAll_dialog_453", pchar, XI_ConvertString("Colony" + sld.city + "Gen"), sld.quest.text1, XI_ConvertString("Colony" + sld.city));
			link.l1.go = "NM_prisonerCap_3";
		break;

		case "NM_prisonerCap_3":
			if (sti(npchar.reputation) > 41)
			{
				dialog.text = StringFromKey("ForAll_dialog_454");
				link.l1 = StringFromKey("ForAll_dialog_455", GetAddress_FormToNPC(NPChar));
				link.l1.go = "NM_prisonerCap_good";
			}
			else
			{
				dialog.text = StringFromKey("ForAll_dialog_456", pchar);
				link.l1 = StringFromKey("ForAll_dialog_457");
				link.l1.go = "NM_prisonerCap_bad";
			}
		break;

		case "NM_prisonerCap_good":
			dialog.text = StringFromKey("ForAll_dialog_458");
			link.l1 = StringFromKey("ForAll_dialog_459");
			link.l1.go = "NM_prisonerCap_good_1";
		break;

		case "NM_prisonerCap_good_1":
			DialogExit();
			NextDiag.CurrentNode = "NM_prisonerDeck_exit";
			npchar.DeckDialogNode = "NM_prisonerDeck_exit";
			npchar.quest.release = "true";
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
			ref chr = GetCharacter(NPC_GenerateCharacter(npchar.quest.SeekCap + "_" + npchar.quest.cribCity, "citiz_" + (rand(9) + 21), "man", "man", 5, sti(npchar.nation), -1, false));
			chr.name = sld.quest.SeekCap.name;
			chr.lastname = "";
			//pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(chr);
			//SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			AddPassenger(pchar, chr, false);//добавить пассажира
			SetCharacterRemovable(chr, false);
			log_info(StringFromKey("InfoMessages_161", sld.quest.SeekCap.name));
			PlaySound("interface\notebook.wav");
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).win_condition.l1 = "MapEnter";
			pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
			//DoQuestFunctionDelay("SCQ_seekCapIsDeath", 0.5); // 170712
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			RemoveLandQuestMark_Gen(npchar, "SeekCitizCap");
		break;

		case "NM_prisonerCap_bad":
			DialogExit();
			NextDiag.CurrentNode = "NM_prisonerDeck_exit";
			npchar.DeckDialogNode = "NM_prisonerDeck_exit";
			npchar.quest.mustboarding = "true";
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			sTitle = sld.City + "SCQ_" + sld.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + sld.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			RemoveLandQuestMark_Gen(npchar, "SeekCitizCap");
		break;

		case "NM_prisonerDeck_exit":
			dialog.text = StringFromKey("ForAll_dialog_460");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_prisonerDeck_exit";
		break;

		//--> разговор на суше и палубе одинаковый, вариант C
		case "NM_peaceCap":
			dialog.text = StringFromKey("ForAll_dialog_461", pchar);
			link.l1 = StringFromKey("ForAll_dialog_462", GetFullName(npchar));
			link.l1.go = "NM_peaceCap_1";
		break;

		case "NM_peaceCap_1":
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);//квестодатель
			dialog.text = StringFromKey("ForAll_dialog_463");
			link.l1 = StringFromKey("ForAll_dialog_464", GetFullName(sld), sld.quest.text1, XI_ConvertString("Colony" + npchar.quest.cribCity + "Pre"));
			link.l1.go = "NM_peaceCap_2";
		break;

		case "NM_peaceCap_2":
			dialog.text = StringFromKey("ForAll_dialog_465", pchar, XI_ConvertString("Colony" + npchar.quest.cribCity));
			link.l1 = StringFromKey("ForAll_dialog_466", GetAddress_FormToNPC(NPChar));
			link.l1.go = "NM_peaceCap_3";
		break;

		case "NM_peaceCap_3":
			DialogExit();
			NextDiag.CurrentNode = "NM_peaceCap_exit";
			npchar.DeckDialogNode = "NM_peaceCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Acc")); //TODO: чек ккс падеж
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);//квестодатель
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
			RemoveLandQuestMark_Gen(npchar, "SeekCitizCap");
		break;

		case "NM_peaceCap_exit":
			dialog.text = StringFromKey("ForAll_dialog_467", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("ForAll_dialog_468");
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_peaceCap_exit";
		break;

		//--> встреча на палубе, вариант А
		case "NM_battleDeck":
			dialog.text = StringFromKey("ForAll_dialog_469", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("ForAll_dialog_470", pchar);
			link.l1.go = "NM_battleDeck_1";
		break;

		case "NM_battleDeck_1":
			dialog.text = StringFromKey("ForAll_dialog_471");
			link.l1 = StringFromKey("ForAll_dialog_472", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName)));
			RemoveLandQuestMark_Gen(npchar, "SeekCitizCap");
		break;

		case "NM_battleDeck_exit":
			dialog.text = StringFromKey("ForAll_dialog_473", pchar);
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
		break;

		//--> абордаж, вариант А
		case "NM_battleBoard":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
			dialog.text = StringFromKey("ForAll_dialog_474", pchar);
			link.l1 = StringFromKey("ForAll_dialog_475", pchar, XI_ConvertString("Colony" + npchar.quest.cribCity), GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]));
			link.l1.go = "NM_battleBoard_1";
		break;

		case "NM_battleBoard_1":
			dialog.text = StringFromKey("ForAll_dialog_476");
			link.l1 = StringFromKey("ForAll_dialog_477");
			link.l1.go = "NM_battleBoard_2";
		break;

		case "NM_battleBoard_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//--> абордаж, вариант В
		case "NM_prisonerBoard":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			dialog.text = StringFromKey("ForAll_dialog_478", pchar);
			if (CheckAttribute(npchar, "quest.mustboarding"))
			{
				link.l1 = StringFromKey("ForAll_dialog_479", pchar);
				link.l1.go = "NM_prisonerBoard_1";
			}
			else
			{
				link.l1 = StringFromKey("ForAll_dialog_480", sld.quest.SeekCap.name, XI_ConvertString("Colony" + npchar.quest.cribCity));
				link.l1.go = "NM_prisonerBoard_1";
			}
		break;

		case "NM_prisonerBoard_1":
			dialog.text = StringFromKey("ForAll_dialog_481", pchar);
			link.l1 = StringFromKey("ForAll_dialog_482");
			link.l1.go = "NM_prisonerBoard_2";
		break;

		case "NM_prisonerBoard_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			pchar.GenQuest.mustboarding = "true";//ставим этот флаг для завершения квеста
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;    //нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.model = "citiz_" + (rand(9) + 21); //модель для нпс
			pchar.GenQuest.CitizSeekCap.PrisonerCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.PrisonerName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.PrisonerLastname = "";
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
		break;

		//--> результаты квестов дворян
		case "SCQ_NM_result":
			dialog.text = StringFromKey("ForAll_dialog_483");
			link.l1 = StringFromKey("ForAll_dialog_484");
			link.l1.go = "exit";
			switch (npchar.quest.SeekCap)
			{
				case "NM_battleover"://сдача квеста, вариант А
					dialog.text = StringFromKey("ForAll_dialog_485");
					link.l1 = StringFromKey("ForAll_dialog_486", npchar.quest.SeekCap.capName, GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName)));
					link.l1.go = "SCQ_NM_result_A1";
				break;

				case "NM_prisonerover"://сдача квеста, вариант B
					dialog.text = StringFromKey("ForAll_dialog_487");
					link.l1 = StringFromKey("ForAll_dialog_488", npchar.quest.SeekCap.Name);
					link.l1.go = "SCQ_NM_result_B1";
				break;

				case "NM_peaceover"://сдача квеста, вариант C
					dialog.text = StringFromKey("ForAll_dialog_489");
					link.l1 = StringFromKey("ForAll_dialog_490");
					link.l1.go = "SCQ_NM_result_C1";
				break;
			}
		break;

		case "SCQ_NM_result_A1":
			dialog.text = StringFromKey("ForAll_dialog_491");
			link.l1 = StringFromKey("ForAll_dialog_492");
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			GiveGoldOnAmount(sti(npchar.quest.money));
			sTitle = npchar.city + "SCQ_NM_battle";
			CloseQuestHeader(sTitle);
			ChangeCharacterReputation(pchar, -2);
			AddCrewMorale(Pchar, -2);
			OfficersReaction("bad");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSeaExpToScill(100, 50, 50, 50, 50, 50, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//лидерство
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;

		case "SCQ_NM_result_B1":
			dialog.text = StringFromKey("ForAll_dialog_493");
			link.l1 = StringFromKey("ForAll_dialog_494");
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			GiveGoldOnAmount(sti(npchar.quest.money));
			sTitle = npchar.city + "SCQ_NM_prisoner";
			CloseQuestHeader(sTitle);
			sld = characterFromId("NM_prisoner_" + npchar.City);
			RemovePassenger(pchar, sld); // 170712
			//ReleasePrisoner(sld);
			sld.lifeday = 0;
			AddCrewMorale(Pchar, 3);
			//OfficersReaction("good");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 150);//лидерство
		break;

		case "SCQ_NM_result_C1":
			dialog.text = StringFromKey("ForAll_dialog_495");
			link.l1 = StringFromKey("ForAll_dialog_496");
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			sld = characterFromId(npchar.quest.SeekCap.capId);
			sld.lifeday = 0;
			Map_ReleaseQuestEncounter(sld.id);
			sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SecondTimer_" + sld.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем возможный таймер на выход в море
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			GiveGoldOnAmount(sti(npchar.quest.money));
			sTitle = npchar.city + "SCQ_NM_peace";
			CloseQuestHeader(sTitle);
			ChangeCharacterReputation(pchar, 2);
			OfficersReaction("good");
			AddCrewMorale(Pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 200);//лидерство
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;

		//========= квесты мужиков ===========
		case "SCQ_man":
			dialog.text = StringFromKey("ForAll_dialog_500", LinkRandPhrase(
						StringFromKey("ForAll_dialog_497"),
						StringFromKey("ForAll_dialog_498"),
						StringFromKey("ForAll_dialog_499")));
			link.l1 = StringFromKey("ForAll_dialog_503", RandPhraseSimple(
						StringFromKey("ForAll_dialog_501", pchar),
						StringFromKey("ForAll_dialog_502")));
			link.l1.go = "SCQ_exit";
			link.l2 = StringFromKey("ForAll_dialog_506", RandPhraseSimple(
						StringFromKey("ForAll_dialog_504"),
						StringFromKey("ForAll_dialog_505")));
			link.l2.go = "SCQ_man_1";
		break;
		case "SCQ_exit":
		//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (CheckAttribute(sld, "questSeekCap") && sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap) - 1;
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		case "SCQ_exit_clear":
		//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (CheckAttribute(sld, "questSeekCap") && sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap) - 1;
			sld = characterFromId(npchar.quest.SeekCap.capId); //капитан	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		//выбираем квест
		case "SCQ_man_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = StringFromKey("ForAll_dialog_507", XI_ConvertString("Colony" + SelectNotEnemyColony(NPChar) + "Acc"));
					link.l1 = StringFromKey("ForAll_dialog_508");
					link.l1.go = "SCQ_Slave";
				break;
				case "1":
					dialog.text = StringFromKey("ForAll_dialog_509");
					link.l1 = StringFromKey("ForAll_dialog_510");
					link.l1.go = "SCQ_RapeWife";
				break;
				case "2":
					dialog.text = StringFromKey("ForAll_dialog_511");
					link.l1 = StringFromKey("ForAll_dialog_512");
					link.l1.go = "SCQ_Friend";
				break;
			}
		break;
		// квест бывшего раба, которого негодяй-кэп взял в плен
		case "SCQ_Slave":
			dialog.text = StringFromKey("ForAll_dialog_513");
			link.l1 = StringFromKey("ForAll_dialog_514");
			link.l1.go = "SCQ_Slave_1";
			link.l2 = StringFromKey("ForAll_dialog_515");
			link.l2.go = "SCQ_exit";
		break;
		case "SCQ_Slave_1":
			npchar.quest.SeekCap = "manSlave"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = StringFromKey("ForAll_dialog_516", npchar.quest.SeekCap.capName, GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Pre")), npchar.quest.SeekCap.shipName, XI_ConvertString("Colony" + npchar.quest.Qcity), FindMoneyString(sti(npchar.quest.money)));
			link.l1 = StringFromKey("ForAll_dialog_517", pchar);
			link.l1.go = "SCQ_Slave_2";
			link.l2 = StringFromKey("ForAll_dialog_518");
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Slave_2":
			dialog.text = StringFromKey("ForAll_dialog_519");
			link.l1 = StringFromKey("ForAll_dialog_520");
			link.l1.go = "SCQ_Slave_3";
		break;
		case "SCQ_Slave_3":
			dialog.text = StringFromKey("ForAll_dialog_521");
			link.l1 = StringFromKey("ForAll_dialog_522");
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			DeleteAttribute(&npchar, "talker"); //что бы не уточнял в тот же день как у нас дела
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";
			pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manSlave";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manSlave", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony" + npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Pre")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
			// evganat - генераторы
			sNPCidx = npchar.index;
			pchar.questTemp.SeekCap.(sNPCidx) = "slave";
		break;
		//пират похитил жену у ситизена
		case "SCQ_RapeWife":
			dialog.text = StringFromKey("ForAll_dialog_523");
			link.l1 = StringFromKey("ForAll_dialog_524");
			link.l1.go = "SCQ_RapeWife_1";
		break;
		case "SCQ_RapeWife_1":
			npchar.quest.SeekCap = "manRapeWife"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "woman";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у мужа есно
			dialog.text = StringFromKey("ForAll_dialog_525", FindMoneyString(sti(npchar.quest.money)));
			link.l1 = StringFromKey("ForAll_dialog_526", pchar);
			link.l1.go = "SCQ_RapeWife_2";
			link.l2 = StringFromKey("ForAll_dialog_527");
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_RapeWife_2":
			dialog.text = StringFromKey("ForAll_dialog_528", npchar.quest.SeekCap.name, npchar.quest.SeekCap.capName, GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Pre")), npchar.quest.SeekCap.shipName, XI_ConvertString("Colony" + npchar.quest.Qcity));
			link.l1 = StringFromKey("ForAll_dialog_529");
			link.l1.go = "SCQ_RapeWife_3";
		break;
		case "SCQ_RapeWife_3":
			dialog.text = StringFromKey("ForAll_dialog_530");
			link.l1 = StringFromKey("ForAll_dialog_531");
			link.l1.go = "SCQ_RapeWife_4";
		break;
		case "SCQ_RapeWife_4":
			dialog.text = StringFromKey("ForAll_dialog_532");
			link.l1 = StringFromKey("ForAll_dialog_533");
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			DeleteAttribute(&npchar, "talker"); //что бы не уточнял в тот же день как у нас дела
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";
			pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manRapeWife";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manRapeWife", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony" + npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Pre")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся", "ась"));
			// evganat - генераторы
			sNPCidx = npchar.index;
			pchar.questTemp.SeekCap.(sNPCidx) = "rapewife";
		break;
		//поиски земляка
		case "SCQ_Friend":
			dialog.text = StringFromKey("ForAll_dialog_534");
			link.l1 = StringFromKey("ForAll_dialog_535");
			link.l1.go = "SCQ_Friend_1";
		break;
		case "SCQ_Friend_1":
			npchar.quest.SeekCap = "manFriend"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = StringFromKey("ForAll_dialog_536", FindMoneyString(sti(npchar.quest.money)));
			link.l1 = StringFromKey("ForAll_dialog_537", pchar);
			link.l1.go = "SCQ_Friend_2";
			link.l2 = StringFromKey("ForAll_dialog_538");
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Friend_2":
			dialog.text = StringFromKey("ForAll_dialog_539");
			link.l1 = StringFromKey("ForAll_dialog_540");
			link.l1.go = "SCQ_Friend_3";
		break;
		case "SCQ_Friend_3":
			dialog.text = StringFromKey("ForAll_dialog_541", npchar.quest.SeekCap.capName, GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")), npchar.quest.SeekCap.shipName, XI_ConvertString("Colony" + npchar.quest.Qcity));
			link.l1 = StringFromKey("ForAll_dialog_542");
			link.l1.go = "SCQ_Friend_4";
		break;
		case "SCQ_Friend_4":
			dialog.text = StringFromKey("ForAll_dialog_543");
			link.l1 = StringFromKey("ForAll_dialog_544");
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			DeleteAttribute(&npchar, "talker"); //что бы не уточнял в тот же день как у нас дела
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";
			pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manFriend";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manFriend", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony" + npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Pre")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			// evganat - генераторы
			sNPCidx = npchar.index;
			pchar.questTemp.SeekCap.(sNPCidx) = "friend";
		break;

		// --- результаты мужских квестов ---
		case "SCQ_manResult":
			dialog.text = StringFromKey("ForAll_dialog_545");
			link.l1 = StringFromKey("ForAll_dialog_546");
			link.l1.go = "SCQ_manResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "manSlaveover":
					dialog.text = StringFromKey("ForAll_dialog_547");
					link.l1 = StringFromKey("ForAll_dialog_548", npchar.quest.SeekCap.capName, GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName)));
					link.l1.go = "SCQR_manSlave";
				break;
				case "manRapeWifeover":
					dialog.text = StringFromKey("ForAll_dialog_549");
					link.l1 = StringFromKey("ForAll_dialog_550", npchar.quest.SeekCap.name, npchar.quest.SeekCap.lastname);
					link.l1.go = "SCQR_manRapeWife";
				break;
				case "manFriendover":
					dialog.text = StringFromKey("ForAll_dialog_551");
					link.l1 = StringFromKey("ForAll_dialog_552", pchar);
					link.l1.go = "SCQR_manFriend";
				break;
			}
		break;
		case "SCQ_manResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = StringFromKey("ForAll_dialog_553", npchar.quest.SeekCap.capName);
					link.l1 = StringFromKey("ForAll_dialog_554", pchar);
					link.l1.go = "exit";
				break;
				case "manRapeWife":
					dialog.text = StringFromKey("ForAll_dialog_555", npchar.quest.SeekCap.capName);
					link.l1 = StringFromKey("ForAll_dialog_556", pchar);
					link.l1.go = "exit";
				break;
				case "manFriend":
					dialog.text = StringFromKey("ForAll_dialog_557", npchar.quest.SeekCap.capName);
					link.l1 = StringFromKey("ForAll_dialog_558", pchar);
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_manSlave":
			dialog.text = StringFromKey("ForAll_dialog_559", FindMoneyString(sti(npchar.quest.money)));
			link.l1 = StringFromKey("ForAll_dialog_560");
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10 + drand(8));
			sTitle = npchar.city + "SCQ_manSlave";
			CloseQuestHeader(sTitle);
			// evganat - генераторы
			sNPCidx = npchar.index;
			DeleteAttribute(pchar, "questTemp.SeekCap." + sNPCidx);
		break;
		case "SCQR_manRapeWife":
			dialog.text = StringFromKey("ForAll_dialog_561", FindMoneyString(sti(npchar.quest.money)));
			link.l1 = StringFromKey("ForAll_dialog_562");
			link.l1.go = "SCQ_exit";
			sld = characterFromId("manRapeWife_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12 + drand(8));
			sTitle = npchar.city + "SCQ_manRapeWife";
			CloseQuestHeader(sTitle);
			// evganat - генераторы
			sNPCidx = npchar.index;
			DeleteAttribute(pchar, "questTemp.SeekCap." + sNPCidx);
		break;
		case "SCQR_manFriend":
			dialog.text = StringFromKey("ForAll_dialog_563", FindMoneyString(sti(npchar.quest.money)));
			link.l1 = StringFromKey("ForAll_dialog_564");
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8 + drand(8));
			sTitle = npchar.city + "SCQ_manFriend";
			CloseQuestHeader(sTitle);
			// evganat - генераторы
			sNPCidx = npchar.index;
			DeleteAttribute(pchar, "questTemp.SeekCap." + sNPCidx);
		break;
		//========= квесты баб ===========
		case "SCQ_woman":
			dialog.text = StringFromKey("ForAll_dialog_568", LinkRandPhrase(
						StringFromKey("ForAll_dialog_565"),
						StringFromKey("ForAll_dialog_566"),
						StringFromKey("ForAll_dialog_567", pchar)));
			link.l1 = StringFromKey("ForAll_dialog_571", RandPhraseSimple(
						StringFromKey("ForAll_dialog_569", pchar),
						StringFromKey("ForAll_dialog_570", GetAddress_FormToNPC(NPChar))));
			link.l1.go = "SCQ_exit";
			link.l2 = StringFromKey("ForAll_dialog_574", RandPhraseSimple(
						StringFromKey("ForAll_dialog_572", GetAddress_FormToNPC(NPChar)),
						StringFromKey("ForAll_dialog_573", GetAddress_FormToNPC(NPChar))));
			link.l2.go = "SCQ_woman_1";
		break;
		//выбираем квест
		case "SCQ_woman_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = StringFromKey("ForAll_dialog_575");
					link.l1 = StringFromKey("ForAll_dialog_576");
					link.l1.go = "SCQ_Hasband";
				break;
				case "1":
					dialog.text = StringFromKey("ForAll_dialog_577", pchar);
					link.l1 = StringFromKey("ForAll_dialog_578", GetAddress_FormToNPC(NPChar));
					link.l1.go = "SCQ_Revenge";
				break;
				case "2":
					dialog.text = StringFromKey("ForAll_dialog_579");
					link.l1 = StringFromKey("ForAll_dialog_580");
					link.l1.go = "SCQ_Pirates";
				break;
			}
		break;

		//жещина разыскивает мужа-торговца
		case "SCQ_Hasband":
			dialog.text = StringFromKey("ForAll_dialog_581");
			link.l1 = StringFromKey("ForAll_dialog_582");
			link.l1.go = "SCQ_Hasband_1";
		break;
		case "SCQ_Hasband_1":
			npchar.quest.SeekCap = "womanHasband"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = StringFromKey("ForAll_dialog_583", pchar, FindMoneyString(sti(npchar.quest.money)));
			link.l1 = StringFromKey("ForAll_dialog_584");
			link.l1.go = "SCQ_Hasband_2";
			link.l2 = StringFromKey("ForAll_dialog_585", pchar);
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Hasband_2":
			dialog.text = StringFromKey("ForAll_dialog_586", npchar.quest.SeekCap.capName, GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Pre")), npchar.quest.SeekCap.shipName, XI_ConvertString("Colony" + npchar.quest.Qcity));
			link.l1 = StringFromKey("ForAll_dialog_587", pchar);
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";
			pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanHasband";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanHasband", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony" + npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Pre")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			// evganat - генераторы
			sNPCidx = npchar.index;
			pchar.questTemp.SeekCap.(sNPCidx) = "husband";
		break;
		//месть отвергнутой женщины
		case "SCQ_Revenge":
			dialog.text = StringFromKey("ForAll_dialog_588", pchar);
			link.l1 = StringFromKey("ForAll_dialog_589");
			link.l1.go = "SCQ_Revenge_1";
		break;
		case "SCQ_Revenge_1":
			dialog.text = StringFromKey("ForAll_dialog_590");
			link.l1 = StringFromKey("ForAll_dialog_591");
			link.l1.go = "SCQ_Revenge_2";
		break;
		case "SCQ_Revenge_2":
			dialog.text = StringFromKey("ForAll_dialog_592");
			link.l1 = StringFromKey("ForAll_dialog_593");
			link.l1.go = "SCQ_Revenge_3";
		break;
		case "SCQ_Revenge_3":
			dialog.text = StringFromKey("ForAll_dialog_594");
			link.l1 = StringFromKey("ForAll_dialog_595", pchar);
			link.l1.go = "SCQ_Revenge_4";
		break;
		case "SCQ_Revenge_4":
			dialog.text = StringFromKey("ForAll_dialog_596", pchar);
			link.l1 = StringFromKey("ForAll_dialog_597", pchar);
			link.l1.go = "SCQ_Revenge_5";
		break;
		case "SCQ_Revenge_5":
			dialog.text = StringFromKey("ForAll_dialog_598", pchar);
			link.l1 = StringFromKey("ForAll_dialog_599", pchar);
			link.l1.go = "SCQ_Revenge_6";
		break;
		case "SCQ_Revenge_6":
			dialog.text = StringFromKey("ForAll_dialog_600", pchar);
			link.l1 = StringFromKey("ForAll_dialog_601");
			link.l1.go = "SCQ_Revenge_7";
		break;
		case "SCQ_Revenge_7":
			npchar.quest.SeekCap = "womanRevenge"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = StringFromKey("ForAll_dialog_602", FindMoneyString(sti(npchar.quest.money)));
			link.l1 = StringFromKey("ForAll_dialog_603");
			link.l1.go = "SCQ_Revenge_8";
			link.l2 = StringFromKey("ForAll_dialog_604", pchar);
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Revenge_8":
			dialog.text = StringFromKey("ForAll_dialog_605", npchar.quest.SeekCap.capName, GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Acc")), npchar.quest.SeekCap.shipName, XI_ConvertString("Colony" + npchar.quest.Qcity));
			link.l1 = StringFromKey("ForAll_dialog_606", GetAddress_FormToNPC(NPChar));
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";
			pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanRevenge";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanRevenge", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony" + npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Pre")));
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("ен", "на"));
			AddQuestUserData(sTitle, "sSex2", GetSexPhrase("", "а"));
			// evganat - генераторы
			sNPCidx = npchar.index;
			pchar.questTemp.SeekCap.(sNPCidx) = "revenge";
		break;
		//муж женщины попал в плен к пиратам
		case "SCQ_Pirates":
			dialog.text = StringFromKey("ForAll_dialog_607");
			link.l1 = StringFromKey("ForAll_dialog_608");
			link.l1.go = "SCQ_Pirates_1";
		break;
		case "SCQ_Pirates_1":
			dialog.text = StringFromKey("ForAll_dialog_609");
			link.l1 = StringFromKey("ForAll_dialog_610");
			link.l1.go = "SCQ_Pirates_2";
		break;
		case "SCQ_Pirates_2":
			dialog.text = StringFromKey("ForAll_dialog_611");
			link.l1 = StringFromKey("ForAll_dialog_612");
			link.l1.go = "SCQ_Pirates_3";
		break;
		case "SCQ_Pirates_3":
			dialog.text = StringFromKey("ForAll_dialog_613");
			link.l1 = StringFromKey("ForAll_dialog_614");
			link.l1.go = "SCQ_Pirates_4";
		break;
		case "SCQ_Pirates_4":
			dialog.text = StringFromKey("ForAll_dialog_615");
			link.l1 = StringFromKey("ForAll_dialog_616");
			link.l1.go = "SCQ_Pirates_5";
		break;
		case "SCQ_Pirates_5":
			npchar.quest.SeekCap = "womanPirates"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = StringFromKey("ForAll_dialog_617");
			link.l1 = StringFromKey("ForAll_dialog_618", pchar);
			link.l1.go = "SCQ_Pirates_6";
			link.l2 = StringFromKey("ForAll_dialog_619", pchar);
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Pirates_6":
			dialog.text = StringFromKey("ForAll_dialog_620");
			link.l1 = StringFromKey("ForAll_dialog_621");
			link.l1.go = "SCQ_Pirates_7";
		break;
		case "SCQ_Pirates_7":
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "man";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у жены есно
			dialog.text = StringFromKey("ForAll_dialog_622", GetFullName(forName), npchar.quest.SeekCap.capName, GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Pre")), npchar.quest.SeekCap.shipName, XI_ConvertString("Colony" + npchar.quest.Qcity));
			link.l1 = StringFromKey("ForAll_dialog_623", pchar);
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";
			pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanPirates";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanPirates", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony" + npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Pre")));
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(forName));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("", "а"));
			// evganat - генераторы
			sNPCidx = npchar.index;
			pchar.questTemp.SeekCap.(sNPCidx) = "pirates";
		break;
		// --- результаты женских квестов ---
		case "SCQ_womanResult":
			dialog.text = StringFromKey("ForAll_dialog_624");
			link.l1 = StringFromKey("ForAll_dialog_625", GetAddress_FormToNPC(NPChar));
			link.l1.go = "SCQ_womanResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "womanHasbandover":
					dialog.text = StringFromKey("ForAll_dialog_626");
					link.l1 = StringFromKey("ForAll_dialog_627", GetAddress_FormToNPC(NPChar), npchar.quest.SeekCap.capName);
					link.l1.go = "SCQR_womanHasband";
				break;
				case "womanRevengeover":
					dialog.text = StringFromKey("ForAll_dialog_628", npchar.quest.SeekCap.capName);
					link.l1 = StringFromKey("ForAll_dialog_629", GetAddress_FormToNPC(NPChar));
					link.l1.go = "SCQR_womanRevenge";
				break;
				case "womanPiratesover":
					dialog.text = StringFromKey("ForAll_dialog_630");
					link.l1 = StringFromKey("ForAll_dialog_631", npchar.quest.SeekCap.name, npchar.quest.SeekCap.lastname);
					link.l1.go = "SCQR_womanPirates";
				break;
			}
		break;
		case "SCQ_womanResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "womanHasband":
					dialog.text = StringFromKey("ForAll_dialog_632", npchar.quest.SeekCap.capName);
					link.l1 = StringFromKey("ForAll_dialog_633", pchar);
					link.l1.go = "exit";
				break;
				case "womanRevenge":
					dialog.text = StringFromKey("ForAll_dialog_634", npchar.quest.SeekCap.capName);
					link.l1 = StringFromKey("ForAll_dialog_635", GetAddress_FormToNPC(NPChar));
					link.l1.go = "exit";
				break;
				case "womanPirates":
					dialog.text = StringFromKey("ForAll_dialog_636");
					link.l1 = StringFromKey("ForAll_dialog_637", pchar, GetAddress_FormToNPC(NPChar), npchar.lastname);
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_womanHasband":
			dialog.text = StringFromKey("ForAll_dialog_638", FindMoneyString(sti(npchar.quest.money)));
			link.l1 = StringFromKey("ForAll_dialog_639");
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8 + drand(8));
			sTitle = npchar.city + "SCQ_womanHasband";
			CloseQuestHeader(sTitle);
			// evganat - генераторы
			sNPCidx = npchar.index;
			DeleteAttribute(pchar, "questTemp.SeekCap." + sNPCidx);
		break;
		case "SCQR_womanRevenge":
			dialog.text = StringFromKey("ForAll_dialog_640", FindMoneyString(sti(npchar.quest.money)));
			link.l1 = StringFromKey("ForAll_dialog_641");
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10 + drand(8));
			TakeNItems(pchar, "jewelry14", rand(3));
			TakeNItems(pchar, "jewelry13", rand(3));
			TakeNItems(pchar, "jewelry10", rand(3));
			TakeNItems(pchar, "jewelry15", rand(3));
			TakeNItems(pchar, "jewelry16", rand(3));
			TakeNItems(pchar, "jewelry18", rand(3));
			TakeNItems(pchar, "jewelry6", rand(3));
			TakeNItems(pchar, "jewelry7", rand(3));
			sTitle = npchar.city + "SCQ_womanRevenge";
			CloseQuestHeader(sTitle);
			// evganat - генераторы
			sNPCidx = npchar.index;
			DeleteAttribute(pchar, "questTemp.SeekCap." + sNPCidx);
		break;
		case "SCQR_womanPirates":
			dialog.text = StringFromKey("ForAll_dialog_642", FindMoneyString(sti(npchar.quest.money)));
			link.l1 = StringFromKey("ForAll_dialog_643");
			link.l1.go = "SCQ_exit";
			sld = characterFromId("womanPirates_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12 + drand(8));
			sTitle = npchar.city + "SCQ_womanPirates";
			CloseQuestHeader(sTitle);
			// evganat - генераторы
			sNPCidx = npchar.index;
			DeleteAttribute(pchar, "questTemp.SeekCap." + sNPCidx);
		break;
		//========= разыскиваемый капитан-работорговец ===========
		case "CitizCap": //встреча на суше
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = StringFromKey("ForAll_dialog_644", pchar);
					link.l1 = StringFromKey("ForAll_dialog_645", GetFullName(npchar));
					link.l1.go = "CCmanSlave";
				break;
			}
		break;
		case "CCmanSlave":
			dialog.text = StringFromKey("ForAll_dialog_646");
			link.l1 = StringFromKey("ForAll_dialog_647", GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]));
			link.l1.go = "CCmanSlave_1";
		break;
		case "CCmanSlave_1":
			dialog.text = StringFromKey("ForAll_dialog_648");
			link.l1 = StringFromKey("ForAll_dialog_649");
			link.l1.go = "CCmanSlave_2";
		break;
		case "CCmanSlave_2":
			dialog.text = StringFromKey("ForAll_dialog_650");
			link.l1 = StringFromKey("ForAll_dialog_651");
			link.l1.go = "CCmanSlave_3";
		break;
		case "CCmanSlave_3":
			dialog.text = StringFromKey("ForAll_dialog_652", pchar);
			link.l1 = StringFromKey("ForAll_dialog_653");
			link.l1.go = "CCmanSlave_4";
		break;

		// Nathaniel (20.08.22): разветвление диалога с целью отсрочить поединок прямо в городе, надо бы добавить запись в журнал Hirurg39
		case "CCmanSlave_4":
			dialog.text = StringFromKey("ForAll_dialog_654");
			link.l1 = StringFromKey("ForAll_dialog_655");
			link.l1.go = "exit";
			NextDiag.TempNode = "CCmanSlave_WaitForFight";
			link.l2 = StringFromKey("ForAll_dialog_656");
			link.l2.go = "CCmanSlave_fight";
		break;

		case "CCmanSlave_WaitForFight":
			dialog.text = StringFromKey("ForAll_dialog_657", pchar);
			link.l1 = StringFromKey("ForAll_dialog_658");
			link.l1.go = "exit";
			link.l2 = StringFromKey("ForAll_dialog_659");
			link.l2.go = "CCmanSlave_fight";
		break;

		case "CCmanSlave_fight":
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			RemoveLandQuestMark_Gen(npchar, "SeekCitizCap");
		break;

		case "CitizCap_inDeck": //встреча на палубе
			dialog.text = StringFromKey("ForAll_dialog_660");
			link.l1 = StringFromKey("ForAll_dialog_661");
			link.l1.go = "CitizCap_inDeck_1";
		break;
		case "CitizCap_inDeck_1":
			dialog.text = StringFromKey("ForAll_dialog_662");
			link.l1 = StringFromKey("ForAll_dialog_663");
			link.l1.go = "CitizCap_inDeck_2";
		break;
		case "CitizCap_inDeck_2":
			dialog.text = StringFromKey("ForAll_dialog_664");
			link.l1 = StringFromKey("ForAll_dialog_665");
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
			RemoveLandQuestMark_Gen(npchar, "SeekCitizCap");
		break;
		case "CitizCap_inDeck_exit":
			dialog.text = StringFromKey("ForAll_dialog_666");
			link.l1 = StringFromKey("ForAll_dialog_667");
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
		break;
		//========= разыскиваемый кэп, похитивший чужую жену ===========
		case "RapeWifeCap":  //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
			dialog.text = StringFromKey("ForAll_dialog_668", pchar);
			link.l1 = StringFromKey("ForAll_dialog_669", pchar, XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen"), GetFullName(sld));
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_1":
			dialog.text = StringFromKey("ForAll_dialog_670");
			link.l1 = StringFromKey("ForAll_dialog_671");
			link.l1.go = "RapeWifeCap_2";
		break;
		case "RapeWifeCap_2":
			dialog.text = StringFromKey("ForAll_dialog_672");
			link.l1 = StringFromKey("ForAll_dialog_673");
			link.l1.go = "RapeWifeCap_3";
		break;
		case "RapeWifeCap_3":
			dialog.text = StringFromKey("ForAll_dialog_674", pchar);
			link.l1 = StringFromKey("ForAll_dialog_675", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
			RemoveLandQuestMark_Gen(npchar, "SeekCitizCap");
		break;
		case "RapeWifeCap_exit":
			dialog.text = StringFromKey("ForAll_dialog_676");
			link.l1 = StringFromKey("ForAll_dialog_677");
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
		break;
		case "RapeWifeCap_inDeck":  //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
			dialog.text = StringFromKey("ForAll_dialog_678", pchar);
			link.l1 = StringFromKey("ForAll_dialog_679", pchar, XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen"), GetFullName(sld));
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_inDeck_1":
			dialog.text = StringFromKey("ForAll_dialog_680");
			link.l1 = StringFromKey("ForAll_dialog_681");
			link.l1.go = "RapeWifeCap_inDeck_2";
		break;
		case "RapeWifeCap_inDeck_2":
			dialog.text = StringFromKey("ForAll_dialog_682");
			link.l1 = StringFromKey("ForAll_dialog_683");
			link.l1.go = "RapeWifeCap_inDeck_3";
		break;
		case "RapeWifeCap_inDeck_3":
			dialog.text = StringFromKey("ForAll_dialog_684", pchar);
			link.l1 = StringFromKey("ForAll_dialog_685", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
			RemoveLandQuestMark_Gen(npchar, "SeekCitizCap");
		break;
		case "RapeWifeCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
			dialog.text = StringFromKey("ForAll_dialog_686");
			link.l1 = StringFromKey("ForAll_dialog_687", pchar, XI_ConvertString("Colony" + npchar.quest.cribCity), sld.quest.SeekCap.name, sld.quest.SeekCap.lastname);
			link.l1.go = "RapeWifeCap_Board_1";
		break;
		case "RapeWifeCap_Board_1":
			dialog.text = StringFromKey("ForAll_dialog_688");
			link.l1 = StringFromKey("ForAll_dialog_689");
			link.l1.go = "RapeWifeCap_Board_2";
		break;
		case "RapeWifeCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;    //нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "woman";
			pchar.GenQuest.CitizSeekCap.ani = "towngirl";
			pchar.GenQuest.CitizSeekCap.model = "women_" + (rand(11) + 1); //модель для нпс
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			SetBan("Looting", 1);
		break;
		//========= похищенная жена ===========
		case "manRapeWife_Board":
			dialog.text = StringFromKey("ForAll_dialog_690");
			link.l1 = StringFromKey("ForAll_dialog_691", pchar);
			link.l1.go = "manRapeWife_Board_1";
		break;
		case "manRapeWife_Board_1":
			dialog.text = StringFromKey("ForAll_dialog_692");
			link.l1 = StringFromKey("ForAll_dialog_693", GetAddress_FormToNPC(NPChar));
			link.l1.go = "manRapeWife_Board_2";
		break;
		case "manRapeWife_Board_2":
			dialog.text = StringFromKey("ForAll_dialog_694");
			link.l1 = StringFromKey("ForAll_dialog_695", GetAddress_FormToNPC(NPChar));
			link.l1.go = "exit";
			//уберем жену из каюты
			ChangeCharacterAddress(npchar, "none", "");
			SetBan("Looting", 0);
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sld.greeting = "cit_complete";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Acc"));
		break;
		//========= разыскиваемый земляк-торговый кэп ===========
		case "FriendCap": //встреча на суше
			dialog.text = StringFromKey("ForAll_dialog_696");
			link.l1 = StringFromKey("ForAll_dialog_697", pchar, TimeGreeting());
			link.l1.go = "FriendCap_1";
		break;
		case "FriendCap_1":
			dialog.text = StringFromKey("ForAll_dialog_698");
			link.l1 = StringFromKey("ForAll_dialog_699", GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]));
			link.l1.go = "FriendCap_2";
		break;
		case "FriendCap_2":
			dialog.text = StringFromKey("ForAll_dialog_700");
			link.l1 = StringFromKey("ForAll_dialog_701", pchar, XI_ConvertString("Colony" + npchar.quest.cribCity + "Pre"));
			link.l1.go = "FriendCap_3";
		break;
		case "FriendCap_3":
			dialog.text = StringFromKey("ForAll_dialog_702");
			link.l1 = StringFromKey("ForAll_dialog_703", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Acc"));
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sld.greeting = "cit_complete";
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
			RemoveLandQuestMark_Gen(npchar, "SeekCitizCap");
		break;
		case "FriendCap_exit":
			dialog.text = StringFromKey("ForAll_dialog_704");
			link.l1 = StringFromKey("ForAll_dialog_705");
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
		break;
		case "FriendCap_inDeck": //встреча на палубе
			dialog.text = StringFromKey("ForAll_dialog_706", TimeGreeting());
			link.l1 = StringFromKey("ForAll_dialog_707");
			link.l1.go = "FriendCap_inDeck_1";
		break;
		case "FriendCap_inDeck_1":
			dialog.text = StringFromKey("ForAll_dialog_708");
			link.l1 = StringFromKey("ForAll_dialog_709", GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]));
			link.l1.go = "FriendCap_inDeck_2";
		break;
		case "FriendCap_inDeck_2":
			dialog.text = StringFromKey("ForAll_dialog_710");
			link.l1 = StringFromKey("ForAll_dialog_711", pchar, XI_ConvertString("Colony" + npchar.quest.cribCity + "Pre"));
			link.l1.go = "FriendCap_inDeck_3";
		break;
		case "FriendCap_inDeck_3":
			dialog.text = StringFromKey("ForAll_dialog_712", pchar);
			link.l1 = StringFromKey("ForAll_dialog_713");
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Acc"));
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sld.greeting = "cit_complete";
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
			RemoveLandQuestMark_Gen(npchar, "SeekCitizCap");
		break;
		//========= разыскиваемый муж-торговец ===========
		case "HasbandCap": //встреча на суше
			dialog.text = StringFromKey("ForAll_dialog_714");
			link.l1 = StringFromKey("ForAll_dialog_715", GetFullName(npchar));
			link.l1.go = "HasbandCap_1";
		break;
		case "HasbandCap_1":
			dialog.text = StringFromKey("ForAll_dialog_716");
			link.l1 = StringFromKey("ForAll_dialog_717");
			link.l1.go = "HasbandCap_2";
		break;
		case "HasbandCap_2":
			dialog.text = StringFromKey("ForAll_dialog_718");
			link.l1 = StringFromKey("ForAll_dialog_719");
			link.l1.go = "HasbandCap_3";
		break;
		case "HasbandCap_3":
			dialog.text = StringFromKey("ForAll_dialog_720");
			link.l1 = StringFromKey("ForAll_dialog_721");
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
			RemoveLandQuestMark_Gen(npchar, "SeekCitizCap");
		break;
		case "HasbandCap_inDeck": //встреча на палубе
			dialog.text = StringFromKey("ForAll_dialog_722");
			link.l1 = StringFromKey("ForAll_dialog_723", GetFullName(npchar));
			link.l1.go = "HasbandCap_inDeck_1";
		break;
		case "HasbandCap_inDeck_1":
			dialog.text = StringFromKey("ForAll_dialog_724");
			link.l1 = StringFromKey("ForAll_dialog_725");
			link.l1.go = "HasbandCap_inDeck_2";
		break;
		case "HasbandCap_inDeck_2":
			dialog.text = StringFromKey("ForAll_dialog_726");
			link.l1 = StringFromKey("ForAll_dialog_727");
			link.l1.go = "HasbandCap_inDeck_3";
		break;
		case "HasbandCap_inDeck_3":
			dialog.text = StringFromKey("ForAll_dialog_728");
			link.l1 = StringFromKey("ForAll_dialog_729");
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
			RemoveLandQuestMark_Gen(npchar, "SeekCitizCap");
		break;
		case "HasbandCap_inDeck_exit":
			dialog.text = StringFromKey("ForAll_dialog_730");
			link.l1 = StringFromKey("ForAll_dialog_731");
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
		break;
		//========= разыскиваемый капитан-обманщик ===========
		case "RevengeCap": //встреча на суше
			dialog.text = StringFromKey("ForAll_dialog_732");
			link.l1 = StringFromKey("ForAll_dialog_733", pchar);
			link.l1.go = "RevengeCap_1";
		break;
		case "RevengeCap_1":
			dialog.text = StringFromKey("ForAll_dialog_734", pchar);
			link.l1 = StringFromKey("ForAll_dialog_735", pchar, GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]));
			link.l1.go = "RevengeCap_2";
		break;
		case "RevengeCap_2":
			dialog.text = StringFromKey("ForAll_dialog_736");
			link.l1 = StringFromKey("ForAll_dialog_737", pchar);
			link.l1.go = "RevengeCap_3";
		break;
		case "RevengeCap_3":
			dialog.text = StringFromKey("ForAll_dialog_738");
			link.l1 = StringFromKey("ForAll_dialog_739", pchar);
			link.l1.go = "RevengeCap_4";
		break;
		case "RevengeCap_4":
			dialog.text = StringFromKey("ForAll_dialog_740");
			link.l1 = StringFromKey("ForAll_dialog_741", pchar);
			link.l1.go = "RevengeCap_5";
		break;
		case "RevengeCap_5":
			dialog.text = StringFromKey("ForAll_dialog_742", pchar);
			link.l1 = StringFromKey("ForAll_dialog_743", pchar);
			link.l1.go = "RevengeCap_6";
		break;
		case "RevengeCap_6":
			dialog.text = StringFromKey("ForAll_dialog_744", pchar);
			link.l1 = StringFromKey("ForAll_dialog_745", pchar);
			link.l1.go = "RevengeCap_7";

			// Nathaniel (06.02.22): дополнительная ветка диалога, чтобы не агрить стражу в городе, надо бы добавить запись в журнал ? Hirurg39
			link.l2 = StringFromKey("ForAll_dialog_746");
			link.l2.go = "exit";
			NextDiag.TempNode = "RevengeCap_6lf";
		break;

		// Nathaniel (06.02.22): дополнительная ветка диалога на случай отсрочки поединка, надо бы добавить запись в журнал ? Hirurg39
		case "RevengeCap_6lf":
			dialog.text = StringFromKey("ForAll_dialog_747", pchar);
			link.l1 = StringFromKey("ForAll_dialog_748", pchar);
			link.l1.go = "RevengeCap_7";
			link.l2 = StringFromKey("ForAll_dialog_749");
			link.l2.go = "exit";
			NextDiag.TempNode = "RevengeCap_6lf";
		break;
		case "RevengeCap_7":
			NextDiag.TempNode = "RevengeCapCap_exit";
			npchar.DeckDialogNode = "RevengeCapCap_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
			LAi_group_Attack(NPChar, Pchar);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			RemoveLandQuestMark_Gen(npchar, "SeekCitizCap");
		break;
		case "RevengeCapCap_exit":
			dialog.text = StringFromKey("ForAll_dialog_750", pchar);
			link.l1 = StringFromKey("ForAll_dialog_751", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_inDeck": //встреча на палубе
			dialog.text = StringFromKey("ForAll_dialog_752");
			link.l1 = StringFromKey("ForAll_dialog_753", GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]));
			link.l1.go = "RevengeCap_inDeck_1";
		break;
		case "RevengeCap_inDeck_1":
			dialog.text = StringFromKey("ForAll_dialog_754");
			link.l1 = StringFromKey("ForAll_dialog_755", pchar);
			link.l1.go = "RevengeCap_inDeck_2";
		break;
		case "RevengeCap_inDeck_2":
			dialog.text = StringFromKey("ForAll_dialog_756");
			link.l1 = StringFromKey("ForAll_dialog_757", pchar);
			link.l1.go = "RevengeCap_inDeck_3";
		break;
		case "RevengeCap_inDeck_3":
			dialog.text = StringFromKey("ForAll_dialog_758");
			link.l1 = StringFromKey("ForAll_dialog_759");
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_inDeck_exit";
			npchar.DeckDialogNode = "RevengeCapCap_inDeck_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
			RemoveLandQuestMark_Gen(npchar, "SeekCitizCap");
		break;
		case "RevengeCapCap_inDeck_exit":
			dialog.text = StringFromKey("ForAll_dialog_760");
			link.l1 = StringFromKey("ForAll_dialog_761");
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_board": //абордаж
			dialog.text = StringFromKey("ForAll_dialog_762");
			link.l1 = StringFromKey("ForAll_dialog_763", pchar, GetFullName(&characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)]));
			link.l1.go = "RevengeCap_board_1";
		break;
		case "RevengeCap_board_1":
			dialog.text = StringFromKey("ForAll_dialog_764", pchar);
			link.l1 = StringFromKey("ForAll_dialog_765", pchar);
			link.l1.go = "RevengeCap_board_2";
		break;
		case "RevengeCap_board_2":
			dialog.text = StringFromKey("ForAll_dialog_766", pchar);
			link.l1 = StringFromKey("ForAll_dialog_767");
			link.l1.go = "RevengeCap_board_3";
		break;
		case "RevengeCap_board_3":
			LAi_SetCurHPMax(npchar);
			//==> флаг квеста сменим у оригинального кэпа
			characters[sti(npchar.baseCapIdx)].quest.SeekCap = "womanRevengeFight";
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= вызволение мужа из пиратских затрюмков =========
		case "PiratesCap_inDeck": //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
			dialog.text = StringFromKey("ForAll_dialog_768");
			link.l1 = StringFromKey("ForAll_dialog_769", sld.quest.SeekCap.name, sld.quest.SeekCap.lastname);
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_inDeck_1":
			dialog.text = StringFromKey("ForAll_dialog_770");
			link.l1 = StringFromKey("ForAll_dialog_771");
			link.l1.go = "PiratesCap_inDeck_2";
		break;
		case "PiratesCap_inDeck_2":
			dialog.text = StringFromKey("ForAll_dialog_772");
			link.l1 = StringFromKey("ForAll_dialog_773");
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
			RemoveLandQuestMark_Gen(npchar, "SeekCitizCap");
		break;
		case "PiratesCapCap_exit":
			dialog.text = StringFromKey("ForAll_dialog_774");
			link.l1 = StringFromKey("ForAll_dialog_775");
			link.l1.go = "exit";
		break;
		case "PiratesCap": //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
			dialog.text = StringFromKey("ForAll_dialog_776");
			link.l1 = StringFromKey("ForAll_dialog_777", sld.quest.SeekCap.name, sld.quest.SeekCap.lastname);
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_1":
			dialog.text = StringFromKey("ForAll_dialog_778");
			link.l1 = StringFromKey("ForAll_dialog_779");
			link.l1.go = "PiratesCap_2";
		break;
		case "PiratesCap_2":
			dialog.text = StringFromKey("ForAll_dialog_780");
			link.l1 = StringFromKey("ForAll_dialog_781");
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
			RemoveLandQuestMark_Gen(npchar, "SeekCitizCap");
		break;
		case "PiratesCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
			dialog.text = StringFromKey("ForAll_dialog_782");
			link.l1 = StringFromKey("ForAll_dialog_783", sld.quest.SeekCap.name, sld.quest.SeekCap.lastname);
			link.l1.go = "PiratesCap_Board_1";
		break;
		case "PiratesCap_Board_1":
			dialog.text = StringFromKey("ForAll_dialog_784");
			link.l1 = StringFromKey("ForAll_dialog_785");
			link.l1.go = "PiratesCap_Board_2";
		break;
		case "PiratesCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;    //нацию для нпс
			pchar.GenQuest.CitizSeekCap.model = "citiz_" + (rand(9) + 11); //модель для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			SetBan("Looting", 1);
		break;
		//========= пленный муж ===========
		case "womanPirates_Board":
			dialog.text = StringFromKey("ForAll_dialog_786");
			link.l1 = StringFromKey("ForAll_dialog_787", pchar, GetFullName(pchar));
			link.l1.go = "womanPirates_Board_1";
		break;
		case "womanPirates_Board_1":
			dialog.text = StringFromKey("ForAll_dialog_788");
			link.l1 = StringFromKey("ForAll_dialog_789");
			link.l1.go = "exit";
			//уберем мужа из каюты
			ChangeCharacterAddress(npchar, "none", "");
			LAi_SetPlayerType(pchar);
			SetBan("Looting", 0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Acc"));
		break;

		//=====================================================================================================================================
		// Warship, 25.05.11. && Jason 10.02.12 Серия миниквестов "Дело чести" -->
		//=====================================================================================================================================
		case "AffairOfHonor_1":
			LAi_CharacterDisableDialog(NPChar);

			if (LoadedLocation.type == "tavern")
			{
				// "Честь мундира"
				if (!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor"))
				{
					dialog.text = StringFromKey("ForAll_dialog_790");
					link.l1 = StringFromKey("ForAll_dialog_791");
					link.l1.go = "AffairOfHonor_CoatHonor_1";
					PChar.QuestTemp.AffairOfHonor.CoatHonor = true;
					break;
				}
			}
			else
			{
				if (NPChar.sex == "man")
				{
					switch (sti(NPChar.quest.AffairOfHonor.numQuest))
					{
						case 0: //"Невольник чести"
							dialog.text = StringFromKey("ForAll_dialog_792", GetAddress_Form(NPChar));
							link.l1 = StringFromKey("ForAll_dialog_793");
							link.l1.go = "AffairOfHonor_HonorSlave_1";
							PChar.QuestTemp.AffairOfHonor.HonorSlave = true;
						break;

						case 1: //"Красотка и пират"
							dialog.text = StringFromKey("ForAll_dialog_794", pchar);
							link.l1 = StringFromKey("ForAll_dialog_795");
							link.l1.go = "AffairOfHonor_BeautifulPirate_1";
							PChar.QuestTemp.AffairOfHonor.BeautifulPirate = true;
						break;

						case 2: //"Заносчивый нахал"
							dialog.text = StringFromKey("ForAll_dialog_796");
							link.l1 = StringFromKey("ForAll_dialog_797", pchar);
							link.l1.go = "AffairOfHonor_Exit";
							link.l2 = StringFromKey("ForAll_dialog_798");
							link.l2.go = "AffairOfHonor_Jackanapes_1";
							PChar.QuestTemp.AffairOfHonor.Jackanapes = true;
						break;

						case 3: //"Волки и овцы"
							dialog.text = StringFromKey("ForAll_dialog_799");
							link.l1 = StringFromKey("ForAll_dialog_800");
							link.l1.go = "AffairOfHonor_WolvesAndSheeps_1";
							PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps = true;
						break;

						case 4: //"Трусливый фехтовалщик"
							dialog.text = StringFromKey("ForAll_dialog_801");
							link.l1 = StringFromKey("ForAll_dialog_802");
							link.l1.go = "AffairOfHonor_CowardFencer_1";
							PChar.QuestTemp.AffairOfHonor.CowardFencer = true;
						break;

						case 5: //"Божий суд"
							dialog.text = StringFromKey("ForAll_dialog_803");
							link.l1 = StringFromKey("ForAll_dialog_804");
							link.l1.go = "exit";
							link.l2 = StringFromKey("ForAll_dialog_805");
							link.l2.go = "AffairOfHonor_GodJudgement_1";
							PChar.QuestTemp.AffairOfHonor.GodJudgement = true;
						break;
					}
				}
				else
				{
					// "Навязчивый кавалер"
					if (!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Cavalier"))
					{
						dialog.text = StringFromKey("ForAll_dialog_806");
						link.l1 = StringFromKey("ForAll_dialog_807", pchar);
						link.l1.go = "AffairOfHonor_Exit";
						link.l2 = StringFromKey("ForAll_dialog_808");
						link.l2.go = "AffairOfHonor_Cavalier_1";
						PChar.QuestTemp.AffairOfHonor.Cavalier = true;
						break;
					}
				}
			}
		break;

		case "AffairOfHonor_Exit":
			ChangeCharacterReputation(PChar, -2);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;

		case "AffairOfHonor_Cavalier_1":
			dialog.text = StringFromKey("ForAll_dialog_809");
			link.l1 = StringFromKey("ForAll_dialog_810");
			link.l1.go = "exit";
			Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 12;
			Scl = 30 + 2 * sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_Cavalier_Man", "off_" + NationShortName(sti(NPChar.nation)) + "_" + (rand(1) + 3), "man", "man", Rank, sti(NPChar.nation), -1, true));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade11", "blade12"), RandPhraseSimple("pistol6", "pistol5"), Scl * 3); //TODO_weapon
			Mft = MOD_SKILL_ENEMY_RATE / 20;
			sld.MultiFighter = 1.0 + Mft; // мультифайтер
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", FindNearestFreeLocator("goto"));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, PChar, "", -1, 5);
			LAi_SetImmortal(sld, true); // Ещё успеем
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_Cavalier_2";
			PChar.QuestTemp.AffairOfHonor.Cavalier.Started = true;
			DisableAllExits(true);
		break;

		case "AffairOfHonor_Cavalier_2":
			if (pchar.sex == "man")
				dialog.text = StringFromKey("ForAll_dialog_811");
			else
				dialog.text = StringFromKey("ForAll_dialog_812");
			link.l1 = StringFromKey("ForAll_dialog_813");
			link.l1.go = "AffairOfHonor_Cavalier_2a";
		break;

		case "AffairOfHonor_Cavalier_2a":
			if (pchar.sex == "man")
				dialog.text = StringFromKey("ForAll_dialog_814");
			else
				dialog.text = StringFromKey("ForAll_dialog_815");
			link.l1 = StringFromKey("ForAll_dialog_816");
			link.l1.go = "AffairOfHonor_Cavalier_3";
		break;

		case "AffairOfHonor_Cavalier_3":
			dialog.text = StringFromKey("ForAll_dialog_817");
			link.l1 = StringFromKey("ForAll_dialog_818");
			link.l1.go = "AffairOfHonor_Cavalier_4";
		break;

		case "AffairOfHonor_Cavalier_4":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DisableAllExits(false);
			// --> заново получаем местный маяк, ибо есть вероятность что выходили из города в другой город
			sld = &Locations[FindLocation(npchar.location)];
			pchar.questTemp.AffairOfHonor.LighthouseId = Colony_GetLighthouseId(sld.fastreload);
			//<--
			LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour() + 2, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "1");
		break;

		case "AffairOfHonor_Cavalier_5":
			dialog.text = StringFromKey("ForAll_dialog_819", pchar);
			link.l1 = StringFromKey("ForAll_dialog_820", pchar);
			link.l1.go = "exit";
			ChangeCharacterReputation(PChar, 6);
			AddCrewMorale(Pchar, 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			ChangeOfficersLoyality("good_all", 1);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;

		case "AffairOfHonor_Cavalier_6":
			dialog.text = StringFromKey("ForAll_dialog_821");
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;

		case "AffairOfHonor_HonorSlave_1":
			sTemp = "";
			if (FindLocation(NPChar.city + "_brothel") != -1)
				sTemp = StringFromKey("ForAll_dialog_822");
			dialog.text = StringFromKey("ForAll_dialog_823", GetAddress_Form(NPChar), sTemp);
			link.l1 = StringFromKey("ForAll_dialog_824");
			link.l1.go = "exit";
			link.l2 = StringFromKey("ForAll_dialog_825");
			link.l2.go = "AffairOfHonor_HonorSlave_1a";
		break;

		case "AffairOfHonor_HonorSlave_1a":
			dialog.text = StringFromKey("ForAll_dialog_826", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("ForAll_dialog_827");
			link.l1.go = "AffairOfHonor_HonorSlave_2";
		break;

		case "AffairOfHonor_HonorSlave_2":
			DialogExit();
			Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 8;
			Scl = 30 + 2 * sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_HonorSlave_Man", "officer_" + (rand(9) + 11), "man", "man", Rank, sti(NPChar.nation), -1, true));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade31", "blade15"), RandPhraseSimple("pistol1", "pistol5"), Scl * 3); //TODO_weapon
			Mft = MOD_SKILL_ENEMY_RATE / 20;
			sld.MultiFighter = 1.0 + Mft; // мультифайтер
			if (rand(1) || FindLocation(NPChar.city + "_brothel") == -1)
			{
				FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
				ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
				LAi_SetSitType(sld);
			}
			else
			{
				ChangeCharacterAddressGroup(sld, NPChar.city + "_brothel", "goto", "goto3");
				LAi_SetCitizenType(sld);
			}
			LAi_SetImmortal(sld, true); // Еще успеем
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_HonorSlave_3";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.HonorSlave.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "3");
		break;

		case "AffairOfHonor_HonorSlave_3":
			dialog.text = StringFromKey("ForAll_dialog_828", pchar);
			link.l1 = StringFromKey("ForAll_dialog_829");
			link.l1.go = "AffairOfHonor_HonorSlave_3a";
		break;

		case "AffairOfHonor_HonorSlave_3a":
			dialog.text = StringFromKey("ForAll_dialog_830", pchar);
			link.l1 = StringFromKey("ForAll_dialog_831");
			link.l1.go = "AffairOfHonor_HonorSlave_3b";
		break;

		case "AffairOfHonor_HonorSlave_3b":
			dialog.text = StringFromKey("ForAll_dialog_832", pchar);
			link.l1 = StringFromKey("ForAll_dialog_833");
			link.l1.go = "AffairOfHonor_HonorSlave_4";
		break;

		case "AffairOfHonor_HonorSlave_4":
			dialog.text = StringFromKey("ForAll_dialog_834");
			link.l1 = StringFromKey("ForAll_dialog_835");
			link.l1.go = "AffairOfHonor_HonorSlave_5";
		break;

		case "AffairOfHonor_HonorSlave_5":
			dialog.text = StringFromKey("ForAll_dialog_836");
			link.l1 = StringFromKey("ForAll_dialog_837");
			link.l1.go = "AffairOfHonor_HonorSlave_6";
		break;

		case "AffairOfHonor_HonorSlave_6":
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour() + 2, false);
			AddQuestRecord("AffairOfHonor", "3_1");
			AddQuestUserData("AffairOfHonor", "sMayak", XI_ConvertString(PChar.QuestTemp.AffairOfHonor.LighthouseId + "Pre"));
		break;

		case "AffairOfHonor_HonorSlave_7":
			dialog.text = StringFromKey("ForAll_dialog_838");
			link.l1 = StringFromKey("ForAll_dialog_839", pchar);
			link.l1.go = "AffairOfHonor_HonorSlave_8";
		break;

		case "AffairOfHonor_HonorSlave_8":
			dialog.text = StringFromKey("ForAll_dialog_840");
			link.l1 = StringFromKey("ForAll_dialog_841");
			link.l1.go = "exit";
			GiveGoldOnAmount(5000 + drand(5) * 1000);
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;

		case "AffairOfHonor_HonorSlave_9":
			dialog.text = StringFromKey("ForAll_dialog_842");
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;

		case "AffairOfHonor_BeautifulPirate_1":
			dialog.text = StringFromKey("ForAll_dialog_843");
			link.l1 = StringFromKey("ForAll_dialog_844");
			link.l1.go = "exit";
			link.l2 = StringFromKey("ForAll_dialog_845");
			link.l2.go = "AffairOfHonor_BeautifulPirate_1a";
		break;

		case "AffairOfHonor_BeautifulPirate_1a":
			dialog.text = StringFromKey("ForAll_dialog_846", pchar);
			link.l1 = StringFromKey("ForAll_dialog_847");
			link.l1.go = "AffairOfHonor_BeautifulPirate_1_1";
		break;

		case "AffairOfHonor_BeautifulPirate_1_1":
			DialogExit();
			NextDiag.CurrentNode = "AffairOfHonor_BeautifulPirate_r";
			npchar.lifeday = 3;
			Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 12;
			Scl = 25 + 3 * sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE / 15;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_BeautifulPirate_Man", "citiz_" + (rand(9) + 51), "man", "man", Rank, sti(NPChar.nation), -1, true)); //watch_quest_moment
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade31", "blade21"), RandPhraseSimple("pistol6", "pistol4"), Scl * 3); //TODO_weapon
			sld.MultiFighter = 1.0 + Mft; // мультифайтер
			FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true); // Еще успеем
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_BeautifulPirate_2";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.BeautifulPirate.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "5");
		break;

		case "AffairOfHonor_BeautifulPirate_r":
			dialog.text = StringFromKey("ForAll_dialog_848");
			link.l1 = StringFromKey("ForAll_dialog_849");
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_BeautifulPirate_r";
		break;

		case "AffairOfHonor_BeautifulPirate_2":
			dialog.text = StringFromKey("ForAll_dialog_850");
			link.l1 = StringFromKey("ForAll_dialog_851");
			link.l1.go = "AffairOfHonor_BeautifulPirate_2a";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;

		case "AffairOfHonor_BeautifulPirate_2a":
			dialog.text = StringFromKey("ForAll_dialog_852", pchar);
			link.l1 = StringFromKey("ForAll_dialog_853", pchar);
			link.l1.go = "AffairOfHonor_BeautifulPirate_3";
		break;

		case "AffairOfHonor_BeautifulPirate_3":
			dialog.text = StringFromKey("ForAll_dialog_854");
			link.l1 = StringFromKey("ForAll_dialog_855");
			link.l1.go = "AffairOfHonor_BeautifulPirate_4";
		break;

		case "AffairOfHonor_BeautifulPirate_4":
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
		break;

		case "AffairOfHonor_BeautifulPirate_5":
			dialog.text = StringFromKey("ForAll_dialog_856");
			link.l1 = StringFromKey("ForAll_dialog_857", pchar);
			link.l1.go = "AffairOfHonor_BeautifulPirate_6";
		break;

		case "AffairOfHonor_BeautifulPirate_6":
			dialog.text = StringFromKey("ForAll_dialog_858");
			link.l1 = StringFromKey("ForAll_dialog_859");
			link.l1.go = "AffairOfHonor_BeautifulPirate_7";
		break;

		case "AffairOfHonor_BeautifulPirate_7":
			dialog.text = StringFromKey("ForAll_dialog_860");
			link.l1 = StringFromKey("ForAll_dialog_861");
			link.l1.go = "exit";
			iTemp = 50 + drand(5) * 10;
			AddMoneyToCharacter(pchar, iTemp * 100);
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;

		case "AffairOfHonor_Jackanapes_1":
			dialog.text = StringFromKey("ForAll_dialog_862");
			link.l1 = StringFromKey("ForAll_dialog_863");
			link.l1.go = "AffairOfHonor_Jackanapes_1_1";
		break;

		case "AffairOfHonor_Jackanapes_1_1":
			dialog.text = StringFromKey("ForAll_dialog_864");
			link.l1 = StringFromKey("ForAll_dialog_865");
			link.l1.go = "AffairOfHonor_Jackanapes_1_2";
		break;

		case "AffairOfHonor_Jackanapes_1_2":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.Jackanapes.Started = true;
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			NPChar.id = "AffairOfHonor_Jackanapes_Man";
			LAi_SetImmortal(NPChar, true); // Еще успеем
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour() + 2, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "7");
			AddQuestUserData("AffairOfHonor", "sMayak", XI_ConvertString(PChar.QuestTemp.AffairOfHonor.LighthouseId + "Pre"));
		break;

		case "AffairOfHonor_Jackanapes_2":
			dialog.text = StringFromKey("ForAll_dialog_866", pchar);
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;

		case "AffairOfHonor_WolvesAndSheeps_1":
			dialog.text = StringFromKey("ForAll_dialog_867");
			link.l1 = StringFromKey("ForAll_dialog_868");
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_2";
		break;

		case "AffairOfHonor_WolvesAndSheeps_2":
			dialog.text = StringFromKey("ForAll_dialog_869");
			link.l1 = StringFromKey("ForAll_dialog_870");
			link.l1.go = "exit";
			link.l2 = StringFromKey("ForAll_dialog_871");
			link.l2.go = "AffairOfHonor_WolvesAndSheeps_3";
		break;

		case "AffairOfHonor_WolvesAndSheeps_3":
			dialog.text = StringFromKey("ForAll_dialog_872");
			link.l1 = StringFromKey("ForAll_dialog_873");
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_4";
		break;

		case "AffairOfHonor_WolvesAndSheeps_4":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps.Started = true;
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 10;
			Scl = 30 + 2 * sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE / 20;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_WolvesAndSheeps_Man", "citiz_" + (rand(9) + 1), "man", "man", Rank, sti(NPChar.nation), -1, true));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade6", "blade9"), RandPhraseSimple("pistol1", "pistol5"), Scl * 3); //TODO_weapon
			sld.MultiFighter = 1.0 + Mft; // мультифайтер
			sld.skill.Fortune = 1;
			sld.Default = NPChar.city + "_tavern";
			sld.Default.group = "sit";
			sld.Default.ToLocator = "sit_front1";
			LAi_SetSitType(sld);
			FreeSitLocator(sld.Default, "sit_base1");
			ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_base1");
			LAi_SetImmortal(sld, true); // Еще успеем
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_WolvesAndSheeps_5";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "9");
		break;

		case "AffairOfHonor_WolvesAndSheeps_5":
			dialog.text = StringFromKey("ForAll_dialog_874", pchar);
			link.l1 = StringFromKey("ForAll_dialog_875", pchar);
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_6";
		break;

		case "AffairOfHonor_WolvesAndSheeps_6":
			if (sti(PChar.money) < 200)
			{
				dialog.text = StringFromKey("ForAll_dialog_876");
				link.l1 = StringFromKey("ForAll_dialog_877");
				link.l1.go = "exit";
				NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_6_1";
			}
			else
			{
				dialog.text = StringFromKey("ForAll_dialog_878");
				link.l1 = StringFromKey("ForAll_dialog_879");
				link.l1.go = "exit";
				PChar.QuestTemp.friend_in_tavern = NPChar.id;
				AddDialogExitQuest("alc");
				DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
				SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
				NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_7";
				NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
			}
		break;

		case "AffairOfHonor_WolvesAndSheeps_6_1":
			dialog.text = StringFromKey("ForAll_dialog_880", pchar);
			if (sti(PChar.money) < 200)
			{
				link.l1 = StringFromKey("ForAll_dialog_881");
				link.l1.go = "AffairOfHonor_WolvesAndSheeps_7";
			}
			else
			{
				link.l1 = StringFromKey("ForAll_dialog_882");
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_6_1";
		break;

		case "AffairOfHonor_WolvesAndSheeps_7":
			dialog.text = StringFromKey("ForAll_dialog_883");
			link.l1 = "...";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_8";
			PChar.GenQuest.Cards.npcharIdx = NPChar.index;
			PChar.GenQuest.Cards.iRate = 50;
			PChar.GenQuest.Cards.SitType = true;
		break;

		case "AffairOfHonor_WolvesAndSheeps_8":
			NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_9";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchCardsGame();
		break;

		case "AffairOfHonor_WolvesAndSheeps_9":
			dialog.text = StringFromKey("ForAll_dialog_884", pchar);
			link.l1 = StringFromKey("ForAll_dialog_885", GetAddress_FormToNPC(NPChar));
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_10";
		break;

		case "AffairOfHonor_WolvesAndSheeps_10":
			dialog.text = StringFromKey("ForAll_dialog_886");
			link.l1 = StringFromKey("ForAll_dialog_887");
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_11";
		break;

		case "AffairOfHonor_WolvesAndSheeps_11":
			AddDialogExitQuest("exit_sit");
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour() + 2, false);
			AddQuestRecord("AffairOfHonor", "17");
			AddQuestUserData("AffairOfHonor", "sNPC", GetFullName(npchar));
			AddQuestUserData("AffairOfHonor", "sMayak", XI_ConvertString(PChar.QuestTemp.AffairOfHonor.LighthouseId + "Pre"));
		break;

		case "AffairOfHonor_WolvesAndSheeps_12":
			dialog.text = StringFromKey("ForAll_dialog_888");
			link.l1 = StringFromKey("ForAll_dialog_889", pchar);
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_13";
		break;

		case "AffairOfHonor_WolvesAndSheeps_13":
			dialog.text = StringFromKey("ForAll_dialog_890");
			link.l1 = StringFromKey("ForAll_dialog_891");
			link.l1.go = "exit";
			iTemp = 50 + drand(5) * 10;
			AddMoneyToCharacter(pchar, iTemp * 100);
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterReputation(PChar, 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;

		case "AffairOfHonor_CowardFencer_1":
			dialog.text = StringFromKey("ForAll_dialog_892");
			link.l1 = StringFromKey("ForAll_dialog_893");
			link.l1.go = "exit";
			link.l2 = StringFromKey("ForAll_dialog_894");
			link.l2.go = "AffairOfHonor_CowardFencer_1_1";
		break;

		case "AffairOfHonor_CowardFencer_1_1":
			dialog.text = StringFromKey("ForAll_dialog_895");
			link.l1 = StringFromKey("ForAll_dialog_896");
			link.l1.go = "AffairOfHonor_CowardFencer_1_2";
		break;

		case "AffairOfHonor_CowardFencer_1_2":
			DialogExit();
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 15;
			Scl = 30 + 3 * sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE / 15;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_CowardFencer_Man", "citiz_" + (rand(9) + 51), "man", "man", Rank, sti(NPChar.nation), -1, true));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade21", "blade31"), RandPhraseSimple("pistol4", "pistol6"), Scl * 3 + 70); //TODO_weapon
			sld.MultiFighter = 1.0 + Mft; // мультифайтер
			LAi_SetCitizenType(sld);
			ChangeCharacterAddressGroup(sld, NPChar.city + "_store", "goto", "goto3");
			LAi_SetImmortal(sld, true); // Еще успеем
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_CowardFencer_2";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.CowardFencer.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "11");
		break;

		case "AffairOfHonor_CowardFencer_2":
			dialog.text = StringFromKey("ForAll_dialog_897");
			link.l1 = StringFromKey("ForAll_dialog_898");
			link.l1.go = "AffairOfHonor_CowardFencer_3";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;

		case "AffairOfHonor_CowardFencer_3":
			dialog.text = StringFromKey("ForAll_dialog_899", pchar);
			link.l1 = StringFromKey("ForAll_dialog_900");
			link.l1.go = "AffairOfHonor_CowardFencer_4";
		break;

		case "AffairOfHonor_CowardFencer_4":
			DialogExit();
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
			LAi_CharacterDisableDialog(NPChar);
		break;

		case "AffairOfHonor_CowardFencer_4_1":
			dialog.text = StringFromKey("ForAll_dialog_901");
			link.l1 = StringFromKey("ForAll_dialog_902");
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;

		case "AffairOfHonor_CowardFencer_5":
			dialog.text = StringFromKey("ForAll_dialog_903");
			link.l1 = StringFromKey("ForAll_dialog_904");
			link.l1.go = "AffairOfHonor_CowardFencer_6";
		break;

		case "AffairOfHonor_CowardFencer_6":
			dialog.text = StringFromKey("ForAll_dialog_905");
			link.l1 = StringFromKey("ForAll_dialog_906");
			link.l1.go = "exit";
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterReputation(PChar, 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddComplexSelfExpToScill(60, 60, 60, 60);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
			AddItemLog(pchar, "chest", "1", StringFromKey("InfoMessages_136"), "Important_item");
		break;

		case "AffairOfHonor_CoatHonor_1":
			LAi_CharacterEnableDialog(NPChar);
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_2";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			PChar.QuestTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "AffairOfHonor_CoatHonor_2":
			dialog.text = StringFromKey("ForAll_dialog_907");
			link.l1 = StringFromKey("ForAll_dialog_908");
			link.l1.go = "AffairOfHonor_CoatHonor_2_1";
		break;

		case "AffairOfHonor_CoatHonor_2_1":
			dialog.text = StringFromKey("ForAll_dialog_909");
			link.l1 = StringFromKey("ForAll_dialog_910");
			link.l1.go = "AffairOfHonor_CoatHonor_2_2";
		break;

		case "AffairOfHonor_CoatHonor_2_2":
			dialog.text = StringFromKey("ForAll_dialog_911");
			link.l1 = StringFromKey("ForAll_dialog_912");
			link.l1.go = "AffairOfHonor_CoatHonor_2_3";
		break;

		case "AffairOfHonor_CoatHonor_2_3":
			dialog.text = StringFromKey("ForAll_dialog_913");
			link.l1 = StringFromKey("ForAll_dialog_914");
			link.l1.go = "AffairOfHonor_CoatHonor_Exit";
			link.l2 = StringFromKey("ForAll_dialog_915");
			link.l2.go = "AffairOfHonor_CoatHonor_2_4";
			LAi_SetAlcoholState(1);
		break;

		case "AffairOfHonor_CoatHonor_2_4":
			dialog.text = StringFromKey("ForAll_dialog_916");
			link.l1 = StringFromKey("ForAll_dialog_917");
			link.l1.go = "AffairOfHonor_CoatHonor_2_5";
		break;

		case "AffairOfHonor_CoatHonor_2_5":
			dialog.text = StringFromKey("ForAll_dialog_918");
			link.l1 = StringFromKey("ForAll_dialog_919");
			link.l1.go = "AffairOfHonor_CoatHonor_3";
		break;

		case "AffairOfHonor_CoatHonor_Exit":
			DialogExit();
			AddDialogExitQuest("exit_sit");
			LAi_CharacterDisableDialog(NPChar);
			NextDiag.CurrentNode = NextDiag.TempNode;

			RemoveLandQuestMark_Gen(NPChar, "AffairOfHonor");
		break;

		case "AffairOfHonor_CoatHonor_3":
			AddDialogExitQuest("exit_sit");
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_Next";
			DialogExit();
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 2, false);
			PChar.QuestTemp.AffairOfHonor.CoatHonor.Started = true;
			PChar.QuestTemp.AffairOfHonor.CoatHonor.CityId = NPChar.city;
			PChar.QuestTemp.AffairOfHonor.CoatHonor.locationId = GetRandomCommonLoc(npchar);
			PChar.quest.CoatHonor.win_condition.l1 = "location";
			PChar.quest.CoatHonor.win_condition.l1.location = PChar.QuestTemp.AffairOfHonor.CoatHonor.locationId;
			PChar.quest.CoatHonor.win_condition = "CoatHonor_Login";
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "13");
			npchar.lifeday = 2;
			RemoveLandQuestMark_Gen(NPChar, "AffairOfHonor");
		break;

		case "AffairOfHonor_CoatHonor_Next":
			dialog.text = StringFromKey("ForAll_dialog_920", pchar);
			link.l1 = StringFromKey("ForAll_dialog_921");
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_Next";
		break;

		case "AffairOfHonor_CoatHonor_Final":
			dialog.text = StringFromKey("ForAll_dialog_922", pchar);
			link.l1 = StringFromKey("ForAll_dialog_923");
			link.l1.go = "AffairOfHonor_CoatHonor_Final_1";
		break;

		case "AffairOfHonor_CoatHonor_Final_1":
			dialog.text = StringFromKey("ForAll_dialog_924", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("ForAll_dialog_925");
			link.l1.go = "AffairOfHonor_CoatHonor_Final_2";
		break;

		case "AffairOfHonor_CoatHonor_Final_2":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_End";
			AddMoneyToCharacter(pchar, 8000 + dRandEx(5, false) * 1000);
			AddCrewMorale(pchar, 2);
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
		break;

		case "AffairOfHonor_CoatHonor_End":
			dialog.text = StringFromKey("ForAll_dialog_926", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("ForAll_dialog_927");
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_End";
		break;

		case "AffairOfHonor_CoatHonor_4":
			dialog.text = StringFromKey("ForAll_dialog_928");
			link.l1 = StringFromKey("ForAll_dialog_929", pchar);
			link.l1.go = "AffairOfHonor_CoatHonor_5";
		break;

		case "AffairOfHonor_CoatHonor_5":
			dialog.text = StringFromKey("ForAll_dialog_930", pchar);
			link.l1 = StringFromKey("ForAll_dialog_931", GetAddress_FormToNPC(NPChar));
			link.l1.go = "AffairOfHonor_CoatHonor_6";
		break;

		case "AffairOfHonor_CoatHonor_6":
			dialog.text = StringFromKey("ForAll_dialog_932", pchar);
			link.l1 = StringFromKey("ForAll_dialog_933", GetAddress_FormToNPC(NPChar));
			link.l1.go = "AffairOfHonor_CoatHonor_7";
		break;

		case "AffairOfHonor_CoatHonor_7":
			dialog.text = StringFromKey("ForAll_dialog_934");
			link.l1 = StringFromKey("ForAll_dialog_935");
			link.l1.go = "AffairOfHonor_CoatHonor_8";
		break;

		case "AffairOfHonor_CoatHonor_8":
			DialogExit();
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour() + 2, false);
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_9";
			LAi_SetWarriorType(npchar); // 140313
			AddQuestRecord("AffairOfHonor", "17");
			AddQuestUserData("AffairOfHonor", "sNPC", GetFullName(npchar));
			AddQuestUserData("AffairOfHonor", "sMayak", XI_ConvertString(PChar.QuestTemp.AffairOfHonor.LighthouseId + "Pre"));
		break;

		case "AffairOfHonor_CoatHonor_9":
			dialog.text = StringFromKey("ForAll_dialog_936");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_9";
		break;

		case "AffairOfHonor_GodJudgement_1":
			dialog.text = StringFromKey("ForAll_dialog_937");
			link.l1 = StringFromKey("ForAll_dialog_938");
			link.l1.go = "AffairOfHonor_GodJudgement_1_1";
		break;

		case "AffairOfHonor_GodJudgement_1_1":
			dialog.text = StringFromKey("ForAll_dialog_939");
			link.l1 = StringFromKey("ForAll_dialog_940");
			link.l1.go = "AffairOfHonor_GodJudgement_1_2";
		break;

		case "AffairOfHonor_GodJudgement_1_2":
			DialogExit();
			// --> заново получаем местный маяк, ибо есть вероятность что выходили из города в другой город
			sld = &Locations[FindLocation(npchar.location)];
			pchar.questTemp.AffairOfHonor.LighthouseId = Colony_GetLighthouseId(sld.fastreload);
			//<--
			PChar.QuestTemp.AffairOfHonor.GodJudgement.Started = true;
			PChar.QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest = true;
			PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId = NPChar.city;
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 12;
			Scl = 30 + 2 * sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE / 20;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man", "citiz_" + (rand(9) + 21), "man", "man", Rank, sti(NPChar.nation), -1, true));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade18", "blade8"), RandPhraseSimple("pistol1", "pistol5"), Scl * 3); //TODO_weapon
			sld.MultiFighter = 1.0 + Mft; // мультифайтер
			LAi_SetImmortal(sld, true); // Еще успеем
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.greeting = "Enc_Raiders";
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "15");
		break;

		case "AffairOfHonor_GodJudgement_2":
			dialog.text = StringFromKey("ForAll_dialog_941");
			link.l1 = StringFromKey("ForAll_dialog_942");
			link.l1.go = "AffairOfHonor_GodJudgement_3";
		break;

		case "AffairOfHonor_GodJudgement_3":
			dialog.text = StringFromKey("ForAll_dialog_943");
			link.l1 = StringFromKey("ForAll_dialog_944");
			link.l1.go = "exit";
			npchar.lifeday = 0;
			GiveGoldOnAmount(6000 + dRandEx(4, false) * 1000);
			AddCrewMorale(Pchar, 3);
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterReputation(PChar, 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			LAi_CharacterDisableDialog(NPChar);
		break;

		// Диалоги до боя -->
		case "AffairOfHonor_BeforeFight_1":
			dialog.text = StringFromKey("ForAll_dialog_945");
			link.l1 = StringFromKey("ForAll_dialog_946");
			link.l1.go = "AffairOfHonor_BeforeFight_2";

			switch (AffairOfHonor_GetCurQuest())
			{
				case "Cavalier":
					dialog.text = StringFromKey("ForAll_dialog_947");
					link.l1 = StringFromKey("ForAll_dialog_948");
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;

				case "HonorSlave":
					dialog.text = StringFromKey("ForAll_dialog_949");
					link.l1 = StringFromKey("ForAll_dialog_950");
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;

				case "BeautifulPirate":
					dialog.text = StringFromKey("ForAll_dialog_951");
					link.l1 = StringFromKey("ForAll_dialog_952", pchar);
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;

				case "Jackanapes":
					dialog.text = StringFromKey("ForAll_dialog_953");
					link.l1 = StringFromKey("ForAll_dialog_954");
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;

				case "WolvesAndSheeps":
					dialog.text = StringFromKey("ForAll_dialog_955", pchar);
					link.l1 = StringFromKey("ForAll_dialog_956");
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;

				case "CowardFencer":
					dialog.text = StringFromKey("ForAll_dialog_957", pchar);
					link.l1 = StringFromKey("ForAll_dialog_958");
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;

				case "CoatHonor":
					dialog.text = StringFromKey("ForAll_dialog_959", pchar);
					link.l1 = StringFromKey("ForAll_dialog_960");
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;

				case "GodJudgement":
					dialog.text = StringFromKey("ForAll_dialog_961", pchar);
					link.l1 = StringFromKey("ForAll_dialog_962");
					link.l1.go = "AffairOfHonor_BeforeFight_2_1";
				break;
			}
		break;

		case "AffairOfHonor_BeforeFight_2_1":
			dialog.text = StringFromKey("ForAll_dialog_963", pchar);
			link.l1 = StringFromKey("ForAll_dialog_964");
			link.l1.go = "AffairOfHonor_BeforeFight_2";
		break;

		case "AffairOfHonor_BeforeFight_2":
			LAi_LocationFightDisable(LoadedLocation, false);
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.Quest.AffairOfHonor_KillChar.win_condition.l1 = "NPC_Death";
			PChar.Quest.AffairOfHonor_KillChar.win_condition.l1.character = "AffairOfHonor_" + AffairOfHonor_GetCurQuest() + "_Man";
			PChar.Quest.AffairOfHonor_KillChar.function = "AffairOfHonor_KillChar";
			if (dRand(1) == 0 && AffairOfHonor_GetCurQuest() != "CowardFencer" && AffairOfHonor_GetCurQuest() != "CoatHonor")
			{
				PChar.QuestTemp.AffairOfHonor.FightWithHelpers = true;
				Log_TestInfo("Секунданты будут сражаться");
			}
			// В квесте "Божий суд" всегда нападают
			if (AffairOfHonor_GetCurQuest() == "GodJudgement")
			{
				Log_TestInfo("Глобальное месиво");
				sld = CharacterFromID("AffairOfHonor_Helper_1");
				LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				LAi_SetImmortal(sld, false);
				sld = CharacterFromID("AffairOfHonor_Helper_2");
				LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				LAi_SetImmortal(sld, false);
				iTemp = dRandEx(3, false);
				if (AffairOfHonor_GetCurQuest() == "GodJudgement")
				{
					for (i = 0; i < iTemp; i++)
					{
						sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(15) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true));
						SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
						ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
						LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
					}
				}
			}
			LAi_Group_MoveCharacter(NPChar, "AffairOfHonor_Enemies");
			LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);
			DialogExit();
		break;

		// Диалоги после боя -->
		case "AffairOfHonor_AfterFight_1":
			if (CheckAttribute(PChar, "QuestTemp.AffairOfHonor.FightWithHelpers"))
			{
				dialog.text = StringFromKey("ForAll_dialog_965");
				link.l1 = StringFromKey("ForAll_dialog_966");
				link.l1.go = "AffairOfHonor_AfterFight_FightWithHelpers";
				break;
			}
			if (AffairOfHonor_GetCurQuest() == "CoatHonor")
			{
				dialog.text = StringFromKey("ForAll_dialog_967");
				link.l1 = StringFromKey("ForAll_dialog_968");
				link.l1.go = "AffairOfHonor_AfterFight_2_1";
			}
			else
			{
				dialog.text = StringFromKey("ForAll_dialog_969");
				link.l1 = StringFromKey("ForAll_dialog_970");
				link.l1.go = "AffairOfHonor_AfterFight_2";
			}
		break;

		case "AffairOfHonor_AfterFight_2_1":
			dialog.text = StringFromKey("ForAll_dialog_971");
			link.l1 = StringFromKey("ForAll_dialog_972");
			link.l1.go = "AffairOfHonor_AfterFight_2";
		break;

		case "AffairOfHonor_AfterFight_2":
			DialogExit();
			LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			LAi_ActorGoToLocation(CharacterFromID("AffairOfHonor_Helper_2"), "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			if (AffairOfHonor_GetCurQuest() == "CoatHonor") ChangeCharacterReputation(PChar, 5);
		break;

		case "AffairOfHonor_AfterFight_FightWithHelpers":
			iTemp = dRandEx(3, false);
			AddDialogExitQuest("MainHeroFightModeOn");
			sld = CharacterFromID("AffairOfHonor_Helper_1");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			sld = CharacterFromID("AffairOfHonor_Helper_2");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			if (AffairOfHonor_GetCurQuest() == "GodJudgement")
			{
				for (i = 0; i < iTemp; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(15) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true));
					SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
					ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
					LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				}
			}
			LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);
			DialogExit();
		break;
		//=====================================================================================================================================
		// <-- Серия миниквестов "Дело чести".
		//=====================================================================================================================================

		//несчастный мушкетер
		case "OffMushketer":
			dialog.text = StringFromKey("ForAll_dialog_973", pchar);
			link.l1 = StringFromKey("ForAll_dialog_974", GetFullName(pchar));
			link.l1.go = "OffM_1";
		break;
		case "OffM_1":
			dialog.text = StringFromKey("ForAll_dialog_975");
			link.l1 = StringFromKey("ForAll_dialog_976");
			link.l1.go = "OffM_2";
		break;
		case "OffM_2":
			dialog.text = StringFromKey("ForAll_dialog_977");
			link.l1 = StringFromKey("ForAll_dialog_978");
			link.l1.go = "OffM_4";
		break;
		case "OffM_4":
			dialog.text = StringFromKey("ForAll_dialog_979");
			link.l1 = StringFromKey("ForAll_dialog_980");
			link.l1.go = "OffM_5";
		break;
		case "OffM_5":
			dialog.text = StringFromKey("ForAll_dialog_981");
			link.l1 = StringFromKey("ForAll_dialog_982");
			link.l1.go = "OffM_6";
		break;
		case "OffM_6":
			dialog.text = StringFromKey("ForAll_dialog_983");
			link.l1 = StringFromKey("ForAll_dialog_984");
			link.l1.go = "OffM_7";
		break;
		case "OffM_7":
			dialog.text = StringFromKey("ForAll_dialog_985");
			link.l1 = StringFromKey("ForAll_dialog_986");
			link.l1.go = "OffM_8";
		break;
		case "OffM_8":
			dialog.text = StringFromKey("ForAll_dialog_987");
			link.l1 = StringFromKey("ForAll_dialog_988");
			link.l1.go = "OffM_9";
		break;
		case "OffM_9":
			dialog.text = StringFromKey("ForAll_dialog_989");
			link.l1 = StringFromKey("ForAll_dialog_990");
			link.l1.go = "OffM_10";
		break;
		case "OffM_10":
			dialog.text = StringFromKey("ForAll_dialog_991");
			link.l1 = StringFromKey("ForAll_dialog_992", pchar);
			link.l1.go = "OffM_11";
		break;
		case "OffM_11":
			dialog.text = StringFromKey("ForAll_dialog_993");
			link.l1 = StringFromKey("ForAll_dialog_994");
			link.l1.go = "OffM_12";
		break;
		case "OffM_12":
			dialog.text = StringFromKey("ForAll_dialog_995");
			link.l1 = StringFromKey("ForAll_dialog_996");
			link.l1.go = "exit";
			pchar.questTemp.mushket2x2 = true;
			AddQuestRecord("SeekDoubleMushket", "1");
			NextDiag.TempNode = "OffM_result";

			RemoveLandQuestMark_Main(npchar, "SeekDoubleMushket");
			RemoveMapQuestMark("PortSpein_town", "SeekDoubleMushket");

			AddLandQuestMark_Main(CharacterFromID("Jackman"), "SeekDoubleMushket");
			AddLandQuestMark_Main(CharacterFromID("LeFransua_Mayor"), "SeekDoubleMushket");
		break;

		case "OffM_result":
			dialog.text = StringFromKey("ForAll_dialog_997");
			if (CheckCharacterItem(pchar, "mushket2x2"))
			{
				link.l1 = StringFromKey("ForAll_dialog_998", pchar);
				link.l1.go = "OffM_result_1";
			}
			else
			{
				link.l1 = StringFromKey("ForAll_dialog_999");
				link.l1.go = "exit";
			}
		break;
		case "OffM_result_1":
			dialog.text = StringFromKey("ForAll_dialog_1000");
			link.l1 = StringFromKey("ForAll_dialog_1001");
			link.l1.go = "OffM_result_2";
			TakeItemFromCharacter(pchar, "mushket2x2");
			Npchar.Payment = true; //для функции ↓
			Npchar.quest.OfficerPrice = GetMoneyForOfficerFull(Npchar);
		break;
		case "OffM_result_2":
			dialog.text = StringFromKey("ForAll_dialog_1002", FindMoneyString(sti(Npchar.quest.OfficerPrice)));
			link.l1 = StringFromKey("ForAll_dialog_1003");
			link.l1.go = "OffM_trade";
			link.l2 = StringFromKey("ForAll_dialog_1004", pchar);
			link.l2.go = "OffM_Ok";
		break;
		case "OffM_trade":
			dialog.text = StringFromKey("ForAll_dialog_1005");
			link.l1 = StringFromKey("ForAll_dialog_1006", pchar);
			link.l1.go = "OffM_Ok";
		break;
		case "OffM_Ok":
			Npchar.quest.OfficerPrice.add = sti(pchar.rank) * 1000;
			dialog.text = StringFromKey("ForAll_dialog_1007", FindMoneyString(sti(Npchar.quest.OfficerPrice.add)));
			link.l1 = StringFromKey("ForAll_dialog_1008");
			link.l1.go = "OffM_Ok_1";
		break;
		case "OffM_Ok_1":
			dialog.text = StringFromKey("ForAll_dialog_1009");
			if (sti(pchar.money) < sti(Npchar.quest.OfficerPrice.add))
			{
				link.l1 = StringFromKey("ForAll_dialog_1010");
				link.l1.go = "OffM_noMoney";
			}
			else
			{
				link.l1 = StringFromKey("ForAll_dialog_1011");
				link.l1.go = "OffM_noMoney";
				link.l2 = StringFromKey("ForAll_dialog_1012", pchar);
				link.l2.go = "OffM_Ok_3";
			}
			NextDiag.TempNode = "OffM_TWO";
		break;
		case "OffM_noMoney":
			dialog.text = StringFromKey("ForAll_dialog_1013");
			link.l1 = StringFromKey("ForAll_dialog_1014");
			link.l1.go = "exit";
		break;
		case "OffM_Ok_3":
			dialog.text = StringFromKey("ForAll_dialog_1015");
			link.l1 = StringFromKey("ForAll_dialog_1016");
			link.l1.go = "exit_hire";
		break;
		case "exit_hire":
			if (CheckAttribute(&TEV, "MushketCapShipRumourId"))
			{
				DeleteRumor(FindRumour(sti(TEV.MushketCapShipRumourId)));
				DeleteAttribute(&TEV, "MushketCapShipRumourId");
			}
			AddQuestRecord("SeekDoubleMushket", "3");
			CloseQuestHeader("SeekDoubleMushket");
			RemoveLandQuestMark_Main(npchar, "SeekDoubleMushket");
			RemoveMapQuestMark("PortSpein_town", "SeekDoubleMushket");
			AddMoneyToCharacter(pchar, -sti(Npchar.quest.OfficerPrice.add));
			npchar.HeroModel = "Humphrey_Douglas,Humphrey_Douglas_1,Humphrey_Douglas_2,Humphrey_Douglas_3,Humphrey_Douglas_4,Humphrey_Douglas_5";
            MakeOffMush(npchar, "mushket2x2", 50, 50); // мушкетёрское
			npchar.greeting = "Gr_questOfficer";
			npchar.Dialog.Filename = "Officer_Man.c";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
			Achievment_Set(ACH_Chudo_mushket);
		break;
		case "OffM_TWO":
			dialog.text = StringFromKey("ForAll_dialog_1017", FindMoneyString(sti(Npchar.quest.OfficerPrice.add)), FindMoneyString(sti(Npchar.quest.OfficerPrice)));
			if (sti(pchar.money) < sti(Npchar.quest.OfficerPrice.add))
			{
				link.l1 = StringFromKey("ForAll_dialog_1018");
				link.l1.go = "OffM_noMoney";
			}
			else
			{
				link.l1 = StringFromKey("ForAll_dialog_1019");
				link.l1.go = "OffM_noMoney";
				link.l2 = StringFromKey("ForAll_dialog_1020", pchar);
				link.l2.go = "OffM_Ok_3";
			}
			NextDiag.TempNode = "OffM_TWO";
		break;
		case "Ericson_cave":
			dialog.text = StringFromKey("ForAll_dialog_1021");
			link.l1 = StringFromKey("ForAll_dialog_1022", NPChar.name);
			link.l1.go = "exit_cave";
		break;
		case "exit_cave":
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetOfficerType(NPChar);
			LAi_SetPlayerType(pchar);
			NPChar.dialog.filename = NPChar.dialog.filename.origin;
			DeleteAttribute(NPChar, "dialog.filename.origin");
			DialogExit();
		break;
	}
}

void GetPerlShore()
{
	switch (rand(4))
	{
		case 0:
			pchar.questTemp.Sharp.PearlAreal = "Mein";
			pchar.questTemp.Sharp.PearlAreal.Island = "Beliz";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore_ship2";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_8";
			pchar.questTemp.Sharp.PearlAreal.add = StringFromKey("ForAll_dialog_1023");
		break;
		case 1:
			pchar.questTemp.Sharp.PearlAreal = "Mein";
			pchar.questTemp.Sharp.PearlAreal.Island = "Cumana";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore18";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_8";
			pchar.questTemp.Sharp.PearlAreal.add = StringFromKey("ForAll_dialog_1024");
		break;
		case 2:
			pchar.questTemp.Sharp.PearlAreal = "Dominica";
			pchar.questTemp.Sharp.PearlAreal.Island = "Dominica";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore26";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_3";
		break;
		case 3:
			pchar.questTemp.Sharp.PearlAreal = "Terks";
			pchar.questTemp.Sharp.PearlAreal.Island = "Terks";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore56";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_1";
		break;
		case 4:
			pchar.questTemp.Sharp.PearlAreal = "Caiman";
			pchar.questTemp.Sharp.PearlAreal.Island = "Caiman";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore17";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_1";
		break;
	}
	pchar.questTemp.Sharp.PearlAreal.terms = rand(5) + 5; //сроки
	pchar.questTemp.Sharp.PearlAreal.qtyShips = rand(6) + 6; //кол-во тартан ловцов
	//	pchar.questTemp.Sharp.PearlAreal.SmallPearlQty = 0; //для итогового подсчета
	//	pchar.questTemp.Sharp.PearlAreal.BigPearlQty = 0;
	pchar.questTemp.Sharp.PearlAreal.PinctadaQty = 0;
	// Если находимся в той же области, то генерим расположение тартан вновь
	if (GetArealByLocation(pchar.location) == pchar.questTemp.Sharp.PearlAreal) GetPerlShore();
}

void SetSeekCapCitizenParam(ref npchar, int iNation)
{
	//создаем кэпов
	int Rank = sti(pchar.rank) + 5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCitizCap_" + npchar.index, "", "man", "man", Rank, iNation, -1, true));
	bool change_award = true;
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle":
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_battleCap";
			sld.DeckDialogNode = "NM_battleDeck";

			change_award = false;
			npchar.quest.money = (7 - sti(RealShips[sti(sld.Ship.Type)].Class)) * 8000 + sti(pchar.rank) * 500;
		break;

		case "NM_prisoner":
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_prisonerCap";
			sld.DeckDialogNode = "NM_prisonerCap";

			change_award = false;
			npchar.quest.money = (7 - sti(RealShips[sti(sld.Ship.Type)].Class)) * 10000 + sti(pchar.rank) * 600;
		break;

		case "NM_peace":
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "war";
			SetCaptanModelByEncType(sld, "war");
			sld.dialog.currentnode = "NM_peaceCap";
			sld.DeckDialogNode = "NM_peaceCap";

			change_award = false;
			npchar.quest.money = (7 - sti(RealShips[sti(sld.Ship.Type)].Class)) * 6000 + sti(pchar.rank) * 400;
		break;

		case "manSlave":
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "CitizCap";
			sld.DeckDialogNode = "CitizCap_inDeck";
		break;

		case "manRapeWife":
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RapeWifeCap";
			sld.DeckDialogNode = "RapeWifeCap_inDeck";
		break;

		case "manFriend":
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "FriendCap";
			sld.DeckDialogNode = "FriendCap_inDeck";
		break;

		case "womanHasband":
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			sld.lastname = npchar.lastname; //во имя крепких семейных уз
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "HasbandCap";
			sld.DeckDialogNode = "HasbandCap_inDeck";
		break;

		case "womanRevenge":
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RevengeCap";
			sld.DeckDialogNode = "RevengeCap_inDeck";
		break;

		case "womanPirates":
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "PiratesCap";
			sld.DeckDialogNode = "PiratesCap_inDeck";
		break;
	}
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	//записываем данные в структуры портмана и кэпа
	npchar.quest.SeekCap.capId = sld.id; //Id искомого кэпа
	npchar.quest.SeekCap.capName = GetFullName(sld); //имя искомого кэпа
	npchar.quest.SeekCap.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.SeekCap.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	if (change_award)
	{
		npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype) + 1) * 1000) + (sti(pchar.rank) * 500); //вознаграждение
		npchar.quest.gem = GenQuestCitizen_GenerateGem(); //камешки
	}
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.quest.SeekCap = npchar.quest.SeekCap; //запишем кэпу флаг квеста
	sld.quest.nation = iNation; //запомним базовую нацию кэпа
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придет
	Log_TestInfo("Разыскиваемый кэп " + sld.id + " вышел из: " + sld.city + " и направился в: " + sld.quest.targetCity + "");
	sld.quest.cribCity = npchar.city; //город, где ошивается квестодатель
	npchar.quest.Qcity = sld.city; // Взял из ККС, чтоб была наводка на город от квестодателя Hirurg39
	// evganat - генераторы
	ref rCharacter;
	rCharacter = &characters[GetCharacterIndex(sld.City + "_PortMan")];
	string sTemp = sld.id;
	rCharacter.quest.capitainsList.(sTemp) = sld.quest.targetCity; //куда отправился
	rCharacter.quest.capitainsList.(sTemp).date = GetDateString(); //запишем дату, когда отправился
	rCharacter.quest.capitainsList.(sTemp).QBString1 = sld.quest.cribCity + "SCQ_" + characters[GetCharacterIndex("QuestCitiz_" + sld.quest.cribCity)].quest.SeekCap;
	rCharacter.quest.capitainsList.(sTemp).QBString2 = "SCQ_" + characters[GetCharacterIndex("QuestCitiz_" + sld.quest.cribCity)].quest.SeekCap;
	rCharacter.quest.capitainsList.(sTemp).QBQty = 2;
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle":     sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_prisoner":     sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_peace":     sld.mapEnc.worldMapShip = "ranger";      break;
		case "manSlave":     sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manRapeWife":     sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manFriend":     sld.mapEnc.worldMapShip = "ranger";      break;
		case "womanHasband": sld.mapEnc.worldMapShip = "ranger";      break;
		case "womanRevenge": sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "womanPirates": sld.mapEnc.worldMapShip = "Galleon_red"; break;
	}
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.SeekCap.shipTapeName) + " '" + npchar.quest.SeekCap.shipName + "'";
	int daysQty = GetMaxDaysFromColony2Colony(sld.quest.targetCity, sld.city) + 5; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на смерть кэпа
	sTemp = "SCQ_" + sld.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на смерть квестодателя
	sTemp = "SCQ_" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).function = "SCQ_CitizenIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	pchar.quest.(sTemp).CitizenId = npchar.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "citizen"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = npchar.id; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SCQ_" + npchar.quest.SeekCap; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
	NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
	NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
	NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	//квест-метка
	AddLandQuestMark_Gen(sld, "SeekCitizCap");
}

string GenQuestCitizen_GenerateGem() // камни
{
	string itemID;
	switch (rand(5))
	{
		case 0:
			itemID = "jewelry1";
		break;
		case 1:
			itemID = "jewelry2";
		break;
		case 2:
			itemID = "jewelry3";
		break;
		case 3:
			itemID = "jewelry4";
		break;
		case 4:
			itemID = "jewelry5";
		break;
		case 5:
			itemID = "jewelry17";
		break;
	}
	return itemID;
}

string SelectNB_battleText()
{
	string sText;
	switch (dRandEx(5, false))
	{
		case 0: sText = StringFromKey("ForAll_dialog_1025"); break;
		case 1: sText = StringFromKey("ForAll_dialog_1026"); break;
		case 2: sText = StringFromKey("ForAll_dialog_1027"); break;
		case 3: sText = StringFromKey("ForAll_dialog_1028"); break;
		case 4: sText = StringFromKey("ForAll_dialog_1029"); break;
		case 5: sText = StringFromKey("ForAll_dialog_1030"); break;
	}
	return sText;
}

void SelectNB_prisonerText(ref npchar)
{
	switch (dRandEx(5, false))
	{
		case 0:
			npchar.quest.text = StringFromKey("ForAll_dialog_1031");
			npchar.quest.text1 = StringFromKey("ForAll_dialog_1032");
		break;
		case 1:
			npchar.quest.text = StringFromKey("ForAll_dialog_1033");
			npchar.quest.text1 = StringFromKey("ForAll_dialog_1034");
		break;
		case 2:
			npchar.quest.text = StringFromKey("ForAll_dialog_1035");
			npchar.quest.text1 = StringFromKey("ForAll_dialog_1036");
		break;
		case 3:
			npchar.quest.text = StringFromKey("ForAll_dialog_1037");
			npchar.quest.text1 = StringFromKey("ForAll_dialog_1038");
		break;
		case 4:
			npchar.quest.text = StringFromKey("ForAll_dialog_1039");
			npchar.quest.text1 = StringFromKey("ForAll_dialog_1040");
		break;
		case 5:
			npchar.quest.text = StringFromKey("ForAll_dialog_1041");
			npchar.quest.text1 = StringFromKey("ForAll_dialog_1042");
		break;
	}
}

void SelectNB_peaceText(ref npchar)
{
	switch (dRandEx(5, false))
	{
		case 0:
			npchar.quest.text = StringFromKey("ForAll_dialog_1043");
			npchar.quest.text1 = StringFromKey("ForAll_dialog_1044");
		break;
		case 1:
			npchar.quest.text = StringFromKey("ForAll_dialog_1045");
			npchar.quest.text1 = StringFromKey("ForAll_dialog_1046");
		break;
		case 2:
			npchar.quest.text = StringFromKey("ForAll_dialog_1047");
			npchar.quest.text1 = StringFromKey("ForAll_dialog_1048");
		break;
		case 3:
			npchar.quest.text = StringFromKey("ForAll_dialog_1049");
			npchar.quest.text1 = StringFromKey("ForAll_dialog_1050");
		break;
		case 4:
			npchar.quest.text = StringFromKey("ForAll_dialog_1051");
			npchar.quest.text1 = StringFromKey("ForAll_dialog_1052");
		break;
		case 5:
			npchar.quest.text = StringFromKey("ForAll_dialog_1053");
			npchar.quest.text1 = StringFromKey("ForAll_dialog_1054");
		break;
	}
}

void SeaPearl_SharpPrisoner_AddTreasureItems()
{
	TakeNItems(pchar, "incas_collection", 1);
	TakeNItems(pchar, "chest", 2);
	TakeNItems(pchar, "jewelry1", 50 + rand(10));
	TakeNItems(pchar, "jewelry2", 50 + rand(10));
	TakeNItems(pchar, "jewelry3", 50 + rand(10));
	TakeNItems(pchar, "jewelry4", 50 + rand(10));
	TakeNItems(pchar, "jewelry11", 100 + rand(10));
	TakeNItems(pchar, "jewelry12", 200 + rand(20));
}

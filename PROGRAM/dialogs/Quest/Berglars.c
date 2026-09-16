void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp, sStr, sPlace;
	float locx, locy, locz;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	if (Dialog.CurrentNode == "First time")
	{
		switch (pchar.questTemp.tugs.berglarState)
		{
			case "2": Dialog.CurrentNode = "Second time";    break;
			case "3": Dialog.CurrentNode = "Third time";    break;
			case "4": Dialog.CurrentNode = "Fourth time";    break;
			case "5": Dialog.CurrentNode = "Fifth time";    break;
			case "6": Dialog.CurrentNode = "Sixth time";    break;
		}
	}

	switch (Dialog.CurrentNode)
	{
		//------------- первая боевка --------------
		case "First time":
			if (sti(pchar.rank) >= 5 || MOD_SKILL_ENEMY_RATE > 9)
			{
				dialog.text = StringFromKey("Berglars_1", pchar);
				link.l1 = StringFromKey("Berglars_2", GetFullName(pchar));
				link.l1.go = "Step1_1";
			}
			else
			{
				dialog.text = StringFromKey("Berglars_3");
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		case "Step1_1":
			dialog.text = StringFromKey("Berglars_4", pchar);
			link.l1 = StringFromKey("Berglars_5");
			link.l1.go = "Step1_2";
		break;
		case "Step1_2":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance")
				sStr = StringFromKey("Berglars_6");
			else
				sStr = StringFromKey("Berglars_7");
			dialog.text = StringFromKey("Berglars_8", sStr);
			link.l1 = StringFromKey("Berglars_9");
			link.l1.go = "Step1_3";
		break;
		case "Step1_3":
			dialog.text = StringFromKey("Berglars_10");
			link.l1 = StringFromKey("Berglars_11");
			link.l1.go = "Step1_4";
		break;
		case "Step1_4":
			dialog.text = StringFromKey("Berglars_12", pchar);
			link.l1 = StringFromKey("Berglars_13", pchar);
			link.l1.go = "Step_overAll";
			AddQuestRecord("BerglarsGang", "1");
			AddQuestUserData("BerglarsGang", "sCity", GetCityName(npchar.City));
			RemoveMapQuestMark(npchar.city + "_town", "BerglarsGang");
		break;
		//--------------
		case "Fight_1":
			dialog.text = StringFromKey("Berglars_14", pchar);
			link.l1 = StringFromKey("Berglars_15", pchar);
			link.l1.go = "FirstFight_1";
			PChar.quest.Birglars_Time.over = "yes";
		break;
		case "FirstFight_1":
			dialog.text = StringFromKey("Berglars_16", pchar);
			link.l1 = StringFromKey("Berglars_17");
			link.l1.go = "FirstFight_2";
		break;
		case "FirstFight_2":
			dialog.text = StringFromKey("Berglars_18", pchar);
			link.l1 = StringFromKey("Berglars_19", pchar);
			link.l1.go = "FirstFight_3";
		break;
		case "FirstFight_3":
			dialog.text = StringFromKey("Berglars_20", pchar);
			link.l1 = StringFromKey("Berglars_21", pchar);
			link.l1.go = "FirstFight_4";
		break;
		case "FirstFight_4":
			dialog.text = StringFromKey("Berglars_22", pchar);
			link.l1 = StringFromKey("Berglars_23");
			link.l1.go = "FirstFight_overAll";
			AddQuestRecord("BerglarsGang", "2");
		break;
		//------------ вторая боевка ----------------
		case "Second time":
			dialog.text = StringFromKey("Berglars_24");
			link.l1 = StringFromKey("Berglars_25");
			link.l1.go = "Step2_1";
		break;
		case "Step2_1":
			dialog.text = StringFromKey("Berglars_26");
			link.l1 = StringFromKey("Berglars_27", GetFullName(pchar));
			link.l1.go = "Step2_2";
		break;
		case "Step2_2":
			dialog.text = StringFromKey("Berglars_28");
			link.l1 = StringFromKey("Berglars_29");
			link.l1.go = "Step2_3";
		break;
		case "Step2_3":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance")
				sStr = StringFromKey("Berglars_30");
			else
				sStr = StringFromKey("Berglars_31");
			dialog.text = StringFromKey("Berglars_32", sStr);
			link.l1 = StringFromKey("Berglars_33");
			link.l1.go = "Step_overAll";
			AddQuestRecord("BerglarsGang", "3");
			AddQuestUserData("BerglarsGang", "sCity", GetCityName(npchar.City));
			RemoveMapQuestMark(npchar.city + "_town", "BerglarsGang");
		break;
		//----------
		case "Fight_2":
			dialog.text = StringFromKey("Berglars_34");
			link.l1 = StringFromKey("Berglars_35", pchar);
			link.l1.go = "SecondFight_1";
			PChar.quest.Birglars_Time.over = "yes";
		break;
		case "SecondFight_1":
			dialog.text = StringFromKey("Berglars_36");
			link.l1 = StringFromKey("Berglars_37");
			link.l1.go = "SecondFight_2";
		break;
		case "SecondFight_2":
			dialog.text = StringFromKey("Berglars_38", pchar);
			link.l1 = StringFromKey("Berglars_39", pchar);
			link.l1.go = "SecondFight_3";
		break;
		case "SecondFight_3":
			dialog.text = StringFromKey("Berglars_40", pchar);
			link.l1 = StringFromKey("Berglars_41");
			link.l1.go = "FirstFight_overAll";
			AddQuestRecord("BerglarsGang", "4");
		break;
		//------------ третья встреча, сумасшедший ----------------
		case "Third time":
			dialog.text = StringFromKey("Berglars_42", pchar);
			link.l1 = StringFromKey("Berglars_43");
			link.l1.go = "Step3_1";
		break;
		case "Step3_1":
			dialog.text = StringFromKey("Berglars_44");
			link.l1 = StringFromKey("Berglars_45");
			link.l1.go = "Step3_2";
		break;
		case "Step3_2":
			dialog.text = StringFromKey("Berglars_46");
			link.l1 = StringFromKey("Berglars_47");
			link.l1.go = "Step3_3";
		break;
		case "Step3_3":
			dialog.text = StringFromKey("Berglars_48", pchar);
			link.l1 = StringFromKey("Berglars_49");
			link.l1.go = "Step3_4";
		break;
		case "Step3_4":
			dialog.text = StringFromKey("Berglars_50", pchar);
			link.l1 = StringFromKey("Berglars_51");
			link.l1.go = "Step3_5";
		break;
		case "Step3_5":
			dialog.text = StringFromKey("Berglars_52", pchar);
			link.l1 = StringFromKey("Berglars_53");
			link.l1.go = "Step3_6";
		break;
		case "Step3_6":
			dialog.text = StringFromKey("Berglars_54");
			link.l1 = StringFromKey("Berglars_55");
			link.l1.go = "Step3_7";
		break;
		case "Step3_7":
			dialog.text = StringFromKey("Berglars_56", pchar);
			link.l1 = StringFromKey("Berglars_57");
			link.l1.go = "Step3_8";
		break;
		case "Step3_8":
			dialog.text = StringFromKey("Berglars_58");
			link.l1 = StringFromKey("Berglars_59");
			link.l1.go = "Step3_9";
			AddQuestRecord("BerglarsGang", "5");
			AddQuestUserData("BerglarsGang", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("BerglarsGang", "sCity", GetCityName(npchar.City));
		break;
		case "Step3_9":
			sTemp = "berglar" + npchar.city;
			pchar.questTemp.tugs.berglarState = sti(pchar.questTemp.tugs.berglarState) + 1; //счетчик
			npchar.LifeDay = 0;
			LAi_SetActorTypeNoGroup(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", pchar.questTemp.tugs.(sTemp).locator, "none", "", "", "", -1);
			pchar.questTemp.(sTemp) = "over";
			DialogExit();
			RemoveMapQuestMark(npchar.city + "_town", "BerglarsGang");
		break;
		//------------ четвёртая встреча ----------------
		case "Fourth time":
			dialog.text = StringFromKey("Berglars_60", GetFullName(pchar));
			link.l1 = StringFromKey("Berglars_61", pchar);
			link.l1.go = "Step4_1";
		break;
		case "Step4_1":
			dialog.text = StringFromKey("Berglars_62");
			link.l1 = StringFromKey("Berglars_63", pchar);
			link.l1.go = "Step4_2";
		break;
		case "Step4_2":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance")
				sStr = StringFromKey("Berglars_64");
			else
				sStr = StringFromKey("Berglars_65");
			dialog.text = StringFromKey("Berglars_66", GetAddress_Form(NPChar), sStr);
			link.l1 = StringFromKey("Berglars_67");
			link.l1.go = "Step4_3";
			link.l2 = StringFromKey("Berglars_68");
			link.l2.go = "Step4_5";
		break;
		case "Step4_3":
			pchar.questTemp.OstinDelete = "true";
			dialog.text = StringFromKey("Berglars_69");
			link.l1 = StringFromKey("Berglars_70");
			link.l1.go = "Step4_4";
		break;
		case "Step4_4":
			sTemp = "berglar" + npchar.city;
			npchar.LifeDay = 0;
			RemoveLandQuestmark_Main(npchar, "BerglarsGang");
			LAi_SetActorTypeNoGroup(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", pchar.questTemp.tugs.(sTemp).locator, "none", "", "", "", -1);
			pchar.questTemp.(sTemp) = "over";
			AddQuestRecord("BerglarsGang", "6");
			AddQuestUserData("BerglarsGang", "sSex", GetSexPhrase("", "а"));
			AddDialogExitQuestFunction("Birglars_Time");
			DialogExit();
		break;
		case "Step4_5":
			dialog.text = StringFromKey("Berglars_71");
			link.l1 = StringFromKey("Berglars_72");
			link.l1.go = "Step4_6";
		break;
		case "Step4_6":
			dialog.text = StringFromKey("Berglars_73", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Berglars_74");
			link.l1.go = "Step_overAll";
			AddQuestRecord("BerglarsGang", "7");
			AddQuestUserData("BerglarsGang", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("BerglarsGang", "sCity", GetCityName(npchar.City));
			RemoveMapQuestMark(npchar.city + "_town", "BerglarsGang");
		break;
		case "Fight_4":
			dialog.text = StringFromKey("Berglars_75", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("Berglars_76");
			link.l1.go = "Fight4_1";
			PChar.quest.Birglars_Time.over = "yes";
		break;
		case "Fight4_1":
			dialog.text = StringFromKey("Berglars_77", pchar);
			link.l1 = StringFromKey("Berglars_78");
			link.l1.go = "Fight4_2";
		break;
		case "Fight4_2":
			dialog.text = StringFromKey("Berglars_79", pchar);
			link.l1 = StringFromKey("Berglars_80");
			link.l1.go = "Fight4_3";
		break;
		case "Fight4_3":
			dialog.text = StringFromKey("Berglars_81");
			link.l1 = StringFromKey("Berglars_82");
			link.l1.go = "Fight4_4";
		break;
		case "Fight4_4":
			dialog.text = StringFromKey("Berglars_83", pchar);
			link.l1 = StringFromKey("Berglars_84");
			link.l1.go = "FirstFight_overAll";
			AddQuestRecord("BerglarsGang", "8");
		break;
		//------------ пятая встреча ----------------
		case "Fifth time":
			dialog.text = StringFromKey("Berglars_85", pchar, GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Berglars_86");
			link.l1.go = "Step5_1";
		break;
		case "Step5_1":
			dialog.text = StringFromKey("Berglars_87", pchar);
			link.l1 = StringFromKey("Berglars_88");
			link.l1.go = "Step5_2";
		break;
		case "Step5_2":
			dialog.text = StringFromKey("Berglars_89");
			link.l1 = StringFromKey("Berglars_90");
			link.l1.go = "Step5_3";
		break;
		case "Step5_3":
			dialog.text = StringFromKey("Berglars_91");
			link.l1 = StringFromKey("Berglars_92");
			link.l1.go = "Step5_4";
		break;
		case "Step5_4":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance")
				sStr = StringFromKey("Berglars_93");
			else
				sStr = StringFromKey("Berglars_94");
			dialog.text = StringFromKey("Berglars_95", sStr);
			link.l1 = StringFromKey("Berglars_96");
			link.l1.go = "Step5_5";
			link.l2 = StringFromKey("Berglars_97");
			link.l2.go = "Step5_7";
		break;
		case "Step5_5":
			pchar.questTemp.OstinDelete = "true";
			dialog.text = StringFromKey("Berglars_98");
			link.l1 = StringFromKey("Berglars_99", pchar);
			link.l1.go = "Step5_6";
		break;
		case "Step5_6":
			sTemp = "berglar" + npchar.city;
			npchar.LifeDay = 0;
			RemoveLandQuestmark_Main(npchar, "BerglarsGang");
			LAi_SetActorTypeNoGroup(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", pchar.questTemp.tugs.(sTemp).locator, "none", "", "", "", -1);
			pchar.questTemp.(sTemp) = "over";
			AddQuestRecord("BerglarsGang", "9");
			AddQuestUserData("BerglarsGang", "sSex", GetSexPhrase("", "а"));
			AddDialogExitQuestFunction("Birglars_Time");
			DialogExit();
		break;
		case "Step5_7":
			dialog.text = StringFromKey("Berglars_100");
			link.l1 = StringFromKey("Berglars_101", pchar);
			link.l1.go = "Step_overAll";
			AddQuestRecord("BerglarsGang", "10");
			AddQuestUserData("BerglarsGang", "sCity", GetCityName(npchar.City));
			RemoveMapQuestMark(npchar.city + "_town", "BerglarsGang");
		break;
		case "Fight_5":
			dialog.text = StringFromKey("Berglars_102", GetFullName(pchar));
			link.l1 = StringFromKey("Berglars_103");
			link.l1.go = "Fight5_1";
			PChar.quest.Birglars_Time.over = "yes";
		break;
		case "Fight5_1":
			dialog.text = StringFromKey("Berglars_104", pchar);
			link.l1 = StringFromKey("Berglars_105");
			link.l1.go = "Fight5_2";
		break;
		case "Fight5_2":
			dialog.text = StringFromKey("Berglars_106");
			link.l1 = StringFromKey("Berglars_107");
			link.l1.go = "Fight5_3";
		break;
		case "Fight5_3":
			dialog.text = StringFromKey("Berglars_108", pchar);
			link.l1 = StringFromKey("Berglars_109");
			link.l1.go = "Fight5_4";
		break;
		case "Fight5_4":
			dialog.text = StringFromKey("Berglars_110");
			link.l1 = StringFromKey("Berglars_111", pchar);
			link.l1.go = "Fight5_5";
		break;
		case "Fight5_5":
			dialog.text = StringFromKey("Berglars_112");
			link.l1 = StringFromKey("Berglars_113");
			link.l1.go = "FirstFight_overAll";
			AddQuestRecord("BerglarsGang", "11");
		break;
		//------------ шестая встреча ----------------
		case "Sixth time":
			dialog.text = StringFromKey("Berglars_114", GetAddress_Form(NPChar), GetFullName(pchar));
			link.l1 = StringFromKey("Berglars_115");
			link.l1.go = "Step6_1";
		break;
		case "Step6_1":
			dialog.text = StringFromKey("Berglars_116");
			link.l1 = StringFromKey("Berglars_117", pchar);
			link.l1.go = "Step6_2";
		break;
		case "Step6_2":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance")
				sStr = StringFromKey("Berglars_118");
			else
				sStr = StringFromKey("Berglars_119");
			dialog.text = StringFromKey("Berglars_120", sStr);
			link.l1 = StringFromKey("Berglars_121");
			link.l1.go = "Step_overAll";
			AddQuestRecord("BerglarsGang", "12");
			AddQuestUserData("BerglarsGang", "sCity", GetCityName(npchar.City));
			RemoveMapQuestMark(npchar.city + "_town", "BerglarsGang");
		break;
		case "Fight_6":
			dialog.text = StringFromKey("Berglars_122", GetFullName(pchar));
			link.l1 = StringFromKey("Berglars_123");
			link.l1.go = "Fight6_1";
			PChar.quest.Birglars_Time.over = "yes";
		break;
		case "Fight6_1":
			dialog.text = StringFromKey("Berglars_124");
			link.l1 = StringFromKey("Berglars_125");
			link.l1.go = "Fight6_2";
		break;
		case "Fight6_2":
			dialog.text = StringFromKey("Berglars_126", GetFullName(pchar));
			link.l1 = StringFromKey("Berglars_127", pchar);
			link.l1.go = "Fight6_3";
		break;
		case "Fight6_3":
			dialog.text = StringFromKey("Berglars_128", pchar);
			link.l1 = StringFromKey("Berglars_129");
			link.l1.go = "Fight6_4";
		break;
		case "Fight6_4":
			dialog.text = StringFromKey("Berglars_130");
			link.l1 = StringFromKey("Berglars_131");
			link.l1.go = "FirstFight_overAll";
			AddQuestRecord("BerglarsGang", "13");
		break;
		//------------ общие ноды ----------------
		case "Step_overAll":
			sTemp = "berglar" + npchar.city;
			sStr = "Birglars_fight_" + npchar.index;
			pchar.quest.(sStr).win_condition.l1 = "locator";
			pchar.quest.(sStr).win_condition.l1.location = pchar.questTemp.tugs.(sTemp);
			pchar.quest.(sStr).win_condition.l1.locator_group = "item";
			pchar.quest.(sStr).win_condition.l1.locator = "berglar1";
			pchar.quest.(sStr).function = "Birglars_fight";
			pchar.quest.(sStr).city = npchar.city; //запомним город грабителя
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			NextDiag.CurrentNode = "Fight_" + pchar.questTemp.tugs.berglarState;
			npchar.equip.blade = FindCharacterItemByGroup(npchar, BLADE_ITEM_TYPE);
			npchar.equip.gun = FindCharacterItemByGroup(npchar, GUN_ITEM_TYPE);
			sTemp = "berglar" + npchar.city;
			LAi_LocationDisableMonGenTimer(pchar.questTemp.tugs.(sTemp), 1); //монстров не генерить 1 день
			LAi_LocationDisableOffGenTimer(pchar.questTemp.tugs.(sTemp), 1); //офицеров не пускать 1 день
			LAi_SetActorTypeNoGroup(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", pchar.questTemp.tugs.(sTemp).locator, pchar.questTemp.tugs.(sTemp), "item", "berglar1", "OpenTheDoors", -1.0);
			chrDisableReloadToLocation = true;
			//SetTimerFunction("Birglars_Time", 0, 0, 1);
			PChar.quest.Birglars_Time.win_condition.l1 = "Timer";
			PChar.quest.Birglars_Time.win_condition.l1.date.hour = 22;
			PChar.quest.Birglars_Time.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.Birglars_Time.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.Birglars_Time.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.Birglars_Time.function = "Birglars_Time";
			//pchar.questTemp.tugs.(sTemp) = "fight";
			DialogExit();
		break;
		case "FirstFight_overAll":
			LAi_group_Delete("BerglarsGang");
			pchar.questTemp.tugs.berglarState = sti(pchar.questTemp.tugs.berglarState) + 1; //счетчик
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			SetCharacterPerk(npchar, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, дается ГГ и боссам уровней
			npchar.cirassId = FindItem("cirass5"); //1.2.3
			sTemp = "berglar" + npchar.city;
			RemoveLandQuestmark_Main(npchar, "BerglarsGang");

			// дадим слухи
			if (sti(pchar.questTemp.tugs.berglarState) == 2)
			{
				AddSimpleRumourCityTip(
					StringFromKey("Berglars_132", GetAddress_Form(pchar)), npchar.city, 3, 1, "habitue", "");
			}
			if (sti(pchar.questTemp.tugs.berglarState) == 4)
			{
				AddSimpleRumourCityTip(
					StringFromKey("Berglars_133", GetAddress_Form(pchar)), npchar.city, 3, 1, "habitue", "");
			}

			LAi_SetHP(npchar, stf(pchar.questTemp.tugs.(sTemp).hp), stf(pchar.questTemp.tugs.(sTemp).hp));
			LAi_SetCurHPMax(npchar);
			chrDisableReloadToLocation = true;
			DeleteAttribute(npchar, "city"); //чтобы не ругались с нацией
			LAi_group_MoveCharacter(npchar, "BerglarsGang");
			if (npchar.id == "BerglarFortFrance")
			{
				GetCharacterPos(pchar, &locx, &locy, &locz);
				sld = GetCharacter(NPC_GenerateCharacter("Berglars_Helper", "citiz_" + (rand(9) + 51), "man", "man", 18, PIRATE, 0, true)); //watch_quest_moment
				FantomMakeCoolFighter(sld, 18, 60, 50, BLADE_LONG, "pistol3", 10);
				LAi_group_MoveCharacter(sld, "BerglarsGang");
				ChangeCharacterAddressGroup(sld, npchar.location, "monsters", LAi_FindNearestFreeLocator("monsters", locx, locy, locz));
			}
			if (npchar.id == "BerglarPanama")
			{
				GetCharacterPos(pchar, &locx, &locy, &locz);
				sld = GetCharacter(NPC_GenerateCharacter("Berglars_Helper", "citiz_" + (rand(9) + 51), "man", "man", 21, PIRATE, 0, true)); //watch_quest_moment
				FantomMakeCoolFighter(sld, 21, 60, 50, BLADE_LONG, "pistol3", 20);
				LAi_group_MoveCharacter(sld, "BerglarsGang");
				ChangeCharacterAddressGroup(sld, npchar.location, "monsters", LAi_FindNearestFreeLocator("monsters", locx, locy, locz));
			}
			if (npchar.id == "BerglarSantaCatalina")
			{
				GetCharacterPos(pchar, &locx, &locy, &locz);
				sld = GetCharacter(NPC_GenerateCharacter("Berglars_Helper", "citiz_" + (rand(9) + 51), "man", "man", 20, PIRATE, 0, true)); //watch_quest_moment
				FantomMakeCoolFighter(sld, 20, 60, 50, BLADE_LONG, "pistol3", 20);
				LAi_group_MoveCharacter(sld, "BerglarsGang");
				ChangeCharacterAddressGroup(sld, npchar.location, "monsters", LAi_FindNearestFreeLocator("monsters", locx, locy, locz));
			}
			LAi_group_SetRelation("BerglarsGang", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("BerglarsGang", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("BerglarsGang", "BerglarsGangEndFight");

			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//------------ финальная боевка с Остином ----------------
		case "Final_fight":
			dialog.text = StringFromKey("Berglars_134");
			link.l1 = StringFromKey("Berglars_135", pchar);
			link.l1.go = "StepF1_1";
		break;
		case "StepF1_1":
			dialog.text = StringFromKey("Berglars_136", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("Berglars_137");
			link.l1.go = "StepF1_2";
		break;
		case "StepF1_2":
			dialog.text = StringFromKey("Berglars_138", pchar);
			link.l1 = StringFromKey("Berglars_139");
			link.l1.go = "StepF1_3";
		break;
		case "StepF1_3":
			dialog.text = StringFromKey("Berglars_140", pchar);
			link.l1 = StringFromKey("Berglars_141");
			link.l1.go = "StepF1_4";
		break;
		case "StepF1_4":
			dialog.text = StringFromKey("Berglars_142");
			link.l1 = StringFromKey("Berglars_143");
			link.l1.go = "StepF1_5";
		break;
		case "StepF1_5":
			dialog.text = StringFromKey("Berglars_144", pchar);
			link.l1 = StringFromKey("Berglars_145");
			link.l1.go = "StepF1_6";
		break;
		case "StepF1_6":
			dialog.text = StringFromKey("Berglars_146", pchar);
			link.l1 = StringFromKey("Berglars_147", pchar);
			link.l1.go = "StepF1_7";
		break;
		case "StepF1_7":
			dialog.text = StringFromKey("Berglars_148", pchar);
			link.l1 = StringFromKey("Berglars_149");
			link.l1.go = "StepF1_8";
		break;
		case "StepF1_8":
			dialog.text = StringFromKey("Berglars_150", pchar, GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Berglars_151", pchar);
			link.l1.go = "StepF1_9";
		break;
		case "StepF1_9":
			LAi_LocationFightDisable(loadedLocation, false);
			CloseQuestHeader("BerglarsGang");
			LAi_group_Delete("EnemyFight");
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			npchar.cirassId = FindItem("cirass5"); //1.2.3
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Berglars_Over");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Exit":
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

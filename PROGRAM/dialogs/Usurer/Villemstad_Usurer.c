// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	float locx, locy, locz;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Villemstad_Usurer_3", RandPhraseSimple(
								StringFromKey("Villemstad_Usurer_1"),
								StringFromKey("Villemstad_Usurer_2"))),
						StringFromKey("Villemstad_Usurer_4"),
						StringFromKey("Villemstad_Usurer_5"),
						StringFromKey("Villemstad_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Villemstad_Usurer_9", RandPhraseSimple(
								StringFromKey("Villemstad_Usurer_7", pchar),
								StringFromKey("Villemstad_Usurer_8"))),
						StringFromKey("Villemstad_Usurer_10"),
						StringFromKey("Villemstad_Usurer_11"),
						StringFromKey("Villemstad_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Эммануэль Пардаль: Портниха знатной дамы
			if(CheckAttribute(pchar, "questTemp.EPL_PZD_Rostovshik"))
			{
				DeleteAttribute(pchar, "questTemp.EPL_PZD_Rostovshik");
				link.l1 = StringFromKey("Villemstad_Usurer_67");
				link.l1.go = "EPL_PZD_Rost_1";
				break;
			}
			// <== Эммануэль Пардаль: Портниха знатной дамы
			// ==> англ.линейка квест №4 Разведмиссию в Кюрасао
			if (pchar.questTemp.State == "Intelligence_Curacao_toYozef")
			{
				link.l1 = StringFromKey("Villemstad_Usurer_13", pchar);
				link.l1.go = "Step_E4_1";
			}
			if (pchar.questTemp.State == "Intelligence_Curacao_NoMoney_Yozef")
			{
				link.l1 = StringFromKey("Villemstad_Usurer_14", pchar);
				link.l1.go = "no_money";
			}
			if (pchar.questTemp.State == "Inquisition_toCuracao" || pchar.questTemp.State == "Inquisition_afterFrancisco")// квест №2 голл. линейки.
			{
				if (!CheckAttribute(pchar, "questTemp.State.Usurer"))
				{
					dialog.text = StringFromKey("Villemstad_Usurer_15");
					link.l1 = StringFromKey("Villemstad_Usurer_16");
					link.l1.go = "Step_S2_1";
				}
				else
				{
					if (CheckPassengerInCharacter(pchar, "JansenDeFonceicao"))
					{
						dialog.text = StringFromKey("Villemstad_Usurer_17");
						link.l1 = StringFromKey("Villemstad_Usurer_18");
						link.l1.go = "Step_S2_5";
					}
					else
					{
						if (pchar.questTemp.State.Usurer != "Ok")
						{
							dialog.text = StringFromKey("Villemstad_Usurer_19", pchar);
							link.l1 = StringFromKey("Villemstad_Usurer_20");
							link.l1.go = "exit";
						}
						else
						{
							dialog.text = StringFromKey("Villemstad_Usurer_21", pchar);
							link.l1 = StringFromKey("Villemstad_Usurer_22");
							link.l1.go = "exit";
						}
					}
				}
			}
			//пиратка, квест №5
			if (pchar.questTemp.piratesLine == "PL5Hunter_toVillemstad")
			{
				link.l1 = StringFromKey("Villemstad_Usurer_23");
				link.l1.go = "Step_P5_1";
			}
		break;
		//********************** Английская линейка, квест №4 "Разведка в Кюрасао" ************************
		case "Step_E4_1":
			dialog.text = StringFromKey("Villemstad_Usurer_24");
			link.l1 = StringFromKey("Villemstad_Usurer_25", pchar);
			link.l1.go = "Step_E4_2";
		break;
		case "Step_E4_2":
			dialog.text = StringFromKey("Villemstad_Usurer_26");
			link.l1 = StringFromKey("Villemstad_Usurer_27", pchar);
			link.l1.go = "Step_E4_3";
		break;
		case "Step_E4_3":
			dialog.text = StringFromKey("Villemstad_Usurer_28");
			link.l1 = StringFromKey("Villemstad_Usurer_29", pchar);
			link.l1.go = "agree_to_pay";
			link.l2 = StringFromKey("Villemstad_Usurer_30");
			link.l2.go = "no_money_now";
			link.l3 = StringFromKey("Villemstad_Usurer_31");
			link.l3.go = "fack_yozef";
		break;
		case "agree_to_pay":
			if (sti(pchar.money) >= 100000)
			{
				dialog.text = StringFromKey("Villemstad_Usurer_32");
				link.l1 = StringFromKey("Villemstad_Usurer_33");
				link.l1.go = "exit";
				AddMoneyToCharacter(pchar, -100000);
				AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "3");
				pchar.questTemp.State = "Intelligence_Curacao_GaveMoneyYozef"; // заглушка на повторный вывод данного пункта в меню.
				RemoveLandQuestmark_Main(npchar, "Eng_Line");
				Pchar.quest.Intelligence_Curacao_GoToShore.win_condition.l1 = "location";
				Pchar.quest.Intelligence_Curacao_GoToShore.win_condition.l1.location = "Curacao";
				Pchar.quest.Intelligence_Curacao_GoToShore.win_condition = "Intelligence_Curacao_GoToShore";
				Log_QuestInfo("Корвет установлен в бухте.");
			}
			else
			{
				dialog.text = StringFromKey("Villemstad_Usurer_34");
				link.l1 = StringFromKey("Villemstad_Usurer_35", pchar);
				link.l1.go = "exit";
				pchar.questTemp.State = "Intelligence_Curacao_NoMoney_Yozef";
				//ChangeCharacterReputation(pchar, -1); TODO eddy
			}
		break;
		case "no_money_now":
			dialog.text = StringFromKey("Villemstad_Usurer_36");
			link.l1 = StringFromKey("Villemstad_Usurer_37");
			link.l1.go = "exit";
			if (pchar.questTemp.State != "Intelligence_Curacao_NoMoney_Yozef")
			{
				AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "4");
			}
			pchar.questTemp.State = "Intelligence_Curacao_NoMoney_Yozef";
		break;
		case "no_money":
			dialog.text = StringFromKey("Villemstad_Usurer_38");
			link.l1 = StringFromKey("Villemstad_Usurer_39", pchar);
			link.l1.go = "agree_to_pay";
			link.l2 = StringFromKey("Villemstad_Usurer_40");
			link.l2.go = "no_money_now";
			link.l3 = StringFromKey("Villemstad_Usurer_41");
			link.l3.go = "fack_yozef";
		break;
		case "fack_yozef":    // посыл Йозефа с попыткой замочить
			dialog.text = StringFromKey("Villemstad_Usurer_42", pchar);
			link.l1 = StringFromKey("Villemstad_Usurer_43");
			link.l1.go = "Step_E4_4";
		break;
		case "Step_E4_4":
			dialog.text = StringFromKey("Villemstad_Usurer_44", pchar);
			link.l1 = StringFromKey("Villemstad_Usurer_45");
			link.l1.go = "Step_E4_5";
		break;
		case "Step_E4_5":
			pchar.questTemp.State = "Intelligence_Curacao_FightGard";
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			AddLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
			LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_bank")], false);
			AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "5");
			AddQuestUserData("Eng_Line_4_Intelligence_Curacao", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Eng_Line_4_Intelligence_Curacao", "sSex1", GetSexPhrase("ся", "ась"));
			LAi_NoRebirthEnable(npchar);
			LAi_group_Register("EnemyFight");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			for (int i = 1; i <= 3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("HolSolder" + i, "urban_hol_" + i, "man", "man", 20, HOLLAND, 0, true));
				FantomMakeCoolFighter(sld, 20, 70, 60, BLADE_LONG, "pistol2", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "Villemstad_bank", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(pchar, 10, true, "Intelligence_Curacao_KickYozef");
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			Pchar.quest.Intelligence_Curacao_GoToShore.win_condition.l1 = "location";
			Pchar.quest.Intelligence_Curacao_GoToShore.win_condition.l1.location = "Curacao";
			Pchar.quest.Intelligence_Curacao_GoToShore.win_condition = "Intelligence_Curacao_GoToShore";
			DialogExit();
		break;
		//********************** Испанская линейка, квест №2 "Инквизиция" ************************
		case "Step_S2_1":
			dialog.text = StringFromKey("Villemstad_Usurer_46");
			link.l1 = StringFromKey("Villemstad_Usurer_47");
			link.l1.go = "Step_S2_2";
		break;
		case "Step_S2_2":
			dialog.text = StringFromKey("Villemstad_Usurer_48");
			link.l1 = StringFromKey("Villemstad_Usurer_49");
			link.l1.go = "Step_S2_3";
			link.l2 = StringFromKey("Villemstad_Usurer_50");
			link.l2.go = "Step_S2_4";
		break;
		case "Step_S2_3":
			dialog.text = StringFromKey("Villemstad_Usurer_51");
			link.l1 = StringFromKey("Villemstad_Usurer_52");
			link.l1.go = "Step_S2_fihgt";
		break;
		case "Step_S2_fihgt":
			bDisableFastReload = false;
			AddQuestRecord("Spa_Line_2_Inquisition", "4");
			LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_bank")], false);
			LAi_NoRebirthEnable(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(npchar);
			LAi_ActorAfraid(npchar, pchar, false);
			sld = GetCharacter(NPC_GenerateCharacter("Andrew", "shipowner_7", "man", "man", 35, HOLLAND, 10, true));
			FantomMakeCoolFighter(sld, 35, 80, 60, BLADE_LONG, "pistol3", 70);
			LAi_SetWarriorType(sld);
			LAi_NoRebirthEnable(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, "Villemstad_bank", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			Pchar.quest.Inquisition_afterFightAndrew.win_condition.l1 = "MapEnter";
			Pchar.quest.Inquisition_afterFightAndrew.win_condition = "Inquisition_afterFightAndrew";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;
		case "Step_S2_4":
			dialog.text = StringFromKey("Villemstad_Usurer_53", pchar);
			link.l1 = StringFromKey("Villemstad_Usurer_54");
			link.l1.go = "exit";
			AddQuestRecord("Spa_Line_2_Inquisition", "5");
			pchar.questTemp.State.Usurer = 1;
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("Villemstad_waitress"), "Spa_Line");
		break;
		case "Step_S2_5":
			dialog.text = StringFromKey("Villemstad_Usurer_55");
			link.l1 = StringFromKey("Villemstad_Usurer_56");
			link.l1.go = "Step_S2_6";
		break;
		case "Step_S2_6":
			dialog.text = StringFromKey("Villemstad_Usurer_57");
			link.l1 = StringFromKey("Villemstad_Usurer_58");
			link.l1.go = "Step_S2_7";
		break;
		case "Step_S2_7":
			dialog.text = StringFromKey("Villemstad_Usurer_59");
			link.l1 = StringFromKey("Villemstad_Usurer_60");
			link.l1.go = "Step_S2_8";
		break;
		case "Step_S2_8":
			AddQuestRecord("Spa_Line_2_Inquisition", "10");
			ReleasePrisoner(characterFromId("JansenDeFonceicao"));
			AddMoneyToCharacter(pchar, 50000);
			pchar.questTemp.State.Usurer = "Ok"; //бабки получены
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;
		//********************** Пиратская линейка, квест №5 ОГЗ ************************
		case "Step_P5_1":
			dialog.text = StringFromKey("Villemstad_Usurer_61", pchar);
			link.l1 = StringFromKey("Villemstad_Usurer_62");
			link.l1.go = "Step_P5_2";
		break;
		case "Step_P5_2":
			dialog.text = StringFromKey("Villemstad_Usurer_63", pchar);
			link.l1 = StringFromKey("Villemstad_Usurer_64");
			link.l1.go = "Step_P5_3";
		break;
		case "Step_P5_3":
			pchar.questTemp.piratesLine.Q5.city_1 = GetQuestNationsCity(ENGLAND);
			dialog.text = StringFromKey("Villemstad_Usurer_65", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_1 + "Pre"));
			link.l1 = StringFromKey("Villemstad_Usurer_66");
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "2");
			AddQuestUserData("Pir_Line_5_Hunter", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_1));
			AddQuestUserData("Pir_Line_5_Hunter", "sIsland", XI_ConvertString(GetIslandNameByCity(pchar.questTemp.piratesLine.Q5.city_1) + "Pre"));
			pchar.questTemp.piratesLine = "PL5Hunter_toFirst";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.piratesLine.Q5.city_1 + "_usurer"), "Pir_Line");
			AddLandQuestMarkToFantoms_Main("habitue", "Pir_Line", "PL5Hunter_toFirst_Habitues_QuestMarkCondition");
		break;
		
		// ==> Эммануэль Пардаль: Портниха знатной дамы
		case "EPL_PZD_Rost_1":
    		dialog.text = StringFromKey("Villemstad_Usurer_68");
    		link.l1 = StringFromKey("Villemstad_Usurer_69");
    		link.l1.go = "EPL_PZD_Rost_2";
			RemoveLandQuestmark_Main(CharacterFromID("Villemstad_usurer"), "EPL_PZD");
 		break;
		case "EPL_PZD_Rost_2":
    		dialog.text = StringFromKey("Villemstad_Usurer_70");
    		link.l1 = StringFromKey("Villemstad_Usurer_71");
    		link.l1.go = "EPL_PZD_Rost_3";
 		break;
		case "EPL_PZD_Rost_3":
    		dialog.text = StringFromKey("Villemstad_Usurer_72");
    		link.l1 = StringFromKey("Villemstad_Usurer_73");
    		link.l1.go = "exit";
 		break;
		// <== Эммануэль Пардаль: Портниха знатной дамы
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


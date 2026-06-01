// Блад
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLocator, sTemp;
	int iTime, n, iChar;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit_Away":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", Pchar.questTemp.sLocator, "none", "", "", "", sti(Pchar.questTemp.iTime));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit_RunAway":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", Pchar.questTemp.sLocator, "none", "", "", "", sti(Pchar.questTemp.iTime));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "sfight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "fight":
			Lai_MethodDelay("ExitNoHideBlade", 0.35); //HardCoffee
			//AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetWarriorTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			chrDisableReloadToLocation = false;
			PlaySpeech(npchar, "toArm");
			if (NPChar.id == "SolderTakeBlades") break; //На случай, если вместо скриптового нпс к гг обратился другой нпс
			iChar = GetCharacterIndex("SolderTakeBlades");
			if (iChar < 0) break;
			sld = &characters[iChar];
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_Attack(sld, Pchar);
		break;

		case "Qfight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetWarriorType(NPChar);
			LAi_group_MoveCharacter(NPChar, "TmpEnemy");
			LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
			LAi_group_FightGroups(GetNationNameByType(ENGLAND) + "_citizens", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			chrDisableReloadToLocation = true;
		break;

		case "Finish":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			RestoreBridgetown();
			CincoLlagasCapture();
			DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
		break;

		case "Man_FackYou":
			dialog.text = StringFromKey("questNPC_4", LinkRandPhrase(
						StringFromKey("questNPC_1"),
						StringFromKey("questNPC_2"),
						StringFromKey("questNPC_3")));
			link.l1 = StringFromKey("questNPC_8", LinkRandPhrase(
						StringFromKey("questNPC_5"),
						StringFromKey("questNPC_6"),
						StringFromKey("questNPC_7")));
			link.l1.go = "Qfight";
		break;

		case "Draguns_0":
			dialog.text = StringFromKey("questNPC_12", LinkRandPhrase(
						StringFromKey("questNPC_9"),
						StringFromKey("questNPC_10"),
						StringFromKey("questNPC_11")));
			link.l1 = StringFromKey("questNPC_16", LinkRandPhrase(
						StringFromKey("questNPC_13"),
						StringFromKey("questNPC_14"),
						StringFromKey("questNPC_15")));
			link.l1.go = "Draguns_1";
			NextDiag.TempNode = "Draguns_0";
		break;

		case "Draguns_1":
			LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = StringFromKey("questNPC_17");
			link.l1 = "...";
			link.l1.go = "Exit";

			if (CheckAttribute(npchar, "CityType") && npchar.CityType == "soldier")
			{
				if (Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape2_1")
				{
					dialog.text = StringFromKey("questNPC_18");
					link.l1 = StringFromKey("questNPC_19");
					link.l1.go = "SQStep_0";
					Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape2_2";
					break;
				}
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY || GetCharacterReputation_WithNation(pchar, sti(NPChar.nation)) <= -15)
				{
					dialog.text = StringFromKey("questNPC_22", RandPhraseSimple(
								StringFromKey("questNPC_20"),
								StringFromKey("questNPC_21")));
					link.l1 = StringFromKey("questNPC_25", RandPhraseSimple(
								StringFromKey("questNPC_23"),
								StringFromKey("questNPC_24")));
					link.l1.go = "sfight";
					break;
				}
				switch (rand(5))
				{
					case 0: ////////////////////////////////////////
						dialog.text = StringFromKey("questNPC_26");
						link.l1 = StringFromKey("questNPC_27");
						link.l1.go = "exit";
					break;

					case 1:
						dialog.text = StringFromKey("questNPC_28");
						link.l1 = StringFromKey("questNPC_29");
						link.l1.go = "exit";
					break;

					case 2: ///////////////////////////////////////////
						dialog.text = StringFromKey("questNPC_30");
						link.l1 = StringFromKey("questNPC_31");
						link.l1.go = "exit";
					break;

					case 3:
						dialog.text = StringFromKey("questNPC_32");
						link.l1 = StringFromKey("questNPC_33");
						link.l1.go = "exit";
					break;

					case 4: ///////////////////////////////////////////
						dialog.text = StringFromKey("questNPC_34");
						link.l1 = StringFromKey("questNPC_35");
						link.l1.go = "exit";
					break;

					case 5: ////////////////////////////////////////////
						dialog.text = StringFromKey("questNPC_36");
						link.l1 = StringFromKey("questNPC_37");
						link.l1.go = "exit";
					break;
				}
			}

			if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen")
			{
				dialog.text = StringFromKey("questNPC_38", TimeGreeting());
				link.l1 = StringFromKey("questNPC_39");
				link.l1.go = "Exit";
				if (Pchar.questTemp.CapBloodLine.stat == "WakerOffer")
				{
					link.l2 = StringFromKey("questNPC_42", RandPhraseSimple(
								StringFromKey("questNPC_40"),
								StringFromKey("questNPC_41")));
					link.l2.go = "Citizen_0";
				}
				if (CheckAttribute(Pchar, "questTemp.CapBloodLine.ShipForJack") && Pchar.questTemp.CapBloodLine.ShipForJack == true)
				{
					Link.l2 = StringFromKey("questNPC_45", RandPhraseSimple(
								StringFromKey("questNPC_43"),
								StringFromKey("questNPC_44")));
					Link.l2.go = "Citizen_1";
				}
			}

			if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && npchar.location.group == "merchant")
			{
				if (or(Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape",
				Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape1"))
				{
					if (CheckAttribute(npchar, "quest.bGoodMerch") && sti(Pchar.reputation) >= 55)
					{
						PlayerRPGCheck_Reputation_NotifyPass(false, true);
						dialog.text = StringFromKey("questNPC_46", npchar);
						link.l1 = StringFromKey("questNPC_47", npchar);
						link.l1.go = "Merchant_0";
						break;
					}
				}
				if (CheckAttribute(npchar, "quest.bGoodMerch"))
				{
					dialog.text = StringFromKey("questNPC_48", TimeGreeting());
					link.l1 = StringFromKey("questNPC_49");
				}
				else
				{
					dialog.text = StringFromKey("questNPC_50");
					link.l1 = StringFromKey("questNPC_51");
				}
				link.l1.go = "Exit";
			}
			//Рабы на плантациях - постоянный диалог
			if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && HasSubStr(npchar.id, "Slave_"))
			{
				dialog.text = StringFromKey("questNPC_58", RandPhraseSimple(
							StringFromKey("questNPC_54", RandPhraseSimple(
									StringFromKey("questNPC_52"),
									StringFromKey("questNPC_53"))),
							StringFromKey("questNPC_57", RandPhraseSimple(
									StringFromKey("questNPC_55"),
									StringFromKey("questNPC_56")))));
				if (CheckAttribute(pchar, "GenQuest.CaptainComission") && pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
				{
					link.l1 = StringFromKey("questNPC_61", RandPhraseSimple(
								StringFromKey("questNPC_59", pchar.GenQuest.CaptainComission.SlaveName),
								StringFromKey("questNPC_60", pchar.GenQuest.CaptainComission.SlaveName)));
					link.l1.go = "CapComission_1";
				}
				else
				{
					link.l1 = StringFromKey("questNPC_64", RandPhraseSimple(
								StringFromKey("questNPC_62"),
								StringFromKey("questNPC_63")));
					link.l1.go = "exit";
				}
			}

			if (npchar.id == "Bridgetown_Poorman")
			{
				dialog.text = StringFromKey("questNPC_65");
				link.l1 = StringFromKey("questNPC_66");
				link.l1.go = "Exit";
			}

			if (npchar.id == "QuestCitiz_Bridgetown")
			{
				dialog.text = StringFromKey("questNPC_67", TimeGreeting());
				link.l1 = StringFromKey("questNPC_68");
				link.l1.go = "Exit";
			}

			if (npchar.id == "SolderTakeBlades")
			{
				dialog.text = StringFromKey("questNPC_71", RandPhraseSimple(
							StringFromKey("questNPC_69"),
							StringFromKey("questNPC_70")));
				link.l1 = StringFromKey("questNPC_74", RandPhraseSimple(
							StringFromKey("questNPC_72"),
							StringFromKey("questNPC_73")));
				link.l1.go = "STBStep_0";
			}

			if (npchar.id == "Winterwood")
			{
				if (npchar.location == "Bridgetown_Brothel_room")
				{
					dialog.text = StringFromKey("questNPC_75");
					link.l1 = StringFromKey("questNPC_76");
					link.l1.go = "WWStep_7";
					break;
				}
				dialog.text = StringFromKey("questNPC_77");
				link.l1 = StringFromKey("questNPC_78");
				link.l1.go = "WWStep_0";
			}

			if (npchar.id == "Quest_Habitue")
			{
				dialog.text = StringFromKey("questNPC_79");
				link.l1 = StringFromKey("questNPC_80");
				link.l1.go = "exit";
			}

			if (npchar.id == "Weston")
			{
				dialog.text = StringFromKey("questNPC_81");
				link.l1 = StringFromKey("questNPC_82");
				link.l1.go = "exit";
			}

			if (npchar.id == "MoneySpy")
			{
				if (npchar.quest.meeting == "1")
				{
					dialog.text = StringFromKey("questNPC_83");
					link.l1 = StringFromKey("questNPC_84");
					link.l1.go = "exit";
				}
				else
				{
					npchar.quest.meeting = "1";
					dialog.text = StringFromKey("questNPC_85");
					link.l1 = StringFromKey("questNPC_86");
					link.l1.go = "MSStep_1";
					link.l2 = StringFromKey("questNPC_87");
					link.l2.go = "MSStep_0";
					AddDialogExitQuestFunction("CapBloodLine_NeedMoney_MoneySpy_DelQuestMarks");
				}
			}

			if (npchar.id == "Fisherman")
			{
				dialog.text = StringFromKey("questNPC_88");
				link.l1 = StringFromKey("questNPC_89");
				link.l1.go = "exit";
			}

			if (npchar.id == "QStranger")
			{
				dialog.text = StringFromKey("questNPC_90");
				link.l1 = StringFromKey("questNPC_91");
				link.l1.go = "QSTStep_0";
				link.l2 = StringFromKey("questNPC_92");
				link.l2.go = "QSTStep_2";
				if (PlayerRPGCheck_SPECIAL(SPECIAL_C, 6) && PlayerRPGCheck_SPECIAL(SPECIAL_S, 8))
				{
					link.l3 = StringFromKey("questNPC_93");
					link.l3.go = "QSTStep_1";
				}
			}
		break;

		case "CapComission_1":
			dialog.text = StringFromKey("questNPC_94");
			link.l1 = StringFromKey("questNPC_95");
			link.l1.go = "exit";
		break;

		case "Citizen_0":
			if (!CheckAttribute(npchar, "quest.btmp"))
			{
				npchar.quest.btmp = true;
				if (rand(3) == 2)
				{
					dialog.text = StringFromKey("questNPC_99", LinkRandPhrase(
								StringFromKey("questNPC_96"),
								StringFromKey("questNPC_97"),
								StringFromKey("questNPC_98")));
					link.l1 = StringFromKey("questNPC_100");
					link.l1.go = "Exit";
				}
				else
				{
					dialog.text = StringFromKey("questNPC_107", RandPhraseSimple(
								StringFromKey("questNPC_103", RandPhraseSimple(
										StringFromKey("questNPC_101"),
										StringFromKey("questNPC_102"))),
								StringFromKey("questNPC_106", RandPhraseSimple(
										StringFromKey("questNPC_104"),
										StringFromKey("questNPC_105")))));
					link.l1 = StringFromKey("questNPC_108");
					link.l1.go = "Exit";
				}
			}
			else
			{
				dialog.text = StringFromKey("questNPC_109");
				link.l1 = StringFromKey("questNPC_110");
				link.l1.go = "Exit";
			}
		break;

		case "Citizen_1":
			dialog.text = StringFromKey("questNPC_114", LinkRandPhrase(
						StringFromKey("questNPC_111"),
						StringFromKey("questNPC_112"),
						StringFromKey("questNPC_113")));
			link.l1 = StringFromKey("questNPC_115");
			link.l1.go = "Exit";
		break;

		case "Merchant_0":
			dialog.text = StringFromKey("questNPC_116");
			link.l1 = StringFromKey("questNPC_117");
			link.l1.go = "Merchant_1";
		break;

		case "Merchant_1":
			dialog.text = StringFromKey("questNPC_118");
			link.l1 = StringFromKey("questNPC_119");
			link.l1.go = "Exit";
			NextDiag.TempNode = "Merchant_2";
			if (Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape")
			{
				Pchar.questTemp.CapBloodLine.stat = "ReadyToEscape"; //fix чтоб не сбивать уже начатые варианты
				RemoveLandQuestmark_Main(CharacterFromID("Bridgetown_tavernkeeper"), "CapBloodLine");
				RemoveLandQuestmark_Main(CharacterFromID("Quest_Smuggler"), "CapBloodLine");
				RemoveLandQuestmark_Main(CharacterFromID("Griffin"), "CapBloodLine");
			}
			GiveItem2Character(Pchar, "Weapon_for_escape");
			AddQuestRecord("WeaponsForEscape", "10");
			CloseQuestHeader("WeaponsForEscape");

			RemoveLandQuestmarkToFantoms_Main("ItemTrader", "CapBloodLine");
			QuestPointerDelLoc("Bridgetown_town", "reload", "HouseSp2");
			QuestPointerDelLocEx("Bridgetown_town", "reload", "reload4_back", "BloodLine_WeaponsForEscape");
		break;

		case "Merchant_2":
			dialog.text = StringFromKey("questNPC_120");
			link.l1 = StringFromKey("questNPC_121");
			link.l1.go = "Exit";
			NextDiag.TempNode = "Merchant_2";
		break;

		// ==> Забираем клинки, пистоли.
		case "STBStep_0":
			dialog.text = StringFromKey("questNPC_122");
			link.l1 = StringFromKey("questNPC_123");
			link.l1.go = "STBStep_1";
			link.l2 = StringFromKey("questNPC_124");
			link.l2.go = "fight";
		break;

		case "STBStep_1":
			dialog.text = StringFromKey("questNPC_125");
			link.l1.go = "Exit_Away";
			Pchar.questTemp.sLocator = FindLocatorForSolderTakeBlades(NPChar);
			Pchar.questTemp.iTime = 40;
			BloodWithdrawWeapon();
			chrDisableReloadToLocation = false;
		break;
		//замечение по обнаженному оружию HardCoffee ref
		case "SoldierNotBlade":
			if (Pchar.questTemp.CapBUnarmed == false)
			{
				dialog.text = StringFromKey("questNPC_129", LinkRandPhrase(
							StringFromKey("questNPC_126"),
							StringFromKey("questNPC_127"),
							StringFromKey("questNPC_128")));
				link.l1 = StringFromKey("questNPC_133", LinkRandPhrase(
							StringFromKey("questNPC_130"),
							StringFromKey("questNPC_131"),
							StringFromKey("questNPC_132")));
				link.l1.go = "exit_HideBlade";
				link.l2 = StringFromKey("questNPC_137", LinkRandPhrase(
							StringFromKey("questNPC_134"),
							StringFromKey("questNPC_135"),
							StringFromKey("questNPC_136")));
				link.l2.go = "fight";
			}
			else
			{
				dialog.text = StringFromKey("questNPC_140", RandPhraseSimple(
							StringFromKey("questNPC_138"),
							StringFromKey("questNPC_139")));
				link.l1 = StringFromKey("questNPC_141");
				link.l1.go = "SoldierNotBladeEx";
				link.l2 = StringFromKey("questNPC_142");
				link.l2.go = "fight";
			}
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;

		case "exit_HideBlade":
			Lai_MethodDelay("ExitHideBlade", 0.35);
			NPChar.Dialog.CurrentNode = NPChar.Dialog.TempNode;
			DialogExit();
		break;

		case "SoldierNotBladeEx":
			dialog.text = StringFromKey("questNPC_143");
			link.l1.go = "Exit";
			BloodWithdrawWeapon();
		break;

		case "NStep_7":
			dialog.text = StringFromKey("questNPC_144");
			link.l1 = StringFromKey("questNPC_145");
			link.l1.go = "Exit_Away";
			Pchar.questTemp.sLocator = "gate1_back";
			Pchar.questTemp.iTime = -1;

			chrDisableReloadToLocation = false;
			pchar.quest.CapBloodEscape2.win_condition.l1 = "location";
			pchar.quest.CapBloodEscape2.win_condition.l1.location = "Bridgetown_Plantation";
			pchar.quest.CapBloodEscape2.function = "ReturnToPlantation2";

			sld = characterFromID("Hugtorp");
			sld.Dialog.CurrentNode = "HTStep_14";
			ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "goto", "goto18");
			QuestPointerToLoc("Bridgetown_town", "reload", "gate1_back");
		break;
		// --> Квестовый солдат
		case "SQStep_0":
			dialog.text = StringFromKey("questNPC_146");
			link.l1 = StringFromKey("questNPC_147");
			link.l1.go = "SQStep_1";
		break;

		case "SQStep_1":
			dialog.text = StringFromKey("questNPC_148");
			link.l1 = StringFromKey("questNPC_149");
			link.l1.go = "Exit_RunAway";
			Pchar.questTemp.sLocator = "houseSp2";
			Pchar.questTemp.iTime = 20;

			string smodel = NPChar.model;
			if (HasSubStr(smodel, "eng_mush")) smodel = "sold_eng_" + (rand(7) + 1);
			sld = GetCharacter(NPC_GenerateCharacter("CPBQuest_Solder", smodel, "man", "man", 10, ENGLAND, 1, false)); //watch_quest_moment
			sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
			SetFantomParamHunter(sld); //крутые парни
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true;
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorSetLayMode(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "CommonFlamHouse", "reload", "reload3");

			sld = &characters[GetCharacterIndex("Griffin")];
			ChangeCharacterAddressGroup(sld, "CommonRoom_MH4", "barmen", "bar1");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorTurnToLocator(sld, "goto", "goto2");
			LAi_SetStayTypeNoGroup(sld);
			sld = &characters[GetCharacterIndex("Spain_spy")];
			ChangeCharacterAddressGroup(sld, "CommonRoom_MH4", "goto", "goto2");
			sld.dialog.currentnode = "SSStep_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);

			pchar.quest.PrepareToEscape2_3.win_condition.l1 = "location";
			pchar.quest.PrepareToEscape2_3.win_condition.l1.location = "CommonFlamHouse";
			pchar.quest.PrepareToEscape2_3.function = "_DeadSolder";

			Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape2_3";
			DoQuestFunctionDelay("SpainSpyAttack", 20.0);
			AddDialogExitQuestFunction("CapBloodLine_SpainSpy_DelQuestMarks");
		break;

		// --> Квестовый раб Сандро Торн
		case "SLQStep_0":

			dialog.text = StringFromKey("questNPC_150");
			if (GetCharacterItem(pchar, "migraine_potion") > 0)
			{
				link.l0 = StringFromKey("questNPC_151");
				link.l0.go = "SLQStep_3";
			}
			link.l1 = StringFromKey("questNPC_152");
			link.l1.go = "SLQStep_1";

		break;

		case "SLQStep_1":
			dialog.text = StringFromKey("questNPC_153");
			link.l1 = StringFromKey("questNPC_154");
			link.l1.go = "Exit";
			NextDiag.TempNode = "SLQStep_2";
		break;

		case "SLQStep_2":
			dialog.text = StringFromKey("questNPC_155");
			if (GetCharacterItem(pchar, "migraine_potion") > 0)
			{
				link.l1 = StringFromKey("questNPC_156");
				link.l1.go = "SLQStep_3";
				link.l2 = StringFromKey("questNPC_157");
				link.l2.go = "Exit";
			}
			else
			{
				link.l1 = StringFromKey("questNPC_158");
				link.l1.go = "Exit";
			}
			NextDiag.TempNode = "SLQStep_2";
		break;

		case "SLQStep_3":
			dialog.text = StringFromKey("questNPC_159");
			link.l1 = StringFromKey("questNPC_160");
			link.l1.go = "SLQStep_4";
			TakeItemFromCharacter(Pchar, "migraine_potion");
			GiveItem2Character(Pchar, GetGeneratedItem("blade5"));
		break;

		case "SLQStep_4":
			dialog.text = StringFromKey("questNPC_161");
			link.l1 = StringFromKey("questNPC_162");
			link.l1.go = "Exit";
			DeleteAttribute(npchar, "talker"); //снимаем говорилку
			NextDiag.TempNode = "First time";
		break;

		// --> Уинтервуд

		case "WWStep_0":
			dialog.text = StringFromKey("questNPC_163");
			link.l1 = StringFromKey("questNPC_164");
			link.l1.go = "WWStep_1";
		break;

		case "WWStep_1":
			dialog.text = StringFromKey("questNPC_165");
			link.l1 = StringFromKey("questNPC_166");
			link.l1.go = "WWStep_2";
		break;

		case "WWStep_2":
			dialog.text = StringFromKey("questNPC_167");
			link.l1 = StringFromKey("questNPC_168");
			link.l1.go = "WWStep_3";
		break;

		case "WWStep_3":
			Dialog.Text = StringFromKey("questNPC_169");
			link.l1 = StringFromKey("questNPC_170");
			link.l1.go = "WWStep_4";
			AddQuestRecord("HugtorpTrouble", "3");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
		break;

		//что ж, пойдём выйдем
		case "WWStep_4":
			PChar.quest.CapBloodLineTimer_3.win_condition.l1 = "Timer";
			PChar.quest.CapBloodLineTimer_3.win_condition.l1.date.hour = sti(GetTime() + 1);
			PChar.quest.CapBloodLineTimer_3.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.CapBloodLineTimer_3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.CapBloodLineTimer_3.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.CapBloodLineTimer_3.function = "WinterwoodDuel";

			// опция скипа времени, если завершены все квесты
			SetFunctionLocationCondition("CapBloodLine_WinterwoodSkipTime", "Bridgetown_town", true);

			NextDiag.CurrentNode = "WWStep_5";
			DialogExit();
		break;

		case "WWStep_5":
			Dialog.Text = StringFromKey("questNPC_171");
			link.l1 = StringFromKey("questNPC_172");
			link.l1.go = "WWStep_5_1";
			link.l2 = StringFromKey("questNPC_173");
			link.l2.go = "Exit";
			NextDiag.TempNode = "WWStep_5";
		break;

		case "WWStep_5_1":
			Dialog.Text = StringFromKey("questNPC_174");
			link.l1 = StringFromKey("questNPC_175");
			link.l1.go = "WWStep_6";
		break;

		case "talk_off_town":
			Dialog.Text = StringFromKey("questNPC_176");
			link.l1 = StringFromKey("questNPC_177");
			link.l1.go = "WWStep_6";
			GiveItem2Character(Pchar, "blade2");
			EquipCharacterByItem(Pchar, "blade2");
			chrDisableReloadToLocation = false;
		break;

		//дуэли быть!
		case "WWStep_6":
			AddDialogExitQuestFunction("Winterwood_Prepare_Fight");
			AddDialogExitQuestFunction("Tutorial_BloodPrologue_StartBarbadosFightTutorials_OnDialogExit");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "WWStep_7":
			dialog.text = StringFromKey("questNPC_178");
			link.l1 = StringFromKey("questNPC_179");
			link.l1.go = "WWStep_8";
		break;

		case "WWStep_8":
			dialog.text = StringFromKey("questNPC_180");
			link.l1 = StringFromKey("questNPC_181");
			link.l1.go = "WWStep_3";
			n = FindLocation("Bridgetown_Brothel");
			locations[n].reload.l2.disable = true;
		break;

		// --> Алкаш

		case "QHStep_0":
			dialog.text = StringFromKey("questNPC_182");
			link.l1 = StringFromKey("questNPC_183");
			link.l1.go = "exit";
			link.l2 = StringFromKey("questNPC_184");
			link.l2.go = "QHStep_1";
			NextDiag.TempNode = "QHStep_0";
		break;

		case "QHStep_1":
			NextDiag.TempNode = "begin_sit";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "begin_sit":
			NextDiag.TempNode = "first time";
			dialog.text = StringFromKey("questNPC_185");
			link.l1 = StringFromKey("questNPC_186");
			link.l1.go = "QHStep_2";
		break;

		case "QHStep_2":
			WaitDate("", 0, 0, 0, 0, 30);
			dialog.text = StringFromKey("questNPC_190", LinkRandPhrase(
						StringFromKey("questNPC_187"),
						StringFromKey("questNPC_188"),
						StringFromKey("questNPC_189")));
			link.l1 = StringFromKey("questNPC_191");
			link.l1.go = "QHStep_3";
		break;

		case "QHStep_3":
			dialog.text = StringFromKey("questNPC_192");
			link.l1 = StringFromKey("questNPC_193");
			link.l1.go = "exit_sit";
			NextDiag.TempNode = "First time";

			if (CheckNationLicence(ENGLAND)) TakeNationLicence(ENGLAND);
			sTemp = NationShortName(ENGLAND) + "TradeLicence";
			ref rItem = ItemsFromID(sTemp);
			SaveCurrentNpcQuestDateParam(rItem, "Action_date");
			rItem.Action_date = GetCurrentDate();
			rItem.Validity = FindDaysString(60);
			rItem.Validity.QtyDays = 60;

			// pchar.GenQuestBox.CommonStoneHouse = true;
			// pchar.GenQuestBox.CommonStoneHouse.stay = true;

			n = FindLocation("CommonStoneHouse");
			locations[n].models.day.locators = "StoneHouse_lPrivate"; // homo for CapBloodLine
			locations[n].models.night.locators = "StoneHouse_lPrivateN";
			// Перенесли в тайник
			//			locations[n].private1.items.indian1 = 1;
			//			locations[n].private1.items.EngTradeLicence = 1;
			//			locations[n].private1.money = 7500;
			// <--

			//Чарльз Вестон
			sld = GetCharacter(NPC_GenerateCharacter("Weston", "trader_3", "man", "man", 10, ENGLAND, 1, false));
			sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
			sld.name = FindPersonalName("Weston_name");
			sld.lastname = FindPersonalName("Weston_lastname");
			sld.greeting = "Gr_bankeer";
			FantomMakeCoolFighter(sld, 7, 100, 50, "topor2", "", 10);
			LAi_SetImmortal(sld, true);
			sTemp = GetNationNameByType(ENGLAND) + "_citizens";
			LAi_group_MoveCharacter(sld, sTemp);
			LAi_SetOwnerTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "CommonStoneHouse", "barmen", "stay");

			pchar.quest.MoneyForDieke.win_condition.l1 = "item";
			pchar.quest.MoneyForDieke.win_condition.l1.item = "EngTradeLicence";
			pchar.quest.MoneyForDieke.function = "MoneyForDieke";
			AddQuestRecord("DiekeQuest", "3");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			QuestPointerToLoc("Bridgetown_town", "reload", "houseS3");
			QuestPointerDelLocEx("Bridgetown_town", "reload", "reload4_back", "DiekeQuest");
			// туториал - тайники
			pchar.quest.BloodPrologueTutorial_Stashes.win_condition.l1 = "location";
			pchar.quest.BloodPrologueTutorial_Stashes.win_condition.l1.location = "CommonStoneHouse";
			pchar.quest.BloodPrologueTutorial_Stashes.function = "Tutorial_BloodPrologue_StashesDelay";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;

		//Шпион

		case "MSStep_0":
			dialog.text = StringFromKey("questNPC_194");
			link.l1 = "";
			link.l1.go = "Exit";
		break;

		case "MSStep_1":
			dialog.text = StringFromKey("questNPC_195");
			link.l1 = StringFromKey("questNPC_196");
			link.l1.go = "MSStep_2";
			link.l2 = StringFromKey("questNPC_197");
			link.l2.go = "MSStep_3";
			link.l3 = StringFromKey("questNPC_198");
			link.l3.go = "MSStep_4";
		break;

		case "MSStep_2":
			dialog.text = StringFromKey("questNPC_199");
			link.l1 = "...";
			link.l1.go = "exit";
		break;

		case "MSStep_3":
			dialog.text = StringFromKey("questNPC_200");
			link.l1 = StringFromKey("questNPC_201");
			link.l1.go = "MSStep_5";
			link.l2 = StringFromKey("questNPC_202");
			link.l2.go = "MSStep_6";
		break;

		case "MSStep_4":
			dialog.text = StringFromKey("questNPC_203");
			link.l1 = "...";
			link.l1.go = "exit";
		break;

		case "MSStep_5":
			dialog.text = StringFromKey("questNPC_204");
			link.l1 = StringFromKey("questNPC_205");
			link.l1.go = "MSStep_7";
			link.l2 = StringFromKey("questNPC_206");
			link.l2.go = "MSStep_8";
		break;

		case "MSStep_6":
			dialog.text = StringFromKey("questNPC_207");
			link.l1 = "...";
			link.l1.go = "exit";
		break;

		case "MSStep_7":
			dialog.text = StringFromKey("questNPC_208");
			link.l1 = "...";
			link.l1.go = "exit";
		break;

		case "MSStep_8":
			dialog.text = StringFromKey("questNPC_209");
			link.l1 = StringFromKey("questNPC_210");
			link.l1.go = "MSStep_9";
			link.l2 = StringFromKey("questNPC_211");
			link.l2.go = "MSStep_10";
			link.l3 = StringFromKey("questNPC_212");
			link.l3.go = "MSStep_11";
		break;

		case "MSStep_9":
			dialog.text = StringFromKey("questNPC_213");
			link.l1 = "...";
			link.l1.go = "exit";
		break;

		case "MSStep_10":
			dialog.text = StringFromKey("questNPC_214");
			link.l1 = "...";
			link.l1.go = "exit";
		break;

		case "MSStep_11":
			dialog.text = StringFromKey("questNPC_215");
			link.l1 = StringFromKey("questNPC_216");
			link.l1.go = "MSStep_12";
			link.l2 = StringFromKey("questNPC_217");
			link.l2.go = "MSStep_13";
			link.l3 = StringFromKey("questNPC_218");
			link.l3.go = "MSStep_14";
		break;

		case "MSStep_12":
			dialog.text = StringFromKey("questNPC_219");
			link.l1 = "...";
			link.l1.go = "exit";
		break;

		case "MSStep_13":
			dialog.text = StringFromKey("questNPC_220");
			link.l1 = "...";
			link.l1.go = "exit";
		break;

		case "MSStep_14":
			dialog.text = StringFromKey("questNPC_221");
			link.l1 = "...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 1000);
			AddCharacterExpToSkill(pchar, "Sneak", 80);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			if (CapBloodLine_CheckMoneyForNettl())
				QuestPointerToLocEx("Bridgetown_town", "reload", "reload4_back", "CapBloodLine_q2");
		break;

		case "FStep_1":
			dialog.text = StringFromKey("questNPC_222");
			if (makeint(Pchar.money) >= 4)
			{
				link.l1 = StringFromKey("questNPC_223");
				link.l1.go = "FStep_1_2";
			}
			link.l2 = StringFromKey("questNPC_224");
			link.l2.go = "FStep_1_3";
		break;

		case "FStep_1_2":
			NextDiag.TempNode = "FStep_2";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "FStep_1_3":
			NextDiag.TempNode = "FStep_3";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "FStep_2":
			AddMoneyToCharacter(pchar, -2);
			dialog.text = StringFromKey("questNPC_225");
			link.l1 = StringFromKey("questNPC_226");
			link.l1.go = "FStep_4";
		break;

		case "FStep_3":
			dialog.text = StringFromKey("questNPC_227");
			link.l1 = StringFromKey("questNPC_228");
			link.l1.go = "FStep_5";
		break;

		case "FStep_4":
			AddMoneyToCharacter(pchar, -2);
			LAi_SetAlcoholState(1);
			dialog.text = StringFromKey("questNPC_229");
			link.l1 = StringFromKey("questNPC_230");
			link.l1.go = "FStep_6";
		break;

		case "FStep_5":
			LAi_SetAlcoholState(1);
			dialog.text = StringFromKey("questNPC_231");
			link.l1 = StringFromKey("questNPC_232");
			link.l1.go = "FStep_7";
		break;

		case "FStep_6":
			dialog.text = StringFromKey("questNPC_233");
			link.l1 = "...";
			link.l1.go = "FStep_8";
			link.l2 = StringFromKey("questNPC_234");
			link.l2.go = "FStep_Fail";
		break;

		case "FStep_7":
			dialog.text = StringFromKey("questNPC_235");
			link.l1 = "...";
			link.l1.go = "FStep_8";
			link.l2 = StringFromKey("questNPC_236");
			link.l2.go = "FStep_Fail";
		break;

		case "FStep_8":
			Pchar.questTemp.CapBloodLine.fishplace = XI_ConvertString("Shore5");
			dialog.text = StringFromKey("questNPC_237", Pchar.questTemp.CapBloodLine.fishplace);
			link.l1 = StringFromKey("questNPC_238");
			link.l1.go = "exit_sit";
			NextDiag.TempNode = "First time";
			AddQuestRecord("FishermanQuest", "2");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			QuestPointerDelLocEx("Bridgetown_town", "reload", "reload4_back", "BloodLine_FishermanQuest");
			AddLandQuestmark_Main(characterFromID("Hells"), "CapBloodLine");
			QuestPointerToLocEx("Bridgetown_town", "reload", "reload11_back", "BloodLine_FishermanQuest");
		break;

		case "FStep_Fail":
			dialog.text = StringFromKey("questNPC_239");
			link.l1 = StringFromKey("questNPC_240");
			link.l1.go = "exit_sit";
			NextDiag.TempNode = "First time";
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");

			QuestPointerDelLocEx("Bridgetown_town", "reload", "reload4_back", "BloodLine_FishermanQuest");
			sld = CharacterFromID("MoneySpy");
			if (sld.quest.meeting == 0)
				QuestPointerToLocEx("Bridgetown_town", "reload", "houseS1", "BloodLine_MoneySpy");
		break;

		case "QSTStep_0":
			dialog.text = StringFromKey("questNPC_241");
			link.l1 = StringFromKey("questNPC_242");
			link.l1.go = "Exit_Away";
			Pchar.questTemp.sLocator = "reload1_back";
			if (npchar.location == "Bridgetown_church") Pchar.questTemp.sLocator = "reload1_back";
			Pchar.questTemp.iTime = -1;
			AddQuestRecord("UsurerQuest", "5");
			CloseQuestHeader("UsurerQuest");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			QuestPointerDelLoc("Bridgetown_town", "reload", "reload7_back");
			QuestPointerDelLoc("Bridgetown_town", "reload", "reload5_back");
			if (CapBloodLine_NeedMoney_CheckHellsForQuest())
			{
				QuestPointerToLocEx("Bridgetown_town", "reload", "reload11_back", "BloodLine_FishermanQuest");
			}
			else
			{
				sld = CharacterFromID("MoneySpy");
				if (sld.quest.meeting == 0)
					QuestPointerToLocEx("Bridgetown_town", "reload", "houseS1", "BloodLine_MoneySpy");
			}
		break;

		case "QSTStep_1":
			dialog.text = StringFromKey("questNPC_243");
			link.l1 = StringFromKey("questNPC_244");
			link.l1.go = "QSTStep_3";
		break;

		case "QSTStep_2":
			dialog.text = StringFromKey("questNPC_245");
			link.l1 = StringFromKey("questNPC_246");
			link.l1.go = "QSTStep_6";
		break;

		case "QSTStep_3":
			dialog.text = StringFromKey("questNPC_247");
			link.l1 = StringFromKey("questNPC_248");
			link.l1.go = "QSTStep_4";
		break;

		case "QSTStep_4":
			dialog.text = StringFromKey("questNPC_249");
			link.l1 = StringFromKey("questNPC_250");
			link.l1.go = "QSTStep_5";
		break;

		case "QSTStep_5":
			PChar.quest.QUsurer.win_condition.l1 = "Timer";
			PChar.quest.QUsurer.win_condition.l1.date.hour = 0;
			PChar.quest.QUsurer.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			PChar.quest.QUsurer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.QUsurer.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.QUsurer.function = "QUsurerLate";

			AddMoneyToCharacter(pchar, 55000);
			ChangeCharacterReputation(PChar, -10);
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 50);
			dialog.text = StringFromKey("questNPC_251");
			link.l1 = StringFromKey("questNPC_252");
			link.l1.go = "Exit_Away";
			Pchar.questTemp.sLocator = "reload1_back";
			if (npchar.location == "Bridgetown_church") Pchar.questTemp.sLocator = "reload1";
			Pchar.questTemp.iTime = -1;
			AddQuestRecord("UsurerQuest", "3");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			QuestPointerDelLoc("Bridgetown_town", "reload", "reload7_back");
			QuestPointerDelLoc("Bridgetown_town", "reload", "reload5_back");
			AddLandQuestmark_Main(characterFromID("Bridgetown_usurer"), "CapBloodLine");
			QuestPointerToLocEx("Bridgetown_town", "reload", "reload8_back", "BloodLine_UsurerQuest");
			if (CapBloodLine_CheckMoneyForNettl())
				QuestPointerToLocEx("Bridgetown_town", "reload", "reload4_back", "CapBloodLine_q2");
		break;

		case "QSTStep_6":
			PChar.quest.QUsurer.win_condition.l1 = "Timer";
			PChar.quest.QUsurer.win_condition.l1.date.hour = 0;
			PChar.quest.QUsurer.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			PChar.quest.QUsurer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.QUsurer.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.QUsurer.function = "QUsurerLate";

			AddMoneyToCharacter(pchar, 30000);
			AddCharacterExpToSkill(pchar, "Fortune", 50); // fix - Fortune, not Luck (SPECIAL)
			dialog.text = StringFromKey("questNPC_253");
			link.l1 = StringFromKey("questNPC_254");
			link.l1.go = "Exit_Away";
			Pchar.questTemp.sLocator = "reload1_back";
			if (npchar.location == "Bridgetown_church") Pchar.questTemp.sLocator = "reload1_back";
			Pchar.questTemp.iTime = -1;
			AddQuestRecord("UsurerQuest", "4");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			QuestPointerDelLoc("Bridgetown_town", "reload", "reload7_back");
			QuestPointerDelLoc("Bridgetown_town", "reload", "reload5_back");
			AddLandQuestmark_Main(characterFromID("Bridgetown_usurer"), "CapBloodLine");
			QuestPointerToLocEx("Bridgetown_town", "reload", "reload8_back", "BloodLine_UsurerQuest");
			if (CapBloodLine_CheckMoneyForNettl())
				QuestPointerToLocEx("Bridgetown_town", "reload", "reload4_back", "CapBloodLine_q2");
		break;

		//Жак Соловей

		case "JSTStep_0":
			dialog.text = StringFromKey("questNPC_255");
			link.l1 = StringFromKey("questNPC_256");
			link.l1.go = "JSTStep_1";
		break;

		case "JSTStep_1":
			dialog.text = StringFromKey("questNPC_257");
			link.l1 = StringFromKey("questNPC_258");
			link.l1.go = "JSTStep_2";
		break;

		case "JSTStep_2":
			dialog.text = StringFromKey("questNPC_259");
			link.l1 = StringFromKey("questNPC_260");
			link.l1.go = "JSTStep_3";
		break;

		case "JSTStep_3":
			dialog.text = StringFromKey("questNPC_261");
			link.l1 = StringFromKey("questNPC_262");
			link.l1.go = "JSTStep_4";
		break;

		case "JSTStep_4":
			dialog.text = StringFromKey("questNPC_263");
			link.l1 = StringFromKey("questNPC_264");
			link.l1.go = "JSTStep_6";
		break;

		case "JSTStep_6":
			dialog.text = StringFromKey("questNPC_265");
			link.l1 = StringFromKey("questNPC_266");
			link.l1.go = "JSTStep_7";
		break;

		case "JSTStep_7":
			dialog.text = StringFromKey("questNPC_267");
			link.l1 = StringFromKey("questNPC_268");
			link.l1.go = "JSTStep_8";
		break;

		case "JSTStep_8":
			dialog.text = StringFromKey("questNPC_269");
			link.l1 = StringFromKey("questNPC_270");
			link.l1.go = "JSTStep_9";
		break;

		case "JSTStep_9":
			dialog.text = StringFromKey("questNPC_271");
			link.l1 = StringFromKey("questNPC_272");
			link.l1.go = "JSTStep_10";
			link.l2 = StringFromKey("questNPC_273");
			link.l2.go = "Exit_Away";
			Pchar.questTemp.sLocator = "reload1_back";
			Pchar.questTemp.iTime = -1;
			AddDialogExitQuestFunction("CapBloodLine_NeedMoney_Jack_DelQuestMarks");
			// когда выйдем с локи Джек исчезнет в любом случае
			SetFunctionExitFromLocationCondition("CapBloodLine_NeedMoney_Jack_Disappear", pchar.location, false);
		break;

		case "JSTStep_10":
			dialog.text = StringFromKey("questNPC_274");
			link.l1 = StringFromKey("questNPC_275");
			link.l1.go = "Exit_Away";
			Pchar.questTemp.sLocator = "reload1_back";
			Pchar.questTemp.iTime = -1;
			AddQuestRecord("PirateQuest", "1");
			Pchar.questTemp.CapBloodLine.ShipForJack = true;
			sld = characterFromID("Bridgetown_trader");
			LAi_RemoveLoginTime(sld);
			AddLandQuestmark_Main(characterFromID("Bridgetown_PortMan"), "CapBloodLine");
			QuestPointerToLocEx("Bridgetown_town", "reload", "reload10_back", "BloodLine_PirateQuest");
		break;

		case "JSTStep_11":
			dialog.text = StringFromKey("questNPC_276");
			link.l1 = StringFromKey("questNPC_277");
			link.l1.go = "JSTStep_12";
		break;

		case "JSTStep_12":
			dialog.text = StringFromKey("questNPC_278");
			link.l1 = StringFromKey("questNPC_279");
			link.l1.go = "JSTStep_13";
		break;

		case "JSTStep_13":
			dialog.text = StringFromKey("questNPC_280");
			link.l1 = StringFromKey("questNPC_281");
			link.l1.go = "JSTStep_14";
		break;

		case "JSTStep_14":
			dialog.text = StringFromKey("questNPC_282");
			link.l1 = StringFromKey("questNPC_283");
			link.l1.go = "Exit";
			AddMoneyToCharacter(pchar, 1500);
			AddQuestRecord("PirateQuest", "5");
			CloseQuestHeader("PirateQuest");
			NextDiag.TempNode = "JSTStep_15";
			NPChar.lifeDay = 0;
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");

			QuestPointerDelLocEx("Bridgetown_town", "reload", "reload4_back", "BloodLine_PirateQuest");

			iChar = GetCharacterIndex("Nettl");
			if (iChar >= 0)
				SetCurrentQuestMark(&Characters[iChar]); // обновим метку

			if (!CheckAttribute(PChar, "questTemp.CapBloodLine.QuestRaff"))
				QuestPointerToLocEx("Bridgetown_town", "reload", "reload8_back", "BloodLine_UsurerQuest");
		break;

		case "JSTStep_15":
			dialog.text = StringFromKey("questNPC_284");
			link.l1 = StringFromKey("questNPC_285");
			link.l1.go = "Exit";
			NextDiag.TempNode = "JSTStep_15";
		break;

		//Джон Майнер

		case "MNStep_0":
			dialog.text = StringFromKey("questNPC_286");
			link.l1 = StringFromKey("questNPC_287");
			link.l1.go = "MNStep_1";
		break;

		case "MNStep_1":
			dialog.text = StringFromKey("questNPC_288");
			link.l1 = StringFromKey("questNPC_289");
			link.l1.go = "MNStep_2";
			link.l2 = StringFromKey("questNPC_290");
			link.l2.go = "MNStep_3";
			link.l3 = StringFromKey("questNPC_291");
			link.l3.go = "MNStep_4";
		break;

		case "MNStep_2":
			dialog.text = StringFromKey("questNPC_292");
			link.l1 = StringFromKey("questNPC_293");
			link.l1.go = "MNStep_5";
		break;

		case "MNStep_3":
			dialog.text = StringFromKey("questNPC_294");
			link.l1 = StringFromKey("questNPC_295");
			link.l1.go = "MNStep_Exit";
		break;

		case "MNStep_4":
			dialog.text = StringFromKey("questNPC_296");
			link.l1 = StringFromKey("questNPC_297");
			link.l1.go = "MNStep_6";
		break;

		case "MNStep_5":
			dialog.text = StringFromKey("questNPC_298");
			link.l1 = StringFromKey("questNPC_299");
			link.l1.go = "MNStep_Exit";
			AddCharacterExpToSkill(pchar, "Sneak", 50);
		break;

		case "MNStep_6":
			dialog.text = StringFromKey("questNPC_300");
			link.l1 = StringFromKey("questNPC_301");
			link.l1.go = "MNStep_Exit";
		break;

		case "MNStep_Exit":
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			QuestPointerDelLoc("Bridgetown_town", "reload", "reload10_back");
			AddQuestRecord("PirateQuest", "4");
			sld = characterFromID("Jack");
			sld.Dialog.CurrentNode = "JSTStep_11";
			LAi_SetSitTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "sit", "sit4");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddLandQuestmark_Main(sld, "CapBloodLine");
			QuestPointerToLocEx("Bridgetown_town", "reload", "reload4_back", "BloodLine_PirateQuest");
		break;

		//Испанский офицер в Бриджтауне
		case "SRStep_0":
			dialog.text = StringFromKey("questNPC_302");
			link.l1 = StringFromKey("questNPC_303");
			link.l1.go = "fight";
		break;

		//Служанка Арабеллы
		case "ASStep_0":
			dialog.text = StringFromKey("questNPC_304");
			link.l1 = StringFromKey("questNPC_305");
			link.l1.go = "ASStep_1";
			ChangeCharacterReputation(pchar, 5);
		break;

		case "ASStep_1":
			dialog.text = StringFromKey("questNPC_306");
			link.l1 = StringFromKey("questNPC_307");
			link.l1.go = "ASStep_2";
		break;

		case "ASStep_2":
			dialog.text = StringFromKey("questNPC_308");
			link.l1 = StringFromKey("questNPC_309");
			Pchar.questTemp.CapBloodLine.SpainInBridgetown = true;
			Pchar.questTemp.sLocator = "gate1_back";
			Pchar.questTemp.iTime = -1;
			link.l1.go = "Exit_RunAway";
			AddQuestRecord("EscapeFormBarbados", "3");
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			SetBan("Looting", 0);
			DoQuestFunctionDelay("Tutorial_BloodPrologue_DeadSearch", 1.0);
			AddDialogExitQuestFunction("CapBloodLine_Escape_SetQuestPointers");
		break;
		
		//Диалог Гобарта с Кирком
		case "Kirk":
			dialog.text = StringFromKey("questNPC_310");
			link.l1 = StringFromKey("questNPC_311");
			link.l1.go = "exit";
			CharacterTurnByChr(CharacterFromID("Kirk"), CharacterFromID("CapGobart"));
			CharacterTurnByChr(CharacterFromID("CapGobart"), CharacterFromID("Kirk"));
			locCameraFromToPos(-22.30, 7.95, 5.04, true, -22.00, 5.94, 1.48);
			AddDialogExitQuestFunction("CapBloodLine_Kirk_3");
		break;
		
		case "Gobart":
			dialog.text = "...";
			link.l1 = StringFromKey("questNPC_312");
			link.l1.go = "exit";
			CharacterTurnToLoc(CharacterFromID("CapGobart"), "goto", "stay5");
			AddDialogExitQuestFunction("CapBloodLine_Kirk_5");
		break;
	}
}

void BloodWithdrawWeapon() //HardCoffee fix
{
	ref rItm;
	string sItm;
	int i;
	bool bDagger = false;
	RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
	for (i = TOTAL_ITEMS - 1; i >= 0; i--)
	{
		rItm = &Items[i];
		if (!CheckAttribute(rItm, "groupID")) continue;
		if (rItm.groupID != GUN_ITEM_TYPE && rItm.groupID != BLADE_ITEM_TYPE && rItm.groupID != AMMO_ITEM_TYPE) continue;
		if (!CheckAttribute(pchar, "items." + rItm.id)) continue;
		sItm = rItm.id;
		if (sItm == "unarmed") continue;
		bDagger = HasSubStr(sItm, "blade5");
		if (bDagger && !CheckAttribute(&TEV, "BloodDetectDagger")) continue;
		else if (bDagger) DeleteAttribute(&TEV, "BloodDetectDagger");
		TakeNItems(pchar, sItm, -sti(pchar.items.(sItm)));
	}

	if ("STBStep_1" == Dialog.CurrentNode) return;
	i = GetCharacterIndex("SolderTakeBlades"); //На случай, если вместо скриптового нпс к гг обратился другой нпс
	if (i < 0) return;
	chrDisableReloadToLocation = false;
	rItm = &characters[i];
	LAi_type_actor_Reset(rItm);
	sItm = FindLocatorForSolderTakeBlades(rItm);
	LAi_ActorGoToLocation(rItm, "reload", sItm, "none", "", "", "", -1);
}

string FindLocatorForSolderTakeBlades(ref rChr)
{
	string sLocator = "";
	aref arLoc;
	//Дом губернатора в городе
	if (FindLocator(loadedlocation.id, "reload3_back", &arLoc, true) && LAi_IsLocatorFree("reload", "reload3_back", 0.05))
		sLocator = "reload3_back";
	//Дом плантатора
	else if (FindLocator(loadedlocation.id, "houseSp1", &arLoc, true) && LAi_IsLocatorFree("reload", "houseSp1", 0.05))
		sLocator = "houseSp1";
	else
	{
		float locx, locy, locz;
		GetCharacterPos(rChr, &locx, &locy, &locz);
		sLocator = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
	}
	return sLocator;
}

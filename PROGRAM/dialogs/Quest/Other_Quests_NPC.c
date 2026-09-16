void ProcessDialogEvent()
{
	ref NPChar;
	int n;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "First time":
			if (NPChar.id == "Andre_Abel_Quest_Guard_1") // Гвардеец в резиденции Кюрасао. Сопровождение флейта "Орион"
			{
				dialog.text = StringFromKey("Other_Quests_NPC_4", LinkRandPhrase(
							StringFromKey("Other_Quests_NPC_1"),
							StringFromKey("Other_Quests_NPC_2"),
							StringFromKey("Other_Quests_NPC_3")));
				link.l1 = StringFromKey("Other_Quests_NPC_5");
				link.l1.go = "Exit_Andre_Abel_Quest_Guard";
			}

			if (NPChar.id == "Martin_Bleker")    // Мартин Блэкер
			{
				dialog.text = StringFromKey("Other_Quests_NPC_6", pchar);
				//	link.l1 = "Да иди ты к чёрту!";
				//	link.l1.go = "Andre_Abel_Quest_In_Prison_Wrong_Way_1";
				link.l2 = StringFromKey("Other_Quests_NPC_7");
				link.l2.go = "Andre_Abel_Quest_In_Prison_1";
			}
		break;

		case "Exit_Andre_Abel_Quest_Guard":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// Мартин Блэкер. Квест "Сопровождение флейта 'Орион'" -->
		case "Andre_Abel_Quest_In_Prison_Wrong_Way_1":
			dialog.text = StringFromKey("Other_Quests_NPC_8");
			link.l1 = StringFromKey("Other_Quests_NPC_9");
			link.l1.go = "Andre_Abel_Quest_In_Prison_Wrong_Way_2";
			link.l2 = StringFromKey("Other_Quests_NPC_10");
			link.l2.go = "Andre_Abel_Quest_In_Prison_2";
		break;

		case "Andre_Abel_Quest_In_Prison_Wrong_Way_2":
			dialog.text = StringFromKey("Other_Quests_NPC_11");
			link.l1 = StringFromKey("Other_Quests_NPC_12");
			link.l1.go = "Andre_Abel_Quest_In_Prison_Wrong_Way_3";
		break;

		case "Andre_Abel_Quest_In_Prison_Wrong_Way_3":
			DialogExit();
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_208"), "", 5, 3);
			LaunchFrameForm();
		break;

		case "Andre_Abel_Quest_In_Prison_1":
			dialog.text = StringFromKey("Other_Quests_NPC_13");
			link.l1 = StringFromKey("Other_Quests_NPC_14");
			link.l1.go = "Andre_Abel_Quest_In_Prison_2";
		break;

		case "Andre_Abel_Quest_In_Prison_2":
			dialog.text = StringFromKey("Other_Quests_NPC_15");
			link.l1 = StringFromKey("Other_Quests_NPC_16");
			link.l1.go = "Andre_Abel_Quest_In_Prison_3";
		break;

		case "Andre_Abel_Quest_In_Prison_3":
			dialog.text = StringFromKey("Other_Quests_NPC_17", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_18");
			link.l1.go = "Andre_Abel_Quest_In_Prison_4";
		break;

		case "Andre_Abel_Quest_In_Prison_4":
			dialog.text = StringFromKey("Other_Quests_NPC_19");
			link.l1 = StringFromKey("Other_Quests_NPC_20");
			link.l1.go = "Andre_Abel_Quest_In_Prison_5";
		break;

		case "Andre_Abel_Quest_In_Prison_5":
			dialog.text = StringFromKey("Other_Quests_NPC_21");
			link.l1 = StringFromKey("Other_Quests_NPC_22", GetFullName(pchar));
			link.l1.go = "Andre_Abel_Quest_In_Prison_6";
		break;

		case "Andre_Abel_Quest_In_Prison_6":
			DialogExit();
			NextDiag.CurrentNode = "Andre_Abel_Quest_In_Prison_7";
			LAi_SetCitizenType(NPChar);
			//ГГ на выбор -->
			sTemp = GetGeneratedItem(Andre_Abel_Quest_GetBladeId_ByFencingType());
			GiveItem2Character(Pchar, sTemp);
			EquipCharacterbyItem(Pchar, sTemp);
			//<-- на выбор
			//Мартину Бильбо -->
			sTemp = GetGeneratedItem("blade7");
			GiveItem2Character(NPChar, sTemp);
			EquipCharacterbyItem(NPChar, sTemp);
			//<-- Бильбо
			SetFunctionLocationCondition("Andre_Abel_Quest_Liberty", "Villemstad_ExitTown", false);
			SetFunctionNPCDeathCondition("Andre_Abel_Quest_Martin_Bleker_Is_Dead", "Martin_Bleker", false);
			ChangeCharacterAddressGroup(NPChar, "Villemstad_prison", "goto", "goto12");
			DoFunctionReloadToLocation("Villemstad_prison", "goto", "goto23", "Andre_Abel_Quest_Runaway_From_Prison");
		break;

		case "Andre_Abel_Quest_In_Prison_7":
			dialog.text = StringFromKey("Other_Quests_NPC_25", RandPhraseSimple(
						StringFromKey("Other_Quests_NPC_23"),
						StringFromKey("Other_Quests_NPC_24")));
			link.l1 = StringFromKey("Other_Quests_NPC_26");
			link.l1.go = "exit";
			NextDiag.TempNode = "Andre_Abel_Quest_In_Prison_7";
		break;

		case "Andre_Abel_Quest_In_Liberty_1":
			dialog.text = StringFromKey("Other_Quests_NPC_27");
			link.l1 = StringFromKey("Other_Quests_NPC_28", pchar);
			link.l1.go = "Andre_Abel_Quest_In_Liberty_2";

			n = FindLocation("Villemstad_prison");
			Locations[n].reload.l1.go = "Villemstad_town";
			Locations[n].reload.l1.emerge = "HouseT1";
		break;

		case "Andre_Abel_Quest_In_Liberty_2":
			dialog.text = StringFromKey("Other_Quests_NPC_29");
			link.l1 = StringFromKey("Other_Quests_NPC_30");
			link.l1.go = "Andre_Abel_Quest_In_Liberty_3";
			link.l2 = StringFromKey("Other_Quests_NPC_31");
			link.l2.go = "Andre_Abel_Quest_In_Liberty_4";
		break;

		case "Andre_Abel_Quest_In_Liberty_3":
			DialogExit();
			LAi_SetPlayerType(PChar);
			NPChar.LifeDay = 0;
			LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
		break;

		case "Andre_Abel_Quest_In_Liberty_4":
			// проверка на обаяние + лимит офицеров
			if (FindFreeRandomOfficer() > 0 && PlayerRPGCheck_SPECIAL(SPECIAL_C, 8))
			{
				dialog.text = StringFromKey("Other_Quests_NPC_32");
				link.l1 = StringFromKey("Other_Quests_NPC_33");
				link.l1.go = "Andre_Abel_Quest_In_Liberty_5";
			}
			else
			{
				dialog.text = StringFromKey("Other_Quests_NPC_34");
				link.l1 = StringFromKey("Other_Quests_NPC_35");
				link.l1.go = "Andre_Abel_Quest_In_Liberty_3";
			}
		break;

		case "Andre_Abel_Quest_In_Liberty_5":
			dialog.text = StringFromKey("Other_Quests_NPC_36");
			link.l1 = StringFromKey("Other_Quests_NPC_37");
			link.l1.go = "Andre_Abel_Quest_In_Liberty_6";
		break;

		case "Andre_Abel_Quest_In_Liberty_6":
			dialog.text = StringFromKey("Other_Quests_NPC_38");
			link.l1 = StringFromKey("Other_Quests_NPC_39");
			link.l1.go = "Andre_Abel_Quest_In_Liberty_7";
		break;

		case "Andre_Abel_Quest_In_Liberty_7":
			LAi_SetPlayerType(PChar);
			NPChar.Dialog.FileName = "Officer_Man.c";
			LAi_SetStayType(NPChar);
			NPChar.OfficerWantToGo.DontGo = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NPChar.loyality = MAX_LOYALITY;
			AddQuestRecord("Andre_Abel_Quest", "19");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("", "а"));
			SetFunctionExitFromLocationCondition("Andre_Abel_Quest_Delete_Martin", PChar.location, false);
			pchar.quest.MartinRecovery.win_condition.l1 = "Timer";
			pchar.quest.MartinRecovery.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
			pchar.quest.MartinRecovery.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.MartinRecovery.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
			pchar.quest.MartinRecovery.function = "MartinRecovery";
			DialogExit();
		break;
		// <-- Мартин Блэкер. Квест "Сопровождение флейта 'Орион'"

		//--> работорговец, пинас
		case "TakeShoreCap":
			dialog.text = StringFromKey("Other_Quests_NPC_40", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_41", pchar);
			link.l1.go = "Node_1";
		break;

		case "Node_1":
			dialog.text = StringFromKey("Other_Quests_NPC_42", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_43");
			link.l1.go = "Node_2";
		break;

		case "Node_2":
			dialog.text = StringFromKey("Other_Quests_NPC_44", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_45");
			link.l1.go = "Node_3";
		break;

		case "Node_3":
			dialog.text = StringFromKey("Other_Quests_NPC_46", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_47");
			link.l1.go = "Node_4";
		break;

		case "Node_4":
			pchar.questTemp.Slavetrader = "TakeShoreCap_end"; //это состояние квеста для проверки у квестодателя
			AddQuestRecord("Slavetrader", "13");
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			pchar.quest.Slavetrader_DieHard.over = "yes";
			pchar.quest.Slavetrader_AfterBattle.over = "yes";
			pchar.quest.Slavetrader_ShoreShipsOver.over = "yes";
			Group_DeleteGroup("Shore_Attack");
			Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.Slavetrader.UsurerId), "Slavetrader");
		break;

		case "Slave_arest":
			dialog.text = StringFromKey("Other_Quests_NPC_48", GetFullName(pchar));
			link.l1 = StringFromKey("Other_Quests_NPC_49");
			link.l1.go = "Slave_arest_1";
		break;

		case "Slave_arest_1":
			dialog.text = StringFromKey("Other_Quests_NPC_50", NationNameGenitive(sti(npchar.nation)));
			link.l1 = StringFromKey("Other_Quests_NPC_51");
			link.l1.go = "Slave_arest_2";
		break;

		case "Slave_arest_2":
			LAi_SetWarriorTypeNoGroup(npchar);
			AddDialogExitQuest("Slavetrader_Ambush");
			DialogExit();
		break;
		//<--работорговец пинас

		//--> работорговец, крыса в доме
		case "Rat_bandos":
			dialog.text = StringFromKey("Other_Quests_NPC_52", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_53");
			link.l1.go = "Node_rat_1";
		break;

		case "Node_rat_1":
			dialog.text = StringFromKey("Other_Quests_NPC_54", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_55");
			link.l1.go = "Node_rat_2";
		break;

		case "Node_rat_2":
			dialog.text = StringFromKey("Other_Quests_NPC_56");
			link.l1 = StringFromKey("Other_Quests_NPC_57");
			link.l1.go = "Node_rat_3";
		break;

		case "Node_rat_3":
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "ST_TortugaRatGroup");
			LAi_group_SetRelation("ST_TortugaRatGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("ST_TortugaRatGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("ST_TortugaRatGroup", "Slavetrader_findTortugaRat1");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Rat_lover":
			dialog.text = StringFromKey("Other_Quests_NPC_58");
			link.l1 = StringFromKey("Other_Quests_NPC_59");
			link.l1.go = "Rat_lover_1";
		break;

		case "Rat_lover_1":
			dialog.text = StringFromKey("Other_Quests_NPC_60");
			link.l1 = StringFromKey("Other_Quests_NPC_61");
			link.l1.go = "Rat_lover_2";
		break;

		case "Rat_lover_2":
			dialog.text = StringFromKey("Other_Quests_NPC_62");
			link.l1 = StringFromKey("Other_Quests_NPC_63");
			link.l1.go = "Rat_lover_3";
			pchar.quest.Slavetrader_RatAttack.win_condition.l1 = "location";
			pchar.quest.Slavetrader_RatAttack.win_condition.l1.location = "Tortuga";//отправляем в локацию
			pchar.quest.Slavetrader_RatAttack.function = "Slavetrader_RatCorvette";//создание корвета
			SetFunctionTimerCondition("Slavetrader_RatCorvetteOver", 0, 0, 1, false);
		break;

		case "Rat_lover_3":
			LAi_SetPlayerType(pchar);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Slavetrader", "21_9");
			RemoveLandQuestmark_Main(CharacterFromID("Tortuga_tavernkeeper"), "Slavetrader");
			RemoveLandQuestmark_Main(CharacterFromID("Tortuga_PortMan"), "Slavetrader");
			SetBan("Looting,Exchange", 0);
			LAi_group_Delete("ST_TortugaRatGroup");
			DialogExit();
		break;
		//<--работорговец крыса в доме

		//--> работорговец, беглые рабы
		case "Slave_woman":
			dialog.text = StringFromKey("Other_Quests_NPC_64");
			link.l1 = StringFromKey("Other_Quests_NPC_65");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_Slavewoman");
		break;
		//<--работорговец беглые рабы

		//ОЗГ, Карлос Кассир
		case "Carlos":
			dialog.text = StringFromKey("Other_Quests_NPC_66", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_67", pchar);
			link.l1.go = "Carlos_7";
		break;

		case "Carlos_3":
			Dialog.Text = StringFromKey("Other_Quests_NPC_68");
			link.l1 = StringFromKey("Other_Quests_NPC_69");
			link.l1.go = "Carlos_4";
			pchar.questTemp.Headhunter = "hunt_carlos_fight";
		break;

		case "Carlos_4":
			LAi_LocationDisableOfficersGen(pchar.questTemp.Headhunter.City + "_ExitTown", true);//офицеров не пускать
			locations[FindLocation(pchar.questTemp.Headhunter.City + "_ExitTown")].DisableEncounters = true; //энкаутеры закроем
			AddQuestRecord("Headhunt", "2_1");
			RemoveLandQuestMark_Main(npchar, "Headhunt");
			pchar.quest.HeadhunterTimer.win_condition.l1 = "Timer";
			pchar.quest.HeadhunterTimer.win_condition.l1.date.hour = sti(GetTime() + 1);
			pchar.quest.HeadhunterTimer.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			pchar.quest.HeadhunterTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.HeadhunterTimer.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			pchar.quest.HeadhunterTimer.function = "CarlosDuel";
			SetFunctionTimerCondition("CarlosDuelOver", 0, 0, 2, false);
			NextDiag.CurrentNode = "Carlos_5";
			DialogExit();
		break;

		case "Carlos_5":
			Dialog.Text = StringFromKey("Other_Quests_NPC_70");
			link.l1 = StringFromKey("Other_Quests_NPC_71", pchar);
			link.l1.go = "Exit";
			NextDiag.TempNode = "Carlos_5";
		break;

		case "talk_off_town_Carlos":
			Dialog.Text = StringFromKey("Other_Quests_NPC_72", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_73");
			link.l1.go = "Carlos_6";
			chrDisableReloadToLocation = true;
		break;

		case "Carlos_6":
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "HH_CarlosGroup");
			LAi_group_SetRelation("HH_CarlosGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("HH_CarlosGroup", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("HH_CarlosGroup", "CarlosDie");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			RemoveLandQuestMark_Main(npchar, "Headhunt");
		break;

		case "Carlos_7":
			dialog.text = StringFromKey("Other_Quests_NPC_74", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_75", pchar);
			link.l1.go = "Carlos_8";
		break;

		case "Carlos_8":
			dialog.text = StringFromKey("Other_Quests_NPC_76", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_77");
			link.l1.go = "Carlos_3";
			n = FindLocation(pchar.questTemp.Headhunter.City + "_Brothel");
			locations[n].reload.l2.disable = true;
		break;
		//ОЗГ, Карлос Кассир

		//ОЗГ, Ганнибал Хоум
		case "Houm":
			dialog.text = StringFromKey("Other_Quests_NPC_78");
			link.l1 = StringFromKey("Other_Quests_NPC_79");
			link.l1.go = "Houm_1";
		break;

		case "Houm_1":
			dialog.text = StringFromKey("Other_Quests_NPC_80");
			link.l1 = StringFromKey("Other_Quests_NPC_81");
			link.l1.go = "Houm_2";
		break;

		case "Houm_2":
			dialog.text = StringFromKey("Other_Quests_NPC_82");
			link.l1 = StringFromKey("Other_Quests_NPC_83");
			link.l1.go = "Houm_3";
		break;

		case "Houm_3":
			dialog.text = StringFromKey("Other_Quests_NPC_84", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_85");
			link.l1.go = "Houm_4";
		break;

		case "Houm_4":
			dialog.text = StringFromKey("Other_Quests_NPC_86", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_87");
			link.l1.go = "Houm_5";
			AddQuestRecord("Headhunt", "6");
			AddQuestUserData("Headhunt", "sSex", GetSexPhrase("", "а"));
			pchar.quest.Headhunter_HoumAttack.win_condition.l1 = "location";
			pchar.quest.Headhunter_HoumAttack.win_condition.l1.location = pchar.questTemp.Headhunter.Island;//отправляем в локацию
			pchar.quest.Headhunter_HoumAttack.function = "Headhunter_CreateHoumShips";//создание кораблей
		break;

		case "Houm_5":
			if (HasSubStr(PChar.location, "_tavern"))
			{
				DialogExit();
				NextDiag.CurrentNode = "Houm_6";
			}
			else
			{
				LAi_SetActorType(npchar);
				LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15.0);
			}
			RemoveLandQuestMark_Main(npchar, "Headhunt");
			DialogExit();
		break;

		case "Houm_6":
			Dialog.Text = StringFromKey("Other_Quests_NPC_88");
			link.l1 = StringFromKey("Other_Quests_NPC_89", pchar);
			link.l1.go = "Exit";
			NextDiag.TempNode = "Houm_6";
		break;

		case "RatOfficer":
			if (CheckAttrValue(pchar, "questTemp.Headhunter", "Rat_officer") && GetCompanionQuantity(pchar) == 1 && 3 - sti(RealShips[sti(pchar.ship.type)].Class) <= 0)
			{
				int iGoods1 = 400 - GetSquadronGoods(Pchar, GOOD_EBONY);
				int iGoods2 = 500 - GetSquadronGoods(Pchar, GOOD_MAHOGANY);
				int iGoods3 = 670 - GetSquadronGoods(Pchar, GOOD_SANDAL);

				if (iGoods1 < 1 || iGoods2 < 1 || iGoods3 < 1)
				{
					dialog.text = StringFromKey("Other_Quests_NPC_90");
					link.l1 = StringFromKey("Other_Quests_NPC_91");
					link.l1.go = "RatOfficer_1";
				}
				else
				{
					dialog.text = StringFromKey("Other_Quests_NPC_92");
					link.l1 = StringFromKey("Other_Quests_NPC_93", pchar);
					link.l1.go = "exit";
					NextDiag.TempNode = "RatOfficer";
				}
				break;
			}
			dialog.text = StringFromKey("Other_Quests_NPC_94");
			link.l1 = StringFromKey("Other_Quests_NPC_95", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "RatOfficer";
		break;

		case "RatOfficer_1":
			dialog.text = StringFromKey("Other_Quests_NPC_96");
			link.l1 = StringFromKey("Other_Quests_NPC_97");
			link.l1.go = "RatOfficer_1_sit";
		break;

		case "RatOfficer_1_sit":
			bDisableLandEncounters = true;
			NextDiag.CurrentNode = "RatOfficer_2";
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 1.5);
			DoQuestReloadToLocation("Tortuga_tavern", "sit", "sit1", "");
			LAi_SetSitType(Pchar);
			DialogExit();
		break;

		case "RatOfficer_2":
			dialog.text = StringFromKey("Other_Quests_NPC_98", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_99");
			link.l1.go = "RatOfficer_3";
		break;

		case "RatOfficer_3":
			dialog.text = StringFromKey("Other_Quests_NPC_100", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_101");
			link.l1.go = "RatOfficer_4";
		break;

		case "RatOfficer_4":
			dialog.text = StringFromKey("Other_Quests_NPC_102");
			link.l1 = StringFromKey("Other_Quests_NPC_103", pchar);
			link.l1.go = "RatOfficer_5";
		break;

		case "RatOfficer_5":
			dialog.text = StringFromKey("Other_Quests_NPC_104");
			link.l1 = StringFromKey("Other_Quests_NPC_105", pchar);
			link.l1.go = "RatOfficer_6";
		break;

		case "RatOfficer_6":
			dialog.text = StringFromKey("Other_Quests_NPC_106");
			link.l1 = StringFromKey("Other_Quests_NPC_107");
			link.l1.go = "RatOfficer_7";
		break;

		case "RatOfficer_7":
			dialog.text = StringFromKey("Other_Quests_NPC_108");
			link.l1 = StringFromKey("Other_Quests_NPC_109");
			link.l1.go = "RatOfficer_8";
		break;

		case "RatOfficer_8":
			dialog.text = StringFromKey("Other_Quests_NPC_110");
			link.l1 = StringFromKey("Other_Quests_NPC_111");
			link.l1.go = "RatOfficer_9";
			pchar.quest.Headhunter_Ratgulf.win_condition.l1 = "location";
			pchar.quest.Headhunter_Ratgulf.win_condition.l1.location = "Shore_ship2";//отправляем в локацию
			pchar.quest.Headhunter_Ratgulf.function = "Headhunter_Ratgulf";
			SetFunctionTimerCondition("Headhunter_RatgulfOver", 0, 0, 15, false);//таймер
		break;

		case "RatOfficer_9":
			LAi_SetAlcoholState(1);
			pchar.quest.Headhunter_RatOfficerOver.over = "yes";
			LAI_SetPlayerType(pchar);
			LAI_SetSitType(npchar);
			DoQuestReloadToLocation("Tortuga_tavern", "goto", "goto4", "RatHunters_TalkInTavernEnd");
			pchar.questTemp.Headhunter = "Rat_gulf";
			NextDiag.CurrentNode = "RatOfficer_10";
			npchar.lifeDay = 0;
			RemoveLandQuestMark_Main(npchar, "Headhunt");
			DialogExit();
		break;

		case "RatOfficer_10":
			dialog.text = StringFromKey("Other_Quests_NPC_112");
			link.l1 = StringFromKey("Other_Quests_NPC_113");
			link.l1.go = "exit";
			NextDiag.TempNode = "RatOfficer_10";
		break;

		//ОЗГ, кэп-Крыса
		case "Rat_talk":
			dialog.text = StringFromKey("Other_Quests_NPC_114");
			link.l1 = StringFromKey("Other_Quests_NPC_115");
			link.l1.go = "Rat_talk_1";
		break;

		case "Rat_talk_1":
			dialog.text = StringFromKey("Other_Quests_NPC_116");
			link.l1 = StringFromKey("Other_Quests_NPC_117");
			link.l1.go = "Rat_talk_exit";
		break;

		case "Rat_talk_exit":
			pchar.questTemp.Headhunter = "hunt_rat_yes1";
			AddQuestRecord("Headhunt", "23");
			AddQuestUserData("Headhunt", "sSex", GetSexPhrase("", "а"));
			pchar.quest.Headhunter_DieHard.over = "yes";
			pchar.quest.Headhunter_AfterBattle.over = "yes";
			Island_SetReloadEnableGlobal("Beliz", true);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "RatHunters":
		//dialog.text = "...";
			link.l1 = StringFromKey("Other_Quests_NPC_118");
			link.l1.go = "RatHunters_1";
		break;

		case "RatHunters_1":
			dialog.text = StringFromKey("Other_Quests_NPC_119");
			link.l1 = StringFromKey("Other_Quests_NPC_120");
			link.l1.go = "RatHunters_2";
		break;

		case "RatHunters_2":
			LAi_SetFightMode(pchar, true);
			LAi_LockFightMode(pchar, false);
			LAi_group_SetRelation("HH_RatHuntersGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("HH_RatHuntersGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("HH_RatHuntersGroup", "RatHunters_Dead");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Halen":
			dialog.text = StringFromKey("Other_Quests_NPC_121", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_122");
			link.l1.go = "Halen_1";
		break;

		case "Halen_1":
			dialog.text = StringFromKey("Other_Quests_NPC_123");
			link.l1 = StringFromKey("Other_Quests_NPC_124");
			link.l1.go = "Halen_2";
			link.l2 = StringFromKey("Other_Quests_NPC_125", pchar);
			link.l2.go = "Halen_3";
		break;

		case "Halen_2":
			dialog.text = StringFromKey("Other_Quests_NPC_126", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_127");
			link.l1.go = "Halen_fight";
		break;

		case "Halen_fight":
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "HOLLAND_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			RemoveLandQuestMark_Main(npchar, "Headhunt");
			pchar.quest.Headhunter_Halen_fight.win_condition.l1 = "NPC_Death";
			pchar.quest.Headhunter_Halen_fight.win_condition.l1.character = "Halen";
			pchar.quest.Headhunter_Halen_fight.win_condition = "Headhunter_HalenDeadInTown";
		break;

		case "Halen_3":
			dialog.text = StringFromKey("Other_Quests_NPC_128", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_129");
			link.l1.go = "exit_halen";
		break;

		case "Halen_4":
			dialog.text = StringFromKey("Other_Quests_NPC_130", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_131");
			link.l1.go = "exit_halen";
			link.l2 = StringFromKey("Other_Quests_NPC_132");
			link.l2.go = "Halen_2";
			NextDiag.CurrentNode = "Halen_4";
		break;

		case "exit_halen":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "none", "", "", "Headhunter_HalenOut", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			NextDiag.CurrentNode = "Halen_4";
			RemoveLandQuestMark_Main(npchar, "Headhunt");
			DialogExit();
		break;

		case "Halen_Deck":
			dialog.text = StringFromKey("Other_Quests_NPC_133", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_134");
			link.l1.go = "exit_halen_board";
		break;

		case "exit_halen_board":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;

		case "Miko":
			dialog.text = StringFromKey("Other_Quests_NPC_135");
			link.l1 = StringFromKey("Other_Quests_NPC_136");
			link.l1.go = "Miko_1";
		break;

		case "Miko_1":
			dialog.text = StringFromKey("Other_Quests_NPC_137");
			link.l1 = StringFromKey("Other_Quests_NPC_138");
			link.l1.go = "Miko_2";
		break;

		case "Miko_2":
			dialog.text = StringFromKey("Other_Quests_NPC_139", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_140");
			link.l1.go = "Miko_3";
		break;

		case "Miko_3":
			dialog.text = StringFromKey("Other_Quests_NPC_141", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_142");
			link.l1.go = "Miko_fight";
			pchar.questTemp.Headhunter = "miko_mustdie";
			pchar.quest.Headhunter_Miko_mustdie.win_condition.l1 = "NPC_Death";
			pchar.quest.Headhunter_Miko_mustdie.win_condition.l1.character = "Miko";
			pchar.quest.Headhunter_Miko_mustdie.function = "Miko_die";
		break;

		case "Miko_fight":
			chrDisableReloadToLocation = true;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "Pearlgroup_2");
			LAi_group_Attack(NPChar, Pchar);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Headhunt", "34");
			RemoveLandQuestMark_Main(npchar, "Headhunt");
		break;

		case "JaHunters":
			dialog.text = StringFromKey("Other_Quests_NPC_143", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_144");
			link.l1.go = "JaHunters_1";
		break;

		case "JaHunters_1":
			dialog.text = StringFromKey("Other_Quests_NPC_145");
			link.l1 = StringFromKey("Other_Quests_NPC_146");
			link.l1.go = "JaHunters_2";
		break;

		case "JaHunters_2":
			LAi_SetImmortal(npchar, false);
			pchar.quest.Headhunter_Find_Ja.win_condition.l1 = "location";
			pchar.quest.Headhunter_Find_Ja.win_condition.l1.location = "SantaCatalina";
			pchar.quest.Headhunter_Find_Ja.function = "Create_Ja";
			LAi_group_SetRelation("HH_JaHuntersGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("HH_JaHuntersGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("HH_JaHuntersGroup", "FindJa");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Ja_talk":
			dialog.text = StringFromKey("Other_Quests_NPC_147");
			link.l1 = StringFromKey("Other_Quests_NPC_148", pchar);
			link.l1.go = "Ja_talk_1";
			link.l2 = StringFromKey("Other_Quests_NPC_149");
			link.l2.go = "Ja_talk_3";
		break;

		case "Ja_talk_1":
			dialog.text = StringFromKey("Other_Quests_NPC_150");
			link.l1 = StringFromKey("Other_Quests_NPC_151");
			link.l1.go = "Ja_talk_exit";
		break;

		case "Ja_talk_exit":
			pchar.questTemp.Headhunter = "hunt_ja_yes";
			bQuestDisableMapEnter = false;
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Ja_talk_3":
			dialog.text = StringFromKey("Other_Quests_NPC_152", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_153");
			link.l1.go = "Ja_talk_4";
		break;

		case "Ja_talk_4":
			dialog.text = StringFromKey("Other_Quests_NPC_154");
			link.l1 = StringFromKey("Other_Quests_NPC_155");
			link.l1.go = "Ja_talk_5";
		break;

		case "Ja_talk_5":
			dialog.text = StringFromKey("Other_Quests_NPC_156", pchar);
			link.l1 = StringFromKey("Other_Quests_NPC_157");
			link.l1.go = "Ja_talk_1";
			link.l2 = StringFromKey("Other_Quests_NPC_158", pchar);
			link.l2.go = "Ja_talk_6";
		break;

		case "Ja_talk_6":
			dialog.text = StringFromKey("Other_Quests_NPC_159");
			link.l1 = StringFromKey("Other_Quests_NPC_160");
			link.l1.go = "Ja_hired";
			pchar.quest.Headhunter_AfterBattleJa.over = "yes";
		break;

		case "Ja_hired":
			bQuestDisableMapEnter = false;
			characters[GetCharacterIndex("Jafar")].lifeDay = 0;
			AddQuestRecord("Headhunt", "38");
			CloseQuestHeader("Headhunt");
			Headhunter_CleanupAll("end_quest_full");
			ref sld = GetCharacter(NPC_GenerateCharacter("Jafarry", "Jafar_Preston", "man", "man", 30, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 30, 70, 70, "blade14", "pistol6", 100);
			sld.name = FindPersonalName("Jafar_name");
			sld.lastname = FindPersonalName("Jafar_lastname");
			sld.greeting = "Gr_Officer";
			sld.rank = 30;
			sld.Dialog.Filename = "Officer_Man.c";
			sld.quest.meeting = true;
			SetSelfSkill(sld, 80, 80, 75, 80, 80);
			SetShipSkill(sld, 70, 75, 75, 75, 80, 70, 70, 70, 70);
			SetSPECIAL(sld, 9, 9, 10, 10, 8, 10, 10);
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "ByWorker");
			SetCharacterPerk(sld, "Ciras");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "IronWill");
			SetCharacterPerk(sld, "BladeDancer");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "FastReload");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "LootCollection");
			SetCharacterPerk(sld, "Mentor");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "Medic");
			//черты
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "LoyalOff");
			SetCharacterPerk(sld, "Rebel"); //TODO: снизить ему репутацию?
			//sld.quest.OfficerPrice = sti(pchar.rank)*500; TODO_salary
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.loyality = MAX_LOYALITY;
			LAi_SetRolyPoly(sld, true); //неваляха
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			QuestAboardCabinDialogNotBattle();
			DialogExit();
			Achievment_Set(ACH_Nayomnik);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

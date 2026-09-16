// это всякая мелочь по изабелле: кэп брига, брат, офицер при аресте и пр.
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			dialog.text = StringFromKey("BrigCaptain_1");
			link.l1 = StringFromKey("BrigCaptain_2");
			link.l1.go = "ShipToDomingoTavenr_2";
			link.l2 = StringFromKey("BrigCaptain_3");
			link.l2.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ShipToDomingoTavenr_2":
			dialog.text = StringFromKey("BrigCaptain_4");
			link.l1 = StringFromKey("BrigCaptain_5");
			link.l1.go = "ShipToDomingoTavenr_3";
		break;

		case "ShipToDomingoTavenr_3":
			NextDiag.TempNode = "ShipToDomingoTavenr_Temp";
			dialog.text = StringFromKey("BrigCaptain_6");
			link.l1 = StringFromKey("BrigCaptain_7");
			link.l1.go = "exit";
			Pchar.quest.Romantic_Brother.win_condition.l1 = "location";
			Pchar.quest.Romantic_Brother.win_condition.l1.location = "Cumana_town";
			Pchar.quest.Romantic_Brother.win_condition = "Romantic_Brother";
			Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
			AddQuestRecord("Romantic_Line", "6");
			npchar.LifeDay = 2;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
			RemoveLandQuestmark_Main(CharacterFromID("Cumana_tavernkeeper"), "Romantic_Line");
		break;

		case "ShipToDomingoTavenr_Temp":
			NextDiag.TempNode = "ShipToDomingoTavenr_Temp";
			dialog.text = StringFromKey("BrigCaptain_8");
			link.l1 = StringFromKey("BrigCaptain_9");
			link.l1.go = "exit";
		break;
		// братан Изабеллы
		case "Romantic_Brother_1":
			NextDiag.TempNode = "Romantic_Brother_2";
			dialog.text = StringFromKey("BrigCaptain_10", GetFullName(Pchar));
			link.l1 = StringFromKey("BrigCaptain_11", GetFullName(Pchar));
			link.l1.go = "Step_1";
		break;
		case "Step_1":
			AddQuestRecord("Romantic_Line", "7");
			OfficersReaction("good");
			AddCharacterExpToSkill(pchar, "Sailing", 40);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddPassenger(pchar, NPChar, false);
			SetCharacterRemovable(NPChar, false);
			Pchar.quest.Romantic_Brother_port.win_condition.l1 = "location";
			Pchar.quest.Romantic_Brother_port.win_condition.l1.location = "SanJuan_town";
			Pchar.quest.Romantic_Brother_port.win_condition = "Romantic_Brother_port";
			// немного веселой жизни
			TraderHunterOnMap();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Romantic_Brother_2":
			NextDiag.TempNode = "Romantic_Brother_2";
			dialog.text = StringFromKey("BrigCaptain_12");
			link.l1 = StringFromKey("BrigCaptain_13");
			link.l1.go = "exit";
		break;

		case "Romantic_Brother_port_1":
			NextDiag.TempNode = "Romantic_Brother_2";
			dialog.text = StringFromKey("BrigCaptain_14");
			link.l1 = StringFromKey("BrigCaptain_15");
			link.l1.go = "Step_2";
		break;
		case "Step_2":
			RemovePassenger(pchar, NPChar);
			Pchar.quest.Romantic_Brother_House.win_condition.l1 = "location";
			Pchar.quest.Romantic_Brother_House.win_condition.l1.location = "SanJuan_houseSp6";
			Pchar.quest.Romantic_Brother_House.win_condition = "Romantic_Brother_House";
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseSp6", "", "goto", "goto4", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Romantic_Brother_Thanks":
			NextDiag.TempNode = "Romantic_Brother_Thanks";
			dialog.text = StringFromKey("BrigCaptain_16");
			link.l1 = StringFromKey("BrigCaptain_17");
			link.l1.go = "Step_3";
		break;
		case "Step_3":
			dialog.text = StringFromKey("BrigCaptain_18");
			link.l1 = StringFromKey("BrigCaptain_19");
			link.l1.go = "exit";
		break;
		//разборки Сальватора с братом
		case "TalkNearHouse_1":
			dialog.text = StringFromKey("BrigCaptain_20");
			link.l1 = StringFromKey("BrigCaptain_21");
			link.l1.go = "TalkNearHouse_2";
		break;
		case "TalkNearHouse_2":
			dialog.text = StringFromKey("BrigCaptain_22");
			link.l1 = StringFromKey("BrigCaptain_23");
			link.l1.go = "TalkNearHouse_3";
		break;
		case "TalkNearHouse_3":
			DialogExit();
			AddDialogExitQuest("Romantic_DeadBrother_1");
		break;
		//офицер в доме Сальватора при аресте
		case "ArrestInHome_2":
			ref rColony = GetColonyByIndex(FindColony("SanJuan"));
			if (sti(rColony.HeroOwn))
			{
				dialog.text = StringFromKey("BrigCaptain_24");
				link.l1 = StringFromKey("BrigCaptain_25");
				link.l1.go = "ArrestInHome_5";
			}
			else
			{
				dialog.text = StringFromKey("BrigCaptain_26", GetFullName(pchar));
				link.l1 = StringFromKey("BrigCaptain_27");
				link.l1.go = "ArrestInHome_3";
			}
		break;
		case "ArrestInHome_3":
			dialog.text = StringFromKey("BrigCaptain_28");
			if (CheckCharacterItem(pchar, "Order"))
			{
				link.l1 = StringFromKey("BrigCaptain_29");
				link.l1.go = "ArrestInHome_Have";
			}
			else
			{
				link.l1 = StringFromKey("BrigCaptain_30");
				link.l1.go = "ArrestInHome_NotHave";
			}
		break;
		case "ArrestInHome_Have":
			dialog.text = StringFromKey("BrigCaptain_31");
			link.l1 = StringFromKey("BrigCaptain_32");
			link.l1.go = "ArrestInHome_4";
		break;
		case "ArrestInHome_4":
			dialog.text = StringFromKey("BrigCaptain_33");
			link.l1 = StringFromKey("BrigCaptain_34");
			link.l1.go = "FightInHouse";
		break;

		case "ArrestInHome_NotHave":
			dialog.text = StringFromKey("BrigCaptain_35");
			link.l1 = StringFromKey("BrigCaptain_36");
			link.l1.go = "ArrestInHome_5";
		break;
		case "ArrestInHome_5":
			dialog.text = StringFromKey("BrigCaptain_37");
			link.l1 = StringFromKey("BrigCaptain_38");
			link.l1.go = "FightInHouse";
		break;

		case "FightInHouse":
			DialogExit();
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_LocationFightDisable(&Locations[FindLocation("SanJuan_houseSp6")], false);
			AddQuestRecord("Romantic_Line", "10");
		break;

		case "ArrestInHome_5":
			dialog.text = StringFromKey("BrigCaptain_39");
			link.l1 = StringFromKey("BrigCaptain_40");
			link.l1.go = "exit";
			AddQuestRecord("Romantic_Line", "31");
		break;
		//засада в доме Сальватора, диалог с наёмным убийцей
		case "AmbushBandit":
			dialog.text = StringFromKey("BrigCaptain_41");
			link.l1 = StringFromKey("BrigCaptain_42");
			link.l1.go = "AmbushBandit_1";
		break;
		case "AmbushBandit_1":
			dialog.text = StringFromKey("BrigCaptain_43");
			link.l1 = StringFromKey("BrigCaptain_44");
			link.l1.go = "AmbushBandit_fight";
		break;
		case "AmbushBandit_fight":
			LAi_LocationFightDisable(&locations[FindLocation("SanJuan_houseSp6")], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Romantic_Line", "12");
		break;
		//абордаж брига, где Изабеллу типа держат
		case "BrigAbordage":
			dialog.text = StringFromKey("BrigCaptain_45");
			link.l1 = StringFromKey("BrigCaptain_46");
			link.l1.go = "BrigAbordage_1";
		break;
		case "BrigAbordage_1":
			dialog.text = StringFromKey("BrigCaptain_47");
			link.l1 = StringFromKey("BrigCaptain_48");
			link.l1.go = "BrigAbordage_2";
		break;
		case "BrigAbordage_2":
			dialog.text = StringFromKey("BrigCaptain_49");
			link.l1 = StringFromKey("BrigCaptain_50");
			link.l1.go = "BrigAbordage_3";
		break;
		case "BrigAbordage_3":
			dialog.text = StringFromKey("BrigCaptain_51");
			link.l1 = StringFromKey("BrigCaptain_52");
			link.l1.go = "BrigAbordage_4";
		break;
		case "BrigAbordage_4":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("Romantic_TaklInCabinBrig");
			pchar.quest.Romantic_BrigDieHard.over = "yes";
			pchar.quest.Romantic_AfterBrigSunk.over = "yes";
			Island_SetReloadEnableGlobal("PortoBello", true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//засада в Портобело
		case "AmbushPotroBello":
			dialog.text = StringFromKey("BrigCaptain_53");
			link.l1 = StringFromKey("BrigCaptain_54");
			link.l1.go = "AmbushPotroBello_1";
		break;
		case "AmbushPotroBello_1":
			dialog.text = StringFromKey("BrigCaptain_55");
			link.l1 = StringFromKey("BrigCaptain_56");
			link.l1.go = "AmbushPotroBello_2";
		break;
		case "AmbushPotroBello_2":
			dialog.text = StringFromKey("BrigCaptain_57");
			link.l1 = StringFromKey("BrigCaptain_58");
			link.l1.go = "AmbushPotroBello_3";
		break;
		case "AmbushPotroBello_3":
			dialog.text = StringFromKey("BrigCaptain_59");
			link.l1 = StringFromKey("BrigCaptain_60");
			link.l1.go = "AmbushPotroBello_4";
		break;
		case "AmbushPotroBello_4":
			dialog.text = StringFromKey("BrigCaptain_61");
			link.l1 = StringFromKey("BrigCaptain_62");
			link.l1.go = "AmbushPotroBello_5";
		break;
		case "AmbushPotroBello_5":
			dialog.text = StringFromKey("BrigCaptain_63");
			link.l1 = StringFromKey("BrigCaptain_64");
			link.l1.go = "AmbushPotroBello_6";
		break;
		case "AmbushPotroBello_6":
			dialog.text = StringFromKey("BrigCaptain_65");
			link.l1 = StringFromKey("BrigCaptain_66");
			link.l1.go = "AmbushPotroBello_7";
		break;
		case "AmbushPotroBello_7":
			LAi_LocationFightDisable(&locations[FindLocation("PortoBello_houseF2")], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Romantic_TalkPortoBello");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//доставка Изабеллы Росите в Белиз
		case "Rosita":
			dialog.text = StringFromKey("BrigCaptain_67");
			link.l1 = StringFromKey("BrigCaptain_68", GetFullName(pchar));
			link.l1.go = "Rosita_1";
		break;
		case "Rosita_1":
			dialog.text = StringFromKey("BrigCaptain_69");
			link.l1 = StringFromKey("BrigCaptain_70");
			link.l1.go = "Rosita_2";
		break;
		case "Rosita_2":
			dialog.text = StringFromKey("BrigCaptain_71");
			link.l1 = StringFromKey("BrigCaptain_72");
			link.l1.go = "Rosita_3";
		break;
		case "Rosita_3":
			dialog.text = StringFromKey("BrigCaptain_73");
			link.l1 = StringFromKey("BrigCaptain_74");
			link.l1.go = "Rosita_4";
		break;
		case "Rosita_4":
			dialog.text = StringFromKey("BrigCaptain_75");
			link.l1 = StringFromKey("BrigCaptain_76");
			link.l1.go = "Rosita_5";
		break;
		case "Rosita_5":
			dialog.text = StringFromKey("BrigCaptain_77");
			link.l1 = StringFromKey("BrigCaptain_78");
			link.l1.go = "Rosita_6";
		break;
		case "Rosita_6":
			dialog.text = StringFromKey("BrigCaptain_79", pchar.name);
			link.l1 = StringFromKey("BrigCaptain_80");
			link.l1.go = "exit";
			NextDiag.TempNode = "Rosita_after";
			Pchar.quest.Romantic_BelizCityTalk.win_condition.l1 = "location";
			Pchar.quest.Romantic_BelizCityTalk.win_condition.l1.location = "Beliz_town";
			Pchar.quest.Romantic_BelizCityTalk.win_condition = "Romantic_BelizCityTalk";
			//снимем прерывания на засады на всякий случай
			pchar.quest.Romantic_AmbushInHouse.over = "yes";
			pchar.quest.Romantic_AmbushInPortoBello.over = "yes";
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
			RemoveLandQuestmark_Main(CharacterFromID("PortoBello_tavernkeeper"), "Romantic_Line");
		break;
		case "Rosita_after":
			dialog.text = StringFromKey("BrigCaptain_81", GetFullName(pchar));
			link.l1 = StringFromKey("BrigCaptain_82");
			link.l1.go = "exit";
			NextDiag.TempNode = "Rosita_after";
		break;
		//Росита переживает, что Изабелла пропала
		case "BackRosita":
			dialog.text = StringFromKey("BrigCaptain_83", pchar.name);
			link.l1 = StringFromKey("BrigCaptain_84");
			link.l1.go = "BackRosita_1";
		break;
		case "BackRosita_1":
			dialog.text = StringFromKey("BrigCaptain_85");
			link.l1 = StringFromKey("BrigCaptain_86");
			link.l1.go = "BackRosita_2";
		break;
		case "BackRosita_2":
			dialog.text = StringFromKey("BrigCaptain_87");
			link.l1 = StringFromKey("BrigCaptain_88");
			link.l1.go = "BackRosita_3";
		break;
		case "BackRosita_3":
			dialog.text = StringFromKey("BrigCaptain_89");
			link.l1 = StringFromKey("BrigCaptain_90");
			link.l1.go = "exit";
			NextDiag.TempNode = "BackRosita_after";
			pchar.RomanticQuest = "SeekIsabella";
			pchar.quest.SeekIsabella_exitTown.win_condition.l1 = "locator";
			pchar.quest.SeekIsabella_exitTown.win_condition.l1.location = "Beliz_ExitTown";
			pchar.quest.SeekIsabella_exitTown.win_condition.l1.locator_group = "quest";
			pchar.quest.SeekIsabella_exitTown.win_condition.l1.locator = "detector1";
			pchar.quest.SeekIsabella_exitTown.function = "SeekIsabella_exitTown";
			AddQuestRecord("Romantic_Line", "21");
			//мёртвая служанка
			sld = GetCharacter(NPC_GenerateCharacter("ServantGirl", "q_girl_servant", "woman", "towngirl", 5, SPAIN, 30, false));
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			LAi_ActorSetLayMode(sld);
			ChangeCharacterAddressGroup(sld, "Beliz_ExitTown", "goto", "goto17");
			locations[FindLocation("Beliz_ExitTown")].DisableEncounters = true; //энкаутеры запретим
			//охранник Изабеллы в шахте
			sld = GetCharacter(NPC_GenerateCharacter("Bandit", "officer_12", "man", "man", 35, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 35, 85, 75, "topor2", "pistol3", 60);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			ChangeCharacterAddressGroup(sld, "Beliz_Cave_2", "goto", "goto4");
			LAi_LocationDisableOfficersGen("Beliz_Cave_2", true); //офицеров не пускать
			LAi_LocationDisableMonstersGen("Beliz_Cave_2", true); //монстров не генерить
			pchar.quest.Romantic_BanditIsDead.win_condition.l1 = "NPC_Death";
			pchar.quest.Romantic_BanditIsDead.win_condition.l1.character = "Bandit";
			pchar.quest.Romantic_BanditIsDead.win_condition = "Romantic_BanditIsDead";
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
		break;
		case "BackRosita_after":
			dialog.text = StringFromKey("BrigCaptain_91");
			link.l1 = StringFromKey("BrigCaptain_92");
			link.l1.go = "exit";
		break;
		//если Изабелла погибла где-нить при похищении
		case "IsabellaIsDead_Beliz":
			dialog.text = StringFromKey("BrigCaptain_93");
			link.l1 = StringFromKey("BrigCaptain_94");
			link.l1.go = "IsabellaIsDead_Beliz_1";
			NextDiag.TempNode = "IsabellaIsDead_Beliz_after";
		break;
		case "IsabellaIsDead_Beliz_1":
			dialog.text = StringFromKey("BrigCaptain_95");
			link.l1 = StringFromKey("BrigCaptain_96");
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
		break;
		case "IsabellaIsDead_Beliz_after":
			dialog.text = StringFromKey("BrigCaptain_97");
			link.l1 = StringFromKey("BrigCaptain_98");
			link.l1.go = "exit";
		break;
		//после спасения Изабеллы в пещере
		case "SavedIsabella":
			dialog.text = StringFromKey("BrigCaptain_99");
			link.l1 = StringFromKey("BrigCaptain_100");
			link.l1.go = "SavedIsabella_1";
		break;
		case "SavedIsabella_1":
			dialog.text = StringFromKey("BrigCaptain_101");
			link.l1 = StringFromKey("BrigCaptain_102");
			link.l1.go = "SavedIsabella_2";
		break;
		case "SavedIsabella_2":
			dialog.text = StringFromKey("BrigCaptain_103");
			link.l1 = StringFromKey("BrigCaptain_104");
			link.l1.go = "SavedIsabella_3";
		break;
		case "SavedIsabella_3":
			dialog.text = StringFromKey("BrigCaptain_105");
			link.l1 = StringFromKey("BrigCaptain_106");
			link.l1.go = "SavedIsabella_4";
		break;
		case "SavedIsabella_4":
			dialog.text = StringFromKey("BrigCaptain_107");
			link.l1 = StringFromKey("BrigCaptain_108");
			link.l1.go = "SavedIsabella_5";
		break;
		case "SavedIsabella_5":
			dialog.text = StringFromKey("BrigCaptain_109");
			link.l1 = StringFromKey("BrigCaptain_110");
			link.l1.go = "exit";
			NextDiag.TempNode = "SavedIsabella_after";
			AddDialogExitQuest("Romantic_DelivToRosita_2");
		break;
		case "SavedIsabella_after":
			dialog.text = StringFromKey("BrigCaptain_111");
			link.l1 = StringFromKey("BrigCaptain_112");
			link.l1.go = "exit";
			NextDiag.TempNode = "SavedIsabella_after";
		break;
		//Нападения на ГГ и Изабеллу в церкви
		case "AmbushInChurch":
			dialog.text = StringFromKey("BrigCaptain_113");
			link.l1 = StringFromKey("BrigCaptain_114");
			link.l1.go = "AmbushInChurch_1";
		break;
		case "AmbushInChurch_1":
			dialog.text = StringFromKey("BrigCaptain_115");
			link.l1 = StringFromKey("BrigCaptain_116");
			link.l1.go = "AmbushInChurch_2";
		break;
		case "AmbushInChurch_2":
			dialog.text = StringFromKey("BrigCaptain_117");
			link.l1 = StringFromKey("BrigCaptain_118");
			link.l1.go = "exit";
			AddDialogExitQuest("Romantic_fightInChurch_1");
		break;
		//базар с Роситой после убийства Изабеллы
		case "IsabellaIsDead":
			dialog.text = StringFromKey("BrigCaptain_119", GetFullName(pchar));
			link.l1 = StringFromKey("BrigCaptain_120");
			link.l1.go = "IsabellaIsDead_1";
		break;
		case "IsabellaIsDead_1":
			dialog.text = StringFromKey("BrigCaptain_121");
			link.l1 = StringFromKey("BrigCaptain_122");
			link.l1.go = "IsabellaIsDead_2";
		break;
		case "IsabellaIsDead_2":
			dialog.text = StringFromKey("BrigCaptain_123");
			link.l1 = StringFromKey("BrigCaptain_124");
			link.l1.go = "exit";
			npchar.LifeDay = 0;
			NextDiag.TempNode = "IsabellaIsDead_after";
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
		break;
		case "IsabellaIsDead_after":
			dialog.text = StringFromKey("BrigCaptain_125");
			link.l1 = StringFromKey("BrigCaptain_126");
			link.l1.go = "exit";
			NextDiag.TempNode = "IsabellaIsDead_after";
		break;
		//базар с Роситой, если ГГ отбился в церкви
		case "IsabellaIsMyWife":
			dialog.text = StringFromKey("BrigCaptain_127", pchar.name);
			link.l1 = StringFromKey("BrigCaptain_128");
			link.l1.go = "IsabellaIsMyWife_1";
		break;
		case "IsabellaIsMyWife_1":
			dialog.text = StringFromKey("BrigCaptain_129");
			link.l1 = StringFromKey("BrigCaptain_130");
			link.l1.go = "IsabellaIsMyWife_2";
		break;
		case "IsabellaIsMyWife_2":
			dialog.text = StringFromKey("BrigCaptain_131", pchar.name);
			link.l1 = StringFromKey("BrigCaptain_132");
			link.l1.go = "exit";
			NextDiag.TempNode = "IsabellaIsMyWife_after";
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
		break;
		case "IsabellaIsMyWife_after":
			dialog.text = StringFromKey("BrigCaptain_133", pchar.name);
			link.l1 = StringFromKey("BrigCaptain_134");
			link.l1.go = "exit";
			NextDiag.TempNode = "IsabellaIsMyWife_after";
		break;
		//семейная жизнь ГГ
		case "IsabellaIsWife":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("BrigCaptain_135", pchar.name),
						StringFromKey("BrigCaptain_136"),
						StringFromKey("BrigCaptain_137", pchar.name),
						StringFromKey("BrigCaptain_138"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("BrigCaptain_139"),
						StringFromKey("BrigCaptain_140"),
						StringFromKey("BrigCaptain_141"),
						StringFromKey("BrigCaptain_142"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("IsabellaIsWife_1", "none", "none", "none", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "IsabellaIsWife";
		break;
		case "IsabellaIsWife_1":
			dialog.text = StringFromKey("BrigCaptain_143");
			link.l1 = StringFromKey("BrigCaptain_144");
			link.l1.go = "exit";
			if (pchar.RomanticQuest == "over")
			{
				link.l2 = StringFromKey("BrigCaptain_145");
				link.l2.go = "HorseCheck";
				break;
			}
			if (pchar.RomanticQuest == "TheDoosIsClosed")
			{
				link.l2 = StringFromKey("BrigCaptain_146");
				link.l2.go = "TheDoosIsClosed";
			}
			sld = characterFromID("Isabella");
			if (CheckAttribute(sld, "angry")) //если Изабелла сидит на ангри
			{
				if (sld.angry.name == "NewLife_Budget_Pay")
				{
					link.l3 = StringFromKey("BrigCaptain_147");
					link.l3.go = "Budget";
				}
				if (sld.angry.name == "NewLife_KnowPirates")
				{
					link.l4 = StringFromKey("BrigCaptain_148");
					link.l4.go = "KnowPirates";
				}
				if (sld.angry.name == "NewLife_Present")
				{
					link.l5 = StringFromKey("BrigCaptain_149");
					link.l5.go = "Present";
				}
			}
		break;
		case "TheDoosIsClosed":
			dialog.text = StringFromKey("BrigCaptain_150");
			link.l1 = StringFromKey("BrigCaptain_151");
			link.l1.go = "TheDoosIsClosed_1";
		break;
		case "TheDoosIsClosed_1":
			dialog.text = StringFromKey("BrigCaptain_152");
			link.l1 = StringFromKey("BrigCaptain_153");
			link.l1.go = "TheDoosIsClosed_2";
		break;
		case "TheDoosIsClosed_2":
			dialog.text = StringFromKey("BrigCaptain_154", pchar.name);
			link.l1 = StringFromKey("BrigCaptain_155");
			link.l1.go = "exit";
			AddQuestRecord("Romantic_Line", "30");
			CloseQuestHeader("Romantic_Line");
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false);
			pchar.RomanticQuest = "OpenTheDoosOfHouse";
		break;

		case "Budget":
			dialog.text = StringFromKey("BrigCaptain_156");
			link.l1 = StringFromKey("BrigCaptain_157");
			link.l1.go = "Budget_1";
		break;
		case "Budget_1":
			dialog.text = StringFromKey("BrigCaptain_158");
			link.l1 = StringFromKey("BrigCaptain_159");
			link.l1.go = "exit";
		break;

		case "KnowPirates":
			dialog.text = StringFromKey("BrigCaptain_160", pchar.name);
			link.l1 = StringFromKey("BrigCaptain_161");
			link.l1.go = "KnowPirates_1";
		break;
		case "KnowPirates_1":
			dialog.text = StringFromKey("BrigCaptain_162");
			link.l1 = StringFromKey("BrigCaptain_163");
			link.l1.go = "KnowPirates_2";
		break;
		case "KnowPirates_2":
			dialog.text = StringFromKey("BrigCaptain_164");
			link.l1 = StringFromKey("BrigCaptain_165");
			link.l1.go = "KnowPirates_3";
		break;
		case "KnowPirates_3":
			dialog.text = StringFromKey("BrigCaptain_166");
			link.l1 = StringFromKey("BrigCaptain_167");
			link.l1.go = "exit";
		break;

		case "Present":
			dialog.text = StringFromKey("BrigCaptain_168");
			link.l1 = StringFromKey("BrigCaptain_169");
			link.l1.go = "Present_1";
		break;
		case "Present_1":
			dialog.text = StringFromKey("BrigCaptain_170");
			link.l1 = StringFromKey("BrigCaptain_171");
			link.l1.go = "Present_2";
		break;
		case "Present_2":
			dialog.text = StringFromKey("BrigCaptain_172");
			link.l1 = StringFromKey("BrigCaptain_173");
			link.l1.go = "Present_3";
		break;
		case "Present_3":
			dialog.text = StringFromKey("BrigCaptain_174");
			link.l1 = StringFromKey("BrigCaptain_175");
			link.l1.go = "exit";
		break;

		case "HorseCheck":
			dialog.text = StringFromKey("BrigCaptain_176");
			link.l1 = StringFromKey("BrigCaptain_177");
			link.l1.go = "HorseCheck_1";
		break;
		case "HorseCheck_1":
			dialog.text = StringFromKey("BrigCaptain_178");
			link.l1 = StringFromKey("BrigCaptain_179");
			link.l1.go = "HorseCheck_2";
		break;
		case "HorseCheck_2":
			dialog.text = StringFromKey("BrigCaptain_180");
			link.l1 = StringFromKey("BrigCaptain_181");
			link.l1.go = "HorseCheck_3";
		break;
		case "HorseCheck_3":
			dialog.text = StringFromKey("BrigCaptain_182");
			link.l1 = StringFromKey("BrigCaptain_183");
			link.l1.go = "HorseCheck_4";
		break;
		case "HorseCheck_4":
			dialog.text = StringFromKey("BrigCaptain_184");
			link.l1 = StringFromKey("BrigCaptain_185");
			link.l1.go = "exit";
			npchar.LifeDay = 0;
			NextDiag.TempNode = "HorseCheck_Bue";
			CloseQuestHeader("Romantic_Line");
			ChangeCharacterReputation(pchar, -10);
		break;
		case "HorseCheck_Bue":
			dialog.text = StringFromKey("BrigCaptain_186");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "HorseCheck_Bue";
		break;
	}
}

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Exit_minus_rep":
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(pchar, -12);
			DialogExit();
		break;

		case "First time":
			if (PChar.sex != "woman")
			{
				dialog.text = StringFromKey("Atilla_1", GetFullName(PChar));
				link.l1 = StringFromKey("Atilla_2");
				link.l1.go = "port_1";
				link.l2 = StringFromKey("Atilla_3");
				link.l2.go = "M_exit";
			}
			else
			{
				dialog.text = StringFromKey("Atilla_4", GetFullName(PChar));
				link.l1 = StringFromKey("Atilla_5");
				link.l1.go = "W_exit";
			}
			NextDiag.TempNode = "First time";
			DeleteAttribute(npchar, "talker"); //снимаем говорилку
			npchar.NoCheckFightMode = true;//чтобы гг не убирал саблю, наткнувшись на этого нпс, так как не сможет с ним заговорить
		break;

		case "W_exit":
			NPChar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
			RemoveMapQuestMark("Pirates_town", "Romantic_Line");
		break;

		case "M_exit":
			NextDiag.TempNode = "First time";
			//NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		/*case "CitizenNotBlade": //HardCoffee ref CitizenNotBlade
			dialog.text = PChar.name + StringFromKey("Atilla_6");
			link.l1 = LinkRandPhrase(StringFromKey("Atilla_7"), StringFromKey("Atilla_8"), StringFromKey("Atilla_9"));
			link.l1.go = "exit_HideBlade";
		break;
		case "exit_HideBlade":
    		NextDiag.CurrentNode = NextDiag.TempNode;
    		DialogExit();
    		SendMessage(pchar, "lsl", MSG_CHARACTER_EX_MSG, "SetFightMode", 1);
    		LAi_SetFightMode(pchar, false);
    	break;*/

		case "port_1":
			sld = characterFromID("Atilla");
			dialog.text = StringFromKey("Atilla_6");
			if (pchar.RomanticQuest == "")
			{
				link.l1 = StringFromKey("Atilla_7");
				link.l1.go = "Exit";
			}
			else
			{
				link.l1 = StringFromKey("Atilla_8");
				link.l1.go = "port_1_1";
			}
		break;

		case "port_1_1":
			dialog.text = StringFromKey("Atilla_9");
			link.l1 = StringFromKey("Atilla_10");
			link.l1.go = "port_toTavern";
		break;

		case "port_toTavern":
			DialogExit();
			NextDiag.CurrentNode = "Tavern_1";
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			bDisableLandEncounters = true;
			FreeSitLocator("Pirates_tavern", "sit3");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Pirates_tavern", "sit", "sit3", "Romantic_Pirat_toTavern", -1);
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
			RemoveMapQuestMark("Pirates_town", "Romantic_Line");
		break;

		case "Tavern_1":
			LAi_SetSitType(Pchar);
			dialog.text = StringFromKey("Atilla_11", GetFullName(PChar));
			link.l1 = StringFromKey("Atilla_12");
			link.l1.go = "Tavern_2";
		break;

		case "Tavern_2":
			dialog.text = StringFromKey("Atilla_13");
			link.l1 = StringFromKey("Atilla_14");
			link.l1.go = "Tavern_3";
		break;

		case "Tavern_3":
			dialog.text = StringFromKey("Atilla_15");
			link.l1 = StringFromKey("Atilla_16");
			link.l1.go = "Tavern_4";
		break;

		case "Tavern_4":
			dialog.text = StringFromKey("Atilla_17");
			link.l1 = StringFromKey("Atilla_18");
			link.l1.go = "Tavern_5";
		break;

		case "Tavern_5":
			dialog.text = StringFromKey("Atilla_19");
			link.l1 = StringFromKey("Atilla_20");
			link.l1.go = "Tavern_6";
		break;

		case "Tavern_6":
			dialog.text = StringFromKey("Atilla_21");
			link.l1 = StringFromKey("Atilla_22");
			link.l1.go = "Tavern_Out";
		break;

		case "Tavern_Out":
			SetTimerConditionParam("Romantic_Atilla_Beer_Timer", "Romantic_Atilla_Beer_Timer", 0, 0, 0, MakeInt(GetHour() + 3), false);
			LAi_SetAlcoholState(1);
			NextDiag.CurrentNode = "Tavern_Bye";
			DialogExit();
			AddDialogExitQuest("Romantic_Pirat_toTavern_end");
		break;

		case "Tavern_Bye":
			NextDiag.TempNode = "Tavern_Bye";
			dialog.text = StringFromKey("Atilla_23");
			link.l1 = StringFromKey("Atilla_24");
			link.l1.go = "exit";
		break;
		//доводим новости до сведения Атиллы
		case "TalkingNews":
			dialog.text = StringFromKey("Atilla_25", GetFullName(pchar));
			link.l1 = StringFromKey("Atilla_26");
			link.l1.go = "TalkingNews_1";
		break;
		case "TalkingNews_1":
			dialog.text = StringFromKey("Atilla_27");
			link.l1 = StringFromKey("Atilla_28");
			link.l1.go = "TalkingNews_2";
		break;
		case "TalkingNews_2":
			dialog.text = StringFromKey("Atilla_29");
			link.l1 = StringFromKey("Atilla_30");
			link.l1.go = "TalkingNews_3";
		break;
		case "TalkingNews_3":
			dialog.text = StringFromKey("Atilla_31");
			link.l1 = StringFromKey("Atilla_32");
			link.l1.go = "TalkingNews_4";
		break;
		case "TalkingNews_4":
			dialog.text = StringFromKey("Atilla_33");
			link.l1 = StringFromKey("Atilla_34");
			link.l1.go = "TalkingNews_5";
		break;
		case "TalkingNews_5":
			dialog.text = StringFromKey("Atilla_35");
			link.l1 = StringFromKey("Atilla_36");
			link.l1.go = "TalkingNews_6";
		break;
		case "TalkingNews_6":
			dialog.text = StringFromKey("Atilla_37");
			link.l1 = StringFromKey("Atilla_38");
			link.l1.go = "TalkingNews_7";
		break;
		case "TalkingNews_7":
			dialog.text = StringFromKey("Atilla_39");
			link.l1 = StringFromKey("Atilla_40");
			link.l1.go = "TalkingNews_8";
		break;
		case "TalkingNews_8":
			dialog.text = StringFromKey("Atilla_41");
			link.l1 = StringFromKey("Atilla_42");
			link.l1.go = "TalkingNews_9";
		break;
		case "TalkingNews_9":
			if (GetBaseHeroNation() == FRANCE)
			{
				dialog.text = StringFromKey("Atilla_43");
				link.l1 = StringFromKey("Atilla_44");
				link.l1.go = "TalkingNews_11";
			}
			else
			{
				dialog.text = "L'amour... Qu'ici faire?..";
				link.l1 = StringFromKey("Atilla_45");
				link.l1.go = "TalkingNews_10";
			}
		break;
		case "TalkingNews_10":
			dialog.text = StringFromKey("Atilla_46");
			link.l1 = StringFromKey("Atilla_47");
			link.l1.go = "TalkingNews_11";
		break;
		case "TalkingNews_11":
			dialog.text = StringFromKey("Atilla_48");
			link.l1 = StringFromKey("Atilla_49");
			link.l1.go = "TalkingNews_12";
		break;
		case "TalkingNews_12":
			dialog.text = StringFromKey("Atilla_50");
			link.l1 = StringFromKey("Atilla_51");
			link.l1.go = "TalkingNews_13";
		break;
		case "TalkingNews_13":
			dialog.text = StringFromKey("Atilla_52");
			link.l1 = StringFromKey("Atilla_53");
			link.l1.go = "TalkingNews_14";
		break;
		case "TalkingNews_14":
			SetTimerCondition("Romantic_AtillaToHouse", 0, 2, 0, false);
			AddQuestRecord("Romantic_Line", "11");
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto2");
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			//открываем дом Сальватора и убираем Изабеллу, ставим наёмных убийц в дом.
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false);
			LocatorReloadEnterDisable("SanJuan_houseSp6", "reload2", false);
			ChangeCharacterAddress(characterFromId("Isabella"), "none", "");
			Pchar.quest.Romantic_AmbushInHouse.win_condition.l1 = "location";
			Pchar.quest.Romantic_AmbushInHouse.win_condition.l1.location = "SanJuan_houseSp6";
			Pchar.quest.Romantic_AmbushInHouse.win_condition = "Romantic_AmbushInHouse";
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
			RemoveLandQuestmark_Main(CharacterFromID("Pirates_tavernkeeper"), "Romantic_Line");
		break;
		//через два месяца по завершению поисков
		case "AtillaInHouse":
			dialog.text = StringFromKey("Atilla_54", GetFullName(pchar));
			link.l1 = StringFromKey("Atilla_55");
			link.l1.go = "AtillaInHouse_1";
		break;
		case "AtillaInHouse_1":
			dialog.text = StringFromKey("Atilla_56", pchar.name);
			link.l1 = StringFromKey("Atilla_57");
			link.l1.go = "AtillaInHouse_2";
		break;
		case "AtillaInHouse_2":
			dialog.text = StringFromKey("Atilla_58");
			link.l1 = StringFromKey("Atilla_59");
			link.l1.go = "AtillaInHouse_3";
		break;
		case "AtillaInHouse_3":
			dialog.text = StringFromKey("Atilla_60");
			link.l1 = StringFromKey("Atilla_61");
			link.l1.go = "AtillaInHouse_4";
		break;
		case "AtillaInHouse_4":
			dialog.text = StringFromKey("Atilla_62");
			link.l1 = StringFromKey("Atilla_63");
			link.l1.go = "AtillaInHouse_5";
		break;
		case "AtillaInHouse_5":
			dialog.text = StringFromKey("Atilla_64");
			link.l1 = StringFromKey("Atilla_65");
			link.l1.go = "AtillaInHouse_6";
		break;
		case "AtillaInHouse_6":
			dialog.text = StringFromKey("Atilla_66");
			link.l1 = StringFromKey("Atilla_67");
			link.l1.go = "AtillaInHouse_7";
		break;
		case "AtillaInHouse_7":
			dialog.text = StringFromKey("Atilla_68", pchar.name);
			link.l1 = StringFromKey("Atilla_69");
			link.l1.go = "exit";
			NextDiag.TempNode = "AtillaInHouse_Again";
			AddQuestRecord("Romantic_Line", "13");
			pchar.RomanticQuest = "AttackBrig"; //флаг для кэпа на абордаже брига
			Pchar.quest.Romantic_AttackBrig.win_condition.l1 = "location";
			Pchar.quest.Romantic_AttackBrig.win_condition.l1.location = "PortoBello";
			Pchar.quest.Romantic_AttackBrig.win_condition = "Romantic_AttackBrig";
			SetTimerCondition("Romantic_BrigTimeOver", 0, 0, 16, false);
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
			RemoveLandQuestmark_Main(CharacterFromID("Pirates_tavernkeeper"), "Romantic_Line");
		break;
		case "AtillaInHouse_Again":
			dialog.text = StringFromKey("Atilla_70");
			link.l1 = StringFromKey("Atilla_71");
			link.l1.go = "exit";
		break;
		// после погони за бригом Восторженный, если не догнал его вообще
		case "Brig_Late":
			dialog.text = StringFromKey("Atilla_72");
			link.l1 = StringFromKey("Atilla_73");
			link.l1.go = "Brig_Late_1";
		break;
		case "Brig_Late_1":
			dialog.text = StringFromKey("Atilla_74");
			link.l1 = StringFromKey("Atilla_75");
			link.l1.go = "Brig_Late_2";
		break;
		case "Brig_Late_2":
			dialog.text = StringFromKey("Atilla_76");
			link.l1 = StringFromKey("Atilla_77");
			link.l1.go = "exit";
			NextDiag.TempNode = "Last_Talk";
			CloseQuestHeader("Romantic_Line");
			DeleteAttribute(pchar, "RomanticQuest");
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
		break;
		case "Last_Talk":
			dialog.text = StringFromKey("Atilla_78");
			link.l1 = StringFromKey("Atilla_79");
			link.l1.go = "exit";
			NextDiag.TempNode = "Last_Talk";
		break;
		// если догнал бриг свалил или ГГ ушёл на карту
		case "Brig_DieHard":
			dialog.text = StringFromKey("Atilla_80");
			link.l1 = StringFromKey("Atilla_81");
			link.l1.go = "Brig_DieHard_1";
		break;
		case "Brig_DieHard_1":
			dialog.text = StringFromKey("Atilla_82");
			link.l1 = StringFromKey("Atilla_83");
			link.l1.go = "Brig_Late_2";
		break;
		// если догнал бриг, но утопил его
		case "Brig_Sunk":
			dialog.text = StringFromKey("Atilla_84");
			link.l1 = StringFromKey("Atilla_85");
			link.l1.go = "Brig_Sunk_1";
		break;
		case "Brig_Sunk_1":
			dialog.text = StringFromKey("Atilla_86");
			link.l1 = StringFromKey("Atilla_87");
			link.l1.go = "Brig_Late_2";
		break;
		// если Изабелла утонула с бригом, нет векселей
		case "Isabella_Sink":
			dialog.text = StringFromKey("Atilla_88");
			link.l1 = StringFromKey("Atilla_89");
			link.l1.go = "Isabella_Sink_1";
		break;
		case "Isabella_Sink_1":
			dialog.text = StringFromKey("Atilla_90");
			link.l1 = StringFromKey("Atilla_91");
			link.l1.go = "Brig_Late_2";
		break;
		// узнать что-нибудь новое о Сальватора
		case "SalvatorNews":
			dialog.text = StringFromKey("Atilla_92", GetFullName(pchar));
			link.l1 = StringFromKey("Atilla_93");
			link.l1.go = "SalvatorNews_1";
		break;
		case "SalvatorNews_1":
			dialog.text = StringFromKey("Atilla_94");
			link.l1 = StringFromKey("Atilla_95");
			link.l1.go = "SalvatorNews_2";
		break;
		case "SalvatorNews_2":
			dialog.text = StringFromKey("Atilla_96");
			link.l1 = StringFromKey("Atilla_97");
			link.l1.go = "SalvatorNews_3";
		break;
		case "SalvatorNews_3":
			dialog.text = StringFromKey("Atilla_98");
			link.l1 = StringFromKey("Atilla_99");
			link.l1.go = "SalvatorNews_4";
		break;
		case "SalvatorNews_4":
			dialog.text = StringFromKey("Atilla_100");
			link.l1 = StringFromKey("Atilla_101");
			link.l1.go = "SalvatorNews_5";
		break;
		case "SalvatorNews_5":
			dialog.text = StringFromKey("Atilla_102");
			link.l1 = StringFromKey("Atilla_103");
			link.l1.go = "SalvatorNews_6";
		break;
		case "SalvatorNews_6":
			dialog.text = StringFromKey("Atilla_104");
			link.l1 = StringFromKey("Atilla_105");
			link.l1.go = "exit";
			NextDiag.TempNode = "AtillaInHouse_Again";
			AddQuestRecord("Romantic_Line", "20");
			ChangeCharacterAddress(characterFromId("Isabella"), "none", "");
			QuestSetCurrentNode("Rosita", "BackRosita");
			AddLandQuestmark_Main(characterFromID("Rosita"), "Romantic_Line");
			//Изабеллу в шахту
			sld = characterFromId("Isabella");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Beliz_Cave_2", "goto", "goto5");
			sld.dialog.currentnode = "IsabellaInCave";
			AddLandQuestmark_Main(sld, "Romantic_Line");
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
		break;
		//Изабелла убита в церкви.
		case "IsabellaIsDead":
			dialog.text = StringFromKey("Atilla_106", GetFullName(pchar));
			link.l1 = StringFromKey("Atilla_107");
			link.l1.go = "IsabellaIsDead_1";
		break;
		case "IsabellaIsDead_1":
			dialog.text = StringFromKey("Atilla_108");
			link.l1 = StringFromKey("Atilla_109");
			link.l1.go = "IsabellaIsDead_2";
		break;
		case "IsabellaIsDead_2":
			NPChar.LifeDay = 1;
			dialog.text = StringFromKey("Atilla_110");
			link.l1 = StringFromKey("Atilla_111");
			link.l1.go = "exit";
			NextDiag.TempNode = "IsabellaIsDead_after";
			CloseQuestHeader("Romantic_Line");
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
		break;
		case "IsabellaIsDead_after":
			dialog.text = StringFromKey("Atilla_112");
			link.l1 = StringFromKey("Atilla_113");
			link.l1.go = "exit";
			NextDiag.TempNode = "IsabellaIsDead_after";
		break;
		//если ГГ отбился в церкви
		case "IsabellaIsMyWife":
			dialog.text = StringFromKey("Atilla_114");
			link.l1 = StringFromKey("Atilla_115");
			link.l1.go = "IsabellaIsMyWife_1";
			npchar.lifeDay = 0;
		break;
		case "IsabellaIsMyWife_1":
			dialog.text = StringFromKey("Atilla_116");
			link.l1 = StringFromKey("Atilla_117");
			link.l1.go = "IsabellaIsMyWife_2";
		break;
		case "IsabellaIsMyWife_2":
			dialog.text = StringFromKey("Atilla_118");
			link.l1 = StringFromKey("Atilla_119");
			link.l1.go = "Exit_minus_rep";
			if (sti(pchar.money) >= 1000)
			{
				link.l2 = StringFromKey("Atilla_120");
				link.l2.go = "IsabellaIsMyWife_3";
			}
			NextDiag.TempNode = "IsabellaIsMyWife_after";
			pchar.RomanticQuest.Atilla = "YouAreSwine";
			npchar.LifeDay = 0;
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
		break;
		case "IsabellaIsMyWife_after":
			dialog.text = StringFromKey("Atilla_121", pchar.name);
			link.l1 = StringFromKey("Atilla_122");
			link.l1.go = "exit";
			NextDiag.TempNode = "IsabellaIsMyWife_after";
		break;
		case "IsabellaIsMyWife_3":
			dialog.text = StringFromKey("Atilla_123");
			link.l1 = StringFromKey("Atilla_124");
			link.l1.go = "IsabellaIsMyWife_4";
		break;
		case "IsabellaIsMyWife_4":
			dialog.text = StringFromKey("Atilla_125");
			if (sti(pchar.money) >= 1000)
			{
				link.l1 = StringFromKey("Atilla_126");
				link.l1.go = "AddRepa_1";
			}
			if (sti(pchar.money) >= 70000)
			{
				link.l2 = StringFromKey("Atilla_127");
				link.l2.go = "AddRepa_2";
			}
			if (sti(pchar.money) >= 150000)
			{
				link.l3 = StringFromKey("Atilla_128");
				link.l3.go = "AddRepa_3";
			}
			if (sti(pchar.money) >= 300000)
			{
				link.l4 = StringFromKey("Atilla_129");
				link.l4.go = "AddRepa_4";
			}
		break;
		case "AddRepa_1":
			dialog.text = StringFromKey("Atilla_130", pchar.name);
			link.l1 = StringFromKey("Atilla_131");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000);
			ChangeCharacterReputation(pchar, -10);
		break;
		case "AddRepa_2":
			dialog.text = StringFromKey("Atilla_132", GetFullName(pchar));
			link.l1 = StringFromKey("Atilla_133");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -70000);
			pchar.RomanticQuest.Atilla = "YouAreNormal";
			ChangeCharacterReputation(pchar, 5);
		break;
		case "AddRepa_3":
			dialog.text = StringFromKey("Atilla_134");
			link.l1 = StringFromKey("Atilla_135");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -150000);
			pchar.RomanticQuest.Atilla = "YouAreNormal";
			ChangeCharacterReputation(pchar, 15);
		break;
		case "AddRepa_4":
			dialog.text = StringFromKey("Atilla_136");
			link.l1 = StringFromKey("Atilla_137");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -300000);
			pchar.RomanticQuest.Atilla = "YouAreGood";
			ChangeCharacterReputation(pchar, 30);
		break;
	}
}

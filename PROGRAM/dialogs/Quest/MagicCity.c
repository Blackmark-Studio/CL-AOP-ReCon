void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp, i;

	switch (Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = StringFromKey("MagicCity_1");
			link.l1 = StringFromKey("MagicCity_2");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_orient":
			for (i = 1; i <= 12; i++)
			{
				sld = characterFromId("CaracasCit_" + i);
				LAi_ActorStay(sld);
				RemoveLandQuestMark_Main(sld, "MagicCity");
			}
			LAi_ActorTurnByLocator(npchar, npchar.location.group, npchar.location.locator);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//замечение по обнаженному оружию
		/*case "CitizenNotBlade": //HardCoffee ref CitizenNotBlade
			dialog.text = StringFromKey("MagicCity_3");
			link.l1 = LinkRandPhrase(StringFromKey("MagicCity_4"), StringFromKey("MagicCity_5"), StringFromKey("MagicCity_6"));
			link.l1.go = "exit";
			NextDiag.TempNode = "DesMoinesCitizen";
		break;*/

		//бунтующие горожане в Каракасе
		case "CaracasMan":
			dialog.text = StringFromKey("MagicCity_3", pchar);
			link.l1 = StringFromKey("MagicCity_4");
			link.l1.go = "CaracasMan_1";
		break;
		case "CaracasMan_1":
			dialog.text = StringFromKey("MagicCity_5");
			link.l1 = StringFromKey("MagicCity_6");
			link.l1.go = "CaracasMan_2";
		break;
		case "CaracasMan_2":
			dialog.text = StringFromKey("MagicCity_7");
			link.l1 = StringFromKey("MagicCity_8");
			link.l1.go = "CaracasMan_3";
		break;
		case "CaracasMan_3":
			dialog.text = StringFromKey("MagicCity_9");
			link.l1 = StringFromKey("MagicCity_10");
			link.l1.go = "exit_orient";
			DeleteAttribute(&locations[reload_location_index], "reload.l41.disable");
		break;
		//оборотень в Каракасе
		case "CaracasWervolf":
			PlayVoice("Voice\" + VoiceGetLanguage() + "\Slave01.wav");
			dialog.text = StringFromKey("MagicCity_11");
			link.l1 = StringFromKey("MagicCity_12", GetFullName(pchar));
			link.l1.go = "CaracasWervolf_1";
		break;
		case "CaracasWervolf_1":
			dialog.text = StringFromKey("MagicCity_13");
			link.l1 = StringFromKey("MagicCity_14");
			link.l1.go = "CaracasWervolf_2";
		break;
		case "CaracasWervolf_2":
			dialog.text = StringFromKey("MagicCity_15");
			link.l1 = StringFromKey("MagicCity_16", pchar);
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			pchar.questTemp.MC = "toCaracasPadre";
			iTemp = FindLocation("Caracas_tavern");
			DeleteAttribute(&locations[iTemp], "reload.l1.disable");
			DeleteAttribute(&locations[iTemp], "reload.l4.disable");
			LocatorReloadEnterDisable("Caracas_town", "reload7_back", false);
			locations[iTemp].reload.l2.disable = true;
			for (i = 1; i <= 12; i++)
			{
				sld = characterFromId("CaracasCit_" + i);
				sld.dialog.currentnode = "CaracasMan2";
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorWaitDialog(sld, pchar);
			}
			RemoveLandQuestMark_Main(npchar, "MagicCity");
			AddLandQuestMark_Main(characterFromId("Caracas_Priest"), "MagicCity");
		break;
		//горожане Каракаса на выходе из таверны
		case "CaracasMan2":
			dialog.text = StringFromKey("MagicCity_17");
			link.l1 = StringFromKey("MagicCity_18");
			link.l1.go = "exit_orient";
		break;
		//охрана Дес-Мойнеса в бухте
		case "ShoreGuard":
			dialog.text = StringFromKey("MagicCity_19");
			link.l1 = StringFromKey("MagicCity_20");
			link.l1.go = "ShoreGuard_1";
		break;
		case "ShoreGuard_1":
			dialog.text = StringFromKey("MagicCity_21", pchar);
			link.l1 = StringFromKey("MagicCity_22");
			link.l1.go = "ShoreGuard_2";
		break;
		case "ShoreGuard_2":
			dialog.text = StringFromKey("MagicCity_23");
			link.l1 = StringFromKey("MagicCity_24");
			link.l1.go = "ShoreGuard_3";
		break;
		case "ShoreGuard_3":
			LocatorReloadEnterDisable("Shore_ship3", "reload1", false);
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_group_SetRelation("MC_DesMoinesInShore_Guards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("MC_DesMoinesInShore_Guards", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("MC_DesMoinesInShore_Guards", "OpenTheDoors");
			LAi_group_SetCheckFunction("MC_DesMoinesInShore_Guards", "MC_DesMoinesInShore_GuardsDead");
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;
		//жители Дес-Мойнеса обычные
		case "DMCitiz":
			NextDiag.TempNode = "DMCitiz";
			dialog.text = StringFromKey("MagicCity_28", LinkRandPhrase(
						StringFromKey("MagicCity_25"),
						StringFromKey("MagicCity_26"),
						StringFromKey("MagicCity_27")));
			link.l1 = StringFromKey("MagicCity_29");
			link.l1.go = "DesMoinesCitizen_1";
			if (pchar.questTemp.MC == "toByeBye")
			{
				dialog.text = StringFromKey("MagicCity_33", LinkRandPhrase(
							StringFromKey("MagicCity_30", pchar),
							StringFromKey("MagicCity_31", pchar),
							StringFromKey("MagicCity_32")));
				link.l1 = StringFromKey("MagicCity_34");
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSister" || pchar.questTemp.MC == "toSeekSkull" || pchar.questTemp.MC == "toSeekQueen")
			{
				dialog.text = StringFromKey("MagicCity_38", LinkRandPhrase(
							StringFromKey("MagicCity_35"),
							StringFromKey("MagicCity_36", pchar, GetAddress_Form(NPChar)),
							StringFromKey("MagicCity_37")));
				link.l1 = StringFromKey("MagicCity_39");
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "over")
			{
				dialog.text = StringFromKey("MagicCity_40", pchar, UpperFirst(GetAddress_Form(NPChar)));
				link.l1 = StringFromKey("MagicCity_41", pchar);
				link.l1.go = "exit";
			}
		break;
		case "DesMoinesCitizen_1":
			dialog.text = StringFromKey("MagicCity_42");
			link.l1 = StringFromKey("MagicCity_43");
			link.l1.go = "DesMoinesCitizen_2";
		break;
		case "DesMoinesCitizen_2":
			dialog.text = StringFromKey("MagicCity_44");
			link.l1 = StringFromKey("MagicCity_45");
			link.l1.go = "exit";
		break;
		//жители Дес-Мойнеса скелеты
		case "DMSkel":
			NextDiag.TempNode = "DMSkel";
			dialog.text = StringFromKey("MagicCity_49", LinkRandPhrase(
						StringFromKey("MagicCity_46"),
						StringFromKey("MagicCity_47"),
						StringFromKey("MagicCity_48")));
			link.l1 = StringFromKey("MagicCity_50");
			link.l1.go = "DesMoinesSkel_1";
			if (pchar.questTemp.MC == "toByeBye")
			{
				dialog.text = StringFromKey("MagicCity_54", LinkRandPhrase(
							StringFromKey("MagicCity_51", pchar),
							StringFromKey("MagicCity_52", pchar),
							StringFromKey("MagicCity_53")));
				link.l1 = StringFromKey("MagicCity_55");
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSister" || pchar.questTemp.MC == "toSeekSkull" || pchar.questTemp.MC == "toSeekQueen")
			{
				dialog.text = StringFromKey("MagicCity_59", LinkRandPhrase(
							StringFromKey("MagicCity_56"),
							StringFromKey("MagicCity_57", GetAddress_Form(NPChar)),
							StringFromKey("MagicCity_58")));
				link.l1 = StringFromKey("MagicCity_60");
				link.l1.go = "exit";
			}
		break;
		case "DesMoinesSkel_1":
			dialog.text = StringFromKey("MagicCity_61");
			link.l1 = StringFromKey("MagicCity_62");
			link.l1.go = "exit";
			LocatorReloadEnterDisable("DesMoines_town", "reload1_back", true);
		break;
		//глава городка обычный
		case "DMCitizHead":
			NextDiag.TempNode = "DMCitizHead";
			dialog.text = StringFromKey("MagicCity_63");
			link.l1 = StringFromKey("MagicCity_64");
			link.l1.go = "DMCitizHead_1";
			if (pchar.questTemp.MC == "AfterMeeting")
			{
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("MagicCity_67", RandPhraseSimple(
									StringFromKey("MagicCity_65", pchar),
									StringFromKey("MagicCity_66", GetAddress_Form(NPChar)))),
							StringFromKey("MagicCity_68", pchar),
							StringFromKey("MagicCity_69"),
							StringFromKey("MagicCity_70", UpperFirst(GetAddress_Form(NPChar))), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("MagicCity_73", RandPhraseSimple(
									StringFromKey("MagicCity_71"),
									StringFromKey("MagicCity_72"))),
							StringFromKey("MagicCity_76", RandPhraseSimple(
									StringFromKey("MagicCity_74"),
									StringFromKey("MagicCity_75"))),
							StringFromKey("MagicCity_79", RandPhraseSimple(
									StringFromKey("MagicCity_77"),
									StringFromKey("MagicCity_78"))),
							StringFromKey("MagicCity_80"), npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toByeBye")
			{
				dialog.text = StringFromKey("MagicCity_81");
				link.l1 = StringFromKey("MagicCity_82");
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSister")
			{
				dialog.text = StringFromKey("MagicCity_83", pchar, UpperFirst(GetAddress_Form(NPChar)));
				link.l1 = StringFromKey("MagicCity_84");
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSkull")
			{
				dialog.text = StringFromKey("MagicCity_85");
				link.l1 = StringFromKey("MagicCity_86", pchar);
				link.l1.go = "FoundLiz";
			}
			if (pchar.questTemp.MC == "toSeekQueen")
			{
				dialog.text = StringFromKey("MagicCity_87");
				link.l1 = StringFromKey("MagicCity_88", pchar);
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "over")
			{
				dialog.text = StringFromKey("MagicCity_89");
				link.l1 = StringFromKey("MagicCity_90", pchar);
				link.l1.go = "DMHeadOver";
			}
			if (CheckAttribute(pchar, "questTemp.MC.DesMoines"))
			{
				dialog.text = StringFromKey("MagicCity_91", pchar, UpperFirst(GetAddress_Form(NPChar)));
				link.l1 = StringFromKey("MagicCity_92");
				link.l1.go = "exit";
			}
		break;
		case "DMCitizHead_1":
			dialog.text = StringFromKey("MagicCity_93");
			link.l1 = StringFromKey("MagicCity_94", pchar);
			link.l1.go = "DMCitizHead_2";
		break;
		case "DMCitizHead_2":
			dialog.text = StringFromKey("MagicCity_95");
			link.l1 = StringFromKey("MagicCity_96");
			link.l1.go = "DMCitizHead_3";
		break;
		case "DMCitizHead_3":
			dialog.text = StringFromKey("MagicCity_97");
			link.l1 = StringFromKey("MagicCity_98");
			link.l1.go = "exit";
			pchar.questTemp.MC = "AfterMeeting";
			RemoveLandQuestMark_Main(CharacterFromId("Maracaibo_tavernkeeper"), "MagicCity");
		break;

		case "FoundLiz":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("MagicCity_99"),
						StringFromKey("MagicCity_100"),
						StringFromKey("MagicCity_101"),
						StringFromKey("MagicCity_102"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("MagicCity_103"),
						StringFromKey("MagicCity_104"),
						StringFromKey("MagicCity_105"),
						StringFromKey("MagicCity_106", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("FoundLiz_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "FoundLiz_1":
			dialog.text = StringFromKey("MagicCity_107");
			link.l1 = StringFromKey("MagicCity_108");
			link.l1.go = "FoundLiz_2";
		break;
		case "FoundLiz_2":
			dialog.text = StringFromKey("MagicCity_109");
			link.l1 = StringFromKey("MagicCity_110");
			link.l1.go = "exit";
		break;

		case "DMHeadOver":
			dialog.text = StringFromKey("MagicCity_111");
			link.l1 = StringFromKey("MagicCity_112");
			link.l1.go = "DMHeadOver_1";
		break;
		case "DMHeadOver_1":
			dialog.text = StringFromKey("MagicCity_113");
			link.l1 = StringFromKey("MagicCity_114");
			link.l1.go = "DMHeadOver_2";
			link.l2 = StringFromKey("MagicCity_115");
			link.l2.go = "DMHeadOver_3";
			DeleteRumor(FindRumour(sti(TEV.DanielleShipRumourId)));
			DeleteAttribute(&TEV, "DanielleShipRumourId");
		break;
		case "DMHeadOver_2":
			dialog.text = StringFromKey("MagicCity_116");
			link.l1 = StringFromKey("MagicCity_117");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 20);
			AddQuestRecord("MagicCity", "9");
			CloseQuestHeader("MagicCity");
			pchar.questTemp.MC.DesMoines = true;
			RemoveLandQuestMarkToFantoms_Main("DesMoinesHead", "MagicCity");
			Achievment_Set(ACH_Ya_vizhu_myortvykh_lyudey);
		break;
		case "DMHeadOver_3":
			dialog.text = StringFromKey("MagicCity_118", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("MagicCity_119");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 20000);
			AddQuestRecord("MagicCity", "9");
			CloseQuestHeader("MagicCity");
			pchar.questTemp.MC.DesMoines = true;
			RemoveLandQuestMarkToFantoms_Main("DesMoinesHead", "MagicCity");
			Achievment_Set(ACH_Ya_vizhu_myortvykh_lyudey);
		break;

		//глава городка скелет
		case "DMSkelHead":
			NextDiag.TempNode = "DMSkelHead";
			dialog.text = StringFromKey("MagicCity_120");
			link.l1 = StringFromKey("MagicCity_121");
			link.l1.go = "DMSkelHead_1";
			if (pchar.questTemp.MC == "toByeBye")
			{
				dialog.text = StringFromKey("MagicCity_122");
				link.l1 = StringFromKey("MagicCity_123");
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSister")
			{
				dialog.text = StringFromKey("MagicCity_124", pchar, UpperFirst(GetAddress_Form(NPChar)));
				link.l1 = StringFromKey("MagicCity_125");
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSkull")
			{
				dialog.text = StringFromKey("MagicCity_126");
				link.l1 = StringFromKey("MagicCity_127", pchar);
				link.l1.go = "FoundLiz";
			}
			if (pchar.questTemp.MC == "toSeekQueen")
			{
				dialog.text = StringFromKey("MagicCity_128");
				link.l1 = StringFromKey("MagicCity_129", pchar);
				link.l1.go = "exit";
			}
		break;
		case "DMSkelHead_1":
			dialog.text = StringFromKey("MagicCity_130");
			link.l1 = StringFromKey("MagicCity_131");
			link.l1.go = "DMSkelHead_2";
		break;
		case "DMSkelHead_2":
			dialog.text = StringFromKey("MagicCity_132");
			link.l1 = StringFromKey("MagicCity_133");
			link.l1.go = "DMSkelHead_3";
		break;
		case "DMSkelHead_3":
			dialog.text = StringFromKey("MagicCity_134");
			link.l1 = StringFromKey("MagicCity_135");
			link.l1.go = "DMSkelHead_4";
		break;
		case "DMSkelHead_4":
			dialog.text = StringFromKey("MagicCity_136");
			link.l1 = StringFromKey("MagicCity_137");
			link.l1.go = "DMSkelHead_5";
		break;
		case "DMSkelHead_5":
			dialog.text = StringFromKey("MagicCity_138");
			link.l1 = StringFromKey("MagicCity_139");
			link.l1.go = "DMSkelHead_6";
		break;
		case "DMSkelHead_6":
			dialog.text = StringFromKey("MagicCity_140");
			link.l1 = StringFromKey("MagicCity_141", pchar);
			link.l1.go = "DMSkelHead_7";
		break;
		case "DMSkelHead_7":
			dialog.text = StringFromKey("MagicCity_142");
			link.l1 = StringFromKey("MagicCity_143");
			link.l1.go = "DMSkelHead_8";
			link.l2 = StringFromKey("MagicCity_144");
			link.l2.go = "DMSkelHead_bye";
			LocatorReloadEnterDisable("DesMoines_town", "reload1_back", false); //выпускаем из города
		break;

		case "DMSkelHead_bye":
			dialog.text = StringFromKey("MagicCity_145", pchar);
			link.l1 = StringFromKey("MagicCity_146");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -20);
			AddQuestRecord("MagicCity", "4");
			AddQuestUserData("MagicCity", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("MagicCity", "sSex1", GetSexPhrase("ёл", "ла"));
			pchar.questTemp.MC = "toByeBye"; //флаг квеста
			RemoveLandQuestMarkToFantoms_Main("DesMoinesHead", "MagicCity");
			RemoveLandQuestMark_Main(CharacterFromId("Maracaibo_tavernkeeper"), "MagicCity");
			AddLandQuestMark_Main(CharacterFromID("Santiago_Inquisitor"), "MagicCity");
		break;

		case "DMSkelHead_8":
			dialog.text = StringFromKey("MagicCity_147");
			link.l1 = StringFromKey("MagicCity_148");
			link.l1.go = "DMSkelHead_9";
		break;
		case "DMSkelHead_9":
			dialog.text = StringFromKey("MagicCity_149");
			link.l1 = StringFromKey("MagicCity_150");
			link.l1.go = "DMSkelHead_10";
		break;
		case "DMSkelHead_10":
			dialog.text = StringFromKey("MagicCity_151");
			link.l1 = StringFromKey("MagicCity_152");
			link.l1.go = "DMSkelHead_11";
		break;
		case "DMSkelHead_11":
			dialog.text = StringFromKey("MagicCity_153");
			link.l1 = StringFromKey("MagicCity_154");
			link.l1.go = "DMSkelHead_12";
		break;
		case "DMSkelHead_12":
			dialog.text = StringFromKey("MagicCity_155");
			link.l1 = StringFromKey("MagicCity_156");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 5);
			AddQuestRecord("MagicCity", "5");
			AddQuestUserData("MagicCity", "sSex", GetSexPhrase("ся", "ась"));
			pchar.questTemp.MC = "toSeekSister"; //флаг квеста	
			LocatorReloadEnterDisable("Charles_town", "housePirate", false);
			RemoveLandQuestMarkToFantoms_Main("DesMoinesHead", "MagicCity");
			RemoveLandQuestMark_Main(CharacterFromId("Maracaibo_tavernkeeper"), "MagicCity");
			//ставим Лиз Шеппард
			sld = GetCharacter(NPC_GenerateCharacter("LizSheppard", "BaynesDaughter", "woman", "towngirl", 10, ENGLAND, -1, false));
			sld.name = FindPersonalName("LizSheppard_name");
			sld.lastname = FindPersonalName("LizSheppard_lastname");
			sld.dialog.filename = "Quest\MagicCity.c";
			sld.dialog.currentnode = "LizBegin";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Charles_PirateHouse", "goto", "goto1");
			AddLandQuestMark_Main(sld, "MagicCity");
		break;
		//Элизабет Шеппард
		case "LizBegin":
			dialog.text = StringFromKey("MagicCity_157");
			link.l1 = StringFromKey("MagicCity_158", pchar, GetFullName(pchar));
			link.l1.go = "LizBegin_1";
		break;
		case "LizBegin_1":
			dialog.text = StringFromKey("MagicCity_159");
			link.l1 = StringFromKey("MagicCity_160", pchar);
			link.l1.go = "LizBegin_2";
		break;
		case "LizBegin_2":
			dialog.text = StringFromKey("MagicCity_161");
			link.l1 = StringFromKey("MagicCity_162");
			link.l1.go = "LizBegin_3";
		break;
		case "LizBegin_3":
			dialog.text = StringFromKey("MagicCity_163");
			link.l1 = StringFromKey("MagicCity_164");
			link.l1.go = "LizBegin_4";
		break;
		case "LizBegin_4":
			dialog.text = StringFromKey("MagicCity_165");
			link.l1 = StringFromKey("MagicCity_166");
			link.l1.go = "LizBegin_5";
		break;
		case "LizBegin_5":
			dialog.text = StringFromKey("MagicCity_167");
			link.l1 = StringFromKey("MagicCity_168");
			link.l1.go = "LizBegin_6";
		break;
		case "LizBegin_6":
			dialog.text = StringFromKey("MagicCity_169");
			link.l1 = StringFromKey("MagicCity_170");
			link.l1.go = "LizBegin_7";
		break;
		case "LizBegin_7":
			dialog.text = StringFromKey("MagicCity_171");
			link.l1 = StringFromKey("MagicCity_172");
			link.l1.go = "LizBegin_8";
		break;
		case "LizBegin_8":
			dialog.text = StringFromKey("MagicCity_173");
			link.l1 = StringFromKey("MagicCity_174");
			link.l1.go = "LizBegin_9";
		break;
		case "LizBegin_9":
			dialog.text = StringFromKey("MagicCity_175");
			link.l1 = StringFromKey("MagicCity_176", pchar);
			link.l1.go = "LizBegin_10";
		break;
		case "LizBegin_10":
			dialog.text = StringFromKey("MagicCity_177");
			link.l1 = StringFromKey("MagicCity_178");
			link.l1.go = "LizBegin_11";
		break;
		case "LizBegin_11":
			dialog.text = StringFromKey("MagicCity_179");
			link.l1 = StringFromKey("MagicCity_180");
			link.l1.go = "LizBegin_12";
		break;
		case "LizBegin_12":
			dialog.text = StringFromKey("MagicCity_181");
			link.l1 = StringFromKey("MagicCity_182");
			link.l1.go = "LizBegin_13";
		break;
		case "LizBegin_13":
			dialog.text = StringFromKey("MagicCity_183");
			link.l1 = StringFromKey("MagicCity_184");
			link.l1.go = "LizBegin_14";
		break;
		case "LizBegin_14":
			dialog.text = StringFromKey("MagicCity_185");
			link.l1 = StringFromKey("MagicCity_186");
			link.l1.go = "LizBegin_15";
		break;
		case "LizBegin_15":
			dialog.text = StringFromKey("MagicCity_187", pchar);
			if (CheckCharacterItem(pchar, "SkullAztec"))
			{
				link.l1 = StringFromKey("MagicCity_188");
				link.l1.go = "LizBegin_haveSkull";
			}
			else
			{
				link.l1 = StringFromKey("MagicCity_189", pchar);
				link.l1.go = "LizBegin_seekSkull";
			}
		break;

		case "LizBegin_SeekSkull":
			dialog.text = StringFromKey("MagicCity_190");
			link.l1 = StringFromKey("MagicCity_191");
			link.l1.go = "LizBegin_16";
			ChangeCharacterReputation(pchar, 3);
		break;
		case "LizBegin_16":
			dialog.text = StringFromKey("MagicCity_192");
			link.l1 = StringFromKey("MagicCity_193");
			link.l1.go = "exit";
			AddQuestRecord("MagicCity", "6");
			AddQuestUserData("MagicCity", "sSex", GetSexPhrase("ёл", "ла"));
			AddQuestUserData("MagicCity", "sSex1", GetSexPhrase("ся", "ась"));
			pchar.questTemp.MC = "toSeekSkull"; //флаг квеста	
			NextDiag.TempNode = "LizCheckSkull";
			AddLandQuestMark_Main_WithCondition(npchar, "MagicCity", "MagicCity_ToSeekSkull_QuestMarkCondition");
		break;

		case "LizBegin_haveSkull":
			dialog.text = StringFromKey("MagicCity_194");
			link.l1 = StringFromKey("MagicCity_195");
			link.l1.go = "LizCheckSkull_1";
		break;
		//проверка черепа
		case "LizCheckSkull":
			dialog.text = StringFromKey("MagicCity_196");
			if (CheckCharacterItem(pchar, "SkullAztec"))
			{
				link.l1 = StringFromKey("MagicCity_197");
				link.l1.go = "LizCheckSkull_Ok";
			}
			else
			{
				link.l1 = StringFromKey("MagicCity_198");
				link.l1.go = "exit";
			}
		break;
		case "LizCheckSkull_Ok":
			dialog.text = StringFromKey("MagicCity_199");
			link.l1 = StringFromKey("MagicCity_200");
			link.l1.go = "LizCheckSkull_1";
		break;
		case "LizCheckSkull_1":
			dialog.text = StringFromKey("MagicCity_201");
			link.l1 = StringFromKey("MagicCity_202");
			link.l1.go = "LizCheckSkull_2";
		break;
		case "LizCheckSkull_2":
			dialog.text = StringFromKey("MagicCity_203");
			link.l1 = StringFromKey("MagicCity_204");
			link.l1.go = "LizCheckSkull_3";
		break;
		case "LizCheckSkull_3":
			dialog.text = StringFromKey("MagicCity_205");
			link.l1 = StringFromKey("MagicCity_206");
			link.l1.go = "exit";
			SetDanielleInWorld();
			AddQuestRecord("MagicCity", "7");
			pchar.questTemp.MC = "toSeekQueen"; //флаг квеста	
			NextDiag.TempNode = "LizSeekQueen";
			RemoveLandQuestMark_Main(npchar, "MagicCity");
			AddLandQuestMark_Main_WithCondition(CharacterFromID("Danielle"), "MagicCity", "MagicCity_ToSeekSkull_QuestMarkCondition");
		break;
		case "LizSeekQueen":
			dialog.text = StringFromKey("MagicCity_207");
			link.l1 = StringFromKey("MagicCity_208");
			link.l1.go = "exit";
			if (pchar.questTemp.MC == "over")
			{
				dialog.text = StringFromKey("MagicCity_209");
				link.l1 = StringFromKey("MagicCity_210");
				link.l1.go = "LizOver";
			}
		break;

		case "LizOver":
			dialog.text = StringFromKey("MagicCity_211");
			link.l1 = StringFromKey("MagicCity_212");
			link.l1.go = "LizOver_1";
		break;
		case "LizOver_1":
			dialog.text = StringFromKey("MagicCity_213");
			link.l1 = StringFromKey("MagicCity_214");
			link.l1.go = "LizOver_2";
		break;
		case "LizOver_2":
			dialog.text = StringFromKey("MagicCity_215");
			link.l1 = StringFromKey("MagicCity_216");
			link.l1.go = "exit";
			npchar.lifeDay = 30;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			NextDiag.TempNode = "LizOver_end";
			RemoveLandQuestMark_Main(npchar, "MagicCity");
		break;
		case "LizOver_end":
			dialog.text = StringFromKey("MagicCity_217");
			link.l1 = StringFromKey("MagicCity_218");
			link.l1.go = "exit";
		break;
		//Даниэль на абордаже
		case "DanAbordage":
			dialog.text = StringFromKey("MagicCity_219");
			link.l1 = StringFromKey("MagicCity_220");
			link.l1.go = "DanAbordage_1";
		break;
		case "DanAbordage_1":
			dialog.text = StringFromKey("MagicCity_221", pchar);
			link.l1 = StringFromKey("MagicCity_222");
			link.l1.go = "DanAbordage_2";
		break;
		case "DanAbordage_2":
			dialog.text = StringFromKey("MagicCity_223");
			link.l1 = StringFromKey("MagicCity_224", pchar);
			link.l1.go = "DanAbordage_3";
		break;
		case "DanAbordage_3":
			dialog.text = StringFromKey("MagicCity_225");
			link.l1 = StringFromKey("MagicCity_226");
			link.l1.go = "DanAbordage_4";
		break;
		case "DanAbordage_4":
			dialog.text = StringFromKey("MagicCity_227", pchar);
			link.l1 = StringFromKey("MagicCity_228", pchar, GetFullName(pchar));
			link.l1.go = "DanAbordage_5";
		break;
		case "DanAbordage_5":
			dialog.text = StringFromKey("MagicCity_229");
			link.l1 = StringFromKey("MagicCity_230");
			link.l1.go = "DanAbordage_6";
		break;
		case "DanAbordage_6":
			dialog.text = StringFromKey("MagicCity_231");
			link.l1 = StringFromKey("MagicCity_232");
			link.l1.go = "DanAbordage_7";
		break;
		case "DanAbordage_7":
			dialog.text = StringFromKey("MagicCity_233");
			link.l1 = StringFromKey("MagicCity_234");
			link.l1.go = "DanAbordage_8";
		break;
		case "DanAbordage_8":
			dialog.text = StringFromKey("MagicCity_235");
			link.l1 = StringFromKey("MagicCity_236");
			link.l1.go = "DanAbordage_10";
		break;
		case "DanAbordage_10":
			dialog.text = StringFromKey("MagicCity_237");
			link.l1 = StringFromKey("MagicCity_238", pchar);
			link.l1.go = "DanAbordage_11";
		break;
		case "DanAbordage_11":
			dialog.text = StringFromKey("MagicCity_239");
			link.l1 = StringFromKey("MagicCity_240");
			link.l1.go = "DanAbordage_12";
		break;
		case "DanAbordage_12":
			dialog.text = StringFromKey("MagicCity_241");
			link.l1 = StringFromKey("MagicCity_242", pchar);
			link.l1.go = "DanAbordage_13";
		break;
		case "DanAbordage_13":
			dialog.text = StringFromKey("MagicCity_243");
			link.l1 = StringFromKey("MagicCity_244");
			link.l1.go = "DanAbordage_14";
		break;
		case "DanAbordage_14":
		//чистим базу нпс-кэпов  -->
			DeleteAttribute(&NullCharacter, "capitainBase.Danielle");
			//<-- чистим базу нпс-кэпов
			AddQuestRecord("MagicCity", "8");
			pchar.quest.MC_DanielleIsDead.over = "yes";
			pchar.questTemp.MC = "over"; //флаг квеста
			DeleteAttribute(&TEV, "DesMoinesTimeSkipDisable"); // разрешаем отдых в поселении Дес-Мойнес
			AddLandQuestMark_Main(CharacterFromID("LizSheppard"), "MagicCity");
			AddLandQuestMarkToFantoms_Main("DesMoinesHead", "MagicCity", "");
			sld = GetCharacter(NPC_GenerateCharacter("DanielleOff", "Danielle_Sheppard", "woman", "Danielle", 30, PIRATE, -1, true));
			sld.HeroModel = "Danielle_Sheppard,Danielle_Sheppard_1,Danielle_Sheppard_2,Danielle_Sheppard_3,Danielle_Sheppard_4,Danielle_Sheppard_5";  // Прописка всех моделей для кирас. <-- Konstrush
			sld.name = FindPersonalName("DanielleOff_name");
			sld.lastname = FindPersonalName("DanielleOff_lastname");
			sld.greeting = "Gr_Danielle";
			sld.Dialog.Filename = "Officer_Girl.c";
			sld.quest.meeting = true;
			sld.rank = 26;
			LAi_SetHP(sld, 310.0, 310.0);
			//               P  I  E  A  T  R  S
			SetSPECIAL(sld, 7, 7, 9, 10, 8, 9, 10);
			SetSelfSkill(sld, 80, 50, 2, 60, 80);
			SetShipSkill(sld, 80, 10, 90, 70, 90, 40, 60, 65, 70);
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "ByWorker");
			SetCharacterPerk(sld, "IronWill");
			SetCharacterPerk(sld, "BladeDancer");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "HawkEye");
			SetCharacterPerk(sld, "FastReload");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "LootCollection");
			SetCharacterPerk(sld, "Mentor");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "CannonProfessional");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "StormProfessional");
			//черты
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "LoyalOff");
			SetCharacterPerk(sld, "SweetBaby");

			ItemTakeEquip(sld, "jewelry15,incas_collection,pistol6,blade22,spyglass4", 1);

			//sld.quest.OfficerPrice = sti(pchar.rank)*500; TODO_salary
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.loyality = MAX_LOYALITY;
			LAi_SetRolyPoly(sld, true); //неваляха
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			QuestAboardCabinDialogNotBattle();
			DialogExit();
		break;
	}
}

void SetDanielleInWorld()
{
	//создаем Даниэль Шеппард
	ref sld = GetCharacter(NPC_GenerateCharacter("Danielle", "Danielle_Sheppard", "woman", "Danielle", 30, PIRATE, -1, true));
	sld.name = FindPersonalName("DanielleOff_name");
	sld.lastname = FindPersonalName("DanielleOff_lastname");
	sld.dialog.filename = "Quest\MagicCity.c";
	sld.dialog.currentnode = "DanAbordage";
	sld.greeting = "";
	sld.CrewType.Skel = true; //команда - скелеты 
	FantomMakeCoolSailor(sld, SHIP_FRIGATEQUEEN, FindPersonalName("DanielleOff_ship"), CANNON_TYPE_CANNON_LBS32, 90, 90, 90);
	sld.Ship.Mode = "pirate";

	ref rShip = GetRealShip(sti(sld.Ship.Type));
	rShip.ship.upgrades.hull = 1;

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
	//AlexBlade > fix Даниель не экипирована
	ItemTakeEquip(sld, "jewelry15,incas_collection,pistol6,blade22,spyglass4", 1);
	sld.SaveItemsForDead = true; // сохранять на трупе вещи
	sld.DontClearDead = true;

	pchar.Quest.MC_DanielleIsDead.win_condition.l1 = "NPC_Death";
	pchar.Quest.MC_DanielleIsDead.win_condition.l1.character = sld.id;
	pchar.Quest.MC_DanielleIsDead.function = "MC_DanielleIsDead";
	//в морскую группу кэпа
	string sGroup = "DanielleGroup";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.city = "SantaCatalina"; //определим колонию, из бухты которой с мушкетом выйдет
	sld.cityShore = GetIslandRandomShoreId(GetArealByCityName(sld.city));
	sld.quest.targetCity = SelectAnyColony(sld.city); //определим колонию, в бухту которой он придет
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	Log_TestInfo("Фрегат Queen вышел из: " + sld.city + " и направился в: " + sld.quest.targetShore + "");
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	// sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.worldMapShip = "QueenShip";
	sld.mapEnc.Name = FindPersonalName("Danielle_mapEnc");
	int daysQty = GetMaxDaysFromColony2Colony(sld.quest.targetCity, sld.city) + 5; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);
	//заносим Id кэпа в базу нпс-кэпов
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "Danielle"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = "MagicCity"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "MagicCity"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
	NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
	NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
	NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	//пускаем слух
	string sRumourName = GetRandName(NAMETYPE_ORIG, NAME_NOM);
	TEV.DanielleShipRumourId = AddSimpleRumour(
				StringFromKey("MagicCity_248", LinkRandPhrase(
						StringFromKey("MagicCity_245", XI_ConvertString(sld.quest.targetShore + "Gen")),
						StringFromKey("MagicCity_246", XI_ConvertString(sld.quest.targetShore + "Pre")),
						StringFromKey("MagicCity_247", sRumourName, XI_ConvertString(sld.quest.targetShore + "Acc")))), 1, daysQty, 1);
}

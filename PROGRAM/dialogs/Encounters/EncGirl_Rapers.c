
//HardCoffee work in progress -->

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iIdx;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "DlgRapers_BeginQuest":
			for (i = 1; i <= ENCGIRL_RAPERS_QTY; i++)
			{
				if (GetCharacterIndex("EncGirl_GangMan_" + i) < 0) continue;
				sld = CharacterFromID("EncGirl_GangMan_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}

			if ("Quest_Begin_WhoreGirl" == pchar.GenQuest.EncGirl) //Шлюха
			{
				dialog.text = StringFromKey("EncGirl_Rapers_25", RandPhraseSimple(
							StringFromKey("EncGirl_Rapers_23", pchar),
							StringFromKey("EncGirl_Rapers_24", pchar)));
				link.l1 = StringFromKey("EncGirl_Rapers_26");
				link.l1.go = "DlgRapers_WhoreRedeem_TheyWantPiastres";
				link.l2 = StringFromKey("EncGirl_Rapers_29", RandPhraseSimple(
							StringFromKey("EncGirl_Rapers_27", pchar),
							StringFromKey("EncGirl_Rapers_28")));
				link.l2.go = "DlgRapers_Result_LeaveHerToRapers";
				pchar.GenQuest.EncGirl = "Quest_Begin_WhoreGirl_AfterRapersDlg";
			}
			else if (pchar.GenQuest.EncGirl == "Quest_Begin_3") //Сбежавшая от родителей
			{
				dialog.text = StringFromKey("EncGirl_Rapers_30", pchar);
				link.l1 = StringFromKey("EncGirl_Rapers_31");
				link.l1.go = "ToParents_RapersExplain";
				pchar.GenQuest.EncGirl = "Quest_Begin_33";
			}
			else //Блудница
			{
				if ("Quest_Begin_CommonGirl" != pchar.GenQuest.EncGirl)
				{
					trace("ERROR: pchar.GenQuest.EncGirl wrong quest attribute: " +pchar.GenQuest.EncGirl);
				}
				dialog.text = StringFromKey("EncGirl_Rapers_4", LinkRandPhrase(
							StringFromKey("EncGirl_Rapers_1", pchar),
							StringFromKey("EncGirl_Rapers_2"),
							StringFromKey("EncGirl_Rapers_3", pchar)));
				link.l1 = StringFromKey("EncGirl_Rapers_8", LinkRandPhrase(
							StringFromKey("EncGirl_Rapers_5"),
							StringFromKey("EncGirl_Rapers_6"),
							StringFromKey("EncGirl_Rapers_7")));
				link.l1.go = "DlgRapers_AboutToFight";
				link.l2 = StringFromKey("EncGirl_Rapers_11", RandPhraseSimple(
							StringFromKey("EncGirl_Rapers_9", pchar),
							StringFromKey("EncGirl_Rapers_10", pchar)));
				link.l2.go = "DlgRapers_Result_LeaveHerToRapers";
				pchar.GenQuest.EncGirl = "Quest_Begin_CommonGirl_AfterRapersDlg"; //Влияет на диалог с девкой, если убьём бандитов
			}
		break;

		case "DlgRapers_AboutToFight":
			dialog.text = StringFromKey("EncGirl_Rapers_41", RandPhraseSimple(
						StringFromKey("EncGirl_Rapers_39", pchar),
						StringFromKey("EncGirl_Rapers_40", pchar)));
			link.l1 = StringFromKey("EncGirl_Rapers_42");
			link.l1.go = "Result_FightToRapers";
		break;

		case "DlgRapers_Result_LeaveHerToRapers":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);
			for (i = 1; i <= ENCGIRL_RAPERS_QTY; i++)
			{
				if (GetCharacterIndex("EncGirl_GangMan_" + i) < 0) continue;
				sld = CharacterFromID("EncGirl_GangMan_" + i);
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorFollow(sld, characterFromId("CangGirl"), "", -1);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld) - 1, false, "LandEnc_EncGirl_FightBeforeDialog");
				//Возможность поговорить ещё раз
				sld.chr_ai.disableDlg = "0";
				sld.chr_ai.type.state = "dialogwait";
				sld.chr_ai.type.dlgchr = pchar.index;
				sld.dialog.currentnode = "DlgRapers_OnceAgain";
			}
			sld = CharacterFromID("CangGirl");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorAfraid(sld, npchar, true);
			LAi_group_SetCheck("EnemyFight", "LandEnc_EncGirl_RapersKilled");
			LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld) - 1, false, "LandEnc_EncGirl_FightBeforeDialog");
			EncGirl_CloseQuestExit("Close_Rapers_LeaveHer");
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "DlgRapers_OnceAgain":
			Diag.TempNode = "DlgRapers_OnceAgain";
			dialog.text = StringFromKey("EncGirl_Rapers_102", pchar);
			Link.l1 = StringFromKey("EncGirl_Rapers_103");
			Link.l1.go = "DlgRapers_Result_LeaveHerToRapers";
			Link.l2 = StringFromKey("EncGirl_Rapers_104");
			Link.l2.go = "DlgRapers_OnceAgain_ToFight";
			AddDialogExitQuestFunction("EncGirl_Rapers_DisableDlg");
		break;

		case "DlgRapers_OnceAgain_ToFight":
			dialog.text = StringFromKey("EncGirl_Rapers_100", pchar);
			Link.l1 = StringFromKey("EncGirl_Rapers_101");
			Link.l1.go = "DlgRapers_Result_OnceAgainFight";
		break;

		case "DlgRapers_Result_OnceAgainFight": //Девка убегает, поговорить с ней нельзя
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;

		case "Result_FightToRapers":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar);
			for (i = 1; i <= ENCGIRL_RAPERS_QTY; i++)
			{
				iIdx = GetCharacterIndex("EncGirl_GangMan_" + i);
				if (iIdx < 0) continue;
				sld = &Characters[iIdx];
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");

			if (pchar.GenQuest.EncGirl == "Quest_RapersTreasure") //Coffee чзнх
			{
				LAi_group_SetCheckFunction("EnemyFight", "EncGirl_RapersAfter");
			}
			else
			{
				LAi_group_SetCheck("EnemyFight", "LandEnc_EncGirl_RapersKilled");
				sld = CharacterFromID("CangGirl");
				LAi_SetActorTypeNoGroup(sld);
				//LAi_SetCheckMinHP(npchar, LAi_GetCharacterHP(npchar) - 1, false, "LandEnc_EncGirl_PunchHer");
				LAi_ActorAfraid(sld, npchar, true);
			}

			EncGirl_CloseQuestExit("Close_Rapers_LeaveHer");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Result_ToParents_YouPromised":
			pchar.GenQuest.EncGirl = "Quest_toParents";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			for (i = 1; i <= ENCGIRL_RAPERS_QTY; i++)
			{
				iIdx = GetCharacterIndex("EncGirl_GangMan_" + i);
				if (iIdx < 0) continue;
				sld = &Characters[iIdx];
				LAi_SetActorTypeNoGroup(sld);
				LAi_SetImmortal(sld, true);
				LAi_ActorRunToLocationNoCheck(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", 5.0);
				sld.lifeDay = "0";
				sld.chr_ai.disableDlg = "1";
			}
			EncGirl_CloseQuestExit("Close_Rapers_ToParentsHer"); //На случай если гг убежит с локации
			AddDialogExitQuestFunction("EncGirl_Rapers_ToParentsHer");
			DialogExit();
		break;

		case "DlgRapers_Result_WhoreRedeem_BoughtOut":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.price)));
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			for (i = 1; i <= ENCGIRL_RAPERS_QTY; i++)
			{
				iIdx = GetCharacterIndex("EncGirl_GangMan_" + i);
				if (iIdx < 0) continue;
				sld = &Characters[iIdx];
				LAi_SetImmortal(sld, true);
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorRunToLocationNoCheck(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", 5.0);
				sld.lifeDay = "0";
				sld.chr_ai.disableDlg = "1";
			}
			EncGirl_CloseQuestExit("Close_Rapers_BoughtOutWhore"); //На случай если гг убежит с локации
			AddDialogExitQuestFunction("EncGirl_Rapers_BoughtOutWhore");
			DialogExit();
		break;

		case "DlgRapers_WhoreRedeem_TheyWantPiastres":
			pchar.GenQuest.EncGirl.price = 1100 * (rand(4) + 5) + 200 * sti(pchar.rank);
			dialog.text = StringFromKey("EncGirl_Rapers_43", pchar, FindMoneyString(sti(pchar.GenQuest.EncGirl.price)));
			if (sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.price))
			{
				link.l1 = StringFromKey("EncGirl_Rapers_46", RandPhraseSimple(
							StringFromKey("EncGirl_Rapers_44"),
							StringFromKey("EncGirl_Rapers_45")));
				link.l1.go = "DlgRapers_Result_WhoreRedeem_BoughtOut";
			}
			link.l2 = StringFromKey("EncGirl_Rapers_50", LinkRandPhrase(
						StringFromKey("EncGirl_Rapers_47"),
						StringFromKey("EncGirl_Rapers_48"),
						StringFromKey("EncGirl_Rapers_49")));
			link.l2.go = "DlgRapers_AboutToFight";
		break;

		case "ToParents_RapersExplain":
			dialog.text = StringFromKey("EncGirl_Rapers_51");
			link.l1 = StringFromKey("EncGirl_Rapers_54", RandPhraseSimple(
						StringFromKey("EncGirl_Rapers_52"),
						StringFromKey("EncGirl_Rapers_53")));
			link.l1.go = "DlgRapers_Result_LeaveHerToRapers";
			link.l2 = StringFromKey("EncGirl_Rapers_57", RandPhraseSimple(
						StringFromKey("EncGirl_Rapers_55"),
						StringFromKey("EncGirl_Rapers_56")));
			link.l2.go = "ToParents_YouDontBelieveIt";
			link.l3 = StringFromKey("EncGirl_Rapers_58", pchar);
			link.l3.go = "ToParents_FindFather";
		break;

		case "ToParents_YouDontBelieveIt":
			dialog.text = StringFromKey("EncGirl_Rapers_59", pchar);
			link.l1 = StringFromKey("EncGirl_Rapers_60");
			link.l1.go = "Result_FightToRapers";
		break;

		case "ToParents_FindFather":
			if (pchar.GenQuest.EncGirl.city == "Panama") i = drand(2); //Coffee TODO:
			else if (pchar.GenQuest.EncGirl.city == "FortOrange") i = 0; //HardCoffee в Оранже только магазин
			else    i = drand(3);
			switch (i)
			{
				case 0:
					pchar.GenQuest.EncGirl.FatherNom = StringFromKey("EncGirl_Rapers_61");
					pchar.GenQuest.EncGirl.FatherGen = StringFromKey("EncGirl_Rapers_62");
					pchar.GenQuest.EncGirl.Father = "store_keeper";
				break;
				case 1:
					pchar.GenQuest.EncGirl.FatherNom = StringFromKey("EncGirl_Rapers_63");
					pchar.GenQuest.EncGirl.FatherGen = StringFromKey("EncGirl_Rapers_64");
					pchar.GenQuest.EncGirl.Father = "portman_keeper";
				break;
				case 2:
					pchar.GenQuest.EncGirl.FatherNom = StringFromKey("EncGirl_Rapers_65");
					pchar.GenQuest.EncGirl.FatherGen = StringFromKey("EncGirl_Rapers_66");
					pchar.GenQuest.EncGirl.Father = "fort_keeper";
				break;
				case 3:
					pchar.GenQuest.EncGirl.FatherNom = StringFromKey("EncGirl_Rapers_67");
					pchar.GenQuest.EncGirl.FatherGen = StringFromKey("EncGirl_Rapers_68");
					pchar.GenQuest.EncGirl.Father = "shipyard_keeper";
				break;
			}
			dialog.text = StringFromKey("EncGirl_Rapers_69", pchar.GenQuest.EncGirl.FatherNom, XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1 = StringFromKey("EncGirl_Rapers_70");
			link.l1.go = "Result_ToParents_YouPromised";
		break;

		case "Node_8":
			dialog.text = StringFromKey("EncGirl_Rapers_71");
			link.l1 = StringFromKey("EncGirl_Rapers_72");
			link.l1.go = "Node_9";
		break;

		case "Node_9":
			if (drand(1) == 0)
			{
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_NICK;
			}
			else
			{
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_VIP;
			}
			pchar.GenQuest.EncGirl.PirateName2 = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			switch (drand(4))
			{
				case 0: sTemp = StringFromKey("EncGirl_Rapers_73"); break;
				case 1: sTemp = StringFromKey("EncGirl_Rapers_74"); break;
				case 2: sTemp = StringFromKey("EncGirl_Rapers_75"); break;
				case 3: sTemp = StringFromKey("EncGirl_Rapers_76"); break;
				case 4: sTemp = StringFromKey("EncGirl_Rapers_77"); break;
			}
			dialog.text = StringFromKey("EncGirl_Rapers_78", GetName(pchar.GenQuest.EncGirl.PirateIdx, pchar.GenQuest.EncGirl.PirateName1, NAME_GEN), GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.PirateName2, NAME_NOM), sTemp, GetName(pchar.GenQuest.EncGirl.PirateIdx, pchar.GenQuest.EncGirl.PirateName1, NAME_NOM));
			link.l1 = StringFromKey("EncGirl_Rapers_79", pchar);
			link.l1.go = "Node_10";
		break;

		case "Node_10":
			dialog.text = StringFromKey("EncGirl_Rapers_80");
			link.l1 = StringFromKey("EncGirl_Rapers_81");
			link.l1.go = "Node_11";
		break;

		case "Node_11":
			pchar.GenQuest.EncGirl = "Quest_RapersTreasure";
			dialog.text = StringFromKey("EncGirl_Rapers_82", pchar);
			link.l1 = StringFromKey("EncGirl_Rapers_83");
			link.l1.go = "Result_FightToRapers";
		break;

		case "EncGirl_InTavern_Burglar":
			dialog.text = StringFromKey("EncGirl_Rapers_84", pchar);
			link.l1 = StringFromKey("EncGirl_Rapers_85");
			link.l1.go = "EncGirl_InTavern_Burglar_2";
		break;

		case "EncGirl_InTavern_Burglar_2":
			dialog.text = StringFromKey("EncGirl_Rapers_86", pchar);
			link.l1 = StringFromKey("EncGirl_Rapers_87");
			link.l1.go = "EncGirl_InTavern_Burglar_Variants";
		break;

		case "EncGirl_InTavern_Burglar_Variants":
			i = makeint(sti(pchar.money) / 5) + 5000;
			if (i > 250000) i = 220000 + rand(30000);
			if (i > 0 && i <= sti(pchar.money))
			{
				dialog.text = StringFromKey("EncGirl_Rapers_88", i);
				link.l1 = StringFromKey("EncGirl_Rapers_89");
				link.l1.go = "EncGirl_InTavern_Burglar_PayMoney";
				link.l2 = StringFromKey("EncGirl_Rapers_90");
				link.l2.go = "EncGirl_InTavern_Burglar_Fight";
			}
			else
			{
				dialog.text = StringFromKey("EncGirl_Rapers_91");
				link.l1 = StringFromKey("EncGirl_Rapers_92");
				link.l1.go = "EncGirl_InTavern_Burglar_LackMoney";
				link.l2 = StringFromKey("EncGirl_Rapers_93");
				link.l2.go = "EncGirl_InTavern_Burglar_Fight";
			}
			pchar.GenQuest.EncGirl.BurglarSum = i;
		break;

		case "EncGirl_InTavern_Burglar_Fight":
			dialog.text = StringFromKey("EncGirl_Rapers_98", pchar);
			link.l1 = StringFromKey("EncGirl_Rapers_99");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_InTavern_FightBurglar");
		break;

		case "EncGirl_InTavern_Burglar_PayMoney":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.BurglarSum)));
			dialog.text = StringFromKey("EncGirl_Rapers_94");
			link.l1 = StringFromKey("EncGirl_Rapers_95");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_InTavern_PayMoneyToBurglar");
		break;

		case "EncGirl_InTavern_Burglar_LackMoney":
			dialog.text = StringFromKey("EncGirl_Rapers_96", pchar);
			link.l1 = StringFromKey("EncGirl_Rapers_97", pchar);
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_InTavern_LackMoneyToBurglar");
		break;
	}
}

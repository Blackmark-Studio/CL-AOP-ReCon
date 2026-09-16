
//HardCoffee work in progress -->

void ProcessDialogEvent()
{
	ref NPChar, sld, rTown;
	aref Link, Diag;
	int i, iRnd;
	string sTemp;
	bool bOk1, bOk2;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	//HardCoffee ref
	chrDisableReloadToLocation = false; //до диалога был повешен лок на локацию для того, чтобы гг не убежал, когда к нему бежит нпс

	if ("DlgGirl_GiveHerPotion" == Dialog.CurrentNode)
	{
		TakeNItemsNotification(pchar, pchar.GenQuest.EncGirl.GiveHerPotion, -1, "default", "migraine_potion", "");
		npchar.chr_ai.hp = npchar.chr_ai.hp_max;
		Dialog.CurrentNode = Diag.TempNode;
		ChangeCharacterReputation(pchar, 2);
		if (CheckAttribute(npchar, "QuestFollower"))
		{
			DeleteAttribute(pchar, "GenQuest.EncGirl.GiveHerPotion");
			dialog.text = StringFromKey("EncGirl_Girl_297");
			link.l1 = StringFromKey("EncGirl_Girl_299");
			link.l1.go = "exit";
			return;
		}
		else
		{
			pchar.GenQuest.EncGirl.GiveHerPotion = "done";
		}
	}

	switch (Dialog.CurrentNode)
	{
		case "DlgGirl_Begin_LetsTalkToTheRapers":
			AddDialogExitQuestFunction("EncGirl_Begin_LetsTalkToTheRapers");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "exit":
			if (CheckAttribute(NPChar, "QuestFollower"))
				LAi_ActorFollowEverywhere(npchar, "", -1);
			else
				LAi_SetCitizenTypeNoGroup(NPChar);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "exit_stay":
			TurnNPCToPcharInit(NPChar);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "DlgGirl_Begin_CommonGirl":
			LAi_RemoveCheckMinHP(npchar);
			EncGirlRapers_ActorReset();
			dialog.text = StringFromKey("EncGirl_Girl_3", RandPhraseSimple(
						StringFromKey("EncGirl_Girl_1", pchar),
						StringFromKey("EncGirl_Girl_2", pchar)));
			link.l1 = StringFromKey("EncGirl_Girl_9", LinkRandPhrase(
						StringFromKey("EncGirl_Girl_4"),
						StringFromKey("EncGirl_Girl_5"),
						StringFromKey("EncGirl_Girl_8", RandPhraseSimple(
								StringFromKey("EncGirl_Girl_6"),
								StringFromKey("EncGirl_Girl_7")))));
			link.l1.go = "DlgGirl_Begin_CommonGirl_1";
		break;

		case "DlgGirl_Begin_CommonGirl_1":
			dialog.text = StringFromKey("EncGirl_Girl_28", RandPhraseSimple(
						StringFromKey("EncGirl_Girl_26"),
						StringFromKey("EncGirl_Girl_27")));
			link.l1 = StringFromKey("EncGirl_Girl_29", pchar);
			link.l1.go = "DlgGirl_Begin_LetsTalkToTheRapers";
		break;

		case "DlgGirl_Begin_WhoreGirl":
			LAi_RemoveCheckMinHP(NPChar);
			EncGirlRapers_ActorReset();
			dialog.text = StringFromKey("EncGirl_Girl_12", RandPhraseSimple(
						StringFromKey("EncGirl_Girl_10", pchar),
						StringFromKey("EncGirl_Girl_11", pchar)));
			link.l1 = StringFromKey("EncGirl_Girl_18", LinkRandPhrase(
						StringFromKey("EncGirl_Girl_13"),
						StringFromKey("EncGirl_Girl_14"),
						StringFromKey("EncGirl_Girl_17", RandPhraseSimple(
								StringFromKey("EncGirl_Girl_15"),
								StringFromKey("EncGirl_Girl_16")))));
			link.l1.go = "DlgGirl_Begin_WhoreGirl_1";
		break;

		case "DlgGirl_Begin_WhoreGirl_1":
			dialog.text = StringFromKey("EncGirl_Girl_32", RandPhraseSimple(
						StringFromKey("EncGirl_Girl_30", pchar),
						StringFromKey("EncGirl_Girl_31", pchar)));
			link.l1 = StringFromKey("EncGirl_Girl_33", pchar);
			link.l1.go = "DlgGirl_Begin_LetsTalkToTheRapers";
		break;

		case "Begin_3":
			LAi_RemoveCheckMinHP(NPChar);
			EncGirlRapers_ActorReset();
			dialog.text = StringFromKey("EncGirl_Girl_19", pchar);
			link.l1 = StringFromKey("EncGirl_Girl_25", LinkRandPhrase(
						StringFromKey("EncGirl_Girl_20"),
						StringFromKey("EncGirl_Girl_21"),
						StringFromKey("EncGirl_Girl_24", RandPhraseSimple(
								StringFromKey("EncGirl_Girl_22"),
								StringFromKey("EncGirl_Girl_23")))));
			link.l1.go = "Begin_31";
		break;

		case "Begin_31":
			dialog.text = StringFromKey("EncGirl_Girl_34");
			link.l1 = StringFromKey("EncGirl_Girl_35", pchar);
			link.l1.go = "DlgGirl_Begin_LetsTalkToTheRapers";
		break;

		case "First time":
			LAi_RemoveCheckMinHP(npchar);
			EncGirlRapers_ActorReset();
			dialog.text = StringFromKey("EncGirl_Girl_39", LinkRandPhrase(
						StringFromKey("EncGirl_Girl_36"),
						StringFromKey("EncGirl_Girl_37", pchar),
						StringFromKey("EncGirl_Girl_38")));
			Link.l1 = StringFromKey("EncGirl_Girl_43", LinkRandPhrase(
						StringFromKey("EncGirl_Girl_40"),
						StringFromKey("EncGirl_Girl_41"),
						StringFromKey("EncGirl_Girl_42")));
			Link.l1.go = "Node_2";
		break;

		case "Node_2":
			dialog.text = StringFromKey("EncGirl_Girl_47", LinkRandPhrase(
						StringFromKey("EncGirl_Girl_44"),
						StringFromKey("EncGirl_Girl_45"),
						StringFromKey("EncGirl_Girl_46")));
			Link.l1 = StringFromKey("EncGirl_Girl_48");
			Link.l1.go = "DlgGirl_Begin_LetsTalkToTheRapers";
		break;

		case "DlgGirl_SheThanksForHelpRepeat":
			Diag.TempNode = "DlgGirl_SheThanksForHelpRepeat";
			dialog.text = StringFromKey("EncGirl_Girl_78", RandPhraseSimple(
						StringFromKey("EncGirl_Girl_76", pchar),
						StringFromKey("EncGirl_Girl_77")));
			link.l1 = StringFromKey("EncGirl_Girl_81", RandPhraseSimple(
						StringFromKey("EncGirl_Girl_79"),
						StringFromKey("EncGirl_Girl_80")));
			link.l1.go = "exit";
		break;
// результаты взаимодействия с бандитами -->
		case "DlgGirl_Rapers_YouKilledRapers": //quests_reaction.c case LandEnc_EncGirl_RapersKilled
			DeleteAttribute(pchar, "quest.LandEnc_EncGirl_CloseQuestExit"); //убрать аварийную закрывашку установленную после диалога с бандитами
			if ("Quest_Begin_CommonGirl_AfterRapersDlg" == pchar.GenQuest.EncGirl)
			{
				if (rand(1))
				{
					dialog.text = StringFromKey("EncGirl_Girl_51", RandPhraseSimple(
								StringFromKey("EncGirl_Girl_49", pchar),
								StringFromKey("EncGirl_Girl_50")));
					link.l1 = StringFromKey("EncGirl_Girl_52", pchar);
					link.l1.go = "DlgGirl_InJungle_SheOffersYouMoney";
				}
				else
				{
					dialog.text = StringFromKey("EncGirl_Girl_53", pchar);
					link.l1 = StringFromKey("EncGirl_Girl_54", pchar);
					link.l1.go = "DlgGirl_Escort_ToTOWN_FromJungle_SheAsks_YouKilledRapers";
				}
				EncGirlShouldWeHealHer(link, npchar);
			}
			else if ("Quest_Begin_WhoreGirl_AfterRapersDlg" == pchar.GenQuest.EncGirl)
			{
				if (CheckAttribute(pchar, "GenQuest.EncGirl.EscapedFromBrothel"))
				{
					dialog.text = StringFromKey("EncGirl_Girl_167");
					link.l1 = StringFromKey("EncGirl_Girl_168");
					link.l1.go = "DlgGirl_Escort_ToTAVERN_FromJungle_SheAsks_EscapedWhore";
				}
				else if (rand(1))
				{
					dialog.text = StringFromKey("EncGirl_Girl_55", pchar);
					link.l1 = StringFromKey("EncGirl_Girl_56", pchar);
					link.l1.go = "DlgGirl_Escort_ToTOWN_FromJungle_SheAsks_YouKilledRapers";
				}
				else //She blames you
				{
					dialog.text = StringFromKey("EncGirl_Girl_57");
					link.l1 = StringFromKey("EncGirl_Girl_58");
					link.l1.go = "DlgGirl_Escort_ToTAVERN_FromJungle_SheAsks_YouKilledRapers";
				}
			}
			else if (pchar.GenQuest.EncGirl == "Quest_Begin_33")
			{
				dialog.text = StringFromKey("EncGirl_Girl_59", pchar);
				link.l1 = StringFromKey("EncGirl_Girl_60");
				link.l1.go = "Node_31";
			}
		break;
		case "DlgGirl_Rapers_BoughtOutWhore": // откупились от раперов переход сюда из case 1 WhoreGirl
			DeleteAttribute(pchar, "quest.LandEnc_EncGirl_CloseQuestExit"); //убрать аварийную закрывашку установленную после диалога с бандитами
			if (CheckAttribute(pchar, "GenQuest.EncGirl.EscapedFromBrothel"))
			{
				dialog.text = StringFromKey("EncGirl_Girl_167");
				link.l1 = StringFromKey("EncGirl_Girl_168");
				link.l1.go = "DlgGirl_Escort_ToTAVERN_FromJungle_SheAsks_EscapedWhore";
			}
			else if (false)//(rand(1)) Coffee
			{
				dialog.text = StringFromKey("EncGirl_Girl_164", pchar);
				link.l1 = StringFromKey("EncGirl_Girl_166", pchar);
				link.l1.go = "DlgGirl_Escort_ToTAVERN_FromJungle_SheAsks_BoughtOutWhore";
				link.l2 = StringFromKey("EncGirl_Girl_165");
				link.l2.go = "DlgGirl_InJungle_BoughtOut_BlameWhore";
			}
			else
			{
				dialog.text = StringFromKey("EncGirl_Girl_162", RandPhraseSimple(
					StringFromKey("EncGirl_Girl_160"),
					StringFromKey("EncGirl_Girl_161")));
				link.l1 = StringFromKey("EncGirl_Girl_163");
				link.l1.go = "DlgGirl_InJungle_BoughtOut_CaveWhore";
			}
		break;
		case "Rapers_ToParentsHer": //Пообщещали отвести её к бате
			dialog.text = StringFromKey("EncGirl_Girl_260");
			link.l1 = StringFromKey("EncGirl_Girl_261", pchar);
			link.l1.go = "SheHasALover";
		break;
// <-- резултаты взаимодействия с бандитами
// Rapers_YouKilledRapers она дала бабло за спасение далее с ней можно ещё раз поговорить -->
		case "DlgGirl_InJungle_SheOffersYouMoney":
			dialog.text = StringFromKey("EncGirl_Girl_61", pchar);
			link.l1 = StringFromKey("EncGirl_Girl_62");
			link.l1.go = "DlgGirl_InJungle_SheGaveYouMoney";
		break;

		case "DlgGirl_InJungle_SheGaveYouMoney":
			pchar.GenQuest.EncGirl = "Quest_InJungle_SheGaveYouMoney";
			AddMoneyToCharacter(pchar, makeint((sti(pchar.rank)) * 25 + frand(2) * 500));
			EncGirlBecameCitizenNoGroup(npchar, "Close_Rapers_AreTheyDead");
			//LAi_SetCheckMinHP(npchar, LAi_GetCharacterHP(npchar) - 1, false, "LandEnc_EncGirl_PunchHer");
			Diag.TempNode = "DlgGirl_InJungle_CanTalkAgain"; //Продолжение, если снова к ней обратится
			Diag.CurrentNode = Diag.TempNode;
			npchar.lifeDay = "1";
			DialogExit();

		break;

		case "DlgGirl_InJungle_CanTalkAgain": //Переход сюда из "Rapers_YouKilledRapers" после того, как девка дала бабло за своё спасение
			dialog.text = StringFromKey("EncGirl_Girl_84", RandPhraseSimple(
						StringFromKey("EncGirl_Girl_82", pchar),
						StringFromKey("EncGirl_Girl_83", pchar)));
			link.l1 = StringFromKey("EncGirl_Girl_87", RandPhraseSimple(
						StringFromKey("EncGirl_Girl_85"),
						StringFromKey("EncGirl_Girl_86")));
			link.l1.go = "DlgGirl_InJungle_CanTalkAgain_Close";
			link.l2 = StringFromKey("EncGirl_Girl_88");
			link.l2.go = "DlgGirl_WhatDoesSheDoInJungle";
			EncGirlShouldWeHealHer(link, npchar);
		break;

		case "DlgGirl_InJungle_CanTalkAgain_Close":
			npchar.chr_ai.disableDlg = "1";
			DialogExit();
		break;
// <-- Rapers_YouKilledRapers она дала бабло за спасение далее с ней можно ещё раз поговорить
		case "DlgGirl_Escort_ToTOWN_FromJungle_SheAsks_YouKilledRapers": // преход сюда из кейсов CommonGirl и WhoreGirl если завалили бандитов
			dialog.text = StringFromKey("EncGirl_Girl_63", pchar, XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1 = StringFromKey("EncGirl_Girl_66", RandPhraseSimple(
						StringFromKey("EncGirl_Girl_64"),
						StringFromKey("EncGirl_Girl_65")));
			link.l1.go = "DlgGirl_Escort_ToTOWN_FromJungle_Begin";
			link.l2 = StringFromKey("EncGirl_Girl_67");
			link.l2.go = "DlgGirl_InJungle_RejectEscort";
			Diag.NodeEscortTo = "DlgGirl_Escort_ToTOWN_FromJungle_Begin";
		break;
		case "DlgGirl_Escort_ToTAVERN_FromJungle_SheAsks_YouKilledRapers": // преход сюда из кейса WhoreGirl если завалили бандитов
			dialog.text = StringFromKey("EncGirl_Girl_68", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1 = StringFromKey("EncGirl_Girl_69");
			link.l1.go = "DlgGirl_Escort_ToTAVERN_FromJungle_Begin";
			link.l2 = StringFromKey("EncGirl_Girl_70", pchar);
			link.l2.go = "DlgGirl_InJungle_RejectEscort";
			Diag.NodeEscortTo = "DlgGirl_Escort_ToTAVERN_FromJungle_Begin";
		break;

		case "Node_31": //Coffee
			dialog.text = StringFromKey("EncGirl_Girl_71");
			link.l1 = StringFromKey("EncGirl_Girl_72");
			link.l1.go = "Node_32";
			link.l2 = StringFromKey("EncGirl_Girl_73", pchar);
			link.l2.go = "DlgGirl_InJungle_RejectEscort";
			Diag.NodeEscortTo = "Node_32";
		break;

		case "Node_32":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man");
			dialog.text = StringFromKey("EncGirl_Girl_74", pchar.GenQuest.EncGirl.sLoverId, XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1 = StringFromKey("EncGirl_Girl_75");
			link.l1.go = "Node_12Next";
		break;

		case "Node_12Next":
			DeleteAttribute(pchar, "quest.LandEnc_EncGirl_CloseQuestExit");
			Diag.TempNode = "DlgGirl_SheThanksForHelpRepeat";
			Diag.CurrentNode = Diag.TempNode;
			pchar.GenQuest.EncGirl = "Quest_FindLover";
			//pchar.GenQuest.EncGirl.MeetSoldiers = 2; //Coffee TODO: to EncGirl_Soldiers_Check ToFather
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;


		case "DlgGirl_WhatDoesSheDoInJungle": //Если она дала бабло за спасение в джунглях и заговорили с ней; если проводили до города
			DeleteAttribute(pchar, "quest.LandEnc_EncGirl_CloseQuestExit");
			bOk1 = GetCharacterIndex(npchar.city + "_Priest") > -1;
			bOk2 = sti(pchar.rank) > 10;
			if (bOk1 && bOk1) i = rand(2);
			else if (bOk1) i = rand(1); //Есть церковь, но нет ранга
			else if (bOk2) //Есть ранг, но нет церкви
			{
				i = rand(1);
				if (i == 1) i = 2;
			}
			else i = 0;
i = 0; //Coffee test
			switch (i)
			{
				case 0:
					if (rand(1))
					{
						dialog.text = StringFromKey("EncGirl_Girl_95");
						link.l1 = StringFromKey("EncGirl_Girl_96", pchar);
					}
					else
					{
						dialog.text = StringFromKey("EncGirl_Girl_97");
						link.l1 = StringFromKey("EncGirl_Girl_98");
					}
					if ("Quest_Escort_ToTown_Should" == pchar.GenQuest.EncGirl)
						link.l1.go = "DlgGirl_Escort_GoodEnd";
					else
						link.l1.go = "DlgGirl_InJungle_GoodEnd";
				break;
				case 1:
					dialog.text = StringFromKey("EncGirl_Girl_99");
					link.l1 = StringFromKey("EncGirl_Girl_100");
					link.l1.go = "Pearls_BeginQuest";
				break;
				case 2: //treasure journey
					dialog.text = StringFromKey("EncGirl_Girl_101");
					link.l1 = StringFromKey("EncGirl_Girl_102");
					link.l1.go = "Treasure_FathersMap";  //Coffee тестить отсюда, ref EncGirl_Death EncGirl_DeleteGirlGroup
				break;
			}
		break;

		case "DlgGirl_InJungle_GoodEnd":
			EncGirl_SheIsInSafe();
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "36");
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("JungleGirl", "sRapersResult", " " +StringFromKey("EncGirl_Girl_291"));
			AddQuestUserData("JungleGirl", "WhatDoesSheDoResult", ""); //Она просто гуляла
			CloseQuestHeader("JungleGirl");
			EncGirlBecameCitizenNoGroup(npchar, "Close_close");
			DialogExit();
		break;
//WhatDoesSheDoInJungle case 1 Pearls -->
		case "Pearls_BeginQuest":
			pchar.GenQuest.EncGirl.SmallPearls = its(rand(25) + 20);
			pchar.GenQuest.EncGirl.BigPearls = its(rand(15) + 5);
			pchar.GenQuest.EncGirl.PearlsToPiastres =
				its((sti(pchar.GenQuest.EncGirl.SmallPearls) * sti(Items[FindItem("Jewelry12")].price)
				 + sti(pchar.GenQuest.EncGirl.BigPearls) * sti(Items[FindItem("Jewelry11")].price)) * 2);
			dialog.text = StringFromKey("EncGirl_Girl_103", sti(pchar.GenQuest.EncGirl.BigPearls), sti(pchar.GenQuest.EncGirl.SmallPearls));
			link.l1 = StringFromKey("EncGirl_Girl_104");
			link.l1.go = "Pearls_RefuseToHelp";
			link.l2 = StringFromKey("EncGirl_Girl_105");
			link.l2.go = "Pearls_AboutToHelpHer";
		break;

		case "Pearls_RefuseToHelp":
			AddSimpleRumour(StringFromKey("Common_rumours_137", pchar.GenQuest.EncGirl.name), sti(pchar.GenQuest.EncGirl.nation), 5, 1);
			ChangeCharacterReputation(pchar, -2);

			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "35");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sPearlsResult", StringFromKey("EncGirl_Girl_293", pchar));
			CloseQuestHeader("JungleGirl");

			EncGirlBecameCitizen(npchar, "Close_close");
			npchar.chr_ai.disableDlg = "1";
			DialogExit();
		break;

		case "Pearls_AboutToHelpHer":
			dialog.text = StringFromKey("EncGirl_Girl_146");
			link.l1 = StringFromKey("EncGirl_Girl_147", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1.go = "Pearls_SheRunsToChurch";
			if (sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.PearlsToPiastres))
			{
				link.l2 = StringFromKey("EncGirl_Girl_148", FindMoneyString(sti(pchar.GenQuest.EncGirl.PearlsToPiastres)));
				link.l2.go = "Pearls_PayMoney";
			}
		break;

		case "Pearls_PayMoney":
			dialog.text = StringFromKey("EncGirl_Girl_158", pchar);
			link.l1 = StringFromKey("EncGirl_Girl_159");
			link.l1.go = "Pearls_PayMoneyEnd";
		break;

		case "Pearls_PayMoneyEnd":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "35");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sPearlsResult", StringFromKey("EncGirl_Girl_292", pchar, FindMoneyString(sti(pchar.GenQuest.EncGirl.PearlsToPiastres))));
			CloseQuestHeader("JungleGirl");
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.EncGirl.PearlsToPiastres));
			ChangeCharacterReputation(pchar, 5); //5 сейчас и 5 после закрытия
			EncGirl_CloseQuestExit("Close_SheIsInSafe");
			EncGigl_SheFleeAway(false, false);
			DialogExit();
		break;

		case "Pearls_SheRunsToChurch":
			pchar.quest.EncGirl_Pearls_ToChurch.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_Pearls_ToChurch.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_Pearls_ToChurch.function = "EncGirl_Pearls_ToChurch_Func";
			pchar.quest.EncGirl_Pearls_TimeIsUp.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_Pearls_TimeIsUp.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			pchar.quest.EncGirl_Pearls_TimeIsUp.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.EncGirl_Pearls_TimeIsUp.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			pchar.quest.EncGirl_Pearls_TimeIsUp.function = "EncGirl_Pearls_TimeIsUp_Func";
			LAi_SetActorTypeNoGroup(npchar);
			if (CheckAttribute(loadedlocation, "locators.reload.reload7_back"))
			{
				LAi_ActorRunToLocation(npchar, "reload", "reload7_back", "none", "", "", "OpenTheDoors", 30.0);
			}
			else
			{
				sTemp = LAi_FindNearestFreeLocator2Pchar("reload");// Лесник (Slayer). Девица убегает, если ГГ сказал ждать в цервки
				LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", 30.0);
			}
			Diag.TempNode = "Pearls_SheWaitsForPearls";
			Diag.CurrentNode = Diag.TempNode;
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "1");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sText1", sti(pchar.GenQuest.EncGirl.BigPearls));
			AddQuestUserData("JungleGirl", "sText2", sti(pchar.GenQuest.EncGirl.SmallPearls));
			DialogExit();
		break;

		case "Pearls_SheWaitsForPearls":
			dialog.text = StringFromKey("EncGirl_Girl_151", RandPhraseSimple(
						StringFromKey("EncGirl_Girl_149", pchar),
						StringFromKey("EncGirl_Girl_150")));
			if (GetCharacterItem(pchar, "jewelry11") >= sti(pchar.GenQuest.EncGirl.BigPearls) && GetCharacterItem(pchar, "jewelry12") >= sti(pchar.GenQuest.EncGirl.SmallPearls))
			{
				link.l1 = StringFromKey("EncGirl_Girl_152");
				link.l1.go = "Pearls_GiveHerPearls";
			}
			else
			{
				link.l1 = StringFromKey("EncGirl_Girl_153");
				link.l1.go = "Pearls_NotEnoughPearls";
			}
		break;

		case "Pearls_GiveHerPearls":
			TakeNItems(pchar, "jewelry11", -sti(pchar.GenQuest.EncGirl.BigPearls));
			TakeNItems(pchar, "jewelry12", -sti(pchar.GenQuest.EncGirl.SmallPearls));
			pchar.quest.EncGirl_Pearls_TimeIsUp.over = "yes";
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			dialog.text = StringFromKey("EncGirl_Girl_154", pchar);
			link.l1 = StringFromKey("EncGirl_Girl_155", pchar);
			link.l1.go = "Pearls_SheGivesYouReward";
		break;

		case "Pearls_NotEnoughPearls":
			dialog.text = StringFromKey("EncGirl_Girl_156", pchar);
			link.l1 = StringFromKey("EncGirl_Girl_157");
			link.l1.go = "exit_stay";
		break;

		case "Pearls_SheGivesYouReward":
			TakeNItemsNotification(pchar, pchar.GenQuest.EncGirl.item, 1, "default", "", "");
			AddQuestRecord("JungleGirl", "2");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterReputation(pchar, 5); //5 сейчас и 5 после закрытия
			EncGirl_CloseQuestExit("Close_SheIsInSafe");
			EncGigl_SheFleeAway(true, true);
			DialogExit();
		break;
// <-- WhatDoesSheDoInJungle case 1 Pearls
//WhatDoesSheDoInJungle case 2 treasure journey -->
		case "Treasure_FathersMap":
			pchar.GenQuest.EncGirl.mapOwner = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = StringFromKey("EncGirl_Girl_106", GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_PRE));
			link.l1 = StringFromKey("EncGirl_Girl_107", pchar);
			link.l1.go = "Treasure_FatherFormerPirat";
		break;

		case "Treasure_FatherFormerPirat":
			dialog.text = StringFromKey("EncGirl_Girl_108", GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_NOM));
			link.l1 = StringFromKey("EncGirl_Girl_109");
			link.l1.go = "Treasure_TalkAboutVessel";
		break;

		case "Treasure_TalkAboutVessel":
			dialog.text = StringFromKey("EncGirl_Girl_110");
			link.l1 = StringFromKey("EncGirl_Girl_111");
			link.l1.go = "Treasure_LeaveHer_End";
			if (GetCharacterItem(pchar, "map_full") == 0)
			{
				link.l2 = StringFromKey("EncGirl_Girl_112");
				link.l2.go = "Treasure_MapBargain";
			}
			link.l3 = StringFromKey("EncGirl_Girl_113");
			link.l3.go = "Treasure_OfferHerJourney";
		break;

		case "Treasure_LeaveHer_End":
			Diag.TempNode = "DlgGirl_SheThanksForHelpRepeat";

			if ("Escort_ToTown_Should" == pchar.GenQuest.EncGirl)
			{
				EncGirl_Escort_CloseLogbook_Good();
				EncGirlBecameCitizen(npchar, "Close_SheIsInSafe");
			}
			else //Запись в журнал не делаем
			{
				EncGirl_CloseQuestExit("Close_SheIsInSafe");
			    EncGigl_SheFleeAway(false, true);
			}

			pchar.GenQuest.EncGirl = "Quest_Treasure_LeaveHer_End";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Treasure_MapBargain":
			dialog.text = StringFromKey("EncGirl_Girl_114");
			link.l1 = StringFromKey("EncGirl_Girl_115");
			link.l1.go = "Treasure_MapPrice";
		break;

		case "Treasure_MapPrice":
			i = 20000 + 500 * sti(pchar.rank);
			pchar.GenQuest.EncGirl.mapPrice = i;
			dialog.text = StringFromKey("EncGirl_Girl_116");
			link.l1 = StringFromKey("EncGirl_Girl_117", FindMoneyString(i));
			link.l1.go = "Treasure_MapArgue";
		break;

		case "Treasure_MapArgue":
			if ((GetSummonSkillFromName(pchar, SKILL_COMMERCE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)) > (rand(220) + 100) && (makeint(pchar.money) >= sti(pchar.GenQuest.EncGirl.mapPrice)))
			{
				PlayerRPGCheck_Skill_NotifyPass(SKILL_COMMERCE);
				PlayerRPGCheck_Skill_NotifyPass(SKILL_LEADERSHIP);
				PlayerRPGCheck_Skill_NotifyPass(SKILL_FORTUNE);
				dialog.text = StringFromKey("EncGirl_Girl_118", pchar);
				link.l1 = StringFromKey("EncGirl_Girl_119");
				link.l1.go = "Treasure_MapIsYour";
			}
			else
			{
				if ((makeint(pchar.money) >= sti(pchar.GenQuest.EncGirl.mapPrice)))
				{
					PlayerRPGCheck_Skill_NotifyFail(SKILL_COMMERCE, true);
					PlayerRPGCheck_Skill_NotifyFail(SKILL_LEADERSHIP, false);
					PlayerRPGCheck_Skill_NotifyFail(SKILL_FORTUNE, false);
				}
				dialog.text = StringFromKey("EncGirl_Girl_120", pchar);
				link.l1 = StringFromKey("EncGirl_Girl_121");
				link.l1.go = "Treasure_LeaveHer_End";
			}
		break;

		case "Treasure_MapIsYour":
			ClearActiveStageNotifications();
			TakeNItemsNotification(pchar, "map_full", 1, StringFromKey("InfoMessages_257"), "MapsAtlas", "noSound");
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.mapPrice)));

			//if (pchar.GenQuest.EncGirl == "Quest_InJungle_SheGaveYouMoney") //Coffee Чекнуть что это и зачем
			if ("Quest_Escort_ToTown_Should" == pchar.GenQuest.EncGirl)
			{
				pchar.GenQuest.EncGirl = "Quest_Treasure_MapIsYour";
			    EncGirl_Escort_CloseLogbook_Good();

			}
			else
			{
				pchar.GenQuest.EncGirl = "Quest_Treasure_MapIsYour";
				AddQuestRecord("JungleGirl", "36");
				AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
				AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","а"));
				AddQuestUserData("JungleGirl", "sRapersResult", " " +StringFromKey("EncGirl_Girl_291"));
				AddQuestUserData("JungleGirl", "WhatDoesSheDoResult", StringFromKey("EncGirl_Girl_295", GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_NOM)));
				CloseQuestHeader("JungleGirl");
			}

			EncGirlBecameCitizen(npchar, "Close_SheIsInSafe");
			DialogExit();
		break;

		case "Treasure_OfferHerJourney":
			dialog.text = StringFromKey("EncGirl_Girl_122");
			link.l1 = StringFromKey("EncGirl_Girl_123");
			link.l1.go = "Journey_SheAgrees";
		break;

		case "Journey_SheAgrees":
			dialog.text = StringFromKey("EncGirl_Girl_124", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1 = StringFromKey("EncGirl_Girl_125");
			link.l1.go = "Journey_WhereToGo";
		break;

		case "Journey_WhereToGo":
			EncGirl_GenQuest_GetChestPlaceName();
			dialog.text = StringFromKey("EncGirl_Girl_126", XI_ConvertString(pchar.GenQuest.EncGirl.islandId + "Acc"), XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen"));
			link.l1 = StringFromKey("EncGirl_Girl_127");
			link.l1.go = "Journey_LetsGo";
		break;

		case "Journey_LetsGo":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "4");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sPirateName", GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sTreasureLoc", XI_ConvertString(pchar.GenQuest.EncGirl.islandId));
			AddQuestUserData("JungleGirl", "sShore", XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			pchar.quest.EncGirl_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_Death.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_Death.function = "EncGirl_Death";
			pchar.quest.EncGirl_FindChest.win_condition.l1 = "location";
			pchar.quest.EncGirl_FindChest.win_condition.l1.location = pchar.GenQuest.EncGirl.placeId;
			pchar.quest.EncGirl_FindChest.function = "EncGirl_FindChest";
			SetFunctionExitFromLocationCondition("EncGirl_AddPassenger", pchar.location, false);
			SetFunctionLocationCondition("EncGirl_DialogAtShore", pchar.GenQuest.EncGirl.shoreId, false);
			Diag.TempNode = "DlgGirl_SheThanksForHelpRepeat";
			pchar.GenQuest.EncGirl = "Quest_Journey_LetsGo";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			//AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Journey_ArrivedAtShore": //GenQuests.c EncGirl_DialogAtShore
			dialog.text = StringFromKey("EncGirl_Girl_128");
			link.l1 = StringFromKey("EncGirl_Girl_129");
			link.l1.go = "exit";
			Diag.TempNode = "Journey_ShouldSeekCave";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;

		case "Journey_ShouldSeekCave":
			Diag.TempNode = "Journey_ShouldSeekCave";
			dialog.text = StringFromKey("EncGirl_Girl_130");
			link.l1 = StringFromKey("EncGirl_Girl_131");
			link.l1.go = "exit";
		break;

		case "Journey_TheChestWasFound": //GenQuests.c EncGirl_FindChest
			DeleteAttribute(NPChar, "QuestFollower");
			dialog.text = StringFromKey("EncGirl_Girl_132");
			link.l1 = StringFromKey("EncGirl_Girl_133");
			link.l1.go = "Journey_OpenTheChest";
		break;

		case "Journey_OpenTheChest":
			dialog.text = StringFromKey("EncGirl_Girl_134");
			link.l1 = StringFromKey("EncGirl_Girl_135");
			link.l1.go = "Journey_OpenTheChest_2";
		break;

		case "Journey_OpenTheChest_2":
			dialog.text = StringFromKey("EncGirl_Girl_136");
			link.l1 = StringFromKey("EncGirl_Girl_137", pchar);
			link.l1.go = "Journey_DivideThePrey";
		break;

		case "Journey_DivideThePrey":
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			PChar.quest.EncGirl_DialogAtShore.over = "yes"; // Лесник (Slayer). Снял прерывание, если не с той бухты зашел
			LAi_LocationDisableMonstersGen(pchar.location, false);
			LogSound_WithNotify(StringFromKey("InfoMessages_197"), "Important_item", "ICollection");
			TakeNItems(pchar, "incas_collection", 1 + drand(1));
			TakeNItems(pchar, "chest", 2 + drand(6));
			TakeNItems(pchar, "jewelry1", 30 + drand(15));
			TakeNItems(pchar, "jewelry2", 30 + drand(15));
			TakeNItems(pchar, "jewelry3", 30 + drand(15));
			TakeNItems(pchar, "jewelry11", 30 + drand(15));
			TakeNItems(pchar, "jewelry5", 30 + rand(10));
			TakeNItems(pchar, "jewelry15", 10 + rand(10));
			TakeNItems(pchar, "jewelry18", 20 + rand(10));
			TakeNItems(pchar, "jewelry14", 30 + rand(10));
			TakeNItems(pchar, "jewelry7", 50 + rand(20));
			AddQuestRecord("JungleGirl", "6");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("JungleGirl", "sPirateName", GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			pchar.GenQuest.EncGirl = "Quest_ChestGetted";
			pchar.quest.EncGirl_EscortTo.win_condition.l1 = "location";
			pchar.quest.EncGirl_EscortTo.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_EscortTo.function = "EncGirl_EscortTo_Done";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathAgain.function = "EncGirl_DeathAgain";
			Diag.TempNode = "Journey_SheIsGlad";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;

		case "Journey_SheIsGlad":
			Diag.TempNode = "TreasureJourney_SheIsGlad";
			dialog.text = StringFromKey("EncGirl_Girl_138");
			link.l1 = StringFromKey("EncGirl_Girl_139", pchar);
			link.l1.go = "exit";
		break;

		case "Journey_ArrivedBackToTown": //GenQuests.c EncGirl_EscortTo ChestGetted
			dialog.text = StringFromKey("EncGirl_Girl_140");
			link.l1 = StringFromKey("EncGirl_Girl_141");
			link.l1.go = "Journey_AtHome_1";
		break;

		case "Journey_AtHome_1":
			dialog.text = StringFromKey("EncGirl_Girl_142");
			link.l1 = StringFromKey("EncGirl_Girl_143");
			link.l1.go = "Journey_AtHome_1";
		break;

		case "Journey_AtHome_2":
			dialog.text = StringFromKey("EncGirl_Girl_144");
			link.l1 = StringFromKey("EncGirl_Girl_145", pchar);
			link.l1.go = "Journey_EndReward";
		break;

		case "Journey_EndReward":
			RemovePassenger(pchar, npchar);
			AddItemLog(pchar, pchar.GenQuest.EncGirl.item, "1", StringFromKey("InfoMessages_135", GetItemName(pchar.GenQuest.EncGirl.item)), "Took_item");
			AddQuestRecord("JungleGirl", "8");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			//AddDialogExitQuest("pchar_back_to_player");
			EncGigl_SheFleeAway(true, true);
			pchar.quest.EncGirl_EnterToSea.over = "yes";    // Лесник (Slayer). Снял прерывание, если не с той бухты зашёл
			PChar.quest.EncGirl_DialogAtShore.over = "yes";    // Лесник (Slayer). Снял прерывание, если не с той бухты зашёл
		break;
// <-- WhatDoesSheDoInJungle case 2 treasure journej


		case "DlgGirl_InJungle_BoughtOut_BlameWhore":
			dialog.text = StringFromKey("EncGirl_Girl_192", pchar);
			link.l1 = StringFromKey("EncGirl_Girl_193", pchar);
			link.l1.go = "DlgGirl_InJungle_BoughtOut_BlameWhore_Close";
		break;

		case "DlgGirl_InJungle_BoughtOut_BlameWhore_Close":
			EncGirl_CloseQuestExit("Close_Rapers_BoughtOutWhore");
			EncGigl_SheFleeAway(false, false);
			DialogExit();
		break;

		case "DlgGirl_InJungle_BoughtOut_CaveWhore":
			if (true) //(rand(1) == 1 && sti(pchar.reputation) > 50)//Coffee
			{
				dialog.text = StringFromKey("EncGirl_Girl_169");
				link.l1 = StringFromKey("EncGirl_Girl_171");
				link.l1.go = "DlgGirl_Escort_ToCaveFromJungle_WhatsWrong";
				link.l2 = StringFromKey("EncGirl_Girl_170");
				link.l2.go = "DlgGirl_InJungle_CaveWhore_BrushHerOff";
			}
			else
			{
				dialog.text = StringFromKey("EncGirl_Girl_172", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
				link.l1 = StringFromKey("EncGirl_Girl_176", RandPhraseSimple(
							StringFromKey("EncGirl_Girl_174"),
							StringFromKey("EncGirl_Girl_175")));
				link.l1.go = "DlgGirl_Escort_ToTOWN_FromJungle_Begin";
				link.l2 = StringFromKey("EncGirl_Girl_173");
				link.l2.go = "DlgGirl_InJungle_RejectEscort";
				Diag.NodeEscortTo = "DlgGirl_Escort_ToTOWN_FromJungle_Begin";
			}
		break;

		case "DlgGirl_InJungle_CaveWhore_BrushHerOff":
			EncGirlBecameCitizenNoGroup(npchar, "Close_InJungle_AbandonHer");
			if (!HasSubStr(loadedlocation.id, "ExitTown")) EncGigl_SheFleeAway(false, false);
			npchar.chr_ai.disableDlg = "1";

			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "36");
			AddQuestUserData("JungleGirl", "sRapersResult", " " +StringFromKey("EncGirl_Girl_289") +" " +FindMoneyString(sti(pchar.GenQuest.EncGirl.price)) +".");
			AddQuestUserData("JungleGirl", "WhatDoesSheDoResult", StringFromKey("EncGirl_Girl_290"));
			CloseQuestHeader("JungleGirl");

			DialogExit();
		break;

		case "DlgGirl_Escort_ToCaveFromJungle_WhatsWrong":
			dialog.text = StringFromKey("EncGirl_Girl_177");
			link.l1 = StringFromKey("EncGirl_Girl_178");
			link.l1.go = "DlgGirl_Escort_ToCaveFromJungle_AboutFather";
		break;

		case "DlgGirl_Escort_ToCaveFromJungle_AboutFather":
			dialog.text = StringFromKey("EncGirl_Girl_179");
			link.l1 = StringFromKey("EncGirl_Girl_180");
			link.l1.go = "DlgGirl_Escort_ToCaveFromJungle_SheAsks";
		break;

		case "DlgGirl_Escort_ToCaveFromJungle_SheAsks":
			dialog.text = StringFromKey("EncGirl_Girl_181");
			link.l1 = StringFromKey("EncGirl_Girl_183");
			link.l1.go = "DlgGirl_Escort_ToCaveFromJungle_Go";
			link.l2 = StringFromKey("EncGirl_Girl_182");
			link.l2.go = "DlgGirl_InJungle_RejectEscort";
			Diag.NodeEscortTo = "DlgGirl_Escort_ToCaveFromJungle_Begin";
		break;

		case "DlgGirl_Escort_ToCaveFromJungle_Go":
			dialog.text = StringFromKey("EncGirl_Girl_184");
			link.l1 = StringFromKey("EncGirl_Girl_185");
			link.l1.go = "DlgGirl_Escort_ToCaveFromJungle_Begin";
		break;

		case "Node_207":
			DeleteAttribute(NPChar, "QuestFollower");
			dialog.text = StringFromKey("EncGirl_Girl_188");
			link.l1 = StringFromKey("EncGirl_Girl_189");
			link.l1.go = "Node_208";
		break;

		case "Node_208":
			dialog.text = StringFromKey("EncGirl_Girl_190", pchar);
			link.l1 = StringFromKey("EncGirl_Girl_191");
			link.l1.go = "Node_209";
		break;

		case "Node_209":
			LAi_LocationDisableMonstersGen(pchar.location, false);
			i = makeint(sti(pchar.GenQuest.EncGirl.price) * 0.01);
			TakeNItems(pchar, "jewelry17", i);
			PlaySound("Took_item");
			EncGigl_SheFleeAway(false, true);
			pchar.quest.EncGirl_RapersExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_RapersExit.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_RapersExit.function = "EncGirl_MeetRapers";
			DialogExit();
		break;

		case "DlgGirl_Escort_ToTAVERN_FromJungle_SheAsks_BoughtOutWhore":
			dialog.text = StringFromKey("EncGirl_Girl_194", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1 = StringFromKey("EncGirl_Girl_195");
			link.l1.go = "DlgGirl_Escort_ToTAVERN_FromJungle_Begin";
			link.l2 = StringFromKey("EncGirl_Girl_67");
			link.l2.go = "DlgGirl_InJungle_RejectEscort";
			Diag.NodeEscortTo = "DlgGirl_Escort_ToTAVERN_FromJungle_Begin";
		break;

		case "DlgGirl_Escort_ToTAVERN_FromJungle_SheAsks_EscapedWhore":
			dialog.text = StringFromKey("EncGirl_Girl_196", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1 = StringFromKey("EncGirl_Girl_198");
			link.l1.go = "DlgGirl_Escort_ToTavern_FromJungle_Accept_EscapedWhore";
			link.l2 = StringFromKey("EncGirl_Girl_197");
			link.l2.go = "DlgGirl_InJungle_RejectEscort";
			Diag.NodeEscortTo = "DlgGirl_Escort_ToTAVERN_FromJungle_Begin";
		break;
		case "DlgGirl_Escort_ToTavern_FromJungle_Accept_EscapedWhore":
			dialog.text = StringFromKey("EncGirl_Girl_199");
			link.l1 = StringFromKey("EncGirl_Girl_200");
			link.l1.go = "DlgGirl_Escort_ToTAVERN_FromJungle_Begin";
		break;

		case "DlgGirl_Escort_InTavern_EscortDone":
			DeleteAttribute(NPChar, "QuestFollower");
			if (PChar.sex != "woman" || dRand(1) == 0)
			{
				dialog.text = StringFromKey("EncGirl_Girl_205");
				link.l1 = StringFromKey("EncGirl_Girl_209", LinkRandPhrase(
							StringFromKey("EncGirl_Girl_206"),
							StringFromKey("EncGirl_Girl_207"),
							StringFromKey("EncGirl_Girl_208")));
				link.l1.go = "DlgGirl_InTavern_BrushHerOff";
				if ("Quest_InTavern_ToRoom_Should" == pchar.GenQuest.EncGirl) //Квест пока не закрываем
				{
					link.l1 = StringFromKey("EncGirl_Girl_301") +" " +link.l1;
					link.l2 = StringFromKey("EncGirl_Girl_288");
					link.l2.go = "exit_stay";
				}
				else
				{
					link.l2 = StringFromKey("EncGirl_Girl_210");
					link.l2.go = "DlgGirl_InTavern_GoToBarmanForRoom";
				}
			}
			else
			{
				dialog.text = StringFromKey("EncGirl_Girl_211", pchar);
				link.l1 = StringFromKey("EncGirl_Girl_212");
				link.l1.go = "DlgGirl_Escort_GoodEnd";
			}
		break;

		case "DlgGirl_InTavern_GoToBarmanForRoom":
			Diag.TempNode = "DlgGirl_Escort_InTavern_EscortDone";
			Diag.CurrentNode = Diag.TempNode;
			pchar.GenQuest.EncGirl = "Quest_InTavern_ToRoom_ToBarman";
			pchar.quest.EncGirl_Escort_ToRoom.win_condition.l1 = "location";
			pchar.quest.EncGirl_Escort_ToRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			pchar.quest.EncGirl_Escort_ToRoom.function = "EncGirl_InTavern_ToRoom_Done";

			DeleteAttribute(pchar, "quest.LandEnc_EncGirl_CloseQuestExit"); //Не закрывать квест при смене локации
			pchar.quest.EncGirl_Escort_ToRoom_Fail.win_condition.l1 = "NOTlocation"; //передумали и свалили из таверны
			pchar.quest.EncGirl_Escort_ToRoom_Fail.win_condition.l1.CurLocation = pchar.location;
			pchar.quest.EncGirl_Escort_ToRoom_Fail.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			pchar.quest.EncGirl_Escort_ToRoom_Fail.function = "EncGirl_Escort_ToTavernFromTown_Fail";

			TurnNPCToPcharInit(NPChar);
			EncGirlDialogExit();
		break;

		case "DlgGirl_InTavern_SpeakInRoom":
			LAi_LockFightMode(pchar, false);
			if (CheckAttribute(pchar, "GenQuest.EncGirl.EscapedFromBrothel"))
			{
				DeleteAttribute(pchar, "GenQuest.EncGirl.EscapedFromBrothel");
				dialog.text = StringFromKey("EncGirl_Girl_213");
				link.l1 = StringFromKey("EncGirl_Girl_214");
				link.l1.go = "DlgGirl_InTavern_BrushHerOff";
				link.l2 = StringFromKey("EncGirl_Girl_215");
				link.l2.go = "Node_233";
			}
			else
			{
				dialog.text = StringFromKey("EncGirl_Girl_216");
				link.l1 = StringFromKey("EncGirl_Girl_217");
				link.l1.go = "DlgGirl_InTavern_GoSex";
				link.l2 = StringFromKey("EncGirl_Girl_218");
				link.l2.go = "DlgGirl_InTavern_RejectSex";
			}
		break;

		case "DlgGirl_InTavern_GoSex":
			dialog.text = StringFromKey("EncGirl_Girl_219");
			link.l1 = StringFromKey("EncGirl_Girl_220");
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "Quest_InTavern_GoodFuck";
			EncGirl_CloseQuestExit("Close_Intavern_GoodFuck");
			AddDialogExitQuest("PlaySex_1");
			chrDisableReloadToLocation = false;
		break;

		case "DlgGirl_InTavern_RejectSex":
			dialog.text = StringFromKey("EncGirl_Girl_221");
			link.l1 = StringFromKey("EncGirl_Girl_222");
			link.l1.go = "DlgGirl_InTavern_ToBurglar";
		break;

		case "DlgGirl_InTavern_ToBurglar":
			dialog.text = StringFromKey("EncGirl_Girl_223");
			link.l1 = StringFromKey("EncGirl_Girl_224");
			link.l1.go = "DlgGirl_InTavern_SetBurglar";
		break;

		case "DlgGirl_InTavern_SetBurglar":
			ChangeCharacterReputation(pchar, 1);
			EncGigl_SheFleeAway(true, true);

			if (idRand(pchar.GenQuest.EncGirl.city +"BurglarEncGirl", 2) == 0)
			{
				EncGirl_CloseQuestExit("Close_Escort_ToTown_Done");
				EncGirl_CloseQuestExit_func("");
			}
			else //Спавним сутенёра
			{
				DoQuestFunctionDelay("EncGirl_InTavern_SetBurglar", 3.0);
				DisableAllExits(true);
				LAi_LockFightMode(pchar, true);

				pchar.quest.EncGirl_InTavern_EndBurglar.win_condition.l1 = "NOTlocation";
				pchar.quest.EncGirl_InTavern_EndBurglar.win_condition.l1.CurLocation = pchar.location;
				pchar.quest.EncGirl_InTavern_EndBurglar.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
				pchar.quest.EncGirl_InTavern_EndBurglar.function = "EncGirl_InTavern_BurglarEnd";
			}

			DialogExit();
		break;

		case "Node_233":
			pchar.GenQuest.EncGirl.Parents_City = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			dialog.text = StringFromKey("EncGirl_Girl_225", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			link.l1 = StringFromKey("EncGirl_Girl_226");
			link.l1.go = "Node_234";
		break;

		case "Node_234":
			dialog.text = StringFromKey("EncGirl_Girl_227");
			link.l1 = StringFromKey("EncGirl_Girl_228");
			link.l1.go = "Node_235";
			link.l2 = StringFromKey("EncGirl_Girl_229");
			link.l2.go = "Node_236";
			if (sti(pchar.money) >= 5000)
			{
				link.l3 = StringFromKey("EncGirl_Girl_230");
				link.l3.go = "Node_237";
			}
		break;

		case "Node_235":
			dialog.text = StringFromKey("EncGirl_Girl_231");
			link.l1 = StringFromKey("EncGirl_Girl_232");
			link.l1.go = "Node_240";
		break;

		case "Node_240":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "20");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			AddQuestUserData("JungleGirl", "sBrothelCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city + "Gen"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			OfficersReaction("bad");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 3.0);
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1.location = pchar.GenQuest.EncGirl.Parents_City + "_town";
			pchar.quest.EncGirl_DeliveToParents.function = "EncGirl_DeliveToParents";
			DialogExit();
		break;

		case "Node_236":
			dialog.text = StringFromKey("EncGirl_Girl_233");
			link.l1 = StringFromKey("EncGirl_Girl_234");
			link.l1.go = "Node_239";
		break;

		case "Node_239":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "21");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			pchar.quest.EncGirl_GenerateBag.win_condition.l1 = "location";
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) > rand(100))
			{
				pchar.GenQuest.EncGirl = "Quest_Bag_BrothelRoomUp";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_Brothel_room";
			}
			else
			{
				pchar.GenQuest.EncGirl = "Quest_Bag_BrothelRoom";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_SecBrRoom";
			}
			pchar.quest.EncGirl_GenerateBag.function = "EncGirl_GenerateLeatherBag";

			pchar.quest.EncGirl_GetBagFail.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.function = "EncGirl_GenQuest_GetBag";

			pchar.quest.EncGirl_ExitRoom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitRoom.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitRoom.function = "EncGirl_ExitTavernRoom";

			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;

		case "Node_240_1":
			pchar.quest.EncGirl_GetBagFail.over = "yes";
			dialog.text = StringFromKey("EncGirl_Girl_235");
			if (CheckCharacterItem(pchar, "leather_bag"))
			{
				link.l1 = StringFromKey("EncGirl_Girl_236");
				link.l1.go = "Node_241";
			}
			else
			{
				link.l1 = StringFromKey("EncGirl_Girl_237", pchar);
				link.l1.go = "Node_242";
			}
		break;

		case "Node_241":
			TakeNItems(pchar, "leather_bag", -1);
			dialog.text = StringFromKey("EncGirl_Girl_238", pchar);
			link.l1 = StringFromKey("EncGirl_Girl_239");
			link.l1.go = "Node_243";
		break;

		case "Node_242":
			dialog.text = StringFromKey("EncGirl_Girl_240");
			if (sti(pchar.money) >= 5000)
			{
				link.l1 = StringFromKey("EncGirl_Girl_241");
				link.l1.go = "Node_237";
			}
			link.l2 = StringFromKey("EncGirl_Girl_242");
			link.l2.go = "Node_244";
		break;

		case "Node_243":
			EncGigl_SheFleeAway(true, true);
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "ла"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("", "а"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterReputation(pchar, 1);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;

		case "Node_244":
			EncGigl_SheFleeAway(true, true);
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterReputation(pchar, -5);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;

		case "Node_245":
			dialog.text = StringFromKey("EncGirl_Girl_243");
			link.l1 = StringFromKey("EncGirl_Girl_244", pchar);
			link.l1.go = "Node_246";
		break;

		case "Node_246":
			dialog.text = StringFromKey("EncGirl_Girl_245");
			link.l1 = StringFromKey("EncGirl_Girl_246");
			link.l1.go = "Node_247";
		break;

		case "Node_247":
			EncGigl_SheFleeAway(false, true);
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "24");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			CloseQuestHeader("JungleGirl");
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;

		case "Node_237":
			dialog.text = StringFromKey("EncGirl_Girl_247");
			i = makeint(pchar.money);
			if (i >= 5000)
			{
				link.l1 = StringFromKey("EncGirl_Girl_248");
				link.l1.go = "Node_237_1";
			}
			if (i >= 25000)
			{
				link.l2 = StringFromKey("EncGirl_Girl_249");
				link.l2.go = "Node_237_2";
			}
			if (i >= 35000)
			{
				link.l3 = StringFromKey("EncGirl_Girl_250");
				link.l3.go = "Node_237_3";
			}
		break;

		case "Node_237_1":
			AddMoneyToCharacter(pchar, -5000);
			ChangeCharacterReputation(pchar, -5);
			dialog.text = StringFromKey("EncGirl_Girl_251", pchar);
			link.l1 = StringFromKey("EncGirl_Girl_252");
			link.l1.go = "Node_238";
			pchar.GenQuest.EncGirl = "Quest_EncGirlFack_GetMoney";
		break;

		case "Node_237_2":
			AddMoneyToCharacter(pchar, -25000);
			ChangeCharacterReputation(pchar, 1);
			dialog.text = StringFromKey("EncGirl_Girl_253", pchar);
			link.l1 = StringFromKey("EncGirl_Girl_254");
			link.l1.go = "Node_238";
		break;

		case "Node_237_3":
			AddMoneyToCharacter(pchar, -35000);
			ChangeCharacterReputation(pchar, 2);
			dialog.text = StringFromKey("EncGirl_Girl_255", pchar);
			link.l1 = StringFromKey("EncGirl_Girl_256");
			link.l1.go = "Node_238";
		break;

		case "Node_238":
			EncGigl_SheFleeAway(false, true);
			if (pchar.GenQuest.EncGirl == "Quest_EncGirlFack_GetMoney")
			{
				AddSimpleRumour(
							StringFromKey("EncGirl_Girl_259", RandPhraseSimple(
									StringFromKey("EncGirl_Girl_257"),
									StringFromKey("EncGirl_Girl_258"))), sti(pchar.GenQuest.EncGirl.nation), 3, 1);
			}
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;

		case "SheHasALover":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man");
			dialog.text = StringFromKey("EncGirl_Girl_262", pchar.GenQuest.EncGirl.sLoverId, XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1 = StringFromKey("EncGirl_Girl_263");
			link.l1.go = "Escort_ToParentsFromJungle";
		break;

		case "Escort_ToParentsFromJungle":
			Diag.TempNode = "DlgGirl_Escort_ToTown_YouPromised";
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "9");
			AddQuestUserData("JungleGirl", "sText", pchar.GenQuest.EncGirl.FatherGen);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sLover", pchar.GenQuest.EncGirl.sLoverId);
			 //Coffee TODO: to EncGirl_Soldiers_Check ToFather
			//pchar.GenQuest.EncGirl.MeetSoldiers = 2; //Отец обратился к солдатам, чтобы её найти
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;

		case "DlgGirl_Escort_ToTown_Done":
			DeleteAttribute(NPChar, "QuestFollower");
			if (rand(1))
			{
				dialog.text = StringFromKey("EncGirl_Girl_270", RandPhraseSimple(
							StringFromKey("EncGirl_Girl_268", pchar),
							StringFromKey("EncGirl_Girl_269", pchar)));
				link.l1 = StringFromKey("EncGirl_Girl_273", RandPhraseSimple(
							StringFromKey("EncGirl_Girl_271"),
							StringFromKey("EncGirl_Girl_272")));
				link.l1.go = "DlgGirl_Escort_GoodEnd";
				link.l2 = StringFromKey("EncGirl_Girl_274");
				link.l2.go = "DlgGirl_WhatDoesSheDoInJungle";
			}
			else
			{
				dialog.text = StringFromKey("EncGirl_Girl_275", pchar);
				link.l1 = StringFromKey("EncGirl_Girl_276", pchar);
				link.l1.go = "DlgGirl_Escort_ToTavern_FromTown_SheAsks";
			}
		break;

		case "DlgGirl_Escort_ToTavern_FromTown_SheAsks":
			dialog.text = StringFromKey("EncGirl_Girl_277");
			link.l1 = StringFromKey("EncGirl_Girl_278", pchar);
			link.l1.go = "DlgGirl_Escort_GoodEnd";
			link.l2 = StringFromKey("EncGirl_Girl_279", pchar);
			link.l2.go = "DlgGirl_Escort_ToTavern_FromTown_Begin";
		break;

//Начинаем эскорт -->
		case "DlgGirl_Escort_ToCaveFromJungle_Begin":
			DeleteAttribute(pchar, "quest.LandEnc_EncGirl_CloseQuestExit");
			pchar.GenQuest.EncGirl = "Quest_Escort_ToCave_Should";

			Diag.TempNode = "Escort_ToCaveFromJungle_YouPromised";

			pchar.quest.EncGirl_FindTreasure.win_condition.l1 = "location";
			pchar.quest.EncGirl_FindTreasure.win_condition.l1.location = GetLocationForTreasure(GetArealByCityName(npchar.city));
			pchar.quest.EncGirl_FindTreasure.function = "EncGirl_FindTreasure";

			pchar.quest.EncGirl_Escort_EnterToSea.win_condition.l1 = "EnterToSea";
			pchar.quest.EncGirl_Escort_EnterToSea.function = "EncGirl_Escort_EnterToSea";

			EncGirlEscortBeginAddQuestRecord("cave");

			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;

		case "DlgGirl_Escort_ToTOWN_FromJungle_Begin":
			g_bEncGirl_Sld = rand(9) == 0; //Шанс, что её хотят арестовать
			DeleteAttribute(pchar, "quest.LandEnc_EncGirl_CloseQuestExit");
			pchar.GenQuest.EncGirl = "Quest_Escort_ToTown_Should";

			Diag.TempNode = "DlgGirl_Escort_ToTown_YouPromised";
			Diag.CurrentNode = Diag.TempNode;

			pchar.quest.EncGirl_EscortTo.win_condition.l1 = "location";
			pchar.quest.EncGirl_EscortTo.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_EscortTo.function = "EncGirl_EscortTo_Done";

			pchar.quest.EncGirl_Escort_EnterToSea.win_condition.l1 = "EnterToSea";
			pchar.quest.EncGirl_Escort_EnterToSea.function = "EncGirl_Escort_EnterToSea";

			EncGirlEscortBeginAddQuestRecord("town");

			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			AddDialogExitQuest("pchar_back_to_player");
			DialogExit();
		break;

		case "DlgGirl_Escort_ToTAVERN_FromJungle_Begin":
			g_bEncGirl_Sld = rand(9) == 0;
			DeleteAttribute(pchar, "quest.LandEnc_EncGirl_CloseQuestExit");
			pchar.GenQuest.EncGirl = "Quest_Escort_ToTavern_FromJungle_Should";

			Diag.TempNode = "DlgGirl_Escort_ToTavern_YouPromised";
			Diag.CurrentNode = Diag.TempNode;

			pchar.quest.EncGirl_EscortTo.win_condition.l1 = "location";
			pchar.quest.EncGirl_EscortTo.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_EscortTo.function = "EncGirl_EscortTo_Done";

			pchar.quest.EncGirl_Escort_EnterToSea.win_condition.l1 = "EnterToSea";
			pchar.quest.EncGirl_Escort_EnterToSea.function = "EncGirl_Escort_EnterToSea";

			EncGirlEscortBeginAddQuestRecord("tavern");

			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			AddDialogExitQuest("pchar_back_to_player");
			DialogExit();
		break;

		case "DlgGirl_Escort_ToTavern_FromTown_Begin":
			pchar.quest.EncGirl_Escort_ToTavernFromTown_Fail.win_condition.l1 = "NOTlocation"; //Если пришли не в таверну
			pchar.quest.EncGirl_Escort_ToTavernFromTown_Fail.win_condition.l1.CurLocation = pchar.location;
			pchar.quest.EncGirl_Escort_ToTavernFromTown_Fail.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_Escort_ToTavernFromTown_Fail.function = "EncGirl_Escort_ToTavernFromTown_Fail";

			DeleteAttribute(pchar, "quest.LandEnc_EncGirl_CloseQuestExit");
			pchar.GenQuest.EncGirl = "Quest_Escort_ToTavern_FromTown_Should";

			Diag.TempNode = "DlgGirl_Escort_ToTavern_YouPromised";
			Diag.CurrentNode = Diag.TempNode;

			pchar.quest.EncGirl_EscortTo.win_condition.l1 = "location";
			pchar.quest.EncGirl_EscortTo.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_EscortTo.function = "EncGirl_EscortTo_Done";

			QuestPointerToLocEx(pchar.GenQuest.EncGirl.city +"_Town", "reload", "reload4_back", "JungleGirl");

			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			AddDialogExitQuest("pchar_back_to_player");

			DialogExit();
		break;
//Начинаем эскорт <--
//Напоминалки куда провожаем -->
		case "DlgGirl_Escort_ToTavern_YouPromised":
			dialog.text = StringFromKey("EncGirl_Girl_201", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1 = StringFromKey("EncGirl_Girl_204", RandPhraseSimple(
						StringFromKey("EncGirl_Girl_202"),
						StringFromKey("EncGirl_Girl_203")));
			link.l1.go = "exit";
			EncGirlShouldWeHealHer(link, npchar);
		break;

		case "DlgGirl_Escort_ToTown_YouPromised":
			dialog.text = StringFromKey("EncGirl_Girl_264", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1 = StringFromKey("EncGirl_Girl_267", RandPhraseSimple(
						StringFromKey("EncGirl_Girl_265"),
						StringFromKey("EncGirl_Girl_266")));
			link.l1.go = "exit";
			EncGirlShouldWeHealHer(link, npchar);
		break;

		case "Escort_ToCaveFromJungle_YouPromised":
			dialog.text = StringFromKey("EncGirl_Girl_186", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1 = StringFromKey("EncGirl_Girl_187");
			link.l1.go = "exit";
			EncGirlShouldWeHealHer(link, npchar);
		break;
//Напоминалки куда провожаем <--
		case "DlgGirl_Escort_ToTavern_FromJungle_RememberInCity":
				dialog.text = StringFromKey("EncGirl_Girl_302");
				link.l1 = StringFromKey("EncGirl_Girl_303");
				link.l1.go = "DlgGirl_Escort_ToTavern_FromTown_Begin";
				link.l2 = StringFromKey("EncGirl_Girl_304");
				link.l2.go = "DlgGirl_Escort_ToTavern_FromJungle_RejectInCity";
		break;
		case "DlgGirl_Escort_ToTavern_FromJungle_RejectInCity":
			dialog.text = StringFromKey("EncGirl_Girl_305");
			link.l1 = StringFromKey("EncGirl_Girl_306");
			link.l1.go = "DlgGirl_Escort_GoodEnd";
		break;

		case "DlgGirl_Escort_GoodEnd":
			pchar.GenQuest.EncGirl = "Quest_Escort_GoodEnd";
			EncGirl_Escort_CloseLogbook_Good();
			EncGirlBecameCitizen(npchar, "Close_SheIsInSafe");
			DialogExit();
		break;

		case "DlgGirl_InTavern_BrushHerOff":
			DeleteAttribute(pchar, "quest.EncGirl_Escort_ToRoom"); //Этот атрибут поставился, когда гг согласился арендовать комнату
			DeleteAttribute(pchar, "quest.EncGirl_Escort_ToRoom_Fail");
			ChangeCharacterReputation(pchar, -1);
			EncGirl_Escort_CloseLogbook_Good();
			EncGirl_CloseQuestExit("Close_close");
			EncGigl_SheFleeAway(false, true);
			EncGirlDialogExit();
		break;

		case "DlgGirl_InJungle_RejectEscort":
			EncGirlBecameCitizenNoGroup(npchar, "Close_InJungle_AbandonHer");
			Diag.TempNode = "DlgGirl_InJungle_RejectEscortAgain";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		case "DlgGirl_InJungle_RejectEscortAgain":
			Diag.TempNode = "DlgGirl_InJungle_RejectEscortAgain";
			Diag.CurrentNode = Diag.TempNode;
			dialog.text = StringFromKey("EncGirl_Girl_91", RandPhraseSimple(
						StringFromKey("EncGirl_Girl_89"),
						StringFromKey("EncGirl_Girl_90")));
			link.l1 = StringFromKey("EncGirl_Girl_94", RandPhraseSimple(
						StringFromKey("EncGirl_Girl_92"),
						StringFromKey("EncGirl_Girl_93")));
			link.l1.go = "exit";
			if (CheckAttribute(Diag, "NodeEscortTo"))
			{
				link.l2 = StringFromKey("EncGirl_Girl_69");
				link.l2.go = Diag.NodeEscortTo;
			}
			EncGirlShouldWeHealHer(link, npchar);
		break;

		//не используется -->  //Coffee
		case "ThanksForHelp_1":
			Diag.TempNode = "ThanksAgain";
			if (makeint(Pchar.reputation) >= 80)
			{
				dialog.text = StringFromKey("EncGirl_Girl_280");
				Link.l1 = StringFromKey("EncGirl_Girl_281");
				Link.l1.go = "exit";
			}
			else
			{
				if (drand(1) == 0)
				{
					dialog.text = StringFromKey("EncGirl_Girl_282", pchar);
					Link.l1 = StringFromKey("EncGirl_Girl_283");
					Link.l1.go = "exit";
				}
				else
				{
					addMoneyToCharacter(Pchar, makeint(PChar.rank) * 100);
					dialog.text = StringFromKey("EncGirl_Girl_284");
					Link.l1 = StringFromKey("EncGirl_Girl_285");
					Link.l1.go = "exit";
				}
			}
		break;

		case "ThanksAgain":
			Diag.TempNode = "ThanksAgain";
			dialog.text = StringFromKey("EncGirl_Girl_286", pchar);
			Link.l1 = StringFromKey("EncGirl_Girl_287");
			Link.l1.go = "exit";
		break;
// <-- не используется
	}
}

void EncGirlBecameCitizenNoGroup(ref rChr, string sCloseQuest)
{
	EncGirl_RemoveQuestMarks();
	EncGirl_Escort_OverQuestHeaders();
	LAi_RemoveCheckMinHP(rChr);

	rChr.lifeDay = "1";

	rChr.Dialog.TempNode = "DlgGirl_SheThanksForHelpRepeat";
	rChr.Dialog.CurrentNode = rChr.Dialog.TempNode;

	EncGirl_CloseQuestExit(sCloseQuest);

	LAi_SetDefaultDead(rChr);
	LAi_SetCitizenTypeNoGroup(rChr);
}

void EncGirlBecameCitizen(ref rChr, string sCloseQuest)
{
	EncGirlBecameCitizenNoGroup(rChr, sCloseQuest);

	string sTemp = GetNationNameByType(sti(rChr.nation)) + "_citizens";
	LAi_group_MoveCharacter(rChr, sTemp);
}

void EncGirlDialogExit()
{
	DialogExit();
	AddDialogExitQuest("pchar_back_to_player");
}

void EncGirlRapers_ActorReset()
{
	int i, iIdx;
	for (i = 1; i <= ENCGIRL_RAPERS_QTY; i++)
	{
		iIdx = GetCharacterIndex("EncGirl_GangMan_" + i);
		if (iIdx < 0) continue;
		LAi_type_actor_Reset(&Characters[iIdx]);
	}
}

bool EncGirlShouldWeHealHer(aref link, ref npchar) //она ранена, предложить ей схавать зелье
{
	string sTemp;

	if (CheckAttribute(pchar, "GenQuest.EncGirl.GiveHerPotion") && pchar.GenQuest.EncGirl.GiveHerPotion == "done")
	{
		DeleteAttribute(pchar, "GenQuest.EncGirl.GiveHerPotion");
		dialog.text = StringFromKey("EncGirl_Girl_297");
		if (CheckAttribute(NPChar, "Dialog.NodeEscortTo"))
		{
		    dialog.text = dialog.text +" " +StringFromKey("EncGirl_Girl_298");
		}
		return false;
	}

	if (stf(npchar.chr_ai.hp) < stf(npchar.chr_ai.hp_max))
	{
		if (GetCharacterItem(pchar, "potion1") > 0)
		{
			sTemp = LowerFirst(GetConvertStr("itmname_potion1", "ItemsDescribe.txt"));
			link.lGivePotion = StringFromKey("EncGirl_Girl_296", sTemp);
			pchar.GenQuest.EncGirl.GiveHerPotion = "potion1";
			link.lGivePotion.go = "DlgGirl_GiveHerPotion";
			NPChar.Dialog.TempNode = Dialog.CurrentNode;
			return true;
		}
		if (GetCharacterItem(pchar, "potion2") > 0)
		{
			sTemp = LowerFirst(GetConvertStr("itmname_potion2", "ItemsDescribe.txt"));
			link.lGivePotion = StringFromKey("EncGirl_Girl_296", sTemp);
			pchar.GenQuest.EncGirl.GiveHerPotion = "potion2";
			link.lGivePotion.go = "DlgGirl_GiveHerPotion";
			NPChar.Dialog.TempNode = Dialog.CurrentNode;
			return true;
		}
	}
	return false;
}

void EncGirlEscortBeginAddQuestRecord(string sWhere)
{
	string sTemp = "";
	ref rLoc = &locations[FindLocation(Pchar.location)];

	ReOpenQuestHeader("JungleGirl");

	if (CheckAttribute(rLoc, "islandId") && sWhere != "cave")
	{
		if (rLoc.islandId == "Mein")
		{
			AddQuestRecord("JungleGirl", "36_mein");
		}
		else
		{
			AddQuestRecord("JungleGirl", "36_island");
			AddQuestUserData("JungleGirl", "sIsland", GetConvertStr(rLoc.islandId, "LocLables.txt"));
		}
	}
	else
	{
		AddQuestRecord("JungleGirl", "36");
	}

	switch (pchar.GenQuest.EncGirl.CloseQuest)
	{
		case "Close_Rapers_AreTheyDead":
			sTemp = StringFromKey("EncGirl_Girl_291");
		break;
		case "Close_Rapers_BoughtOutWhore":
			sTemp = StringFromKey("EncGirl_Girl_289") +" " +FindMoneyString(sti(pchar.GenQuest.EncGirl.price)) +".";
		break;

	}
	AddQuestUserData("JungleGirl", "sRapersResult", " " +sTemp);
	AddQuestUserData("JungleGirl", "WhatDoesSheDoResult", " ");

	AddQuestRecord("JungleGirl", "43_" +sWhere);
	AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "а"));

	if (sWhere != "cave")
	{
		AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
	}
}
// Малькольм Фаун контрабандист
#include "DIALOGS\Rumours\Simple_rumors.c"
#include "DIALOGS\Quest\LostShipsCity\SeekLSCCitizen_CN.c"

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;
	int iTemp = 0;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	ProcessDialog_SeekLSCCitizenCN(NPChar, Link, NextDiag);

	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;

	switch (Dialog.CurrentNode)
	{
		case "First time":
		// --> кольцо
			if (!CheckAttribute(npchar, "quest.ring") && CheckAttribute(npchar, "quest.startRing"))
			{
				dialog.text = StringFromKey("MalcolmFawn_1", pchar);
				link.l1 = StringFromKey("MalcolmFawn_2");
				link.l1.go = "ring";
				npchar.quest.meeting = "1";
				break;
			}
			//<--
			if (npchar.quest.meeting == "0")
			{
				dialog.text = StringFromKey("MalcolmFawn_3");
				link.l1 = StringFromKey("MalcolmFawn_4");
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = StringFromKey("MalcolmFawn_5", pchar, GetFullName(pchar), TimeGreeting());
				link.l1 = StringFromKey("MalcolmFawn_6");
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("MalcolmFawn_7");
				link.l2.go = "int_quests";
				link.l3 = StringFromKey("MalcolmFawn_11", LinkRandPhrase(
							StringFromKey("MalcolmFawn_8"),
							StringFromKey("MalcolmFawn_9"),
							StringFromKey("MalcolmFawn_10")));
				link.l3.go = "rumours_LSC";
				// --> пьянь
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && pchar.questTemp.LSC.Drink == "begin")
				{
					link.l5 = StringFromKey("MalcolmFawn_12");
					link.l5.go = "drink";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && sti(pchar.money) >= 50000 && pchar.questTemp.LSC.Drink == "wait")
				{
					link.l5 = StringFromKey("MalcolmFawn_13", pchar);
					link.l5.go = "drink_4";
				}
				// <--
				//сбор отряда самоубийц
				if (CheckAttribute(pchar, "questTemp.LSC.suicideSquad") && !CheckAttribute(npchar, "quest.NotSuicideSquad") && !CheckAttribute(pchar, "questTemp.LSC.suicideSquad." + GetCharacterIndex(npchar.id)))
				{
					link.l1 = StringFromKey("MalcolmFawn_14");
					link.l1.go = "SuicideSquad";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.suicideSquad." + GetCharacterIndex(npchar.id)))
				{
					int deceasedCaspers = LSC_CheckDeceasedCaspers();
					//если оба мушкетера живы
					bool checkStateOne = deceasedCaspers == 2 && !LAi_IsDead(CharacterFromId("CasperMush_3")) && !LAi_IsDead(CharacterFromId("CasperMush_4"));
					//если CasperMush_3 жив
					bool checkStateTwo = deceasedCaspers == 1 && !LAi_IsDead(CharacterFromId("CasperMush_3"));
					//если CasperMush_4 жив
					bool checkStateThree = deceasedCaspers == 1 && !LAi_IsDead(CharacterFromId("CasperMush_4"));
					link.l3 = StringFromKey("MalcolmFawn_15");
					if (checkStateOne || checkStateTwo || checkStateThree) link.l3.go = "StormCaspers_1";
					else link.l3.go = "RefusalToGo";
				}
				//поиск грузчика на корвет
				if (pchar.questTemp.LSC == "toSeekStevedore")
				{
					link.l8 = StringFromKey("MalcolmFawn_16");
					link.l8.go = "SeekStevedore";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = StringFromKey("MalcolmFawn_17");
					if (CheckAttribute(npchar, "quest.seekGoods")) link.l8.go = "SeekGoods_4";
					else link.l8.go = "SeekGoods";
				}
				link.l10 = StringFromKey("MalcolmFawn_18", pchar);
				link.l10.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "meeting": // первая встреча
			dialog.text = StringFromKey("MalcolmFawn_19", pchar);
			link.l1 = StringFromKey("MalcolmFawn_20");
			link.l1.go = "meeting_1";
		break;

		case "meeting_1":
			dialog.text = StringFromKey("MalcolmFawn_21");
			link.l1 = StringFromKey("MalcolmFawn_22", GetFullName(pchar));
			link.l1.go = "meeting_2";
		break;

		case "meeting_2":
			dialog.text = StringFromKey("MalcolmFawn_23", pchar);
			link.l1 = StringFromKey("MalcolmFawn_24");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		// Кольцо
		case "ring":
			dialog.text = StringFromKey("MalcolmFawn_25");
			link.l1 = StringFromKey("MalcolmFawn_26");
			link.l1.go = "ring_1";
			npchar.quest.ring = "true";
		break;

		case "ring_1":
			dialog.text = StringFromKey("MalcolmFawn_27");
			link.l1 = StringFromKey("MalcolmFawn_28", pchar);
			link.l1.go = "ring_2";
		break;

		case "ring_2":
			dialog.text = StringFromKey("MalcolmFawn_29");
			link.l1 = StringFromKey("MalcolmFawn_30");
			link.l1.go = "ring_3";
		break;

		case "ring_3":
			dialog.text = StringFromKey("MalcolmFawn_31");
			link.l1 = StringFromKey("MalcolmFawn_32");
			link.l1.go = "ring_4";
		break;

		case "ring_4":
			dialog.text = StringFromKey("MalcolmFawn_33", pchar);
			link.l1 = StringFromKey("MalcolmFawn_34");
			link.l1.go = "ring_4_5";
		break;

		case "ring_4_5":
			dialog.text = StringFromKey("MalcolmFawn_35");
			link.l1 = StringFromKey("MalcolmFawn_36", pchar);
			link.l1.go = "ring_5";
			link.l2 = StringFromKey("MalcolmFawn_37");
			link.l2.go = "ring_exit";
		break;

		case "ring_exit":
			dialog.text = StringFromKey("MalcolmFawn_38");
			link.l1 = StringFromKey("MalcolmFawn_39");
			link.l1.go = "exit";
			AddQuestRecord("LSC_Ring", "10");
			CloseQuestHeader("LSC_Ring");
			npchar.location = "FleuronTavern";
			npchar.location.group = "sit";
			npchar.location.locator = "sit19";
			sld = characterFromID("LSCBarmen");
			sld.quest.doneRing = true;
			RemoveLandQuestMark_Main(npchar, "LSC_Ring");
		break;

		case "ring_5":
			dialog.text = StringFromKey("MalcolmFawn_40", pchar);
			link.l1 = StringFromKey("MalcolmFawn_41");
			link.l1.go = "ring_6";
		break;

		case "ring_6":
			dialog.text = StringFromKey("MalcolmFawn_42");
			link.l1 = StringFromKey("MalcolmFawn_43");
			link.l1.go = "ring_7";
		break;

		case "ring_7":
			dialog.text = StringFromKey("MalcolmFawn_44");
			link.l1 = StringFromKey("MalcolmFawn_45");
			link.l1.go = "ring_8";
		break;

		case "ring_repeat":
			dialog.text = StringFromKey("MalcolmFawn_46");
			link.l1 = StringFromKey("MalcolmFawn_47");
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_repeat";
		break;

		case "ring_8":
			DialogExit();
			NextDiag.CurrentNode = "ring_repeat";
			pchar.quest.LSC_Ring_Start.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.hour = 7.0;
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Start.function = "LSC_RingStart"; // готовы
			pchar.quest.LSC_Ring_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.hour = 10.0;
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Over.function = "LSC_RingOver"; // опоздание
			AddQuestRecord("LSC_Ring", "1");
			RemoveLandQuestMark_Main(npchar, "LSC_Ring");
		break;

		case "ring_9":
			dialog.text = StringFromKey("MalcolmFawn_48", pchar);
			link.l1 = StringFromKey("MalcolmFawn_49");
			link.l1.go = "ring_10";
		break;

		case "ring_10":
			DialogExit();
			LAi_Fade("LSC_DeployShellBoat", "LSC_RingTalkAfterDeployShellBoat");
		break;

		case "ring_11":
			dialog.text = StringFromKey("MalcolmFawn_50");
			link.l1 = StringFromKey("MalcolmFawn_51");
			link.l1.go = "ring_12";
		break;

		case "ring_12":
			dialog.text = StringFromKey("MalcolmFawn_52");
			link.l1 = "...";
			link.l1.go = "ring_look";
		break;

		case "ring_look":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_ring");
			DoQuestCheckDelay("LSC_RingTalkLook", 6.0);
		break;

		case "ring_13":
			dialog.text = "";
			link.l1 = StringFromKey("MalcolmFawn_53", pchar);
			link.l1.go = "ring_14";
		break;

		case "ring_14":
			dialog.text = StringFromKey("MalcolmFawn_54");
			link.l1 = StringFromKey("MalcolmFawn_55");
			link.l1.go = "ring_swim_1";
		break;

		case "ring_swim_1":
			dialog.text = StringFromKey("MalcolmFawn_56");
			link.l1 = "...";
			link.l1.go = "ring_swim_2";
		break;

		case "ring_swim_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetImmortal(npchar, true);
			pchar.quest.LSC_Ring_enter.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_enter.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator = "reload_ring";
			pchar.quest.LSC_Ring_enter.function = "LSC_RingEnter";
			AddQuestRecord("LSC_Ring", "3");
			RemoveLandQuestMark_Main(npchar, "LSC_Ring");
		break;

		case "ring_15":
			dialog.text = StringFromKey("MalcolmFawn_57", pchar);
			link.l1 = StringFromKey("MalcolmFawn_58", pchar);
			link.l1.go = "ring_16";
		break;

		case "ring_16":
			dialog.text = StringFromKey("MalcolmFawn_59", pchar);
			link.l1 = StringFromKey("MalcolmFawn_60");
			link.l1.go = "ring_17";
		break;

		case "ring_17":
			dialog.text = StringFromKey("MalcolmFawn_61");
			link.l1 = StringFromKey("MalcolmFawn_62");
			link.l1.go = "ring_18";
		break;

		case "ring_18":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 60.0); // 1 минуту на пошариться
			npchar.quest.diagnode = "ring_19";
			AddQuestRecord("LSC_Ring", "4");
			AddQuestUserData("LSC_Ring", "sSex", GetSexPhrase("ся", "ась"));
			sld = characterFromID("LSCBarmen");
			sld.quest.doneRing = true;
			npchar.quest.doneRing = true;
		break;

		case "ring_wait":
			dialog.text = StringFromKey("MalcolmFawn_63", pchar);
			link.l1 = StringFromKey("MalcolmFawn_64");
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_wait";
		break;

		case "ring_19":
			dialog.text = StringFromKey("MalcolmFawn_65");
			link.l1 = StringFromKey("MalcolmFawn_66");
			link.l1.go = "ring_20";
		break;

		case "ring_20":
			dialog.text = StringFromKey("MalcolmFawn_67");
			link.l1 = StringFromKey("MalcolmFawn_68");
			link.l1.go = "ring_21";
		break;

		case "ring_21":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Ring_deck.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_Ring_deck.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_Ring_deck.win_condition = "LSC_RingEnterDeck";
		break;

		case "ring_22":
			dialog.text = StringFromKey("MalcolmFawn_69");
			link.l1 = StringFromKey("MalcolmFawn_70");
			link.l1.go = "ring_23";
		break;

		case "ring_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "reload", "reload1", "", -1);
		break;

		case "ring_24":
			dialog.text = StringFromKey("MalcolmFawn_71");
			link.l1 = StringFromKey("MalcolmFawn_72");
			link.l1.go = "ring_25";
		break;

		case "ring_25":
			dialog.text = StringFromKey("MalcolmFawn_73", pchar);
			link.l1 = StringFromKey("MalcolmFawn_74");
			link.l1.go = "ring_26";
		break;

		case "ring_26":
			dialog.text = StringFromKey("MalcolmFawn_75");
			link.l1 = StringFromKey("MalcolmFawn_76");
			link.l1.go = "ring_27";
		break;

		case "ring_27":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 80.0); // 1.3 минуты на пошариться
			npchar.quest.diagnode = "ring_28";
			AddQuestRecord("LSC_Ring", "5");
		break;

		case "ring_28":
			dialog.text = StringFromKey("MalcolmFawn_77");
			link.l1 = StringFromKey("MalcolmFawn_78", pchar);
			link.l1.go = "ring_29";
		break;

		case "ring_29":
			dialog.text = StringFromKey("MalcolmFawn_79", pchar.name);
			link.l1 = StringFromKey("MalcolmFawn_80");
			link.l1.go = "ring_30";
		break;

		case "ring_30":
			DialogExit();
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("ExternalRingDeck", "reload2", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "ExternalRingCabin1", "reload", "reload1", "OpenTheDoors", -1);
			pchar.quest.LSC_Ring_cabin.win_condition.l1 = "location";
			pchar.quest.LSC_Ring_cabin.win_condition.l1.location = "ExternalRingCabin1";
			pchar.quest.LSC_Ring_cabin.win_condition = "LSC_RingEnterCabin";
			sld = ItemsFromID("RingCapBook"); // кладем журнал 'Санта-Люсии'
			sld.shown = true;
			sld.startLocation = "ExternalRingCabin1";
			sld.startLocator = "item1";
		break;

		case "ring_31":
			dialog.text = StringFromKey("MalcolmFawn_81");
			link.l1 = StringFromKey("MalcolmFawn_82");
			link.l1.go = "ring_32";
		break;

		case "ring_32":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "LSC_RingSetToBarman", -1);
			DoQuestCheckDelay("LSC_RingDialog", 30.0); // 30 сек на пошариться
			npchar.quest.diagnode = "ring_33";
		break;

		case "ring_33":
			dialog.text = StringFromKey("MalcolmFawn_83", pchar);
			link.l1 = StringFromKey("MalcolmFawn_84");
			link.l1.go = "ring_34";
		break;

		case "ring_34":
			dialog.text = StringFromKey("MalcolmFawn_85");
			link.l1 = StringFromKey("MalcolmFawn_86");
			link.l1.go = "ring_35";
		break;

		case "ring_35":
			AddMoneyToCharacter(pchar, 20000);
			AddItemLog(pchar, "incas_collection,jewelry4,chest", "1,25", StringFromKey("InfoMessages_180"), "Important_item");
			Log_Info(StringFromKey("InfoMessages_150"));
			Log_Info(StringFromKey("InfoMessages_151"));
			dialog.text = StringFromKey("MalcolmFawn_87");
			link.l1 = StringFromKey("MalcolmFawn_88");
			link.l1.go = "ring_36";
		break;

		case "ring_36":
			dialog.text = StringFromKey("MalcolmFawn_89", pchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = StringFromKey("MalcolmFawn_90", pchar);
				link.l1.go = "ring_41";
			}
			else
			{
				if (CheckCharacterItem(pchar, "RingCapBook")) // взял журнал
				{
					link.l1 = StringFromKey("MalcolmFawn_91", pchar);
					link.l1.go = "ring_38";
				}
				else
				{
					link.l1 = StringFromKey("MalcolmFawn_92");
					link.l1.go = "ring_37";
				}
			}
		break;

		case "ring_37":
			dialog.text = StringFromKey("MalcolmFawn_93");
			link.l1 = StringFromKey("MalcolmFawn_94");
			link.l1.go = "ring_cabin_exit";
		break;

		case "ring_38":
			dialog.text = StringFromKey("MalcolmFawn_95", pchar);
			link.l1 = StringFromKey("MalcolmFawn_96");
			link.l1.go = "ring_39";
		break;

		case "ring_39":
			dialog.text = StringFromKey("MalcolmFawn_97");
			link.l1 = StringFromKey("MalcolmFawn_98");
			link.l1.go = "ring_40";
		break;

		case "ring_40":
			DialogExit();
			NextDiag.CurrentNode = "book_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
		break;

		case "book_wait":
			dialog.text = StringFromKey("MalcolmFawn_99", pchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = StringFromKey("MalcolmFawn_100");
				link.l1.go = "ring_41";
			}
			else
			{
				link.l1 = StringFromKey("MalcolmFawn_101");
				link.l1.go = "exit";
				NextDiag.TempNode = "book_wait";
			}
		break;

		case "ring_41":
			dialog.text = StringFromKey("MalcolmFawn_102", pchar.name);
			link.l1 = StringFromKey("MalcolmFawn_103");
			link.l1.go = "ring_42";
		break;

		case "ring_42":
			dialog.text = "...";
			link.l1 = StringFromKey("MalcolmFawn_104");
			link.l1.go = "ring_43";
		break;

		case "ring_43":
			dialog.text = "...";
			link.l1 = StringFromKey("MalcolmFawn_105");
			link.l1.go = "ring_44";
		break;

		case "ring_44":
			dialog.text = "...";
			link.l1 = StringFromKey("MalcolmFawn_106");
			link.l1.go = "ring_45";
		break;

		case "ring_45":
			dialog.text = StringFromKey("MalcolmFawn_107");
			link.l1 = StringFromKey("MalcolmFawn_108");
			link.l1.go = "ring_seek_gold";
		break;

		case "ring_cabin_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход // patch-2
			DoQuestReloadToLocation("ExternalRingDeck", "reload", "reload2", "LSC_RingFinalStage");
			sld = ItemsFromID("RingCapBook");
			sld.shown = false; // убираем журнал
			AddQuestRecord("LSC_Ring", "6");
		break;

		case "ring_seek_gold":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			// ставим прерывание на локатор
			pchar.quest.LSC_Ring_gold.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_gold.win_condition.l1.location = "ExternalRingInside";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator = "gold";
			pchar.quest.LSC_Ring_gold.win_condition = "LSC_RingFindGold";
			// подменяем состав бокса
			pchar.GenQuestBox.ExternalRingInside = true;
			pchar.GenQuestBox.ExternalRingInside.box1.items.jewelry5 = 2522;
			AddQuestRecord("LSC_Ring", "7");
		break;

		case "ring_46":
			dialog.text = StringFromKey("MalcolmFawn_109");
			link.l1 = StringFromKey("MalcolmFawn_110");
			link.l1.go = "ring_47";
		break;

		case "ring_47":
			dialog.text = StringFromKey("MalcolmFawn_111");
			link.l1 = StringFromKey("MalcolmFawn_112");
			link.l1.go = "ring_48";
		break;

		case "ring_48":
			dialog.text = StringFromKey("MalcolmFawn_113");
			link.l1 = StringFromKey("MalcolmFawn_114");
			link.l1.go = "ring_49";
		break;

		case "ring_49":
			DialogExit();
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_209") + NewStr() + StringFromKey("InfoMessages_210"), "", 0, 5); //табличка
			WaitDate("", 0, 0, 0, 2, 10);
			LaunchFrameForm();
			RecalculateJumpTable();
			npchar.quest.diagnode = "ring_50";
			DoQuestCheckDelay("LSC_RingDialog", 5.0);
		break;

		case "ring_50":
			dialog.text = StringFromKey("MalcolmFawn_115", pchar);
			link.l1 = StringFromKey("MalcolmFawn_116");
			link.l1.go = "ring_51";
		break;

		case "ring_51":
			dialog.text = StringFromKey("MalcolmFawn_117");
			link.l1 = StringFromKey("MalcolmFawn_118");
			link.l1.go = "ring_54";
			link.l2 = StringFromKey("MalcolmFawn_119");
			link.l2.go = "ring_52";
		break;

		case "ring_52":
			dialog.text = StringFromKey("MalcolmFawn_120", pchar, pchar.name);
			link.l1 = StringFromKey("MalcolmFawn_121");
			link.l1.go = "ring_53";
		break;

		case "ring_53":
			DialogExit();
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход
			DoQuestCheckDelay("LSC_RingFinalStage", 0.5);
			DeleteAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook");
			npchar.quest.fullRing = true;
			AddQuestRecord("LSC_Ring", "8");
		break;

		case "ring_54":
			dialog.text = StringFromKey("MalcolmFawn_122");
			link.l1 = StringFromKey("MalcolmFawn_123");
			link.l1.go = "ring_55";
		break;

		case "ring_55":
			dialog.text = StringFromKey("MalcolmFawn_124");
			link.l1 = StringFromKey("MalcolmFawn_125");
			link.l1.go = "ring_56";
		break;

		case "ring_56":
			DialogExit();
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_30"), "", 0, 4); //табличка
			WaitDate("", 0, 0, 0, 10, 10);
			LaunchFrameForm();
			RecalculateJumpTable();

			npchar.quest.diagnode = "ring_57";
			DoQuestCheckDelay("LSC_RingDialog", 4.5);
			DoQuestCheckDelay("LSC_RingGoToBack", 4.0);
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход

			DeleteAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook");
			npchar.quest.fullRing = true;
			AddQuestRecord("LSC_Ring", "11");
			//перемещаем золото
			pchar.GenQuestBox.ExternalRingInside.box1.items.jewelry5 = 1;
			iTemp = FindLocation("LostShipsCity_town");
			if (CheckAttribute(&locations[iTemp], "private11.items.jewelry5"))
				locations[iTemp].private11.items.jewelry5 = sti(locations[iTemp].private11.items.jewelry5) + 2522;
			else
				locations[iTemp].private11.items.jewelry5 = 2522;
		break;

		case "ring_57":
			dialog.text = StringFromKey("MalcolmFawn_126", pchar);
			link.l1 = StringFromKey("MalcolmFawn_127");
			link.l1.go = "ring_58";
		break;

		case "ring_58":
			dialog.text = StringFromKey("MalcolmFawn_128");
			link.l1 = StringFromKey("MalcolmFawn_129");
			link.l1.go = "exit";
			AddDialogExitQuest("LSC_RingFinalStage");
		break;

		// --> пей до дна
		case "drink":
			dialog.text = StringFromKey("MalcolmFawn_130", pchar);
			link.l1 = StringFromKey("MalcolmFawn_131");
			link.l1.go = "drink_1";
		break;

		case "drink_1":
			dialog.text = StringFromKey("MalcolmFawn_132", pchar);
			link.l1 = StringFromKey("MalcolmFawn_133", pchar);
			link.l1.go = "drink_2";
		break;

		case "drink_2":
			dialog.text = StringFromKey("MalcolmFawn_134", pchar);
			link.l1 = StringFromKey("MalcolmFawn_135");
			link.l1.go = "drink_3";
		break;

		case "drink_3":
			dialog.text = StringFromKey("MalcolmFawn_136", pchar);
			if (sti(pchar.money) >= 50000)
			{
				link.l1 = StringFromKey("MalcolmFawn_137", pchar);
				link.l1.go = "drink_4";
			}
			link.l2 = StringFromKey("MalcolmFawn_138");
			link.l2.go = "drink_wait";
		break;

		case "drink_wait":
			dialog.text = StringFromKey("MalcolmFawn_139", pchar);
			link.l1 = StringFromKey("MalcolmFawn_140");
			link.l1.go = "exit";
			pchar.questTemp.LSC.Drink = "wait";
		break;

		case "drink_4":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = StringFromKey("MalcolmFawn_141", pchar);
			link.l1 = StringFromKey("MalcolmFawn_142");
			link.l1.go = "drink_5";
		break;

		case "drink_5":
			dialog.text = StringFromKey("MalcolmFawn_143");
			link.l1 = StringFromKey("MalcolmFawn_144");
			link.l1.go = "drink_6";
		break;

		case "drink_6":
			DialogExit();
			pchar.questTemp.LSC.Drink = "start";
			pchar.quest.LSC_DrinkOver.over = "yes"; //снять таймер
			pchar.quest.LSC_Drink.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink.win_condition.l1.date.hour = 21.0;
			pchar.quest.LSC_Drink.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink.function = "LSC_WaitDrinkPrepare";
			pchar.quest.LSC_Drink_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.hour = 23.0;
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink_Over.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "2");
			AddQuestUserData("LSC_Drink", "sSex", GetSexPhrase("", "а"));
			RemoveLandQuestMark_Main(npchar, "LSC_Drink");
		break;

		case "drink_8":
			dialog.text = StringFromKey("MalcolmFawn_145", pchar);
			link.l1 = StringFromKey("MalcolmFawn_146");
			link.l1.go = "drink_9";
		break;

		case "drink_9":
			/* перки не влияют больше на шанс
			//железная воля даёт волю к победе в спортивном мероприятии

			if (CheckCharacterPerk(pchar, "IronWill")) pchar.questTemp.LSC.Drink.Chance = sti(pchar.questTemp.LSC.Drink.Chance) + 30;
			//отменное здоровье поможет больше выпить
			if (CheckCharacterPerk(pchar, "Medic")) pchar.questTemp.LSC.Drink.Chance = sti(pchar.questTemp.LSC.Drink.Chance) + 30;*/

			// Считаем сумму Силы и Выносливости
			iTemp = GetCharacterSPECIAL(pchar, "Strength") + GetCharacterSPECIAL(pchar, "Endurance");

			// Вычисляем процент успеха от 5% (минималка) до 100%
			int iWinChance = 5;
			if (iTemp >= 20)
			{
				iWinChance = 100;
			}
			else if (iTemp > 6)
			{
				iWinChance = 5 + ((iTemp - 6) * 95) / 14;
			}

			// Записываем наш итоговый шанс в процентах
			pchar.questTemp.LSC.Drink.Chance = iWinChance;

			DialogExit();
			pchar.questTemp.LSC.Drink = "go";
			pchar.quest.LSC_Drink_Over.over = "yes"; //снять таймер
			RemoveLandQuestMark_Main(npchar, "LSC_Drink");
			ChangeCharacterAddressGroup(pchar, "FleuronTavern", "quest", "sit1");
			LAi_SetActorType(pchar);
			LAi_ActorSetSitMode(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			DoQuestFunctionDelay("LSC_DrinkGo", 0.5);
		break;

		case "drunk":
			dialog.text = StringFromKey("MalcolmFawn_147");
			link.l1 = StringFromKey("MalcolmFawn_148");
			link.l1.go = "exit";
			NextDiag.TempNode = "drunk";
		break;
		// <-- пей до дна
		//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = StringFromKey("MalcolmFawn_149");
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = StringFromKey("MalcolmFawn_150");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = StringFromKey("MalcolmFawn_151");
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = StringFromKey("MalcolmFawn_152");
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l4 = StringFromKey("MalcolmFawn_153");
				link.l4.go = "ansewer_4";
			}
			link.l10 = StringFromKey("MalcolmFawn_154");
			link.l10.go = "exit";
		break;

		case "ansewer_1":
			dialog.text = StringFromKey("MalcolmFawn_155");
			link.l1 = StringFromKey("MalcolmFawn_156");
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;

		case "ansewer_2":
			dialog.text = StringFromKey("MalcolmFawn_157");
			link.l1 = StringFromKey("MalcolmFawn_158");
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;

		case "ansewer_3":
			dialog.text = StringFromKey("MalcolmFawn_159");
			link.l1 = StringFromKey("MalcolmFawn_160");
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;

		case "ansewer_4":
			dialog.text = StringFromKey("MalcolmFawn_161");
			link.l1 = StringFromKey("MalcolmFawn_162");
			link.l1.go = "ansewer_4_1";
			npchar.quest.answer_4 = "true";
		break;
		case "ansewer_4_1":
			dialog.text = StringFromKey("MalcolmFawn_163");
			link.l1 = StringFromKey("MalcolmFawn_164");
			link.l1.go = "ansewer_4_2";
		break;
		case "ansewer_4_2":
			dialog.text = StringFromKey("MalcolmFawn_165");
			link.l1 = StringFromKey("MalcolmFawn_166");
			link.l1.go = "exit";
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;
		// <-- блок вопросов и ответов

		//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = StringFromKey("MalcolmFawn_170", LinkRandPhrase(
						StringFromKey("MalcolmFawn_167"),
						StringFromKey("MalcolmFawn_168"),
						StringFromKey("MalcolmFawn_169", pchar)));
			link.l1 = StringFromKey("MalcolmFawn_171");
			link.l1.go = "fight";
		break;

		case "Woman_FackYou":
			dialog.text = StringFromKey("MalcolmFawn_172", pchar);
			link.l1 = StringFromKey("MalcolmFawn_173");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//замечание по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("MalcolmFawn_177", LinkRandPhrase(
						StringFromKey("MalcolmFawn_174", pchar),
						StringFromKey("MalcolmFawn_175"),
						StringFromKey("MalcolmFawn_176")));
			link.l1 = StringFromKey("MalcolmFawn_181", LinkRandPhrase(
						StringFromKey("MalcolmFawn_178"),
						StringFromKey("MalcolmFawn_179"),
						StringFromKey("MalcolmFawn_180")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("MalcolmFawn_182", npchar);
				link.l1 = StringFromKey("MalcolmFawn_186", LinkRandPhrase(
							StringFromKey("MalcolmFawn_183"),
							StringFromKey("MalcolmFawn_184"),
							StringFromKey("MalcolmFawn_185")));
			}
			else
			{
				dialog.text = StringFromKey("MalcolmFawn_187", npchar);
				link.l1 = StringFromKey("MalcolmFawn_190", RandPhraseSimple(
							StringFromKey("MalcolmFawn_188", pchar),
							StringFromKey("MalcolmFawn_189")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		// <-- специальные реакции

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("MalcolmFawn_191");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("MalcolmFawn_192");
				Link.l1 = StringFromKey("MalcolmFawn_193");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("MalcolmFawn_194", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("MalcolmFawn_195");
					link.l1 = StringFromKey("MalcolmFawn_196", pchar);
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("MalcolmFawn_197", GetFullName(sld));
					Link.l1 = StringFromKey("MalcolmFawn_198");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("MalcolmFawn_199");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("MalcolmFawn_200", GetFullName(sld));
					Link.l1 = StringFromKey("MalcolmFawn_201");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("MalcolmFawn_202");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("MalcolmFawn_203");
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("MalcolmFawn_204");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;

		case "SeekCitizen_agree":
			sld = &characters[sti(npchar.quest.seekIdx)];
			npchar.quest.seekIdx.where = WhereLSCCitizen(sld);
			if (npchar.quest.seekIdx.where == "none")
			{
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("MalcolmFawn_208", LinkRandPhrase(
								StringFromKey("MalcolmFawn_205"),
								StringFromKey("MalcolmFawn_206"),
								StringFromKey("MalcolmFawn_207")));
					link.l1 = StringFromKey("MalcolmFawn_211", RandPhraseSimple(
								StringFromKey("MalcolmFawn_209"),
								StringFromKey("MalcolmFawn_210")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("MalcolmFawn_215", LinkRandPhrase(
								StringFromKey("MalcolmFawn_212"),
								StringFromKey("MalcolmFawn_213"),
								StringFromKey("MalcolmFawn_214")));
					link.l1 = StringFromKey("MalcolmFawn_218", RandPhraseSimple(
								StringFromKey("MalcolmFawn_216"),
								StringFromKey("MalcolmFawn_217")));
					link.l1.go = "exit";
				}
			}
			else
			{
				if (sld.sex == "man")
				{
					if (sld.location == "LostShipsCity_town")
					{
						string Str1 = npchar.location.locator;
						string Str2 = sld.location.locator;
						if (npchar.location == sld.location && strcut(Str1, 0, 5) == strcut(Str2, 0, 5))
						{
							dialog.text = StringFromKey("MalcolmFawn_222", LinkRandPhrase(
										StringFromKey("MalcolmFawn_219"),
										StringFromKey("MalcolmFawn_220"),
										StringFromKey("MalcolmFawn_221", pchar)));
						}
						else
						{
							dialog.text = StringFromKey("MalcolmFawn_226", LinkRandPhrase(
										StringFromKey("MalcolmFawn_223", npchar.quest.seekIdx.where),
										StringFromKey("MalcolmFawn_224", npchar.quest.seekIdx.where),
										StringFromKey("MalcolmFawn_225", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("MalcolmFawn_230", LinkRandPhrase(
										StringFromKey("MalcolmFawn_227", npchar.quest.seekIdx.where),
										StringFromKey("MalcolmFawn_228"),
										StringFromKey("MalcolmFawn_229")));
						}
						else
						{
							dialog.text = StringFromKey("MalcolmFawn_234", LinkRandPhrase(
										StringFromKey("MalcolmFawn_231", npchar.quest.seekIdx.where),
										StringFromKey("MalcolmFawn_232", npchar.quest.seekIdx.where),
										StringFromKey("MalcolmFawn_233", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("MalcolmFawn_237", RandPhraseSimple(
								StringFromKey("MalcolmFawn_235"),
								StringFromKey("MalcolmFawn_236")));
					link.l1.go = "exit";
				}
				else
				{
					if (sld.location == "LostShipsCity_town")
					{
						string Str3 = npchar.location.locator;
						string Str4 = sld.location.locator;
						if (npchar.location == sld.location && strcut(Str3, 0, 5) == strcut(Str4, 0, 5))
						{
							dialog.text = StringFromKey("MalcolmFawn_241", LinkRandPhrase(
										StringFromKey("MalcolmFawn_238"),
										StringFromKey("MalcolmFawn_239"),
										StringFromKey("MalcolmFawn_240", pchar)));
						}
						else
						{
							dialog.text = StringFromKey("MalcolmFawn_245", LinkRandPhrase(
										StringFromKey("MalcolmFawn_242", npchar.quest.seekIdx.where),
										StringFromKey("MalcolmFawn_243", npchar.quest.seekIdx.where),
										StringFromKey("MalcolmFawn_244", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("MalcolmFawn_249", LinkRandPhrase(
										StringFromKey("MalcolmFawn_246", npchar.quest.seekIdx.where),
										StringFromKey("MalcolmFawn_247"),
										StringFromKey("MalcolmFawn_248")));
						}
						else
						{
							dialog.text = StringFromKey("MalcolmFawn_253", LinkRandPhrase(
										StringFromKey("MalcolmFawn_250", npchar.quest.seekIdx.where),
										StringFromKey("MalcolmFawn_251", npchar.quest.seekIdx.where),
										StringFromKey("MalcolmFawn_252", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("MalcolmFawn_256", RandPhraseSimple(
								StringFromKey("MalcolmFawn_254"),
								StringFromKey("MalcolmFawn_255")));
					link.l1.go = "exit";
				}
			}
		break;

		//сбор отряда самоубийц
		case "SuicideSquad":
			if (!CheckAttribute(pchar, "questTemp.LSC.suicideSquad_TalkCounter"))
				pchar.questTemp.LSC.suicideSquad_TalkCounter = 0;
			pchar.questTemp.LSC.suicideSquad_TalkCounter = sti(pchar.questTemp.LSC.suicideSquad_TalkCounter) + 1;
			RemoveLandQuestMark_Main(npchar, "ISS_DefeatCasperClan");

			if (CheckAttribute(npchar, "quest.fullRing"))
			{
				dialog.text = StringFromKey("MalcolmFawn_257", pchar);
				link.l1 = StringFromKey("MalcolmFawn_258");
				link.l1.go = "exit";
				AddQuestRecord("ISS_DefeatCasperClan", "18");
				AddQuestUserData("ISS_DefeatCasperClan", "sName", GetFullName(npchar));
				string sIndex = its(GetCharacterIndex(npchar.id));
				pchar.questTemp.LSC.suicideSquad.(sIndex) = true;
				//с этого момента Малькольм впишется на Церес Смити
				npchar.location.baseShip = "03"; //базовый корабль в ГПК
				npchar.location.baseLocator = "goto7";
				npchar.location.baseLocation = "CeresSmithy"; //базовая внутреняя локация
				npchar.location.baseShip.going = false; //перемещаться между кораблями в городе
				npchar.location = "CeresSmithy";
				npchar.location.group = "goto";
				npchar.location.locator = "goto7";

				LSC_SuicideSquadEnough();
			}
			else
			{
				dialog.text = StringFromKey("MalcolmFawn_259", pchar);
				link.l1 = StringFromKey("MalcolmFawn_260");
				link.l1.go = "exit";
				npchar.quest.NotSuicideSquad = true;
				AddQuestRecord("ISS_DefeatCasperClan", "22");
			}
		break;
		case "RefusalToGo":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("MalcolmFawn_261"),
						StringFromKey("MalcolmFawn_262"),
						StringFromKey("MalcolmFawn_263"),
						StringFromKey("MalcolmFawn_264"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("MalcolmFawn_265"),
						StringFromKey("MalcolmFawn_266", pchar),
						StringFromKey("MalcolmFawn_267"),
						StringFromKey("MalcolmFawn_268", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;

		//поиск грузчика на корвет
		case "SeekStevedore":
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "win")
			{
				dialog.text = StringFromKey("MalcolmFawn_269");
				link.l1 = StringFromKey("MalcolmFawn_270");
				link.l1.go = "SeekStevedore_1";
				link.l2 = StringFromKey("MalcolmFawn_271", pchar);
				link.l2.go = "SeekStevedore_7";
			}
			else
			{
				dialog.text = StringFromKey("MalcolmFawn_272");
				link.l1 = StringFromKey("MalcolmFawn_273");
				link.l1.go = "SeekStevedore_2";
			}
			npchar.quest.crewDone = 1;
		break;
		case "SeekStevedore_1":
			dialog.text = StringFromKey("MalcolmFawn_274");
			link.l1 = StringFromKey("MalcolmFawn_275", pchar);
			link.l1.go = "SeekStevedore_2";
			npchar.quest.lie = 1; //ГГ соврал, запоминаем
		break;
		case "SeekStevedore_2":
			dialog.text = StringFromKey("MalcolmFawn_276");
			link.l1 = StringFromKey("MalcolmFawn_277");
			link.l1.go = "SeekStevedore_3";
		break;
		case "SeekStevedore_3":
			dialog.text = StringFromKey("MalcolmFawn_278");
			link.l1 = StringFromKey("MalcolmFawn_279");
			link.l1.go = "SeekStevedore_4";
			pchar.questTemp.LSC = "foundStevedore";
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
			RemoveLandQuestMark_Main(CharacterFromID("LSCBarmen"), "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("Mechanic"), "ISS_MainLine");
		break;
		case "SeekStevedore_4":
			dialog.text = StringFromKey("MalcolmFawn_280");
			link.l1 = StringFromKey("MalcolmFawn_281");
			link.l1.go = "SeekStevedore_5";
			link.l2 = StringFromKey("MalcolmFawn_282");
			link.l2.go = "SeekStevedore_6";
			AddQuestRecord("ISS_MainLine", "68");
		break;
		case "SeekStevedore_5":
			dialog.text = StringFromKey("MalcolmFawn_283", pchar);
			link.l1 = StringFromKey("MalcolmFawn_284");
			link.l1.go = "exit";
			SetQuestHeader("MalcolmsTobacco");
			AddQuestRecord("MalcolmsTobacco", "1");
			pchar.quest.Malcolm_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.Malcolm_Death.win_condition.l1.character = "MalcolmFawn";
			pchar.quest.Malcolm_Death.win_condition = "Malcolm_Fawn_is_death";
			pchar.quest.MalcolmsTobacco.win_condition.l1 = "location";
			pchar.quest.MalcolmsTobacco.win_condition.l1.location = "PuertoPrincipe_town";
			pchar.quest.MalcolmsTobacco.function = "MalcolmIntoPuertoPrincipe";
			AddCharacterGoods(pchar, GOOD_TOBACCO, 700);
		break;
		case "SeekStevedore_6":
			dialog.text = StringFromKey("MalcolmFawn_285", pchar);
			link.l1 = StringFromKey("MalcolmFawn_286");
			link.l1.go = "exit";
		break;
		case "SeekStevedore_7":
			dialog.text = StringFromKey("MalcolmFawn_287");
			link.l1 = StringFromKey("MalcolmFawn_288", pchar);
			link.l1.go = "SeekStevedore_2";
		break;

		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = StringFromKey("MalcolmFawn_289");
			link.l1 = StringFromKey("MalcolmFawn_290");
			link.l1.go = "SeekGoods_1";
			npchar.quest.seekGoods = 1; //в следующий раз будем торговать лютнями и прочим хламом
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("MalcolmFawn_291");
			link.l1 = StringFromKey("MalcolmFawn_292");
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			iTemp = and(CheckAttribute(npchar, "quest.doneRing") || CheckAttribute(npchar, "quest.fullRing"), !CheckAttribute(npchar, "quest.drink") || npchar.quest.drink != "win");
			sTemp = StringFromKey("MalcolmFawn_293");
			link.l1.go = "exit";
			if (iTemp == true) // если не грабили и прошли Люсию, то предлагает пиастры
			{
				sTemp = StringFromKey("MalcolmFawn_294", pchar, sTemp);
				link.l1.go = "Exit_SeekGoods_TakeMoney";
			}
			dialog.text = sTemp;
			link.l1 = StringFromKey("MalcolmFawn_295", pchar);

			if (iTemp == true) // если не грабили и прошли Люсию, то предлагает ещё и товары бесплатно
			{
				link.l2 = StringFromKey("MalcolmFawn_296");
				link.l2.go = "SeekGoods_3";
			}
			AddLandQuestMark_Main_WithCondition(npchar, "ISS_MainLine", "LSC_ToSeekGoods_MalcolmFawn_QuestMarkCondition");
		break;
		case "Exit_SeekGoods_TakeMoney":
			iTemp = 5000;
			if (CheckAttribute(npchar, "quest.fullRing")) iTemp = 20000;
			else if (CheckAttribute(npchar, "quest.doneRing")) iTemp = 10000;

			AddMoneyToCharacter(pchar, iTemp);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "SeekGoods_3":
			dialog.text = StringFromKey("MalcolmFawn_297");
			link.l1 = StringFromKey("MalcolmFawn_298");
			link.l1.go = "exit";
			npchar.quest.withoutMoney = 1;
		break;
		case "SeekGoods_4":
			dialog.text = StringFromKey("MalcolmFawn_299", pchar);
			bool bPotionwine = CheckCharacterItem(pchar, "potionwine") && sti(pchar.items.potionwine) < 3;
			bool bPotion5 = CheckCharacterItem(pchar, "potion5") && sti(pchar.items.potion5) < 10;
			bool bGoods = !CheckCharacterItem(pchar, "Mineral2") || !CheckCharacterItem(pchar, "potionwine") || !CheckCharacterItem(pchar, "potion5") || bPotionwine || bPotion5;
			sld = CharacterFromID("ElizaCalvo");
			if (GetCargoGoods(pchar, GOOD_BOMBS) < 100 && bGoods && CheckAttribute(sld, "quest.bombs"))
			{
				link.l1 = StringFromKey("MalcolmFawn_300");
				link.l1.go = "SeekGoods_5";
			}
			bool bMineral = CheckCharacterItem(pchar, "Mineral10") && sti(pchar.items.Mineral10) < 10;
			bGoods = !CheckCharacterItem(pchar, "Mineral10") || bMineral;
			sld = CharacterFromID("LeaToors");
			if (GetCargoGoods(pchar, GOOD_GRAPES) < 100 && bGoods && CheckAttribute(sld, "quest.grapes"))
			{
				link.l2 = StringFromKey("MalcolmFawn_301");
				link.l2.go = "SeekGoods_7";
			}
			link.l9 = StringFromKey("MalcolmFawn_302");
			link.l9.go = "exit";
		break;
		case "SeekGoods_5":
			sTemp = StringFromKey("MalcolmFawn_303", pchar);
			if (!CheckAttribute(npchar, "quest.withoutMoney")) sTemp = StringFromKey("MalcolmFawn_304", sTemp);
			dialog.text = sTemp;
			if (CheckAttribute(npchar, "quest.withoutMoney"))
			{
				link.l1 = StringFromKey("MalcolmFawn_305");
				link.l1.go = "SeekGoods_6";
			}
			else
			{
				if (sti(pchar.money < 15000))
				{
					link.l1 = StringFromKey("MalcolmFawn_306");
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = StringFromKey("MalcolmFawn_307");
					link.l1.go = "SeekGoods_6";
					link.l2 = StringFromKey("MalcolmFawn_308");
					link.l2.go = "exit";
				}
			}
		break;
		case "SeekGoods_6":
			AddItemLog(pchar, "Mineral2", "1", StringFromKey("InfoMessages_181"), "Important_item");
			AddItemLog(pchar, "potionwine", "3", StringFromKey("InfoMessages_182"), "Important_item");
			AddItemLog(pchar, "potion5", "10", StringFromKey("InfoMessages_183"), "Important_item");
			if (!CheckAttribute(npchar, "quest.withoutMoney")) AddMoneyToCharacter(pchar, -15000);
			DialogExit();
			SetCurrentQuestMark(npchar);
		break;
		case "SeekGoods_7":
			sTemp = StringFromKey("MalcolmFawn_309");
			if (!CheckAttribute(npchar, "quest.withoutMoney")) sTemp = StringFromKey("MalcolmFawn_310", sTemp);
			dialog.text = sTemp;
			if (CheckAttribute(npchar, "quest.withoutMoney"))
			{
				link.l1 = StringFromKey("MalcolmFawn_311");
				link.l1.go = "SeekGoods_8";
			}
			else
			{
				if (sti(pchar.money < 10000))
				{
					link.l1 = StringFromKey("MalcolmFawn_312");
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = StringFromKey("MalcolmFawn_313");
					link.l1.go = "SeekGoods_8";
					link.l2 = StringFromKey("MalcolmFawn_314");
					link.l2.go = "exit";
				}
			}
		break;
		case "SeekGoods_8":
			AddItemLog(pchar, "Mineral10", "10", StringFromKey("InfoMessages_184"), "Important_item");
			if (!CheckAttribute(npchar, "quest.withoutMoney")) AddMoneyToCharacter(pchar, -10000);
			DialogExit();
			SetCurrentQuestMark(npchar);
		break;

		case "SeekCrewInTavern":
			dialog.text = StringFromKey("MalcolmFawn_315");
			link.l1 = StringFromKey("MalcolmFawn_316");
			link.l1.go = "SeekCrewInTavern_1";
		break;
		case "SeekCrewInTavern_1":
			dialog.text = StringFromKey("MalcolmFawn_317");
			link.l1 = StringFromKey("MalcolmFawn_318");
			link.l1.go = "SeekCrewInTavern_2";
		break;
		case "SeekCrewInTavern_2":
			dialog.text = StringFromKey("MalcolmFawn_319");
			link.l1 = StringFromKey("MalcolmFawn_320");
			link.l1.go = "SeekCrewInTavern_3";
		break;
		case "SeekCrewInTavern_3":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", LAi_FindNearestLocator2NPC(npchar, "reload"), "none", "", "", "LSC_MalcolmReturn", 5.0);
		break;
		//разговор что надо бюежать в тюрьму
		case "GoToSaveMechanic":
			dialog.text = StringFromKey("MalcolmFawn_321", pchar);
			link.l1 = StringFromKey("MalcolmFawn_322");
			link.l1.go = "GoToSaveMechanic_Exit";
		break;
		case "GoToSaveMechanic_Exit":
			chrDisableReloadToLocation = false;
			AddDialogExitQuest("LSC_talkWithWalker_MilitiaEscape");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload55", "none", "", "", "", 90.0);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//начало перевозки
		case "BeginningOfTransportation":
			dialog.text = StringFromKey("MalcolmFawn_323");
			link.l1 = StringFromKey("MalcolmFawn_324");
			link.l1.go = "BeginningOfTransportation_1";
		break;
		case "BeginningOfTransportation_1":
			dialog.text = StringFromKey("MalcolmFawn_325");
			link.l1 = StringFromKey("MalcolmFawn_326");
			link.l1.go = "BeginningOfTransportation_2";
		break;
		case "BeginningOfTransportation_2":
			dialog.text = StringFromKey("MalcolmFawn_327", pchar);
			link.l1 = StringFromKey("MalcolmFawn_328");
			link.l1.go = "BeginningOfTransportation_3";
		break;
		case "BeginningOfTransportation_3":
			dialog.text = StringFromKey("MalcolmFawn_329");
			link.l1 = StringFromKey("MalcolmFawn_330", pchar);
			link.l1.go = "BeginningOfTransportation_4";
		break;
		case "BeginningOfTransportation_4":
			dialog.text = StringFromKey("MalcolmFawn_331", pchar);
			link.l1 = StringFromKey("MalcolmFawn_332");
			link.l1.go = "BeginningOfTransportation_5";
		break;
		case "BeginningOfTransportation_5":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "LostShipsCity_town", "goto", "goto17_3", "LSC_MalcolmStay", 5.0);
			AddQuestRecord("ISS_MainLine", "76");
		break;
		//финальная реплика
		case "GoodBye":
			dialog.text = StringFromKey("MalcolmFawn_333");
			link.l1 = StringFromKey("MalcolmFawn_334");
			link.l1.go = "GoodBye_1";
		break;
		case "GoodBye_1":
			dialog.text = StringFromKey("MalcolmFawn_335");
			link.l1 = StringFromKey("MalcolmFawn_336");
			link.l1.go = "GoodBye_2";
		break;
		case "GoodBye_2":
			dialog.text = StringFromKey("MalcolmFawn_337");
			link.l1 = StringFromKey("MalcolmFawn_338");
			link.l1.go = "GoodBye_3";
		break;
		case "GoodBye_3":
			dialog.text = StringFromKey("MalcolmFawn_339");
			link.l1 = StringFromKey("MalcolmFawn_340");
			link.l1.go = "GoodBye_4";
		break;
		case "GoodBye_4":
			dialog.text = StringFromKey("MalcolmFawn_341");
			link.l1 = StringFromKey("MalcolmFawn_342");
			link.l1.go = "exit";
			AddDialogExitQuest("LSC_finishSelfTalk");
		break;

		//TODO к релизу удалить, если не понадобится конечно...
		/*
		//найм команды
		case "SeekCrew":
			dialog.text = "Конечно! Спасибо, " + GetSexPhrase("дружище","подруга") + ", что не " + GetSexPhrase("забыл", "забыла") + " старика!";
			link.l1 = "Отлично! Тогда немедленно беги на 'Сан Габриэль'. Хенрик Ведекер переправит тебя на мой корвет.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = "Хорошо, я так и сделаю. Скраб давно упакован, остаётся его только взять. Хе-хе.";
			link.l1 = "Не задерживайся!";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
		    DialogExit();
			DeleteAttribute(npchar, "quest.toSeekPeopleInCrew");
			AddQuestRecord("ISS_MainLine", "71");
            AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("",StringFromKey("SexEnding_1")));
			npchar.quest.crewDone = 1;
			chrDisableReloadToLocation = true;
			GetCharacterPos(pchar, &locx, &locy, &locz);
            if (npchar.location.group == "sit")
            {
                ChangeCharacterAddressGroup(npchar, npchar.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
            }
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 10.0);
		break;*/

		//квест Табак Малькольма
		case "Tobacco":
			dialog.text = StringFromKey("MalcolmFawn_343", pchar);
			link.l1 = StringFromKey("MalcolmFawn_344");
			link.l1.go = "Tobacco_1";
		break;
		case "Tobacco_1":
			AddQuestRecord("MalcolmsTobacco", "4");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload5", "none", "", "", "OpenTheDoors", 10.0);

			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload8", "MalcolmTobacco_GoToStore", -1);

			NextDiag.CurrentNode = "Tobacco_2";
			DialogExit();
		break;
		case "Tobacco_2":
			dialog.text = StringFromKey("MalcolmFawn_345");
			link.l1 = StringFromKey("MalcolmFawn_346");
			link.l1.go = "Tobacco_3";
		break;
		case "Tobacco_3":
			AddQuestRecord("MalcolmsTobacco", "5");

			pchar.quest.MalcolmsTobacco.win_condition.l1 = "location";
			pchar.quest.MalcolmsTobacco.win_condition.l1.location = "Shore11";
			pchar.quest.MalcolmsTobacco.function = "GenerateTobaccoSmugglersInShore";
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 7.0);

			NextDiag.CurrentNode = "Tobacco_4";
			DialogExit();
		break;
		case "Tobacco_4":
			dialog.text = StringFromKey("MalcolmFawn_347");
			link.l1 = StringFromKey("MalcolmFawn_348");
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false;
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			pchar.quest.Malcolm_Death.over = "yes";
			AddDialogExitQuestFunction("MalcolmDialogInShore");
		break;
		//диалог Малькольма с Контрабандистами начало
		case "Tobacco_5":
			sld = characterFromId("Blaze");
			dialog.text = StringFromKey("MalcolmFawn_349");
			if (CheckAttribute(npchar, "quest.lie"))
			{
				link.l1 = StringFromKey("MalcolmFawn_350", sld);
				link.l1.go = "Tobacco_6";
			}
			else
			{
				link.l1 = StringFromKey("MalcolmFawn_351");
				link.l1.go = "Tobacco_7";
			}
		break;
		case "Tobacco_6":
			sld = characterFromId("Blaze");
			iTemp = GetCargoGoods(sld, GOOD_TOBACCO);
			if (CheckAttribute(npchar, "quest.lie") || iTemp > 100)
			{
				dialog.text = StringFromKey("MalcolmFawn_352", sld);
			}
			else
			{
				dialog.text = StringFromKey("MalcolmFawn_366", sld);
				Achievment_Set(ACH_Krysa);
			}
			link.l1 = StringFromKey("MalcolmFawn_353");
			link.l1.go = "exit";
			AddDialogExitQuest("MalcolmShoreGangDialog");
		break;
		case "Tobacco_7":
			sld = characterFromId("Blaze");
			iTemp = GetCargoGoods(sld, GOOD_TOBACCO);
			dialog.text = StringFromKey("MalcolmFawn_354", iTemp);
			if (iTemp < 700)
			{
				if (iTemp < 690)
				{
					link.l1 = StringFromKey("MalcolmFawn_355", sld, iTemp);
					link.l1.go = "Tobacco_6";
				}
				else
				{
					link.l1 = StringFromKey("MalcolmFawn_356", iTemp);
					link.l1.go = "Tobacco_8";
				}
			}
			else
			{
				link.l1 = StringFromKey("MalcolmFawn_357");
				link.l1.go = "Tobacco_8";
			}
		break;
		case "Tobacco_8":
			sld = characterFromId("Blaze");
			aref refGoods;
			ref Colony = GetColonyByIndex(FindColony("PuertoPrincipe"));
			ref trader = &stores[sti(Colony.StoreNum)];
			int moneyback = 0;

			string goodname = Goods[GOOD_TOBACCO].Name;
			makearef(refGoods, trader.Goods.(goodname));
			int iUnits = Goods[GOOD_TOBACCO].Units;
			int iStoreQty = GetStoreGoodsQuantity(trader, GOOD_TOBACCO);
			int iStorePrice = GetStoreGoodsPrice(trader, GOOD_TOBACCO, PRICE_TYPE_SELL, sld, 1);
			RemoveCharacterGoods(sld, GOOD_TOBACCO, 700);
			moneyback += makeint(iStorePrice * 700 / iUnits + 0.5);
			sld = CharacterFromID("MalcolmFawn");
			sld.quest.MalcolmsTobacco.moneyback = moneyback / 2;

			sld.dialog.currentnode = "Tobacco_9";
			AddDialogExitQuest("MalcolmShoreGangDialog");
			DialogExit();
		break;
		//диалог Малькольма с Контрабандистами конец
		case "Tobacco_9":
			LAi_LockFightMode(pchar, false);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			InterfaceStates.Buttons.Save.enable = true;
			dialog.text = StringFromKey("MalcolmFawn_358", pchar);
			link.l1 = StringFromKey("MalcolmFawn_359");
			link.l1.go = "Tobacco_9_1";
			link.l2 = StringFromKey("MalcolmFawn_360");
			link.l2.go = "Tobacco_10";
			AddMoneyToCharacter(pchar, sti(npchar.quest.MalcolmsTobacco.moneyback));
			SetCharacterPerk(pchar, "Schemer");
		break;
		case "Tobacco_9_1":
			dialog.text = StringFromKey("MalcolmFawn_361", pchar);
			link.l1 = StringFromKey("MalcolmFawn_362");
			link.l1.go = "Tobacco_11";
			link.l2 = StringFromKey("MalcolmFawn_363");
			link.l2.go = "Tobacco_10";
		break;

		case "Tobacco_10":
			npchar.lifeDay = 0;
			AddQuestRecord("MalcolmsTobacco", "6");
			CloseQuestHeader("MalcolmsTobacco");

			DeleteAttribute(pchar, "quest.MalcolmsTobacco");
			DeleteAttribute(pchar, "quest.WaitMalcolm");
			DeleteAttribute(pchar, "GenQuest.Hunter2Pause");
			DialogExit();
		break;
		case "Tobacco_11":
			dialog.text = StringFromKey("MalcolmFawn_364");
			link.l1 = StringFromKey("MalcolmFawn_365");
			link.l1.go = "Tobacco_12";
		break;
		case "Tobacco_12":
			AddQuestRecord("MalcolmsTobacco", "7");
			CloseQuestHeader("MalcolmsTobacco");

			DeleteAttribute(pchar, "quest.MalcolmsTobacco");
			DeleteAttribute(pchar, "quest.WaitMalcolm");
			DeleteAttribute(pchar, "GenQuest.Hunter2Pause");
			DeleteAttribute(npchar, "quest");
			SetCharacterRemovable(npchar, true);

			npchar.Dialog.Filename = "Officer_Man.c";
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			LAi_SetRolyPoly(npchar, true); //неваляха
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			LAi_SetActorType(npchar);   //делает нпс актёром
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7);  // идёт в определённый локатор.
			DialogExit();
		break;
	}
}
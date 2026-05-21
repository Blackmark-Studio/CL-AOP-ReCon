void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref rItem, rChar, sld, MerPrm;
	aref arTemp1, arTemp2;
	bool bOk;
	int iBanditsCount, i, iMoney, iNation, iTemp, iGoods;
	string sTitle, sGroup, sTemp, sText;
	float locx, locy, locz;

	switch (Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = StringFromKey("GenQuests_Dialog_1");
			link.l1 = StringFromKey("GenQuests_Dialog_2", RandSwear());
			link.l1.go = "exit";

			if (HasSubStr(NPChar.id, "ContraMeetManQuest_Soldier_")) // Солдеры по квесту "встреча в бухте"
			{
				dialog.text = StringFromKey("GenQuests_Dialog_3");
				link.l1 = StringFromKey("GenQuests_Dialog_7", LinkRandPhrase(
							StringFromKey("GenQuests_Dialog_4"),
							StringFromKey("GenQuests_Dialog_5"),
							StringFromKey("GenQuests_Dialog_6")));
				link.l1.go = "exit";
				break;
			}

			if (HasSubStr(NPChar.id, "ContraMeetManQuest_Officer_")) // Офицер по квесту "встреча в бухте"
			{
				dialog.text = StringFromKey("GenQuests_Dialog_8");
				link.l1 = StringFromKey("GenQuests_Dialog_9", GetFullName(PChar));
				link.l1.go = "ContraMeetManQuest_Sold_1";
				break;
			}

			if (NPChar.id == "ContraMeetManQuest_QuestMan" && PChar.location == PChar.GenQuest.ContraMeetMan.ShoreID) // Квестовый чел по генеру "встреча в бухте"
			{
				dialog.text = StringFromKey("GenQuests_Dialog_10", GetFullName(PChar));
				link.l1 = StringFromKey("GenQuests_Dialog_11");
				link.l1.go = "ContraMeetManQuest_1";
				link.l2 = StringFromKey("GenQuests_Dialog_12");
				link.l2.go = "exit";
				break;
			}

			if (NPChar.id == "ContraMeetManQuest_QuestMan" && CheckAttribute(PChar, "GenQuest.ContraMeetMan.ContraIsDead")) // В комнате таверны после убицства контриков
			{
				LAi_LocationFightDisable(LoadedLocation, false);
				dialog.text = StringFromKey("GenQuests_Dialog_13", PChar.name);
				link.l1 = StringFromKey("GenQuests_Dialog_14");
				link.l1.go = "ContraMeetManQuest_7";
				link.l2 = StringFromKey("GenQuests_Dialog_15", pchar);
				link.l2.go = "ContraMeetManQuest_8";
				break;
			}

			if (NPChar.id == "ContraMeetManQuest_Contrick_0") // Контрик в комнате по квесту "встреча в бухте"
			{
				iMoney = (rand(3) + 2) * 500;
				PChar.GenQuest.ContraMeetMan.Money = iMoney;
				if (!CheckAttribute(PChar, "GenQuest.ContraMeetMan.ManIsTraitor")) // Просто платят деньги
				{
					dialog.text = StringFromKey("GenQuests_Dialog_16", pchar, FindMoneyString(iMoney));
					link.l1 = "...";
					link.l1.go = "ContraMeetManQuest_3";
				}
				else
				{
					dialog.text = StringFromKey("GenQuests_Dialog_17", pchar, FindMoneyString(iMoney));
					link.l1 = StringFromKey("GenQuests_Dialog_18");
					link.l1.go = "ContraMeetManQuest_4";
					link.l2 = StringFromKey("GenQuests_Dialog_19");
					link.l2.go = "ContraMeetManQuest_5";
				}
				break;
			}

			if (NPChar.id == "ContraDeliverQuest_Soldier_0") // Солдер в комнате
			{
				dialog.text = StringFromKey("GenQuests_Dialog_20");
				link.l1 = StringFromKey("GenQuests_Dialog_21", pchar);
				link.l1.go = "ContraDeliverQuest_Sold1";
				break;
			}

			if (CheckAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom") && NPChar.id == "ContraDeliverQuest_Contra_1")
			{
				dialog.text = StringFromKey("GenQuests_Dialog_22", pchar);
				link.l1 = StringFromKey("GenQuests_Dialog_23");
				link.l1.go = "ContraDeliverQuest_1";
				DeleteAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom");
				DeleteAttribute(PChar, "GenQuest.ContraDeliver.GoToTavern");
				break;
			}

			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = StringFromKey("GenQuests_Dialog_24", pchar);
				link.l1 = StringFromKey("GenQuests_Dialog_25", pchar);
				link.l1.go = "Church_GenQuest_2_ShoreBandit_1";
				break;
			}

			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestGangJungle") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = StringFromKey("GenQuests_Dialog_26", pchar);
				link.l1 = StringFromKey("GenQuests_Dialog_27");
				link.l1.go = "Church_GenQuest_2_1";
				break;
			}

			if (NPChar.id == "ReasonToFast_Hunter")
			{
				//				if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > sti(pchar.questTemp.ReasonToFast.p2))
				if (PlayerRPGCheck_Skill(SKILL_LEADERSHIP, sti(pchar.questTemp.ReasonToFast.p2) + 1, false))
				{
					dialog.text = StringFromKey("GenQuests_Dialog_28");
					link.l1 = StringFromKey("GenQuests_Dialog_29");
					link.l1.go = "ReasonToFast_Hunter1";
				}
				else
				{
					dialog.text = StringFromKey("GenQuests_Dialog_30");
					link.l1 = StringFromKey("GenQuests_Dialog_31", pchar);
					link.l1.go = "ReasonToFast_Hunter2";
				}
				link.l2 = StringFromKey("GenQuests_Dialog_32");
				link.l2.go = "ReasonToFast_Hunter3";
				break;
			}

			if (NPChar.id == "PirateOnUninhabited_0")
			{
				dialog.text = StringFromKey("GenQuests_Dialog_35", RandPhraseSimple(
							StringFromKey("GenQuests_Dialog_33"),
							StringFromKey("GenQuests_Dialog_34")));
				link.l1 = StringFromKey("GenQuests_Dialog_36", GetFullName(PChar));
				link.l1.go = "PiratesOnUninhabited_3";
				link.l2 = StringFromKey("GenQuests_Dialog_37", pchar);
				link.l2.go = "PiratesOnUninhabited_1";
				break;
			}

			if (NPChar.id == "ShipWreck_0")
			{
				dialog.text = StringFromKey("GenQuests_Dialog_40", RandPhraseSimple(
							StringFromKey("GenQuests_Dialog_38"),
							StringFromKey("GenQuests_Dialog_39")));
				link.l1 = StringFromKey("GenQuests_Dialog_41", GetFullName(pchar));
				link.l1.go = "ShipWreck_2";
				link.l2 = StringFromKey("GenQuests_Dialog_42", pchar);
				link.l2.go = "ShipWreck_1";
				break;
			}

			if (NPChar.id == "Convict_0")
			{
				pchar.GenQuest.Convict.ShoreLocation = SelectQuestShoreLocation();
				dialog.text = StringFromKey("GenQuests_Dialog_46", LinkRandPhrase(
							StringFromKey("GenQuests_Dialog_43", GetAddress_Form(pchar)),
							StringFromKey("GenQuests_Dialog_44", pchar),
							StringFromKey("GenQuests_Dialog_45", pchar)));
				link.l1 = StringFromKey("GenQuests_Dialog_50", LinkRandPhrase(
							StringFromKey("GenQuests_Dialog_47"),
							StringFromKey("GenQuests_Dialog_48"),
							StringFromKey("GenQuests_Dialog_49")));
				link.l1.go = "Convict_0End";
				if (pchar.GenQuest.Convict.ShoreLocation != "")
				{
					link.l2 = StringFromKey("GenQuests_Dialog_54", LinkRandPhrase(
								StringFromKey("GenQuests_Dialog_51"),
								StringFromKey("GenQuests_Dialog_52"),
								StringFromKey("GenQuests_Dialog_53")));
					link.l2.go = "Convict_Begin";
				}
				break;
			}

			// "Правосудие на продажу" (Warship, Rosarak)
			if (HasSubStr(NPChar.id, "JusticeOnSale_Jungle_"))
			{
				TEV.ContraRepCheck = ""; //чтоб в отдельную ноду не выносить
				sTemp = "JusticeOnSale_Jungle_";
				for (i = 0; i < 4; i++)
				{
					if (GetCharacterIndex(sTemp + i) == -1) continue;
					sld = CharacterFromID(sTemp + i);
					DeleteAttribute(sld, "talker");
				}

				dialog.text = StringFromKey("GenQuests_Dialog_55");
				link.l1 = StringFromKey("GenQuests_Dialog_56");
				link.l1.go = "JusticeOnSale_1";
				link.l2 = StringFromKey("GenQuests_Dialog_60", LinkRandPhrase(
							StringFromKey("GenQuests_Dialog_57"),
							StringFromKey("GenQuests_Dialog_58", pchar),
							StringFromKey("GenQuests_Dialog_59")));
				link.l2.go = "JusticeOnSale_2";
				break;
			}
		break;

		// Генератор "Ситуация в трюме - Выкуп"
		case "Hold_GenQuest1":
			pchar.quest.Hold_GenQuest_FindCharTimeIsOver.over = "yes";
			dialog.text = StringFromKey("GenQuests_Dialog_61");
			link.l1 = StringFromKey("GenQuests_Dialog_62", pchar.GenQuest.Hold_GenQuest.Name);
			link.l1.go = "Hold_GenQuest2";
		break;

		case "Hold_GenQuest2":
			dialog.text = StringFromKey("GenQuests_Dialog_65", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_63", pchar.GenQuest.Hold_GenQuest.Name),
						StringFromKey("GenQuests_Dialog_64")));
			link.l1 = StringFromKey("GenQuests_Dialog_66", GetFullName(pchar), pchar.GenQuest.Hold_GenQuest.CapName);
			link.l1.go = "Hold_GenQuest3";
		break;

		case "Hold_GenQuest3":
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			pchar.GenQuest.Hold_GenQuest.RansomSum = makeint(3 * sti(sld.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(sld, "Leadership") * 500 + GetCharacterSkillToOld(pchar, "commerce") * 500);

			switch (drand(3))
			{
				case 0:
					dialog.text = StringFromKey("GenQuests_Dialog_67");
					link.l1 = StringFromKey("GenQuests_Dialog_68", pchar.GenQuest.Hold_GenQuest.Name, pchar.GenQuest.Hold_GenQuest.CapName);
					link.l1.go = "Hold_GenQuest40";
				break;
				case 1:
					dialog.text = StringFromKey("GenQuests_Dialog_69");
					link.l1 = StringFromKey("GenQuests_Dialog_70");
					link.l1.go = "Hold_GenQuest50";
				break;
				case 2:
					dialog.text = StringFromKey("GenQuests_Dialog_71");
					link.l1 = StringFromKey("GenQuests_Dialog_72");
					link.l1.go = "Hold_GenQuest60";
				break;
				case 3:
					dialog.text = StringFromKey("GenQuests_Dialog_73");
					link.l1 = StringFromKey("GenQuests_Dialog_74");
					link.l1.go = "Hold_GenQuest70";
				break;
			}
		break;

		case "Hold_GenQuest40":
			dialog.text = StringFromKey("GenQuests_Dialog_75", pchar.GenQuest.Hold_GenQuest.Name, pchar.GenQuest.Hold_GenQuest.CapName);
			link.l1 = StringFromKey("GenQuests_Dialog_76");
			link.l1.go = "Hold_GenQuest41";
		break;

		case "Hold_GenQuest41":
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;

		case "Hold_GenQuest50":
			dialog.text = StringFromKey("GenQuests_Dialog_77");
			link.l1 = StringFromKey("GenQuests_Dialog_78", FindMoneyString(sti(pchar.GenQuest.Hold_GenQuest.RansomSum)));
			link.l1.go = "Hold_GenQuest51";
		break;

		case "Hold_GenQuest51":
			dialog.text = StringFromKey("GenQuests_Dialog_79");
			link.l1 = StringFromKey("GenQuests_Dialog_80");
			link.l1.go = "Hold_GenQuest52";
		break;

		case "Hold_GenQuest52":
			dialog.text = StringFromKey("GenQuests_Dialog_84", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_81"),
						StringFromKey("GenQuests_Dialog_82"),
						StringFromKey("GenQuests_Dialog_83")));
			link.l1 = StringFromKey("GenQuests_Dialog_85");
			link.l1.go = "Hold_GenQuest53";
		break;

		case "Hold_GenQuest53":
			dialog.text = StringFromKey("GenQuests_Dialog_86");
			link.l1 = StringFromKey("GenQuests_Dialog_87");
			link.l1.go = "Hold_GenQuest54";
		break;

		case "Hold_GenQuest54":
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar)); // НПС вешать собрались? )))
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;

		case "Hold_GenQuest60":
			dialog.text = StringFromKey("GenQuests_Dialog_88", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_89", FindMoneyString(sti(pchar.GenQuest.Hold_GenQuest.RansomSum)));
			link.l1.go = "Hold_GenQuest61";
		break;

		case "Hold_GenQuest61":
			dialog.text = StringFromKey("GenQuests_Dialog_90", pchar, NationNameGenitive(sti(pchar.GenQuest.Hold_GenQuest.Nation)));
			link.l1 = StringFromKey("GenQuests_Dialog_91");
			link.l1.go = "Hold_GenQuest62";
		break;

		case "Hold_GenQuest62":
			LAi_SetImmortal(NPChar, false);
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_SetWarriorTypeNoGroup(NPChar);
			LAi_warrior_DialogEnable(NPChar, false);
			LAi_group_MoveCharacter(NPChar, "TmpEnemy");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheckFunction("TmpEnemy", "Hold_GenQuest_AfterBattle");
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
			DialogExit();
		break;

		case "Hold_GenQuest70":
			dialog.text = StringFromKey("GenQuests_Dialog_92");
			link.l1 = StringFromKey("GenQuests_Dialog_93");
			link.l1.go = "Hold_GenQuest71";
		break;

		case "Hold_GenQuest71":
			dialog.text = StringFromKey("GenQuests_Dialog_94");
			link.l1 = StringFromKey("GenQuests_Dialog_95", pchar, FindMoneyString(sti(pchar.GenQuest.Hold_GenQuest.RansomSum)));
			link.l1.go = "Hold_GenQuest72";
		break;

		case "Hold_GenQuest72":
			dialog.text = StringFromKey("GenQuests_Dialog_96");
			link.l1 = StringFromKey("GenQuests_Dialog_97");
			link.l1.go = "Hold_GenQuest73";
		break;

		case "Hold_GenQuest73":
			addMoneyToCharacter(pchar, sti(pchar.GenQuest.Hold_GenQuest.RansomSum));
			AddQuestRecord("HoldQuest", "11");
			AddQuestUserData("HoldQuest", "sNameChar", GetFullName(NPChar)); // belamour gen
			AddQuestUserData("HoldQuest", "sName", NPChar.Hold_GenQuest.Name); // belamour gen
			AddQuestUserData("HoldQuest", "sSum", FindMoneyString(sti(pchar.GenQuest.Hold_GenQuest.RansomSum)));
			pchar.GenQuest.Hold_GenQuest = "prisoner_ransom";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		// Генератор "Ситуация в трюме -Выкуп"

		// Генератор "Ситуация в трюме -Подельник"
		case "Hold_GenQuest80":
			dialog.text = StringFromKey("GenQuests_Dialog_98");
			link.l1 = StringFromKey("GenQuests_Dialog_99", pchar, pchar.GenQuest.Hold_GenQuest.Name, GetFullName(pchar));
			link.l1.go = "Hold_GenQuest81";
		break;

		case "Hold_GenQuest81":
			dialog.text = StringFromKey("GenQuests_Dialog_100", GetFullName(pchar));
			link.l1 = StringFromKey("GenQuests_Dialog_101");
			link.l1.go = "Hold_GenQuest82";
		break;

		case "Hold_GenQuest82":
			dialog.text = StringFromKey("GenQuests_Dialog_102");
			link.l1 = StringFromKey("GenQuests_Dialog_103", GetName(NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			link.l1.go = "Hold_GenQuest83";
		break;

		case "Hold_GenQuest83":
			dialog.text = StringFromKey("GenQuests_Dialog_104", pchar.GenQuest.Hold_GenQuest.CapName);
			link.l1 = StringFromKey("GenQuests_Dialog_105");
			link.l1.go = "Hold_GenQuest84";
		break;

		case "Hold_GenQuest84":
			dialog.text = StringFromKey("GenQuests_Dialog_106");
			link.l1 = StringFromKey("GenQuests_Dialog_107", GetName(NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_NOM));
			link.l1.go = "Hold_GenQuest85";
		break;

		case "Hold_GenQuest85":
			dialog.text = StringFromKey("GenQuests_Dialog_108", FindMoneyString(sti(pchar.GenQuest.Hold_GenQuest.Sum)));
			if (sti(pchar.money) >= sti(pchar.GenQuest.Hold_GenQuest.Sum) && !CheckCharacterItem(pchar, "mapQuest") && !CheckCharacterItem(pchar, "map_full"))
			{
				link.l1 = StringFromKey("GenQuests_Dialog_109");
				link.l1.go = "Hold_GenQuest86";
			}
			link.l2 = StringFromKey("GenQuests_Dialog_110");
			link.l2.go = "Hold_GenQuest87";
			pchar.quest.Hold_GenQuest_GetMapTimeIsOver.over = "yes";
		break;

		case "Hold_GenQuest86":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Hold_GenQuest.Sum));
			GiveItem2Character(pchar, "mapQuest");
			rItem = ItemsFromID("mapQuest");
			Hold_GenQuest_GenerateTreasureMap(rItem);
			AddQuestRecord("HoldQuest", "15");
			AddQuestUserData("HoldQuest", "sPirateName", GetName(NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("HoldQuest", "sSum", FindMoneyString(sti(pchar.GenQuest.Hold_GenQuest.Sum)));
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Hold_GenQuest87":
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			AddQuestRecord("HoldQuest", "16");
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest");
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		// Генератор "Ситуация в трюме -Подельник"

		// Генератор "Потерпевшие кораблекрушение"
		case "ShipWreck_1":
			dialog.text = StringFromKey("GenQuests_Dialog_111");
			link.l1 = StringFromKey("GenQuests_Dialog_112");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -1);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;

		case "ShipWreck_2":
			pchar.GenQuest.ShipWreck.StartShipType = PiratesOnUninhabited_GenerateShipType();
			pchar.GenQuest.ShipWreck.ShipTypeName = GenerateRandomNameToShip(sti(pchar.GenQuest.ShipWreck.Nation));
			if (rand(1) == 0)
			{
				dialog.text = StringFromKey("GenQuests_Dialog_115", RandPhraseSimple(
							StringFromKey("GenQuests_Dialog_113", pchar.GenQuest.ShipWreck.Name, GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc")), pchar.GenQuest.ShipWreck.ShipTypeName, FindWeekString(dRand(7) + 1)),
							StringFromKey("GenQuests_Dialog_114", pchar.GenQuest.ShipWreck.Name, GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc")), pchar.GenQuest.ShipWreck.ShipTypeName, FindWeekString(dRand(7) + 1))));
				link.l1 = StringFromKey("GenQuests_Dialog_118", RandPhraseSimple(
							StringFromKey("GenQuests_Dialog_116"),
							StringFromKey("GenQuests_Dialog_117")));
				link.l1.go = "ShipWreck_3";
			}
			else
			{
				pchar.GenQuest.ShipWreck.Mutiny = true;
				pchar.GenQuest.ShipWreck.BadName = GenerateRandomName_Generator(sti(pchar.GenQuest.ShipWreck.Nation), "man");
				pchar.GenQuest.ShipWreck.City = GetQuestNationsCity(sti(pchar.GenQuest.ShipWreck.Nation));
				dialog.text = StringFromKey("GenQuests_Dialog_128", pchar.GenQuest.ShipWreck.Name, GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc")), pchar.GenQuest.ShipWreck.ShipTypeName, pchar.GenQuest.ShipWreck.BadName, LinkRandPhrase(
							StringFromKey("GenQuests_Dialog_121", RandPhraseSimple(
									StringFromKey("GenQuests_Dialog_119"),
									StringFromKey("GenQuests_Dialog_120"))),
							StringFromKey("GenQuests_Dialog_124", RandPhraseSimple(
									StringFromKey("GenQuests_Dialog_122"),
									StringFromKey("GenQuests_Dialog_123"))),
							StringFromKey("GenQuests_Dialog_127", RandPhraseSimple(
									StringFromKey("GenQuests_Dialog_125"),
									StringFromKey("GenQuests_Dialog_126")))), XI_ConvertString("Colony" + pchar.GenQuest.ShipWreck.City + "Pre"), FindWeekString(dRand(7) + 1));
				link.l1 = StringFromKey("GenQuests_Dialog_129");
				link.l1.go = "ShipWreck_4";
			}
		break;

		case "ShipWreck_3":
			dialog.text = StringFromKey("GenQuests_Dialog_132", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_130", ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty))),
						StringFromKey("GenQuests_Dialog_131", ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)))));
			link.l1 = StringFromKey("GenQuests_Dialog_136", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_133"),
						StringFromKey("GenQuests_Dialog_134"),
						StringFromKey("GenQuests_Dialog_135")));
			link.l1.go = "ShipWreck_5";
		break;

		case "ShipWreck_4":
			dialog.text = StringFromKey("GenQuests_Dialog_137", ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)));
			link.l1 = StringFromKey("GenQuests_Dialog_140", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_138"),
						StringFromKey("GenQuests_Dialog_139")));
			link.l1.go = "ShipWreck_5";
			link.l2 = StringFromKey("GenQuests_Dialog_141", pchar);
			link.l2.go = "ShipWreck_6";
		break;

		case "ShipWreck_5":
			dialog.text = StringFromKey("GenQuests_Dialog_144", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_142"),
						StringFromKey("GenQuests_Dialog_143")));
			if (GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l1 = StringFromKey("GenQuests_Dialog_145");
				link.l1.go = "ShipWreck_7";
			}
			link.l2 = StringFromKey("GenQuests_Dialog_152", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_148", RandPhraseSimple(
								StringFromKey("GenQuests_Dialog_146"),
								StringFromKey("GenQuests_Dialog_147"))),
						StringFromKey("GenQuests_Dialog_151", RandPhraseSimple(
								StringFromKey("GenQuests_Dialog_149"),
								StringFromKey("GenQuests_Dialog_150", pchar)))));
			link.l2.go = "ShipWreck_8";
			if (stf(pchar.reputation) <= REPUTATION_NEUTRAL)
			{
				link.l3 = StringFromKey("GenQuests_Dialog_153");
				link.l3.go = "ShipWreck_9";
			}
		break;

		case "ShipWreck_6":
			dialog.text = StringFromKey("GenQuests_Dialog_154", GetAddress_Form(npchar), pchar.lastname);
			link.l1 = StringFromKey("GenQuests_Dialog_155");
			link.l1.go = "ShipWreck_18";
			if (GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = StringFromKey("GenQuests_Dialog_156", pchar.GenQuest.ShipWreck.BadName);
				link.l2.go = "ShipWreck_19";
			}
		break;

		case "ShipWreck_7":
			if (rand(1) == 0)
			{
				if (rand(100) < 90)
				{
					pchar.GenQuest.ShipWreck.variant = "1";
					dialog.text = StringFromKey("GenQuests_Dialog_157", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
					link.l1 = StringFromKey("GenQuests_Dialog_158");
					link.l1.go = "ShipWreck_10";
					link.l2 = StringFromKey("GenQuests_Dialog_159");
					link.l2.go = "ShipWreck_11";
				}
				else
				{
					dialog.text = StringFromKey("GenQuests_Dialog_160");
					link.l1 = StringFromKey("GenQuests_Dialog_161");
					link.l1.go = "ShipWreck_12";
					pchar.GenQuest.ShipWreck.Crazy = true; // получите психа на борт :-)

				}
			}
			else
			{
				pchar.GenQuest.ShipWreck.variant = "2";
				dialog.text = StringFromKey("GenQuests_Dialog_162");
				link.l1 = StringFromKey("GenQuests_Dialog_163");
				link.l1.go = "ShipWreck_10_1";
				link.l2 = StringFromKey("GenQuests_Dialog_164");
				link.l2.go = "ShipWreck_11";
			}
		break;

		case "ShipWreck_8":
			pchar.GenQuest.ShipWreck.FoodQty = sti(pchar.GenQuest.ShipWreck.Qty) * 10 + rand(10);
			pchar.GenQuest.ShipWreck.MedicamentQty = sti(pchar.GenQuest.ShipWreck.Qty) * 5 + rand(10);
			pchar.GenQuest.ShipWreck.AmunitionQty = sti(pchar.GenQuest.ShipWreck.Qty) * 3 + rand(5);
			pchar.GenQuest.ShipWreck.RumQty = sti(pchar.GenQuest.ShipWreck.Qty) * 7 + rand(10);
			if (GetFreeCrewQuantity(pchar) < sti(pchar.GenQuest.ShipWreck.Qty))
			{
				if (GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))
				{
					dialog.text = StringFromKey("GenQuests_Dialog_165");
					link.l1 = StringFromKey("GenQuests_Dialog_166");
					link.l1.go = "ShipWreck_8_1";
					link.l2 = StringFromKey("GenQuests_Dialog_167");
					link.l2.go = "ShipWreck_16";
				}
				else
				{
					dialog.text = StringFromKey("GenQuests_Dialog_168");
					if (GetSquadronGoods(pchar, GOOD_WEAPON) < sti(pchar.GenQuest.ShipWreck.AmunitionQty) || GetSquadronGoods(pchar, GOOD_RUM) < sti(pchar.GenQuest.ShipWreck.RumQty))
					{
						link.l1 = StringFromKey("GenQuests_Dialog_169");
						link.l1.go = "ShipWreck_8_2";
					}
					else
					{
						if (rand(1) == 0)
						{
							link.l1 = StringFromKey("GenQuests_Dialog_170");
							link.l1.go = "ShipWreck_8_2";
						}
						else
						{
							link.l1 = StringFromKey("GenQuests_Dialog_171", pchar);
							link.l1.go = "ShipWreck_8_4";
						}
					}
				}
			}
			else
			{
				if (stf(pchar.reputation) <= REPUTATION_NEUTRAL) // плохиш
				{
					if (GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))
					{
						dialog.text = StringFromKey("GenQuests_Dialog_172");
						link.l1 = StringFromKey("GenQuests_Dialog_173");
						link.l1.go = "ShipWreck_8_1";
						link.l2 = StringFromKey("GenQuests_Dialog_174");
						link.l2.go = "ShipWreck_16";
					}
					else
					{
						link.l1 = StringFromKey("GenQuests_Dialog_175");
						link.l1.go = "ShipWreck_8_2";
					}
				}
				else // кибальчиш
				{
					if (GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))
					{
						if (rand(1) == 0)
						{
							dialog.text = StringFromKey("GenQuests_Dialog_176");
							link.l1 = StringFromKey("GenQuests_Dialog_177");
							link.l1.go = "ShipWreck_8_1";
							link.l2 = StringFromKey("GenQuests_Dialog_178");
							link.l2.go = "ShipWreck_16";
						}
						else
						{
							dialog.text = StringFromKey("GenQuests_Dialog_179");
							link.l1 = StringFromKey("GenQuests_Dialog_180");
							link.l1.go = "ShipWreck_16";
						}
					}
					else
					{
						link.l1 = StringFromKey("GenQuests_Dialog_181");
						link.l1.go = "ShipWreck_8_2";
					}
				}
			}
		break;

		case "ShipWreck_8_1":
			dialog.text = StringFromKey("GenQuests_Dialog_182");
			link.l1 = StringFromKey("GenQuests_Dialog_183", pchar);
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -5);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;

		case "ShipWreck_8_2":
			dialog.text = StringFromKey("GenQuests_Dialog_184");
			link.l1 = StringFromKey("GenQuests_Dialog_185");
			link.l1.go = "ShipWreck_8_3";
		break;

		case "ShipWreck_8_3":
			ChangeCharacterReputation(pchar, -2);
			AddCharacterExpToSkill(pchar, "Leadership", 25);
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));
			Log_SetStringToLog(StringFromKey("InfoMessages_190", pchar.GenQuest.ShipWreck.FoodQty));
			Log_SetStringToLog(StringFromKey("InfoMessages_191", pchar.GenQuest.ShipWreck.MedicamentQty));
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_7";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "ShipWreck_8_4":
			dialog.text = StringFromKey("GenQuests_Dialog_186");
			link.l1 = StringFromKey("GenQuests_Dialog_187");
			link.l1.go = "ShipWreck_8_5";
		break;

		case "ShipWreck_8_5":
			pchar.quest.ShipWreck_LocationExit.over = "yes";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));
			RemoveCharacterGoods(pchar, GOOD_WEAPON, sti(pchar.GenQuest.ShipWreck.AmunitionQty));
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.GenQuest.ShipWreck.RumQty));
			Log_SetStringToLog(StringFromKey("InfoMessages_190", pchar.GenQuest.ShipWreck.FoodQty));
			Log_SetStringToLog(StringFromKey("InfoMessages_191", pchar.GenQuest.ShipWreck.MedicamentQty));
			Log_SetStringToLog(StringFromKey("InfoMessages_192", pchar.GenQuest.ShipWreck.AmunitionQty));
			Log_SetStringToLog(StringFromKey("InfoMessages_193", pchar.GenQuest.ShipWreck.RumQty));
			ReOpenQuestHeader("ShipWrecked");
			if (CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "11");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("", "а"));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen")));
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "10");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("", "а"));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen")));
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_6";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.ShipWreck = "SailorsOnShore";
			SetFunctionTimerCondition("ShipWreck_SaveSailors", 0, 0, 30, false);
			pchar.GenQuest.ShipWreck.Shore = pchar.location;
			SaveCurrentQuestDateParam("GenQuest.ShipWreck");
			SetFunctionLocationCondition("ShipWreck_MeetInShore", pchar.GenQuest.ShipWreck.Shore, true);
		break;

		case "ShipWreck_8_6":
			dialog.text = StringFromKey("GenQuests_Dialog_190", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_188"),
						StringFromKey("GenQuests_Dialog_189")));
			link.l1 = StringFromKey("GenQuests_Dialog_191");
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_6";
		break;

		case "ShipWreck_8_7":
			dialog.text = StringFromKey("GenQuests_Dialog_194", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_192"),
						StringFromKey("GenQuests_Dialog_193")));
			link.l1 = StringFromKey("GenQuests_Dialog_195");
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_7";
		break;

		case "ShipWreck_9":
			pchar.GenQuest.ShipWreck = "SailorsOnShoreFight"; // belamour gen
			dialog.text = StringFromKey("GenQuests_Dialog_196");
			link.l1 = StringFromKey("GenQuests_Dialog_197");
			link.l1.go = "ShipWreck_16";
		break;

		case "ShipWreck_10":
			dialog.text = StringFromKey("GenQuests_Dialog_198");
			link.l1 = StringFromKey("GenQuests_Dialog_199");
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Nation_City";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.nation = sti(pchar.GenQuest.ShipWreck.Nation);
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if (CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "2");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "count",  FindSailorString(sti(pchar.GenQuest.ShipWreck.Qty), "No"));
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "1");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "count",  FindSailorString(sti(pchar.GenQuest.ShipWreck.Qty), "No"));
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины
				if (ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", StringFromKey("GenQuests_Dialog_1204"));
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", StringFromKey("GenQuests_Dialog_1205"));
				}
				// <-- belamour
			}

		break;

		case "ShipWreck_10_1":
			dialog.text = StringFromKey("GenQuests_Dialog_200");
			link.l1 = StringFromKey("GenQuests_Dialog_201");
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if (CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "4");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				AddQuestUserData("ShipWrecked", "count",  FindSailorString(sti(pchar.GenQuest.ShipWreck.Qty), "No"));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "3");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "count",  FindSailorString(sti(pchar.GenQuest.ShipWreck.Qty), "No"));
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины
				if (ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", StringFromKey("GenQuests_Dialog_1204"));
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", StringFromKey("GenQuests_Dialog_1205"));
				}
				// <-- belamour
			}
		break;

		case "ShipWreck_11":
			dialog.text = StringFromKey("GenQuests_Dialog_202");
			link.l1 = StringFromKey("GenQuests_Dialog_203");
			link.l1.go = "ShipWreck_14";
			if (GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l2 = StringFromKey("GenQuests_Dialog_204", pchar);
				link.l2.go = "ShipWreck_15";
			}
		break;

		case "ShipWreck_12":
			dialog.text = StringFromKey("GenQuests_Dialog_205");
			link.l1 = StringFromKey("GenQuests_Dialog_206");
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ChangeOfficersLoyality("bad_all", 1);
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "5");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); //TODO: падежи, а что если он напишет "на берегу берега..."
			AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
			AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc")));
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
			// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины
			if (ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
			{
				AddQuestUserData("ShipWrecked", "sText", StringFromKey("GenQuests_Dialog_1204"));
			}
			else
			{
				AddQuestUserData("ShipWrecked", "sText", StringFromKey("GenQuests_Dialog_1205"));
			}
		// <-- belamour
		break;

		case "ShipWreck_13": // берем пассажирами
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			if (CheckAttribute(pchar, "GenQuest.ShipWreck.variant"))
			{
				if (pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterReputation(pchar, 1);
				if (pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterReputation(pchar, 2);
			}
			for (i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if (i == 0)
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "ShipWreck_13_again";
			}
			DialogExit();
		break;

		case "ShipWreck_13_again":
			dialog.text = StringFromKey("GenQuests_Dialog_210", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_207"),
						StringFromKey("GenQuests_Dialog_208"),
						StringFromKey("GenQuests_Dialog_209")));
			link.l1 = StringFromKey("GenQuests_Dialog_211");
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_13_again";
		break;

		case "ShipWreck_14":
			dialog.text = StringFromKey("GenQuests_Dialog_212");
			link.l1 = StringFromKey("GenQuests_Dialog_213", pchar);
			link.l1.go = "ShipWreck_16";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "ShipWreck_15":
			dialog.text = StringFromKey("GenQuests_Dialog_214");
			link.l1 = StringFromKey("GenQuests_Dialog_215");
			link.l1.go = "ShipWreck_17";
		break;

		case "ShipWreck_16":
			ChangeCharacterReputation(pchar, -3);
			for (i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetImmortal(rChar, false);
				if (CheckPassengerInCharacter(pchar, "ShipWreck_" + i))
				{
					RemovePassenger(pchar, rChar);
				}
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ShipWreckGroup");
			}

			LAi_Group_SetRelation("ShipWreckGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("ShipWreckGroup", LAI_GROUP_PLAYER, true);
			if (pchar.GenQuest.ShipWreck == "fight" || pchar.GenQuest.ShipWreck == "SailorsOnShoreFight") // belamour gen
			{
				LAi_group_SetCheck("ShipWreckGroup", "OpenTheDoors");
				LAi_group_SetCheckFunction("ShipWreckGroup", "ShipWreck_AfterBattle");
			}
			DialogExit();
		break;

		case "ShipWreck_17": // принимаем в команду
			if (pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterReputation(pchar, 1);
			if (pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterReputation(pchar, 2);
			for (i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.currentnode = "ShipWreck_17_again";
			}
			AddCharacterCrew(pchar, sti(pchar.GenQuest.ShipWreck.Qty));
			Log_Info(StringFromKey("InfoMessages_148", FindPeoplesString(sti(pchar.GenQuest.ShipWreck.Qty), "Acc")));
			pchar.quest.ShipWreck_LocExit.over = "yes"; // Снимаем прерывание на выход из локации			
			DeleteAttribute(pchar, "GenQuest.ShipWreck");
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			DialogExit();
		break;

		case "ShipWreck_17_again":
			dialog.text = StringFromKey("GenQuests_Dialog_219", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_216"),
						StringFromKey("GenQuests_Dialog_217"),
						StringFromKey("GenQuests_Dialog_218")));
			link.l1 = StringFromKey("GenQuests_Dialog_222", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_220"),
						StringFromKey("GenQuests_Dialog_221")));
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_17_again";
		break;

		case "ShipWreck_18":
			dialog.text = StringFromKey("GenQuests_Dialog_223");
			link.l1 = StringFromKey("GenQuests_Dialog_224");
			link.l1.go = "ShipWreck_20";
		break;

		case "ShipWreck_19":
			dialog.text = StringFromKey("GenQuests_Dialog_225");
			link.l1 = StringFromKey("GenQuests_Dialog_226");
			link.l1.go = "ShipWreck_13";
			ShipWreck_SetCapToMap();
			SetFunctionTimerCondition("DeadlineHasExpired", 0, 0, 180, false); // таймер лесник тамймер на поиск корабля
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "16");
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "count",  FindSailorString(sti(pchar.GenQuest.ShipWreck.Qty), "No"));
			AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
		break;

		case "ShipWreck_20":
			dialog.text = StringFromKey("GenQuests_Dialog_227");
			if (GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l1 = StringFromKey("GenQuests_Dialog_228");
				link.l1.go = "ShipWreck_17";
			}
			link.l2 = StringFromKey("GenQuests_Dialog_229");
			link.l2.go = "ShipWreck_22";
			link.l3 = StringFromKey("GenQuests_Dialog_230");
			link.l3.go = "ShipWreck_10_1";
		break;

		case "ShipWreck_22":
			dialog.text = StringFromKey("GenQuests_Dialog_231");
			link.l1 = StringFromKey("GenQuests_Dialog_232");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;

		case "ShipWreck_30":
			if (pchar.GenQuest.ShipWreck == "SailorsSaved")
			{
				dialog.text = StringFromKey("GenQuests_Dialog_233", GetFullName(pchar));
				link.l1 = StringFromKey("GenQuests_Dialog_234", pchar.GenQuest.ShipWreck.Name);
				link.l1.go = "ShipWreck_47";
			}
			else
			{
				dialog.text = StringFromKey("GenQuests_Dialog_235");
				link.l1 = StringFromKey("GenQuests_Dialog_236");
				link.l1.go = "ShipWreck_31";
			}
		break;

		case "ShipWreck_31":
		//addMoneyToCharacter(pchar, sti(pchar.rank) * 200 + rand(2000));
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			TakeNItems(pchar, "jewelry2", 15 + drand(10));
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + Locations[FindLocation(PChar.location)].townsack + "Acc"));
			CloseQuestHeader("ShipWrecked");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;

		case "ShipWreck_32":
			dialog.text = StringFromKey("GenQuests_Dialog_237");
			link.l1 = StringFromKey("GenQuests_Dialog_238");
			link.l1.go = "ShipWreck_33";
		break;

		case "ShipWreck_33":
			GiveItem2Character(pchar, pchar.GenQuest.ShipWreck.Prize);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString(pchar.location + "Acc"));
			CloseQuestHeader("ShipWrecked");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;

		case "ShipWreck_34":
			dialog.text = StringFromKey("GenQuests_Dialog_245", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_241", RandPhraseSimple(
								StringFromKey("GenQuests_Dialog_239"),
								StringFromKey("GenQuests_Dialog_240"))),
						StringFromKey("GenQuests_Dialog_244", RandPhraseSimple(
								StringFromKey("GenQuests_Dialog_242"),
								StringFromKey("GenQuests_Dialog_243")))));
			bOk = !GetCharacterItem(pchar, "map_part1") || !GetCharacterItem(pchar, "map_part2");
			if (rand(100) > 75 && !isDay() && bOk)
			{
				link.l1 = StringFromKey("GenQuests_Dialog_246");
				link.l1.go = "ShipWreck_40";
			}
			else
			{
				link.l1 = StringFromKey("GenQuests_Dialog_250", LinkRandPhrase(
							StringFromKey("GenQuests_Dialog_247"),
							StringFromKey("GenQuests_Dialog_248"),
							StringFromKey("GenQuests_Dialog_249")));
				link.l1.go = "ShipWreck_35";
			}
		break;

		case "ShipWreck_35":
			dialog.text = StringFromKey("GenQuests_Dialog_254", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_251"),
						StringFromKey("GenQuests_Dialog_252"),
						StringFromKey("GenQuests_Dialog_253")));
			if (rand(100) < 70)
			{
				link.l1 = StringFromKey("GenQuests_Dialog_255", pchar);
				link.l1.go = "ShipWreck_36";
			}
			link.l2 = StringFromKey("GenQuests_Dialog_264", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_259", LinkRandPhrase(
								StringFromKey("GenQuests_Dialog_256"),
								StringFromKey("GenQuests_Dialog_257"),
								StringFromKey("GenQuests_Dialog_258"))),
						StringFromKey("GenQuests_Dialog_263", LinkRandPhrase(
								StringFromKey("GenQuests_Dialog_260"),
								StringFromKey("GenQuests_Dialog_261"),
								StringFromKey("GenQuests_Dialog_262")))));
			link.l2.go = "ShipWreck_37";
		break;

		case "ShipWreck_36":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			pchar.GenQuest.ShipWreck = "fight";
			dialog.text = StringFromKey("GenQuests_Dialog_265");
			link.l1 = StringFromKey("GenQuests_Dialog_266");
			link.l1.go = "ShipWreck_16";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "ShipWreck_37":
			dialog.text = StringFromKey("GenQuests_Dialog_274", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_269", RandPhraseSimple(
								StringFromKey("GenQuests_Dialog_267"),
								StringFromKey("GenQuests_Dialog_268"))),
						StringFromKey("GenQuests_Dialog_272", RandPhraseSimple(
								StringFromKey("GenQuests_Dialog_270"),
								StringFromKey("GenQuests_Dialog_271"))),
						StringFromKey("GenQuests_Dialog_273")));
			link.l1 = StringFromKey("GenQuests_Dialog_275");
			link.l1.go = "ShipWreck_38";
		break;

		case "ShipWreck_38":
			chrDisableReloadToLocation = false;
			SetFunctionExitFromLocationCondition("ShipWreck_ExitFromTown", pchar.location, false);
			if (!CheckAttribute(pchar, "GenQuest.ShipWreck.CrazyRec"))
			{
				pchar.GenQuest.ShipWreck.CrazyRec = true;
				AddQuestRecord("ShipWrecked", "7");
			}
			DialogExit();
		break;

		case "ShipWreck_40":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			dialog.text = StringFromKey("GenQuests_Dialog_276");
			link.l1 = StringFromKey("GenQuests_Dialog_277");
			link.l1.go = "ShipWreck_41";
		break;

		case "ShipWreck_41":
			dialog.text = StringFromKey("GenQuests_Dialog_278");
			link.l1 = StringFromKey("GenQuests_Dialog_279");
			link.l1.go = "ShipWreck_42";
		break;

		case "ShipWreck_42":
			dialog.text = StringFromKey("GenQuests_Dialog_280", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_281");
			link.l1.go = "ShipWreck_43";
		break;

		case "ShipWreck_43":
			sld = CharacterFromID("ShipWreck_0");
			RemovePassenger(pchar, sld);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			if (!GetCharacterItem(pchar, "map_part1"))    GiveItem2Character(pchar, "map_part1");
			else                                        GiveItem2Character(pchar, "map_part2");
			AddQuestRecord("ShipWrecked", "9");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("ShipWrecked");
			AddSimpleRumourCity(
						StringFromKey("GenQuests_Dialog_289", LinkRandPhrase(
								StringFromKey("GenQuests_Dialog_284", RandPhraseSimple(
										StringFromKey("GenQuests_Dialog_282"),
										StringFromKey("GenQuests_Dialog_283"))),
								StringFromKey("GenQuests_Dialog_287", RandPhraseSimple(
										StringFromKey("GenQuests_Dialog_285"),
										StringFromKey("GenQuests_Dialog_286"))),
								StringFromKey("GenQuests_Dialog_288"))), pchar.location, 5, 3, "");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;

		case "ShipWreck_44":
			dialog.text = StringFromKey("GenQuests_Dialog_292", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_290"),
						StringFromKey("GenQuests_Dialog_291")));
			link.l1 = StringFromKey("GenQuests_Dialog_293", pchar, pchar.GenQuest.ShipWreck.Name);
			link.l1.go = "ShipWreck_45";
			link.l2 = StringFromKey("GenQuests_Dialog_294", pchar.GenQuest.ShipWreck.Name);
			link.l2.go = "ShipWreck_9";
		break;

		case "ShipWreck_45":
			dialog.text = StringFromKey("GenQuests_Dialog_295");
			link.l1 = StringFromKey("GenQuests_Dialog_296");
			link.l1.go = "ShipWreck_46";
		break;

		case "ShipWreck_46":
			ChangeCharacterReputation(pchar, 4);
			for (i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if (i == 0)
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.dialog.currentnode = "ShipWreck_13_again";
			}
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen снять таймер на 30 дней
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			if (CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny")) DeleteAttribute(pchar, "GenQuest.ShipWreck.Mutiny");
			SetFunctionExitFromLocationCondition("ShipWreck_LocationExit", pchar.location, false);
			DialogExit();
		break;

		case "ShipWreck_47":
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			GiveItem2Character(pchar, "indian15");
			AddQuestRecord("ShipWrecked", "15");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			CloseQuestHeader("ShipWrecked");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;

		case "ShipWreck_48":
			dialog.text = StringFromKey("GenQuests_Dialog_297");
			link.l1 = StringFromKey("GenQuests_Dialog_298");
			link.l1.go = "ShipWreck_49";
		break;

		case "ShipWreck_49":
			AddQuestRecord("ShipWrecked", "17");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("ShipWrecked");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;

		case "ShipWreck_50":
			dialog.text = StringFromKey("GenQuests_Dialog_299");
			link.l1 = StringFromKey("GenQuests_Dialog_300", pchar, pchar.GenQuest.ShipWreck.Name);
			link.l1.go = "ShipWreck_51";
		break;

		case "ShipWreck_51":
			dialog.text = StringFromKey("GenQuests_Dialog_301");
			link.l1 = StringFromKey("GenQuests_Dialog_302");
			link.l1.go = "ShipWreck_52";
		break;

		case "ShipWreck_52":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheckFunction(LAI_GROUP_BRDENEMY, "ShipWreck_afterCabinFight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "ShipWreck_53":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			pchar.quest.ShipWreck_ShipSink.over = "yes";
			dialog.text = StringFromKey("GenQuests_Dialog_303");
			link.l1 = StringFromKey("GenQuests_Dialog_304");
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_53_again";
			AddDialogExitQuestFunction("ShipWreck_SetShipNew");
		break;

		case "ShipWreck_53_again":
			dialog.text = StringFromKey("GenQuests_Dialog_305", GetFullName(pchar));
			link.l1 = StringFromKey("GenQuests_Dialog_306");
			link.l1.go = "ShipWreck_53_again1";
		break;

		case "ShipWreck_53_again1":
			dialog.text = StringFromKey("GenQuests_Dialog_307");
			link.l1 = StringFromKey("GenQuests_Dialog_308");
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_53_again";
		break;
		// Генератор "Потерпевшие кораблекрушение"

		// Генератор "Каторжане"
		case "Convict_0End":
			pchar.GenQuest.Convict = "close";
			chrDisableReloadToLocation = false;
			ChangeCharacterReputation(pchar, -1);
			AddDialogExitQuestFunction("Convict_ConvictsRunAway");
			DialogExit();
		break;

		case "Convict_Begin":
			switch (sti(pchar.GenQuest.Convict.var))
			{
				case 0:
					dialog.text = StringFromKey("GenQuests_Dialog_309");
					link.l1 = StringFromKey("GenQuests_Dialog_310");
					link.l1.go = "Convict_11";
				break;
				case 1:
					dialog.text = StringFromKey("GenQuests_Dialog_311");
					link.l1 = StringFromKey("GenQuests_Dialog_312");
					link.l1.go = "Convict_12";
				break;
				case 2:
					pchar.GenQuest.Convict.ToCity = FindColonyWithMayakExceptIsland(GetCharacterCurrentIslandId(pchar));
					pchar.GenQuest.Convict.Mayak = GetMayakByCityName(pchar.GenQuest.Convict.ToCity);
					dialog.text = StringFromKey("GenQuests_Dialog_313", XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen"));
					link.l1 = StringFromKey("GenQuests_Dialog_314");
					link.l1.go = "Convict_13";
				break;
			}
			link.l2 = StringFromKey("GenQuests_Dialog_318", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_315"),
						StringFromKey("GenQuests_Dialog_316"),
						StringFromKey("GenQuests_Dialog_317")));
			link.l2.go = "Convict_14";
			Convict_GetMineType();
		break;

		case "Convict_11":
			dialog.text = StringFromKey("GenQuests_Dialog_319", GetStrSmallRegister(XI_ConvertString("MineType" + pchar.GenQuest.Convict.MineType + "Dat")));
			if (GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l1 = StringFromKey("GenQuests_Dialog_320");
				link.l1.go = "Convict_11_1";
			}
			link.l2 = StringFromKey("GenQuests_Dialog_321");
			link.l2.go = "Convict_11_2";
		break;

		case "Convict_12":
			dialog.text = StringFromKey("GenQuests_Dialog_322", GetStrSmallRegister(XI_ConvertString("MineType" + pchar.GenQuest.Convict.MineType + "Dat")));
			if (sti(pchar.money) >= 3000)
			{
				link.l1 = StringFromKey("GenQuests_Dialog_323");
				link.l1.go = "Convict_12_1";
				link.l2 = StringFromKey("GenQuests_Dialog_324");
				link.l2.go = "Convict_12_2";
			}
			link.l3 = StringFromKey("GenQuests_Dialog_325");
			link.l3.go = "Convict_12_3";
		break;

		case "Convict_12_1":
			if (drand(1) == 0 && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				dialog.text = StringFromKey("GenQuests_Dialog_326");
				link.l1 = StringFromKey("GenQuests_Dialog_327");
				link.l1.go = "Convict_12_1_1";
			}
			else
			{
				dialog.text = StringFromKey("GenQuests_Dialog_328");
				link.l1 = StringFromKey("GenQuests_Dialog_329");
				link.l1.go = "Convict_12_1_2";
			}
			link.l2 = StringFromKey("GenQuests_Dialog_330");
			link.l2.go = "Convict_12_1_End"; // выход из локи с закрытием квеста
		break;

		case "Convict_12_1_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = StringFromKey("GenQuests_Dialog_331", GetName(NAMETYPE_NICK, pchar.GenQuest.Convict.PirateName, NAME_INS), pchar.GenQuest.Convict.ConvictQty);
			link.l1 = StringFromKey("GenQuests_Dialog_332", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation));
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";
		break;

		case "Convict_12_1_2":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			iTemp = drand(3);
			if (iTemp == 2)
			{
				dialog.text = StringFromKey("GenQuests_Dialog_335");
				link.l1 = StringFromKey("GenQuests_Dialog_336");
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			else if (iTemp == 3)
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = StringFromKey("GenQuests_Dialog_337", MerPrm.QuestGoodsIdx, MerPrm.ShipName, MerPrm.nation);
				link.l1 = StringFromKey("GenQuests_Dialog_338");
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}
			else
			{
				dialog.text = StringFromKey("GenQuests_Dialog_333");
				link.l1 = StringFromKey("GenQuests_Dialog_334");
			}
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_ConvictsRunAway");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2":
			dialog.text = StringFromKey("GenQuests_Dialog_339");
			link.l1 = StringFromKey("GenQuests_Dialog_340");
			link.l1.go = "Convict_12_2_1";
			link.l2 = StringFromKey("GenQuests_Dialog_341");
			link.l2.go = "Convict_12_2_2";
			link.l3 = StringFromKey("GenQuests_Dialog_342");
			link.l3.go = "Convict_12_2_3";
		break;

		case "Convict_12_2_1":
			addMoneyToCharacter(pchar, -300);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			dialog.text = StringFromKey("GenQuests_Dialog_343");
			link.l1 = StringFromKey("GenQuests_Dialog_344");
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_ConvictsRunAway");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_2":
			addMoneyToCharacter(pchar, -1000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 40);
			if (drand(1) == 0)
			{
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				dialog.text = StringFromKey("GenQuests_Dialog_345");
				link.l1 = StringFromKey("GenQuests_Dialog_346");
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 20);
			}
			else
			{
				dialog.text = StringFromKey("GenQuests_Dialog_347");
				link.l1 = StringFromKey("GenQuests_Dialog_348");
			}
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_ConvictsRunAway");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_3":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			if (drand(1) == 0)
			{
				dialog.text = StringFromKey("GenQuests_Dialog_349");
				link.l1 = StringFromKey("GenQuests_Dialog_350");
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			else
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = StringFromKey("GenQuests_Dialog_351", MerPrm.QuestGoodsIdx, MerPrm.ShipName, MerPrm.nation);
				link.l1 = StringFromKey("GenQuests_Dialog_352");
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_ConvictsRunAway");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_1_End":
			ChangeCharacterReputation(pchar, -2);
			OfficersReaction("bad");
			pchar.GenQuest.Convict = "close";
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_3":
			if (drand(1) == 0)
			{
				dialog.text = StringFromKey("GenQuests_Dialog_353");
				link.l1 = StringFromKey("GenQuests_Dialog_354");
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddItemLog(pchar, pchar.GenQuest.Convict.Item, "1", StringFromKey("InfoMessages_135", GetItemName(pchar.GenQuest.Convict.Item)), "Important_item");
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = StringFromKey("GenQuests_Dialog_355");
				link.l1 = StringFromKey("GenQuests_Dialog_356");
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "fight";
			}
		break;

		case "Convict_13":
			dialog.text = StringFromKey("GenQuests_Dialog_357");
			link.l1 = StringFromKey("GenQuests_Dialog_358");
			link.l1.go = "Convict_13_1";
			link.l2 = StringFromKey("GenQuests_Dialog_359");
			link.l2.go = "Convict_11_5";
		break;

		case "Convict_11_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = StringFromKey("GenQuests_Dialog_360", GetName(NAMETYPE_NICK, pchar.GenQuest.Convict.PirateName, NAME_INS), FindPeoplesString(sti(pchar.GenQuest.Convict.ConvictQty), "Acc"));
			link.l1 = StringFromKey("GenQuests_Dialog_361", pchar);
			link.l1.go = "Convict_11_3";
		break;

		case "Convict_11_2":
			dialog.text = StringFromKey("GenQuests_Dialog_362", GetStrSmallRegister(XI_ConvertString("MineType" + pchar.GenQuest.Convict.MineType + "Dat")));
			link.l1 = StringFromKey("GenQuests_Dialog_363", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Pre"));
			link.l1.go = "Convict_11_4";
			link.l2 = StringFromKey("GenQuests_Dialog_364", pchar);
			link.l2.go = "Convict_11_5";
		break;

		case "Convict_11_3":
			dialog.text = StringFromKey("GenQuests_Dialog_365", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_366", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation));
			link.l1.go = "Convict_11_6";
		break;

		case "Convict_11_4":
			dialog.text = StringFromKey("GenQuests_Dialog_367", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_368");
			link.l1.go = "Convict_11_7";
		break;

		case "Convict_11_5":
			if (makeint(pchar.reputation) < 11 || makeint(pchar.reputation) > 79) //макс. репутатция 90
			{
				dialog.text = StringFromKey("GenQuests_Dialog_369");
				link.l1 = StringFromKey("GenQuests_Dialog_370");
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				ChangeCharacterReputation(pchar, -2);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = StringFromKey("GenQuests_Dialog_371", pchar);
				link.l1 = StringFromKey("GenQuests_Dialog_372");
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "fight";
			}
		break;

		case "Convict_11_6":
			pchar.GenQuest.Convict = "ToShore";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "1");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandNameByCity(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty)));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen"));
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;
			AddDialogExitQuestFunction("Convict_ConvictsRunAway");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;

		case "Convict_11_7":
			pchar.GenQuest.Convict = "GetShip";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "2");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandNameByCity(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen"));
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_13_1":
			pchar.GenQuest.Convict.Sum = (sti(pchar.rank) + 10) * 100 + 1000;
			dialog.text = StringFromKey("GenQuests_Dialog_373", FindPeoplesString(sti(PChar.GenQuest.Convict.ConvictQty), "Acc"));
			link.l1 = StringFromKey("GenQuests_Dialog_374", FindMoneyString(sti(pchar.GenQuest.Convict.Sum)));
			link.l1.go = "Convict_13_2";
			if (GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = StringFromKey("GenQuests_Dialog_375");
				link.l2.go = "Convict_13_3";
			}
		break;

		case "Convict_13_2":
			dialog.text = StringFromKey("GenQuests_Dialog_376", FindMoneyString(sti(pchar.GenQuest.Convict.Sum)));
			link.l1 = StringFromKey("GenQuests_Dialog_377", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));
			link.l1.go = "Convict_13_4";
			pchar.GenQuest.Convict = "ToMayak";
			pchar.GenQuest.Convict.Sum = sti(pchar.GenQuest.Convict.Sum) * sti(pchar.GenQuest.Convict.ConvictQty);
		break;

		case "Convict_13_3":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = StringFromKey("GenQuests_Dialog_380", GetName(NAMETYPE_NICK, pchar.GenQuest.Convict.PirateName, NAME_INS), RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_378"),
						StringFromKey("GenQuests_Dialog_379")));
			link.l1 = StringFromKey("GenQuests_Dialog_381", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation));
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";
		break;

		case "Convict_13_4":
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "8");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandNameByCity(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen колво прописью
			AddQuestUserData("Convict", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen"));
			AddQuestUserData("Convict", "sSum", FindMoneyString(sti(pchar.GenQuest.Convict.Sum)));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_14":
			dialog.text = StringFromKey("GenQuests_Dialog_388", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_384", RandPhraseSimple(
								StringFromKey("GenQuests_Dialog_382", pchar),
								StringFromKey("GenQuests_Dialog_383"))),
						StringFromKey("GenQuests_Dialog_387", RandPhraseSimple(
								StringFromKey("GenQuests_Dialog_385"),
								StringFromKey("GenQuests_Dialog_386")))));
			link.l1 = StringFromKey("GenQuests_Dialog_392", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_389"),
						StringFromKey("GenQuests_Dialog_390"),
						StringFromKey("GenQuests_Dialog_391")));
			link.l1.go = "Convict_Fight";
			pchar.GenQuest.Convict = "fight";
		break;

		case "Convict_Fight":
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			iTemp = sti(PChar.GenQuest.Convict.ConvictQty);
			for (i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID("Convict_" + i);
				DeleteAttribute(rChar, "City");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ConvictGroup");
				LAi_SetImmortal(rChar, false);
			}
			LAi_group_SetRelation("ConvictGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("ConvictGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("ConvictGroup", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Convict_15":
			dialog.text = StringFromKey("GenQuests_Dialog_396", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_393"),
						StringFromKey("GenQuests_Dialog_394"),
						StringFromKey("GenQuests_Dialog_395")));
			if (Convict_CheckShipType(SHIP_TARTANE) || Convict_CheckShipType(SHIP_WAR_TARTANE))
			{
				link.l1 = StringFromKey("GenQuests_Dialog_397", pchar, pchar.GenQuest.Convict.ShipPrice, sti(pchar.GenQuest.Convict.ShipPrice));
				link.l1.go = "Convict_15_1";
			}
			link.l2 = StringFromKey("GenQuests_Dialog_398", pchar);
			link.l2.go = "Convict_15_2";
		break;

		case "Convict_15_1":
			switch (sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = StringFromKey("GenQuests_Dialog_399");
					link.l1 = StringFromKey("GenQuests_Dialog_400");
					link.l1.go = "Convict_15_1_1End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Commerce", 30);
					TakeNItems(pchar, "jewelry17", makeint(sti(pchar.GenQuest.Convict.ShipPrice) / 50));
				break;
				case 2:
					dialog.text = StringFromKey("GenQuests_Dialog_401");
					link.l1 = StringFromKey("GenQuests_Dialog_402");
					link.l1.go = "Convict_15_1_2End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Fortune", 30);
					AddItemLog(pchar, pchar.GenQuest.Convict.Item, "1", StringFromKey("InfoMessages_135", GetItemName(pchar.GenQuest.Convict.Item)), "Important_item");
				break;
				case 3:
					pchar.GenQuest.Convict = "FightInShore";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
					dialog.text = StringFromKey("GenQuests_Dialog_403");
					link.l1 = StringFromKey("GenQuests_Dialog_404");
					link.l1.go = "Convict_Fight";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Sneak", 30);
				break;
			}
		break;

		case "Convict_15_1_1End":
			AddQuestRecord("Convict", "4");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen"));
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;

		case "Convict_15_1_2End":
			AddQuestRecord("Convict", "5");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen"));
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;

		case "Convict_15_2":
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("Convict");
			for (i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
			{
				sld = CharacterFromID("Convict_" + i);
				sld.LifeDay = 0;
			}
			ChangeCharacterReputation(pchar, -2);
			LAi_group_Delete("ConvictGroup");
			DeleteAttribute(pchar, "GenQuest.Convict");
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_16":
			dialog.text = StringFromKey("GenQuests_Dialog_407", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_405"),
						StringFromKey("GenQuests_Dialog_406")));
			link.l1 = StringFromKey("GenQuests_Dialog_408");
			link.l1.go = "Convict_16_1";
			if (pchar.GenQuest.Convict == "ToMayak")
			{
				link.l2 = StringFromKey("GenQuests_Dialog_409");
				link.l2.go = "Convict_16_2";
			}
			if (pchar.GenQuest.Convict == "ToShore" && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l2 = StringFromKey("GenQuests_Dialog_410");
				link.l2.go = "Convict_16_2";
			}
		break;

		case "Convict_16_1":
			if (rand(1) == 0)
			{
				dialog.text = StringFromKey("GenQuests_Dialog_411", pchar);
				link.l1 = StringFromKey("GenQuests_Dialog_412");
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "ShoreFight";
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			else
			{
				dialog.text = StringFromKey("GenQuests_Dialog_413", pchar);
				link.l1 = StringFromKey("GenQuests_Dialog_414");
				link.l1.go = "Convict_16_3";
			}
		break;

		case "Convict_16_2":
			if (pchar.GenQuest.Convict == "ToShore")
			{
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterCrew(pchar, sti(pchar.GenQuest.Convict.ConvictQty));
				OfficersReaction("bad");
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "10");
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_ConvictsRunAway");
			}
			if (pchar.GenQuest.Convict == "ToMayak")
			{
				AddQuestRecord("Convict", "10");
				sld = characterFromId("Convict_0");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false);
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				SetFunctionLocationCondition("Convict_OnMayak", pchar.GenQuest.Convict.Mayak, true);
				locations[FindLocation(pchar.GenQuest.Convict.Mayak)].DisableEncounters = true;
				AddDialogExitQuestFunction("Convict_DialogDisable");
			}
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;

		case "Convict_16_3":
			ChangeCharacterReputation(pchar, -2);
			OfficersReaction("bad");
			pchar.GenQuest.Convict = "close";
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("Convict");
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			AddDialogExitQuestFunction("Convict_DialogDisable");
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_17":
			dialog.text = StringFromKey("GenQuests_Dialog_418", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_415", pchar),
						StringFromKey("GenQuests_Dialog_416", pchar),
						StringFromKey("GenQuests_Dialog_417")));
			link.l1 = StringFromKey("GenQuests_Dialog_422", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_419"),
						StringFromKey("GenQuests_Dialog_420"),
						StringFromKey("GenQuests_Dialog_421")));
			link.l1.go = "Convict_17_1";
		break;

		case "Convict_17_1":
			switch (sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = StringFromKey("GenQuests_Dialog_423");
					link.l1 = StringFromKey("GenQuests_Dialog_424");
					link.l1.go = "Convict_17_1_1End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Commerce", 80);
					TakeNItems(pchar, "jewelry5", makeint(sti(pchar.GenQuest.Convict.Sum) / 200));
				break;
				case 2:
					dialog.text = StringFromKey("GenQuests_Dialog_425");
					link.l1 = StringFromKey("GenQuests_Dialog_426");
					link.l1.go = "Convict_17_1_2End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Fortune", 80);
					AddItemLog(pchar, pchar.GenQuest.Convict.Item, "1", StringFromKey("InfoMessages_135", GetItemName(pchar.GenQuest.Convict.Item)), "Important_item");
				break;
				case 3:
					dialog.text = StringFromKey("GenQuests_Dialog_427");
					link.l1 = StringFromKey("GenQuests_Dialog_428");
					link.l1.go = "Convict_Fight";
					pchar.GenQuest.Convict = "MayakFight";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Sneak", 80);
				break;
			}
		break;

		case "Convict_17_1_1End":
			AddQuestRecord("Convict", "11");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));
			AddQuestUserData("Convict", "sSum", FindMoneyString(sti(pchar.GenQuest.Convict.Sum)));
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
			for (i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
			{
				sld = CharacterFromID("Convict_" + i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 15.0);
			}
		break;

		case "Convict_17_1_2End":
			AddQuestRecord("Convict", "12");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
			for (i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
			{
				sld = CharacterFromID("Convict_" + i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 15.0);
			}
		break;
		// <-- Генератор "Каторжане"

		// Генератор "Повод для спешки" -->
		// Встреча с ОЗГ на берегу
		case "ReasonToFast_Hunter1":
			dialog.text = StringFromKey("GenQuests_Dialog_429", GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
			link.l1 = StringFromKey("GenQuests_Dialog_430", GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
			link.l1.go = "ReasonToFast_Hunter4";
		break;

		case "ReasonToFast_Hunter2":
			dialog.text = StringFromKey("GenQuests_Dialog_431", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_432");
			link.l1.go = "ReasonToFast_Hunter6";
		break;

		case "ReasonToFast_Hunter3":
			dialog.text = StringFromKey("GenQuests_Dialog_433");
			link.l1 = StringFromKey("GenQuests_Dialog_434");
			link.l1.go = "ReasonToFast_Fight";
		break;

		case "ReasonToFast_Hunter4":
			dialog.text = StringFromKey("GenQuests_Dialog_435");
			link.l1 = StringFromKey("GenQuests_Dialog_436", GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT));
			link.l1.go = "ReasonToFast_Hunter5";
			AddQuestRecord("ReasonToFast", "5");
			AddQuestUserData("ReasonToFast", "sName", GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
		break;

		case "ReasonToFast_Hunter5":
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_HunterGoOut");
		break;

		case "ReasonToFast_Hunter6":
			pchar.questTemp.ReasonToFast = "MeetHunterFail";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_PatrolAngry");
		break;

		case "ReasonToFast_Fight":
			LAi_SetPlayerType(pchar);
			pchar.questTemp.ReasonToFast = "PatrolAngry";
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY);
			pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять
			sTemp = "Patrol" + pchar.questTemp.ReasonToFast.LocIdx + "_";
			sGroup = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);
			iTemp = sti(pchar.questTemp.ReasonToFast.PatrolNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("ReasonToFast_Hunter");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for (i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors");
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// бой с кэпом пиратского корабля
		case "ReasonToFast_FightCap":
			dialog.text = StringFromKey("GenQuests_Dialog_437", pchar, GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
			link.l1 = StringFromKey("GenQuests_Dialog_438");
			link.l1.go = "ReasonToFast_FightCap_1";
		break;

		case "ReasonToFast_FightCap_1":
			dialog.text = StringFromKey("GenQuests_Dialog_439");
			link.l1 = StringFromKey("GenQuests_Dialog_440");
			link.l1.go = "ReasonToFast_FightCap_2";
		break;

		case "ReasonToFast_FightCap_2":
			dialog.text = StringFromKey("GenQuests_Dialog_441");
			link.l1 = StringFromKey("GenQuests_Dialog_442", pchar);
			link.l1.go = "ReasonToFast_FightCap_Last";
		break;

		case "ReasonToFast_FightCap_Last":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// встреча с лакеем в резиденции
		case "ReasonToFast_Lakey":
			dialog.text = StringFromKey("GenQuests_Dialog_443", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("GenQuests_Dialog_444");
			link.l1.go = "ReasonToFast_Lakey1";
			link.l2 = StringFromKey("GenQuests_Dialog_445", pchar);
			link.l2.go = "ReasonToFast_Lakey2";
			link.l3 = StringFromKey("GenQuests_Dialog_446");
			link.l3.go = "ReasonToFast_Lakey3";
			pchar.questTemp.ReasonToFast = "MeetLakey";
			pchar.questTemp.ReasonToFast.SpeakOther = true;
		break;

		case "ReasonToFast_Lakey1":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = StringFromKey("GenQuests_Dialog_447");
			link.l1 = StringFromKey("GenQuests_Dialog_448");
			link.l1.go = "ReasonToFast_Lakey11";
		break;

		case "ReasonToFast_Lakey11":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = StringFromKey("GenQuests_Dialog_449");
			link.l1 = StringFromKey("GenQuests_Dialog_450");
			link.l1.go = "exit";
			bDisableFastReload = false;
		break;

		case "ReasonToFast_Lakey2":
			dialog.text = StringFromKey("GenQuests_Dialog_451", pchar.questTemp.ReasonToFast.password);
			Link.l1.edit = 1;
			link.l1 = "";
			link.l1.go = "ReasonToFast_Lakey21";
		break;

		case "ReasonToFast_Lakey3":
			dialog.text = StringFromKey("GenQuests_Dialog_452");
			link.l1 = StringFromKey("GenQuests_Dialog_453");
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;
		break;

		case "ReasonToFast_Lakey21":
			if (GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipName) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = StringFromKey("GenQuests_Dialog_454");
				link.l1 = StringFromKey("GenQuests_Dialog_455");
				link.l1.go = "ReasonToFast_Lakey_exit";
				TakeNItems(pchar, "incas_collection", sti(pchar.questTemp.ReasonToFast.p8));
				TakeNItems(pchar, "Chest", sti(pchar.questTemp.ReasonToFast.p7));
				pchar.questTemp.ReasonToFast = "LakeyExitSuccess";
				bDisableFastReload = true;
				//chrDisableReloadToLocation = true;			
			}
			else
			{
				dialog.text = StringFromKey("GenQuests_Dialog_456");
				link.l1 = StringFromKey("GenQuests_Dialog_457");
				link.l1.go = "ReasonToFast_Lakey_exit";
				pchar.questTemp.ReasonToFast = "LakeyExitFail";
				bDisableFastReload = false;
			}
		break;

		case "ReasonToFast_Lakey_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.ReasonToFast_ClearLakey.over = "yes"; //снимаем таймер
			ReasonToFast_SetHunterCoastal();
			AddDialogExitQuest("ReasonToFast_LakeyGoOut");
		break;

		case "Man_FackYou":
			dialog.text = StringFromKey("GenQuests_Dialog_461", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_458", pchar),
						StringFromKey("GenQuests_Dialog_459", pchar),
						StringFromKey("GenQuests_Dialog_460", pchar)));
			link.l1 = StringFromKey("GenQuests_Dialog_462");
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;
		break;
		// Генератор "Повод для спешки" <--

		// ситуации с капитаном захваченного корабля
		// взрыв на корабле
		case "ShipSituation11": // пираты или ДУ
			dialog.text = StringFromKey("GenQuests_Dialog_465", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_463", pchar),
						StringFromKey("GenQuests_Dialog_464")));
			link.l1 = StringFromKey("GenQuests_Dialog_468", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_466"),
						StringFromKey("GenQuests_Dialog_467")));
			link.l1.go = "ShipSituation12";
		break;

		case "ShipSituation12":
			dialog.text = StringFromKey("GenQuests_Dialog_471", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_469"),
						StringFromKey("GenQuests_Dialog_470", pchar)));
			link.l1 = StringFromKey("GenQuests_Dialog_474", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_472"),
						StringFromKey("GenQuests_Dialog_473")));
			link.l1.go = "ShipSituation_End";
		break;

		case "ShipSituation21": // военный корабль (не флагман)
			dialog.text = StringFromKey("GenQuests_Dialog_475", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_478", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_476"),
						StringFromKey("GenQuests_Dialog_477")));
			link.l1.go = "ShipSituation22";
		break;

		case "ShipSituation22":
			dialog.text = StringFromKey("GenQuests_Dialog_481", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_479"),
						StringFromKey("GenQuests_Dialog_480")));
			link.l1 = StringFromKey("GenQuests_Dialog_484", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_482"),
						StringFromKey("GenQuests_Dialog_483")));
			link.l1.go = "ShipSituation_End";
		break;

		case "ShipSituation31": // ОЗГ
			dialog.text = StringFromKey("GenQuests_Dialog_487", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_485", pchar),
						StringFromKey("GenQuests_Dialog_486", pchar)));
			link.l1 = StringFromKey("GenQuests_Dialog_490", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_488"),
						StringFromKey("GenQuests_Dialog_489")));
			link.l1.go = "ShipSituation32";
		break;

		case "ShipSituation32":
			dialog.text = StringFromKey("GenQuests_Dialog_493", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_491"),
						StringFromKey("GenQuests_Dialog_492", pchar)));
			link.l1 = StringFromKey("GenQuests_Dialog_496", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_494"),
						StringFromKey("GenQuests_Dialog_495")));
			link.l1.go = "ShipSituation_End";
		break;

		case "ShipSituation_End":
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			DialogExit();
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			NPChar.LifeDay = 0;
			LAi_LockFightMode(pchar, false);
			Log_Info(XI_ConvertString("Ship can explode"));
			pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4;
			pchar.GenQuest.ShipSituation.Explosion.CapId = NPChar.CaptanId;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;

		// эпидемия
		case "ShipEpidemy1":
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = StringFromKey("GenQuests_Dialog_499", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_497"),
						StringFromKey("GenQuests_Dialog_498")));
			link.l1 = StringFromKey("GenQuests_Dialog_503", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_500"),
						StringFromKey("GenQuests_Dialog_501", pchar),
						StringFromKey("GenQuests_Dialog_502")));
			link.l1.go = "ShipEpidemy2";
		break;

		case "ShipEpidemy2":
			dialog.text = StringFromKey("GenQuests_Dialog_504");
			link.l1 = StringFromKey("GenQuests_Dialog_507", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_505"),
						StringFromKey("GenQuests_Dialog_506")));
			link.l1.go = "ShipEpidemy3";
		break;

		case "ShipEpidemy3":
			dialog.text = StringFromKey("GenQuests_Dialog_508");
			link.l1 = StringFromKey("GenQuests_Dialog_511", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_509"),
						StringFromKey("GenQuests_Dialog_510", pchar)));
			link.l1.go = "ShipEpidemy31";
			link.l2 = StringFromKey("GenQuests_Dialog_514", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_512"),
						StringFromKey("GenQuests_Dialog_513")));
			link.l2.go = "ShipEpidemy32";
			pchar.GenQuest.ShipSituation.Epidemy.CapId = NPChar.CaptanId;
			pchar.GenQuest.ShipSituation.Epidemy = ShipSituation_4;
		break;

		case "ShipEpidemy31":
			pchar.GenQuest.QuestAboardCabinDialogIdx = NPChar.index;
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Died"; // вражеский кэп на волосок от смерти от переизбытка стали и свинца в организме
			LAi_LockFightMode(pchar, false);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "ShipEpidemy32":
			DialogExit();
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			LAi_LockFightMode(pchar, false);
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Live"; // вражеский кэп остался в живых
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		// ситуации с капитаном захваченного корабля

		// Генератор "Девица в джунглях"
		case "EncGirl_Lover":
			dialog.text = StringFromKey("GenQuests_Dialog_515");
			link.l1 = StringFromKey("GenQuests_Dialog_516", pchar.GenQuest.EncGirl.sLoverId);
			link.l1.go = "EncGirl_Lover1";
		break;

		case "EncGirl_Lover1":
			dialog.text = StringFromKey("GenQuests_Dialog_517");
			link.l1 = StringFromKey("GenQuests_Dialog_518", pchar, pchar.GenQuest.EncGirl.name);
			link.l1.go = "EncGirl_Lover2";
		break;

		case "EncGirl_Lover2":
			dialog.text = StringFromKey("GenQuests_Dialog_519");
			link.l1 = StringFromKey("GenQuests_Dialog_520");
			link.l1.go = "EncGirl_Lover3";
		break;

		case "EncGirl_Lover3":
			pchar.GenQuest.EncGirl.LoverCity = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			pchar.GenQuest.EncGirl.LoverIsland = GetIslandNameByCity(pchar.GenQuest.EncGirl.LoverCity);
			dialog.text = StringFromKey("GenQuests_Dialog_521", XI_ConvertString(pchar.GenQuest.EncGirl.LoverIsland + "Acc"), XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.LoverCity));
			link.l1 = StringFromKey("GenQuests_Dialog_522");
			link.l1.go = "EncGirl_Lover4";
			link.l2 = StringFromKey("GenQuests_Dialog_523");
			link.l2.go = "EncGirl_Lover5";
		break;

		case "EncGirl_Lover4":
			npchar.lifeDay = 0;
			AddDialogExitQuestFunction("EncGirl_LoverExit");
			DialogExit();
		break;

		case "EncGirl_Lover5":
			AddDialogExitQuestFunction("EncGirl_ToLoverParents");
			DialogExit();
		break;

		case "EncGirl_Lover6":
			AddSimpleRumourCityTip(
						StringFromKey("GenQuests_Dialog_526", RandPhraseSimple(
								StringFromKey("GenQuests_Dialog_524", pchar.GenQuest.EncGirl.name),
								StringFromKey("GenQuests_Dialog_525", pchar.GenQuest.EncGirl.name))), pchar.GenQuest.EncGirl.LoverCity, 3, 2, "citizen,habitue", "");
			dialog.text = StringFromKey("GenQuests_Dialog_527");
			link.l1 = StringFromKey("GenQuests_Dialog_528");
			link.l1.go = "EncGirl_Lover7";
		break;

		case "EncGirl_Lover7":
			switch (rand(4))
			{
				case 0:
					sTemp = StringFromKey("GenQuests_Dialog_529");
					pchar.GenQuest.EncGirl.LoverFather = "store_keeper";
				break;
				case 1:
					sTemp = StringFromKey("GenQuests_Dialog_530");
					pchar.GenQuest.EncGirl.LoverFather = "shipyard_keeper";
				break;
				case 2:
					sTemp = StringFromKey("GenQuests_Dialog_531");
					pchar.GenQuest.EncGirl.LoverFather = "portman_keeper";
				break;
				case 3:
					sTemp = StringFromKey("GenQuests_Dialog_532");
					pchar.GenQuest.EncGirl.LoverFather = "tavern_keeper";
				break;
				case 4:
					sTemp = StringFromKey("GenQuests_Dialog_533");
					pchar.GenQuest.EncGirl.LoverFather = "usurer_keeper";
				break;
			}
			pchar.GenQuest.EncGirl.FatherLoc = sTemp;
			dialog.text = StringFromKey("GenQuests_Dialog_534", sTemp);
			link.l1 = StringFromKey("GenQuests_Dialog_535");
			link.l1.go = "EncGirl_Lover8";
		break;

		case "EncGirl_Lover8":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			npchar.lifeday = 0;
			AddQuestRecord("JungleGirl", "16");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("JungleGirl", "sText", pchar.GenQuest.EncGirl.FatherLoc);
			if ((GetSummonSkillFromName(pchar, SKILL_FORTUNE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)) < 175)
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 0; // папочка жениха счастлив за сына
			}
			else
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 1; // папочка жениха разъярен за то что сын притащил в дом шалаву
			}
			chrDisableReloadToLocation = false;
			pchar.GenQuest.EncGirl = "toLoverFather";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.function = "EncGirl_GenQuest_GetLoverFather";
			DialogExit();
		break;
		// Генератор "Девица в джунглях"

		// Генератор "Поручение капитана"
		case "CaptainComission_1":
			dialog.text = StringFromKey("GenQuests_Dialog_538", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_536"),
						StringFromKey("GenQuests_Dialog_537")));
			link.l1 = StringFromKey("GenQuests_Dialog_542", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_539"),
						StringFromKey("GenQuests_Dialog_540"),
						StringFromKey("GenQuests_Dialog_541")));
			link.l1.go = "CaptainComission_2";
		break;

		case "CaptainComission_2":
			dialog.text = StringFromKey("GenQuests_Dialog_543");
			link.l1 = StringFromKey("GenQuests_Dialog_546", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_544"),
						StringFromKey("GenQuests_Dialog_545")));
			link.l1.go = "CaptainComission_21";
			link.l2 = StringFromKey("GenQuests_Dialog_547");
			link.l2.go = "CaptainComission_22";
		break;

		case "CaptainComission_21":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterReputation(pchar, -2);
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CaptainComission_22":
			if (rand(1)) // "Выкуп"
			{
				CaptainComission_Init(NPChar);
				dialog.text = StringFromKey("GenQuests_Dialog_548", pchar.GenQuest.CaptainComission.Name, XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
				link.l1 = StringFromKey("GenQuests_Dialog_551", RandPhraseSimple(
							StringFromKey("GenQuests_Dialog_549"),
							StringFromKey("GenQuests_Dialog_550")));
				link.l1.go = "CaptainComission_22_1";
				link.l2 = StringFromKey("GenQuests_Dialog_552");
				link.l2.go = "CaptainComission_22_2";
			}
			else // "операция 'Галеон'"
			{
				CaptainComission_GaleonInit(NPChar);
				dialog.text = StringFromKey("GenQuests_Dialog_553", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")), pchar.GenQuest.CaptainComission.ShipTypeName, pchar.GenQuest.CaptainComission.Name, XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Pre"), GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name") + "Acc")), pchar.GenQuest.CaptainComission.VictimShipName, GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name"))), XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"), XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen"));
				link.l1 = StringFromKey("GenQuests_Dialog_556", RandPhraseSimple(
							StringFromKey("GenQuests_Dialog_554"),
							StringFromKey("GenQuests_Dialog_555")));
				link.l1.go = "CaptainComission_300";
			}
		break;

		case "CaptainComission_22_1":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar);
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();
		break;

		case "CaptainComission_22_2":
			dialog.text = StringFromKey("GenQuests_Dialog_557");
			link.l1 = StringFromKey("GenQuests_Dialog_558");
			link.l1.go = "CaptainComission_22_3";
		break;

		case "CaptainComission_22_3":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterReputation(pchar, -3);
			pchar.GenQuest.CaptainComission = "Begin_2";
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CaptainComission_3":
			dialog.text = StringFromKey("GenQuests_Dialog_562", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_559", GetAddress_Form(pchar)),
						StringFromKey("GenQuests_Dialog_560"),
						StringFromKey("GenQuests_Dialog_561")));
			if (pchar.GenQuest.CaptainComission == "Begin_1" || pchar.GenQuest.CaptainComission == "Begin_2") // лесник - доп.проверка если есть квест. для перехода .
			{
				link.l1 = StringFromKey("GenQuests_Dialog_563", pchar.GenQuest.CaptainComission.Name, pchar.GenQuest.CaptainComission.CapName);
				link.l1.go = "CaptainComission_4";
				break;
			}
			link.l2 = StringFromKey("GenQuests_Dialog_564");
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_3"; // лесник - переход чтобы не вызывал баг при повтороном обращении
		break;

		case "CaptainComission_4":
			dialog.text = StringFromKey("GenQuests_Dialog_565", pchar.GenQuest.CaptainComission.CapName);
			link.l1 = StringFromKey("GenQuests_Dialog_566");
			link.l1.go = "CaptainComission_5";
		break;

		case "CaptainComission_5":
			dialog.text = StringFromKey("GenQuests_Dialog_567");
			link.l1 = StringFromKey("GenQuests_Dialog_568");
			link.l1.go = "CaptainComission_6";
		break;

		case "CaptainComission_6":
			CaptainComission_GetPirateIsland();
			CaptainComission_GetFamilyType();
			if (pchar.GenQuest.CaptainComission == "Begin_1")
			{
				dialog.text = StringFromKey("GenQuests_Dialog_569", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Gen"), GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")), pchar.GenQuest.CaptainComission.SlaveName);
				link.l1 = StringFromKey("GenQuests_Dialog_570");
				link.l1.go = "CaptainComission_6_1";
				link.l2 = StringFromKey("GenQuests_Dialog_571");
				link.l2.go = "CaptainComission_6_2";
			}
			if (pchar.GenQuest.CaptainComission == "Begin_2")
			{
				dialog.text = StringFromKey("GenQuests_Dialog_572");
				link.l1 = StringFromKey("GenQuests_Dialog_573");
				link.l1.go = "CaptainComission_6_3";
				pchar.GenQuest.CaptainComission.CanFindChest = true;
			}
		break;

		case "CaptainComission_6_1":
			dialog.text = StringFromKey("GenQuests_Dialog_574");
			link.l1 = StringFromKey("GenQuests_Dialog_575");
			link.l1.go = "CaptainComission_6_1End";
		break;

		case "CaptainComission_6_2":
			dialog.text = StringFromKey("GenQuests_Dialog_576", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_ACC));
			link.l1 = StringFromKey("GenQuests_Dialog_577");
			link.l1.go = "CaptainComission_6_21";
		break;

		case "CaptainComission_6_3":
			dialog.text = StringFromKey("GenQuests_Dialog_578", pchar, pchar.GenQuest.CaptainComission.CapName, ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT), XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"), pchar.GenQuest.CaptainComission.SlaveName);
			link.l1 = StringFromKey("GenQuests_Dialog_579");
			link.l1.go = "CaptainComission_6_31";
		break;

		case "CaptainComission_6_1End":
			AddQuestRecord("CaptainComission1", "3");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCharType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			CloseQuestHeader("CaptainComission1");
			sld = CharacterFromID("CapComission_1"); // удаление. лесник.
			sld.LifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			ChangeCharacterReputation(pchar, -2);
			DialogExit();
		break;

		case "CaptainComission_6_21":
			dialog.text = StringFromKey("GenQuests_Dialog_580", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"), GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			link.l1 = StringFromKey("GenQuests_Dialog_581", pchar);
			link.l1.go = "CaptainComission_6_22";
			link.l2 = StringFromKey("GenQuests_Dialog_582");
			link.l2.go = "CaptainComission_6_1";
		break;

		case "CaptainComission_6_22":
			dialog.text = StringFromKey("GenQuests_Dialog_583", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			link.l1 = StringFromKey("GenQuests_Dialog_584");
			link.l1.go = "CaptainComission_6_22End";
		break;

		case "CaptainComission_6_22End":
			AddQuestRecord("CaptainComission1", "4");
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sFamilyType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			AddQuestUserData("CaptainComission1", "sSlaveName", pchar.GenQuest.CaptainComission.SlaveName);
			addMoneyToCharacter(pchar, 150000);
			pchar.GenQuest.CaptainComission = "Begin_11";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "goodSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "CaptainComission_6_31":
			dialog.text = StringFromKey("GenQuests_Dialog_585", pchar.GenQuest.CaptainComission.SlaveName);
			link.l1 = StringFromKey("GenQuests_Dialog_586");
			link.l1.go = "CaptainComission_6_32";
		break;

		case "CaptainComission_6_32":
			dialog.text = StringFromKey("GenQuests_Dialog_587", pchar.GenQuest.CaptainComission.SlaveName);
			link.l1 = StringFromKey("GenQuests_Dialog_588");
			link.l1.go = "CaptainComission_6_33";
		break;

		case "CaptainComission_6_33":
			dialog.text = StringFromKey("GenQuests_Dialog_589");
			link.l1 = StringFromKey("GenQuests_Dialog_590");
			link.l1.go = "CaptainComission_6_33End";
		break;

		case "CaptainComission_6_33End":
			AddQuestRecord("CaptainComission1", "5");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "ла"));
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sSlaveName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			pchar.GenQuest.CaptainComission = "Begin_22";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "badSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "CaptainComission_7":
			if (pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
			{
				if (pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = StringFromKey("GenQuests_Dialog_594", LinkRandPhrase(
								StringFromKey("GenQuests_Dialog_591", GetFullName(pchar)),
								StringFromKey("GenQuests_Dialog_592"),
								StringFromKey("GenQuests_Dialog_593")));
					if (makeint(pchar.money) >= 150000)
					{
						link.l1 = StringFromKey("GenQuests_Dialog_595", pchar);
						link.l1.go = "CaptainComission_7_1";
					}
					link.l2 = StringFromKey("GenQuests_Dialog_596");
					link.l2.go = "CaptainComission_7_2";
				}
				if (pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
				{
					dialog.text = StringFromKey("GenQuests_Dialog_600", LinkRandPhrase(
								StringFromKey("GenQuests_Dialog_597", GetFullName(pchar)),
								StringFromKey("GenQuests_Dialog_598"),
								StringFromKey("GenQuests_Dialog_599")));
					link.l1 = StringFromKey("GenQuests_Dialog_601");
					link.l1.go = "CaptainComission_7_3";
					link.l2 = StringFromKey("GenQuests_Dialog_602");
					link.l2.go = "CaptainComission_7_4";
				}
			}
			if (pchar.GenQuest.CaptainComission.GetSlave == "GetSlave")
			{
				if (pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = StringFromKey("GenQuests_Dialog_606", LinkRandPhrase(
								StringFromKey("GenQuests_Dialog_603", GetFullName(pchar)),
								StringFromKey("GenQuests_Dialog_604"),
								StringFromKey("GenQuests_Dialog_605")));
					link.l1 = StringFromKey("GenQuests_Dialog_607", pchar.GenQuest.CaptainComission.SlaveName);
					link.l1.go = "CaptainComission_30";
				}
				else
				{
					dialog.text = StringFromKey("GenQuests_Dialog_611", LinkRandPhrase(
								StringFromKey("GenQuests_Dialog_608", GetFullName(pchar)),
								StringFromKey("GenQuests_Dialog_609"),
								StringFromKey("GenQuests_Dialog_610")));
					link.l1 = StringFromKey("GenQuests_Dialog_612", pchar);
					link.l1.go = "CaptainComission_32";
				}
			}
			if (pchar.GenQuest.CaptainComission.GetSlave == "SlaveDied")
			{
				if (pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = StringFromKey("GenQuests_Dialog_616", LinkRandPhrase(
								StringFromKey("GenQuests_Dialog_613", GetFullName(pchar)),
								StringFromKey("GenQuests_Dialog_614"),
								StringFromKey("GenQuests_Dialog_615")));
					link.l1 = StringFromKey("GenQuests_Dialog_617", pchar, pchar.GenQuest.CaptainComission.Name);
					link.l1.go = "CaptainComission_50";
				}
				else
				{
					dialog.text = StringFromKey("GenQuests_Dialog_621", LinkRandPhrase(
								StringFromKey("GenQuests_Dialog_618", GetFullName(pchar)),
								StringFromKey("GenQuests_Dialog_619"),
								StringFromKey("GenQuests_Dialog_620")));
					link.l1 = StringFromKey("GenQuests_Dialog_622");
					link.l1.go = "CaptainComission_60";
				}
			}
		break;

		case "CaptainComission_30":
			dialog.text = StringFromKey("GenQuests_Dialog_623");
			link.l1 = StringFromKey("GenQuests_Dialog_624");
			link.l1.go = "CaptainComission_30_1";
			if (CheckAttribute(pchar, "GenQuest.CaptainComission.SlaveAddMoney"))
			{
				link.l2 = StringFromKey("GenQuests_Dialog_625");
				link.l2.go = "CaptainComission_31";
			}
		break;

		case "CaptainComission_30_1":
			AddItemLog(pchar, "chest", "3", StringFromKey("InfoMessages_134"), "Important_item");
			// evganat - энциклопедия
			if (CheckRandomPage("questcaptain", "comission", 1))
			{
				GetPage(GetRandomTome(), 5);
			}
			AddQuestRecord("CaptainComission1", "14");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			ChangeCharacterReputation(pchar, 2);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_31":
			AddItemLog(pchar, "chest", "2", StringFromKey("InfoMessages_134"), "Important_item");
			dialog.text = StringFromKey("GenQuests_Dialog_626");
			link.l1 = StringFromKey("GenQuests_Dialog_627");
			link.l1.go = "CaptainComission_31_1";
		break;

		case "CaptainComission_31_1":
			dialog.text = StringFromKey("GenQuests_Dialog_628");
			link.l1 = StringFromKey("GenQuests_Dialog_629");
			link.l1.go = "CaptainComission_31_1End";
		break;

		case "CaptainComission_31_1End":
			AddQuestRecord("CaptainComission1", "15");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_32":
			dialog.text = StringFromKey("GenQuests_Dialog_630");
			link.l1 = StringFromKey("GenQuests_Dialog_631");
			link.l1.go = "CaptainComission_32_1";
		break;

		case "CaptainComission_32_1":
			GetSlaveSpeciality();
			dialog.text = StringFromKey("GenQuests_Dialog_632", NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)), pchar.GenQuest.CaptainComission.SlaveSpeciality);
			link.l1 = StringFromKey("GenQuests_Dialog_633", pchar);
			link.l1.go = "CaptainComission_32_2";
		break;

		case "CaptainComission_32_2":
			dialog.text = StringFromKey("GenQuests_Dialog_634", pchar, NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)));
			link.l1 = StringFromKey("GenQuests_Dialog_635");
			link.l1.go = "CaptainComission_32_2End";
		break;

		case "CaptainComission_32_2End":
		// evganat - энциклопедия
			if (CheckRandomPage("questcaptain", "comission", 2))
			{
				GetPage(GetRandomTome(), 5);
			}
			AddQuestRecord("CaptainComission1", "16");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission1", "sSpeciality", pchar.GenQuest.CaptainComission.SlaveSpeciality);
			AddQuestUserData("CaptainComission1", "sNation", NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)));
			CloseQuestHeader("CaptainComission1");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 15);
			sTemp = pchar.GenQuest.CaptainComission.Item;
			AddItemLog(pchar, sTemp + ",jewelry5", "1,100", StringFromKey("InfoMessages_170") + " " + XI_ConvertString("NationLegendText_4") + " '" + GetItemName(sTemp) + "'", "Important_item");
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_7_1":
			dialog.text = StringFromKey("GenQuests_Dialog_636");
			link.l1 = StringFromKey("GenQuests_Dialog_637");
			link.l1.go = "CaptainComission_7_1End";
		break;

		case "CaptainComission_7_1End":
			AddQuestRecord("CaptainComission1", "8");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			rChar = characterFromId("CapComission_1");
			rChar.lifeDay = 0;
			pchar.quest.CaptainComission1_30DaysIsLeft.over = "yes";
			addMoneyToCharacter(pchar, -150000);
			ChangeCharacterReputation(pchar, -4);
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_7_2":
			dialog.text = StringFromKey("GenQuests_Dialog_638");
			link.l1 = StringFromKey("GenQuests_Dialog_639");
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;

		case "CaptainComission_7_3":
			dialog.text = StringFromKey("GenQuests_Dialog_640");
			link.l1 = StringFromKey("GenQuests_Dialog_641");
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;

		case "CaptainComission_7_4":
			dialog.text = StringFromKey("GenQuests_Dialog_642", pchar, pchar.GenQuest.CaptainComission.CapName);
			link.l1 = StringFromKey("GenQuests_Dialog_643");
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;

		// диалоги с рабом
		case "CaptainComission_20":
			CaptainComission_ReturnPlantatorDialogNode();
			if (pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = StringFromKey("GenQuests_Dialog_644");
				link.l1 = StringFromKey("GenQuests_Dialog_645", pchar.GenQuest.CaptainComission.Name, XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
				link.l1.go = "CaptainComission_201";
			}
			else
			{
				dialog.text = StringFromKey("GenQuests_Dialog_646");
				link.l1 = StringFromKey("GenQuests_Dialog_647");
				link.l1.go = "CaptainComission_202";
			}
		break;

		case "CaptainComission_201":
			dialog.text = StringFromKey("GenQuests_Dialog_648");
			link.l1 = StringFromKey("GenQuests_Dialog_649");
			link.l1.go = "CaptainComission_201_1";
		break;

		case "CaptainComission_201_1":
			AddQuestRecord("CaptainComission1", "11");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", FindMoneyString(sti(pchar.GenQuest.CaptainComission.SlaveMoney)));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			DialogExit();
		break;

		case "CaptainComission_202":
			dialog.text = StringFromKey("GenQuests_Dialog_650");
			link.l1 = StringFromKey("GenQuests_Dialog_651", pchar);
			link.l1.go = "CaptainComission_202_1";
		break;

		case "CaptainComission_202_1":
			dialog.text = StringFromKey("GenQuests_Dialog_652", NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation)));
			link.l1 = StringFromKey("GenQuests_Dialog_653", pchar.GenQuest.CaptainComission.Name, XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			link.l1.go = "CaptainComission_202_2";
		break;

		case "CaptainComission_202_2":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));    // mitrokosta
			if (iNation == -1) iNation(rand(3));
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			dialog.text = StringFromKey("GenQuests_Dialog_654", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Gen"));
			link.l1 = StringFromKey("GenQuests_Dialog_655");
			link.l1.go = "CaptainComission_202_3";
			link.l2 = StringFromKey("GenQuests_Dialog_656");
			link.l2.go = "CaptainComission_203";
		break;

		case "CaptainComission_202_3":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			rChar = characterFromId("CapComission_1");
			ChangeCharacterAddress(rChar, "none", "");
			rChar.lifeDay = 0;
			AddQuestRecord("CaptainComission1", "12");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("ся", "ась"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", FindMoneyString(sti(pchar.GenQuest.CaptainComission.SlaveMoney)));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Gen"));
			pchar.quest.CapComission_DeliveSlave.win_condition.l1 = "location";
			pchar.quest.CapComission_DeliveSlave.win_condition.l1.location = pchar.GenQuest.CaptainComission.SlaveCity + "_tavern";
			pchar.quest.CapComission_DeliveSlave.function = "CaptainComission_DeliveSlave";
			LAi_SetActorType(NPChar);
			LAi_ActorFollow(NPChar, PChar, "OpenTheDoors", -1.0); //лесник  идем за ГГ
			DialogExit();
		break;

		case "CaptainComission_203":
			dialog.text = StringFromKey("GenQuests_Dialog_657");
			link.l1 = StringFromKey("GenQuests_Dialog_658");
			link.l1.go = "CaptainComission_203_1";
		break;

		case "CaptainComission_203_1":
			AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", FindMoneyString(sti(pchar.GenQuest.CaptainComission.SlaveMoney)));
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0); //лесник - провожаем на корабль типа..
			DialogExit();
		break;

		case "CaptainComission_50":
			dialog.text = StringFromKey("GenQuests_Dialog_659");
			link.l1 = StringFromKey("GenQuests_Dialog_660");
			link.l1.go = "CaptainComission_51";
		break;

		case "CaptainComission_51":
			ChangeCharacterReputation(pchar, -3);
			dialog.text = StringFromKey("GenQuests_Dialog_661");
			link.l1 = StringFromKey("GenQuests_Dialog_662", pchar);
			link.l1.go = "CaptainComission_52";
		break;

		case "CaptainComission_52":
			dialog.text = StringFromKey("GenQuests_Dialog_663");
			link.l1 = StringFromKey("GenQuests_Dialog_664");
			link.l1.go = "CaptainComission_53";
			if (sti(pchar.money) >= 150000)
			{
				link.l2 = StringFromKey("GenQuests_Dialog_665", pchar);
				link.l2.go = "CaptainComission_54";
			}
		break;

		case "CaptainComission_53":
			ChangeCharacterReputation(pchar, -5);
			OfficersReaction("bad");
			AddQuestRecord("CaptainComission1", "22");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_54":
			OfficersReaction("good");
			addMoneyToCharacter(pchar, -150000);
			AddQuestRecord("CaptainComission1", "23");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_60":
			dialog.text = StringFromKey("GenQuests_Dialog_666");
			link.l1 = StringFromKey("GenQuests_Dialog_667", pchar);
			link.l1.go = "CaptainComission_61";
		break;

		case "CaptainComission_61":
			ChangeCharacterReputation(pchar, -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -15);
			AddQuestRecord("CaptainComission1", "32");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		// диалог с рабом в колодках
		case "CaptainComission_70":
			dialog.text = StringFromKey("GenQuests_Dialog_668");
			link.l1 = StringFromKey("GenQuests_Dialog_669", pchar.GenQuest.CaptainComission.SlaveName);
			link.l1.go = "CaptainComission_71";
		break;

		case "CaptainComission_71":
			dialog.text = StringFromKey("GenQuests_Dialog_670");
			link.l1 = StringFromKey("GenQuests_Dialog_671", XI_ConvertString(pchar.GenQuest.CaptainComission.SlaveEscapeLocation));
			link.l1.go = "CaptainComission_72";
		break;

		case "CaptainComission_72":
			dialog.text = StringFromKey("GenQuests_Dialog_672");
			link.l1 = StringFromKey("GenQuests_Dialog_673");
			link.l1.go = "CaptainComission_73";
		break;

		case "CaptainComission_73":
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);
			sTemp = GetNationNameByType(sti(pchar.GenQuest.CaptainComission.SlaveEscapePlantationNation)) + "_citizens";
			for (i = 0; i < 3; i++)
			{
				if (GetCharacterIndex("SlaveGuard_" + i) == -1) continue;
				sld = CharacterFromID("SlaveGuard_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SlaveGuards");
			}

			LAi_group_SetRelation("SlaveGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetRelation("SlaveGuards", sTemp, LAI_GROUP_NEITRAL);
			LAi_group_SetAlarmReaction("SlaveGuards", sTemp, LAI_GROUP_NEITRAL, LAI_GROUP_FRIEND);
			LAi_group_FightGroups("SlaveGuards", LAI_GROUP_PLAYER, true);
			LAi_group_SetAlarm("SlaveGuards", LAI_GROUP_PLAYER, 0);
			LAi_group_SetCheck("SlaveGuards", "OpenTheDoors");
			LAi_group_SetCheckFunction("SlaveGuards", "CaptainComission_GuardsAfter");

			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// диалог охранников раба
		case "CaptainComission_80":
			dialog.text = StringFromKey("GenQuests_Dialog_676", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_674"),
						StringFromKey("GenQuests_Dialog_675")));
			link.l1 = StringFromKey("GenQuests_Dialog_679", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_677", pchar.GenQuest.CaptainComission.SlaveName),
						StringFromKey("GenQuests_Dialog_678", pchar.GenQuest.CaptainComission.SlaveName)));
			link.l1.go = "CaptainComission_81";
		break;

		case "CaptainComission_81":
			dialog.text = StringFromKey("GenQuests_Dialog_680");
			link.l1 = StringFromKey("GenQuests_Dialog_681");
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_80";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "CaptainComission_85":
			dialog.text = StringFromKey("GenQuests_Dialog_682");
			link.l1 = StringFromKey("GenQuests_Dialog_683", XI_ConvertString(pchar.GenQuest.CaptainComission.SlaveEscapeLocation + "Dat"));
			link.l1.go = "CaptainComission_86";
		break;

		case "CaptainComission_86":
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", pchar.GenQuest.CaptainComission.SlaveEscapeReload, "none", "", "", "OpenTheDoors", -1.0);
			sTemp = GetNationNameByType(sti(pchar.GenQuest.CaptainComission.SlaveEscapePlantationNation)) + "_citizens";
			LAi_group_AttackGroup(sTemp, LAI_GROUP_PLAYER);
			DialogExit();
		break;

		case "CaptainComission_90":
			if (pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = StringFromKey("GenQuests_Dialog_684");
				link.l1 = StringFromKey("GenQuests_Dialog_685", pchar.GenQuest.CaptainComission.Name, XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
				link.l1.go = "CaptainComission_91";
			}
			if (pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
			{
				dialog.text = StringFromKey("GenQuests_Dialog_686");
				link.l1 = StringFromKey("GenQuests_Dialog_687");
				link.l1.go = "CaptainComission_92";
			}
		break;

		case "CaptainComission_91":
			dialog.text = StringFromKey("GenQuests_Dialog_688");
			link.l1 = StringFromKey("GenQuests_Dialog_689");
			link.l1.go = "CaptainComission_91End";
		break;

		case "CaptainComission_91End":
			pchar.GenQuest.CaptainComission = "toOurTavern";
			rChar = CharacterFromID("CapComission_Slave");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;

		case "CaptainComission_92":
			dialog.text = StringFromKey("GenQuests_Dialog_690");
			link.l1 = StringFromKey("GenQuests_Dialog_691");
			link.l1.go = "CaptainComission_93";
		break;

		case "CaptainComission_93":
			dialog.text = StringFromKey("GenQuests_Dialog_692", NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation)));
			link.l1 = StringFromKey("GenQuests_Dialog_693", pchar.GenQuest.CaptainComission.Name, XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			link.l1.go = "CaptainComission_94";
		break;

		case "CaptainComission_94":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));    // mitrokosta
			if (iNation == -1) iNation(rand(3));
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			dialog.text = StringFromKey("GenQuests_Dialog_694", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Gen"));
			link.l1 = StringFromKey("GenQuests_Dialog_695");
			link.l1.go = "CaptainComission_95";
			link.l2 = StringFromKey("GenQuests_Dialog_696");
			link.l2.go = "CaptainComission_96";
		break;

		case "CaptainComission_95":
			AddQuestRecord("CaptainComission1", "12"); // поставил запись в СЖ лесник
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("ся", "ась"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", FindMoneyString(sti(pchar.GenQuest.CaptainComission.SlaveMoney)));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.GenQuest.CaptainComission = "toEnemyTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;

		case "CaptainComission_96":
			dialog.text = StringFromKey("GenQuests_Dialog_697");
			link.l1 = StringFromKey("GenQuests_Dialog_698");
			link.l1.go = "CaptainComission_97";
		break;

		case "CaptainComission_97":
			AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			pchar.GenQuest.CaptainComission = "toTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;

		case "CaptainComission_100":
			dialog.text = StringFromKey("GenQuests_Dialog_699");
			link.l1 = StringFromKey("GenQuests_Dialog_700");
			link.l1.go = "CaptainComission_101";
		break;

		case "CaptainComission_101":
			GetSlaveSpeciality();
			dialog.text = StringFromKey("GenQuests_Dialog_701", pchar.GenQuest.CaptainComission.SlaveSpeciality, NationNamePeople(sti(pchar.GenQuest.CaptainComission.EnemyNation)));
			link.l1 = StringFromKey("GenQuests_Dialog_702");
			link.l1.go = "CaptainComission_102";
		break;

		case "CaptainComission_102":
			switch (sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					sTemp = StringFromKey("GenQuests_Dialog_703");
				break;
				case 1:
					sTemp = StringFromKey("GenQuests_Dialog_704");
				break;
				case 2:
					sTemp = StringFromKey("GenQuests_Dialog_705");
				break;
			}
			dialog.text = StringFromKey("GenQuests_Dialog_706", sTemp);
			link.l1 = StringFromKey("GenQuests_Dialog_707");
			link.l1.go = "CaptainComission_103";
		break;

		case "CaptainComission_103":
			dialog.text = StringFromKey("GenQuests_Dialog_708");
			link.l1 = StringFromKey("GenQuests_Dialog_709");
			link.l1.go = "CaptainComission_104";
		break;

		case "CaptainComission_104":
		// evganat - энциклопедия
			if (CheckRandomPage("questcaptain", "comission", 3))
			{
				GetPage(GetRandomTome(), 5);
			}
			AddQuestRecord("CaptainComission1", "21");
			CloseQuestHeader("CaptainComission1");
			// а теперь раздача слонов !!!!!!!
			switch (sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					if (drand(1) == 0)
					{
						AddCharacterSkill(pchar, SKILL_DEFENCE, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_REPAIR, 10);
					}
				break;
				case 1:
					if (drand(1) == 0)
					{
						AddCharacterSkill(pchar, SKILL_CANNONS, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_ACCURACY, 10);
					}
				break;
				case 2:
					AddCharacterSkill(pchar, SKILL_SAILING, 10);
				break;
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		// Генератор "Поручение капитана"

		// Генератор "Операция Галеон"
		case "CaptainComission_300":
			ReOpenQuestHeader("CaptainComission2");
			AddQuestRecord("CaptainComission2", "1");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCapName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission2", "sShipTypeNom", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name"))));
			AddQuestUserData("CaptainComission2", "sCity2", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen"));
			AddQuestUserData("CaptainComission2", "sCity11", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			SetFunctionLocationCondition("CaptainComission_GenerateQuestContinuation", GetArealByCityName(pchar.GenQuest.CaptainComission.City), false);
			SetFunctionTimerCondition("CaptainComission_TimeIsOver", 0, 0, 15, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission");
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar);
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();
		break;

		// диалог с кэпом на палубе
		case "CaptainComission_301":
			if (!CheckAttribute(pchar, "GenQuest.AlreadyTalked")) // проверка если разговор уже состоялся . чтобы не повторяться. лесник
			{
				pchar.quest.CaptainComission_TimeIsOver.over = "yes";
				dialog.text = StringFromKey("GenQuests_Dialog_712", RandPhraseSimple(
							StringFromKey("GenQuests_Dialog_710", GetFullName(NPChar), pchar.GenQuest.CaptainComission.ShipTypeName),
							StringFromKey("GenQuests_Dialog_711", GetFullName(NPChar))));
				link.l1 = StringFromKey("GenQuests_Dialog_713", GetFullName(pchar), pchar.GenQuest.CaptainComission.CapName, XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Pre"), GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name") + "Acc")));
				link.l1.go = "CaptainComission_302";
				break;
			}
			dialog.text = StringFromKey("GenQuests_Dialog_714");
			link.l2 = StringFromKey("GenQuests_Dialog_715");
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_301"; // чтобы не было перехода на баг  - и т.д.  лесник
		break;

		case "CaptainComission_302":
			dialog.text = StringFromKey("GenQuests_Dialog_716", pchar.GenQuest.CaptainComission.CapName);
			link.l1 = StringFromKey("GenQuests_Dialog_717");
			link.l1.go = "CaptainComission_303";
		break;

		case "CaptainComission_303":
			dialog.text = StringFromKey("GenQuests_Dialog_718", GetFullName(pchar), pchar.GenQuest.CaptainComission.CapName, XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			link.l1 = StringFromKey("GenQuests_Dialog_719");
			link.l1.go = "CaptainComission_304";
		break;

		case "CaptainComission_304":
			pchar.GenQuest.CaptainComission.ShoreLocation = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = StringFromKey("GenQuests_Dialog_720", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
			link.l1 = StringFromKey("GenQuests_Dialog_721");
			link.l1.go = "CaptainComission_305";
			link.l2 = StringFromKey("GenQuests_Dialog_722");
			link.l2.go = "CaptainComission_306";
		break;

		case "CaptainComission_305":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name") + "Gen"));
			if (LanguageGetLanguage() == "russian")
				dialog.text = StringFromKey("GenQuests_Dialog_723", NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)), sTemp, pchar.GenQuest.CaptainComission.VictimShipName, GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Ins")), sTemp, sTemp);
			else
				dialog.text = StringFromKey("GenQuests_Dialog_723", NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)), sTemp, pchar.GenQuest.CaptainComission.VictimShipName, GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Ins")));
			link.l1 = StringFromKey("GenQuests_Dialog_724");
			link.l1.go = "CaptainComission_307";
		break;

		case "CaptainComission_306":
			dialog.text = StringFromKey("GenQuests_Dialog_725");
			link.l1 = StringFromKey("GenQuests_Dialog_726");
			link.l1.go = "CaptainComission_306End";
		break;

		case "CaptainComission_306End":
			AddQuestRecord("CaptainComission2", "3");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", 1.5);
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
		break;

		case "CaptainComission_307":
			dialog.text = StringFromKey("GenQuests_Dialog_727");
			link.l1 = StringFromKey("GenQuests_Dialog_728");
			link.l1.go = "CaptainComission_308";
			link.l2 = StringFromKey("GenQuests_Dialog_729");
			link.l2.go = "CaptainComission_309";
		break;

		case "CaptainComission_308":
			dialog.text = StringFromKey("GenQuests_Dialog_730", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen")); // belamour gen
			link.l1 = StringFromKey("GenQuests_Dialog_731");
			link.l1.go = "CaptainComission_313";
		//			bQuestDisableMapEnter = true;
		break;

		case "CaptainComission_309":
			dialog.text = StringFromKey("GenQuests_Dialog_732", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")));
			link.l1 = StringFromKey("GenQuests_Dialog_733");
			link.l1.go = "CaptainComission_310";
		break;

		case "CaptainComission_310":
			dialog.text = StringFromKey("GenQuests_Dialog_734", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen")); // belamour gen
			link.l1 = StringFromKey("GenQuests_Dialog_735");
			link.l1.go = "CaptainComission_311";
			link.l2 = StringFromKey("GenQuests_Dialog_736", pchar);
			link.l2.go = "CaptainComission_312";
		break;

		case "CaptainComission_311":
			pchar.GenQuest.CaptainComission.FightAfterDeck = true; //после резни на палубе - драка в море		
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "CaptainComission_FightInDeck", 3.5);
			DialogExit();
		break;

		case "CaptainComission_312":
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_toShore");
		break;

		case "CaptainComission_313":
			NextDiag.TempNode = "CaptainComission_314";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("CaptainComission2", "7");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreNameDat", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Dat"));
			SetFunctionTimerCondition("CaptainCommission_SailToShore", 0, 0, 1, false);
			pchar.GenQuest.AlreadyTalked = "true"; // лесник временная запоминалка для диалога
			DialogExit();
		break;

		case "CaptainComission_314":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = StringFromKey("GenQuests_Dialog_737");
			link.l1 = StringFromKey("GenQuests_Dialog_738");
			link.l1.go = "exit";
		break;

		case "CaptainComission_315":
			dialog.text = StringFromKey("GenQuests_Dialog_739");
			link.l1 = StringFromKey("GenQuests_Dialog_740");
			link.l1.go = "CaptainComission_316";
		break;

		case "CaptainComission_316":
			dialog.text = StringFromKey("GenQuests_Dialog_741");
			link.l1 = StringFromKey("GenQuests_Dialog_742");
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.AlreadyTalked"); // удаление проверки на повтор диалога лесник
			AddDialogExitQuestFunction("CaptainComission_GenerateShorePatrol");
		break;

		// диалог с патрулем на берегу
		case "CaptainComission_317":
			dialog.text = StringFromKey("GenQuests_Dialog_743", pchar.GenQuest.CaptainComission.Name);
			link.l1 = StringFromKey("GenQuests_Dialog_744");
			link.l1.go = "CaptainComission_318";
		break;

		case "CaptainComission_318":
			dialog.text = StringFromKey("GenQuests_Dialog_745");
			link.l1 = StringFromKey("GenQuests_Dialog_746");
			link.l1.go = "CaptainComission_319";
		break;

		case "CaptainComission_319":
			DialogExit();
			for (i = 1; i <= sti(pchar.GenQuest.CaptainComission.SoldierQty); i++)
			{
				sTemp = "SoldierIDX" + i;
				sld = GetCharacter(sti(pchar.GenQuest.CaptainComission.(sTemp)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
			}

			LAi_group_SetHearRadius("CoastalGuards", 100.0);
			sld = characterFromId("CapComission_1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);
			LAi_SetFightMode(Pchar, true);
		break;

		case "CaptainComission_320":
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие если жив.
			pchar.GenQuest.CaptainComission.GoodsQty = makeint((sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Capacity")) - sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Capacity")) + rand(250)) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			pchar.GenQuest.CaptainComission.GoodsQtyNorm = sti(pchar.GenQuest.CaptainComission.GoodsQty);
			dialog.text = StringFromKey("GenQuests_Dialog_747", pchar.GenQuest.CaptainComission.GoodsQty, GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			link.l1 = StringFromKey("GenQuests_Dialog_748");
			link.l1.go = "CaptainComission_321";
		break;

		case "CaptainComission_321":
			iTemp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation), pchar.GenQuest.CaptainComission.City, true);
			sTemp = Colonies[iTemp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;
			dialog.text = StringFromKey("GenQuests_Dialog_749", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen"), XI_ConvertString(GetIslandNameByCity(sTemp) + "Pre"));
			link.l1 = StringFromKey("GenQuests_Dialog_750");
			link.l1.go = "CaptainComission_322";
			if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l2 = StringFromKey("GenQuests_Dialog_751", pchar);
				link.l2.go = "CaptainComission_323";
			}
		break;

		case "CaptainComission_322":
			Group_DeleteGroup("Sea_CapComission_1");
			sld = characterFromId("CapComission_1");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			sld.lifeDay = 0;
			CaptainComission_GenerateCoastalPatrol();
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if (iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			AddQuestRecord("CaptainComission2", "10");
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_323":
			sld = characterFromId("CapComission_1");
			Fantom_SetCharacterGoods(sld, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoFreeSpace(sld), 1);
			pchar.GenQuest.CaptainComission.ConvoyMoney = makeint((sti(pchar.rank) * 100 + sti(NPChar.rank) * 170 + dRand(30) * 20) * 2.5);
			pchar.GenQuest.CaptainComission.iDay = 15 + dRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if (iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = StringFromKey("GenQuests_Dialog_752", FindMoneyString(sti(pchar.GenQuest.CaptainComission.ConvoyMoney)), pchar.GenQuest.CaptainComission.iDay);
			link.l1 = StringFromKey("GenQuests_Dialog_753");
			link.l1.go = "CaptainComission_324";
			NextDiag.TempNode = "CaptainComission_325";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "CaptainComission_324":
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха 
			sld = characterFromId("CapComission_1");
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(sld);
			LAi_ActorSetStayMode(sld);
			CharacterIntoCompanionAndGoOut(pchar, sld, "reload", sTemp, 5, false);
			SetShipRemovable(sld, false);
			SetCharacterRemovable(sld, false);
			Group_ChangeCharacter(PLAYER_GROUP, "CapComission_1");
			AddQuestRecord("CaptainComission2", "11");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(GetIslandNameByCity(pchar.GenQuest.CaptainComission.ConvoyCity) + "Pre"));
			AddQuestUserData("CaptainComission2", "sSum", FindMoneyString(sti(pchar.GenQuest.CaptainComission.ConvoyMoney)));
			CaptainComission_GenerateCoastalPatrol();
			pchar.quest.CaptainComission_MapEnter.win_condition.l1 = "MapEnter";
			pchar.quest.CaptainComission_MapEnter.function = "CaptainComission_MapEnter";
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1 = "Character_sink";
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_CapShip_Sink.function = "CaptainComission_CapShip_Sink";
			DialogExit();
		break;

		case "CaptainComission_325":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = StringFromKey("GenQuests_Dialog_757", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_754"),
						StringFromKey("GenQuests_Dialog_755"),
						StringFromKey("GenQuests_Dialog_756", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name"))))));
			link.l1 = StringFromKey("GenQuests_Dialog_761", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_758"),
						StringFromKey("GenQuests_Dialog_759"),
						StringFromKey("GenQuests_Dialog_760")));
			link.l1.go = "exit";
		break;

		case "CaptainComission_326_0":
			dialog.text = StringFromKey("GenQuests_Dialog_762");
			link.l1 = StringFromKey("GenQuests_Dialog_763");
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false;
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;

		case "CaptainComission_326":
			sld = characterFromId("Blaze");
			dialog.text = StringFromKey("GenQuests_Dialog_764", pchar.CaptainComission.Name, pchar.CaptainComission.CapName);
			link.l1 = StringFromKey("GenQuests_Dialog_765", sld, pchar.CaptainComission.CapName, pchar.CaptainComission.FullName);
			link.l1.go = "CaptainComission_327";
		break;

		case "CaptainComission_327":
			sld = characterFromId("Blaze");
			dialog.text = StringFromKey("GenQuests_Dialog_766", sld);
			link.l1 = StringFromKey("GenQuests_Dialog_767", sld);
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialog");
		break;

		case "CaptainComission_328":
			dialog.text = StringFromKey("GenQuests_Dialog_768", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("GenQuests_Dialog_769");
			link.l1.go = "CaptainComission_329";
		break;

		case "CaptainComission_329":
			pchar.GenQuest.CaptainComission.GoodsSum = 2 * sti(pchar.GenQuest.CaptainComission.GoodsQtyNorm) * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost);
			dialog.text = StringFromKey("GenQuests_Dialog_770", FindMoneyString(sti(pchar.GenQuest.CaptainComission.GoodsSum)));
			link.l1 = StringFromKey("GenQuests_Dialog_771");
			link.l1.go = "CaptainComission_330";
		break;

		case "CaptainComission_330":
			dialog.text = StringFromKey("GenQuests_Dialog_772");
			link.l1 = StringFromKey("GenQuests_Dialog_773", pchar);
			link.l1.go = "CaptainComission_331";
			if (sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsSum))
			{
				link.l2 = StringFromKey("GenQuests_Dialog_774");
				link.l2.go = "CaptainComission_332";
			}
		break;

		case "CaptainComission_331":
			dialog.text = StringFromKey("GenQuests_Dialog_775", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_776");
			link.l1.go = "CaptainComission_334";
			CaptainComission_ChangeCaptain();
		break;

		case "CaptainComission_332":
			dialog.text = StringFromKey("GenQuests_Dialog_777");
			link.l1 = StringFromKey("GenQuests_Dialog_778");
			link.l1.go = "CaptainComission_333";
		break;

		case "CaptainComission_333":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);// лесник - разрешить снова драться после сдачи денег. но после драки кулаками не машут ..как говориться))
			LAi_LockFightMode(pchar, false);
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsSum));
			AddQuestRecord("CaptainComission2", "17");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", UpperFirst(XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsSum);
			CloseQuestHeader("CaptainComission2");
			ChangeOfficersLoyality("bad_all", 1);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GangExit");
		break;

		case "CaptainComission_334":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for (i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
				// evganat - энциклопедия
				if (i == 0)
				{
					if (CheckRandomPage("questcaptain", "comission", 4))
					{
						rChar.encyclopedia.tome = GetRandomTome();
						rChar.encyclopedia.page = 5;
					}
				}
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors");
			LAi_group_SetCheckFunction(sGroup, "CaptainComission_GangDied");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CaptainComission_340":
			dialog.text = StringFromKey("GenQuests_Dialog_779", GetFullName(pchar));
			link.l1 = StringFromKey("GenQuests_Dialog_780", pchar);
			link.l1.go = "CaptainComission_341";
		break;

		case "CaptainComission_341":
			Group_DeleteGroup("Sea_CapComission_1");
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0;
			AddQuestRecord("CaptainComission2", "15");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name"))));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_Canoneer":
			dialog.text = StringFromKey("GenQuests_Dialog_781");
			link.l1 = StringFromKey("GenQuests_Dialog_782");
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_Canoneer1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("CaptainComission_TalkCanoneer");
		break;

		case "CaptainComission_Canoneer1":
			dialog.text = StringFromKey("GenQuests_Dialog_783", GetAddress_Form(pchar));
			link.l1 = StringFromKey("GenQuests_Dialog_784");
			link.l1.go = "CaptainComission_Canoneer2";
		break;

		case "CaptainComission_Canoneer2":
			dialog.text = StringFromKey("GenQuests_Dialog_785", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_786", pchar, pchar.GenQuest.CaptainComission.Name);
			link.l1.go = "CaptainComission_Canoneer3";
		break;

		case "CaptainComission_Canoneer3":
			dialog.text = StringFromKey("GenQuests_Dialog_787", pchar.GenQuest.CaptainComission.Name);
			link.l1 = StringFromKey("GenQuests_Dialog_788");
			link.l1.go = "CaptainComission_Canoneer4";
		break;

		case "CaptainComission_Canoneer4":
			dialog.text = StringFromKey("GenQuests_Dialog_789", pchar.GenQuest.CaptainComission.Name);
			link.l1 = StringFromKey("GenQuests_Dialog_790", pchar, pchar.GenQuest.CaptainComission.CapName, pchar.GenQuest.CaptainComission.Name, GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name") + "Acc")), pchar.GenQuest.CaptainComission.VictimShipName);
			link.l1.go = "CaptainComission_Canoneer5";
		break;

		case "CaptainComission_Canoneer5":
			dialog.text = StringFromKey("GenQuests_Dialog_791", pchar.GenQuest.CaptainComission.CapName, GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name"))), XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen"), GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Ins")));
			link.l1 = StringFromKey("GenQuests_Dialog_792");
			link.l1.go = "CaptainComission_Canoneer6";
		break;

		case "CaptainComission_Canoneer6":
			dialog.text = StringFromKey("GenQuests_Dialog_793", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name") + "Acc")));
			link.l1 = StringFromKey("GenQuests_Dialog_794");
			link.l1.go = "CaptainComission_Canoneer7";
		break;

		case "CaptainComission_Canoneer7":
			dialog.text = StringFromKey("GenQuests_Dialog_795", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")));
			link.l1 = StringFromKey("GenQuests_Dialog_796");
			link.l1.go = "CaptainComission_Canoneer8";
		break;

		case "CaptainComission_Canoneer8":
			dialog.text = StringFromKey("GenQuests_Dialog_797", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name") + "Gen")));
			link.l1 = StringFromKey("GenQuests_Dialog_798");
			link.l1.go = "CaptainComission_Canoneer9";
		break;

		case "CaptainComission_Canoneer9":
			dialog.text = StringFromKey("GenQuests_Dialog_799", NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)), GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")), GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name") + "Gen")));
			link.l1 = StringFromKey("GenQuests_Dialog_800");
			link.l1.go = "CaptainComission_Canoneer10";
		break;

		case "CaptainComission_Canoneer10":
			iTemp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation), pchar.GenQuest.CaptainComission.City, true);
			pchar.GenQuest.CaptainComission.CanoneerCity = Colonies[iTemp].id;
			pchar.GenQuest.CaptainComission.Sum = 20000 + 2000 * sti(pchar.rank);
			dialog.text = StringFromKey("GenQuests_Dialog_801", FindMoneyString(sti(pchar.GenQuest.CaptainComission.Sum)), XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity));
			if (sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))
			{
				link.l1 = StringFromKey("GenQuests_Dialog_802", pchar);
				link.l1.go = "CaptainComission_Canoneer11";
			}
			else
			{
				link.l1 = StringFromKey("GenQuests_Dialog_803");
				link.l1.go = "CaptainComission_Canoneer12";
			}
			link.l2 = StringFromKey("GenQuests_Dialog_804");
			link.l2.go = "CaptainComission_Canoneer13";
		break;

		case "CaptainComission_Canoneer11":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.Sum));
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = StringFromKey("GenQuests_Dialog_805", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen"), pchar.GenQuest.CaptainComission.GoodsQty, GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen"))); // belamour gen
			link.l1 = StringFromKey("GenQuests_Dialog_806");
			link.l1.go = "CaptainComission_Canoneer14";
		break;

		case "CaptainComission_Canoneer12":
			AddQuestRecord("CaptainComission2", "41");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sSum", FindMoneyString(sti(pchar.GenQuest.CaptainComission.Sum)));
			AddQuestUserData("CaptainComission2", "sName", GetName(NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			SetFunctionTimerCondition("CaptainComission_CanoneerWaitMoney", 0, 0, 1, false);
			NextDiag.TempNode = "CaptainComission_Canoneer15";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;

		case "CaptainComission_Canoneer13":
			AddQuestRecord("CaptainComission2", "40");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sName", GetName(NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(NPChar);
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;

		case "CaptainComission_Canoneer14":
			AddQuestRecord("CaptainComission2", "43");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sName", GetName(NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat"));
			LAi_CharacterDisableDialog(NPChar);
			SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			SetFunctionTimerCondition("CaptainComission_MeetCanoneerInShoreTimer", 0, 0, 1, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;

		case "CaptainComission_Canoneer15":
			if (sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))
			{
				dialog.text = StringFromKey("GenQuests_Dialog_807");
				link.l1 = StringFromKey("GenQuests_Dialog_808", pchar);
				pchar.quest.CaptainComission_CanoneerWaitMoney.over = "yes";// лесник . снят таймер ожилания бабла
				link.l1.go = "CaptainComission_Canoneer11";
			}
			else
			{
				dialog.text = StringFromKey("GenQuests_Dialog_809");
				link.l1 = StringFromKey("GenQuests_Dialog_810");
				link.l1.go = "exit";
				NextDiag.TempNode = "CaptainComission_Canoneer15";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
		break;

		case "CaptainComission_350":
			dialog.text = StringFromKey("GenQuests_Dialog_811");
			link.l1 = StringFromKey("GenQuests_Dialog_812", pchar);
			link.l1.go = "CaptainComission_351";
			link.l2 = StringFromKey("GenQuests_Dialog_813", pchar);
			link.l2.go = "CaptainComission_352";
		break;

		case "CaptainComission_351":
			DialogExit();
			AddDialogExitQuest("CaptainComission_GangDialog_1");
		break;

		case "CaptainComission_352":
			DialogExit();
			//SetFunctionExitFromLocationCondition("CaptainComission_NoGangDialog", pchar.location, false);
			AddDialogExitQuestFunction("CaptainComission_NoGangDialog");   // лесник - исправлено . предыдцщий код не работал
		break;

		case "CaptainComission_360":
			dialog.text = StringFromKey("GenQuests_Dialog_814");
			link.l1 = StringFromKey("GenQuests_Dialog_815");
			link.l1.go = "CaptainComission_361";
		break;

		case "CaptainComission_361":
			dialog.text = StringFromKey("GenQuests_Dialog_816");
			link.l1 = StringFromKey("GenQuests_Dialog_817");
			link.l1.go = "CaptainComission_362";
		break;

		case "CaptainComission_362":
			dialog.text = StringFromKey("GenQuests_Dialog_818");
			link.l1 = StringFromKey("GenQuests_Dialog_819");
			link.l1.go = "CaptainComission_363";
		break;

		case "CaptainComission_363":
			dialog.text = StringFromKey("GenQuests_Dialog_820");
			link.l1 = StringFromKey("GenQuests_Dialog_821");
			link.l1.go = "CaptainComission_364";
		break;

		case "CaptainComission_364":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			if (pchar.GenQuest.CaptainComission.variant == "A2")
			{
				rChar = CharacterFromID("CapComission_1");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
			}
			if (pchar.GenQuest.CaptainComission.variant == "A3")
			{
				rChar = CharacterFromID("CapComission_Canoneer");
				//LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
			}
			for (i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors");
			if (pchar.GenQuest.CaptainComission.variant == "A2")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckCaptainAfterBattle");
			}
			if (pchar.GenQuest.CaptainComission.variant == "A3")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckGangAfterBattle");
			}
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CaptainComission_365":
			dialog.text = StringFromKey("GenQuests_Dialog_822");
			link.l1 = StringFromKey("GenQuests_Dialog_823");
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_365";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "CaptainComission_366":
			dialog.text = StringFromKey("GenQuests_Dialog_824", GetFullName(pchar));
			link.l1 = StringFromKey("GenQuests_Dialog_825");
			link.l1.go = "CaptainComission_367";
		break;

		case "CaptainComission_367":
			dialog.text = StringFromKey("GenQuests_Dialog_826");
			link.l1 = StringFromKey("GenQuests_Dialog_827", pchar);
			link.l1.go = "CaptainComission_368";
		break;

		case "CaptainComission_368":
			LAi_SetActorType(NPChar);
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.LifeDay = 0;
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			// evganat - энциклопедия
			if (CheckRandomPage("questcaptain", "comission", 5))
			{
				GetPage(GetRandomTome(), 6);
			}
			AddQuestRecord("CaptainComission2", "48");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCharName", GetName(NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_INS));
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity + "Gen"));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_370":
			if (pchar.GenQuest.CaptainComission == "MayorTalkBad")
			{
				pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			}
			dialog.text = StringFromKey("GenQuests_Dialog_828"); // лесник
			link.l1 = StringFromKey("GenQuests_Dialog_829", pchar.GenQuest.CaptainComission.Name);
			link.l1.go = "CaptainComission_371";
		break;

		case "CaptainComission_371":
			dialog.text = StringFromKey("GenQuests_Dialog_830", pchar.GenQuest.CaptainComission.Name);
			link.l1 = StringFromKey("GenQuests_Dialog_831", GetFullName(pchar));
			link.l1.go = "CaptainComission_372";
		break;

		case "CaptainComission_372":
			dialog.text = StringFromKey("GenQuests_Dialog_832");
			link.l1 = StringFromKey("GenQuests_Dialog_833", pchar, pchar.GenQuest.CaptainComission.CapName, GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name") + "Acc")), pchar.GenQuest.CaptainComission.VictimShipName, GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name"))), XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen"));
			link.l1.go = "CaptainComission_373";
		break;

		case "CaptainComission_373":
			dialog.text = StringFromKey("GenQuests_Dialog_834", pchar.GenQuest.CaptainComission.CapName);
			link.l1 = StringFromKey("GenQuests_Dialog_835");
			link.l1.go = "CaptainComission_374";
		break;

		case "CaptainComission_374":
			dialog.text = StringFromKey("GenQuests_Dialog_836", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name") + "Gen")), pchar.GenQuest.CaptainComission.CapName, GetFullName(pchar));
			if (!CheckAttribute(pchar, "GenQuest.CaptainComission.GetRumour"))
			{
				if (CheckAttribute(pchar, "GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = StringFromKey("GenQuests_Dialog_837");
					link.l1.go = "CaptainComission_375";
				}
				else
				{
					link.l1 = StringFromKey("GenQuests_Dialog_838");
					link.l1.go = "CaptainComission_375";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = StringFromKey("GenQuests_Dialog_839");
					link.l1.go = "CaptainComission_375";
				}
				else
				{
					link.l1 = StringFromKey("GenQuests_Dialog_840");
					link.l1.go = "CaptainComission_375";
				}
			}
		break;

		case "CaptainComission_375":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name") + "Gen"));
			if (LanguageGetLanguage() == "russian")
				dialog.text = StringFromKey("GenQuests_Dialog_841", NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)), sTemp, pchar.GenQuest.CaptainComission.VictimShipName, GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Ins")), sTemp, sTemp);
			else
				dialog.text = StringFromKey("GenQuests_Dialog_841", NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)), sTemp, pchar.GenQuest.CaptainComission.VictimShipName, GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Ins")));
			link.l1 = StringFromKey("GenQuests_Dialog_842");
			link.l1.go = "CaptainComission_376";
		break;

		case "CaptainComission_376":
			dialog.text = StringFromKey("GenQuests_Dialog_843");
			link.l1 = StringFromKey("GenQuests_Dialog_844");
			link.l1.go = "CaptainComission_377";
			link.l2 = StringFromKey("GenQuests_Dialog_845");
			link.l2.go = "CaptainComission_378";
		break;

		case "CaptainComission_377":
			dialog.text = StringFromKey("GenQuests_Dialog_846");
			link.l1 = StringFromKey("GenQuests_Dialog_847");
			link.l1.go = "CaptainComission_379";
		break;

		case "CaptainComission_378":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			sld = CharacterFromID("CapComission_1");
			sld.LifeDay = 0;
			ChangeCharacterReputation(pchar, -5);
			AddQuestRecord("CaptainComission2", "8");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(npchar);// лесник - запрет диалога
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_379":
			AddQuestRecord("CaptainComission2", "21");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition = "CaptainComission_PrisonFree_Death";
			GetCharacterPos(npchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_group_Register("CapComission_Prison");
			LAi_group_SetRelation("CapComission_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "CapComission_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "CapComission_Prison");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CaptainComission.PrisonFree = true;
			if (pchar.GenQuest.CaptainComission == "MayorTalkGood")
			{
				chrDisableReloadToLocation = true;
				sld = CharacterFromId(pchar.GenQuest.CaptainComission.City + "JailOff");
				sld.dialog.currentnode = "CapComission_PrisonFree1";
			}
			pchar.quest.CapComission_ExitFromPrison.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_ExitFromPrison.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_ExitFromPrison.win_condition = "CaptainComission_ExitFromPrison";
			DialogExit();
		break;

		case "CaptainComission_380":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			pchar.quest.CaptainComission_PrisonFree_Death.over = "yes";
			DeleteAttribute(pchar, "GenQuest.CaptainComission.canSpeakCaptain");
			DeleteAttribute(pchar, "GenQuest.CaptainComission.PrisonFree");
			pchar.GenQuest.CaptainComission = "CanGetGoods";
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = StringFromKey("GenQuests_Dialog_848", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Acc"));
			link.l1 = StringFromKey("GenQuests_Dialog_849");
			link.l1.go = "CaptainComission_381";
		break;

		case "CaptainComission_381":
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = StringFromKey("GenQuests_Dialog_850", pchar.GenQuest.CaptainComission.GoodsQty, GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			link.l1 = StringFromKey("GenQuests_Dialog_851");
			link.l1.go = "CaptainComission_382";
		break;

		case "CaptainComission_382":
			AddQuestRecord("CaptainComission2", "24");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Pre"));
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			SetFunctionLocationCondition("CaptainComission_MeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
			SetFunctionTimerConditionParam("CaptainComission_CapEscapeTimer", 0, 0, 1, MakeInt(24 - GetHour()), false);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false; // Откроем выход
			DeleteAttribute(pchar, "TownEscape");
			QuestOpenSeaExit();
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;

		case "CaptainComission_383":
			dialog.text = StringFromKey("GenQuests_Dialog_852");
			link.l1 = StringFromKey("GenQuests_Dialog_853");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialogGetGoods");
		break;

		case "CaptainComission_384":
			dialog.text = StringFromKey("GenQuests_Dialog_854");
			link.l1 = StringFromKey("GenQuests_Dialog_855", pchar);
			link.l1.go = "CaptainComission_385";
		break;

		case "CaptainComission_385":
			dialog.text = StringFromKey("GenQuests_Dialog_856");
			link.l1 = StringFromKey("GenQuests_Dialog_857");
			link.l1.go = "CaptainComission_386";
		break;

		case "CaptainComission_386":
			dialog.text = StringFromKey("GenQuests_Dialog_858");
			link.l1 = StringFromKey("GenQuests_Dialog_859");
			link.l1.go = "CaptainComission_364";
		break;

		case "CaptainComission_387":
			LAi_LocationDisableOfficersGen(pchar.GenQuest.CaptainComission.ConvoyShore, false);
			pchar.GenQuest.CaptainComission.MaxGoodsQty = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if (sti(pchar.GenQuest.CaptainComission.MaxGoodsQty) > sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.MaxGoodsQty = pchar.GenQuest.CaptainComission.GoodsQty;
			dialog.text = StringFromKey("GenQuests_Dialog_860", pchar.GenQuest.CaptainComission.GoodsQty, GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			link.l1 = StringFromKey("GenQuests_Dialog_861", pchar);
			link.l1.go = "CaptainComission_388";
			if (!CheckAttribute(pchar, "GenQuest.CaptainComission.MayorTalkGood"))
			{
				link.l2 = StringFromKey("GenQuests_Dialog_862");
				link.l2.go = "CaptainComission_389";
			}
			if (CheckAttribute(pchar, "GenQuest.CaptainComission.MayorTalkGood"))
			{
				link.l3 = StringFromKey("GenQuests_Dialog_863", pchar, pchar.GenQuest.CaptainComission.Name);
				link.l3.go = "CaptainComission_389";
				link.l2 = StringFromKey("GenQuests_Dialog_864");
				link.l2.go = "CaptainComission_389_1"; // // лесник . отдельный диалог в случае обмана всех.
			}
		break;

		case "CaptainComission_388":
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			iTemp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation), pchar.GenQuest.CaptainComission.City, true);
			sTemp = Colonies[iTemp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;
			pchar.GenQuest.CaptainComission.iDay = 20 + dRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if (iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = StringFromKey("GenQuests_Dialog_865", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen"), XI_ConvertString(GetIslandNameByCity(sTemp) + "Pre"), pchar.GenQuest.CaptainComission.iDay);
			link.l1 = StringFromKey("GenQuests_Dialog_866");
			link.l1.go = "CaptainComission_391";
		break;

		case "CaptainComission_389_1": // лесник . отдельный диалог в случае обмана всех.
			DeleteAttribute(pchar, "GenQuest.CaptainComission.MayorTalkGood");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = StringFromKey("GenQuests_Dialog_867");
			link.l1 = StringFromKey("GenQuests_Dialog_868");
			link.l1.go = "CaptainComission_390";
			SetFunctionTimerConditionParam("CaptainComission_DeceivedGovernor", 0, 0, 1, MakeInt(24 - GetHour()), false);
		break;

		case "CaptainComission_389":
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = StringFromKey("GenQuests_Dialog_869");
			link.l1 = StringFromKey("GenQuests_Dialog_870");
			link.l1.go = "CaptainComission_390";
		break;

		case "CaptainComission_390":
			LAi_SetPlayerType(pchar);
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			if (pchar.GenQuest.CaptainComission == "CapDuel")
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CaptainDiedDuel");
			}
			else
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CheckCaptainDied");
			}
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CaptainComission_391":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			pchar.GenQuest.CaptainComission.CapGoodsQty = sti(pchar.GenQuest.CaptainComission.GoodsQty) / 2;
			if (sti(pchar.GenQuest.CaptainComission.CapGoodsQty) > sti(pchar.GenQuest.CaptainComission.MaxGoodsQty)) pchar.GenQuest.CaptainComission.CapGoodsQty = pchar.GenQuest.CaptainComission.MaxGoodsQty;
			if (CheckAttribute(pchar, "GenQuest.CaptainComission.MayorTalkGood"))
			{
				AddQuestRecord("CaptainComission2", "52");// лесник. выбор записи в СЖ
				AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("", "а"));
			}
			else AddQuestRecord("CaptainComission2", "26");// смотря по какому пути пошел
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.MaxGoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum1", pchar.GenQuest.CaptainComission.CapGoodsQty);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sDays", pchar.GenQuest.CaptainComission.iDay);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Acc"));
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyIsland + "Pre"));
			OfficersReaction("bad");
			if (CheckAttribute(pchar, "GenQuest.CaptainComission.MayorTalkGood"))
			{
				ChangeCharacterReputation(pchar, -5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
			}
			CaptainComission_GenerateCoastalPatrol();
			pchar.GenQuest.CaptainComission = "GetGoodsEscape";
			SetFunctionLocationCondition("CaptainComission_CapMeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission.DeleiveCapShore");
			DialogExit();
		break;

		case "CaptainComission_392":
			dialog.text = StringFromKey("GenQuests_Dialog_871");
			link.l1 = StringFromKey("GenQuests_Dialog_872");
			link.l1.go = "CaptainComission_393";
		break;

		case "CaptainComission_393":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = StringFromKey("GenQuests_Dialog_873", GetFullName(pchar), FindMoneyString(sti(pchar.GenQuest.CaptainComission.GoodsPrice)));
			if (sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				link.l1 = StringFromKey("GenQuests_Dialog_874");
				link.l1.go = "CaptainComission_394";
			}
			link.l2 = StringFromKey("GenQuests_Dialog_875");
			link.l2.go = "CaptainComission_395_1"; // лесник . верный переход
		break;

		case "CaptainComission_394":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			dialog.text = StringFromKey("GenQuests_Dialog_876");
			link.l1 = StringFromKey("GenQuests_Dialog_877", pchar);
			link.l1.go = "CaptainComission_395";
		break;

		case "CaptainComission_395_1": // лесник . верное назначение диалога
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes";
			dialog.text = StringFromKey("GenQuests_Dialog_878");
			link.l1 = StringFromKey("GenQuests_Dialog_879");
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
		break;

		case "CaptainComission_395":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "32");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Pre"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", FindMoneyString(sti(pchar.GenQuest.CaptainComission.GoodsPrice)));
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_396_0":
			dialog.text = StringFromKey("GenQuests_Dialog_880");
			link.l1 = StringFromKey("GenQuests_Dialog_881");
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false;
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;

		case "CaptainComission_396":
			sld = characterFromId("Blaze");
			dialog.text = StringFromKey("GenQuests_Dialog_882", GetFullName(pchar), pchar.CaptainComission.CapName);
			link.l1 = StringFromKey("GenQuests_Dialog_883", sld, pchar.CaptainComission.CapName, pchar.CaptainComission.FullName);
			link.l1.go = "CaptainComission_397";
		break;

		case "CaptainComission_397":
			sld = characterFromId("Blaze");
			dialog.text = StringFromKey("GenQuests_Dialog_884", sld);
			link.l1 = StringFromKey("GenQuests_Dialog_885", sld);
			link.l1.go = "CaptainComission_398";
		break;

		case "CaptainComission_398":
			sld = characterFromId("Blaze");
			dialog.text = StringFromKey("GenQuests_Dialog_886", sld, GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.CaptainComission.ShipTypeVictim), "Name"))));
			link.l1 = StringFromKey("GenQuests_Dialog_887", sld, GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.CaptainComission.ShipTypeVictim), "Name") + "Acc")));
			link.l1.go = "CaptainComission_399";
		break;

		case "CaptainComission_399":
			dialog.text = StringFromKey("GenQuests_Dialog_888");
			link.l1 = StringFromKey("GenQuests_Dialog_889");
			link.l1.go = "CaptainComission_400";
		break;

		case "CaptainComission_400":
			sld = characterFromId("Blaze");
			dialog.text = StringFromKey("GenQuests_Dialog_890", sld);
			link.l1 = StringFromKey("GenQuests_Dialog_891");
			link.l1.go = "exit";
			AddDialogExitQuest("CaptainComission_ShoreGangDialog");
		break;

		case "CaptainComission_401":
			dialog.text = StringFromKey("GenQuests_Dialog_892");
			link.l1 = StringFromKey("GenQuests_Dialog_893");
			link.l1.go = "CaptainComission_402";
		break;

		case "CaptainComission_402":
			dialog.text = StringFromKey("GenQuests_Dialog_894");
			link.l1 = StringFromKey("GenQuests_Dialog_895");
			link.l1.go = "CaptainComission_403";
		break;

		case "CaptainComission_403":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = StringFromKey("GenQuests_Dialog_896", GetFullName(pchar), FindMoneyString(sti(pchar.GenQuest.CaptainComission.GoodsPrice)));
			if (sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				pchar.quest.CaptainComission_Capitan_Cdox.over = "yes"; // на всякий случай .лесник
				pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник
				link.l1 = StringFromKey("GenQuests_Dialog_897");
				link.l1.go = "CaptainComission_404";
			}
			link.l2 = StringFromKey("GenQuests_Dialog_898");
			link.l2.go = "CaptainComission_405";
		break;

		case "CaptainComission_404":
			bOk = false;
			if (drand(1) == 0)
			{
				NPChar.reputation = 60 + rand(20);
				NPChar.alignment = "good";
				SetCharacterPerk(NPChar, "Honest");
			}
			else
			{
				NPChar.reputation = 10 + rand(20);
				NPChar.alignment = "bad";
				SetCharacterPerk(NPChar, "Rebel");
			}
			if (NPChar.alignment == "good" && sti(pchar.reputation) > 50) bOk = true;
			if (NPChar.alignment == "bad" && sti(pchar.reputation) <= 50) bOk = true;

			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));

			if (!bOk || FindFreeRandomOfficer() < 0)
			{
				dialog.text = StringFromKey("GenQuests_Dialog_899");
				link.l1 = StringFromKey("GenQuests_Dialog_900", pchar);
				link.l1.go = "CaptainComission_406";
			}
			else
			{
				dialog.text = StringFromKey("GenQuests_Dialog_901");
				if (!CaptainComission_CheckAllPassengersHired())
				{
					link.l1 = StringFromKey("GenQuests_Dialog_902", pchar);
					link.l1.go = "CaptainComission_407";
				}
				link.l2 = StringFromKey("GenQuests_Dialog_903");
				link.l2.go = "CaptainComission_408";
			}
		break;

		case "CaptainComission_405":
			dialog.text = StringFromKey("GenQuests_Dialog_904");
			link.l1 = StringFromKey("GenQuests_Dialog_905");
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
			pchar.GenQuest.CaptainComission.Duel = true;
		break;

		case "CaptainComission_406":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "34");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", FindMoneyString(sti(pchar.GenQuest.CaptainComission.GoodsPrice)));
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_407":
			AddQuestRecord("CaptainComission2", "36");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", FindMoneyString(sti(pchar.GenQuest.CaptainComission.GoodsPrice)));
			CloseQuestHeader("CaptainComission2");
			npchar.CaptainComission = true;
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			SetCharacterRemovable(Npchar, true);
			NPChar.Dialog.Filename = "Officer_Man.c";
			NPChar.greeting = "Gr_Officer";
			//NPChar.quest.OfficerPrice = sti(pchar.rank)*500; TODO_salary
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);

			DeleteAttribute(Npchar, "Ship");
			Npchar.Ship.Type = SHIP_NOTUSED;
			DeleteAttribute(Npchar, "Fellows"); // его офицеры
			Npchar.Fellows.Passengers.id0 = Npchar.index; // свой пассажир

			Npchar.Fellows.Passengers.boatswain = "-1";
			Npchar.Fellows.Passengers.navigator = "-1";
			Npchar.Fellows.Passengers.doctor = "-1";
			Npchar.Fellows.Passengers.cannoner = "-1";
			Npchar.Fellows.Passengers.treasurer = "-1";
			Npchar.Fellows.Passengers.carpenter = "-1";

			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "CaptainComission_408":
			AddQuestRecord("CaptainComission2", "35");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", FindMoneyString(sti(pchar.GenQuest.CaptainComission.GoodsPrice)));
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		// Генератор "Операция Галеон"

		// Квест "встреча в бухте" -->
		// Офицер
		case "ContraMeetManQuest_Sold_1":
			dialog.text = StringFromKey("GenQuests_Dialog_906");
			link.l1 = StringFromKey("GenQuests_Dialog_907");
			link.l1.go = "ContraMeetManQuest_Sold_2";
		break;

		case "ContraMeetManQuest_Sold_2":
			dialog.text = StringFromKey("GenQuests_Dialog_908", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_909");
			link.l1.go = "ContraMeetManQuest_Sold_3";
		break;

		case "ContraMeetManQuest_Sold_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteQuestCondition("ContraMeetManQuest_TimeIsLeft"); // Время больше не роляет
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "8");
			PChar.GenQuest.ContraMeetMan.ToTavernPatrolInShore = true;
			LAi_CharacterDisableDialog(NPChar);
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			ContraMeetManQuest_DeletePatrolFromShore(); // По выходу потрем всех из локации
		break;

		// Сам чел
		case "ContraMeetManQuest_1":
			dialog.text = StringFromKey("GenQuests_Dialog_910");
			link.l1 = StringFromKey("GenQuests_Dialog_911");
			link.l1.go = "ContraMeetManQuest_2";
		break;

		case "ContraMeetManQuest_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(NPChar);
			LAi_ActorFollowEverywhere(NPChar, "", -1);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "3");
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat")); //TODO: падежи
			PChar.GenQuest.ContraMeetMan.ToTavernWithMan = true;
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
		break;

		// Контрики в комнате таверны	
		case "ContraMeetManQuest_3":
			ContraMeetManQuest_ContersGoQut();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "4");
			AddQuestUserData(sQuestTitle, "sMoney", FindMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ChangeContrabandRelation(PChar, 5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
		break;

		case "ContraMeetManQuest_4":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "5");
			AddQuestUserData(sQuestTitle, "sMoney", FindMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContraBeatMan();
			ChangeContrabandRelation(PChar, 5);
			ChangeCharacterReputation(PChar, -5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
		break;

		case "ContraMeetManQuest_5":
			dialog.text = StringFromKey("GenQuests_Dialog_912", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_913");
			link.l1.go = "ContraMeetManQuest_6";
		break;

		case "ContraMeetManQuest_6":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraMeetManQuest_PlayerBeatContra();
		break;

		case "ContraMeetManQuest_7":
			dialog.text = StringFromKey("GenQuests_Dialog_914", PChar.name);
			link.l1 = "...";
			link.l1.go = "ContraMeetManQuest_9";
		break;

		case "ContraMeetManQuest_8":
			iMoney = (rand(3) + 2) * 500;
			PChar.GenQuest.ContraMeetMan.Money = iMoney;
			dialog.text = StringFromKey("GenQuests_Dialog_915", FindMoneyString(iMoney));
			link.l1 = StringFromKey("GenQuests_Dialog_916");
			link.l1.go = "ContraMeetManQuest_10";
		break;

		case "ContraMeetManQuest_9":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ChangeCharacterReputation(PChar, 10);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "6");
			AddQuestUserData(sQuestTitle, "sMoney", FindMoneyString(iMoney));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat")); //TODO: падежи
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
		break;

		case "ContraMeetManQuest_10":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "7");
			AddQuestUserData(sQuestTitle, "sMoney", FindMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat")); //TODO: падежи
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
		break;
		// <-- Квест "встреча в бухте"

		// Квест на доставку письма контрику -->
		case "ContraDeliverQuest_Sold1":
			dialog.text = StringFromKey("GenQuests_Dialog_917");
			//if(80 > rand(100) || sti(PChar.skill.Fortune) > rand(100)) // Попытка отмазаться
			//{
			link.l1 = StringFromKey("GenQuests_Dialog_918");
			link.l1.go = "ContraDeliverQuest_Sold2_Liberty";
		//}
		/*else // Тюрьма
		{
			link.l1 = "";
			link.l1.go = "ContraDeliverQuest_Sold2_Prison";
		}*/
		break;

		case "ContraDeliverQuest_Sold2_Liberty":
			dialog.text = StringFromKey("GenQuests_Dialog_919");
			link.l1 = StringFromKey("GenQuests_Dialog_920");
			link.l1.go = "ContraDeliverQuest_Sold2_Liberty1";
		break;

		case "ContraDeliverQuest_Sold2_Liberty1":
			dialog.text = StringFromKey("GenQuests_Dialog_921");
			link.l1 = StringFromKey("GenQuests_Dialog_922");
			link.l1.go = "ContraDeliverQuest_Sold2_Liberty2";
		break;

		case "ContraDeliverQuest_Sold2_Liberty2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraDeliverQuest_SoldiersGoOut();
		break;

		case "ContraDeliverQuest_1":
			iMoney = (rand(3) + 2) * 500;
			if (rand(1) == 0) // Денег не даёт
			{
				dialog.text = StringFromKey("GenQuests_Dialog_923");
				link.l1 = StringFromKey("GenQuests_Dialog_924");
				link.l1.go = "ContraDeliverQuest_NoMon";
			}
			else // Деньги или патруль
			{
				if (rand(2) == 1) // Патруль
				{
					dialog.text = StringFromKey("GenQuests_Dialog_925");
					link.l1 = StringFromKey("GenQuests_Dialog_926");
					link.l1.go = "ContraDeliverQuest_Patrol";
				}
				else // Просто отдает деньги
				{
					dialog.text = StringFromKey("GenQuests_Dialog_927", FindMoneyString(iMoney));
					link.l1 = StringFromKey("GenQuests_Dialog_928");
					link.l1.go = "ContraDeliverQuest_GoWithMoney";
					PChar.GenQuest.ContraDeliver.Money = iMoney;
				}
			}

			ChangeContrabandRelation(PChar, 5); // Письмо доставили - повышаем отношение у контриков
			ChangeCharacterReputation(PChar, -5); // Помогли контрикам - репу понижаем
			rChar = &Characters[GetCharacterIndex(Locations[FindLocation(PChar.location)].townsack + "_Smuggler")];
			SaveCurrentNpcQuestDateParam(rChar, "work_date");
		break;

		case "ContraDeliverQuest_Patrol":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_LocationFightDisable(LoadedLocation, true); // Чтоб не поубивали кого-нить
			ContraDeliverQuest_GeneratePatrolToRoom();
		break;

		case "ContraDeliverQuest_NoMon":
			dialog.text = StringFromKey("GenQuests_Dialog_929");
			link.l1 = StringFromKey("GenQuests_Dialog_930");
			link.l1.go = "ContraDeliverQuest_GoWithoutMoney";
			link.l2 = StringFromKey("GenQuests_Dialog_931", RandSwear());
			link.l2.go = "ContraDeliverQuest_PrepareToFight";
		break;

		case "ContraDeliverQuest_GoWithoutMoney": // Уходим без денег
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			PChar.GenQuest.ContraDeliver.Complete.WithoutMoney = true;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "4");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ContraDeliver.QuestTown));
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
		break;

		case "ContraDeliverQuest_PrepareToFight":
			dialog.text = StringFromKey("GenQuests_Dialog_932", pchar);
			link.l1 = "...";
			link.l1.go = "ContraDeliverQuest_Fight";
		break;

		case "ContraDeliverQuest_Fight": // Бой
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetImmortal(NPChar, false);
			LAi_ActorAttack(NPChar, PChar, "");
			LAi_SetFightMode(PChar, true);
			SetFunctionNPCDeathCondition("ContraDeliverQuest_ContraIsDead", NPChar.ID, false);
		break;

		case "ContraDeliverQuest_GoWithMoney": // Уходим с деньгами
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraDeliver.Money));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "3");
			AddQuestUserData(sQuestTitle, "sMoney", FindMoneyString(sti(PChar.GenQuest.ContraDeliver.Money)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ContraDeliver"); // Квест пройден - атрибуды потрем
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
		break;
		// <-- Квест на доставку письма контрику

		// Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем -->
		case "ChurchGenQuest_1_DeckDialog_1":
			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap"))
			{
				if (CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern")) // Если ждёт в таверне
				{
					dialog.text = StringFromKey("GenQuests_Dialog_935", RandPhraseSimple(
								StringFromKey("GenQuests_Dialog_933"),
								StringFromKey("GenQuests_Dialog_934")));
					link.l1 = StringFromKey("GenQuests_Dialog_936", GetFullname(NPChar));
					link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_2";
					PChar.Quest.Church_GenQuest1_Timer.over = "yes";
				}
				else // на палубе своего шипа
				{
					if (!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
					{
						dialog.text = StringFromKey("GenQuests_Dialog_937");
						link.l1 = StringFromKey("GenQuests_Dialog_938", GetFullName(NPChar), PChar.name);
						link.l1.go = "ChurchGenQuest1_DialogShip_1";
					}
					else
					{
						dialog.text = StringFromKey("GenQuests_Dialog_942", LinkRandPhrase(
									StringFromKey("GenQuests_Dialog_939"),
									StringFromKey("GenQuests_Dialog_940"),
									StringFromKey("GenQuests_Dialog_941")));
						link.l1 = StringFromKey("GenQuests_Dialog_943");
						link.l1.go = "exit";
					}
				}
			}
			else
			{
				dialog.text = StringFromKey("GenQuests_Dialog_946", RandPhraseSimple(
							StringFromKey("GenQuests_Dialog_944"),
							StringFromKey("GenQuests_Dialog_945")));
				link.l1 = StringFromKey("GenQuests_Dialog_947");
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "ChurchGenQuest_1_DeckDialog_1";
		break;

		case "ChurchGenQuest1_DialogInTavernWithCap_2":
			dialog.text = StringFromKey("GenQuests_Dialog_950", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_948"),
						StringFromKey("GenQuests_Dialog_949")));
			link.l1 = StringFromKey("GenQuests_Dialog_951", pchar);
			link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_3";
		break;

		case "ChurchGenQuest1_DialogInTavernWithCap_3":
			dialog.text = StringFromKey("GenQuests_Dialog_952");
			link.l1 = StringFromKey("GenQuests_Dialog_953", pchar);
			link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_4";
		break;

		case "ChurchGenQuest1_DialogInTavernWithCap_4":
			dialog.text = StringFromKey("GenQuests_Dialog_954", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_955");
			link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_5";
		break;

		case "ChurchGenQuest1_DialogInTavernWithCap_5":
			dialog.text = StringFromKey("GenQuests_Dialog_956", PChar.GenQuest.ChurchQuest_1.ToName, XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			link.l1 = StringFromKey("GenQuests_Dialog_957", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen"));
			link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_6";
		break;

		case "ChurchGenQuest1_DialogInTavernWithCap_6":
			dialog.text = StringFromKey("GenQuests_Dialog_958");
			link.l1 = StringFromKey("GenQuests_Dialog_959", pchar, XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_7";
		break;

		case "ChurchGenQuest1_DialogInTavernWithCap_7":
			dialog.text = StringFromKey("GenQuests_Dialog_960");
			link.l1 = StringFromKey("GenQuests_Dialog_961");
			link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_8";
		break;

		case "ChurchGenQuest1_DialogInTavernWithCap_8":
			DialogExit();
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap");
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithBarmen = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7_2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			NextDiag.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
		break;

		case "ChurchGenQuest1_DialogShip_1":
			dialog.text = StringFromKey("GenQuests_Dialog_962", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_963", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Pre"), PChar.GenQuest.ChurchQuest_1.ToName, XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			link.l1.go = "ChurchGenQuest1_DialogShip_2";
		break;

		case "ChurchGenQuest1_DialogShip_2":
			dialog.text = StringFromKey("GenQuests_Dialog_964");
			link.l1 = StringFromKey("GenQuests_Dialog_965", pchar, XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Pre"));
			link.l1.go = "ChurchGenQuest1_DialogShip_3";
		break;

		case "ChurchGenQuest1_DialogShip_3":
			dialog.text = StringFromKey("GenQuests_Dialog_966");
			link.l1 = StringFromKey("GenQuests_Dialog_967", pchar, PChar.GenQuest.ChurchQuest_1.ToName, XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			link.l1.go = "ChurchGenQuest1_DialogShip_4";
		break;

		case "ChurchGenQuest1_DialogShip_4":
			if (rand(3) != 1)
			{
				dialog.text = StringFromKey("GenQuests_Dialog_968", pchar);
				link.l1 = StringFromKey("GenQuests_Dialog_969");
				link.l1.go = "ChurchGenQuest1_DialogShip_5_1";
			}
			else // Свитки не отдает
			{
				dialog.text = StringFromKey("GenQuests_Dialog_970", pchar, XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown), NPChar.name);
				link.l1 = StringFromKey("GenQuests_Dialog_971");
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2";
			}
		break;

		case "ChurchGenQuest1_DialogShip_5_1":
			DialogExit();
			AddItems(PChar, "ChurchManuscript", 1);    // Даем рукописи
			items[FindItem("ChurchManuscript")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "а"));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
		break;

		case "ChurchGenQuest1_DialogShip_5_2":
			dialog.text = StringFromKey("GenQuests_Dialog_972", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			//			link.l1 = "Что ж. Вы человек ответственный, но это Ваша единственная приятная чёрта. Всего хорошего, мой нелюбезный друг.";
			//			link.l1.go = "ChurchGenQuest1_DialogShip_5_2_1"; // Сваливаем, поверили ему
			link.l2 = StringFromKey("GenQuests_Dialog_973", pchar);
			link.l2.go = "ChurchGenQuest1_DialogShip_5_2_2"; // 
		break;

		case "ChurchGenQuest1_DialogShip_5_2_1":
			DialogExit();
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "11");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete.NoManuscripts = true; // Квест выполнен без манускриптов
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
		break;

		case "ChurchGenQuest1_DialogShip_5_2_2":
			dialog.text = StringFromKey("GenQuests_Dialog_974", PChar.name);
			link.l1 = StringFromKey("GenQuests_Dialog_975", pchar);
			link.l1.go = "ChurchGenQuest1_DialogShip_5_2_3"; // Сваливаем, поверили ему
		break;

		case "ChurchGenQuest1_DialogShip_5_2_3":
			DialogExit();
			AddItems(PChar, "ChurchManuscript", 1);    // Даем рукописи
			items[FindItem("ChurchManuscript")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "а"));
			AddQuestUserData(sQuestTitle, "sIsland", XI_ConvertString(GetIslandNameByCity(PChar.GenQuest.ChurchQuest_1.QuestTown) + "Dat"));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
		break;

		// <-- Церковный генератор. Квест № 1. Диалог кэпа, которого ищем

		case "Left_Time_Case":
			dialog.text = StringFromKey("GenQuests_Dialog_978", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_976"),
						StringFromKey("GenQuests_Dialog_977")));
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Left_Time_Case";
		break;

		case "Church_GenQuest_2_1":
		// evganat - возвращаю развилку
			if (!CheckAttribute(PChar, "GenQuest.ChurchQuest_2.WayOfShortVariant"))
			{
				dialog.text = StringFromKey("GenQuests_Dialog_979", pchar);
				Link.l1 = StringFromKey("GenQuests_Dialog_980");
				Link.l1.go = "exit";
				LAi_LocationFightDisable(LoadedLocation, false);
				AddDialogExitQuest("Church_GenQuest2_AskedBand");
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
				break;
			}
			if (sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 1)
			{
				dialog.text = StringFromKey("GenQuests_Dialog_981", RandSwear());
			}

			if (sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 2)
			{
				dialog.text = StringFromKey("GenQuests_Dialog_982", RandSwear());
			}

			if (sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) > 2)
			{
				dialog.text = StringFromKey("GenQuests_Dialog_983", RandSwear());
			}

			link.l1 = StringFromKey("GenQuests_Dialog_984");
			link.l1.go = "exit";
			NPChar.money = sti(PChar.GenQuest.ChurchQuest_2.MoneyCount);
			LAi_LocationFightDisable(LoadedLocation, false);
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
		break;

		case "Church_GenQuest_2_ShoreBandit_1":
			dialog.text = StringFromKey("GenQuests_Dialog_985");
			link.l1 = StringFromKey("GenQuests_Dialog_986");
			link.l1.go = "Church_GenQuest_2_ShoreBandit_2";
			LAi_LocationFightDisable(LoadedLocation, false);
		break;

		case "Church_GenQuest_2_ShoreBandit_2":
			dialog.text = StringFromKey("GenQuests_Dialog_987");
			link.l1 = StringFromKey("GenQuests_Dialog_988", pchar);
			link.l1.go = "Church_GenQuest_2_ShoreBandit_3";
		break;

		case "Church_GenQuest_2_ShoreBandit_3":
			if (rand(1) == 0)
			{
				dialog.text = StringFromKey("GenQuests_Dialog_989", pchar);
				link.l1 = StringFromKey("GenQuests_Dialog_990", pchar, XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen"));
				link.l1.go = "Church_GenQuest_2_ShoreBandit_4";
				break;
			}

			dialog.text = StringFromKey("GenQuests_Dialog_991", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_992", pchar, XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen"));
			link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_1";
		break;

		case "Church_GenQuest_2_ShoreBandit_4":
			dialog.text = StringFromKey("GenQuests_Dialog_993", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_994");
			link.l1.go = "Church_GenQuest_2_ShoreBandit_5";
		break;

		case "Church_GenQuest_2_ShoreBandit_5":
			dialog.text = StringFromKey("GenQuests_Dialog_995", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_996");
			link.l1.go = "Church_GenQuest_2_ShoreBandit_6";
		break;

		case "Church_GenQuest_2_ShoreBandit_6":
			dialog.text = StringFromKey("GenQuests_Dialog_997");
			link.l1 = StringFromKey("GenQuests_Dialog_998", pchar);
			link.l1.go = "Church_GenQuest_2_ShoreBandit_7";
			link.l2 = StringFromKey("GenQuests_Dialog_999", pchar);
			link.l2.go = "Church_GenQuest_2_ShoreBandit_8";
			// Тут давать чашу, если будет
			ChurchGenQuest2_GiveCup();
			PChar.GenQuest.ChurchQuest_2.Complete.PriestIsThief = true;
		break;

		case "Church_GenQuest_2_ShoreBandit_7":
			NextDiag.CurrentNode = NextDiag.TempNode;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for (i = 0; i < iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
				LAi_ActorRunToLocation(rChar, "reload", "reload1_back", "none", "", "", "", -1);
			}

			// Разрешим генерацию энкаунтеров, откроем выходы
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;

			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_1");
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName);
			DialogExit();
		break;

		case "Church_GenQuest_2_ShoreBandit_8":
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_2");
			AddQuestUserData("ChurchGenQuest2", "sSex", GetSexPhrase("", "а"));
			DialogExit();
		break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_1":
			if (PChar.GenQuest.ChurchQuest_2.BanditsCount == 1)
			{
				dialog.text = StringFromKey("GenQuests_Dialog_1000", RandSwear());
			}
			else
			{
				dialog.text = StringFromKey("GenQuests_Dialog_1001", RandSwear());
			}
			link.l1 = StringFromKey("GenQuests_Dialog_1002");
			link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2";
		break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2":
			dialog.text = StringFromKey("GenQuests_Dialog_1003");
			link.l1 = StringFromKey("GenQuests_Dialog_1004");
			link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_1";
			link.l2 = StringFromKey("GenQuests_Dialog_1005");
			link.l2.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_2";
			link.l3 = StringFromKey("GenQuests_Dialog_1006");
			link.l3.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3";
		break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_1":
		// Не забыть чашу!
			rItem = ItemsFromID("ChurchCup");
			rItem.City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen");
			GiveItem2Character(npchar, "ChurchCup");
			PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
			NPChar.money = ((rand(3) + 6) * 1000);
			PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ёл", "ла"));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("", "а"));
			DialogExit();
		break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_2":
			AddMoneyToCharacter(PChar, -sti(PChar.money) / 2); // Забираем половину денег
			PChar.GenQuest.ChurchQuest_2.Complete.Without_All = true; // Полностью проигрышный вариант. Остаемся ни с чем
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for (i = 0; i < iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "First time";
			}

			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "11_2");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "а"));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("ся", "ась"));
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3":
			iMoney = makeint(makeint(Pchar.money) / 20) * 10;
			dialog.text = StringFromKey("GenQuests_Dialog_1007", GetAddress_Form(pchar));
			if (iMoney >= makeint(Pchar.rank) * 300)
			{
				link.l1 = StringFromKey("GenQuests_Dialog_1008", FindMoneyString(iMoney));
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1";
			}
			else
			{
				link.l1 = StringFromKey("GenQuests_Dialog_1009", pchar);
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2";
			}
		break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_GiveCup();    // Даем чашу
			AddMoneyToCharacter(PChar, -(makeint(makeint(Pchar.money) / 20) * 10));
			PChar.GenQuest.ChurchQuest_2.Complete.Only_With_Cup = true;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for (i = 0; i < iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "Left_Time_Case"; // Диалог не забыть поменять.
			}

			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_3");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "а"));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			DialogExit();
		break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2":
			dialog.text = StringFromKey("GenQuests_Dialog_1010", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_1011", pchar);
			link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3";
		break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3":
			dialog.text = StringFromKey("GenQuests_Dialog_1012", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_1013");
			link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4";
		break;

		// Можно этот кэйс - Church_GenQuest_2_ShoreBandit_Real_Band_2_1
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4":
		// ГГ как-бы может обыскать трупики и забрать все барахло...
			rItem = ItemsFromID("ChurchCup");
			rItem.City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen");
			GiveItem2Character(npchar, "ChurchCup");
			PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
			NPChar.money = ((rand(3) + 6) * 1000);
			PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase(StringFromKey("SexPhrase_9"), StringFromKey("SexPhrase_10")));
			DialogExit();
		break;

		///////////////////////////////////////////////////////////////////////////////////////////////////
		// ГЕНЕР "ПИРАТЫ НА НЕОБИТАЕМОМ ОСТРОВЕ"
		///////////////////////////////////////////////////////////////////////////////////////////////////

		case "PiratesOnUninhabited_1":
			dialog.text = StringFromKey("GenQuests_Dialog_1014");
			link.l1 = StringFromKey("GenQuests_Dialog_1015");
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "PiratesOnUninhabited_2":
			for (i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				LAi_SetImmortal(CharacterFromID("PirateOnUninhabited_" + i), false);
			}

			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			DialogExit();
		break;

		case "PiratesOnUninhabited_3":
			PChar.GenQuest.PiratesOnUninhabited.MainPirateName = GetRandName(NAMETYPE_NICK, NAME_GEN);
			PChar.GenQuest.PiratesOnUninhabited.BadPirateName = GetRandName(NAMETYPE_ORIG, NAME_NOM);

			i = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.PiratesOnUninhabited.StartShipType = i;

			if (dRand(1) == 0)
			{
				PChar.GenQuest.PiratesOnUninhabited.Shipwrecked = true;

				dialog.text = StringFromKey("GenQuests_Dialog_1016", PChar.GenQuest.PiratesOnUninhabited.MainPirateName, GetStrSmallRegister(XI_ConvertString(ShipsTypes[i].Name)), dRand(7) + 1);
				link.l1 = StringFromKey("GenQuests_Dialog_1023", RandPhraseSimple(
							StringFromKey("GenQuests_Dialog_1019", RandPhraseSimple(
									StringFromKey("GenQuests_Dialog_1017"),
									StringFromKey("GenQuests_Dialog_1018"))),
							StringFromKey("GenQuests_Dialog_1022", RandPhraseSimple(
									StringFromKey("GenQuests_Dialog_1020"),
									StringFromKey("GenQuests_Dialog_1021")))));
				link.l1.go = "PiratesOnUninhabited_4";
			}
			else
			{
				dialog.text = StringFromKey("GenQuests_Dialog_1024", PChar.GenQuest.PiratesOnUninhabited.BadPirateName, ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC));
				link.l1 = StringFromKey("GenQuests_Dialog_1027", RandPhraseSimple(
							StringFromKey("GenQuests_Dialog_1025"),
							StringFromKey("GenQuests_Dialog_1026", pchar)));
				link.l1.go = "PiratesOnUninhabited_41";
			}
		break;

		case "PiratesOnUninhabited_4":
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = 5 + dRand(5);

			dialog.text = StringFromKey("GenQuests_Dialog_1030", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_1028", PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))),
						StringFromKey("GenQuests_Dialog_1029", PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount)))));

			if (GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l1 = StringFromKey("GenQuests_Dialog_1031");
				link.l1.go = "PiratesOnUninhabited_5";
			}

			link.l2 = StringFromKey("GenQuests_Dialog_1038", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_1034", RandPhraseSimple(
								StringFromKey("GenQuests_Dialog_1032"),
								StringFromKey("GenQuests_Dialog_1033"))),
						StringFromKey("GenQuests_Dialog_1037", RandPhraseSimple(
								StringFromKey("GenQuests_Dialog_1035"),
								StringFromKey("GenQuests_Dialog_1036", pchar)))));
			link.l2.go = "PiratesOnUninhabited_21";

			if (stf(PChar.reputation) <= REPUTATION_NEUTRAL)
			{
				link.l3 = StringFromKey("GenQuests_Dialog_1039");
				link.l3.go = "PiratesOnUninhabited_7";
			}
		break;

		case "PiratesOnUninhabited_5":
			dialog.text = StringFromKey("GenQuests_Dialog_1040");
			link.l1 = StringFromKey("GenQuests_Dialog_1041");
			link.l1.go = "PiratesOnUninhabited_10";
			link.l2 = StringFromKey("GenQuests_Dialog_1042");
			link.l2.go = "PiratesOnUninhabited_6";
		break;

		case "PiratesOnUninhabited_6":
			dialog.text = StringFromKey("GenQuests_Dialog_1043");
			link.l1 = StringFromKey("GenQuests_Dialog_1044");
			link.l1.go = "PiratesOnUninhabited_7";
			link.l2 = StringFromKey("GenQuests_Dialog_1045");
			link.l2.go = "PiratesOnUninhabited_8";
		break;

		case "PiratesOnUninhabited_7":
			dialog.text = StringFromKey("GenQuests_Dialog_1046");
			link.l1 = StringFromKey("GenQuests_Dialog_1047");
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterReputation(PChar, -3.0);
		break;

		// Берем их в команду
		case "PiratesOnUninhabited_8":
			dialog.text = StringFromKey("GenQuests_Dialog_1048");
			link.l1 = StringFromKey("GenQuests_Dialog_1049");
			link.l1.go = "PiratesOnUninhabited_9";
		break;

		case "PiratesOnUninhabited_9":
			bOk = CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked");

			for (i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				//rChar.LifeDay = 0;
				rChar.location = "none"; // Убираем из локации при выходе
				rChar.location.locator = ""; // лесник

				if (bOk)
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				}
				else
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_43_again";
				}
			}

			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount));

			Log_Info(StringFromKey("InfoMessages_148", FindPeoplesString(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount), "Acc")));
			OfficersReaction("bad");

			//PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации

			//DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");

			DialogExit();
		break;

		case "PiratesOnUninhabited_10":
			dialog.text = StringFromKey("GenQuests_Dialog_1050");
			link.l1 = StringFromKey("GenQuests_Dialog_1051");
			link.l1.go = "PiratesOnUninhabited_11";
		break;

		// Берем их в пассажирами - держать курс на населенный остров
		case "PiratesOnUninhabited_11":
			for (i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
			}

			Log_Info(StringFromKey("InfoMessages_148", FindPeoplesString(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount), "Acc")));

			ChangeCharacterReputation(PChar, 3.0);

			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			OfficersReaction("good");
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации

			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);

			sTemp = XI_ConvertString(PChar.location + "Gen");

			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);

			if (!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.TreasureMap"))
			{
				if (CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked"))
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "1");
					AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen")));
					// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины
					if (ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
					{
						AddQuestUserData(sTitle, "sText", StringFromKey("GenQuests_Dialog_1202"));
					}
					else
					{
						AddQuestUserData(sTitle, "sText", StringFromKey("GenQuests_Dialog_1203"));
					}
					// <-- belamour gen
				}
				else
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "11");
					AddQuestUserData(sTitle, "pirateName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_INS));
				}
			}
			else
			{
				AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "5");
				AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
				// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины
				if (ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData(sTitle, "sText", StringFromKey("GenQuests_Dialog_1202"));
				}
				else
				{
					AddQuestUserData(sTitle, "sText", StringFromKey("GenQuests_Dialog_1203"));
				}
				// <-- belamour gen
			}

			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);

			AddQuestUserData(sTitle, "count",  FindSailorString(sti(pchar.GenQuest.PiratesOnUninhabited.PiratesCount), "No"));

			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;

			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1.location = PChar.location;
			PChar.Quest.PiratesOnUninhabited_LocExitGood.function = "PiratesOnUninhabited_LocationExit_Good";

			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1.location_type = "seashore";
			PChar.Quest.PiratesOnUninhabited_OnShore.again = true;
			PChar.Quest.PiratesOnUninhabited_OnShore.function = "PiratesOnUninhabited_OnShore";

			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1.location_type = "mayak";
			PChar.Quest.PiratesOnUninhabited_OnMayak.again = true;
			PChar.Quest.PiratesOnUninhabited_OnMayak.function = "PiratesOnUninhabited_OnShore";

			DialogExit();
		break;

		case "PiratesOnUninhabited_11_Again":
			dialog.text = StringFromKey("GenQuests_Dialog_1055", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_1052"),
						StringFromKey("GenQuests_Dialog_1053"),
						StringFromKey("GenQuests_Dialog_1054")));
			link.l1 = StringFromKey("GenQuests_Dialog_1056");
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_11_Again";
		break;

		// Базар с главарем уже в другой бухте на обитаемом острове
		case "PiratesOnUninhabited_12":
			if (dRand(1) == 0)
			{
				// Успешное завершение квеста - даст награду
				dialog.text = StringFromKey("GenQuests_Dialog_1057");
				link.l1 = StringFromKey("GenQuests_Dialog_1058", pchar);
				link.l1.go = "PiratesOnUninhabited_13";
			}
			else
			{
				// Требуют денег
				dialog.text = StringFromKey("GenQuests_Dialog_1059");
				link.l1 = StringFromKey("GenQuests_Dialog_1060");
				link.l1.go = "PiratesOnUninhabited_15";
				link.l2 = StringFromKey("GenQuests_Dialog_1061");
				link.l2.go = "PiratesOnUninhabited_17";
			}

			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;

		case "PiratesOnUninhabited_13":
			AddItems(PChar, "jewelry4", 1);

			for (i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;

				rChar.Dialog.currentnode = "PiratesOnUninhabited_14";
			}

			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "2");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("", "а"));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen")));
			CloseQuestHeader(sTitle);

			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");

			DialogExit();
		break;

		case "PiratesOnUninhabited_14":
			dialog.text = StringFromKey("GenQuests_Dialog_1065", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_1062"),
						StringFromKey("GenQuests_Dialog_1063"),
						StringFromKey("GenQuests_Dialog_1064", PChar.name)));
			link.l1 = StringFromKey("GenQuests_Dialog_1066");
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_14";
		break;

		case "PiratesOnUninhabited_15":
			dialog.text = StringFromKey("GenQuests_Dialog_1067");
			link.l1 = StringFromKey("GenQuests_Dialog_1068");
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterReputation(PChar, 2.0);
		break;

		case "PiratesOnUninhabited_16":
			for (i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);

				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}

			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);

			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "3");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("", "а"));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen")));
			CloseQuestHeader(sTitle);

			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");

			DialogExit();
		break;

		case "PiratesOnUninhabited_17":
			iMoney = sti(PChar.rank) * 500;
			PChar.GenQuest.PiratesOnUninhabited.Money = iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);

			dialog.text = StringFromKey("GenQuests_Dialog_1069", FindMoneyString(iMoney));
			link.l1 = StringFromKey("GenQuests_Dialog_1072", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_1070"),
						StringFromKey("GenQuests_Dialog_1071", pchar)));
			link.l1.go = "PiratesOnUninhabited_18";

			if (sti(PChar.money) >= iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				link.l2 = StringFromKey("GenQuests_Dialog_1073", pchar);
				link.l2.go = "PiratesOnUninhabited_19";
			}
		break;

		case "PiratesOnUninhabited_18":
			dialog.text = StringFromKey("GenQuests_Dialog_1074");
			link.l1 = StringFromKey("GenQuests_Dialog_1075");
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "PiratesOnUninhabited_19":
			dialog.text = StringFromKey("GenQuests_Dialog_1076");
			link.l1 = StringFromKey("GenQuests_Dialog_1077");
			link.l1.go = "PiratesOnUninhabited_20";

			iMoney = sti(PChar.GenQuest.PiratesOnUninhabited.Money);

			AddMoneyToCharacter(PChar, -iMoney);
			AddMoneyToCharacter(NPChar, iMoney);
		break;

		case "PiratesOnUninhabited_20":
			for (i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);

				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_CharacterDisableDialog(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}

			ChangeCharacterReputation(PChar, 2.0);
			OfficersReaction("good");

			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("", "а"));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("ся", "ась"));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen")));
			CloseQuestHeader(sTitle);

			NPChar.SaveItemsForDead = true; // сохранять на трупе вещи
			NPChar.DontClearDead = true;  // не убирать труп через 200с

			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");

			DialogExit();
		break;

		case "PiratesOnUninhabited_21":
			if (GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				// Игрок врет - свободное место есть
				dialog.text = StringFromKey("GenQuests_Dialog_1078");
				link.l1 = StringFromKey("GenQuests_Dialog_1079");
				link.l1.go = "PiratesOnUninhabited_23";
			}
			else
			{
				dialog.text = StringFromKey("GenQuests_Dialog_1080");
				link.l1 = StringFromKey("GenQuests_Dialog_1081");
				link.l1.go = "PiratesOnUninhabited_22";
			}
		break;

		case "PiratesOnUninhabited_22":
			dialog.text = StringFromKey("GenQuests_Dialog_1082");
			link.l1 = StringFromKey("GenQuests_Dialog_1083");
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "PiratesOnUninhabited_23":
			dialog.text = StringFromKey("GenQuests_Dialog_1084");
			link.l1 = StringFromKey("GenQuests_Dialog_1085");
			link.l1.go = "PiratesOnUninhabited_25";
			link.l2 = StringFromKey("GenQuests_Dialog_1086", pchar);
			link.l2.go = "PiratesOnUninhabited_24";
		break;

		case "PiratesOnUninhabited_24":
			dialog.text = StringFromKey("GenQuests_Dialog_1087");
			link.l1 = StringFromKey("GenQuests_Dialog_1088");
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "PiratesOnUninhabited_25":
			dialog.text = StringFromKey("GenQuests_Dialog_1089");
			link.l1 = StringFromKey("GenQuests_Dialog_1090");
			link.l1.go = "PiratesOnUninhabited_11";
			PChar.GenQuest.PiratesOnUninhabited.TreasureMap = true;
		break;

		// Базар с главарем уже в другой бухте на обитаемом острове. Вариант, когда нам обещали карту сокровищ
		case "PiratesOnUninhabited_26":
		// PChar.GenQuest.PiratesOnUninhabited.MainPirateName - имя в родительном падеже

			dialog.text = StringFromKey("GenQuests_Dialog_1091", pchar, PChar.name, ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_DAT));
			link.l1 = StringFromKey("GenQuests_Dialog_1092");
			link.l1.go = "PiratesOnUninhabited_27";
			link.l2 = StringFromKey("GenQuests_Dialog_1093", pchar);
			link.l2.go = "PiratesOnUninhabited_30";
			link.l3 = StringFromKey("GenQuests_Dialog_1094");
			link.l3.go = "PiratesOnUninhabited_33";

			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;

		case "PiratesOnUninhabited_27":
			dialog.text = StringFromKey("GenQuests_Dialog_1095");
			link.l1 = StringFromKey("GenQuests_Dialog_1096");
			link.l1.go = "PiratesOnUninhabited_28";
		break;

		case "PiratesOnUninhabited_28":
			dialog.text = StringFromKey("GenQuests_Dialog_1097");
			link.l1 = StringFromKey("GenQuests_Dialog_1098");
			link.l1.go = "PiratesOnUninhabited_29";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "PiratesOnUninhabited_29":
			for (i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);

				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}

			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);

			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "6");
			CloseQuestHeader(sTitle);

			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");

			DialogExit();
		break;

		case "PiratesOnUninhabited_30":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;

			dialog.text = StringFromKey("GenQuests_Dialog_1099", pchar, UpperFirst(XI_ConvertString(sTitle + "Pre")), ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_GEN));
			link.l1 = StringFromKey("GenQuests_Dialog_1100");
			link.l1.go = "PiratesOnUninhabited_28";
			link.l2 = StringFromKey("GenQuests_Dialog_1101");
			link.l2.go = "PiratesOnUninhabited_31";
		break;

		case "PiratesOnUninhabited_31":
			for (i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);

				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				rChar.Dialog.currentnode = "PiratesOnUninhabited_32";
			}

			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "7");
			AddQuestUserData(sTitle, "capName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_NOM));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.TreasureShore + "Gen")));

			// Таймер для клада. По прошествии 10 дней в кладе будут всякие бакланы и т.д.
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1 = "Timer";
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.function = "PiratesOnUninhabited_TreasureLose"; // belamour gen

			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1 = "Location";
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1.Location = PChar.GenQuest.PiratesOnUninhabited.TreasureShore;
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.function = "PiratesOnUninhabited_InTreasureLoc";

			DialogExit();

		// Курс в бухту, которую назвал пират. У нас сроку 10 дней, котом клад пропадет
		break;

		case "PiratesOnUninhabited_32":
			sTemp = ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC);

			dialog.text = StringFromKey("GenQuests_Dialog_1105", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_1102", sTemp),
						StringFromKey("GenQuests_Dialog_1103", sTemp),
						StringFromKey("GenQuests_Dialog_1104")));
			link.l1 = StringFromKey("GenQuests_Dialog_1106");
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_32";
		break;

		case "PiratesOnUninhabited_33":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;

			dialog.text = StringFromKey("GenQuests_Dialog_1107", pchar, XI_ConvertString(sTitle + "Gen"), ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_GEN)); // belamour gen
			link.l1 = StringFromKey("GenQuests_Dialog_1108");
			link.l1.go = "PiratesOnUninhabited_28";
		break;

		// Пираты в бухте с сокровищем
		case "PiratesOnUninhabited_34":
			dialog.text = StringFromKey("GenQuests_Dialog_1109", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_1110", pchar);
			link.l1.go = "PiratesOnUninhabited_35";
			link.l2 = StringFromKey("GenQuests_Dialog_1111", ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_GEN));
			link.l2.go = "PiratesOnUninhabited_38";
			NextDiag.TempNode = "PiratesOnUninhabited_34";
		break;

		case "PiratesOnUninhabited_35":
			dialog.text = StringFromKey("GenQuests_Dialog_1112", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_1113");
			link.l1.go = "exit";
			link.l2 = StringFromKey("GenQuests_Dialog_1114");
			link.l2.go = "PiratesOnUninhabited_36";
		break;

		case "PiratesOnUninhabited_36":
			dialog.text = StringFromKey("GenQuests_Dialog_1115");
			link.l1 = StringFromKey("GenQuests_Dialog_1116");
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "PiratesOnUninhabited_37":
			DialogExit();
			LAi_Group_SetRelation("PiratesOnUninhabited_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;

		case "PiratesOnUninhabited_38":
			dialog.text = StringFromKey("GenQuests_Dialog_1117");
			link.l1 = StringFromKey("GenQuests_Dialog_1118", LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Pre")));
			link.l1.go = "PiratesOnUninhabited_39";
		break;

		case "PiratesOnUninhabited_39":
			dialog.text = StringFromKey("GenQuests_Dialog_1119");
			link.l1 = StringFromKey("GenQuests_Dialog_1120");
			link.l1.go = "PiratesOnUninhabited_40";
		break;

		case "PiratesOnUninhabited_40":
			dialog.text = StringFromKey("GenQuests_Dialog_1121", LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Acc")), PChar.GenQuest.PiratesOnUninhabited.MainPirateName);
			link.l1 = StringFromKey("GenQuests_Dialog_1122");
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.GenQuest.PiratesOnUninhabited.UseMainPiratename = true;
		break;

		// Ветка из PiratesOnUninhabited_3
		case "PiratesOnUninhabited_41":
			iBanditsCount = 5 + dRand(5);
			iMoney = GetFreeCrewQuantity(PChar);

			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = iBanditsCount;

			dialog.text = StringFromKey("GenQuests_Dialog_1123", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_INS), iBanditsCount);
			link.l1 = StringFromKey("GenQuests_Dialog_1124");
			link.l1.go = "PiratesOnUninhabited_42";

			if (iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l2 = StringFromKey("GenQuests_Dialog_1125", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_GEN));
				link.l2.go = "PiratesOnUninhabited_44";
			}
		break;

		case "PiratesOnUninhabited_42":
			dialog.text = StringFromKey("GenQuests_Dialog_1126");
			link.l1 = StringFromKey("GenQuests_Dialog_1127");
			link.l1.go = "PiratesOnUninhabited_43";
		break;

		case "PiratesOnUninhabited_43":
			iBanditsCount = sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			iMoney = GetFreeCrewQuantity(PChar);

			dialog.text = StringFromKey("GenQuests_Dialog_1128");

			if (iMoney >= iBanditsCount)
			{
				link.l1 = StringFromKey("GenQuests_Dialog_1129");
				link.l1.go = "PiratesOnUninhabited_9"; // Берем в команду
			}

			link.l2 = StringFromKey("GenQuests_Dialog_1130");
			link.l2.go = "PiratesOnUninhabited_24"; // Рубилово и конец квеста

			if (iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l3 = StringFromKey("GenQuests_Dialog_1131");
				link.l3.go = "PiratesOnUninhabited_11"; // В пассажиры и на остров
			}
		break;

		case "PiratesOnUninhabited_43_again":
			dialog.text = StringFromKey("GenQuests_Dialog_1135", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_1132"),
						StringFromKey("GenQuests_Dialog_1133"),
						StringFromKey("GenQuests_Dialog_1134")));
			link.l1 = StringFromKey("GenQuests_Dialog_1138", RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_1136"),
						StringFromKey("GenQuests_Dialog_1137")));
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_43_again";
		break;

		case "PiratesOnUninhabited_44":
			sTitle = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.PiratesOnUninhabited.StartShipName = sTitle;

			dialog.text = StringFromKey("GenQuests_Dialog_1139", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Name + "Pre")), sTitle, ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC));
			link.l1 = StringFromKey("GenQuests_Dialog_1140");
			link.l1.go = "PiratesOnUninhabited_45";
		break;

		case "PiratesOnUninhabited_45":
			for (i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				rChar.location = "none"; // Убираем из локации при выходе   исправлено с NPChar на rChar - лесник
				rChar.location.locator = ""; // лесник  - так же исправлено .  тогда бага не будет.
			}

			Log_Info(StringFromKey("InfoMessages_148", FindPeoplesString(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount), "Acc")));

			ChangeCharacterReputation(PChar, 3.0);

			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);

			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации

			sTemp = XI_ConvertString(PChar.location + "Gen");

			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "13");
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "count",  FindSailorString(sti(pchar.GenQuest.PiratesOnUninhabited.PiratesCount), "No"));
			AddQuestUserData(sTitle, "badCapName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_INS));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Pre")) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");

			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;

			PiratesOnUninhabited_SetCapToMap(); // Ставим корабль на карту

			DialogExit();
		break;

		// Диалог с кэпом в каюте
		case "PiratesOnUninhabited_46":
			dialog.text = StringFromKey("GenQuests_Dialog_1141");
			link.l1 = StringFromKey("GenQuests_Dialog_1142", pchar, ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_GEN));
			link.l1.go = "PiratesOnUninhabited_47";

			PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
			PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
			Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
		break;

		case "PiratesOnUninhabited_47":
			dialog.text = StringFromKey("GenQuests_Dialog_1143");
			link.l1 = StringFromKey("GenQuests_Dialog_1144");
			link.l1.go = "PiratesOnUninhabited_48";
		break;

		case "PiratesOnUninhabited_48":
			LAi_CharacterDisableDialog(NPChar);
			LAi_Group_Attack(NPChar, Pchar);

			LAi_SetCurHPMax(NPChar);
			QuestAboardCabinDialogFree(); // важный метод

			LAi_Group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_Group_SetCheckFunction(LAI_GROUP_BRDENEMY, "PiratesOnUninhabited_CapDeath");

			AddDialogExitQuest("MainHeroFightModeOn");

			DialogExit();
		break;

		case "PiratesOnUninhabited_49":
			dialog.text = StringFromKey("GenQuests_Dialog_1145");
			link.l1 = StringFromKey("GenQuests_Dialog_1146");
			link.l1.go = "PiratesOnUninhabited_50";
		break;

		case "PiratesOnUninhabited_50":
			NPChar.LifeDay = 0;
			NPChar.location = "none"; // Убираем из каюты
			NPChar.location.locator = "";

			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);

			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "14");
			AddQuestUserData("PiratesOnUninhabited", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);

			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");

			ChangeAttributesFromCharacter(CharacterFromID("PiratesOnUninhabited_BadPirate"), NPChar, true);
			DialogExit();

		break;

		// На палубе, когда корабль с нашим пиратом отпустили
		case "PiratesOnUninhabited_50_Deck1":
			dialog.text = StringFromKey("GenQuests_Dialog_1147", PChar.name);
			link.l1 = StringFromKey("GenQuests_Dialog_1148");
			link.l1.go = "PiratesOnUninhabited_50_Deck2";
		break;

		case "PiratesOnUninhabited_50_Deck2":
			dialog.text = StringFromKey("GenQuests_Dialog_1149");
			link.l1 = StringFromKey("GenQuests_Dialog_1150");
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_50_Deck1";
		break;

		// В бухте, вариант, когда корабль, который нужно было захватить, утопили
		case "PiratesOnUninhabited_51":
			dialog.text = StringFromKey("GenQuests_Dialog_1151", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_1152", pchar);
			link.l1.go = "PiratesOnUninhabited_52";
			RemovePassenger(pchar, npchar);
		break;

		case "PiratesOnUninhabited_52":
			if (dRand(1) == 1)
			{
				dialog.text = StringFromKey("GenQuests_Dialog_1153", pchar);
				link.l1 = StringFromKey("GenQuests_Dialog_1154");
				link.l1.go = "PiratesOnUninhabited_53";
			}
			else
			{
				iMoney = sti(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Price);
				iMoney = MakeInt((iMoney / 1.2 + dRand(iMoney - (iMoney / 1.2))) * 1.2);
				dialog.text = StringFromKey("GenQuests_Dialog_1155", pchar, FindMoneyString(iMoney));
				link.l1 = StringFromKey("GenQuests_Dialog_1156", pchar);
				link.l1.go = "PiratesOnUninhabited_54";

				if (sti(PChar.money) >= iMoney)
				{
					link.l2 = StringFromKey("GenQuests_Dialog_1157");
					link.l2.go = "PiratesOnUninhabited_55";
				}
			}
		break;

		case "PiratesOnUninhabited_53":
			for (i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}

			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);

			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "15");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);

			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");

			AddDialogExitQuest("MainHeroFightModeOn");

			DialogExit();
		break;

		case "PiratesOnUninhabited_54":
			dialog.text = StringFromKey("GenQuests_Dialog_1158", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_NOM));
			link.l1 = StringFromKey("GenQuests_Dialog_1159");
			link.l1.go = "PiratesOnUninhabited_53";
		break;

		case "PiratesOnUninhabited_55":
			for (i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
			}

			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "16");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("", "а"));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);

			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");

			DialogExit();
		break;
		// КОНЕЦ

		// "Правосудие на продажу" (Warship, Rosarak)
		case "JusticeOnSale_1":
			DeleteAttribute(&TEV, "ContraRepCheck");
			dialog.text = StringFromKey("GenQuests_Dialog_1160");
			link.l1 = StringFromKey("GenQuests_Dialog_1161");
			link.l1.go = "JusticeOnSale_3";
		break;

		case "JusticeOnSale_2":
		//Снижение репутации, если ГГ напал сам
			if (CheckAttribute(&TEV, "ContraRepCheck"))
				ChangeContrabandRelation(pchar, -5);
			DeleteAttribute(&TEV, "ContraRepCheck");
			for (i = 0; i < 4; i++)
			{
				if (GetCharacterIndex("JusticeOnSale_Jungle_" + i) == -1) continue;
				sld = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_RemoveCheckMinHP(sld);
			}
			LAi_Group_SetRelation("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, true);
			DialogExit();
			LAi_SetFightMode(PChar, true);
		break;

		case "JusticeOnSale_3":
			dialog.text = StringFromKey("GenQuests_Dialog_1162", PChar.GenQuest.JusticeOnSale.SmugglerName, XI_ConvertString("Colony" + PChar.GenQuest.JusticeOnSale.CityId + "Gen"));
			link.l1 = StringFromKey("GenQuests_Dialog_1163", pchar);
			link.l1.go = "JusticeOnSale_4";
			link.l2 = StringFromKey("GenQuests_Dialog_1164");
			bOk = GetCharacterSkillToOld(Pchar, "Fencing") >= 7 && sti(Pchar.Rank) >= 10 && sti(PChar.reputation) <= 30;
			if (bOk || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				link.l2.go = "JusticeOnSale_5";
			}
			else
			{
				iTemp = makeint((
							makefloat(sti(PChar.reputation) - 41) / (100 - 41) + // репа ГГ
								(1 - (makefloat(GetPlayerContrabandRelation()) / 60)) + // репа контров
								makefloat(GetCharacterReputation_WithNation(pchar, GetCityNation(PChar.GenQuest.JusticeOnSale.CityId))) / 100) // репа с нацией города
					* 100.0
					);
				if (iTemp <= rand(35))
				{
					link.l2.go = "JusticeOnSale_5";
				}
				else
				{
					link.l2.go = "JusticeOnSale_5_1";
				}
			}
		break;

		case "JusticeOnSale_4":
			dialog.text = StringFromKey("GenQuests_Dialog_1166");
			link.l1 = StringFromKey("GenQuests_Dialog_1167");
			link.l1.go = "JusticeOnSale_6";
			link.l2 = StringFromKey("GenQuests_Dialog_1168", pchar);
			link.l2.go = "JusticeOnSale_7";
			link.l3 = StringFromKey("GenQuests_Dialog_1169");
			bOk = GetCharacterSkillToOld(Pchar, "Fencing") >= 7 && sti(Pchar.Rank) >= 10 && sti(PChar.reputation) <= 30;
			if (bOk || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				link.l3.go = "JusticeOnSale_5";
			}
			else
			{
				iTemp = makeint((
							makefloat(sti(PChar.reputation) - 41) / (100 - 41) + // репа ГГ
								(1 - (makefloat(GetPlayerContrabandRelation()) / 60)) + // репа контров
								makefloat(GetCharacterReputation_WithNation(pchar, GetCityNation(PChar.GenQuest.JusticeOnSale.CityId))) / 100) // репа с нацией города
					* 100.0
					);
				if (iTemp <= rand(35))
				{
					link.l3.go = "JusticeOnSale_5";
				}
				else
				{
					link.l3.go = "JusticeOnSale_5_1";
				}
			}
		break;

		case "JusticeOnSale_5_1":
			dialog.text = StringFromKey("GenQuests_Dialog_1173", pchar, RandPhraseSimple(
						StringFromKey("GenQuests_Dialog_1171"),
						StringFromKey("GenQuests_Dialog_1172")));
			link.l1 = StringFromKey("GenQuests_Dialog_1177", LinkRandPhrase(
						StringFromKey("GenQuests_Dialog_1174"),
						StringFromKey("GenQuests_Dialog_1175"),
						StringFromKey("GenQuests_Dialog_1176")));
			link.l1.go = "JusticeOnSale_2";
		break;

		case "JusticeOnSale_5":
			if (CheckCharacterPerk(pchar, "SeaDogProfessional"))
				PlayerRPGCheck_Perk_NotifyPass("SeaDogProfessional");
			for (i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			DialogExit();
		break;

		case "JusticeOnSale_6":
		// --> Побрякушки
		//TODO: items_update
			PChar.GenQuest.JusticeOnSale.RewardType = 0;
			sTemp = "indian1,indian3,indian5,indian6,indian7,indian10,indian12,indian14";
			PChar.GenQuest.JusticeOnSale.RewardType.Name_1 = GetRandSubString(sTemp);
			PChar.GenQuest.JusticeOnSale.RewardType.Name_2 = GetRandSubString(sTemp);
			PChar.GenQuest.JusticeOnSale.RewardType.Name_3 = GetRandSubString(sTemp);
			// <-- Побрякушки
			dialog.text = StringFromKey("GenQuests_Dialog_1178", XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Dat"), LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name)), PChar.GenQuest.JusticeOnSale.ShipName);
			link.l1 = StringFromKey("GenQuests_Dialog_1179");
			link.l1.go = "JusticeOnSale_8";
		break;

		case "JusticeOnSale_7":
			PChar.GenQuest.JusticeOnSale.RewardType = 1; // Деньги
			dialog.text = StringFromKey("GenQuests_Dialog_1180", XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Dat"), LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name)), PChar.GenQuest.JusticeOnSale.ShipName);
			link.l1 = StringFromKey("GenQuests_Dialog_1181");
			link.l1.go = "JusticeOnSale_8";
		break;

		case "JusticeOnSale_8":
			for (i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}

			ReOpenQuestHeader("JusticeOnSale");
			AddQuestRecord("JusticeOnSale", "1");
			AddQuestUserData("JusticeOnSale", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("JusticeOnSale", "cityName", XI_ConvertString("Colony" + PChar.GenQuest.JusticeOnSale.CityId + "Gen"));
			AddQuestUserData("JusticeOnSale", "Shore", XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Pre"));
			PChar.GenQuest.JusticeOnSale.MayorWait = true;
			PChar.GenQuest.JusticeOnSale.PrisonWait = true;

			//Корабль контры (Rosarak)
			iTemp = sti(PChar.rank) + MOD_SKILL_ENEMY_RATE;
			i = 3 * sti(pchar.rank) + 10;
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_ShipPirate", PChar.GenQuest.JusticeOnSale.CapModel, "man", "man", iTemp, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, iTemp, i, i, "auto", "auto", 35);
			FantomMakeSmallSailor(sld, sti(PChar.GenQuest.JusticeOnSale.ShipType), PChar.GenQuest.JusticeOnSale.ShipName, CANNON_TYPE_LBS_BY_SHIP, i + 10, i, i, i, i);
			sld.name = PChar.GenQuest.JusticeOnSale.CapName;
			sld.lastname = "";
			sld.greeting = "Gr_Smuggler Agent";
			sld.QuestFireAction = true; //Rosarak. Новый метод
			sld.dialog.filename = "Quest\GenQuests_dialog.c";
			sld.DeckDialogNode = "JusticeOnSale_ShipPirate";
			sld.AlwaysFriend = true;
			sld.AnalizeShips = true;
			sld.CrewType.Smugglers = true;
			DeleteAttribute(sld, "SinkTenPercent");
			DeleteAttribute(sld, "AboardToFinalDeck");
			Fantom_SetUpgrade(sld, "pirate");
			SetRandGeraldSail(sld, PIRATE);
			SetCharacterShipLocation(sld, PChar.GenQuest.JusticeOnSale.ShoreId);

			Group_FindOrCreateGroup("JusticeOnSaleGroup");
			Group_AddCharacter("JusticeOnSaleGroup", "JusticeOnSale_ShipPirate");
			Group_SetGroupCommander("JusticeOnSaleGroup", "JusticeOnSale_ShipPirate");
			GetNearestQuestShipLocatorByLocation(UpperFirst(PChar.GenQuest.JusticeOnSale.ShoreId));
			Group_SetTaskNone("JusticeOnSaleGroup");
			Group_LockTask("JusticeOnSaleGroup");
			SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);

			//Прерывание по времени
			iTemp = 3 + drand(2);
			PChar.Quest.JusticeOnSale_Over.win_condition.l1 = "Timer";
			PChar.Quest.JusticeOnSale_Over.win_condition.l1.date.day = GetAddingDataDay(0, 0, iTemp);
			PChar.Quest.JusticeOnSale_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
			PChar.Quest.JusticeOnSale_Over.win_condition.l1.date.year = GetAddingDataYear(0, 0, iTemp);
			PChar.Quest.JusticeOnSale_Over.function = "JusticeOnSale_Over";

			//Прерывание за потопление
			PChar.Quest.JusticeOnSale_PirateShip_Sink.win_condition.l1 = "Character_sink";
			PChar.Quest.JusticeOnSale_PirateShip_Sink.win_condition.l1.character = "JusticeOnSale_ShipPirate";
			PChar.Quest.JusticeOnSale_PirateShip_Sink.function = "JusticeOnSale_PirateShip_Sink";

			//Прерывание за абордаж
			PChar.Quest.JusticeOnSale_PirateShip_Boarding.win_condition.l1 = "Character_Capture";
			PChar.Quest.JusticeOnSale_PirateShip_Boarding.win_condition.l1.character = "JusticeOnSale_ShipPirate";
			PChar.Quest.JusticeOnSale_PirateShip_Boarding.function = "JusticeOnSale_PirateShip_Sink";
			//<-- Корабль контры (Rosarak)

			//Капитана в тюрьму (Rosarak)
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_Smuggler", PChar.GenQuest.JusticeOnSale.SmugglerModel, "man", "man", sti(PChar.rank), PIRATE, -1, true));
			SetFantomParamFromRank(sld, sti(PChar.rank) + 5, true);
			sld.name = PChar.GenQuest.JusticeOnSale.SmugglerName;
			sld.lastName = "";
			sld.dialog.filename = "Quest\GenQuests_dialog.c";
			sld.dialog.currentnode = "JusticeOnSale_Captain";
			sld.greeting = "marginal";
			RemoveAllCharacterItems(sld, true);
			ChangeCharacterAddressGroup(sld, PChar.GenQuest.JusticeOnSale.CityId + "_prison", "goto", "goto9");
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, "Prisoner_Group");

			//Прерывание на смерть
			PChar.Quest.JusticeOnSale_CaptainDeath.win_condition.l1 = "NPC_Death";
			PChar.Quest.JusticeOnSale_CaptainDeath.win_condition.l1.character = "JusticeOnSale_Smuggler";
			PChar.Quest.JusticeOnSale_CaptainDeath.function = "JusticeOnSale_CaptainDeath";

			DialogExit();
		break;

		case "JusticeOnSale_Captain":
			NextDiag.TempNode = "JusticeOnSale_Captain";
			if (NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = StringFromKey("GenQuests_Dialog_1182", pchar);
			}
			else
				dialog.text = StringFromKey("GenQuests_Dialog_1183");
			if (CheckAttribute(PChar, "GenQuest.JusticeOnSale.Persuade"))
			{
				link.l1 = StringFromKey("GenQuests_Dialog_1184", pchar, LowerFirst(XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Acc")));
				link.l1.go = "JusticeOnSale_Captain_1";
			}
			else
			{
				link.l1 = StringFromKey("GenQuests_Dialog_1185");
				link.l1.go = "JusticeOnSale_Captain_2";
			}
			link.l2 = StringFromKey("GenQuests_Dialog_1186");
			link.l2.go = "exit";
		break;

		case "JusticeOnSale_Captain_1":
			AddDialogExitQuestFunction("JusticeOnSale_CaptainPeace");
			dialog.text = StringFromKey("GenQuests_Dialog_1187", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_1188");
			link.l1.go = "exit";
		break;

		case "JusticeOnSale_Captain_2":
			AddDialogExitQuestFunction("JusticeOnSale_CaptainFight");
			dialog.text = StringFromKey("GenQuests_Dialog_1189", pchar);
			link.l1 = StringFromKey("GenQuests_Dialog_1190");
			link.l1.go = "exit";
		break;

		case "JusticeOnSale_ShipPirate":
			NextDiag.TempNode = "JusticeOnSale_ShipPirate";
			if (NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = StringFromKey("GenQuests_Dialog_1191", GetFullName(pchar));
				link.l1 = StringFromKey("GenQuests_Dialog_1192");
				link.l1.go = "exit";
				break;
			}
			dialog.text = StringFromKey("GenQuests_Dialog_1193");
			link.l1 = StringFromKey("GenQuests_Dialog_1194");
			link.l1.go = "exit";
		break;

		case "JusticeOnSale_9":
			DeleteQuestCondition("JusticeOnSale_Over");
			if (CheckAttribute(PChar, "GenQuest.JusticeOnSale.Escape"))
				sTemp = StringFromKey("GenQuests_Dialog_1195");
			else
				sTemp = StringFromKey("GenQuests_Dialog_1196");
			if (dRand(2) || CheckAttribute(PChar, "GenQuest.JusticeOnSale.Escape"))
			{
				if (sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
				{
					// Награда побрякушками
					dialog.text = StringFromKey("GenQuests_Dialog_1197", sTemp);
				}
				else
				{
					// Награда золотом
					dialog.text = StringFromKey("GenQuests_Dialog_1198", sTemp);
				}

				link.l1 = StringFromKey("GenQuests_Dialog_1199");
				link.l1.go = "JusticeOnSale_10";
			}
			else
			{
				// Резня (только при выкупе без побега)
				dialog.text = StringFromKey("GenQuests_Dialog_1200");
				link.l1 = StringFromKey("GenQuests_Dialog_1201", RandSwear());
				link.l1.go = "JusticeOnSale_11";
			}
			chrDisableReloadToLocation = false;
		break;

		case "JusticeOnSale_10":
			DialogExit();
			if (sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
			{
				//TODO: items_update
				sTemp = PChar.GenQuest.JusticeOnSale.RewardType.Name_1;
				AddItemLog(pchar, sTemp, "1", StringFromKey("InfoMessages_135", LowerFirst(GetItemName(sTemp))), "Important_item");
				if (sti(PChar.rank) > 11)
				{
					sTemp = PChar.GenQuest.JusticeOnSale.RewardType.Name_2;
					AddItemLog(pchar, sTemp, "1", StringFromKey("InfoMessages_135", LowerFirst(GetItemName(sTemp))), "Important_item");
				}
				if (CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					sTemp = PChar.GenQuest.JusticeOnSale.RewardType.Name_3;
					AddItemLog(pchar, sTemp, "1", StringFromKey("InfoMessages_135", LowerFirst(GetItemName(sTemp))), "Important_item");
				}
			}
			else
			{
				if (CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 700 + dRand(2000));
				}
				else
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 500 + dRand(1000));
				}
			}
			for (i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_ActorGoToLocation(rChar, "reload", LAi_FindNearestFreeLocator2Pchar("reload"), "none", "", "", "", 3.0);
			}
			//AddQuestRecord("JusticeOnSale", "4");
			//AddQuestUserData("JusticeOnSale", "sSex", GetSexPhrase("",StringFromKey("SexEnding_1")));
			CloseQuestHeader("JusticeOnSale");
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
		break;

		case "JusticeOnSale_11":
			AddQuestRecord("JusticeOnSale", "4_1");
			CloseQuestHeader("JusticeOnSale");
			for (i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_Group_MoveCharacter(rChar, "JusticeOnSale_ShoreGroup");
			}

			LAi_Group_SetRelation("JusticeOnSale_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
			DialogExit();

			//Удалим группу на выходе
			PChar.quest.DeleteGroupOnExitLocation.GroupName = "JusticeOnSale_ShoreGroup";
			PChar.Quest.JusticeOnSale_LocationExit.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.JusticeOnSale_LocationExit.win_condition.l1.location = PChar.location;
			PChar.Quest.JusticeOnSale_LocationExit.function = "JusticeOnSale_LocationExit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

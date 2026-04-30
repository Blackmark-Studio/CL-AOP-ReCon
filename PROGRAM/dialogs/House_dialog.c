void ProcessDialogEvent()
{
	ref NPChar, rColony;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;
	bool ok;

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

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_GoOut":
			makearef(arRld, Locations[reload_cur_location_index].reload);
			Qty = GetAttributesNum(arRld);
			for (i = 0; i < Qty; i++)
			{
				arDis = GetAttributeN(arRld, i);
				if (arDis.go == npchar.location)
				{
					arDis.disable = true; //закрываем вход в дом
					break;
				}
			}
			DoQuestFunctionDelay("HouseEnc_TimerGoUot", 10.0);
			pchar.questTemp.HouseEncTimer = pchar.location;
			pchar.questTemp.HouseEncTimer.Id = npchar.id;
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_close":
			makearef(arRld, Locations[reload_cur_location_index].reload);
			Qty = GetAttributesNum(arRld);
			for (i = 0; i < Qty; i++)
			{
				arDis = GetAttributeN(arRld, i);
				if (arDis.go == npchar.location)
				{
					arDis.disable = true; //закрываем вход в дом
					break;
				}
			}
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------------- мужик ---------------------------------
		case "HouseMan":
			NextDiag.TempNode = "HouseMan";
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = PCharRepPhrase(
							StringFromKey("House_dialog_4", LinkRandPhrase(
									StringFromKey("House_dialog_1"),
									StringFromKey("House_dialog_2"),
									StringFromKey("House_dialog_3"))),
							StringFromKey("House_dialog_8", LinkRandPhrase(
									StringFromKey("House_dialog_5", pchar),
									StringFromKey("House_dialog_6", pchar),
									StringFromKey("House_dialog_7", pchar))));
				link.l1 = PCharRepPhrase(
							StringFromKey("House_dialog_11", RandPhraseSimple(
									StringFromKey("House_dialog_9"),
									StringFromKey("House_dialog_10", XI_ConvertString("Colony" + npchar.city + "Gen")))),
							StringFromKey("House_dialog_14", RandPhraseSimple(
									StringFromKey("House_dialog_12"),
									StringFromKey("House_dialog_13"))));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = StringFromKey("House_dialog_15", pchar);
					link.l1 = StringFromKey("House_dialog_16");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("House_dialog_17", pchar);
					link.l1 = StringFromKey("House_dialog_21", LinkRandPhrase(
								StringFromKey("House_dialog_18"),
								StringFromKey("House_dialog_19"),
								StringFromKey("House_dialog_20")));
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat(
								StringFromKey("House_dialog_22"),
								StringFromKey("House_dialog_23"),
								StringFromKey("House_dialog_24"),
								StringFromKey("House_dialog_25"), "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(
								StringFromKey("House_dialog_26"),
								StringFromKey("House_dialog_27"),
								StringFromKey("House_dialog_28"),
								StringFromKey("House_dialog_29"), npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseMan_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat(
								StringFromKey("House_dialog_30"),
								StringFromKey("House_dialog_31"),
								StringFromKey("House_dialog_32"),
								StringFromKey("House_dialog_33"), "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(
								StringFromKey("House_dialog_34"),
								StringFromKey("House_dialog_35"),
								StringFromKey("House_dialog_36"),
								StringFromKey("House_dialog_37"), npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "fight", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseMan_1":
			dialog.text = StringFromKey("House_dialog_38", GetFullName(npchar));
			link.l1 = StringFromKey("House_dialog_39", GetFullName(pchar));
			link.l1.go = "exit_setOwner";
		break;
		case "Man_FackYou":
			if (CheckAttribute(loadedLocation, "packhouse")) NextDiag.TempNode = "SkladMan";
			dialog.text = StringFromKey("House_dialog_43", LinkRandPhrase(
						StringFromKey("House_dialog_40", pchar),
						StringFromKey("House_dialog_41", pchar),
						StringFromKey("House_dialog_42", pchar)));
			link.l1 = StringFromKey("House_dialog_44");
			link.l1.go = "fight";
		break;
		// --------------------------------- баба ---------------------------------
		case "HouseWoman":
			NextDiag.TempNode = "HouseWoman";
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = PCharRepPhrase(
							StringFromKey("House_dialog_48", LinkRandPhrase(
									StringFromKey("House_dialog_45"),
									StringFromKey("House_dialog_46"),
									StringFromKey("House_dialog_47"))),
							StringFromKey("House_dialog_52", LinkRandPhrase(
									StringFromKey("House_dialog_49"),
									StringFromKey("House_dialog_50"),
									StringFromKey("House_dialog_51", pchar))));
				link.l1 = PCharRepPhrase(
							StringFromKey("House_dialog_55", RandPhraseSimple(
									StringFromKey("House_dialog_53"),
									StringFromKey("House_dialog_54"))),
							StringFromKey("House_dialog_58", RandPhraseSimple(
									StringFromKey("House_dialog_56"),
									StringFromKey("House_dialog_57"))));
				link.l1.go = "exit_setOwner";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = StringFromKey("House_dialog_59");
					link.l1 = StringFromKey("House_dialog_60");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("House_dialog_61", pchar);
					link.l1 = StringFromKey("House_dialog_62");
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat(
								StringFromKey("House_dialog_63", GetFullName(npchar)),
								StringFromKey("House_dialog_64"),
								StringFromKey("House_dialog_65"),
								StringFromKey("House_dialog_66"), "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(
								StringFromKey("House_dialog_67", pchar, GetFullName(pchar)),
								StringFromKey("House_dialog_68"),
								StringFromKey("House_dialog_69"),
								StringFromKey("House_dialog_70"), npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseWoman_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat(
								StringFromKey("House_dialog_71"),
								StringFromKey("House_dialog_72", pchar),
								StringFromKey("House_dialog_73"),
								StringFromKey("House_dialog_74"), "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(
								StringFromKey("House_dialog_75"),
								StringFromKey("House_dialog_76"),
								StringFromKey("House_dialog_77"),
								StringFromKey("House_dialog_78"), npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "HouseWoman_2", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseWoman_1":
			dialog.text = StringFromKey("House_dialog_79", pchar);
			link.l1 = StringFromKey("House_dialog_80");
			link.l1.go = "exit_setOwner";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("House_dialog_81", pchar);
			link.l1 = StringFromKey("House_dialog_82");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		case "HouseWoman_2":
			dialog.text = StringFromKey("House_dialog_83");
			link.l1 = StringFromKey("House_dialog_84");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- завсклад ---------------------------------
		case "SkladMan":
			NextDiag.TempNode = "SkladMan";
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,
						StringFromKey("House_dialog_88", LinkRandPhrase(
								StringFromKey("House_dialog_85"),
								StringFromKey("House_dialog_86"),
								StringFromKey("House_dialog_87"))),
						StringFromKey("House_dialog_92", LinkRandPhrase(
								StringFromKey("House_dialog_89", pchar),
								StringFromKey("House_dialog_90", pchar),
								StringFromKey("House_dialog_91", pchar))));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("House_dialog_95", RandPhraseSimple(
								StringFromKey("House_dialog_93"),
								StringFromKey("House_dialog_94", XI_ConvertString("Colony" + npchar.city + "Gen")))),
						StringFromKey("House_dialog_98", RandPhraseSimple(
								StringFromKey("House_dialog_96"),
								StringFromKey("House_dialog_97"))));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			//			if (isBadReputation(pchar, 40))
			if (PlayerRPGCheck_BadReputation(40, false))
			{
				dialog.text = StringFromKey("House_dialog_99", pchar);
				link.l1 = StringFromKey("House_dialog_100");
				link.l1.go = "fight";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("House_dialog_101", GetFullName(npchar)),
							StringFromKey("House_dialog_102"),
							StringFromKey("House_dialog_103"),
							StringFromKey("House_dialog_106", RandPhraseSimple(
									StringFromKey("House_dialog_104"),
									StringFromKey("House_dialog_105"))), "block", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("House_dialog_107"),
							StringFromKey("House_dialog_108"),
							StringFromKey("House_dialog_109"),
							StringFromKey("House_dialog_110"), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
				//открывание двери верфи по квесту промышленного шпионажа
				if (CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && pchar.questTemp.different.ShipyardsMap == "toTarget" && npchar.city == pchar.questTemp.different.ShipyardsMap.city && locations[reload_cur_location_index].type == "shipyard" && (GetTime() > 6.0) && (GetTime() < 22.0))
				{
					link.l2 = StringFromKey("House_dialog_113", RandPhraseSimple(
								StringFromKey("House_dialog_111"),
								StringFromKey("House_dialog_112")));
					link.l2.go = "ShipyardsMap_1";
				}
			}
		break;
		case "ShipyardsMap_1":
			dialog.text = StringFromKey("House_dialog_114");
			link.l1 = StringFromKey("House_dialog_115");
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			if (CheckAttribute(pchar, "questTemp.different.ShipyardsMap.skladFight") && sti(pchar.questTemp.different.ShipyardsMap.skladFight))
			{
				PlayerRPGCheck_SPECIAL_NotifyFail(SPECIAL_C);
				dialog.text = StringFromKey("House_dialog_116");
				link.l1 = StringFromKey("House_dialog_117", pchar);
				link.l1.go = "fight";
				AddCharacterExpToSkill(pchar, "FencingLight", 5);
				AddCharacterExpToSkill(pchar, "Fencing", 5);
				AddCharacterExpToSkill(pchar, "FencingHeavy", 5);
				ChangeCharacterReputation(pchar, -1);
			}
			else
			{
				dialog.text = StringFromKey("House_dialog_118", pchar);
				link.l1 = StringFromKey("House_dialog_119");
				link.l1.go = "ShipyardsMap_3";
			}
		break;
		case "ShipyardsMap_3":
			dialog.text = StringFromKey("House_dialog_120");
			link.l1 = StringFromKey("House_dialog_121", pchar);
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = StringFromKey("House_dialog_122", FindMoneyString(sti(pchar.questTemp.different.ShipyardsMap.sklad) * 1000));
			link.l1 = StringFromKey("House_dialog_123");
			link.l1.go = "exit";
			if (sti(pchar.money) >= (sti(pchar.questTemp.different.ShipyardsMap.sklad) * 1000))
			{
				link.l2 = StringFromKey("House_dialog_124", pchar);
				link.l2.go = "ShipyardsMap_5";
			}
		break;
		case "ShipyardsMap_5":
			dialog.text = StringFromKey("House_dialog_125");
			link.l1 = StringFromKey("House_dialog_126");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.ShipyardsMap.sklad) * 1000);
			AddQuestRecord("ShipyardsMap", "5");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddCharacterExpToSkill(pchar, "Fortune", 5 + rand(5));
			AddCharacterExpToSkill(pchar, "Sneak", 5 + rand(5));
			pchar.questTemp.different.ShipyardsMap = "toShipyard";
			//снимаем close_for_night
			string sName;
			int location_index = FindLocation(npchar.city + "_town");
			makearef(arRld, Locations[location_index].reload);
			Qty = GetAttributesNum(arRld);
			for (int a = 0; a < Qty; a++)
			{
				arDis = GetAttributeN(arRld, a);
				sName = arDis.go;
				if (HasSubStr(sName, "_shipyard"))
				{
					DeleteAttribute(arDis, "close_for_night");
					break;
				}
			}
			LocatorReloadEnterDisable(npchar.city + "_shipyard", "reload2", true);
			//ставим таймер на возврат close_for_night
			SetTimerFunction("ShipyardsMap_returnCFN", 0, 0, 2);
		break;

		case "GlavSklad":
			NextDiag.TempNode = "GlavSklad";
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,
						StringFromKey("House_dialog_130", LinkRandPhrase(
								StringFromKey("House_dialog_127"),
								StringFromKey("House_dialog_128"),
								StringFromKey("House_dialog_129"))),
						StringFromKey("House_dialog_134", LinkRandPhrase(
								StringFromKey("House_dialog_131", pchar),
								StringFromKey("House_dialog_132", pchar),
								StringFromKey("House_dialog_133", pchar))));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("House_dialog_137", RandPhraseSimple(
								StringFromKey("House_dialog_135"),
								StringFromKey("House_dialog_136", XI_ConvertString("Colony" + npchar.city + "Gen")))),
						StringFromKey("House_dialog_140", RandPhraseSimple(
								StringFromKey("House_dialog_138"),
								StringFromKey("House_dialog_139"))));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("House_dialog_141"),
						StringFromKey("House_dialog_142"),
						StringFromKey("House_dialog_143"),
						StringFromKey("House_dialog_146", RandPhraseSimple(
								StringFromKey("House_dialog_144"),
								StringFromKey("House_dialog_145"))), "block", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("House_dialog_147"),
						StringFromKey("House_dialog_148"),
						StringFromKey("House_dialog_149"),
						StringFromKey("House_dialog_150"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
			if (pchar.questTemp.CapBloodLine == true) break;
			// ugeen --> склад товаров для ГГ
			if (CheckAttribute(npchar, "Storage"))
			{
				if (!CheckAttribute(npchar, "Storage.Speak"))
				{
					dialog.text = StringFromKey("House_dialog_151");
					link.l1 = StringFromKey("House_dialog_152");
					link.l1.go = "storage_rent";
				}
				else
				{
					if (CheckAttribute(npchar, "Storage.Activate"))
					{
						link.l7 = StringFromKey("House_dialog_153");
						link.l7.go = "storage_0";
						link.l8 = StringFromKey("House_dialog_154", pchar);
						link.l8.go = "storage_04";
					}
					else
					{
						if (!CheckAttribute(npchar, "Storage.NoActivate"))
						{
							link.l7 = StringFromKey("House_dialog_155");
							link.l7.go = "storage_01";
						}
						else //krizis
						{
							link.l7 = StringFromKey("House_dialog_156");
							link.l7.go = "storage_01a";
						}
					}
				}
				// <-- ugeen
			}
		break;
		//--------------------------------- Аренда склада ---------------------------------
		case "storage_rent":
			NPChar.Storage.Speak = true;
			dialog.text = StringFromKey("House_dialog_157");
			link.l1 = StringFromKey("House_dialog_158");
			link.l1.go = "storage_rent1";
		break;
		case "storage_rent1":
			NPChar.MoneyForStorage = GetStoragePrice(15000);
			dialog.text = StringFromKey("House_dialog_159", FindMoneyString(sti(npchar.MoneyForStorage)));
			link.l1 = StringFromKey("House_dialog_160");
			link.l1.go = "storage_rent2";
			link.l2 = StringFromKey("House_dialog_161");
			link.l2.go = "storage_rent3";
		break;
		case "storage_rent2":
			dialog.text = StringFromKey("House_dialog_162");
			if (sti(pchar.money) >= sti(npchar.MoneyForStorage))
			{
				link.l1 = StringFromKey("House_dialog_163");
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = StringFromKey("House_dialog_164");
				link.l1.go = "exit";
			}
		break;
		case "storage_rent3":
			dialog.text = StringFromKey("House_dialog_165");
			link.l1 = StringFromKey("House_dialog_166");
			link.l1.go = "exit";
		break;
		case "storage_0":
			npchar.MoneyForStorage = GetNpcQuestPastMonthParam(npchar, "Storage.Date") * sti(npchar.Storage.MoneyForStorage);
			if (sti(npchar.MoneyForStorage) > 0)
			{
				dialog.text = StringFromKey("House_dialog_167", FindMoneyString(sti(npchar.MoneyForStorage)));
				if (sti(pchar.money) >= sti(npchar.MoneyForStorage))
				{
					link.l1 = StringFromKey("House_dialog_168");
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = StringFromKey("House_dialog_169");
					link.l1.go = "exit";
				}
			}
			else
			{
				// лесник . если забыл с собой корабль то никак.
				i = FindColony(npchar.City);
				if (i != -1) rColony = GetColonyByIndex(i);

				if (CheckShipMooredInColony(rColony))
				{
					dialog.text = StringFromKey("House_dialog_170");
					link.l1 = StringFromKey("House_dialog_171");
					link.l1.go = "storage_2";
				}
				else
				{
					dialog.text = StringFromKey("House_dialog_174", RandPhraseSimple(
								StringFromKey("House_dialog_172"),
								StringFromKey("House_dialog_173")));
					link.l1 = StringFromKey("House_dialog_177", RandPhraseSimple(
								StringFromKey("House_dialog_175", pchar),
								StringFromKey("House_dialog_176")));
					link.l1.go = "exit";
					break;
				}
			}
			link.l2 = StringFromKey("House_dialog_178", pchar);
			link.l2.go = "exit";
		break;
		case "storage_01":
			dialog.text = StringFromKey("House_dialog_179", GetAddress_Form(npchar));
			link.l1 = StringFromKey("House_dialog_180");
			link.l1.go = "storage_1";
			link.l2 = StringFromKey("House_dialog_181", pchar);
			link.l2.go = "exit";
		break;
		case "storage_01a": //krizis
			dialog.text = StringFromKey("House_dialog_182", GetAddress_Form(npchar));
			link.l1 = StringFromKey("House_dialog_183");
			link.l1.go = "storage_1";
			link.l2 = StringFromKey("House_dialog_184", pchar);
			link.l2.go = "exit";
		break;
		case "storage_1":
			npchar.MoneyForStorage = GetStoragePrice(15000);
			dialog.text = StringFromKey("House_dialog_185");
			if (sti(pchar.money) >= sti(npchar.MoneyForStorage))
			{
				link.l1 = StringFromKey("House_dialog_186");
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = StringFromKey("House_dialog_187");
				link.l1.go = "exit";
			}
		break;
		case "storage_11":
			i = FindColony(npchar.City);
			if (i != -1) rColony = GetColonyByIndex(i);
			AddMoneyToCharacter(pchar, -makeint(npchar.MoneyForStorage));
			npchar.Storage.MoneyForStorage = npchar.MoneyForStorage;
			npchar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));
		break;
		case "storage_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			i = FindColony(npchar.City);
			if (i != -1) rColony = GetColonyByIndex(i);
			LaunchStorage(sti(rColony.StoreNum));
		break;
		case "storage_3":
			AddMoneyToCharacter(pchar, -sti(npchar.MoneyForStorage));
			npchar.MoneyForStorage = GetStoragePrice(15000);
			npchar.Storage.MoneyForStorage = npchar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			i = FindColony(npchar.City);
			if (i != -1) rColony = GetColonyByIndex(i);
			LaunchStorage(sti(rColony.StoreNum));
		break;
		case "storage_04":
			dialog.text = StringFromKey("House_dialog_188");
			link.l1 = StringFromKey("House_dialog_189", pchar);
			link.l1.go = "storage_4";
			link.l2 = StringFromKey("House_dialog_190", pchar);
			link.l2.go = "exit";
		break;
		case "storage_4":
			npchar.MoneyForStorage = GetNpcQuestPastMonthParam(npchar, "Storage.Date") * sti(npchar.Storage.MoneyForStorage);
			if (sti(NPChar.MoneyForStorage) > 0)
			{
				dialog.text = StringFromKey("House_dialog_191", FindMoneyString(sti(npchar.MoneyForStorage)));
				if (sti(pchar.money) >= sti(npchar.MoneyForStorage))
				{
					link.l1 = StringFromKey("House_dialog_192");
					link.l1.go = "storage_5";
				}
			}
			else
			{
				// лесник . если нет корабля то и товар не забрать
				i = FindColony(npchar.City);
				if (i != -1) rColony = GetColonyByIndex(i);

				if (CheckShipMooredInColony(rColony))
				{
					dialog.text = StringFromKey("House_dialog_193"); //krizis
					link.l1 = StringFromKey("House_dialog_194");
					link.l1.go = "storage_6";
				}
				else
				{
					dialog.text = StringFromKey("House_dialog_197", RandPhraseSimple(
								StringFromKey("House_dialog_195"),
								StringFromKey("House_dialog_196")));
					link.l1 = StringFromKey("House_dialog_200", RandPhraseSimple(
								StringFromKey("House_dialog_198"),
								StringFromKey("House_dialog_199")));
					link.l1.go = "exit";
					break;
				}
			}
		break;
		case "storage_5":
			i = FindColony(npchar.City);
			if (i != -1) rColony = GetColonyByIndex(i);
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(npchar.MoneyForStorage));
			npchar.Storage.NoActivate = true;
			DeleteAttribute(npchar, "Storage.Activate");
			DialogExit();
		break;
		case "storage_6":
			i = FindColony(npchar.City);
			if (i != -1) rColony = GetColonyByIndex(i);
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(npchar, "Storage.Activate");
			npchar.Storage.NoActivate = true;
			DialogExit();
		break;
		//--------------------------------- Аренда склада ---------------------------------

		case "GlavBankVault":
			NextDiag.TempNode = "GlavBankVault";
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,
						StringFromKey("House_dialog_204", LinkRandPhrase(
								StringFromKey("House_dialog_201"),
								StringFromKey("House_dialog_202"),
								StringFromKey("House_dialog_203"))),
						StringFromKey("House_dialog_208", LinkRandPhrase(
								StringFromKey("House_dialog_205", pchar),
								StringFromKey("House_dialog_206", pchar),
								StringFromKey("House_dialog_207", pchar))));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("House_dialog_211", RandPhraseSimple(
								StringFromKey("House_dialog_209"),
								StringFromKey("House_dialog_210", XI_ConvertString("Colony" + npchar.city + "Gen")))),
						StringFromKey("House_dialog_214", RandPhraseSimple(
								StringFromKey("House_dialog_212"),
								StringFromKey("House_dialog_213"))));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("House_dialog_215"),
						StringFromKey("House_dialog_216"),
						StringFromKey("House_dialog_217"),
						StringFromKey("House_dialog_220", RandPhraseSimple(
								StringFromKey("House_dialog_218"),
								StringFromKey("House_dialog_219"))), "block", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("House_dialog_221"),
						StringFromKey("House_dialog_222"),
						StringFromKey("House_dialog_223"),
						StringFromKey("House_dialog_224"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
			if (pchar.questTemp.CapBloodLine == true) break;
			if (!CheckAttribute(npchar, "StorageOpen"))
			{
				link.l9 = StringFromKey("House_dialog_225");
				link.l9.go = "PersonalStorage";
			}
			else
			{
				link.l9 = StringFromKey("House_dialog_226");
				link.l9.go = "PersonalStorage_Open";
				link.l10 = StringFromKey("House_dialog_227");
				link.l10.go = "PersonalStorage_Close";
			}
			link.l69 = StringFromKey("House_dialog_228", pchar);
			link.l69.go = "exit";
		break;
		//--------------------------------- Аренда хранилища ---------------------------------
		case "PersonalStorage":
			npchar.MoneyForStorage = GetStoragePrice(1000);
			npchar.MoneyForStorageRent = GetStoragePrice(150);
			dialog.text = StringFromKey("House_dialog_229", FindMoneyString(sti(npchar.MoneyForStorage)), npchar.MoneyForStorageRent);
			if (sti(pchar.money) >= sti(npchar.MoneyForStorage))
			{
				link.l1 = StringFromKey("House_dialog_230");
				link.l1.go = "PersonalStorage_1";
			}
			link.l2 = StringFromKey("House_dialog_231");
			link.l2.go = "exit";
		break;
		case "PersonalStorage_1":
			AddMoneyToCharacter(pchar, -sti(npchar.MoneyForStorage));
			npchar.StorageOpen = "Opened";
			npchar.StoragePrice = npchar.MoneyForStorageRent;
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			DeleteAttribute(npchar, "items");
			dialog.text = StringFromKey("House_dialog_232");
			link.l1 = StringFromKey("House_dialog_233");
			link.l1.go = "PersonalStorage_Open_2";
		break;
		case "PersonalStorage_Open":
			npchar.MoneyForStorage = GetNpcQuestPastMonthParam(npchar, "Storage.Date") * sti(npchar.StoragePrice);
			if (sti(npchar.MoneyForStorage) > 0)
			{
				dialog.text = StringFromKey("House_dialog_234", FindMoneyString(sti(npchar.MoneyForStorage)));
				if (sti(pchar.money) >= sti(npchar.MoneyForStorage))
				{
					link.l1 = StringFromKey("House_dialog_235");
					link.l1.go = "PersonalStorage_Open_1";
				}
				else
				{
					link.l1 = StringFromKey("House_dialog_236");
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = StringFromKey("House_dialog_237");
				link.l1 = StringFromKey("House_dialog_238");
				link.l1.go = "PersonalStorage_Open_2";
			}
			link.l2 = StringFromKey("House_dialog_239", pchar);
			link.l2.go = "exit";
		break;
		case "PersonalStorage_Open_1":
			AddMoneyToCharacter(pchar, -sti(npchar.MoneyForStorage));
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			dialog.text = StringFromKey("House_dialog_240");
			link.l1 = StringFromKey("House_dialog_241");
			link.l1.go = "PersonalStorage_Open_2";
		break;
		case "PersonalStorage_Open_2":
			DialogExit();
			i = FindColony(npchar.City);
			if (i != -1) rColony = GetColonyByIndex(i);
			LaunchItemsStorage(&stores[sti(rColony.StoreNum)]);
		break;
		case "PersonalStorage_Close":
			npchar.MoneyForStorage = GetNpcQuestPastMonthParam(npchar, "Storage.Date") * sti(npchar.StoragePrice);
			if (sti(npchar.MoneyForStorage) > 0)
			{
				dialog.text = StringFromKey("House_dialog_242", FindMoneyString(sti(npchar.MoneyForStorage)));
				if (sti(pchar.money) >= sti(npchar.MoneyForStorage))
				{
					link.l1 = StringFromKey("House_dialog_243");
					link.l1.go = "PersonalStorage_Close_1";
				}
				else
				{
					link.l1 = StringFromKey("House_dialog_244");
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = StringFromKey("House_dialog_245");
				link.l1 = StringFromKey("House_dialog_246", pchar);
				link.l1.go = "PersonalStorage_Close_1";
			}
			link.l2 = StringFromKey("House_dialog_247", pchar);
			link.l2.go = "exit";
		break;
		case "PersonalStorage_Close_1":
			DialogExit();
			string sTemp;
			i = FindColony(NPChar.City);
			if (i != -1) rColony = GetColonyByIndex(i);
			rColony = &stores[sti(rColony.StoreNum)];
			if (CheckAttribute(rColony, "items"))
			{
				if (CheckAttribute(rColony, "items.gold"))
				{
					AddMoneyToCharacter(pchar, sti(rColony.items.gold));
					DeleteAttribute(rColony, "items.gold");
				}
				makearef(arRld, rColony.items);
				for (i = 0; i < GetAttributesNum(arRld); i++)
				{
					sTemp = GetAttributeName(GetAttributeN(arRld, i));
					Qty = sti(GetAttributeValue(GetAttributeN(arRld, i)));
					AddItems(pchar, sTemp, Qty);
				}
				DeleteAttribute(rColony, "items");
			}
			DeleteAttribute(npchar, "StorageOpen");
			DeleteAttribute(npchar, "StoragePrice");
		break;
		//--------------------------------- Аренда хранилища ---------------------------------
	}
}

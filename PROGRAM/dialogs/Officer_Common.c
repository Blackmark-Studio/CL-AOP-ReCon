// базовый диалог-файл для офицеров

string AtEase(ref rChar)
{
	if (rChar.sex == "woman")
	{
		if (pchar.sex == "woman")
		{
			return StringFromKey("Officer_Common_1");
		}
		else
		{
			return StringFromKey("Officer_Common_2");
		}
	}
	else
	{
		return StringFromKey("Officer_Common_3");
	}
}

string Agree(ref rChar)
{
	if (pchar.sex == "woman")
	{
		return StringFromKey("Officer_Common_4");
	}
	else
	{
		if (rChar.sex == "woman")
		{
			return StringFromKey("Officer_Common_5");
		}
		else
		{
			return StringFromKey("Officer_Common_6");
		}
	}
}

void ProcessBaseOfficerEvent(ref NPChar, aref Link, aref Diag)
{
	ref chr, sld;
	string attr, attrLoc, sGun, sGunType;
	int i, iTemp, iTax, iFortValue;
	bool isOrder = false;

	sGunType = GUN_ITEM_TYPE;
	if (CharUseMusket(NPChar) || IsMusketer(NPChar) || MusketPriority(NPChar))
		sGunType = MUSKET_ITEM_TYPE;

	sGun = GetCharacterEquipByGroup(NPChar, sGunType);

	if (NPChar.chr_ai.type == LAI_TYPE_HUBER) //Налоги наместника
	{
		iTemp = GetNpcQuestPastDayParam(NPChar, "StartTaxDate");
		iTax = makeint((GetCharacterSkillSimple(NPChar, SKILL_COMMERCE) + GetCharacterSkillSimple(NPChar, SKILL_LEADERSHIP)) / 2);
		sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
		if (CheckAttribute(sld, "FortValue")) iFortValue = sti(sld.FortValue);
		else
		{
			if (sld.id == "Panama") iFortValue = 80;
			else iFortValue = 20;
		}
		NPChar.Gover_Tax_Sum = iFortValue * iTax * iTemp;
	} // Rosarak. Сейчас в ветке наместника эти переменные не обновляются, но в будущем надо следить.

	string sAttr = Dialog.CurrentNode;
	if (HasSubStr(sAttr, "_exitFire")) //HardCoffee ref exit_fire_
	{
		i = sti(sAttr);
		if (CheckAttribute(NPChar, "PGGAi"))
		{
			pchar.questTemp.FiringOfficerIDX = NPChar.index;
			AddDialogExitQuestFunction("PGG_FireOfficer");
			DialogExit();
			return;
		}    //navy <--
		Diag.TempNode = "Fired_" + i;
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
		AddDialogExitQuestFunction("LandEnc_OfficerFired");
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
	}

	if (HasSubStr(sAttr, "_chang")) //HardCoffee ref Get_out_ chang
	{
		i = sti(sAttr);
		Diag.TempNode = "Fired_" + i;
		if (1 == i || 3 == i || 5 == i)    AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank) * 1000)));
		if (1 == i || 4 == i) ChangeCharacterReputation(pchar, -1);
		if (3 == i || 5 == i) ChangeCharacterReputation(pchar, 1);
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
		AddDialogExitQuestFunction("LandEnc_OfficerFired");
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
		LaunchCharacterItemChange(npchar);
	}

	if (HasStr(sAttr, "SetGunBullets1_"))
	{
		i = findsubstr(sAttr, "_", 0);
		TEV.CT.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1);
		Dialog.CurrentNode = "SetGunBullets2";
	}

	if (HasStr(sAttr, "TalkBoatswain_Training_Calculate_Companion_"))
	{
		TEV.CT.CompanionNum = FindStringAfterSubStr(sAttr, "Companion_");
		Dialog.CurrentNode = "TalkBoatswain_Training_Calculate_Companion_Result";
	}

	switch (Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = StringFromKey("Officer_Common_9", RandPhraseSimple(
							StringFromKey("Officer_Common_7"),
							StringFromKey("Officer_Common_8")));
				link.l1 = StringFromKey("Officer_Common_12", RandPhraseSimple(
							StringFromKey("Officer_Common_10"),
							StringFromKey("Officer_Common_11", pchar)));
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = StringFromKey("Officer_Common_13");
			if (FindFreeRandomOfficer() > 0)
			{
				Link.l1 = StringFromKey("Officer_Common_14");
				Link.l1.go = "Node_2";
			}
			Link.l2 = StringFromKey("Officer_Common_15");
			Link.l2.go = "Exit";
		break;

		case "NiceDayLSC":
			if (pchar.questTemp.LSC == "over")
			{
				dialog.text = StringFromKey("Officer_Common_16");
				link.l1 = StringFromKey("Officer_Common_17");
			}
			else
			{
				dialog.text = StringFromKey("Officer_Common_18");
				link.l1 = StringFromKey("Officer_Common_19");
			}
			Diag.TempNode = "NiceDayLSC";
			link.l1.go = "exit";
		break;

		/*case "CitizenNotBlade": //HardCoffee ref CitizenNotBlade
			dialog.text = StringFromKey("Officer_Common_12");
			link.l1 = LinkRandPhrase(StringFromKey("Officer_Common_13"), StringFromKey("Officer_Common_14"), StringFromKey("Officer_Common_15"));
			link.l1.go = "exit_HideBlade";
			Link.l2 = LinkRandPhrase(StringFromKey("Officer_Common_555"), StringFromKey("Officer_Common_556"), StringFromKey("Officer_Common_557"));
			link.l2.go = "exit_NoHideBlade";
		break;
		case "exit_HideBlade":
			NPChar.Dialog.CurrentNode = NPChar.Dialog.TempNode;
			DialogExit();
			SendMessage(pchar, "lsl", MSG_CHARACTER_EX_MSG, "SetFightMode", 1);
			LAi_SetFightMode(pchar, false);
		break;
		case "exit_NoHideBlade":
			NPChar.Dialog.CurrentNode = NPChar.Dialog.TempNode;
			NPChar.chr_ai.type.checkFight = 6.0;
			DialogExit();
			Lai_MethodDelay("ExitNoHideBlade", 0.5);
		break;*/

		case "hired":
			Diag.TempNode = "Hired";

			if (CheckAttribute(NPChar, "walker")) // Rosarak. Пока только для бывших наместников, но можно модифицировать
			{
				Dialog.text = StringFromKey("Officer_Common_20", npchar);
				if (FindFreeRandomOfficer() == -1)
				{
					link.l1 = StringFromKey("Officer_Common_21");
					link.l1.go = "Exit";
				}
				else
				{
					link.l1 = StringFromKey("Officer_Common_22", pchar);
					link.l1.go = "exit_hire";
				}
				link.l2 = StringFromKey("Officer_Common_23", npchar);
				if (NPChar.id == "Rimalier" && CheckAttribute(pchar, "questTemp.Brides_Tortuga.RimalierDismissLocked"))
					link.l2.go = "Rimalier_DismissLocked";
				else
					link.l2.go = "AsYouWish";
				link.l3 = StringFromKey("Officer_Common_24");
				link.l3.go = "Exit";
				if (FindFreeRandomOfficer() == -1) DeleteAttribute(link, "l3");
				break;
			}
			// только наняли -->
			if (IsCompanion(NPChar))
			{
				Dialog.text = StringFromKey("Officer_Common_25");
				link.l2 = StringFromKey("Officer_Common_26", pchar);
				link.l2.go = "Exit";
				break;
			}
			if (Npchar.location.group == "sit" && !isShipInside(pchar.location))
			{
				dialog.text = StringFromKey("Officer_Common_27");
				Link.l1 = StringFromKey("Officer_Common_28");
				Link.l1.go = "Exit";
				break;
			}
			// только наняли <--
			if (NPChar.id == "James_Callow")
			{
				dialog.text = StringFromKey("Officer_Common_29");
				isOrder = true;
			}
			else if (NPChar.id == "Andreas_Fickler")
			{
				dialog.text = StringFromKey("Officer_Common_30", pchar.name);
			}
			else
			{
				if (NPChar.sex != "woman" && rand(2) == 0)
				{
					dialog.text = StringFromKey("Officer_Common_31");
					isOrder = true;
				}
				else
				{
					dialog.text = StringFromKey("Officer_Common_34", RandPhraseSimple(
								StringFromKey("Officer_Common_32", npchar),
								StringFromKey("Officer_Common_33", npchar)));
				}
			}

			// диалог компаньона на корабле.
			if (CheckAttribute(NPChar, "IsCompanionClone"))
			{
				dialog.Text = StringFromKey("Officer_Common_35");
				if (bBettaTestMode) // Только при бета-тесте
				{
					Link.l1 = StringFromKey("Officer_Common_36", npchar);
					Link.l1.go = "CompanionTravel";
				}
				if (!checkattribute(NPChar, "Tasks.CanBoarding") || sti(NPChar.Tasks.CanBoarding))
				{
					Link.l2 = StringFromKey("Officer_Common_37", npchar);
					Link.l2.go = "Companion_TaskBoardingNo";
				}
				else
				{
					Link.l2 = StringFromKey("Officer_Common_38", npchar);
					Link.l2.go = "Companion_TaskBoardingYes";
				}
				if (!checkattribute(NPChar, "Tasks.CanChangeShipAfterBoarding") || sti(NPChar.Tasks.CanChangeShipAfterBoarding))
				{
					Link.l3 = StringFromKey("Officer_Common_39", npchar);
					Link.l3.go = "Companion_TaskChangeNo";
				}
				else
				{
					Link.l3 = StringFromKey("Officer_Common_40");
					Link.l3.go = "Companion_TaskChangeYes";
				}
				if (!GetBan("Exchange"))
				{
					Link.l4 = StringFromKey("Officer_Common_41");
					Link.l4.go = "exchangeItems";
				}
				Link.l5 = StringFromKey("Officer_Common_42");
				Link.l5.go = "FallOut";
				link.l6 = StringFromKey("Officer_Common_43");
				link.l6.go = "goToExit";
				break;
			}

			if (isOfficer(Npchar)) // проверка для кампуса, где слотовые офы
			{
				Link.l2 = StringFromKey("Officer_Common_44");
				Link.l2.go = "stay_follow";
			}

			if (CheckAttribute(pchar, "Fellows.Passengers.boatswain") && sti(pchar.Fellows.Passengers.boatswain) == sti(NPChar.index))
			{
				if (!isOrder)
					Link.l13 = StringFromKey("Officer_Common_45", NPChar.name);
				else
					Link.l13 = StringFromKey("Officer_Common_46", NPChar.name);
				Link.l13.go = "TalkBoatswain_Start";
			}

			// boal отчёт о корабле
			if (CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
				Link.l8 = StringFromKey("Officer_Common_47", GetStrSmallRegister(XI_ConvertString("treasurer")));
				Link.l8.go = "QMASTER_1";
				if (NPChar.id == "Andreas_Fickler")
				{
					Link.l8 = StringFromKey("Officer_Common_48");
					Link.l8.go = "QMASTER_1";
				}

				Link.l11 = StringFromKey("Officer_Common_49", npchar);
				Link.l11.go = "TransferGoodsEnable";
			}
			//fix увольнения Уоркмана //HardCoffee фикс для увольнений на орудийной палубе)
			if (pchar.questTemp.LSC != "MechanicIsArrest_toResidence" && pchar.location != "My_Deck_Medium" && pchar.location != "My_Orlop")
			{
				Link.l4 = StringFromKey("Officer_Common_50");
				if (NPChar.id == "Rimalier" && CheckAttribute(pchar, "questTemp.Brides_Tortuga.RimalierDismissLocked"))
					Link.l4.go = "Rimalier_DismissLocked";
				else
					Link.l4.go = "AsYouWish";
			}

			// по тек локации определим можно ли тут приказать  -->
			if (IsEntity(loadedLocation))
			{
				if (CheckAttribute(loadedLocation, "fastreload"))
				{
					iTemp = FindColony(loadedLocation.fastreload);
					if (iTemp != -1)
					{
						sld = GetColonyByIndex(iTemp);
						if (sti(sld.HeroOwn) == true && !CheckAttribute(sld, "OfficerIdx") && !CheckAttribute(sld, "GovernorDisable") && !CheckAttribute(NPChar, "MushForever")) // ~!mu
						{
							NPChar.ColonyIdx = iTemp;
							Link.l7 = StringFromKey("Officer_Common_51");
							Link.l7.go = "Gover_Hire";
						}
					}
				}
			}
			if (!checkattribute(NPChar, "Tasks.beInCabin") || sti(NPChar.Tasks.beInCabin) == false)
			{
				Link.l12 = StringFromKey("Officer_Common_52");
				Link.l12.go = "beInCabin";
			}
			else
			{
				Link.l12 = StringFromKey("Officer_Common_53");
				Link.l12.go = "outOfCabin";
			}
			if (!GetBan("Exchange"))
			{
				Link.l14 = StringFromKey("Officer_Common_54");
				Link.l14.go = "exchangeItems";
			}

			if (NPChar.id == "Andreas_Fickler")
				Link.l9 = StringFromKey("Officer_Common_55");
			else
				Link.l9 = AtEase(NPChar) + ".";
			Link.l9.go = "FallOut";
			if (Get_My_Cabin() == NPChar.location)
			{
				Link.l10 = StringFromKey("Officer_Common_56");
				Link.l10.go = "goToExit";
			}
		break;

		case "Rimalier_DismissLocked":
			Diag.TempNode = "Hired";
			dialog.text = StringFromKey("Officer_Common_657");
			Link.l1 = StringFromKey("Officer_Common_658");
			Link.l1.go = "hired";
		break;

		case "exchangeItems":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
			LaunchCharacterItemChange(npchar);
		break;

		case "TransferGoodsEnable":
			if (sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = StringFromKey("Officer_Common_57");
				Link.l1 = StringFromKey("Officer_Common_58", npchar);
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
			}
			dialog.text = StringFromKey("Officer_Common_61", RandPhraseSimple(
						StringFromKey("Officer_Common_59"),
						StringFromKey("Officer_Common_60")));
			if (NPChar.id == "Andreas_Fickler")
			{
				dialog.text = StringFromKey("Officer_Common_64", RandPhraseSimple(
							StringFromKey("Officer_Common_62"),
							StringFromKey("Officer_Common_63")));
			}
			Link.l1 = StringFromKey("Officer_Common_65");
			Link.l1.go = "TransferGoodsEnable_2";
		break;

		case "TransferGoodsEnable_2":
			Diag.CurrentNode = "Hired";
			DialogExit();
			LaunchTransferGoodsScreen(); // Интерфейс автозакупки товаров
		break;

		case "ShowParam_exit":
			Diag.CurrentNode = "OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			LaunchCharacter(NPChar);
		break;

		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_hire":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		// boal 29.05.04 офицер хочет свалить -->
		case "WantToGo":
			chrDisableReloadToLocation = false;
			Diag.TempNode = "Hired";
			dialog.text = StringFromKey("Officer_Common_78", LinkRandPhrase(
						StringFromKey("Officer_Common_69", LinkRandPhrase(
								StringFromKey("Officer_Common_66", npchar),
								StringFromKey("Officer_Common_67", npchar),
								StringFromKey("Officer_Common_68"))),
						StringFromKey("Officer_Common_73", LinkRandPhrase(
								StringFromKey("Officer_Common_70"),
								StringFromKey("Officer_Common_71"),
								StringFromKey("Officer_Common_72"))),
						StringFromKey("Officer_Common_77", LinkRandPhrase(
								StringFromKey("Officer_Common_74"),
								StringFromKey("Officer_Common_75"),
								StringFromKey("Officer_Common_76")))));
			Link.l1 = StringFromKey("Officer_Common_87", RandPhraseSimple(
						StringFromKey("Officer_Common_82", LinkRandPhrase(
								StringFromKey("Officer_Common_79", npchar),
								StringFromKey("Officer_Common_80", pchar),
								StringFromKey("Officer_Common_81", npchar))),
						StringFromKey("Officer_Common_86", LinkRandPhrase(
								StringFromKey("Officer_Common_83", pchar),
								StringFromKey("Officer_Common_84", pchar),
								StringFromKey("Officer_Common_85")))));
			Link.l1.go = "WantToGo_free";
			if (sti(Pchar.money) >= sti(NPChar.rank) * 250)
			{
				Link.l2 = StringFromKey("Officer_Common_91", LinkRandPhrase(
							StringFromKey("Officer_Common_88", pchar, FindMoneyString(sti(NPChar.rank) * 250)),
							StringFromKey("Officer_Common_89", npchar, sti(NPChar.rank)),
							StringFromKey("Officer_Common_90", sti(NPChar.rank))));
				Link.l2.go = "Im_kind_A2_1";
			}
			Link.l3 = StringFromKey("Officer_Common_95", LinkRandPhrase(
						StringFromKey("Officer_Common_92"),
						StringFromKey("Officer_Common_93", pchar),
						StringFromKey("Officer_Common_94", pchar)));
			Link.l3.go = "WantToGo_Stay";
		break;

		case "Im_kind_A2_1":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank) * 250)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterReputation(pchar, 1);
			dialog.text = StringFromKey("Officer_Common_96");
			Link.l1 = StringFromKey("Officer_Common_97");
			Link.l1.go = "2_Get_out_chang";
			Link.l2 = StringFromKey("Officer_Common_98");
			Link.l2.go = "WantToGo_free";
		break;

		case "WantToGo_Stay":
			dialog.text = StringFromKey("Officer_Common_101", RandPhraseSimple(
						StringFromKey("Officer_Common_99", npchar),
						StringFromKey("Officer_Common_100", npchar)));
			Link.l1 = StringFromKey("Officer_Common_105", LinkRandPhrase(
						StringFromKey("Officer_Common_102"),
						StringFromKey("Officer_Common_103", npchar),
						StringFromKey("Officer_Common_104", npchar)));
			Link.l1.go = "WantToGo_Stay_2";
			Link.l2 = PCharRepPhrase(
						StringFromKey("Officer_Common_108", RandPhraseSimple(
								StringFromKey("Officer_Common_106", npchar),
								StringFromKey("Officer_Common_107", pchar))),
						StringFromKey("Officer_Common_112", LinkRandPhrase(
								StringFromKey("Officer_Common_109"),
								StringFromKey("Officer_Common_110", npchar),
								StringFromKey("Officer_Common_111"))));
			Link.l2.go = "WantToGo_Stay_force";
		break;

		case "WantToGo_Stay_2":
			dialog.text = StringFromKey("Officer_Common_116", LinkRandPhrase(
						StringFromKey("Officer_Common_113", FindMoneyString(sti(NPChar.rank) * 500)),
						StringFromKey("Officer_Common_114", npchar, FindMoneyString(sti(NPChar.rank) * 500)),
						StringFromKey("Officer_Common_115", FindMoneyString(sti(NPChar.rank) * 500))));
			if (sti(Pchar.money) >= sti(NPChar.rank) * 500)
			{
				Link.l1 = StringFromKey("Officer_Common_120", LinkRandPhrase(
							StringFromKey("Officer_Common_117"),
							StringFromKey("Officer_Common_118", npchar),
							StringFromKey("Officer_Common_119", pchar)));
				Link.l1.go = "WantToGo_Stay_ForMoney";
			}
			Link.l2 = StringFromKey("Officer_Common_124", LinkRandPhrase(
						StringFromKey("Officer_Common_121"),
						StringFromKey("Officer_Common_122"),
						StringFromKey("Officer_Common_123", pchar)));
			Link.l2.go = "WantToGo_free";
		break;

		case "WantToGo_Stay_force":
		// Npchar.loyality = makeint(Npchar.loyality) - 2;
			ChangeCharacterLoyality(Npchar, -2);
			dialog.text = StringFromKey("Officer_Common_125");
			Link.l1 = StringFromKey("Officer_Common_129", LinkRandPhrase(
						StringFromKey("Officer_Common_126"),
						StringFromKey("Officer_Common_127"),
						StringFromKey("Officer_Common_128")));
			Link.l1.go = "exit";
		break;

		case "WantToGo_Stay_ForMoney":
			Diag.TempNode = "Hired";
			NPChar.greeting = "Gr_Officer";
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank) * 500)));
			// Npchar.loyality = makeint(Npchar.loyality) + 1;
			ChangeCharacterLoyality(Npchar, 1);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
		break;

		case "WantToGo_free":
		//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				Diag.CurrentNode = Diag.TempNode;
				DialogExit();
				break;
			}
			//navy <--
			Diag.TempNode = "WantToGo_free_Yet";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "WantToGo_free_Yet":
			Diag.TempNode = "WantToGo_free_Yet";
			dialog.text = StringFromKey("Officer_Common_133", LinkRandPhrase(
						StringFromKey("Officer_Common_130"),
						StringFromKey("Officer_Common_131"),
						StringFromKey("Officer_Common_132")));
			Link.l1 = StringFromKey("Officer_Common_136", RandPhraseSimple(
						StringFromKey("Officer_Common_134"),
						StringFromKey("Officer_Common_135")));
			Link.l1.go = "exit";
		break;
		// boal 29.05.04 офицер хочет свалить <--

		// пассажир возмущен игроком и сваливает -->
		case "WantToRemove":
			chrDisableReloadToLocation = false;
			if (Npchar.alignment == "good")
			{
				dialog.text = StringFromKey("Officer_Common_145", RandPhraseSimple(
							StringFromKey("Officer_Common_140", LinkRandPhrase(
									StringFromKey("Officer_Common_137"),
									StringFromKey("Officer_Common_138"),
									StringFromKey("Officer_Common_139"))),
							StringFromKey("Officer_Common_144", LinkRandPhrase(
									StringFromKey("Officer_Common_141", npchar),
									StringFromKey("Officer_Common_142"),
									StringFromKey("Officer_Common_143")))));
				Link.l1 = StringFromKey("Officer_Common_146");
				Link.l1.go = "1_exitFire";
				if (sti(Pchar.money) >= sti(NPChar.rank) * 500)
				{
					Link.l2 = StringFromKey("Officer_Common_147", pchar, FindMoneyString(sti(NPChar.rank) * 500));
					Link.l2.go = "Im_kind_A2";
				}
				Link.l3 = StringFromKey("Officer_Common_151", LinkRandPhrase(
							StringFromKey("Officer_Common_148"),
							StringFromKey("Officer_Common_149"),
							StringFromKey("Officer_Common_150", pchar)));
				Link.l3.go = "WantToGo_stop";
			}
			else
			{
				dialog.text = StringFromKey("Officer_Common_160", RandPhraseSimple(
							StringFromKey("Officer_Common_155", LinkRandPhrase(
									StringFromKey("Officer_Common_152"),
									StringFromKey("Officer_Common_153"),
									StringFromKey("Officer_Common_154"))),
							StringFromKey("Officer_Common_159", LinkRandPhrase(
									StringFromKey("Officer_Common_156"),
									StringFromKey("Officer_Common_157"),
									StringFromKey("Officer_Common_158")))));
				Link.l1 = StringFromKey("Officer_Common_163", RandPhraseSimple(
							StringFromKey("Officer_Common_161"),
							StringFromKey("Officer_Common_162")));
				Link.l1.go = "1_exitFire";
				if (sti(Pchar.money) >= sti(NPChar.rank) * 500)
				{
					Link.l2 = StringFromKey("Officer_Common_164", pchar, FindMoneyString(sti(NPChar.rank) * 500));
					Link.l2.go = "Im_kind_A2";
				}
				Link.l3 = StringFromKey("Officer_Common_167", RandPhraseSimple(
							StringFromKey("Officer_Common_165", npchar),
							StringFromKey("Officer_Common_166")));
				Link.l3.go = "WantToGo_stop";
			}
		break;

		case "WantToGo_stop":
			if (Npchar.alignment == "good")
			{
				dialog.text = StringFromKey("Officer_Common_171", LinkRandPhrase(
							StringFromKey("Officer_Common_168"),
							StringFromKey("Officer_Common_169", npchar),
							StringFromKey("Officer_Common_170", npchar)));
				Link.l1 = StringFromKey("Officer_Common_172", npchar);
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank)) Link.l1.go = "WantToGo_stop_stay";
				else Link.l1.go = "WantToGo_stop_fight";
				Link.l2 = StringFromKey("Officer_Common_173", npchar);
				Link.l2.go = "5_exitFire";
			}
			else
			{
				dialog.text = StringFromKey("Officer_Common_177", LinkRandPhrase(
							StringFromKey("Officer_Common_174"),
							StringFromKey("Officer_Common_175", npchar),
							StringFromKey("Officer_Common_176", npchar)));
				Link.l1 = StringFromKey("Officer_Common_178", npchar);
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank)) Link.l1.go = "WantToGo_stop_stay";
				else Link.l1.go = "WantToGo_stop_fight";
				Link.l2 = StringFromKey("Officer_Common_179", npchar);
				Link.l2.go = "5_exitFire";
			}
		break;

		case "WantToGo_stop_stay":
			dialog.text = StringFromKey("Officer_Common_182", RandPhraseSimple(
						StringFromKey("Officer_Common_180"),
						StringFromKey("Officer_Common_181")));
			Link.l1 = StringFromKey("Officer_Common_185", RandPhraseSimple(
						StringFromKey("Officer_Common_183", pchar),
						StringFromKey("Officer_Common_184", pchar)));
			Link.l1.go = "WantToGo_Munity"; //этот линк ведет к бегству
		break;

		case "WantToGo_stop_fight":
			dialog.text = NPCharRepPhrase(NPChar,
					StringFromKey("Officer_Common_186"),
					StringFromKey("Officer_Common_187"));
			Link.l1 = NPCharRepPhrase(NPChar,
					StringFromKey("Officer_Common_188", npchar),
					StringFromKey("Officer_Common_189", pchar));
			Link.l1.go = "WantToGo_stop_fight_1";
			Link.l2 = NPCharRepPhrase(NPChar,
					StringFromKey("Officer_Common_190"),
					StringFromKey("Officer_Common_191", npchar));
			Link.l2.go = "5_exitFire";
		break;

		case "WantToGo_stop_fight_1":
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterReputation(pchar, -1);
			dialog.text = NPCharRepPhrase(NPChar,
					StringFromKey("Officer_Common_192"),
					StringFromKey("Officer_Common_193"));
			Link.l1 = NPCharRepPhrase(NPChar,
					StringFromKey("Officer_Common_194", npchar),
					StringFromKey("Officer_Common_195", npchar, pchar));
			Link.l1.go = "Get_out_fight";
			if (Number_Group_People(LAI_GROUP_PLAYER, 1) > 2)
			{
				Link.l2 = StringFromKey("Officer_Common_196"); //если потенциальной подмоги больше двух
				Link.l2.go = "Get_out_chicken_fight";
			}
			else if (Number_Group_People(LAI_GROUP_PLAYER, 1) > 1) //если один потенциальный помощьник
			{
				Link.l2 = StringFromKey("Officer_Common_197");
				Link.l2.go = "Get_out_chicken_fight";
			}
		break;
		///////////////////////////////////////////////////////////////////////////////////
		case "WantToGo_Munity":    //zagolski. отыгрыш бегство офицера
			Diag.TempNode = "Hired";

			if (!CheckAttribute(pchar, "questTemp.MunityOfficerIDX"))
				pchar.questTemp.MunityOfficerIDX = "-1";

			if (sti(Pchar.questTemp.MunityOfficerIDX) != GetCharacterIndex(Npchar.id))
			{
				Pchar.questTemp.MunityOfficerIDX = GetCharacterIndex(Npchar.id);
				Pchar.questTemp.MunityOfficerIDX.begin = "1";
				SetFunctionTimerCondition("mOfficer_fc", 0, 0, 1, false);
			}
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
			DialogExit();
		break;
		////////////////////////////////////////////////////////////////////
		// пассажир возмущен игроком и сваливает <--

		case "Node_2":
			sAttr = GetOfficerType_2(npchar);
			dialog.text = NPCharRepPhrase(Npchar,
					StringFromKey("Officer_Common_198", npchar, RandSwear(), XI_ConvertString(Npchar.quest.officertype), sAttr),
					StringFromKey("Officer_Common_199", npchar, XI_ConvertString(Npchar.quest.officertype), sAttr));
			Link.l1 = StringFromKey("Officer_Common_200");
			Link.l1.go = "price";
			Link.l2 = StringFromKey("Officer_Common_201", npchar);
			Link.l2.go = "ShowParam_exit";
			Link.l3 = StringFromKey("Officer_Common_202", XI_ConvertString(Npchar.quest.officertype));
			Link.l3.go = "Exit";
		break;

		case "OnceAgain":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = StringFromKey("Officer_Common_205", RandPhraseSimple(
							StringFromKey("Officer_Common_203"),
							StringFromKey("Officer_Common_204")));
				link.l1 = StringFromKey("Officer_Common_208", RandPhraseSimple(
							StringFromKey("Officer_Common_206"),
							StringFromKey("Officer_Common_207", pchar)));
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = StringFromKey("Officer_Common_209", XI_ConvertString(Npchar.quest.officertype));
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
				Link.l1 = StringFromKey("Officer_Common_210");
				Link.l1.go = "price";
			}
			Link.l2 = StringFromKey("Officer_Common_211", npchar);
			Link.l2.go = "ShowParam_exit";
			// boal <--
			Link.l3 = StringFromKey("Officer_Common_212");
			Link.l3.go = "exit";
		break;

		case "price":
			dialog.text = StringFromKey("Officer_Common_213", FindMoneyString(sti(Npchar.quest.OfficerPrice)));
			Link.l1 = StringFromKey("Officer_Common_214");
			Link.l1.go = "trade";
			Link.l2 = StringFromKey("Officer_Common_215", npchar, Agree(NPChar));
			Link.l2.go = "hire";
			Link.l3 = StringFromKey("Officer_Common_216");
			Link.l3.go = "exit";
		break;

		case "trade":
			if ((sti(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce") * 100) >= sti(Npchar.quest.OfficerLowPrice))
			{
				if (GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE) >= Rand(12))// bug fix
				{
					Npchar.quest.OfficerPrice = makeint(makeint(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce") * 100); // пусть будет коммерция перса голой
					dialog.text = StringFromKey("Officer_Common_217", npchar, FindMoneyString(sti(Npchar.quest.OfficerPrice)));
					Link.l1 = StringFromKey("Officer_Common_218", npchar);
					Link.l1.go = "hire";
					Link.l2 = StringFromKey("Officer_Common_219");
					Link.l2.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("Officer_Common_220", npchar);
					Link.l1 = StringFromKey("Officer_Common_221", pchar);
					Link.l1.go = "hire";
					Link.l2 = StringFromKey("Officer_Common_222");
					Link.l2.go = "exit";
				}
			}
			else
			{
				dialog.text = StringFromKey("Officer_Common_223", npchar, FindMoneyString(sti(Npchar.quest.OfficerPrice)));
				Link.l1 = StringFromKey("Officer_Common_224");
				Link.l1.go = "hire";
				Link.l2 = StringFromKey("Officer_Common_225");
				Link.l2.go = "exit";
			}
		break;

		case "hire":
			if (makeint(Pchar.money) >= makeint(Npchar.quest.OfficerPrice))
			{
				AddMoneyToCharacter(Pchar, -(makeint(Npchar.quest.OfficerPrice)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = StringFromKey("Officer_Common_226", npchar);
				Link.l1 = StringFromKey("Officer_Common_227");
				Link.l1.go = "Exit_hire";
			}
			else
			{
				dialog.text = StringFromKey("Officer_Common_228");
				Link.l1 = StringFromKey("Officer_Common_229");
				Link.l1.go = "Exit";
			}
		break;

		case "OnboardSoon":
			Diag.TempNode = "OnboardSoon";
			dialog.text = StringFromKey("Officer_Common_230");
			Link.l1 = StringFromKey("Officer_Common_231");
			Link.l1.go = "Exit";
		break;

		case "QMASTER_1":
			if (sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = StringFromKey("Officer_Common_232");
				Link.l1 = StringFromKey("Officer_Common_233");
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
			}

			dialog.text = StringFromKey("Officer_Common_234", FloatToString(50.0 / (2.0 + GetSummonSkillFromNameToOld(PChar, SKILL_REPAIR) + GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK)), 1), FindSailorString(GetCrewQuantity(PChar), "Acc"), makeint((GetCrewQuantity(PChar) + 6) / 10));
			Link.l1 = StringFromKey("Officer_Common_235");
			Link.l1.go = "Exit";
			if (NPChar.id == "Andreas_Fickler")
			{
				dialog.text = StringFromKey("Officer_Common_236", FloatToString(50.0 / (2.0 + GetSummonSkillFromNameToOld(PChar, SKILL_REPAIR) + GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK)), 1), FindSailorString(GetCrewQuantity(PChar), "Acc"), makeint((GetCrewQuantity(PChar) + 6) / 10));
				Link.l1 = StringFromKey("Officer_Common_237");
				Link.l1.go = "Exit";
			}
			Diag.TempNode = "Hired";
		break;

		// boal 05.09.03 offecer need to go to abordage -->
		case "stay_follow":
			dialog.text = StringFromKey("Officer_Common_238");
			if (NPChar.id == "Andreas_Fickler")
			{
				dialog.text = StringFromKey("Officer_Common_239");
			}
			Link.l1 = StringFromKey("Officer_Common_240");
			Link.l1.go = "Boal_Stay";
			Link.l2 = StringFromKey("Officer_Common_241");
			Link.l2.go = "Boal_Follow";
			// boal 05.09.03 offecer need to go to abordage <--
			if (CheckAttribute(npchar, "equip.gun") && HasStr(npchar.equip.gun, "mushket"))
			{
				Link.l3 = StringFromKey("Officer_Common_242", npchar);
				Link.l3.go = "TargetDistance";
			}

			if (sGun != "" && CheckAttribute(NPChar, "chr_ai." + sGunType + ".bulletNum") && sti(NPChar.chr_ai.(sGunType).bulletNum) > 0)
			{
				Link.l4 = StringFromKey("Officer_Common_243");
				Link.l4.go = "SetGunBullets";
			}

			if (CheckAttribute(pchar, "Fellows.Passengers.boatswain") && sti(pchar.Fellows.Passengers.boatswain) == sti(NPChar.index))
			{
				Link.l5 = StringFromKey("Officer_Common_244", NPChar.name);
				Link.l5.go = "TalkBoatswain_Start";
			}

			Link.l99 = StringFromKey("Officer_Common_245");
			Link.l99.go = "Exit";
		break;

		case "SetGunBullets":
			Dialog.Text = StringFromKey("Officer_Common_246");
			ref rAmmo;
			sld = ItemsFromID(sGun);
			string sType = sld.chargetype;
			iTemp = KZ|Symbol(sType, ",");

			int iCurLen = strlen(&sType);
			int iCurPos = 0;
			int iCurEnd;

			for (i = 0; i <= iTemp; i++)
			{
				iCurEnd = findSubStr(&sType, ",", iCurPos);

				if (iCurEnd < 0)
					iCurEnd = iCurLen;

				sAttr = "";

				if (iCurEnd > iCurPos)
					sAttr = strcut(&sType, iCurPos, iCurEnd - 1);

				iCurPos = iCurEnd + 1;

				if (sAttr != "")
				{
					rAmmo = ItemsFromID(sld.type.(sAttr).bullet);
					TEV.CT.AMMOQ = " " + StringFromKey("Officer_Common_247");

					if (GetCharacterItem(NPChar, rAmmo.id) > 0)
					{
						TEV.CT.AMMOQ = " (";

						if (sAttr == LAi_GetCharacterBulletType(NPChar, sGunType) && GetCharacterItem(NPChar, sAttr) > 0)
							TEV.CT.AMMOQ = " " + StringFromKey("Officer_Common_248") + " ";

						TEV.CT.BULLET = GetCharacterItem(NPChar, rAmmo.id);
						TEV.CT.POWDER = GetCharacterItem(NPChar, LAi_GetAmmoGunpowderType(sAttr));

						if (LAi_GetAmmoGunpowderType(sAttr) != "")
							TEV.CT.CHARGE = func_min(sti(TEV.CT.BULLET), sti(TEV.CT.POWDER));
						else
							TEV.CT.CHARGE = TEV.CT.BULLET;

						TEV.CT.AMMOQ = StringFromKey("Officer_Common_249", TEV.CT.AMMOQ, TEV.CT.CHARGE);
					}

					attr = "l" + i;
					Link.(attr) = GetConvertStr(rAmmo.name, "ItemsDescribe.txt") + TEV.CT.AMMOQ;
					Link.(attr).go = "SetGunBullets1_" + i;
				}
			}

			Link.l99 = StringFromKey("Officer_Common_250");
			Link.l99.go = "stay_follow";
		break;

		case "SetGunBullets2":
			sld = ItemsFromID(sGun);
			sAttr = sld.chargetype;
			TEV.CT.TEMP0 = GetConvertStr(sld.name, "ItemsDescribe.txt");

			if (findSubStr(&sAttr, ",", 0) >= 0)
				sAttr = GetSubStr(sld.chargetype, ",", sti(TEV.CT.SetGunBullets));

			TEV.CT.TEMP1 = sld.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, sGunType, TEV.CT.TEMP1);
			LAi_GunSetUnload(NPChar, sGunType);
			sld = ItemsFromID(TEV.CT.TEMP1);
			Log_Clear();
			LogSound_WithNotify(StringFromKey("InfoMessages_198", GetFullName(NPChar), TEV.CT.TEMP0, GetConvertStr(sld.name, "ItemsDescribe.txt")), "Reload", "AmmoSelect");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "TargetDistance":
			dialog.text = StringFromKey("Officer_Common_251");
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = StringFromKey("Officer_Common_252");
				link.l1 = StringFromKey("Officer_Common_253");
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = StringFromKey("Officer_Common_254");
				link.l1 = StringFromKey("Officer_Common_255");
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = StringFromKey("Officer_Common_256", npchar);
				link.l1 = StringFromKey("Officer_Common_257");
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = StringFromKey("Officer_Common_258", npchar);
			link.l1 = StringFromKey("Officer_Common_259");
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;

		case "AsYouWish":
		// проверка на море -->
			if (bSeaActive)
			{
				attr = Sea_FindNearColony(true); //Rosarak. при true мы проверим не просто есть ли на острове бухта, где мы останавливались, а к какому городу она привязана
				if (attr == "none")
				{
					dialog.text = StringFromKey("Officer_Common_260");
					Link.l1 = StringFromKey("Officer_Common_261", pchar);
					Link.l1.go = "Exit"; //HardCoffee если уж прям хочется поиграть в босса и не терпится уволить
					Link.l2 = StringFromKey("Officer_Common_262");
					Link.l2.go = "Get_out_A3_strife";
					break;
				}
			}
			// проверка на море <--
			if (NPChar.id == "Andreas_Fickler") //TODO: переделать эту и дописать последующие ноды
			{
				dialog.text = StringFromKey("Officer_Common_269", RandPhraseSimple(
							StringFromKey("Officer_Common_265", RandPhraseSimple(
									StringFromKey("Officer_Common_263"),
									StringFromKey("Officer_Common_264"))),
							StringFromKey("Officer_Common_268", RandPhraseSimple(
									StringFromKey("Officer_Common_266"),
									StringFromKey("Officer_Common_267")))));
				Link.l1 = StringFromKey("Officer_Common_278", RandPhraseSimple(
							StringFromKey("Officer_Common_273", LinkRandPhrase(
									StringFromKey("Officer_Common_270"),
									StringFromKey("Officer_Common_271"),
									StringFromKey("Officer_Common_272"))),
							StringFromKey("Officer_Common_277", LinkRandPhrase(
									StringFromKey("Officer_Common_274"),
									StringFromKey("Officer_Common_275"),
									StringFromKey("Officer_Common_276", pchar)))));
				Link.l1.go = "Get_out_A2";
				break;
			}
			if (makeint(PChar.reputation) >= 41 && makeint(NPChar.reputation) < 41) //герой против злодея
			{
				dialog.text = StringFromKey("Officer_Common_286", RandPhraseSimple(
							StringFromKey("Officer_Common_282", LinkRandPhrase(
									StringFromKey("Officer_Common_279"),
									StringFromKey("Officer_Common_280"),
									StringFromKey("Officer_Common_281"))),
							StringFromKey("Officer_Common_285", RandPhraseSimple(
									StringFromKey("Officer_Common_283"),
									StringFromKey("Officer_Common_284", npchar)))));
				Link.l1 = StringFromKey("Officer_Common_295", RandPhraseSimple(
							StringFromKey("Officer_Common_290", LinkRandPhrase(
									StringFromKey("Officer_Common_287", pchar),
									StringFromKey("Officer_Common_288"),
									StringFromKey("Officer_Common_289"))),
							StringFromKey("Officer_Common_294", LinkRandPhrase(
									StringFromKey("Officer_Common_291"),
									StringFromKey("Officer_Common_292", pchar),
									StringFromKey("Officer_Common_293")))));
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank)) Link.l1.go = "Get_out_A1_peace";
				else Link.l1.go = "Get_out_A1_strife";
				break;
			}
			if (makeint(PChar.reputation) >= 41 && makeint(NPChar.reputation) >= 41) // герой против героя
			{
				dialog.text = StringFromKey("Officer_Common_302", RandPhraseSimple(
							StringFromKey("Officer_Common_298", RandPhraseSimple(
									StringFromKey("Officer_Common_296"),
									StringFromKey("Officer_Common_297"))),
							StringFromKey("Officer_Common_301", RandPhraseSimple(
									StringFromKey("Officer_Common_299"),
									StringFromKey("Officer_Common_300")))));
				Link.l1 = StringFromKey("Officer_Common_311", RandPhraseSimple(
							StringFromKey("Officer_Common_306", LinkRandPhrase(
									StringFromKey("Officer_Common_303"),
									StringFromKey("Officer_Common_304"),
									StringFromKey("Officer_Common_305", npchar))),
							StringFromKey("Officer_Common_310", LinkRandPhrase(
									StringFromKey("Officer_Common_307", pchar),
									StringFromKey("Officer_Common_308"),
									StringFromKey("Officer_Common_309", pchar)))));
				Link.l1.go = "Get_out_A2";
				break;
			}
			if (makeint(PChar.reputation) < 41 && makeint(NPChar.reputation) >= 41) // злодей против героя 
			{
				dialog.text = StringFromKey("Officer_Common_318", RandPhraseSimple(
							StringFromKey("Officer_Common_314", RandPhraseSimple(
									StringFromKey("Officer_Common_312"),
									StringFromKey("Officer_Common_313"))),
							StringFromKey("Officer_Common_317", RandPhraseSimple(
									StringFromKey("Officer_Common_315"),
									StringFromKey("Officer_Common_316")))));
				Link.l1 = StringFromKey("Officer_Common_327", RandPhraseSimple(
							StringFromKey("Officer_Common_322", LinkRandPhrase(
									StringFromKey("Officer_Common_319"),
									StringFromKey("Officer_Common_320"),
									StringFromKey("Officer_Common_321", pchar))),
							StringFromKey("Officer_Common_326", LinkRandPhrase(
									StringFromKey("Officer_Common_323", pchar),
									StringFromKey("Officer_Common_324"),
									StringFromKey("Officer_Common_325")))));
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank)) Link.l1.go = "Get_out_A3_peace";
				else Link.l1.go = "Get_out_A3_strife";
				break;

			}
			if (makeint(PChar.reputation) < 41 && makeint(NPChar.reputation) < 41) // злодей против злодея
			{
				dialog.text = StringFromKey("Officer_Common_335", RandPhraseSimple(
							StringFromKey("Officer_Common_331", LinkRandPhrase(
									StringFromKey("Officer_Common_328", npchar),
									StringFromKey("Officer_Common_329"),
									StringFromKey("Officer_Common_330"))),
							StringFromKey("Officer_Common_334", RandPhraseSimple(
									StringFromKey("Officer_Common_332"),
									StringFromKey("Officer_Common_333")))));
				Link.l1 = StringFromKey("Officer_Common_344", RandPhraseSimple(
							StringFromKey("Officer_Common_339", LinkRandPhrase(
									StringFromKey("Officer_Common_336", npchar, pchar),
									StringFromKey("Officer_Common_337", pchar),
									StringFromKey("Officer_Common_338"))),
							StringFromKey("Officer_Common_343", LinkRandPhrase(
									StringFromKey("Officer_Common_340", npchar),
									StringFromKey("Officer_Common_341", pchar),
									StringFromKey("Officer_Common_342", npchar)))));
				Link.l1.go = "Get_out_A4";
				break;
			}
		break;

		case "Get_out_A1_peace":
			dialog.text = StringFromKey("Officer_Common_353", RandPhraseSimple(
						StringFromKey("Officer_Common_348", LinkRandPhrase(
								StringFromKey("Officer_Common_345"),
								StringFromKey("Officer_Common_346"),
								StringFromKey("Officer_Common_347"))),
						StringFromKey("Officer_Common_352", LinkRandPhrase(
								StringFromKey("Officer_Common_349"),
								StringFromKey("Officer_Common_350"),
								StringFromKey("Officer_Common_351")))));
			Link.l1 = StringFromKey("Officer_Common_354");
			Link.l1.go = "exit_bad";
			Link.l2 = StringFromKey("Officer_Common_355");
			Link.l2.go = "1_exitFire";
			if (sti(Pchar.money) >= sti(NPChar.rank) * 500)
			{
				Link.l3 = StringFromKey("Officer_Common_356", pchar, FindMoneyString(sti(NPChar.rank) * 500));
				Link.l3.go = "Get_out_A1_ForMoney";
			}
		break;

		case "Get_out_A1_strife":
			dialog.text = StringFromKey("Officer_Common_360", LinkRandPhrase(
						StringFromKey("Officer_Common_357", npchar),
						StringFromKey("Officer_Common_358"),
						StringFromKey("Officer_Common_359")));
			Link.l1 = StringFromKey("Officer_Common_361");
			Link.l1.go = "exit_bad";
			Link.l2 = StringFromKey("Officer_Common_362");
			Link.l2.go = "Get_out_A1_strife_1";
			if (sti(Pchar.money) >= sti(NPChar.rank) * 500)
			{
				Link.l3 = StringFromKey("Officer_Common_363", pchar, FindMoneyString(sti(NPChar.rank) * 500));
				Link.l3.go = "Get_out_A1_ForMoney";
			}
		break;

		case "Get_out_A1_strife_1":
			dialog.text = StringFromKey("Officer_Common_366", RandPhraseSimple(
						StringFromKey("Officer_Common_364"),
						StringFromKey("Officer_Common_365", npchar)), FindMoneyString(sti(NPChar.rank) * 1000));
			Link.l1 = StringFromKey("Officer_Common_367", pchar);
			Link.l1.go = "exit_bad1";
			Link.l2 = StringFromKey("Officer_Common_368", npchar);
			Link.l2.go = "Get_out_A1_strife_battle";
			if (sti(Pchar.money) >= sti(NPChar.rank) * 1000)
			{
				Link.l3 = StringFromKey("Officer_Common_369");
				Link.l3.go = "1_Get_out_chang";
			}
		break;

		case "Get_out_A1_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank) * 500)));
			ChangeCharacterReputation(pchar, 1);
			dialog.text = StringFromKey("Officer_Common_370");
			Link.l1 = StringFromKey("Officer_Common_371");
			Link.l1.go = "1_exitFire";
		break;

		case "Get_out_A1_strife_battle":
			dialog.text = StringFromKey("Officer_Common_375", LinkRandPhrase(
						StringFromKey("Officer_Common_372"),
						StringFromKey("Officer_Common_373"),
						StringFromKey("Officer_Common_374", npchar, pchar)));
			if (sti(Pchar.money) >= sti(NPChar.rank) * 1000)
			{
				Link.l1 = StringFromKey("Officer_Common_376");
				Link.l1.go = "Get_out_A1_ForMoney_angry";
			}
			Link.l2 = StringFromKey("Officer_Common_377", npchar);
			Link.l2.go = "Get_out_A1_strife_death";
		break;

		case "Get_out_A1_strife_death":
			ChangeCharacterReputation(pchar, 1);
			OfficersReaction("good");
			dialog.text = StringFromKey("Officer_Common_378", pchar);
			Link.l1 = StringFromKey("Officer_Common_379", pchar);
			Link.l1.go = "Get_out_fight";
			if (Number_Group_People(LAI_GROUP_PLAYER, 1) > 1)
			{
				Link.l2 = StringFromKey("Officer_Common_380");
				Link.l2.go = "Get_out_chicken_fight";
			}
		break;

		case "Get_out_A1_ForMoney_angry":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank) * 1000)));
			ChangeCharacterReputation(pchar, -1);
			OfficersReaction("bad");
			dialog.text = StringFromKey("Officer_Common_381");
			Link.l1 = StringFromKey("Officer_Common_382");
			Link.l1.go = "1_exitFire";
		break;

		case "Get_out_A2":
			dialog.text = StringFromKey("Officer_Common_391", RandPhraseSimple(
						StringFromKey("Officer_Common_386", LinkRandPhrase(
								StringFromKey("Officer_Common_383"),
								StringFromKey("Officer_Common_384", npchar),
								StringFromKey("Officer_Common_385"))),
						StringFromKey("Officer_Common_390", LinkRandPhrase(
								StringFromKey("Officer_Common_387"),
								StringFromKey("Officer_Common_388"),
								StringFromKey("Officer_Common_389")))));
			Link.l1 = StringFromKey("Officer_Common_392", pchar);
			Link.l1.go = "exit_good";
			Link.l2 = StringFromKey("Officer_Common_393");
			Link.l2.go = "2_exitFire";
			Link.l3 = StringFromKey("Officer_Common_394", pchar);
			Link.l3.go = "Return_items_A2";
			if (sti(Pchar.money) >= sti(NPChar.rank) * 500)
			{
				Link.l4 = StringFromKey("Officer_Common_395", FindMoneyString(sti(NPChar.rank) * 500));
				Link.l4.go = "Im_kind_A2";
			}
		break;

		case "Return_items_A2":
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = StringFromKey("Officer_Common_396");
			Link.l1 = StringFromKey("Officer_Common_397", pchar);
			Link.l1.go = "2_Get_out_chang";
		break;

		case "Im_kind_A2":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank) * 500)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterReputation(pchar, 1);
			dialog.text = StringFromKey("Officer_Common_398");
			Link.l1 = StringFromKey("Officer_Common_399");
			Link.l1.go = "2_Get_out_chang";
			Link.l2 = StringFromKey("Officer_Common_400");
			Link.l2.go = "2_exitFire";
		break;

		case "Get_out_A3_peace":
			dialog.text = StringFromKey("Officer_Common_409", RandPhraseSimple(
						StringFromKey("Officer_Common_404", LinkRandPhrase(
								StringFromKey("Officer_Common_401"),
								StringFromKey("Officer_Common_402"),
								StringFromKey("Officer_Common_403", npchar))),
						StringFromKey("Officer_Common_408", LinkRandPhrase(
								StringFromKey("Officer_Common_405"),
								StringFromKey("Officer_Common_406"),
								StringFromKey("Officer_Common_407")))));
			Link.l1 = StringFromKey("Officer_Common_410");
			Link.l1.go = "exit_bad";
			Link.l2 = StringFromKey("Officer_Common_411");
			Link.l2.go = "3_exitFire";
			if (sti(Pchar.money) >= sti(NPChar.rank) * 500)
			{
				Link.l3 = StringFromKey("Officer_Common_412", FindMoneyString(sti(NPChar.rank) * 500));
				Link.l3.go = "Get_out_A3_ForMoney";
			}
		break;

		case "Get_out_A3_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank) * 500)));
			ChangeCharacterReputation(pchar, 1);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = StringFromKey("Officer_Common_416", LinkRandPhrase(
						StringFromKey("Officer_Common_413"),
						StringFromKey("Officer_Common_414"),
						StringFromKey("Officer_Common_415")));
			Link.l1 = StringFromKey("Officer_Common_417", pchar);
			Link.l1.go = "3_exitFire";
		break;

		case "Get_out_A3_strife":
			dialog.text = StringFromKey("Officer_Common_421", LinkRandPhrase(
						StringFromKey("Officer_Common_418"),
						StringFromKey("Officer_Common_419", npchar),
						StringFromKey("Officer_Common_420")));
			Link.l1 = StringFromKey("Officer_Common_422", pchar);
			Link.l1.go = "exit_bad";
			if (sti(Pchar.money) >= sti(NPChar.rank) * 500)
			{
				Link.l2 = StringFromKey("Officer_Common_423", FindMoneyString(sti(NPChar.rank) * 500));
				Link.l2.go = "Get_out_A3_ForMoney";
				Link.l3 = StringFromKey("Officer_Common_424", npchar);
				Link.l3.go = "Return_items_A3";
			}
			Link.l4 = StringFromKey("Officer_Common_425", pchar);
			Link.l4.go = "Get_out_A3_strife_1";
		break;

		case "Return_items_A3":
			dialog.text = StringFromKey("Officer_Common_426", FindMoneyString(sti(NPChar.rank) * 1000));
			Link.l1 = StringFromKey("Officer_Common_427");
			Link.l1.go = "3_Get_out_chang";
			Link.l2 = StringFromKey("Officer_Common_428", pchar);
			Link.l2.go = "Get_out_A3_strife_1";
		break;

		case "Get_out_A3_strife_1":
			dialog.text = StringFromKey("Officer_Common_429", npchar, pchar);
			Link.l1 = StringFromKey("Officer_Common_430");
			Link.l1.go = "Get_out_A3_strife_death";
		break;

		case "Get_out_A3_strife_death":
			ChangeCharacterReputation(pchar, -1);
			OfficersReaction("bad");
			dialog.text = StringFromKey("Officer_Common_431");
			Link.l1 = StringFromKey("Officer_Common_432");
			Link.l1.go = "Get_out_fight";
			if (Number_Group_People(LAI_GROUP_PLAYER, 1) > 2)//если потенциальной подмоги больше двух
			{
				Link.l2 = StringFromKey("Officer_Common_433");
				Link.l2.go = "Get_out_chicken_fight";
			}
			else if (Number_Group_People(LAI_GROUP_PLAYER, 1) > 1) //если один потенциальный помощьник
			{
				Link.l2 = StringFromKey("Officer_Common_434", npchar);
				Link.l2.go = "Get_out_chicken_fight";
			}
		break;

		case "Get_out_A4":
			dialog.text = StringFromKey("Officer_Common_443", RandPhraseSimple(
						StringFromKey("Officer_Common_438", LinkRandPhrase(
								StringFromKey("Officer_Common_435"),
								StringFromKey("Officer_Common_436"),
								StringFromKey("Officer_Common_437"))),
						StringFromKey("Officer_Common_442", LinkRandPhrase(
								StringFromKey("Officer_Common_439"),
								StringFromKey("Officer_Common_440"),
								StringFromKey("Officer_Common_441")))));
			Link.l1 = StringFromKey("Officer_Common_444");
			Link.l1.go = "exit_good";
			Link.l2 = StringFromKey("Officer_Common_447", RandPhraseSimple(
						StringFromKey("Officer_Common_445"),
						StringFromKey("Officer_Common_446")));
			Link.l2.go = "4_exitFire";
			if (sti(Pchar.money) >= sti(NPChar.rank) * 500)
			{
				Link.l3 = StringFromKey("Officer_Common_448", FindMoneyString(sti(NPChar.rank) * 500));
				Link.l3.go = "Get_out_A4_ForMoney";
			}
			Link.l4 = StringFromKey("Officer_Common_449", pchar);
			Link.l4.go = "Return_items_A4";
		break;

		case "Get_out_A4_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank) * 500)));
			ChangeCharacterReputation(pchar, 1);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = StringFromKey("Officer_Common_453", LinkRandPhrase(
						StringFromKey("Officer_Common_450"),
						StringFromKey("Officer_Common_451"),
						StringFromKey("Officer_Common_452")));
			Link.l1 = StringFromKey("Officer_Common_454");
			Link.l1.go = "4_exitFire";
		break;

		case "Return_items_A4":
			if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
			{
				dialog.text = StringFromKey("Officer_Common_458", LinkRandPhrase(
							StringFromKey("Officer_Common_455"),
							StringFromKey("Officer_Common_456"),
							StringFromKey("Officer_Common_457")));
				Link.l1 = StringFromKey("Officer_Common_459");
				Link.l1.go = "4_Get_out_chang";
			}
			else
			{
				dialog.text = StringFromKey("Officer_Common_462", RandPhraseSimple(
							StringFromKey("Officer_Common_460", FindMoneyString(sti(NPChar.rank) * 1000)),
							StringFromKey("Officer_Common_461", FindMoneyString(sti(NPChar.rank) * 1000))));
				if (sti(Pchar.money) >= sti(NPChar.rank) * 1000)
				{
					Link.l1 = StringFromKey("Officer_Common_463");
					Link.l1.go = "5_Get_out_chang";
				}
				Link.l2 = StringFromKey("Officer_Common_464", npchar, pchar);
				Link.l2.go = "Get_out_A4_strife";
				Link.l3 = StringFromKey("Officer_Common_465", pchar, npchar);
				Link.l3.go = "exit_bad1";
			}
		break;

		case "Get_out_A4_strife":
			ChangeCharacterReputation(pchar, -1);
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = StringFromKey("Officer_Common_466");
			Link.l1 = StringFromKey("Officer_Common_467");
			//Link.l1 = RandPhraseSimple("Сейчас ты услышишь, как звенит мой клинок!", "Значит, тебя унесут вперёд ногами!");
			Link.l1.go = "Get_out_fight";
			if (Number_Group_People(LAI_GROUP_PLAYER, 1) > 1)//если есть потенциальная подмога
			{
				Link.l2 = StringFromKey("Officer_Common_468");
				Link.l2.go = "Get_out_chicken_fight";
			}
		break;
		//HardCoffee попытка разнообразить схватки с уволняемыми офицерами -->
		case "Get_out_chicken_fight": //толпой валим офицера
			if (Npchar.location == Get_My_Cabin() || Npchar.location == "My_Campus")
			{
				//HardCoffee фиксы застревания сидячих офицеров
				if (LAI_TYPE_SIT == Npchar.chr_ai.type) PlaceCharacter(Npchar, "rld", PChar.location);
			}
			CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
			RemoveCharacterCompanion(pchar, Npchar);
			LAi_CharacterDisableDialog(NPChar);
			LAi_SetWarriorTypeNoGroup(NPChar);
			NPChar.location = "";
			Npchar.LifeDay = 0;
			LAi_group_MoveCharacter(Npchar, LAI_GROUP_TmpEnemy);
			LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);

			if (HasStrEx(PChar.location, "_tavern,_store", "|"))
			{
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "CannotFightCurLocation");
				LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "MainHeroFightModeOff_NoLock");
			}
			else if (HasStrEx(PChar.location, "My_Cabin,My_Campus,My_Deck", "|"))
			{
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
				SetPrisonerLocationToNone();
				Reset_Officers_InCabin(); //поднять сидячих офицеров
				chrDisableReloadToLocation = true; //Закроем локацию, чтобы гг не сбежал
			}
			LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			OfficersReaction("bad"); //за базар надо отвечать самостоятельно
			AddCharacterExpToSkill(pchar, "Leadership", -100);
			ChangeCharacterReputation(pchar, -1);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//test а это типо дуэль, но, по факту только на корабле, в таверне и магазине. Во всех остальных случаях - толпа будет валить оффа
		//ограничения на локацию связаны с тем, что не понятно, что будет происходить при, скажем, потенциальном "Бое за панаму" или в захваченном городе
		//Может стоит ограничить возможность увольнения офов только некоторыми локациями?
		case "Get_out_fight":
			if (Npchar.location == Get_My_Cabin() || Npchar.location == "My_Campus")
			{
				//HardCoffee фиксы застревания сидячих офицеров
				if (LAI_TYPE_SIT == Npchar.chr_ai.type) PlaceCharacter(Npchar, "rld", PChar.location);
			}
			CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
			RemoveCharacterCompanion(pchar, Npchar); //на всякий случай, если пытаемся выгнать компаньона
			LAi_CharacterDisableDialog(NPChar);
			LAi_SetWarriorTypeNoGroup(NPChar);
			NPChar.location = "";    //иначе при повторном заходе на локацию будет зомби
			Npchar.LifeDay = 0;
			LAi_group_MoveCharacter(Npchar, LAI_GROUP_TmpEnemy);
			LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
			if (HasStrEx(PChar.location, "_tavern,_store", "|"))
			{
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "CannotFightCurLocation");
				LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "MainHeroFightModeOff_NoLock");
			}
			else if (HasStrEx(PChar.location, "My_Cabin,My_Campus,My_Deck", "|")) //очистим локацию от присутствующих, чтобы не мешались
			{
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
				SetOfficersLocationToNone();
				CompanionSaveTasks();
				SetPrisonerLocationToNone();
				chrDisableReloadToLocation = true;
			}
			OfficersReaction("good"); //все любят посмотреть на хороший мордобой
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//HardCoffee попытка разнообразить схватки с уволняемыми офицерами <--

		case "exit_bad":
		// Npchar.loyality = makeint(Npchar.loyality) - 3;
			ChangeCharacterLoyality(Npchar, -3);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_bad1":
		// Npchar.loyality = makeint(Npchar.loyality) - 2;
			ChangeCharacterLoyality(Npchar, -2);
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterReputation(pchar, -1);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_good":
		// Npchar.loyality = makeint(Npchar.loyality) - 1;
			ChangeCharacterLoyality(Npchar, -1);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "Fired_1":
			Diag.TempNode = "Fired_1";
			dialog.text = StringFromKey("Officer_Common_469");
			Link.l1 = StringFromKey("Officer_Common_472", RandPhraseSimple(
						StringFromKey("Officer_Common_470"),
						StringFromKey("Officer_Common_471")));
			Link.l1.go = "Exit";
		break;

		case "Fired_2":
			Diag.TempNode = "Fired_2";
			dialog.text = StringFromKey("Officer_Common_473");
			Link.l1 = StringFromKey("Officer_Common_474", pchar);
			Link.l1.go = "Exit";
		break;

		case "Fired_3":
			Diag.TempNode = "Fired_3";
			dialog.text = StringFromKey("Officer_Common_475");
			Link.l1 = StringFromKey("Officer_Common_476");
			Link.l1.go = "Exit";
		break;

		case "Fired_4":
			Diag.TempNode = "Fired_4";
			dialog.text = StringFromKey("Officer_Common_477", npchar);
			Link.l1 = StringFromKey("Officer_Common_478", npchar);
			Link.l1.go = "Exit";
		break;

		// boal 05.09.03 offecer need to go to abordage -->
		case "Boal_Stay":
		//SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
		//Log_SetStringToLog(Npchar.id +" "+Npchar.index);
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerStay");
			Diag.TempNode = "Hired";
			dialog.text = StringFromKey("Officer_Common_479");
			Link.l1 = StringFromKey("Officer_Common_480");
			Link.l1.go = "Exit";
			Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
		break;

		case "Boal_Follow":
			SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
			Diag.TempNode = "Hired";
			dialog.text = StringFromKey("Officer_Common_481");
			Link.l1 = StringFromKey("Officer_Common_482");
			Link.l1.go = "Exit";
		break;
		// boal 05.09.03 offecer need to go to abordage <--

		//////////////////////////////    офицер-наместник -->
		case "Gover_Hire":
			dialog.Text = StringFromKey("Officer_Common_483");
			Link.l1 = StringFromKey("Officer_Common_484");
			Link.l1.go = "Exit_Gover_Hire";
			Link.l2 = StringFromKey("Officer_Common_485", pchar);
			Link.l2.go = "Exit";
			Diag.TempNode = "Hired";
		break;

		case "Exit_Gover_Hire":
			sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
			attr = sld.id + "_townhall";
			if (sld.id == "Villemstad") attr += 2;

			// снимем пассажира -->
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			// снимем пассажира <--
			sld.OfficerIdx = sti(NPChar.index);
			ChangeCharacterAddressGroup(NPChar, attr, "sit", "sit1");
			LAi_SetHuberTypeNoGroup(NPChar);
			LAi_SetImmortal(NPChar, true);
			SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
			SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
			SaveCurrentNpcQuestDateParam(NPChar, "GoverHiredDate");
			LAi_LoginInCaptureTown(NPChar, true);
			//  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
			AddQuestRecord("Gen_CityCapture", "t3_1");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
			Diag.CurrentNode = "Gover_Main";
			DialogExit();
		break;

		case "Gover_Main":
			iTemp = GetNpcQuestPastDayParam(NPChar, "GoverTalkDate");
			if (iTemp > 0)
				dialog.Text = StringFromKey("Officer_Common_486", FindDaysString(iTemp));
			else
				dialog.Text = StringFromKey("Officer_Common_487");
			Link.l1 = StringFromKey("Officer_Common_488", npchar);
			Link.l1.go = "Gover_Tax";
			Link.l8 = StringFromKey("Officer_Common_489", npchar);
			Link.l8.go = "Gover_Fire";
			Link.l9 = StringFromKey("Officer_Common_490");
			Link.l9.go = "Exit";
			Diag.TempNode = "Gover_Main";
			SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
		break;

		case "Gover_Tax":
			if (sti(NPChar.Gover_Tax_Sum) > 0)
			{
				dialog.Text = StringFromKey("Officer_Common_491", npchar, FindMoneyString(iFortValue * iTax), FindDaysString(iTemp), FindMoneyString(sti(NPChar.Gover_Tax_Sum)));
				Link.l1 = StringFromKey("Officer_Common_492");
				Link.l1.go = "Gover_Tax_Get";
				Link.l2 = StringFromKey("Officer_Common_493");
				Link.l2.go = "Exit";
				break;
			}
			if (GetNpcQuestPastDayParam(NPChar, "GoverHiredDate") < 1)
			{
				dialog.Text = StringFromKey("Officer_Common_494", npchar, UpperFirst(GetAddress_Form(NPChar)));
				Link.l1 = StringFromKey("Officer_Common_497", RandPhraseSimple(
							StringFromKey("Officer_Common_495"),
							StringFromKey("Officer_Common_496")));
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.Text = StringFromKey("Officer_Common_498", npchar);
				Link.l1 = StringFromKey("Officer_Common_499");
				Link.l1.go = "Exit";
			}
		break;

		case "Gover_Tax_Get":
			SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
			AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));

			Diag.CurrentNode = "Gover_Main";
			DialogExit();
		break;

		case "Gover_Fire":
			if (NPChar.Gover_Tax_Sum != 0)
			{
				dialog.Text = StringFromKey("Officer_Common_503", npchar, LinkRandPhrase(
							StringFromKey("Officer_Common_500"),
							StringFromKey("Officer_Common_501"),
							StringFromKey("Officer_Common_502")), FindMoneyString(sti(NPChar.Gover_Tax_Sum)));
				Link.l8 = StringFromKey("Officer_Common_504");
				Link.l8.go = "exit_hire";
				AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));
				SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
			}
			else
			{
				dialog.Text = StringFromKey("Officer_Common_505");
				Link.l8 = StringFromKey("Officer_Common_506");
				Link.l8.go = "exit_hire";
			}
			Diag.TempNode = "Hired";
			sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
			DeleteAttribute(sld, "OfficerIdx");
			LAi_SetImmortal(NPChar, false);
			//  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
			AddQuestRecord("Gen_CityCapture", "t3_2");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
		//  СЖ <--
		break;
		//////////////////////////////    офицер-наместник <--

		case "Companion_TaskBoardingNo":
			dialog.Text = StringFromKey("Officer_Common_507");
			Link.l1 = StringFromKey("Officer_Common_508");
			Link.l1.go = "FallOut";
			link.l2 = StringFromKey("Officer_Common_509");
			link.l2.go = "goToExit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = StringFromKey("Officer_Common_510");
			Link.l1 = StringFromKey("Officer_Common_511");
			Link.l1.go = "FallOut";
			link.l2 = StringFromKey("Officer_Common_512");
			link.l2.go = "goToExit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = StringFromKey("Officer_Common_513");
			Link.l1 = StringFromKey("Officer_Common_514");
			Link.l1.go = "FallOut";
			link.l2 = StringFromKey("Officer_Common_515");
			link.l2.go = "goToExit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = StringFromKey("Officer_Common_516");
			Link.l1 = StringFromKey("Officer_Common_517");
			Link.l1.go = "FallOut";
			link.l2 = StringFromKey("Officer_Common_518");
			link.l2.go = "goToExit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;

		case "goToExit": //HardCoffee выгнать кого-либо из каюты
			if (CheckAttribute(NPChar, "IsCompanionClone"))
			{
				ThisCompanionSaveTasks();
				NPChar.IsCompanionClone.SaveTasks = true;
				LAi_MethodDelay("ThisCompanionSaveTasks", 4.0);
			}
			if (CheckAttribute(loadedLocation, "locators.reload.reload1"))
			{
				LAi_SetActorTypeNoGroup(NPChar);
				LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", 5.0);
			}
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "beInCabin": //hardCoffee на случай, если гг боится отстаться в кибитке один
			dialog.Text = StringFromKey("Officer_Common_519");
			NPChar.Tasks.beInCabin = true;
			Link.l9 = StringFromKey("Officer_Common_520");
			Link.l9.go = "FallOut";
		break;
		case "outOfCabin":
			dialog.Text = StringFromKey("Officer_Common_521");
			NPChar.Tasks.beInCabin = false;
			Link.l9 = StringFromKey("Officer_Common_522");
			Link.l9.go = "FallOut";
			if (Get_My_Cabin() == NPChar.location)
			{
				Link.l10 = StringFromKey("Officer_Common_523");
				Link.l10.go = "goToExit";
			}
		break;

		case "FallOut": //HardCoffee TODO: команда разойтись (в диалоге это "вольно")
		//планируется добавить сюда возможность ходить по каюте
		//LAi_SetCitizenType(NPChar);
		//LAi_SetWarriorType(NPChar);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		// Самостоятельное плавание компаньона -->
		case "CompanionTravel":
			if (GetAttrValue(PChar, "CompanionTravel") == 3) // Если уже троих отпустил
			{
				dialog.Text = StringFromKey("Officer_Common_524");
				Link.l1 = StringFromKey("Officer_Common_525", npchar);
				Link.l1.go = "exit";
				break;
			}

			dialog.Text = StringFromKey("Officer_Common_526");
			for (iTemp = 0; iTemp < MAX_COLONIES; iTemp++)
			{
				sld = &colonies[iTemp];
				attr = sld.ID;
				if (sld.nation == "none" || sld.nation == PIRATE || attr == "Panama" || attr == "FortOrange") continue;
				attrLoc = "l" + iTemp;
				Link.(attrLoc) = StringFromKey("Officer_Common_527", XI_ConvertString("Colony" + attr + "Pre"));
				Link.(attrLoc).go = "CompanionTravelToColony_" + attr;
			}
			Link.l99 = StringFromKey("Officer_Common_528", pchar);
			Link.l99.go = "exit";
		break;

		case "CompanionTravel_EnemyColony":
			dialog.Text = StringFromKey("Officer_Common_529");
			Link.l1 = StringFromKey("Officer_Common_530");
			Link.l1.go = "exit";
		break;

		case "CompanionTravel_NoCrew":
			dialog.Text = StringFromKey("Officer_Common_531");
			Link.l1 = StringFromKey("Officer_Common_532");
			Link.l1.go = "exit";
		break;

		case "CompanionTravel_NoFood":
			dialog.Text = StringFromKey("Officer_Common_533");
			Link.l1 = StringFromKey("Officer_Common_534", npchar);
			Link.l1.go = "exit";
		break;

		case "CompanionTravel_NoHP":
			dialog.Text = StringFromKey("Officer_Common_535", npchar);
			Link.l1 = StringFromKey("Officer_Common_536", npchar);
			Link.l1.go = "exit";
		break;

		case "CompanionTravel_PrepareStart":
			dialog.Text = StringFromKey("Officer_Common_537", XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen"), sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days));
			Link.l1 = StringFromKey("Officer_Common_538");
			Link.l1.go = "CompanionTravel_PrepareStart_2";
			Link.l2 = StringFromKey("Officer_Common_539");
			Link.l2.go = "exit";
		break;

		case "CompanionTravel_PrepareStart_2":
			dialog.Text = StringFromKey("Officer_Common_540");
			Link.l1 = StringFromKey("Officer_Common_541");
			Link.l1.go = "CompanionTravel_Start";
		break;

		case "CompanionTravel_Start":
			Diag.CurrentNode = "CompanionTravel_LastNode";
			NPChar.quest.meeting = true;
			CompanionTravel_SetTraveller(NPChar);
			DialogExit();
		break;

		case "CompanionTravel_LastNode":
			Dialog.text = StringFromKey("Officer_Common_544", RandPhraseSimple(
						StringFromKey("Officer_Common_542"),
						StringFromKey("Officer_Common_543", XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Pre"))));
			link.l2 = "...";
			link.l2.go = "Exit";
			Diag.TempNode = "CompanionTravel_LastNode";
		break;

		case "CompanionTravel_ToSquadron":
			if (GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				dialog.text = StringFromKey("Officer_Common_545");
				Link.l1 = StringFromKey("Officer_Common_546");
				Link.l1.go = "exit";
				Diag.TempNode = "hired";
				CompanionTravel_DeleteSpecialShipAttributes(NPChar);
				Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID); // Потрем группу
				SetCompanionIndex(PChar, -1, sti(NPChar.index));
				PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
				DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				dialog.text = StringFromKey("Officer_Common_547");
				Link.l1 = StringFromKey("Officer_Common_548");
				Link.l1.go = "exit";
				Diag.TempNode = "CompanionTravel_ToSquadron_2";
				NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2"; // ставим снова эту ноду
			}
		break;

		case "CompanionTravel_ToSquadron_2":
			dialog.text = StringFromKey("Officer_Common_549", npchar);
			if (GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				Link.l1 = StringFromKey("Officer_Common_550", NPChar.name);
				Link.l1.go = "exit";
				Diag.TempNode = "hired";
				CompanionTravel_DeleteSpecialShipAttributes(NPChar);
				Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID);
				SetCompanionIndex(PChar, -1, sti(NPChar.index));
				PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
				DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				Link.l1 = StringFromKey("Officer_Common_551");
				Link.l1.go = "exit";
				Diag.TempNode = "CompanionTravel_ToSquadron_2";
				NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2";
			}
		break;
		// <-- Самостоятельное плавание компаньона

		// KZ > Взаимодействие с боцманом
		case "TalkBoatswain_Start":
			dialog.text = StringFromKey("Officer_Common_552");

			Link.l1 = StringFromKey("Officer_Common_553");
			Link.l1.go = "Hired";

			if (CheckCharacterPerk(pchar, "LootCollection") || CheckCharacterPerk(NPChar, "LootCollection"))
			{
				Link.l2 = StringFromKey("Officer_Common_554", NPChar.name);
				Link.l2.go = "TalkBoatswain_LootingMode";
			}

			if (CheckCharacterPerk(NPChar, "Mentor") || CheckCharacterPerk(pchar, "Mentor"))
			{
				Link.l3 = StringFromKey("Officer_Common_555", NPChar.name);
				Link.l3.go = "TalkBoatswain_Training_Prepare";
			}
		break;

		// > Сбор трофеев
		case "TalkBoatswain_LootingMode":
			if (CheckAttribute(&TEV, "LootingTempMode"))
				Dialog.Text = StringFromKey("Officer_Common_556");
			else
				Dialog.Text = StringFromKey("Officer_Common_557");

			DeleteAttribute(&TEV, "LootingTempMode");

			if (sti(TEV.LootCollector.Mode) != 0)
			{
				Link.l1 = StringFromKey("Officer_Common_558");
				Link.l1.go = "TalkBoatswain_LootingMode_0";
			}

			if (sti(TEV.LootCollector.Mode) != 1)
			{
				Link.l2 = StringFromKey("Officer_Common_559", pchar);
				Link.l2.go = "TalkBoatswain_LootingMode_1";
			}

			if (sti(TEV.LootCollector.Mode) != 2)
			{
				Link.l3 = StringFromKey("Officer_Common_560");
				Link.l3.go = "TalkBoatswain_LootingMode_2";
			}

			if (sti(TEV.LootCollector.Mode) != 3)
			{
				Link.l4 = StringFromKey("Officer_Common_561");
				Link.l4.go = "TalkBoatswain_LootingMode_3";
			}

			Link.l5 = StringFromKey("Officer_Common_562", NPChar.name);
			Link.l5.go = "Hired";
		break;

		case "TalkBoatswain_LootingMode_0":
			Dialog.Text = StringFromKey("Officer_Common_563");
			TEV.LootingTempMode = 0;
			Link.l1 = StringFromKey("Officer_Common_564");
			Link.l1.go = "TalkBoatswain_LootingMode_Exit";
			Link.l2 = StringFromKey("Officer_Common_565", pchar);
			Link.l2.go = "TalkBoatswain_LootingMode";
		break;

		case "TalkBoatswain_LootingMode_1":
			Dialog.Text = StringFromKey("Officer_Common_566");
			TEV.LootingTempMode = 1;
			Link.l1 = StringFromKey("Officer_Common_567");
			Link.l1.go = "TalkBoatswain_LootingMode_Exit";
			Link.l2 = StringFromKey("Officer_Common_568");
			Link.l2.go = "TalkBoatswain_LootingMode";
		break;

		case "TalkBoatswain_LootingMode_2":
			Dialog.Text = StringFromKey("Officer_Common_569");
			TEV.LootingTempMode = 2;
			Link.l1 = StringFromKey("Officer_Common_570");
			Link.l1.go = "TalkBoatswain_LootingMode_Exit";
			Link.l2 = StringFromKey("Officer_Common_571");
			Link.l2.go = "TalkBoatswain_LootingMode";
		break;

		case "TalkBoatswain_LootingMode_3":
			Dialog.Text = StringFromKey("Officer_Common_572");
			TEV.LootingTempMode = 3;
			Link.l1 = StringFromKey("Officer_Common_573");
			Link.l1.go = "TalkBoatswain_LootingMode_Exit";
			Link.l2 = StringFromKey("Officer_Common_574");
			Link.l2.go = "TalkBoatswain_LootingMode";
		break;

		case "TalkBoatswain_LootingMode_Exit":
			Log_Clear();

			if (CheckAttribute(&TEV, "LootingTempMode") && sti(TEV.LootingTempMode) >= 0)
			{
				switch (sti(TEV.LootingTempMode))
				{
					case 0:
						TEV.LootCollector.Mode = 0;
						Log_Info(StringFromKey("InfoMessages_144"));
					break;
					case 1:
						TEV.LootCollector.Mode = 1;
						Log_Info(StringFromKey("InfoMessages_145"));
					break;
					case 2:
						TEV.LootCollector.Mode = 2;
						Log_Info(StringFromKey("InfoMessages_146"));
					break;
					case 3:
						TEV.LootCollector.Mode = 3;
						Log_Info(StringFromKey("InfoMessages_147"));
						Log_Info(StringFromKey("InfoMessages_143", GetHeroNameDat(startHeroType)));
					break;
				}

				PlaySound("Notebook_1");
			}

			DialogExit();
			DeleteAttribute(&TEV, "LootingTempMode");
		//			LaunchInfoMessage(4);
		break;
		// < Сбор трофеев

		// > Тренировка команды, на базе кода от Qwerry, St.
		case "TalkBoatswain_Training_Prepare":
			Diag.TempNode = "Hired";

			if (sti(PChar.Ship.Type) == SHIP_NOTUSED && GetCompanionQuantity(PChar) < 2)
			{
				dialog.text = StringFromKey("Officer_Common_575");
				Link.l1 = StringFromKey("Officer_Common_576", npchar);
				Link.l1.go = "Hired";
				break;
			}

			if (bSeaActive && Sea_FindNearColony(false) == "none") //Rosarak. при false нас интересует только бухта, где мы останавливались, даже если это необитайка
			{
				dialog.text = StringFromKey("Officer_Common_577");
				Link.l1 = StringFromKey("Officer_Common_578", npchar, NPChar.name);
				Link.l1.go = "Hired";
				break;
			}

			dialog.text = StringFromKey("Officer_Common_579");
			link.l1 = StringFromKey("Officer_Common_580");
			link.l1.go = "TalkBoatswain_Training_Sail_Prepare";
			link.l2 = StringFromKey("Officer_Common_581");
			link.l2.go = "TalkBoatswain_Training_Cannon_Prepare";
			link.l3 = StringFromKey("Officer_Common_582");
			link.l3.go = "TalkBoatswain_Training_Boarding_Prepare";
			link.l4 = StringFromKey("Officer_Common_583");
			link.l4.go = "Hired";
		break;

		case "TalkBoatswain_Training_Sail_Prepare":
			TEV.CT.Crew = "Sailors";
			TEV.CT.SkillValue.0 = GetSummonSkillFromNameSimple(pchar, SKILL_SAILING);

			if (GetCompanionQuantity(PChar) > 1)
			{
				Dialog.Text = StringFromKey("Officer_Common_584");
				Link.l1 = StringFromKey("Officer_Common_585", GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Pre")), Pchar.Ship.Name);
				Link.l1.go = "TalkBoatswain_Training_Calculate_Flagship";

				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);

					if (iTemp > 0)
					{
						chr = GetCharacter(iTemp);
						sld = &RealShips[sti(chr.ship.type)];

						if (GetRemovable(chr))
						{
							attr = i;
							TEV.CT.SkillValue.(attr) = GetSummonSkillFromNameSimple(chr, SKILL_SAILING);
							TEV.CT.Who.(attr) = chr.id;
							attr = "l" + (i + 1);
							Link.(attr) = StringFromKey("Officer_Common_586", chr, GetStrSmallRegister(XI_ConvertString(sld.BaseName + "Pre")), chr.Ship.name, GetFullName(chr));
							Link.(attr).go = "TalkBoatswain_Training_Calculate_Companion_" + i;
						}
					}
				}
			}
			else
			{
				Dialog.Text = StringFromKey("Officer_Common_587");
				Link.l1 = StringFromKey("Officer_Common_588");
				Link.l1.go = "TalkBoatswain_Training_Calculate_Flagship";
			}

			Link.l98 = StringFromKey("Officer_Common_589");
			Link.l98.go = "Hired";
			Link.l99 = StringFromKey("Officer_Common_590");
			Link.l99.go = "Exit";
		break;

		case "TalkBoatswain_Training_Cannon_Prepare":
			TEV.CT.Crew = "Cannoners";
			TEV.CT.SkillValue.0 = (GetSummonSkillFromNameSimple(PChar, SKILL_ACCURACY) + GetSummonSkillFromNameSimple(PChar, SKILL_CANNONS)) / 2;

			if (GetCompanionQuantity(PChar) > 1)
			{
				Dialog.Text = StringFromKey("Officer_Common_591");
				Link.l1 = StringFromKey("Officer_Common_592", GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Pre")), Pchar.Ship.Name);
				Link.l1.go = "TalkBoatswain_Training_Calculate_Flagship";

				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);

					if (iTemp > 0)
					{
						chr = GetCharacter(iTemp);
						sld = &RealShips[sti(chr.ship.type)];

						if (GetRemovable(chr))
						{
							attr = i;
							TEV.CT.SkillValue.(attr) = (GetSummonSkillFromNameSimple(chr, SKILL_ACCURACY) + GetSummonSkillFromNameSimple(chr, SKILL_CANNONS)) / 2;
							TEV.CT.Who.(attr) = chr.id;
							attr = "l" + (i + 1);
							Link.(attr) = StringFromKey("Officer_Common_593", chr, GetStrSmallRegister(XI_ConvertString(sld.BaseName + "Pre")), chr.Ship.name, GetFullName(chr));
							Link.(attr).go = "TalkBoatswain_Training_Calculate_Companion_" + i;
						}
					}
				}
			}
			else
			{
				Dialog.Text = StringFromKey("Officer_Common_594");
				Link.l1 = StringFromKey("Officer_Common_595");
				Link.l1.go = "TalkBoatswain_Training_Calculate_Flagship";
			}

			Link.l98 = StringFromKey("Officer_Common_596");
			Link.l98.go = "Hired";
			Link.l99 = StringFromKey("Officer_Common_597");
			Link.l99.go = "Exit";
		break;

		case "TalkBoatswain_Training_Boarding_Prepare":
			TEV.CT.Crew = "Soldiers";
			TEV.CT.SkillValue.0 = GetSummonSkillFromNameSimple(PChar, SKILL_GRAPPLING);

			if (GetCompanionQuantity(PChar) > 1)
			{
				Dialog.Text = StringFromKey("Officer_Common_598");
				Link.l1 = StringFromKey("Officer_Common_599", GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Pre")), Pchar.Ship.Name);
				Link.l1.go = "TalkBoatswain_Training_Calculate_Flagship";

				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);

					if (iTemp > 0)
					{
						chr = GetCharacter(iTemp);
						sld = &RealShips[sti(chr.ship.type)];

						if (GetRemovable(chr))
						{
							attr = i;
							TEV.CT.SkillValue.(attr) = GetSummonSkillFromNameSimple(chr, SKILL_GRAPPLING);
							TEV.CT.Who.(attr) = chr.id;
							attr = "l" + (i + 1);
							Link.(attr) = StringFromKey("Officer_Common_600", chr, GetStrSmallRegister(XI_ConvertString(sld.BaseName + "Pre")), chr.Ship.name, GetFullName(chr));
							Link.(attr).go = "TalkBoatswain_Training_Calculate_Companion_" + i;
						}
					}
				}
			}
			else
			{
				Dialog.Text = StringFromKey("Officer_Common_601");
				Link.l1 = StringFromKey("Officer_Common_602");
				Link.l1.go = "TalkBoatswain_Training_Calculate_Flagship";
			}

			Link.l98 = StringFromKey("Officer_Common_603");
			Link.l98.go = "Hired";
			Link.l99 = StringFromKey("Officer_Common_604");
			Link.l99.go = "Exit";
		break;

		case "TalkBoatswain_Training_Calculate_Flagship":
			if (sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = StringFromKey("Officer_Common_605");
				Link.l1 = StringFromKey("Officer_Common_606", npchar);
				Link.l1.go = "Hired";
				break;
			}

			if (GetCrewQuantity(pchar) < 5)
			{
				dialog.text = StringFromKey("Officer_Common_607");
				Link.l1 = StringFromKey("Officer_Common_608", pchar);
				Link.l1.go = "Hired";
				break;
			}

			if (CheckAttribute(&TEV, "CrewTraining.Flagship") && TEV.CrewTraining.Flagship == GetCurrentDate())
			{
				dialog.text = StringFromKey("Officer_Common_609");
				Link.l1 = StringFromKey("Officer_Common_610");
				Link.l1.go = "Hired";
				break;
			}

			TEV.CT.Who = pchar.id;
			TEV.CT.GainExp = (stf(TEV.CT.SkillValue.0) - GetCrewExp(pchar, TEV.CT.Crew)) / MOD_SKILL_ENEMY_RATE;
			TEV.CT.Price = GetCharacterRaiseCrewMoraleMoney(pchar);

			if (sti(TEV.CT.GainExp) >= 1)
			{
				dialog.text = StringFromKey("Officer_Common_611", pchar.lastname, FindMoneyString(sti(TEV.CT.Price)));

				if (sti(Pchar.money) >= sti(TEV.CT.Price))
				{
					link.l1 = StringFromKey("Officer_Common_612", NPChar.name);
					link.l1.go = "TalkBoatswain_Training_Start";
					link.l2 = StringFromKey("Officer_Common_613");
					link.l2.go = "Hired";
					break;
				}

				link.l1 = StringFromKey("Officer_Common_614", TEV.CT.Price);
				link.l1.go = "Exit";
				break;
			}

			dialog.text = StringFromKey("Officer_Common_615");
			link.l1 = StringFromKey("Officer_Common_616");
			link.l1.go = "Hired";
			link.l2 = StringFromKey("Officer_Common_617");
			link.l2.go = "TalkBoatswain_Training_Prepare";
		break;

		case "TalkBoatswain_Training_Calculate_Companion_Result":
			attr = TEV.CT.CompanionNum;
			TEV.CT.Who = TEV.CT.Who.(attr);
			sld = characterFromId(TEV.CT.Who);
			TEV.CT.GainExp = (stf(TEV.CT.SkillValue.(attr)) - GetCrewExp(sld, TEV.CT.Crew)) / MOD_SKILL_ENEMY_RATE;
			TEV.CT.Price = GetCharacterRaiseCrewMoraleMoney(sld);

			if (GetCrewQuantity(sld) < 5)
			{
				dialog.text = StringFromKey("Officer_Common_618", sld.ship.name);
				Link.l1 = StringFromKey("Officer_Common_619", pchar);
				Link.l1.go = "Hired";
				break;
			}

			if (CheckAttribute(&TEV, "CrewTraining.Companion." + attr) && TEV.CrewTraining.Companion.(attr) == GetCurrentDate())
			{
				dialog.text = StringFromKey("Officer_Common_620", sld.ship.name);
				Link.l1 = StringFromKey("Officer_Common_621");
				Link.l1.go = "Hired";
				break;
			}

			if (sti(TEV.CT.GainExp) >= 1)
			{
				dialog.text = StringFromKey("Officer_Common_622", pchar.lastname, FindMoneyString(sti(TEV.CT.Price)));

				if (sti(Pchar.money) >= sti(TEV.CT.Price))
				{
					TEV.CT.Companion = attr;
					link.l1 = StringFromKey("Officer_Common_623", NPChar.name);
					link.l1.go = "TalkBoatswain_Training_Start";
					link.l2 = StringFromKey("Officer_Common_624");
					link.l2.go = "Hired";
					break;
				}

				link.l1 = StringFromKey("Officer_Common_625", TEV.CT.Price);
				link.l1.go = "Exit";
				break;
			}

			dialog.text = StringFromKey("Officer_Common_626", sld.ship.name);
			link.l1 = StringFromKey("Officer_Common_627");
			link.l1.go = "Hired";
			link.l2 = StringFromKey("Officer_Common_628");
			link.l2.go = "TalkBoatswain_Training_Prepare";
		break;

		case "TalkBoatswain_Training_Start":
			sld = characterFromId(TEV.CT.Who);
			TEV.CT.Price = GetCharacterRaiseCrewMoraleMoney(sld);
			ChangeCrewExp(sld, TEV.CT.Crew, stf(TEV.CT.GainExp));
			AddMoneyToCharacter(pchar, -(sti(TEV.CT.Price)));
			Statistic_AddValue(pchar, "PartitionPay", sti(TEV.CT.Price));
			PlayVoice("EvEnemy_0");

			if (sld.id == pchar.id)
				TEV.CrewTraining.Flagship = GetCurrentDate();
			else
			{
				if (CheckAttribute(&TEV, "CT.Companion"))
				{
					attr = TEV.CT.Companion;
					TEV.CrewTraining.Companion.(attr) = GetCurrentDate();
				}
			}

			DialogExit();
			AddTimeToCurrent(4, 30 + rand(30));
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_203", sld.ship.name), "", 0, 4);
			LAi_MethodDelay("LaunchFrameForm", 0);
		break;
		// < Тренировка команды
		// KZ < Взаимодействие с боцманом

		case "TalkAboutTizerDen":
			dialog.text = StringFromKey("Officer_Common_649");
			Link.l1 = StringFromKey("Officer_Common_650");
			Link.l1.go = "TalkAboutTizerDen_1";
		break;
		case "TalkAboutTizerDen_1":
			dialog.text = StringFromKey("Officer_Common_651");
			Link.l1 = StringFromKey("Officer_Common_652");
			Link.l1.go = "TalkAboutTizerDen_2";
		break;
		case "TalkAboutTizerDen_2":
			dialog.text = StringFromKey("Officer_Common_653");
			Link.l1 = StringFromKey("Officer_Common_654");
			Link.l1.go = "TalkAboutTizerDen_3";
		break;
		case "TalkAboutTizerDen_3":
			dialog.text = StringFromKey("Officer_Common_655");
			Link.l1 = StringFromKey("Officer_Common_656");
			Link.l1.go = "TalkAboutTizerDen_4";
		break;
		case "TalkAboutTizerDen_4":
			Diag.CurrentNode = "hired";
			if (CheckAttribute(npchar, "quest.capellan"))
			{
				Diag.filename    = "Population\Monk.c";
				Diag.currentnode = "capellan_4";
			}
			NPChar.quest.meeting = true;
			DialogExit();
			AddQuestRecord("ISS_PoorsMurder", "35");
			AddItemLog(pchar, "strangeNoteLSC", "1", StringFromKey("InfoMessages_135", GetItemName("strangeNoteLSC")), "Important_item");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			Lai_SetPlayerType(pchar);
		break;
	}
}

string GetOfficerType_2(ref npchar)
{
	if (CheckAttribute(Npchar, "quest.officertype_2"))
	{
		return Npchar.quest.officertype_2;
	}

	Npchar.quest.officertype_2 = "";
	if (CheckAttribute(Npchar, "quest.officertype_hobby"))
	{
		string hobbyType = Npchar.quest.officertype_hobby;
		switch (hobbyType)
		{
			case "doctor":
				Npchar.quest.officertype_2 = StringFromKey("Officer_Common_631", RandPhraseSimple(
							StringFromKey("Officer_Common_629"),
							StringFromKey("Officer_Common_630")));
				if (Npchar.quest.officertype == "navigator")
				{
					Npchar.quest.officertype_2 = StringFromKey("Officer_Common_634", RandPhraseSimple(
								StringFromKey("Officer_Common_632"),
								StringFromKey("Officer_Common_633")));
				}
			break;
			case "carpenter":
				Npchar.quest.officertype_2 = StringFromKey("Officer_Common_637", RandPhraseSimple(
							StringFromKey("Officer_Common_635"),
							StringFromKey("Officer_Common_636")));
			break;
			case "treasurer":
				Npchar.quest.officertype_2 = StringFromKey("Officer_Common_640", RandPhraseSimple(
							StringFromKey("Officer_Common_638"),
							StringFromKey("Officer_Common_639")));
			break;
			case "cannoner":
				Npchar.quest.officertype_2 = StringFromKey("Officer_Common_643", RandPhraseSimple(
							StringFromKey("Officer_Common_641"),
							StringFromKey("Officer_Common_642")));
			break;
			case "boatswain":
				Npchar.quest.officertype_2 = NPCharRepPhrase(Npchar,
						StringFromKey("Officer_Common_644"),
						StringFromKey("Officer_Common_645"));
			break;
			case "fighter_l":
				Npchar.quest.officertype_2 = StringFromKey("Officer_Common_646");
			break;
			case "fighter_h":
				Npchar.quest.officertype_2 = StringFromKey("Officer_Common_647");
			break;
			case "fighter_m":
				Npchar.quest.officertype_2 = StringFromKey("Officer_Common_648");
			break;
		}
	}
	if (Npchar.quest.officertype_2 != "")
		Npchar.quest.officertype_2 = Npchar.quest.officertype_2 + " ";

	return Npchar.quest.officertype_2;
}
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;
	int Shit, i, iContraStore;
	ref refStore;
	ref sld;
	string sPhraseNum = "0";
	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "First time":
			Diag.TempNode = "first time";
			if (CheckAttribute(PChar, "quest.Contraband.active"))
			{
				if (!CanSquadronContraband())
				{
					dialog.text = NPCStringReactionRepeat(
								StringFromKey("Smuggler_OnShore_dialog_1", pchar),
								StringFromKey("Smuggler_OnShore_dialog_2", pchar),
								StringFromKey("Smuggler_OnShore_dialog_3"),
								StringFromKey("Smuggler_OnShore_dialog_4", pchar), "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(
								StringFromKey("Smuggler_OnShore_dialog_5"),
								StringFromKey("Smuggler_OnShore_dialog_6"),
								StringFromKey("Smuggler_OnShore_dialog_7"),
								StringFromKey("Smuggler_OnShore_dialog_8", pchar), npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
					break;
				}

				if (!CanShipclassContraband())
				{
					dialog.text = NPCStringReactionRepeat(
								StringFromKey("Smuggler_OnShore_dialog_9", pchar),
								StringFromKey("Smuggler_OnShore_dialog_10", pchar),
								StringFromKey("Smuggler_OnShore_dialog_11"),
								StringFromKey("Smuggler_OnShore_dialog_12", pchar), "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(
								StringFromKey("Smuggler_OnShore_dialog_13", pchar),
								StringFromKey("Smuggler_OnShore_dialog_14"),
								StringFromKey("Smuggler_OnShore_dialog_15"),
								StringFromKey("Smuggler_OnShore_dialog_16", pchar), npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
					break;
				}

				dialog.Text = StringFromKey("Smuggler_OnShore_dialog_19", RandPhraseSimple(
							StringFromKey("Smuggler_OnShore_dialog_17", pchar),
							StringFromKey("Smuggler_OnShore_dialog_18", RandSwear())));
				Link.l1 = StringFromKey("Smuggler_OnShore_dialog_22", RandPhraseSimple(
							StringFromKey("Smuggler_OnShore_dialog_20", pchar),
							StringFromKey("Smuggler_OnShore_dialog_21", pchar)));
				Pchar.quest.Contraband.Counter = 0; // не торговали
				if (Pchar.Location == Pchar.location.from_sea)
				{
					Link.l1.go = "Exchange";
				}
				else
				{
					Link.l1.go = "No_Ship";
				}
				//по заданию губернатора, истребление контры, только эта ветка.
				if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GetArealByLocation(&locations[FindLocation(pchar.location)]))
				{
					Link.l2 = StringFromKey("Smuggler_OnShore_dialog_23", XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city + "Gen"));
					Link.l2.go = "GenQuestKillContraband_1";
				}
			}
			else
			{
				//================ METRO ====================
				//если заплатил, то разговаривают, иначе посылают
				if (CheckAttribute(PChar, "GenQuest.contraTravel.payed") && sti(PChar.GenQuest.contraTravel.payed) == true)
				{
					dialog.Text = StringFromKey("Smuggler_OnShore_dialog_26", RandPhraseSimple(
								StringFromKey("Smuggler_OnShore_dialog_24"),
								StringFromKey("Smuggler_OnShore_dialog_25")));
					//по заданию губернатора, истребление контры, только эта ветка.
					if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GetArealByLocation(&locations[FindLocation(pchar.location)]))
					{
						Link.l1 = StringFromKey("Smuggler_OnShore_dialog_27", XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city + "Gen"));
						Link.l1.go = "GenQuestKillContraband_1";
						break;
					}
					//если набрал пассажиров, в сад..
					if (GetPassengersQuantity(PChar) > 0)
					{
						dialog.Text = StringFromKey("Smuggler_OnShore_dialog_28", pchar);
						Link.l1 = StringFromKey("Smuggler_OnShore_dialog_29");
						Link.l1.go = "Exit";
						break;
					}
					//если набрал компаньонов или купил корабль себе уже, в сад..
					if (GetCompanionQuantity(PChar) > 1 || sti(PChar.ship.type) != SHIP_NOTUSED)
					{
						dialog.Text = StringFromKey("Smuggler_OnShore_dialog_32", RandPhraseSimple(
									StringFromKey("Smuggler_OnShore_dialog_30"),
									StringFromKey("Smuggler_OnShore_dialog_31")));
						Link.l1 = StringFromKey("Smuggler_OnShore_dialog_33");
						Link.l1.go = "Exit";
						break;
					}
					//типа помог отбиться, свой парень... 
					if (CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight") && sti(PChar.GenQuest.contraTravel.PatrolFight) == true)
					{
						if (chrDisableReloadToLocation) // ещё бой идёт
						{
							dialog.Text = StringFromKey("Smuggler_OnShore_dialog_34");
							Link.l1 = StringFromKey("Smuggler_OnShore_dialog_35");
							Link.l1.go = "Exit";
							break;
						}
						dialog.Text = StringFromKey("Smuggler_OnShore_dialog_38", RandPhraseSimple(
									StringFromKey("Smuggler_OnShore_dialog_36"),
									StringFromKey("Smuggler_OnShore_dialog_37", pchar)));
						ChangeContrabandRelation(PChar, 5);
						PChar.GenQuest.contraTravel.PatrolFight = false;
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
					//тут все ок, отправляемся.
					Link.l2 = StringFromKey("Smuggler_OnShore_dialog_39");
					Link.l2.go = "Exit";
					//а это патруль... 
					if ((GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) - GetFortuneBonus(1)) < frandSmall(13.0 * (1.0 - pow(0.9, sti(PChar.rank)))) && !CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight"))
					{
						PlayerRPGCheck_Skill_NotifyFail("Sneak", false);
						AddDialogExitQuest("Rand_ContrabandInterruption");
						PChar.GenQuest.contraTravel.PatrolFight = true;
					}
					else
					{
						//поместим Грея в локацию.
						refStore = CharacterFromID("Abracham_Gray");
						ChangeCharacterAddressGroup(refStore, "Ship_deck", "goto", "goto2");
						refStore.dialog.Filename = "Smuggler_Ship_dialog.c";
						refStore.dialog.CurrentNode = "Travel_talkStart";
						//поплыл, иначе RemoveTravelSmugglers грохнет всю ветку
						PChar.GenQuest.contraTravel.ship = true;
						PChar.quest.Munity = "";  // признак выхода с палубы
						SetLaunchFrameFormParam(StringFromKey("InfoMessages_204", FindDaysString(sti(Pchar.GenQuest.contraTravel.destination.days)), NewStr()),
								"Reload_To_Location", 0.1, 5.0);
						bQuestCheckProcessFreeze = true;
						WaitDate("", 0, 0, sti(Pchar.GenQuest.contraTravel.destination.days), rand(20), 0);
						bQuestCheckProcessFreeze = false;
						MakeCloneShipDeck(refStore, true); // подмена палубы
						SetLaunchFrameReloadLocationParam("Ship_deck", "reload", "reload1", "Travel_talkOnDeck");
						AddDialogExitQuest("LaunchFrameForm");
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
					//================ METRO ====================
				}
				else
				{
					// если таможня уже бежит
					if (CheckAttribute(NPChar, "ContrabandInterruption"))
					{
						if (CheckAttribute(&TEV, "ContrabandMoment.PatrolFight.End"))
						{
							sPhraseNum = NPCStringReactionRepeatNumber("block", 1, npchar, Dialog.CurrentNode);
							dialog.Text = NPCStringReactionRepeat(
										StringFromKey("Smuggler_OnShore_dialog_40"),
										StringFromKey("Smuggler_OnShore_dialog_41", pchar),
										StringFromKey("Smuggler_OnShore_dialog_42"),
										StringFromKey("Smuggler_OnShore_dialog_43"), "block", 1, npchar, Dialog.CurrentNode);
							link.l1 = HeroStringReactionRepeat(
										StringFromKey("Smuggler_OnShore_dialog_44"),
										StringFromKey("Smuggler_OnShore_dialog_45", pchar),
										StringFromKey("Smuggler_OnShore_dialog_46"),
										StringFromKey("Smuggler_OnShore_dialog_47"), npchar, Dialog.CurrentNode);
							link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);

							if (!CheckAttribute(&TEV, "ContrabandMoment.PatrolFight.End.Done"))
							{
								TEV.ContrabandMoment.PatrolFight.End.Done = true;
								ChangeContrabandRelation(PChar, 5);
								AddCharacterExpToSkill(Pchar, "Leadership", 25);
								AddCharacterExpToSkill(Pchar, "Sneak", 25);
							}

							if (sPhraseNum == "3")
							{
								Link.l2 = StringFromKey("Smuggler_OnShore_dialog_48");
								Link.l2.go = "Exit_Pre_fight";
							}
						}
						else
						{
							dialog.Text = StringFromKey("Smuggler_OnShore_dialog_49", RandSwear());
							Link.l1 = StringFromKey("Smuggler_OnShore_dialog_50");
							Link.l1.go = "Exit";
						}
					}
					else
					{
						dialog.Text = StringFromKey("Smuggler_OnShore_dialog_51");
						Link.l1 = StringFromKey("Smuggler_OnShore_dialog_52");
						Link.l1.go = "Exit";
						Link.l2 = StringFromKey("Smuggler_OnShore_dialog_53"); // сюда надо придумать какую то проверку
						Link.l2.go = "Exchange1";
						Link.l3 = StringFromKey("Smuggler_OnShore_dialog_54");
						Link.l3.go = "Exit_Pre_fight";
					}
				}
			}
		break;

		case "Exit_Pre_fight":
			ChangeContrabandRelation(pchar, -30);
			dialog.Text = StringFromKey("Smuggler_OnShore_dialog_55");
			Link.l1 = StringFromKey("Smuggler_OnShore_dialog_56");
			Link.l1.go = "Exit_fight";
		break;

		case "No_Ship":
			dialog.Text = StringFromKey("Smuggler_OnShore_dialog_57");
			Link.l1 = StringFromKey("Smuggler_OnShore_dialog_60", RandPhraseSimple(
						StringFromKey("Smuggler_OnShore_dialog_58", pchar),
						StringFromKey("Smuggler_OnShore_dialog_59", pchar)));
			Link.l1.go = "No_ship_1";
			Link.l2 = StringFromKey("Smuggler_OnShore_dialog_61");
			Link.l2.go = "Cancellation";
		break;

		case "No_ship_1":
			dialog.Text = StringFromKey("Smuggler_OnShore_dialog_62");
			Link.l1 = StringFromKey("Smuggler_OnShore_dialog_63");
			Link.l1.go = "Exit";
		break;

		case "Exit_fight":
		//DeleteAttribute(Pchar, "quest.Contraband");

			DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");

			AddSimpleRumourCity(
				StringFromKey("Smuggler_OnShore_dialog_64"), Pchar.quest.contraband.City, 3, 5, "");

			CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			LAi_group_FightGroups(LAI_GROUP_PLAYER, pchar.GenQuest.Smugglers_Group, true);
			RemoveSmugglersFromShore();
			AddDialogExitQuest("MainHeroFightModeOn");

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "Exit_Cancel":
			DeleteAttribute(Pchar, "quest.Contraband");
			CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "Cancellation":
			if (sti(Pchar.quest.Contraband.Counter) == 0)
			{
				dialog.Text = StringFromKey("Smuggler_OnShore_dialog_65");
				Link.l1 = StringFromKey("Smuggler_OnShore_dialog_66");
				Link.l1.go = "Cancellation_1";
			}
			else
			{
				dialog.Text = StringFromKey("Smuggler_OnShore_dialog_67");
				Link.l1 = StringFromKey("Smuggler_OnShore_dialog_68");
				Link.l1.go = "Finish_exit";
			}
		break;

		case "Cancellation_1":
			if (makeint(Pchar.rank) <= 3 || GetSummonSkillFromNameToOld(Pchar, SKILL_FENCING) <= 5 || GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) <= 5)
			{
				if (Rand(1) == 1)
				{
					ChangeContrabandRelation(pchar, -30);
					dialog.Text = StringFromKey("Smuggler_OnShore_dialog_69", pchar);
					Link.l1 = StringFromKey("Smuggler_OnShore_dialog_70");
					Link.l1.go = "Exit_fight";
				}
				else
				{
					ChangeContrabandRelation(pchar, -10);
					dialog.Text = StringFromKey("Smuggler_OnShore_dialog_71");
					Link.l1 = StringFromKey("Smuggler_OnShore_dialog_72");
					Link.l1.go = "Exit_cancel";
				}
			}
			else
			{
				ChangeContrabandRelation(pchar, -10);
				dialog.Text = StringFromKey("Smuggler_OnShore_dialog_73");
				Link.l1 = StringFromKey("Smuggler_OnShore_dialog_74");
				Link.l1.go = "Exit_cancel";
			}
		break;

		case "GenQuestKillContraband_1":
		//счетчик подстав по "метро"...
			if (CheckAttribute(PChar, "GenQuest.contraTravel.active") && sti(PChar.GenQuest.contraTravel.active) == true)
			{
				Statistic_AddValue(PChar, "contr_TravelKill", 1);
				ChangeContrabandRelation(pchar, -20); //репу контры вниз
			}
			dialog.Text = StringFromKey("Smuggler_OnShore_dialog_75");
			Link.l1 = StringFromKey("Smuggler_OnShore_dialog_76");
			Link.l1.go = "Exit_fight";
			ChangeContrabandRelation(PChar, -20);
		break;

		case "Exchange":
		// сама торговля -->

		// установим окружение -->
			if (sti(Pchar.quest.Contraband.Counter) == 0) // не торговали ещё
			{

				if (idRand(npchar.id + "Exchange", 11) == 3)
				{
					dialog.Text = StringFromKey("Smuggler_OnShore_dialog_77");
					Link.l1 = StringFromKey("Smuggler_OnShore_dialog_80", RandPhraseSimple(
								StringFromKey("Smuggler_OnShore_dialog_78"),
								StringFromKey("Smuggler_OnShore_dialog_79")));
					Link.l1.go = "Exit_fight";
					break;
				}

				if ((GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) - GetFortuneBonus(1)) < Rand(120)) // это морской патруль
				{
					SetCoastalGuardPursuit();
				}
				// при убегании от патруля на карту - корабли трем
				SetTimerCondition("Rand_ContrabandInterruptionAtSeaEnded", 0, 0, 2, false);// если в порту сидим, спим, то 2 день

				Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition.l1 = "MapEnter";
				Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition = "Rand_ContrabandAtSeaEnded";

			}
			// установим окружение <--
			dialog.Text = StringFromKey("Smuggler_OnShore_dialog_83", RandPhraseSimple(
						StringFromKey("Smuggler_OnShore_dialog_81", pchar),
						StringFromKey("Smuggler_OnShore_dialog_82")));
			Link.l1 = StringFromKey("Smuggler_OnShore_dialog_84");
			Link.l1.go = "Exchange1";
			if (sti(Pchar.quest.Contraband.Counter) == 0)
			{
				Link.l99 = StringFromKey("Smuggler_OnShore_dialog_85", pchar);
				Link.l99.go = "Cancellation";
			}
		break;

		case "Exchange1":
			// KZ FreeStores > магазин берём с проверкой
			if (CheckAttribute(pchar, "FindContrabandGoods.StoreIdx")) iContraStore = sti(pchar.FindContrabandGoods.StoreIdx);
			else                                                       iContraStore = GetCharacterCurrentStore(pchar);

			NPChar.quest.meeting = NPC_Meeting;
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			LaunchContrabandTrade(NPChar, iContraStore);
		break;

		case "NoGoods":
			ChangeContrabandRelation(pchar, -10);
			dialog.Text = StringFromKey("Smuggler_OnShore_dialog_86");
			Link.l1 = StringFromKey("Smuggler_OnShore_dialog_87");
			Link.l1.go = "Exit_Cancel";
		break;

		case "Finish_exit":
		// таможня на суше
			if ((GetSummonSkillFromName(pchar, "Sneak") - GetFortuneBonus(5)) < Rand(120))
			{
				PlayerRPGCheck_Skill_NotifyFail("Sneak", false);
				AddCharacterExpToSkill(Pchar, "Leadership", 50);
				AddDialogExitQuest("Rand_ContrabandInterruption");
				for (i = 1; i <= 3; i++)
				{
					characters[GetCharacterIndex("Rand_Smug0" + i)].ContrabandInterruption = true;
				}
			}
			else
				AddCharacterExpToSkill(Pchar, "Fortune", 50);

			AddCharacterExpToSkill(Pchar, "Sneak", 100);

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			ChangeContrabandRelation(pchar, 15);
			OfficersReaction("bad");
			ChangeCharacterReputation(pchar, -1);

			CloseQuestHeader("Gen_Contraband");

			DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");

			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
		break;
	}
}


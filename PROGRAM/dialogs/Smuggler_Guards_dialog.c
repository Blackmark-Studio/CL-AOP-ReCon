void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	int iTemp, i; // нужно для вычислений любых целых (нации)
	string attrName; // любые строки для вычислений
	ref sld;

	switch (Dialog.CurrentNode)
	{
		case "exit":
			StopCoastalGuardPursuit();
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			LAi_SetPlayerType(Pchar);
		break;

		case "First time":
			TEV.CT.BLADETYPE = SKILL_FENCING;
			if (GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) != "")
				TEV.CT.BLADETYPE = Items[FindItem(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE))].FencingType;

			chrDisableReloadToLocation = false;
			LAi_LockFightMode(pchar, false);
			dialog.text = StringFromKey("Smuggler_Guards_dialog_3", RandPhraseSimple(
						StringFromKey("Smuggler_Guards_dialog_1"),
						StringFromKey("Smuggler_Guards_dialog_2", NationKingsName(npchar))));
			Link.l1 = StringFromKey("Smuggler_Guards_dialog_4");
			if (makeint(Pchar.reputation) >= 70 && GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) >= 5)
			{
				Link.l1.go = "ThisTimeFree";
			}
			else
			{
				Link.l1.go = "IDontBelieveYou";
			}
			Link.l2 = StringFromKey("Smuggler_Guards_dialog_5");
			if (makeint(Pchar.rank) >= 4 && GetSummonSkillFromNameToOld(Pchar, SKILL_COMMERCE) >= 5)
			{
				Link.l2.go = "GiveMeSomeMoneyToo";
			}
			else
			{
				Link.l2.go = "TryingToGiveBribe";
			}
			Link.l3 = StringFromKey("Smuggler_Guards_dialog_6");
			if (makeint(Pchar.reputation) <= 25 && GetSummonSkillFromNameToOld(Pchar, TEV.CT.BLADETYPE) >= 8)
			{
				Link.l3.go = "GettingLostFromHere";
			}
			else
			{
				Link.l3.go = "howDareYou";
			}
		break;

		case "ThisTimeFree":
			PlayerRPGCheck_Reputation_NotifyPass(false, true);
			PlayerRPGCheck_Skill_NotifyPass(SKILL_LEADERSHIP);
			dialog.text = StringFromKey("Smuggler_Guards_dialog_7", Pchar.name);
			Link.l1 = StringFromKey("Smuggler_Guards_dialog_8");
			Link.l1.go = "ThisTimeFree_1";
			Link.l2 = StringFromKey("Smuggler_Guards_dialog_9");
			Link.l2.go = "ThisTimeFree_fight";
		break;

		case "ThisTimeFree_1":
			ChangeCharacterReputation(pchar, -40);
			dialog.text = StringFromKey("Smuggler_Guards_dialog_10");
			Link.l1 = StringFromKey("Smuggler_Guards_dialog_11");
			Link.l1.go = "ThisTimeFree_exit";
		break;

		case "ThisTimeFree_fight":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			for (i = 1; i <= sti(Pchar.quest.contraband.SoldierQty); i++)
			{
				attrName = "SoldierIDX" + i;
				sld = GetCharacter(sti(Pchar.quest.contraband.(attrName)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
			}
			for (i = 1; i < 4; i++)
			{
				attrName = "Rand_Smug0" + i;
				sld = CharacterFromID(attrName);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER); // no friendly fire
			}

			//			LAi_group_SetRelation(pchar.GenQuest.Smugglers_Group, "CoastalGuards", LAI_GROUP_ENEMY);
			LAi_group_SetHearRadius("CoastalGuards", 100.0);
			//			LAi_group_SetHearRadius(pchar.GenQuest.Smugglers_Group, 100.0);
			//			LAi_group_FightGroups("CoastalGuards", pchar.GenQuest.Smugglers_Group, true);
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);

			//LAi_SetPlayerType(Pchar);
			LAi_SetFightMode(Pchar, true);
			//trace("And we fight those soldiers!!" + Pchar.quest.contraband.CurrentPlace);
			chrDisableReloadToLocation = true;
		break;

		case "ThisTimeFree_exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;

			DialogExit();
			StopCoastalGuardPursuit();
			ChangeContrabandRelation(pchar, -30);
			for (i = 1; i <= sti(Pchar.quest.contraband.SoldierQty); i++)
			{
				attrName = "SoldierIDX" + i;
				sld = GetCharacter(sti(Pchar.quest.contraband.(attrName)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
			}
			LAi_group_SetRelation(pchar.GenQuest.Smugglers_Group, "CoastalGuards", LAI_GROUP_ENEMY);
			LAi_group_FightGroups(pchar.GenQuest.Smugglers_Group, "CoastalGuards", true);
			LAi_SetPlayerType(Pchar);
		break;

		case "IDontBelieveYou":
			if (makeint(Pchar.reputation) < 70)
			{
				PlayerRPGCheck_Reputation_NotifyFail("good");
			}
			PlayerRPGCheck_Skill_NotifyFail(SKILL_LEADERSHIP, false);
			dialog.text = StringFromKey("Smuggler_Guards_dialog_12");
			Link.l1 = StringFromKey("Smuggler_Guards_dialog_13");
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "GiveMeSomeMoneyToo":
			PlayerRPGCheck_Skill_NotifyPass(SKILL_COMMERCE);
			dialog.text = StringFromKey("Smuggler_Guards_dialog_14");
			Link.l1 = StringFromKey("Smuggler_Guards_dialog_15", FindMoneyString(makeint(sti(Pchar.money) / 10)));
			if (makeint(Pchar.rank) * 1000 <= makeint(sti(Pchar.money) / 10))
			{
				Link.l1.go = "MoneyAccepted10";
			}
			else
			{
				Link.l1.go = "TryingToGiveBribe";
			}

			Link.l2 = StringFromKey("Smuggler_Guards_dialog_16", FindMoneyString(makeint(sti(Pchar.money) / 5)));
			if (makeint(Pchar.rank) * 1000 <= makeint(sti(Pchar.money) / 5))
			{
				Link.l2.go = "MoneyAccepted5";
			}
			else
			{
				Link.l2.go = "TryingToGiveBribe";
			}

			Link.l3 = StringFromKey("Smuggler_Guards_dialog_17", FindMoneyString(makeint(sti(Pchar.money) / 2)));
			if (makeint(Pchar.rank) * 1000 <= makeint(sti(Pchar.money) / 2))
			{
				Link.l3.go = "MoneyAccepted2";
			}
			else
			{
				Link.l3.go = "TryingToGiveBribe";
			}
		break;

		case "TryingToGiveBribe":
			dialog.text = StringFromKey("Smuggler_Guards_dialog_18");
			Link.l1 = StringFromKey("Smuggler_Guards_dialog_19");
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "MoneyAccepted10":
			dialog.text = StringFromKey("Smuggler_Guards_dialog_20");
			Link.l1 = StringFromKey("Smuggler_Guards_dialog_21");
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -makeint(sti(Pchar.money) / 10));
		break;

		case "MoneyAccepted5":
			dialog.text = StringFromKey("Smuggler_Guards_dialog_22");
			Link.l1 = StringFromKey("Smuggler_Guards_dialog_23");
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -makeint(sti(Pchar.money) / 5));
		break;

		case "MoneyAccepted2":
			dialog.text = StringFromKey("Smuggler_Guards_dialog_24");
			Link.l1 = StringFromKey("Smuggler_Guards_dialog_25");
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -makeint(sti(Pchar.money) / 2));
		break;

		case "GettingLostFromHere":
			PlayerRPGCheck_Reputation_NotifyPass(false, false);
			PlayerRPGCheck_Skill_NotifyPass(TEV.CT.BLADETYPE);
			dialog.text = StringFromKey("Smuggler_Guards_dialog_26");
			Link.l1 = StringFromKey("Smuggler_Guards_dialog_27");
			Link.l1.go = "GettingLostFromHere_1";
		break;

		case "GettingLostFromHere_1":
			dialog.text = StringFromKey("Smuggler_Guards_dialog_28");
			Link.l1 = StringFromKey("Smuggler_Guards_dialog_29");
			Link.l1.go = "GettingLostFromHere_exit";
		break;

		case "GettingLostFromHere_exit":
			ChangeContrabandRelation(pchar, 10);

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();

			StopCoastalGuardPursuit();
			for (i = 1; i <= sti(Pchar.quest.contraband.SoldierQty); i++)
			{
				attrName = "SoldierIDX" + i;
				LAi_SetActorType(&Characters[sti(Pchar.quest.contraband.(attrName))]);
				LAi_ActorRunToLocation(&Characters[sti(Pchar.quest.contraband.(attrName))], "reload", "Reload1", "none", "", "", "", 40);
			}
			LAi_SetPlayerType(Pchar);
		break;

		case "howDareYou":
			if (makeint(Pchar.reputation) > 25)
			{
				PlayerRPGCheck_Reputation_NotifyFail("bad");
			}
			PlayerRPGCheck_Skill_NotifyFail(TEV.CT.BLADETYPE, false);
			dialog.text = StringFromKey("Smuggler_Guards_dialog_30");
			Link.l1 = StringFromKey("Smuggler_Guards_dialog_31");
			Link.l1.go = "ThisTimeFree_fight";
		break;
	}
}

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
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,
						StringFromKey("Incquistors_dialog_4", LinkRandPhrase(
								StringFromKey("Incquistors_dialog_1"),
								StringFromKey("Incquistors_dialog_2"),
								StringFromKey("Incquistors_dialog_3", pchar))),
						StringFromKey("Incquistors_dialog_8", LinkRandPhrase(
								StringFromKey("Incquistors_dialog_5", pchar),
								StringFromKey("Incquistors_dialog_6", pchar),
								StringFromKey("Incquistors_dialog_7", pchar))));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("Incquistors_dialog_11", RandPhraseSimple(
								StringFromKey("Incquistors_dialog_9"),
								StringFromKey("Incquistors_dialog_10"))),
						StringFromKey("Incquistors_dialog_14", RandPhraseSimple(
								StringFromKey("Incquistors_dialog_12"),
								StringFromKey("Incquistors_dialog_13"))));
				link.l1.go = "exit";
				break;
			}

			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = StringFromKey("Incquistors_dialog_17", RandPhraseSimple(
							StringFromKey("Incquistors_dialog_15"),
							StringFromKey("Incquistors_dialog_16")));
				link.l1 = StringFromKey("Incquistors_dialog_18");
				link.l1.go = "fight";
			}
			else
			{

				dialog.text = NPCStringReactionRepeat(
							StringFromKey("Incquistors_dialog_23", RandPhraseSimple(
									StringFromKey("Incquistors_dialog_21", pchar),
									StringFromKey("Incquistors_dialog_22", pchar))),
							StringFromKey("Incquistors_dialog_24", pchar),
							StringFromKey("Incquistors_dialog_25", pchar),
							StringFromKey("Incquistors_dialog_28", RandPhraseSimple(
									StringFromKey("Incquistors_dialog_26"),
									StringFromKey("Incquistors_dialog_27", pchar))), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("Incquistors_dialog_31", RandPhraseSimple(
									StringFromKey("Incquistors_dialog_29", pchar),
									StringFromKey("Incquistors_dialog_30", pchar))),
							StringFromKey("Incquistors_dialog_32"),
							StringFromKey("Incquistors_dialog_33", pchar),
							StringFromKey("Incquistors_dialog_36", RandPhraseSimple(
									StringFromKey("Incquistors_dialog_34"),
									StringFromKey("Incquistors_dialog_35"))), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "NoMoreTalkExit", npchar, Dialog.CurrentNode);
				if (CheckAttribute(pchar, "questTemp.PDM_ONV_OhotaNaVedmu") && npchar.chr_ai.type != "guardian")
				{
					link.l2 = StringFromKey("Incquistors_dialog_74");
					link.l2.go = "PDM_ONW_Inqizitor_1";
				}
			}

			if (CheckAttribute(npchar, "protector.CheckAlways")) //гарды на камерах
			{
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = StringFromKey("Incquistors_dialog_37");
					link.l1 = StringFromKey("Incquistors_dialog_38");
					link.l1.go = "fight";
				}
				else
				{
					dialog.text = StringFromKey("Incquistors_dialog_42", LinkRandPhrase(
								StringFromKey("Incquistors_dialog_39"),
								StringFromKey("Incquistors_dialog_40"),
								StringFromKey("Incquistors_dialog_41")));
					link.l1 = StringFromKey("Incquistors_dialog_45", RandPhraseSimple(
								StringFromKey("Incquistors_dialog_43"),
								StringFromKey("Incquistors_dialog_44")));
					link.l1.go = "exit";
				}
			}

			if (HasSubStr(npchar.id, "Prisoner")) //заключенные
			{
				if (LAi_group_IsActivePlayerAlarm())
				{
					dialog.text = StringFromKey("Incquistors_dialog_49", LinkRandPhrase(
								StringFromKey("Incquistors_dialog_46"),
								StringFromKey("Incquistors_dialog_47"),
								StringFromKey("Incquistors_dialog_48", pchar)));
					link.l1 = StringFromKey("Incquistors_dialog_52", RandPhraseSimple(
								StringFromKey("Incquistors_dialog_50"),
								StringFromKey("Incquistors_dialog_51")));
					link.l1.go = "exit";
					//==> квест №7, базар о Роке Бразильце.
					if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
					{
						link.l1 = StringFromKey("Incquistors_dialog_53");
						link.l1.go = "Step_F7_2";
					}
					//<== квест №7, базар о Роке Бразильце.
				}
				else
				{
					dialog.text = StringFromKey("Incquistors_dialog_57", LinkRandPhrase(
								StringFromKey("Incquistors_dialog_54"),
								StringFromKey("Incquistors_dialog_55"),
								StringFromKey("Incquistors_dialog_56")));
					link.l1 = StringFromKey("Incquistors_dialog_60", RandPhraseSimple(
								StringFromKey("Incquistors_dialog_58"),
								StringFromKey("Incquistors_dialog_59")));
					link.l1.go = "exit";
					//==> квест №7, базар о Роке Бразильце.
					if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
					{
						link.l1 = StringFromKey("Incquistors_dialog_61");
						link.l1.go = "Step_F7_1";
					}
					//<== квест №7, базар о Роке Бразильце.
				}
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;

		case "fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			StartIncquisitioAttack();
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		//**************************** Фр. линейка. Квест №7, спасение Рока Бразильца ********************************
		case "Step_F7_1":
			dialog.text = StringFromKey("Incquistors_dialog_62");
			link.l1 = StringFromKey("Incquistors_dialog_63");
			link.l1.go = "exit";
		break;
		case "Step_F7_2":
			dialog.text = StringFromKey("Incquistors_dialog_64", pchar);
			link.l1 = StringFromKey("Incquistors_dialog_65");
			link.l1.go = "exit";
		break;
		
		//**************************** Прокажённая ********************************
		case "PDM_ONW_Inqizitor_1":
			dialog.text = StringFromKey("Incquistors_dialog_75", pchar);
			link.l1 = StringFromKey("Incquistors_dialog_76");
			link.l1.go = "PDM_ONW_Inqizitor_2";
			DeleteAttribute(pchar, "questTemp.PDM_ONV_OhotaNaVedmu");
		break;

		case "PDM_ONW_Inqizitor_2":
			DialogExit();
			
			sld = GetCharacter(CreateCharacterClone(npchar, -1));
			sld.id = "PDM_ONW_Inqizitor";
			
			locations[FindLocation("Cuba_jungle_01")].DisableEncounters = true;
			// TavernWaitDate("wait_night");
			TavernWaitDateEx(22);
			DoFunctionReloadToLocation("Cuba_jungle_01", "goto", "goto4", "PDM_ONW_Kino_1");
		break;

		//замечение по обнаженному оружию
		/*case "SoldierNotBlade": //HardCoffee ref SoldierNotBlade CitizenNotBlade
			if(GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if(sti(pchar.nation) == PIRATE)
				{
					dialog.text = RandPhraseSimple(StringFromKey("Incquistors_dialog_65", GetSexPhrase(StringFromKey("SexPhrase_54"), StringFromKey("SexPhrase_55"))), StringFromKey("Incquistors_dialog_66", GetSexPhrase(StringFromKey("SexPhrase_54"), StringFromKey("SexPhrase_55"))));
					link.l1 = RandPhraseSimple(StringFromKey("Incquistors_dialog_67"), StringFromKey("Incquistors_dialog_68"));
					link.l1.go = "fight";
					break;
				}
				dialog.text = RandPhraseSimple(StringFromKey("Incquistors_dialog_70"), StringFromKey("Incquistors_dialog_69", GetSexPhrase(StringFromKey("SexPhrase_54"), StringFromKey("SexPhrase_55"))));
				link.l1 = RandPhraseSimple(StringFromKey("Incquistors_dialog_71"), StringFromKey("Incquistors_dialog_72"));
				link.l1.go = "fight";
			}
			else
			{
				dialog.text = LinkRandPhrase(StringFromKey("Incquistors_dialog_74"), StringFromKey("Incquistors_dialog_75"), StringFromKey("Incquistors_dialog_73", GetAddress_Form(NPChar)));
				link.l1 = LinkRandPhrase(StringFromKey("Incquistors_dialog_77"), StringFromKey("Incquistors_dialog_76", GetSexPhrase("",StringFromKey("SexEnding_1"))), StringFromKey("Incquistors_dialog_78"));
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) != RELATION_ENEMY) link.l1.go = "exit";
				else link.l1.go = "First Time"; //Не миновать нам проверки!
				link.l2 = LinkRandPhrase(StringFromKey("Incquistors_dialog_79"), StringFromKey("Incquistors_dialog_80"), StringFromKey("Incquistors_dialog_81"));
				link.l2.go = "fight";
				NextDiag.TempNode = "First Time";
				if (CheckAttribute(NPChar, "protector")) NPChar.greeting = "soldier_arest";
				else NPChar.greeting = "soldier_common";
			}
		break;*/
	}
}

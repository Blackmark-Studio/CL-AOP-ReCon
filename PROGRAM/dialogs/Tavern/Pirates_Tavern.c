// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Pirates_Tavern_3", RandPhraseSimple(
								StringFromKey("Pirates_Tavern_1"),
								StringFromKey("Pirates_Tavern_2", GetAddress_Form(NPChar)))),
						StringFromKey("Pirates_Tavern_4", GetAddress_Form(NPChar)),
						StringFromKey("Pirates_Tavern_5"),
						StringFromKey("Pirates_Tavern_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Pirates_Tavern_9", RandPhraseSimple(
								StringFromKey("Pirates_Tavern_7", pchar),
								StringFromKey("Pirates_Tavern_8"))),
						StringFromKey("Pirates_Tavern_10"),
						StringFromKey("Pirates_Tavern_11"),
						StringFromKey("Pirates_Tavern_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Линейка Ле Баска. Третий квест.
			if (pchar.quest.Hunting_huntsman == "Talk_Tavern")
			{
                link.l3 = StringFromKey("Pirates_Tavern_61");
                link.l3.go = "Hunting_huntsman_1";
            }
			// ==> Проверяем поле состояния квестов.
			if (pchar.questTemp.State == "SeekBible_toBermudes")
			{
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("Pirates_Tavern_13"),
							StringFromKey("Pirates_Tavern_14", pchar),
							StringFromKey("Pirates_Tavern_15"),
							StringFromKey("Pirates_Tavern_16"), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("Step_H8_1", "", "", "", npchar, Dialog.CurrentNode);
			}
			if (pchar.RomanticQuest == "BrotherIsDead")
			{
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("Pirates_Tavern_17"),
							StringFromKey("Pirates_Tavern_18"),
							StringFromKey("Pirates_Tavern_19"),
							StringFromKey("Pirates_Tavern_20"), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("Step_Romantic_1", "", "", "", npchar, Dialog.CurrentNode);
			}
			if (pchar.questTemp.BlueBird == "toBermudes")
			{
				link.l1 = StringFromKey("Pirates_Tavern_21");
				link.l1.go = "BlueBird_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toBermudes")
			{
				link.l1 = StringFromKey("Pirates_Tavern_22");
				link.l1.go = "PL_Q3_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toTavernAgain" || pchar.questTemp.piratesLine == "KillLoy_2toTavernAgain")
			{
				link.l1 = StringFromKey("Pirates_Tavern_23");
				link.l1.go = "PL_Q3_2";
			}
			if (pchar.questTemp.piratesLine == "PL5Hunter_toBermudes")
			{
				link.l1 = StringFromKey("Pirates_Tavern_24");
				link.l1.go = "StepPL5Berm_1";
			}
		// <== Проверяем поле состояния квестов.
		break;

		// Ле Баск. Третий квест.
		case "Hunting_huntsman_1":
			dialog.text = StringFromKey("Pirates_Tavern_62");
			link.l1 = StringFromKey("Pirates_Tavern_63");
			link.l1.go = "Hunting_huntsman_2";
		break;

		case "Hunting_huntsman_2":
			dialog.text = StringFromKey("Pirates_Tavern_64");
			link.l1 = StringFromKey("Pirates_Tavern_65");
			link.l1.go = "Hunting_huntsman_2_exit";
		break;

		case "Hunting_huntsman_2_exit":
			RemoveLandQuestmark_Main(npchar, "Hunting_huntsman");
			AddDialogExitQuest("Hunting_huntsman_26");
			dialogexit();
		break;

		//шебека Синяя Птица
		case "BlueBird_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Pirates_Tavern_25"),
						StringFromKey("Pirates_Tavern_26"),
						StringFromKey("Pirates_Tavern_27"),
						StringFromKey("Pirates_Tavern_28"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Pirates_Tavern_29"),
						StringFromKey("Pirates_Tavern_30"),
						StringFromKey("Pirates_Tavern_31"),
						StringFromKey("Pirates_Tavern_32"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("BlueBird_2", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		break;

		case "BlueBird_2":
			dialog.text = StringFromKey("Pirates_Tavern_33");
			link.l1 = StringFromKey("Pirates_Tavern_34");
			link.l1.go = "BlueBird_3";
		break;
		case "BlueBird_3":
			dialog.text = StringFromKey("Pirates_Tavern_35");
			link.l1 = StringFromKey("Pirates_Tavern_36");
			link.l1.go = "BlueBird_4";
		break;
		case "BlueBird_4":
			dialog.text = StringFromKey("Pirates_Tavern_37");
			link.l1 = StringFromKey("Pirates_Tavern_38");
			link.l1.go = "BlueBird_5";
		break;
		case "BlueBird_5":
			dialog.text = StringFromKey("Pirates_Tavern_39");
			link.l1 = StringFromKey("Pirates_Tavern_40");
			link.l1.go = "BlueBird_6";
		break;
		case "BlueBird_6":
			dialog.text = StringFromKey("Pirates_Tavern_41");
			link.l1 = StringFromKey("Pirates_Tavern_42");
			link.l1.go = "BlueBird_7";
		break;
		case "BlueBird_7":
			dialog.text = StringFromKey("Pirates_Tavern_43", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Pirates_Tavern_44");
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "3");
			pchar.questTemp.BlueBird = "toPuertoPrincipe";

			AddLandQuestMark_Main(CharacterFromID("PuertoPrincipe_trader"), "Xebeca_BlueBird");
			RemoveLandQuestMark_Main(npchar, "Xebeca_BlueBird");
			RemoveLandQuestMark_Main(CharacterFromID("Pirates_trader"), "Xebeca_BlueBird");
			RemoveLandQuestMark_Main(CharacterFromID("Jackman"), "Xebeca_BlueBird");
		break;

		//голл. линейка, квест №8
		case "Step_H8_1":
			dialog.text = StringFromKey("Pirates_Tavern_45");
			link.l1 = StringFromKey("Pirates_Tavern_46");
			link.l1.go = "Step_H8_2";
		break;
		case "Step_H8_2":
			dialog.text = StringFromKey("Pirates_Tavern_47");
			link.l1 = StringFromKey("Pirates_Tavern_48");
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
		break;
		//Изабелла, ищем Атиллу
		case "Step_Romantic_1":
			dialog.text = StringFromKey("Pirates_Tavern_49");
			link.l1 = StringFromKey("Pirates_Tavern_50");
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
		break;
		//Пиратка, квест №3, поиски Лоу
		case "PL_Q3_1":
			dialog.text = StringFromKey("Pirates_Tavern_51");
			link.l1 = StringFromKey("Pirates_Tavern_52");
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "9");
			pchar.questTemp.piratesLine = "KillLoy_toAlexus";

			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			AddLandQuestmark_Main(CharacterFromID("Pirates_shipyarder"), "Pir_Line");
		break;

		case "PL_Q3_2":
			dialog.text = StringFromKey("Pirates_Tavern_53");
			link.l1 = StringFromKey("Pirates_Tavern_54");
			link.l1.go = "PL_Q3_3";
		break;
		case "PL_Q3_3":
			dialog.text = StringFromKey("Pirates_Tavern_55");
			link.l1 = StringFromKey("Pirates_Tavern_56");
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "KillLoy_toGoogly";
			//садим капитана Гудли в таверну
			ref sld = GetCharacter(NPC_GenerateCharacter("CapGoodly", "Goodley", "man", "man", 20, PIRATE, -1, true));
			sld.name = FindPersonalName("QuestPirate1_name");
			sld.lastname = FindPersonalName("QuestPirate1_lastname");
			sld.rank = 20;
			sld.city = "Pirates";
			sld.dialog.filename = "Quest\PiratesLine_dialog.c";
			sld.dialog.currentnode = "CapGoodly";
			sld.greeting = "Gr_EvilPirate";
			LAi_SetSitType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			FreeSitLocator("Pirates_tavern", "sit2");
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "sit", "sit2");
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			RemoveLandQuestmark_Main(CharacterFromID("Jackman"), "Pir_Line");
			AddLandQuestmark_Main(sld, "Pir_Line");
		break;
		//Пиратка, квест №5, ОЗГ
		case "StepPL5Berm_1":
			dialog.text = StringFromKey("Pirates_Tavern_57");
			link.l1 = StringFromKey("Pirates_Tavern_58");
			link.l1.go = "StepPL5Berm_2";
		break;
		case "StepPL5Berm_2":
			dialog.text = StringFromKey("Pirates_Tavern_59");
			link.l1 = StringFromKey("Pirates_Tavern_60");
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "10");
			pchar.questTemp.piratesLine = "PL5Hunter_toOrryHouse";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Tortuga_Usurer_3", RandPhraseSimple(
								StringFromKey("Tortuga_Usurer_1"),
								StringFromKey("Tortuga_Usurer_2"))),
						StringFromKey("Tortuga_Usurer_4"),
						StringFromKey("Tortuga_Usurer_5"),
						StringFromKey("Tortuga_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Tortuga_Usurer_9", RandPhraseSimple(
								StringFromKey("Tortuga_Usurer_7", pchar),
								StringFromKey("Tortuga_Usurer_8"))),
						StringFromKey("Tortuga_Usurer_10"),
						StringFromKey("Tortuga_Usurer_11"),
						StringFromKey("Tortuga_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
			if (CheckAttribute(pchar, "questTemp.PDM_PI_Rostov"))    //Квест "Проклятый Идол"
			{
				link.l1 = StringFromKey("Tortuga_Usurer_13", pchar);
				link.l1.go = "PDM_PI_Rostov_2";
			}
			switch (pchar.questTemp.State)
			{
				case "WormEnglPlans_WormPicarder": //Голландская линейка, квест №3. узнаем о Пеьере Пикардийце.
					link.l2 = StringFromKey("Tortuga_Usurer_14", pchar);
					link.l2.go = "Step_H3_1";
				break;

			}
		// <== Проверяем поле состояния квестов.
		break;

		//Квест "Проклятый Идол"
		case "PDM_PI_Rostov_2":
			dialog.text = StringFromKey("Tortuga_Usurer_15", UpperFirst(GetAddress_Form(NPChar)), pchar.name);
			link.l1 = StringFromKey("Tortuga_Usurer_16");
			link.l1.go = "PDM_PI_Rostov_3";
		break;
		case "PDM_PI_Rostov_3":
			dialog.text = StringFromKey("Tortuga_Usurer_17", GetAddress_Form(NPChar), pchar.name);
			link.l1 = StringFromKey("Tortuga_Usurer_18", pchar);
			link.l1.go = "PDM_PI_Rostov_4";
			AddItemLog(pchar, "Cursed_idol", "-1", StringFromKey("InfoMessages_158"), "Important_item");
		break;
		case "PDM_PI_Rostov_4":
			dialog.text = StringFromKey("Tortuga_Usurer_19");
			link.l1 = StringFromKey("Tortuga_Usurer_20");
			link.l1.go = "Rostovshik_5";
			bDisableFastReload = true;
			DeleteAttribute(pchar, "questTemp.PDM_PI_Rostov");
		//DeleteAttribute(pchar, "questTemp.PDM_PI_Skelety_v_more");
		break;
		case "Rostovshik_5":
			DelLandQuestMark(npchar);
			DialogExit();
			int iPhrase = 1;
			if (CheckCharacterPerk(pchar, "WildCaribbean")) iPhrase++;
			ref sld;
			iPhrase = rand(iPhrase);
			if (iPhrase == 0)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Bandit_1", "pirate_4", "man", "man", sti(pchar.rank), PIRATE, -1, true));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
				LAi_SetActorType(sld);
				sld.dialog.filename = "Quest\PDM\Cursed_Idol.c";
				sld.dialog.currentnode = "Rostovshik_Fra_Off_1";
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				sld.SaveItemsForDead = true;
				sld.DontChangeBlade = true;
				AddMoneyToCharacter(sld, 3000);
				AddItems(sld, "potionrum", 2);
				AddItems(sld, "jewelry7", 2);
				AddItems(sld, "spyglass3", 1);
				break;
			}
			if (iPhrase == 1)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Bandit_1", "off_fra_3", "man", "man", sti(pchar.rank), PIRATE, -1, true));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
				LAi_SetActorType(sld);
				sld.dialog.filename = "Quest\PDM\Cursed_Idol.c";
				sld.dialog.currentnode = "Rostovshik_Fra_Off_2";
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				sld.SaveItemsForDead = true;
				sld.DontChangeBlade = true;
				AddMoneyToCharacter(sld, 1500);
				AddItems(sld, "potionwine", 3);
				AddItems(sld, "jewelry15", 6);
				AddItems(sld, "jewelry14", 6);
				AddItems(sld, "jewelry13", 6);
				break;
			}
			if (iPhrase == 2)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Bandit_1", "skel1", "skeleton", "man", sti(pchar.rank), PIRATE, -1, true));
				sld.skeleton = "1";
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
				LAi_SetActorType(sld);
				sld.dialog.filename = "Quest\PDM\Cursed_Idol.c";
				sld.dialog.currentnode = "Rostovshik_Fra_Off_3";
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				sld.SaveItemsForDead = true;
				sld.DontChangeBlade = true;
				AddMoneyToCharacter(sld, 500);
				AddItems(sld, "indian5", 1);
				AddItems(sld, "indian9", 1);
				AddItems(sld, "indian2", 1);
				AddItems(sld, "Totem_8", 1);
				break;
			}
		break;

		//Голландская линейка, квест №3
		case "Step_H3_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Tortuga_Usurer_21"),
						StringFromKey("Tortuga_Usurer_22"),
						StringFromKey("Tortuga_Usurer_23"),
						StringFromKey("Tortuga_Usurer_24"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Tortuga_Usurer_25"),
						StringFromKey("Tortuga_Usurer_26"),
						StringFromKey("Tortuga_Usurer_27"),
						StringFromKey("Tortuga_Usurer_28"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H3_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_H3_2":
			dialog.text = StringFromKey("Tortuga_Usurer_29");
			link.l1 = StringFromKey("Tortuga_Usurer_30", pchar);
			link.l1.go = "exit";
			pchar.questTemp.Hol_Line_AboutWorm.Usurer = true;
			AddQuestRecord("Hol_Line_3_WormEnglishPlans", "10");
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

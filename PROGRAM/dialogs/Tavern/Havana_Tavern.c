// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Havana_Tavern_1", GetCityName(npchar.city)),
						StringFromKey("Havana_Tavern_2"),
						StringFromKey("Havana_Tavern_3"),
						StringFromKey("Havana_Tavern_4", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Havana_Tavern_5", NPChar.name),
						StringFromKey("Havana_Tavern_6", pchar),
						StringFromKey("Havana_Tavern_7"),
						StringFromKey("Havana_Tavern_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
			{
				dialog.text = StringFromKey("Havana_Tavern_9", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Havana_Tavern_10", pchar);
				link.l1.go = "Step_F7_1";
				break;
			}
			Link.l1.go = "exit";
			if (pchar.questTemp.Ascold == "ToHavanna") // квест Аскольда
			{
				Link.l1 = StringFromKey("Havana_Tavern_11");
				Link.l1.go = "Step_A1";
			}
			if (pchar.questTemp.Slavetrader == "FindRatHavana")
			{
				link.l1 = StringFromKey("Havana_Tavern_12", pchar.questTemp.Slavetrader.ShipName);
				link.l1.go = "Havana_ratT_1";
			}
		break;
		//******************** Фр.линейка, квест №7. Спасение Рока Бразильца ******************
		case "Step_F7_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Havana_Tavern_13", GetAddress_Form(NPChar)),
						StringFromKey("Havana_Tavern_14"),
						StringFromKey("Havana_Tavern_15"),
						StringFromKey("Havana_Tavern_16"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Havana_Tavern_17"),
						StringFromKey("Havana_Tavern_18", pchar),
						StringFromKey("Havana_Tavern_19", pchar),
						StringFromKey("Havana_Tavern_20"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_F7_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_F7_2":
			dialog.text = StringFromKey("Havana_Tavern_21", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Havana_Tavern_22");
			link.l1.go = "Step_F7_3";
		break;
		case "Step_F7_3":
			dialog.text = StringFromKey("Havana_Tavern_23", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Havana_Tavern_24");
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;
		//******************** Квест Аскольда, узнаем о мановарах с ипанским добром ******************
		case "Step_A1":
			dialog.text = StringFromKey("Havana_Tavern_25");
			Link.l1 = StringFromKey("Havana_Tavern_26");
			Link.l1.go = "Step_A2";
		break;

		case "Step_A2":
			dialog.text = StringFromKey("Havana_Tavern_27");
			Link.l1 = StringFromKey("Havana_Tavern_28");
			Link.l1.go = "Step_A3";
		break;

		case "Step_A3":
			dialog.text = StringFromKey("Havana_Tavern_29");
			Link.l1 = StringFromKey("Havana_Tavern_30");
			Link.l1.go = "Step_A4";
		break;

		case "Step_A4":
			dialog.text = StringFromKey("Havana_Tavern_31", pchar);
			Link.l1 = StringFromKey("Havana_Tavern_32", pchar);
			Link.l1.go = "Step_A5";
		break;

		case "Step_A5":
			dialog.text = StringFromKey("Havana_Tavern_33", pchar);
			Link.l1 = StringFromKey("Havana_Tavern_34", pchar);
			Link.l1.go = "exit";
			pchar.questTemp.Ascold = "SeekInformatorHavanna";
			AddQuestRecord("Ascold", "6");
			ref sld = GetCharacter(NPC_GenerateCharacter("FernandoGonsales", "off_spa_4", "man", "man", 28, SPAIN, -1, true)); //wath_quest_moment
			FantomMakeCoolFighter(sld, 28, 90, 70, BLADE_LONG, "pistol3", 10);
			LAi_SetStayType(sld);
			sld.name = FindPersonalName("FernandoGonsales_name");
			sld.lastname = FindPersonalName("FernandoGonsales_lastname");
			sld.Dialog.Filename = "Quest\AscoldNpc.c";
			ChangeCharacterAddressGroup(sld, "Santiago_houseSp2", "goto", "goto2");
			LAi_LocationFightDisable(&Locations[FindLocation("Santiago_houseSp2")], true);
			RemoveLandQuestmark_Main(npchar, "Ascold");
			AddLandQuestmark_Main(sld, "Ascold");
			AddLandQuestmark_Main(CharacterFromID("Ascold"), "Ascold");
		break;

		case "Havana_ratT_1":
			dialog.text = StringFromKey("Havana_Tavern_35");
			Link.l1 = StringFromKey("Havana_Tavern_36");
			Link.l1.go = "Havana_ratT_2";
		break;

		case "Havana_ratT_2":
			dialog.text = StringFromKey("Havana_Tavern_37");
			Link.l1 = StringFromKey("Havana_Tavern_38", pchar);
			Link.l1.go = "Havana_ratT_3";
		break;

		case "Havana_ratT_3":
			dialog.text = StringFromKey("Havana_Tavern_39");
			Link.l1 = StringFromKey("Havana_Tavern_40");
			Link.l1.go = "Havana_ratT_4";
		break;

		case "Havana_ratT_4":
			dialog.text = StringFromKey("Havana_Tavern_41");
			Link.l1 = StringFromKey("Havana_Tavern_42", npchar.name);
			Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_7");
			pchar.questTemp.Slavetrader = "FindRatTortuga";
			pchar.quest.Slavetrader_findTortugaRat.win_condition.l1 = "location";
			pchar.quest.Slavetrader_findTortugaRat.win_condition.l1.location = "Tortuga_HouseHut";
			pchar.quest.Slavetrader_findTortugaRat.win_condition = "Slavetrader_findTortugaRat";
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			AddLandQuestmark_Main(CharacterFromID("Tortuga_tavernkeeper"), "Slavetrader");
			AddLandQuestmark_Main(CharacterFromID("Tortuga_PortMan"), "Slavetrader");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Villemstad_PortMan_3", RandPhraseSimple(
								StringFromKey("Villemstad_PortMan_1"),
								StringFromKey("Villemstad_PortMan_2", GetAddress_Form(NPChar)))),
						StringFromKey("Villemstad_PortMan_4", GetAddress_Form(NPChar)),
						StringFromKey("Villemstad_PortMan_5"),
						StringFromKey("Villemstad_PortMan_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Villemstad_PortMan_9", RandPhraseSimple(
								StringFromKey("Villemstad_PortMan_7", pchar),
								StringFromKey("Villemstad_PortMan_8"))),
						StringFromKey("Villemstad_PortMan_10"),
						StringFromKey("Villemstad_PortMan_11"),
						StringFromKey("Villemstad_PortMan_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> квест №5 голл.линейки, забрать три флейта.
			if (pchar.questTemp.State == "ThreeFleutes_toPortMan")
			{
				link.l1 = StringFromKey("Villemstad_PortMan_13");
				link.l1.go = "Step_H5_1";
			}
			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_P")
			{
				link.l1 = StringFromKey("Villemstad_PortMan_14", pchar);
				link.l1.go = "EscapeSlave_Villemstad_P1";
			}
			//ОЗГ, Крыса
			if (CheckAttrValue(pchar, "questTemp.Headhunter", "Rat") && pchar.questTemp.Headhunter.countV == 0)
			{
				link.l1 = StringFromKey("Villemstad_PortMan_15", pchar);
				link.l1.go = "Rat_portmanV";
			}
			// ==> Эммануэль Пардаль: Портниха знатной дамы
			if(CheckAttribute(pchar, "questTemp.EPL_PZD_PU"))
			{
				DeleteAttribute(pchar, "questTemp.EPL_PZD_taverna");
				DeleteAttribute(pchar, "questTemp.EPL_PZD_PU");
				link.l1 = StringFromKey("Villemstad_PortMan_30");
				link.l1.go = "EPL_PZD_PU_1";
				break;
			}
			// <== Эммануэль Пардаль: Портниха знатной дамы
		break;

		//************************************* Диалоги по голл.линейке *******************************
		case "Step_H5_1":
			if (GetCompanionQuantity(pchar) == 1)
			{
				dialog.text = StringFromKey("Villemstad_PortMan_16");
				link.l1 = StringFromKey("Villemstad_PortMan_17");
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HL5_portManGiveFleuts");
				RemoveLandQuestmark_Main(npchar, "Hol_Line");
			}
			else
			{
				dialog.text = StringFromKey("Villemstad_PortMan_18");
				link.l1 = StringFromKey("Villemstad_PortMan_19");
				link.l1.go = "exit";
			}
		break;
		//работорговец
		case "EscapeSlave_Villemstad_P1":
			dialog.text = StringFromKey("Villemstad_PortMan_20");
			link.l1 = StringFromKey("Villemstad_PortMan_21");
			link.l1.go = "EscapeSlave_Villemstad_P2";
		break;

		case "EscapeSlave_Villemstad_P2":
			dialog.text = StringFromKey("Villemstad_PortMan_22", pchar.questTemp.Slavetrader.ShipName);
			link.l1 = StringFromKey("Villemstad_PortMan_23");
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "22_3");
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_H";
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			AddLandQuestMarkToFantoms_Main("habitue", "Slavetrader", "Slavetrader_EscapeSlave_Habitues_QuestMarkCondition");
		break;

		//ОЗГ, Крыса
		case "Rat_portmanV":
			dialog.text = StringFromKey("Villemstad_PortMan_24");
			link.l1 = StringFromKey("Villemstad_PortMan_25");
			link.l1.go = "Rat_portmanV_1";
		break;

		case "Rat_portmanV_1":
			dialog.text = StringFromKey("Villemstad_PortMan_26");
			link.l1 = StringFromKey("Villemstad_PortMan_27");
			link.l1.go = "Rat_portmanV_2";
		break;

		case "Rat_portmanV_2":
			dialog.text = StringFromKey("Villemstad_PortMan_28");
			link.l1 = StringFromKey("Villemstad_PortMan_29");
			link.l1.go = "CheckV";
			pchar.questTemp.Headhunter.count = sti(pchar.questTemp.Headhunter.count) + 1;
			pchar.questTemp.Headhunter.countV = 1;
		break;

		case "CheckV":
			if (pchar.questTemp.Headhunter.count == 3)
			{
				pchar.questTemp.Headhunter = "Rat_Tavern";
				pchar.questTemp.Headhunter.Ratrumcity = npchar.city;
				AddQuestRecord("Headhunt", "13");
				AddLandQuestMarkToFantoms_Main("habitue", "Headhunt", "Headhunt_Rat_Habitues_QuestMarkCondition");
			}
			else
			{
				AddQuestRecord("Headhunt", "12_3");
			}
			RemoveLandQuestMark_Main(npchar, "Headhunt");
			DialogExit();
		break;
		
		// ==> Эммануэль Пардаль: Портниха знатной дамы
		case "EPL_PZD_PU_1":
    		dialog.text = StringFromKey("Villemstad_PortMan_31", PChar.Ship.Name);
    		link.l1 = StringFromKey("Villemstad_PortMan_32");
    		link.l1.go = "EPL_PZD_PU_2";
			RemoveLandQuestmark_Main(CharacterFromID("Villemstad_tavernkeeper"), "EPL_PZD");
			RemoveLandQuestmark_Main(CharacterFromID("Villemstad_portman"), "EPL_PZD");
 		break;
		
		case "EPL_PZD_PU_2":
    		dialog.text = StringFromKey("Villemstad_PortMan_33");
    		link.l1 = StringFromKey("Villemstad_PortMan_34");
    		link.l1.go = "EPL_PZD_PU_3";
 		break;
		
		case "EPL_PZD_PU_3":
    		dialog.text = StringFromKey("Villemstad_PortMan_35");
    		link.l1 = StringFromKey("Villemstad_PortMan_36");
    		link.l1.go = "EPL_PZD_PU_4";
 		break;
		
		case "EPL_PZD_PU_4":
    		dialog.text = StringFromKey("Villemstad_PortMan_37");
    		link.l1 = StringFromKey("Villemstad_PortMan_38");
    		link.l1.go = "exit";
			AddDialogExitQuestFunction("EPL_PZD_PortUprDialogExit");
 		break;
		// <== Эммануэль Пардаль: Портниха знатной дамы
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

//Jason общий диалог уличных матросов
#include "DIALOGS\Rumours\Simple_rumors.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\Citizen\" + NPChar.City + "_Citizen.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	switch (Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.crew"))//найм в команду
				{
					dialog.text = StringFromKey("Sailor_1", GetAddress_Form(NPChar));
					link.l1 = StringFromKey("Sailor_2", GetAddress_FormToNPC(NPChar));
					link.l1.go = "crew";
					link.l2 = StringFromKey("Sailor_3", GetAddress_FormToNPC(NPChar));
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = StringFromKey("Sailor_7", LinkRandPhrase(
							StringFromKey("Sailor_4"),
							StringFromKey("Sailor_5", pchar),
							StringFromKey("Sailor_6", pchar)));
				link.l1 = StringFromKey("Sailor_8", GetFullName(pchar));
				link.l1.go = "question";
				link.l2 = StringFromKey("Sailor_11", RandPhraseSimple(
							StringFromKey("Sailor_9"),
							StringFromKey("Sailor_10")));
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = StringFromKey("Sailor_12", pchar);
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
				//--> Эммануэль Пардаль
				if (CheckAttribute(pchar, "questTemp.EPL_Prologue"))
				{
					dialog.text = StringFromKey("Sailor_43");
					link.l1 = StringFromKey("Sailor_44");
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
					DeleteAttribute(link, "l3");
					npchar.quest.meeting = "0";
					break;
				}
				//<-- Эммануэль Пардаль
			}
			else
			{
				dialog.text = StringFromKey("Sailor_13", pchar);
				link.l1 = StringFromKey("Sailor_14");
				link.l1.go = "question";
				link.l2 = StringFromKey("Sailor_17", RandPhraseSimple(
							StringFromKey("Sailor_15"),
							StringFromKey("Sailor_16")));
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = StringFromKey("Sailor_18");
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Sailor_19", pchar, GetFullName(npchar)),
						StringFromKey("Sailor_20"),
						StringFromKey("Sailor_21"),
						StringFromKey("Sailor_22"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Sailor_23"),
						StringFromKey("Sailor_24"),
						StringFromKey("Sailor_25"),
						StringFromKey("Sailor_26"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_sailor", "rumours_sailor", "rumours_sailor", "exit", npchar, Dialog.CurrentNode);
		break;

		case "crew":
			switch (drand(2))
			{
				case 0: sTemp = StringFromKey("Sailor_27"); break;
				case 1: sTemp = StringFromKey("Sailor_28"); break;
				case 2: sTemp = StringFromKey("Sailor_29"); break;
			}
			dialog.text = sTemp;
			link.l1 = StringFromKey("Sailor_30", pchar);
			link.l1.go = "crew_1";
			link.l2 = StringFromKey("Sailor_31");
			link.l2.go = "exit";
		break;

		case "crew_1":
			switch (sti(npchar.quest.crew.type))
			{
				case 0: sTemp = StringFromKey("Sailor_32"); break;
				case 1: sTemp = StringFromKey("Sailor_33"); break;
				case 2: sTemp = StringFromKey("Sailor_34"); break;
			}
			dialog.text = StringFromKey("Sailor_35", FindPeoplesString(sti(npchar.quest.crew.qty), "No"), sTemp);
			if (GetFreeCrewQuantity(pchar) >= sti(npchar.quest.crew.qty))
			{
				link.l1 = StringFromKey("Sailor_36");
				link.l1.go = "crew_2";
			}
			link.l2 = StringFromKey("Sailor_37");
			link.l2.go = "exit";
		break;

		case "crew_2":
			iTemp = sti(npchar.quest.crew.money) * sti(npchar.quest.crew.qty);
			dialog.text = StringFromKey("Sailor_38", FindMoneyString(sti(npchar.quest.crew.money)));
			if (sti(pchar.money) >= iTemp)
			{
				link.l1 = StringFromKey("Sailor_39", pchar.ship.name);
				link.l1.go = "crew_3";
			}
			link.l2 = StringFromKey("Sailor_40");
			link.l2.go = "exit";
		break;

		case "crew_3":
			iTemp = sti(npchar.quest.crew.money) * sti(npchar.quest.crew.qty);
			AddMoneyToCharacter(pchar, -iTemp);
			dialog.text = StringFromKey("Sailor_41");
			link.l1 = StringFromKey("Sailor_42");
			link.l1.go = "crew_4";
		break;

		case "crew_4":
			DialogExit();
			int iBaseCrew = sti(pchar.ship.crew.quantity);
			int iType = sti(npchar.quest.crew.type);
			AddCharacterCrew(pchar, sti(npchar.quest.crew.qty));
			//увеличиваем опыт
			iTemp = makeint(sti(npchar.quest.crew.qty) * 60 / (iBaseCrew + 1));
			switch (iType)
			{
				case 0: ChangeCrewExp(pchar, "Sailors", iTemp); break;
				case 1: ChangeCrewExp(pchar, "Cannoners", iTemp); break;
				case 2: ChangeCrewExp(pchar, "Soldiers", iTemp); break;
			}
			if (iBaseCrew == 0) //Rosarak fix
			{
				if (iType != 0) pchar.Ship.Crew.Exp.Sailors = 50.0;
				if (iType != 1) pchar.Ship.Crew.Exp.Cannoners = 50.0;
				if (iType != 2) pchar.Ship.Crew.Exp.Soldiers = 50.0;
			}
			//увеличиваем мораль
			iTemp = makeint(sti(npchar.quest.crew.qty) / 10) + 1;
			if (iTemp > 5) iTemp = 5;
			AddCrewMorale(pchar, iTemp);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;

		//замечание по обнаженному оружию от персонажей типа citizen
		/*case "CitizenNotBlade": //HardCoffee ref TODO подчистить, если всё норм
			dialog.text = NPCharSexPhrase(NPChar, StringFromKey("Sailor_40"), StringFromKey("Sailor_41"));
			link.l1 = LinkRandPhrase(StringFromKey("Sailor_42"), StringFromKey("Sailor_43"), StringFromKey("Sailor_44"));
			link.l1.go = "exit";
		break;*/

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

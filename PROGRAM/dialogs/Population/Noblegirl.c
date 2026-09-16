//Jason общий диалог дворянок
#include "DIALOGS\Rumours\Simple_rumors.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

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
			NextDiag.TempNode = "First time";
			//первая встреча
			if (NPChar.quest.meeting == "0")
			{
				dialog.text = StringFromKey("Noblegirl_3", RandPhraseSimple(
							StringFromKey("Noblegirl_1", GetAddress_Form(NPChar)),
							StringFromKey("Noblegirl_2")));
				link.l1 = StringFromKey("Noblegirl_4", TimeGreeting(), GetAddress_FormToNPC(NPChar));
				link.l1.go = "question";
				link.l2 = StringFromKey("Noblegirl_7", RandPhraseSimple(
							StringFromKey("Noblegirl_5"),
							StringFromKey("Noblegirl_6")));
				link.l2.go = "quests"; //(перессылка в файл города)
				link.l3 = PCharRepPhrase(
							StringFromKey("Noblegirl_10", RandPhraseSimple(
									StringFromKey("Noblegirl_8"),
									StringFromKey("Noblegirl_9", pchar))),
							StringFromKey("Noblegirl_13", RandPhraseSimple(
									StringFromKey("Noblegirl_11"),
									StringFromKey("Noblegirl_12"))));
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
				//--> Эммануэль Пардаль
				if (CheckAttribute(pchar, "questTemp.EPL_Prologue"))
				{
					dialog.text = NPCharSexPhrase(NPChar, StringFromKey("Gipsy_69", TimeGreeting(), pchar.name), StringFromKey("Gipsy_70", TimeGreeting(), pchar.name));
					link.l1 = StringFromKey("Gipsy_71", TimeGreeting(), npchar.name);
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
				//повторные обращения
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("Noblegirl_14"),
							StringFromKey("Noblegirl_15"),
							StringFromKey("Noblegirl_16", pchar),
							StringFromKey("Noblegirl_17"), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("Noblegirl_18"),
							StringFromKey("Noblegirl_19", pchar),
							StringFromKey("Noblegirl_20"),
							StringFromKey("Noblegirl_21"), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			}
		break;

		//сюда вставляем любые проверки и направления на квесты
		case "question":
			dialog.text = StringFromKey("Noblegirl_25", LinkRandPhrase(
						StringFromKey("Noblegirl_22"),
						StringFromKey("Noblegirl_23"),
						StringFromKey("Noblegirl_24")));
			link.l1 = StringFromKey("Noblegirl_29", LinkRandPhrase(
						StringFromKey("Noblegirl_26"),
						StringFromKey("Noblegirl_27"),
						StringFromKey("Noblegirl_28")));
			link.l1.go = "rumours_noblegirl";
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнаженному оружию от персонажей типа citizen
		/*case "CitizenNotBlade": //HardCoffee ref
			dialog.text = NPCharSexPhrase(NPChar, StringFromKey("Noblegirl_24"), StringFromKey("Noblegirl_25"));
			link.l1 = LinkRandPhrase(StringFromKey("Noblegirl_26"), StringFromKey("Noblegirl_27"), StringFromKey("Noblegirl_28"));
			link.l1.go = "exit";
		break;*/

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

//TODO: переработка гадания с новыми интересными фишками

#include "DIALOGS\Rumours\Simple_rumors.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int poison_price;

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
			if (npchar.quest.meeting == "0")
			{
				dialog.text = StringFromKey("Gipsy_4", LinkRandPhrase(
							StringFromKey("Gipsy_1", pchar),
							StringFromKey("Gipsy_2"),
							StringFromKey("Gipsy_3", pchar)));
				link.l1 = StringFromKey("Gipsy_5");
				link.l1.go = "exit";
				link.l2 = StringFromKey("Gipsy_6");
				link.l2.go = "guess";
				link.l3 = StringFromKey("Gipsy_9", RandPhraseSimple(
							StringFromKey("Gipsy_7"),
							StringFromKey("Gipsy_8")));
				link.l3.go = "quests"; //(перессылка в файл города)
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
				break;
			}
			dialog.text = StringFromKey("Gipsy_10", pchar);
			link.l1 = StringFromKey("Gipsy_11");
			link.l1.go = "exit";
			link.l2 = StringFromKey("Gipsy_14", RandPhraseSimple(
						StringFromKey("Gipsy_12"),
						StringFromKey("Gipsy_13")));
			link.l2.go = "quests"; //(перессылка в файл города)
		break;

		//-------------------------------------------------гадание-------------------------------------------------
		case "guess":
			dialog.text = StringFromKey("Gipsy_15", pchar);
			link.l1 = StringFromKey("Gipsy_16", pchar);
			link.l1.go = "exit";
			if (sti(pchar.money) >= 100)
			{
				link.l2 = StringFromKey("Gipsy_17");
				link.l2.go = "guess_1";
			}
		break;

		case "guess_1":
			dialog.text = StringFromKey("Gipsy_18", pchar);
			link.l1 = StringFromKey("Gipsy_19");
			link.l1.go = "guess_rate_1";
			if (sti(pchar.money) >= 500)
			{
				link.l2 = StringFromKey("Gipsy_20");
				link.l2.go = "guess_rate_2";
			}
			if (sti(pchar.money) >= 1000)
			{
				link.l3 = StringFromKey("Gipsy_21");
				link.l3.go = "guess_rate_3";
			}
			if (sti(pchar.money) >= 5000)
			{
				link.l4 = StringFromKey("Gipsy_22");
				link.l4.go = "guess_rate_4";
			}
			link.l5 = StringFromKey("Gipsy_23");
			link.l5.go = "guess_rate_none";
		break;

		sTemp = GuessText();
		case "guess_rate_1"://никаких плюшек
			AddMoneyToCharacter(pchar, -100);
			dialog.text = StringFromKey("Gipsy_24", pchar, sTemp);
			link.l1 = StringFromKey("Gipsy_28", LinkRandPhrase(
						StringFromKey("Gipsy_25"),
						StringFromKey("Gipsy_26"),
						StringFromKey("Gipsy_27")));
			link.l1.go = "exit";
		break;

		case "guess_rate_2"://немного в везение или скрытность
			AddMoneyToCharacter(pchar, -500);
			dialog.text = StringFromKey("Gipsy_29", pchar, sTemp);
			link.l1 = StringFromKey("Gipsy_33", LinkRandPhrase(
						StringFromKey("Gipsy_30"),
						StringFromKey("Gipsy_31"),
						StringFromKey("Gipsy_32")));
			link.l1.go = "exit";
			if (drand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 30 + rand(10));//везение
			else AddCharacterExpToSkill(pchar, "Sneak", 30 + rand(10));//скрытность
		break;

		case "guess_rate_3"://здоровье + везение или скрытность, харизма
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = StringFromKey("Gipsy_34", pchar, sTemp);
			link.l1 = StringFromKey("Gipsy_38", LinkRandPhrase(
						StringFromKey("Gipsy_35"),
						StringFromKey("Gipsy_36"),
						StringFromKey("Gipsy_37")));
			link.l1.go = "exit";
			AddCharacterHealth(pchar, 1);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (drand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 50 + rand(20));//везение
			else AddCharacterExpToSkill(pchar, "Sneak", 50 + rand(20));//скрытность
		break;

		case "guess_rate_4"://умения в оружие, везение+скрытность, здоровье, харизма
			TEV.GipsyFortuneBonus = "1";
			TEV.GipsyFortuneText = "1";
			sTemp = GuessText();
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = StringFromKey("Gipsy_39", pchar, sTemp);
			link.l1 = StringFromKey("Gipsy_43", LinkRandPhrase(
						StringFromKey("Gipsy_40"),
						StringFromKey("Gipsy_41"),
						StringFromKey("Gipsy_42")));
			link.l1.go = "exit";
			AddCharacterHealth(pchar, 2);
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			AddCharacterExpToSkill(pchar, "Fortune", 50 + rand(100));//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50 + rand(50));//скрытность
			AddComplexSelfExpToScill(20, 20, 20, 20);
		break;

		case "guess_rate_none":
			dialog.text = StringFromKey("Gipsy_44", pchar);
			link.l1 = StringFromKey("Gipsy_45");
			link.l1.go = "guess_exit";
		break;

		case "guess_exit":
			DialogExit();
			AddCharacterHealth(pchar, -10);
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(&TEV, "GipsyFortuneBonus");
		break;
		//<-- гадание

		/*//замечание по обнаженному оружию от персонажей типа citizen
		case "CitizenNotBlade": //HardCoffee ref
			dialog.text = NPCharSexPhrase(NPChar, StringFromKey("Gipsy_39"), StringFromKey("Gipsy_40"));
			link.l1 = LinkRandPhrase(StringFromKey("Gipsy_41"), StringFromKey("Gipsy_42"), StringFromKey("Gipsy_43"));
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;*/

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string GuessText()
{
	string sText;

	if (CheckAttribute(&TEV, "GipsyFortuneText") && !CheckAttribute(&TEV, "GipsyFortuneTimer"))
	{
		switch (rand(2))
		{
			case 0: sText = StringFromKey("Gipsy_46"); break;
			case 1: sText = StringFromKey("Gipsy_47"); break;
			case 2: sText = StringFromKey("Gipsy_48"); break;
		}

		TEV.GipsyFortuneTimer = "1";
		SetTimerFunction("GipsyFortuneBonusEnd", 0, 0, 7);
	}
	else
	{
		switch (dRandEx(19, false))
		{
			case 0: sText = StringFromKey("Gipsy_49", pchar); break;
			case 1: sText = StringFromKey("Gipsy_50"); break;
			case 2: sText = StringFromKey("Gipsy_51"); break;
			case 3: sText = StringFromKey("Gipsy_52", pchar); break;
			case 4: sText = StringFromKey("Gipsy_53"); break;
			case 5: sText = StringFromKey("Gipsy_54"); break;
			case 6: sText = StringFromKey("Gipsy_55"); break;
			case 7: sText = StringFromKey("Gipsy_56", pchar); break;
			case 8: sText = StringFromKey("Gipsy_57", pchar); break;
			case 9: sText = StringFromKey("Gipsy_58", pchar); break;
			case 10: sText = StringFromKey("Gipsy_59"); break;
			case 11: sText = StringFromKey("Gipsy_60", pchar); break;
			case 12: sText = StringFromKey("Gipsy_61"); break;
			case 13: sText = StringFromKey("Gipsy_62", pchar); break;
			case 14: sText = StringFromKey("Gipsy_63", pchar); break;
			case 15: sText = StringFromKey("Gipsy_64"); break;
			case 16: sText = StringFromKey("Gipsy_65", pchar); break;
			case 17: sText = StringFromKey("Gipsy_66"); break;
			case 18: sText = StringFromKey("Gipsy_67"); break;
			case 19: sText = StringFromKey("Gipsy_68"); break;
		}
	}
	DeleteAttribute(&TEV, "GipsyFortuneText");
	return sText;
}

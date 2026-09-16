void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\Tavern\" + NPChar.City + "_Waitress.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.different.FackWaitress"))
			{
				if (pchar.questTemp.different == "FackWaitress_toRoom" || pchar.questTemp.different == "FackWaitress_toRoomUp")
				{
					dialog.text = StringFromKey("Common_Waitress_1");
					link.l1 = StringFromKey("Common_Waitress_2");
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_noMoney" || pchar.questTemp.different == "FackWaitress_fighted")
				{
					dialog.text = StringFromKey("Common_Waitress_3");
					link.l1 = StringFromKey("Common_Waitress_4", pchar.questTemp.different.FackWaitress.Name);
					link.l1.go = "Love_IDN";
				}
				if (pchar.questTemp.different == "FackWaitress_facking")
				{
					dialog.text = StringFromKey("Common_Waitress_5");
					link.l1 = StringFromKey("Common_Waitress_6");
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_fackNoMoney")
				{
					dialog.text = StringFromKey("Common_Waitress_7");
					link.l1 = StringFromKey("Common_Waitress_8");
					link.l1.go = "Love_IDN_1";
				}
				break;
			}
			switch (Rand(4))
			{
				case 0:
					dialog.text = StringFromKey("Common_Waitress_9", pchar);
					link.l1 = "...";
					link.l1.go = "exit";
				break;

				case 1:
					dialog.text = StringFromKey("Common_Waitress_10");
					link.l1 = StringFromKey("Common_Waitress_11", pchar);
					link.l1.go = "exit";
				break;

				case 2:
					if (idRand(npchar.id + "Love", 2) == 0) // Addon-2016 Jason
					{
						dialog.text = StringFromKey("Common_Waitress_12", pchar);
						link.l1 = StringFromKey("Common_Waitress_13", pchar);
						link.l1.go = "exit";
						if (pchar.questTemp.different == "free" && !CheckAttribute(pchar, "questTemp.different.FackWaitress") && pchar.questTemp.piratesLine != "Soukins_toPuertoPrincipe" && PChar.sex != "woman" && pchar.questTemp.piratesLine != "Soukins_seekRings" && Pchar.questTemp.CapBloodLine != true && !CheckAttribute(pchar, "GenQuest.EncGirl") && !CheckAttrValue(pchar, "GenQuest.EncGirl", "HorseToTavern"))
						{
							link.l2 = StringFromKey("Common_Waitress_14");
							link.l2.go = "Love_1";
						}
					}
					else
					{
						dialog.text = StringFromKey("Common_Waitress_15");
						link.l1 = StringFromKey("Common_Waitress_16");
						link.l1.go = "exit";
					}
				break;

				case 3:
					dialog.text = StringFromKey("Common_Waitress_17");
					link.l1 = StringFromKey("Common_Waitress_18");
					link.l1.go = "exit";
				break;

				case 4:
					dialog.text = StringFromKey("Common_Waitress_19");
					link.l1 = StringFromKey("Common_Waitress_20");
					link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City")) //квест мэра поп поиску шпиона
			{
				link.l4 = StringFromKey("Common_Waitress_21", pchar);
				if (pchar.GenQuest.SeekSpy.City == "1")
				{
					link.l4.go = "SeekSpy_Seen";
				}
				else
				{
					link.l4.go = "SeekSpy_NotSeen";
				}
			}
			link.l9 = StringFromKey("Common_Waitress_22");
			link.l9.go = "quests"; //(перессылка в файл города)
		break;

		case "Love_1":
			dialog.text = StringFromKey("Common_Waitress_23");
			link.l1 = StringFromKey("Common_Waitress_24");
			link.l1.go = "exit";
			pchar.questTemp.different = "FackWaitress_toRoom";
			SetTimerFunction("WaitressFack_null", 0, 0, 1); //освобождаем разрешалку на миниквесты на след. день
			//Шанс, что ограбят, если рендом выпадет на 0. он же делитель сколько она вытащит из кармана
			pchar.questTemp.different.FackWaitress.Kick = idRand(npchar.id, 2);
			if (npchar.city == "Villemstad") pchar.questTemp.different.FackWaitress.Kick = 1; //Квестовая официантка - давалка и не обманывает
			pchar.questTemp.different.FackWaitress.Name = GetFullName(npchar); //запомним имя официантки
			pchar.questTemp.different.FackWaitress.City = npchar.city;
			//делаем клона официантки
			sld = GetCharacter(NPC_GenerateCharacter("WairessQuest", npchar.model, "woman", npchar.model.animation, 5, sti(npchar.nation), 3, false));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.dialog.Filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "Waitress";
			Pchar.quest.WaitressFack_inRoom.win_condition.l1 = "location";
			Pchar.quest.WaitressFack_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			Pchar.quest.WaitressFack_inRoom.function = "WaitressFack_inRoom";
			ChangeCharacterReputation(pchar, -1);
		break;
		case "Love_IDN":
			dialog.text = StringFromKey("Common_Waitress_25");
			link.l1 = StringFromKey("Common_Waitress_26");
			link.l1.go = "exit";
		break;
		case "Love_IDN_1":
			dialog.text = StringFromKey("Common_Waitress_27");
			link.l1 = StringFromKey("Common_Waitress_28");
			link.l1.go = "Love_IDN_2";
		break;
		case "Love_IDN_2":
			dialog.text = StringFromKey("Common_Waitress_29");
			link.l1 = StringFromKey("Common_Waitress_30");
			link.l1.go = "exit";
		break;

		case "without_money":
			NextDiag.TempNode = "first time";
			dialog.text = StringFromKey("Common_Waitress_31");
			link.l1 = StringFromKey("Common_Waitress_32");
			link.l1.go = "without_money_2";
		break;

		case "without_money_2":
			dialog.text = StringFromKey("Common_Waitress_33");
			link.l1 = StringFromKey("Common_Waitress_34");
			link.l1.go = "without_money_3";
		break;

		case "without_money_3":
			dialog.text = StringFromKey("Common_Waitress_35");
			link.l1 = StringFromKey("Common_Waitress_36");
			link.l1.go = "without_money_4";
		break;

		case "without_money_4":
			dialog.text = StringFromKey("Common_Waitress_37");
			link.l2 = StringFromKey("Common_Waitress_38");
			link.l2.go = "exit";
		break;
		//==> eddy. квест мэра, вопросы не замечала ли шпиона
		case "SeekSpy_Seen":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Common_Waitress_39"),
						StringFromKey("Common_Waitress_40"),
						StringFromKey("Common_Waitress_41"),
						StringFromKey("Common_Waitress_42"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Common_Waitress_43", pchar),
						StringFromKey("Common_Waitress_44"),
						StringFromKey("Common_Waitress_45"),
						StringFromKey("Common_Waitress_46", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		case "SeekSpy_NotSeen":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Common_Waitress_47"),
						StringFromKey("Common_Waitress_48"),
						StringFromKey("Common_Waitress_49"),
						StringFromKey("Common_Waitress_50"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Common_Waitress_51", pchar),
						StringFromKey("Common_Waitress_52"),
						StringFromKey("Common_Waitress_53"),
						StringFromKey("Common_Waitress_54", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
}

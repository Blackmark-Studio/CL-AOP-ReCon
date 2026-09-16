// реплики солдат на палубе при разговоре в море
// форт-стража и комендант форта
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
		case "exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "First time":
			dialog.text = StringFromKey("Sailors_dialog_1");
			Link.l1 = StringFromKey("Sailors_dialog_2");
			Link.l1.go = "exit";

			NextDiag.TempNode = "first time";
		break;
		//  на палубе -->
		case "On_Deck":
			dialog.text = StringFromKey("Sailors_dialog_3");
			Link.l1 = StringFromKey("Sailors_dialog_4");
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Deck";
			/*
						// Первый церковный генератор
						if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern"))
						{
							if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"))
							{
								dialog.text = "Госпо"+ GetSexPhrase("дин","жа") +", вы кого-то ищете?";
								Link.l1 = "Да, парень. Могу я видеть капитана этого судна?";
								Link.l1.go = "ChurchQuest1_Node1";
							}
							else
							{
								dialog.text = "По всем вопросам обращайтесь к капитану. Он недавно сошёл на берег.";
								Link.l1 = "Хорошо-хорошо";
								Link.l1.go = "exit";
							}
							break;
						}
			*/
			//--> eddy. квест мэра, закрываем выход с палубы и ноду даем нужную
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && pchar.GenQuest.CaptainId == "MQPirate")
			{
				dialog.text = StringFromKey("Sailors_dialog_7", RandPhraseSimple(
							StringFromKey("Sailors_dialog_5", pchar),
							StringFromKey("Sailors_dialog_6", pchar)));
				Link.l1 = StringFromKey("Sailors_dialog_8");
				Link.l1.go = "exit";
			}
		//<-- eddy. квест мэра, закрываем выход с палубы
		break;
		/*
				case "ChurchQuest1_Node1":
					dialog.text = "Вам лучше поискать его в порту.";
					Link.l1 = "Спасибо, любезный.";
					Link.l1.go = "exit";
					NextDiag.TempNode = "On_Deck";
					PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true;
					DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"); // Не спрашиваем моряков
				break;
		*/
		//  на палубе <--

		// ugeen --> разговор с боцманом по генератору "Повод для спешки"
		case "On_MyShip_Deck":
			dialog.text = StringFromKey("Sailors_dialog_9");
			link.l1 = StringFromKey("Sailors_dialog_10");
			link.l1.go = "On_MyShip_Deck_1";
		break;

		case "On_MyShip_Deck_1":
			if (pchar.questTemp.ReasonToFast == "speakSuccess_chain_A")
			{
				// карты не было
				dialog.text = StringFromKey("Sailors_dialog_11", FindMoneyString(sti(pchar.questTemp.ReasonToFast.p9)));
			}
			if (pchar.questTemp.ReasonToFast == "speakSuccess_chain_B")
			{
				// карту отобрали
				GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
				dialog.text = StringFromKey("Sailors_dialog_12", FindMoneyString(sti(pchar.questTemp.ReasonToFast.p9)));
			}
			link.l1 = StringFromKey("Sailors_dialog_13");
			link.l1.go = "On_MyShip_Deck_End";
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.ReasonToFast.p9));
			pchar.Ship.Crew.Morale = MORALE_MAX;
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("ReasonToFast", "17");
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("ся", "ась"));
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar, "TownEscape");
			DeleteAttribute(pchar, "questTemp.ReasonToFast");
			QuestOpenSeaExit();
		break;

		case "On_MyShip_Deck_End":
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;

		// разговор с боцманом по генератору 'Операция Галеон'
		case "CapComission_OnShipDeck":
			dialog.text = StringFromKey("Sailors_dialog_14");
			link.l1 = StringFromKey("Sailors_dialog_15");
			link.l1.go = "CapComission_OnShipDeck1";
		break;

		case "CapComission_OnShipDeck1":
			dialog.text = StringFromKey("Sailors_dialog_16");
			link.l1 = StringFromKey("Sailors_dialog_17");
			link.l1.go = "CapComission_OnShipDeck2";
		break;

		case "CapComission_OnShipDeck2":
			dialog.text = StringFromKey("Sailors_dialog_18");
			link.l1 = StringFromKey("Sailors_dialog_19");
			link.l1.go = "CapComission_OnShipDeck3";
		break;

		case "CapComission_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("CaptainComission2", "25");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterReputationABS(pchar, 4);
			pchar.quest.CaptainComission_CapEscapeCleanup.over = "yes";
			DeleteAttribute(pchar, "TownEscape");
			DeleteAttribute(pchar, "GenQuest.CaptainComission.canSpeakBoatswain");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			QuestOpenSeaExit();
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		// <-- ugeen

		// разговор с боцманом по ситуациям в трюме
		case "Hold_GenQuest_OnShipDeck":
			dialog.text = StringFromKey("Sailors_dialog_20");
			link.l1 = StringFromKey("Sailors_dialog_21");
			link.l1.go = "Hold_GenQuest_OnShipDeck1";
		break;

		case "Hold_GenQuest_OnShipDeck1":
			dialog.text = StringFromKey("Sailors_dialog_22", pchar.GenQuest.Hold_GenQuest.CapName);
			link.l1 = StringFromKey("Sailors_dialog_23");
			link.l1.go = "Hold_GenQuest_OnShipDeck2";
		break;

		case "Hold_GenQuest_OnShipDeck2":
			dialog.text = StringFromKey("Sailors_dialog_24");
			link.l1 = StringFromKey("Sailors_dialog_25");
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;

		case "Hold_GenQuest_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			ReleasePrisoner(sld);
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar, "TownEscape");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest.canSpeakSailor");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest");
			QuestOpenSeaExit();
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;

		case "Hold_GenQuest_OnShipDeck4":
			dialog.text = StringFromKey("Sailors_dialog_26");
			link.l1 = StringFromKey("Sailors_dialog_27", pchar.GenQuest.Hold_GenQuest.CapName);
			link.l1.go = "Hold_GenQuest_OnShipDeck5";
		break;

		case "Hold_GenQuest_OnShipDeck5":
			dialog.text = StringFromKey("Sailors_dialog_28");
			link.l1 = StringFromKey("Sailors_dialog_29");
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;

		// Warship 09.07.09 Базар с нашим матросом на палубе Мэри Селест -->
		case "On_MaryCeleste_Deck":
			Dialog.text = StringFromKey("Sailors_dialog_30");
			Link.l1 = StringFromKey("Sailors_dialog_31");
			Link.l1.go = "On_MaryCeleste_Deck_1";
		break;

		case "On_MaryCeleste_Deck_1":
			Dialog.text = StringFromKey("Sailors_dialog_32");
			Link.l1 = StringFromKey("Sailors_dialog_33");
			Link.l1.go = "On_MaryCeleste_Deck_2";
		break;

		case "On_MaryCeleste_Deck_2":
			Dialog.text = StringFromKey("Sailors_dialog_34");
			Link.l1 = StringFromKey("Sailors_dialog_35");
			Link.l1.go = "On_MaryCeleste_Last";
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;

		case "On_MaryCeleste_Last":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetCitizenType(NPChar); // Чтоб по палубе ходил

			NPChar = GetRealShip(GetCharacterShipType(CharacterFromID("MaryCelesteCapitan")));
			NPChar.TurnRate = sti(PChar.QuestTemp.MaryCeleste.TurnRate); // Вернём маневренность, для интерфейса

			chrDisableReloadToLocation = false; // Откроем выход

			LaunchTransferMain(PChar, CharacterFromID("MaryCelesteCapitan"), "MaryCelesteTransfer");
		break;

		case "On_MaryCeleste_Deck_SailorLast":
			switch (rand(2))
			{
				case 0:
					Dialog.text = StringFromKey("Sailors_dialog_36");
					Link.l1 = StringFromKey("Sailors_dialog_37");
					Link.l1.go = "exit";
				break;

				case 1:
					Dialog.text = StringFromKey("Sailors_dialog_38");
					Link.l1 = StringFromKey("Sailors_dialog_39", pchar);
					Link.l1.go = "exit";
				break;

				case 2:
					Dialog.text = StringFromKey("Sailors_dialog_40");
					Link.l1 = StringFromKey("Sailors_dialog_41");
					Link.l1.go = "On_MaryCeleste_Deck_SailorLast_1";
				break;
			}

			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;

		case "On_MaryCeleste_Deck_SailorLast_1":
			Dialog.text = StringFromKey("Sailors_dialog_42");
			Link.l1 = StringFromKey("Sailors_dialog_43");
			Link.l1.go = "exit";
		break;
		// <-- Базар с нашим матросом на палубе Мэри Селест

		//  на палубе <--
		case "On_Fort":
			dialog.text = StringFromKey("Sailors_dialog_46", RandPhraseSimple(
						StringFromKey("Sailors_dialog_44"),
						StringFromKey("Sailors_dialog_45")));
			Link.l1 = StringFromKey("Sailors_dialog_47");
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort";
		break;

		case "On_Fort_Head":
			dialog.text = StringFromKey("Sailors_dialog_50", RandPhraseSimple(
						StringFromKey("Sailors_dialog_48"),
						StringFromKey("Sailors_dialog_49")));
			Link.l1 = StringFromKey("Sailors_dialog_51");
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort_Head";
		break;

		case "Morgan_wait_you":
			dialog.text = StringFromKey("Sailors_dialog_54", RandPhraseSimple(
						StringFromKey("Sailors_dialog_52"),
						StringFromKey("Sailors_dialog_53")));
			Link.l1 = StringFromKey("Sailors_dialog_55");
			Link.l1.go = "exit";

			NextDiag.TempNode = "Morgan_wait_you";
		break;
	}
}

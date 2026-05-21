void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	string sTemp, sTemp1, str, str1;
	int s1, s2, s3, s4, s5, p1, iColony, iCrewFuckPrice, iCrewQty = GetCrewQuantity(pchar); // > матросы на остальных кораблях эскадры: "Ну да, ну да. Пошли мы нахер." TODO

	if (iCrewQty > 0)
		iCrewFuckPrice = iCrewQty * 30;
	else
		iCrewFuckPrice = 1;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\Brothel\" + NPChar.City + "_Brothel.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--
	switch (Dialog.CurrentNode)
	{
		// ============= хозяйка борделя =============
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,
						StringFromKey("Common_Brothel_4", LinkRandPhrase(
								StringFromKey("Common_Brothel_1", pchar),
								StringFromKey("Common_Brothel_2"),
								StringFromKey("Common_Brothel_3"))),
						StringFromKey("Common_Brothel_8", LinkRandPhrase(
								StringFromKey("Common_Brothel_5", pchar),
								StringFromKey("Common_Brothel_6", pchar),
								StringFromKey("Common_Brothel_7", pchar))));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("Common_Brothel_11", RandPhraseSimple(
								StringFromKey("Common_Brothel_9"),
								StringFromKey("Common_Brothel_10"))),
						StringFromKey("Common_Brothel_14", RandPhraseSimple(
								StringFromKey("Common_Brothel_12"),
								StringFromKey("Common_Brothel_13"))));
				link.l1.go = "exit";
				break;
			}

			//homo Линейка Блада
			if (Pchar.questTemp.CapBloodLine == true)
			{
				dialog.Text = StringFromKey("Common_Brothel_18", LinkRandPhrase(
							StringFromKey("Common_Brothel_15", TimeGreeting()),
							StringFromKey("Common_Brothel_16"),
							StringFromKey("Common_Brothel_17", GetFullName(pchar))));
				Link.l1 = StringFromKey("Common_Brothel_19", NPChar.name);
				Link.l1.go = "exit";
				break;
			}
			//-->> квест Кольцо Жозефины Лодет
			if (CheckAttribute(pchar, "questTemp.PDM_PK_UvestiNaVerh") && npchar.city == "SantoDomingo")
			{
				dialog.text = StringFromKey("Common_Brothel_20", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Common_Brothel_21", npchar.name);
				link.l1.go = "PDM_PK_UvestiNaVerh";
				break;
			}
			//<<-- квест Кольцо Жозефины Лодет

			//-->> квест пожертвования в церковь
			//результаты
			if (npchar.questChurch == "baster")
			{
				dialog.text = StringFromKey("Common_Brothel_22", pchar);
				link.l1 = StringFromKey("Common_Brothel_23");
				link.l1.go = "exit";
				link.l2 = StringFromKey("Common_Brothel_24", pchar);
				link.l2.go = "quests"; //(перессылка в файл города)
				break;
			}
			if (npchar.questChurch == "taken")
			{
				dialog.text = StringFromKey("Common_Brothel_25", pchar);
				link.l1 = StringFromKey("Common_Brothel_26");
				link.l1.go = "exit";
				break;
			}
			if (npchar.questChurch == "yes")
			{
				dialog.text = StringFromKey("Common_Brothel_27", pchar);
				link.l1 = StringFromKey("Common_Brothel_28", pchar);
				link.l1.go = "ResultChurch_1";
				break;
			}
			if (npchar.questChurch == "no")
			{
				dialog.text = StringFromKey("Common_Brothel_29", pchar);
				link.l1 = StringFromKey("Common_Brothel_30", npchar.name);
				link.l1.go = "ResultChurch_2";
				break;
			}
			//-->> дача квеста пожертвования в церковь
			if (rand(2) == 1 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questChurch") > 45 && GetHour() < 20 && !CheckAttribute(npchar, "no_donation"))
			{
				dialog.text = StringFromKey("Common_Brothel_31");
				link.l5 = StringFromKey("Common_Brothel_32");
				link.l5.go = "toChurch";
				//личные флаги хозяйки на взятие квеста
				npchar.questChurch = "taken";
				SaveCurrentNpcQuestDateParam(npchar, "questChurch");
				break;
			}
			//<<-- квест пожертвования в церковь

			//-->> дача развода на секс
			if (rand(3) == 1 && pchar.questTemp.different == "free" && PChar.sex != "woman" && GetNpcQuestPastDayWOInit(npchar, "questSex") > 180 && !CheckAttribute(npchar, "quest.selected") && !CheckAttribute(npchar, "quest.NotGoneToSex.over"))
			{
				if (!CheckAttribute(npchar, "quest.NotGoneToSex"))
				{
					dialog.text = StringFromKey("Common_Brothel_33");
					link.l5 = StringFromKey("Common_Brothel_34");
					link.l5.go = "toHostessSex";
					link.l8 = StringFromKey("Common_Brothel_35", npchar.name);
					link.l8.go = "exit";
					pchar.questTemp.different = "HostessSex";
					SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты 
					SaveCurrentNpcQuestDateParam(npchar, "questSex");
				}
				else
				{
					dialog.text = StringFromKey("Common_Brothel_36");
					link.l1 = StringFromKey("Common_Brothel_37");
					link.l1.go = "exit";
					npchar.quest.NotGoneToSex.over = true; //больше вообще не говоить
				}
				break;
			}
			//<<-- развод на секс

			if (npchar.quest.meeting == "0")
			{
				dialog.text = StringFromKey("Common_Brothel_40", RandPhraseSimple(
							StringFromKey("Common_Brothel_38", pchar, TimeGreeting(), npchar.name, GetAddress_Form(NPChar)),
							StringFromKey("Common_Brothel_39", pchar, TimeGreeting(), NPChar.Name)));
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = StringFromKey("Common_Brothel_43", RandPhraseSimple(
							StringFromKey("Common_Brothel_41", TimeGreeting(), GetAddress_Form(NPChar)),
							StringFromKey("Common_Brothel_42", TimeGreeting(), GetAddress_Form(NPChar))));
			}
			link.l2 = StringFromKey("Common_Brothel_44", npchar.name);
			link.l2.go = "Hostess_1";
			if (CheckShip(pchar) && iCrewQty > 0)
			{
				link.l3 = StringFromKey("Common_Brothel_45", pchar);
				link.l3.go = "ForCrew";
			}
			link.l4 = StringFromKey("Common_Brothel_46");
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakBrothelMadam"))
			{
				if ((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l4.go = "ShipLetters_1";// генератор  "Найденные документы"
				}
				else
				{
					link.l4.go = "quests";
				}
			}
			else
			{
				link.l4.go = "quests";//(перессылка в файл города)
			}
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = StringFromKey("Common_Brothel_47", npchar.name);
				link.l5.go = "TakeMayorsRing_H1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
			link.l9 = StringFromKey("Common_Brothel_48");
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		case "ShipLetters_1":
			pchar.questTemp.different.GiveShipLetters.speakBrothelMadam = true;
			dialog.text = StringFromKey("Common_Brothel_51", RandPhraseSimple(
						StringFromKey("Common_Brothel_49"),
						StringFromKey("Common_Brothel_50")));
			link.l1 = StringFromKey("Common_Brothel_52", pchar, npchar.name);
			link.l1.go = "ShipLetters_2";
		break;
		case "ShipLetters_2":
			if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = StringFromKey("Common_Brothel_53");
				link.l1 = StringFromKey("Common_Brothel_54");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Common_Brothel_55");
				link.l1 = StringFromKey("Common_Brothel_56");
				link.l1.go = "exit";
				link.l2 = StringFromKey("Common_Brothel_57", pchar);
				link.l2.go = "ShipLetters_3";
			}
		break;

		case "ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook");
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "2");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Hostess_1":
			if (!CheckAttribute(npchar, "quest.selected"))
			{
				if (CheckNPCQuestDate(npchar, "quest.date"))
				{
					dialog.text = StringFromKey("Common_Brothel_58", pchar);
					Link.l1 = StringFromKey("Common_Brothel_59", pchar);
					Link.l1.go = "Hostess_NotChoice";
					Link.l2 = StringFromKey("Common_Brothel_60", pchar);
					Link.l2.go = "Hostess_Choice";
				}
				else
				{
					dialog.text = StringFromKey("Common_Brothel_61");
					Link.l1 = StringFromKey("Common_Brothel_62", pchar);
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = StringFromKey("Common_Brothel_63", pchar);
				Link.l1 = StringFromKey("Common_Brothel_64");
				Link.l1.go = "exit";
			}
		break;

		case "Hostess_NotChoice":
			sld = GetFreeHorseRef(npchar.city);
			location = &locations[FindLocation(npchar.city + "_Brothel")];
			if (sld.id == "none" || GetNpcQuestPastDayParam(location, "Brothel_date") > 98)
			{
				dialog.text = StringFromKey("Common_Brothel_65");
				Link.l1 = StringFromKey("Common_Brothel_66");
				Link.l1.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Common_Brothel_67", pchar, GetFullName(sld), FindMoneyString(sti(sld.quest.price)));
				Link.l1 = StringFromKey("Common_Brothel_68");
				Link.l1.go = "exit";
				if (sti(pchar.money) >= sti(sld.quest.price))
				{
					Link.l2 = StringFromKey("Common_Brothel_69", pchar);
					Link.l2.go = "Hostess_NotChoice_agree";
					npchar.quest.choiceIdx = sld.index;
				}
				else
				{
					Link.l1 = StringFromKey("Common_Brothel_70");
					Link.l1.go = "exit";
				}
			}
		break;
		case "Hostess_NotChoice_agree":
			sld = &characters[sti(npchar.quest.choiceIdx)];
			if (sti(pchar.money) >= sti(sld.quest.price))
			{
				dialog.text = StringFromKey("Common_Brothel_71", pchar, sld.name);
				Link.l1 = StringFromKey("Common_Brothel_72", pchar);
				Link.l1.go = "exit";
				AddMoneyToCharacter(pchar, -sti(sld.quest.price));
				sld.dialog.currentnode = "Horse_ReadyFack";
				//--> таймер на возврат, чтобы не вечно ждали
				str = npchar.city;
				pchar.quest.(str).win_condition.l1 = "Timer";
				pchar.quest.(str).win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
				pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
				pchar.quest.(str).HorseId = sld.id;
				pchar.quest.(str).locator = sld.location.locator;
				//<-- таймер на возврат, чтобы не вечно ждали
				ChangeCharacterAddressGroup(sld, npchar.city + "_Brothel_room", "goto", "goto" + (rand(2) + 1));
				LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload2_back", false); //открываем комнату
				npchar.quest.selected = true; //флаг взял девку у хозяйки
				SetNPCQuestDate(npchar, "quest.date"); //дату взятия запишем
				for (int n = 0; n < MAX_CHARACTERS; n++)
				{
					makeref(sld, Characters[n]);
					if (sld.location == npchar.city + "_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
					{
						sld.dialog.currentnode = "Horse_4";
					}
				}

				// генератор найденных бумаг
				if ((rand(4) == 1) && (pchar.questTemp.different == "free") && (!CheckCharacterItem(pchar, "CaptainBook")) && GetNpcQuestPastDayWOInit(npchar, "questShipLetters") > 10)
				{
					pchar.questTemp.different = "GiveShipLetters";
					pchar.questTemp.different.GiveShipLetters = "toBrothel";
					pchar.questTemp.different.GiveShipLetters.Id = GetFullName(npchar);
					pchar.questTemp.different.GiveShipLetters.city = npchar.city;
					pchar.questTemp.different.GiveShipLetters.variant = rand(2);
					p1 = rand(20 - MOD_SKILL_ENEMY_RATE) + 1; // даем хотя бы один день
					s1 = rand(80 - pchar.rank - p1) * 50 + rand(100);
					s2 = s1 * 2;
					s3 = s1 * rand(GetCharacterSPECIAL(pchar, "Luck")) + s1;
					s4 = s2 + s3;
					s5 = s4 * GetCharacterSPECIAL(pchar, "Charisma");
					pchar.questTemp.different.GiveShipLetters.price1 = s1;
					pchar.questTemp.different.GiveShipLetters.price2 = s2;
					pchar.questTemp.different.GiveShipLetters.price3 = s3;
					pchar.questTemp.different.GiveShipLetters.price4 = s4;
					pchar.questTemp.different.GiveShipLetters.price5 = s5;

					sld = ItemsFromID("CaptainBook");
					sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
					//ложим бумаги в итем								
					sTemp = "_Brothel_room";
					sTemp1 = "_town";
					sld.shown = true;
					sld.startLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp;
					sld.startLocator = "item" + (rand(4) + 1);
					sld.endLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp1;
					pchar.questTemp.different.GiveShipLetters.item = true; //флаг -  бумаги валяются в итемах
					Log_QuestInfo("Бумаги находятся в локации " + sld.startLocation + ", в локаторе " + sld.startLocator + " p1 : " + p1 + "");

					pchar.quest.CheckShipLetters.win_condition.l1 = "location";
					pchar.quest.CheckShipLetters.win_condition.l1.location = sld.endLocation;
					pchar.quest.CheckShipLetters.function = "CheckShipLetters";

					SetTimerFunction("GiveShipLetters_null", 0, 0, p1); //освобождаем разрешалку на миниквесты 
					SaveCurrentNpcQuestDateParam(npchar, "questShipLetters");
				}

				// генератор - "Повод для спешки"			
				if ((rand(5) == 2) && !CheckAttribute(pchar, "questTemp.ReasonToFast") && GetNpcQuestPastDayWOInit(npchar, "questReasonToFast") > 20)
				{
					iColony = FindColony(npchar.city);
					if (sti(Colonies[iColony].HeroOwn) == false && npchar.city != "Panama" && npchar.city != "Charles" && npchar.city != "Providencia")
					{
						pchar.questTemp.ReasonToFast = "Begin";
						pchar.questTemp.ReasonToFast.city = npchar.city;
						sTemp1 = "_town";
						pchar.quest.CheckReasonToFast.win_condition.l1 = "location";
						pchar.quest.CheckReasonToFast.win_condition.l1.location = npchar.city + sTemp1;
						pchar.quest.CheckReasonToFast.function = "ReasonToFast_CheckHorse";
						SaveCurrentNpcQuestDateParam(npchar, "questReasonToFast");
					}
				}

			}
			else
			{
				dialog.text = StringFromKey("Common_Brothel_73", pchar, sld.name, FindMoneyString(sti(sld.quest.price)));
				Link.l1 = StringFromKey("Common_Brothel_74");
				Link.l1.go = "exit";
			}
		break;

		case "Hostess_Choice":
			dialog.text = StringFromKey("Common_Brothel_75");
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
		break;
		case "Hostess_Choice_1":
			sld = CheckHorsesName(npchar.city, 9);
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("Common_Brothel_76");
				Link.l1 = StringFromKey("Common_Brothel_77", pchar);
				Link.l1.go = "Hostess_Choice_2";
				Link.l2 = StringFromKey("Common_Brothel_78");
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Common_Brothel_79", GetFullName(sld));
				Link.l1 = StringFromKey("Common_Brothel_80");
				Link.l1.go = "Hostess_NotChoice_agree";
				Link.l2 = StringFromKey("Common_Brothel_81");
				Link.l2.go = "Hostess_Choice_2";
				npchar.quest.choiceIdx = sld.index;
			}
		break;
		case "Hostess_Choice_2":
			dialog.text = StringFromKey("Common_Brothel_82");
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
			Link.l2 = StringFromKey("Common_Brothel_83");
			Link.l2.go = "exit";
		break;
		//==> команда
		case "ForCrew":
			dialog.text = StringFromKey("Common_Brothel_84", pchar, FindMoneyString(iCrewFuckPrice));
			link.l1 = StringFromKey("Common_Brothel_85", pchar);
			link.l1.go = "ForCrew_1";
			link.l2 = StringFromKey("Common_Brothel_86");
			link.l2.go = "exit";
		break;

		case "ForCrew_1":
			if (sti(Pchar.money) >= iCrewFuckPrice)
			{
				AddMoneyToCharacter(Pchar, -makeint(iCrewFuckPrice));
				AddCrewMorale(Pchar, 10);
				LAi_Fade("", "");
				AddTimeToCurrent(5 + rand(1), rand(30));
				DialogExit();
			}
			else
			{
				dialog.text = StringFromKey("Common_Brothel_87");
				link.l1 = StringFromKey("Common_Brothel_88");
				link.l1.go = "exit";
			}
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("Common_Brothel_89", pchar);
			link.l1 = StringFromKey("Common_Brothel_90");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//просьба о пожертвовании в церкви
		case "toChurch":
			dialog.text = StringFromKey("Common_Brothel_91");
			link.l1 = StringFromKey("Common_Brothel_92");
			link.l1.go = "toChurch_1";
		break;
		case "toChurch_1":
			dialog.text = StringFromKey("Common_Brothel_93");
			link.l1 = StringFromKey("Common_Brothel_94");
			link.l1.go = "toChurch_2";
		break;
		case "toChurch_2":
			pchar.questTemp.different.HostessChurch.money = (rand(4) + 1) * 300;
			dialog.text = StringFromKey("Common_Brothel_95", FindMoneyString(sti(pchar.questTemp.different.HostessChurch.money)));
			link.l1 = StringFromKey("Common_Brothel_96");
			link.l1.go = "toChurch_3";
			link.l2 = StringFromKey("Common_Brothel_97", pchar);
			link.l2.go = "toChurch_4";
		break;
		case "toChurch_3":
			dialog.text = StringFromKey("Common_Brothel_98");
			link.l1 = StringFromKey("Common_Brothel_99");
			link.l1.go = "exit";
			pchar.questTemp.different.HostessChurch.city = npchar.city; //город
			pchar.questTemp.different = "HostessChurch_toChurch";
			SetTimerFunction("HostessChurch_null", 0, 0, 1); //освобождаем разрешалку на миниквесты и чистим структуру
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.HostessChurch.money));
			ChangeCharacterReputation(pchar, 0.30);
		break;
		case "toChurch_4":
			dialog.text = StringFromKey("Common_Brothel_100");
			link.l1 = StringFromKey("Common_Brothel_101");
			link.l1.go = "exit";
			pchar.questTemp.different = "free";
			DeleteAttribute(pchar, "questTemp.different.HostessChurch");
			npchar.questChurch = ""; //нулим личный флаг квеста
			ChangeCharacterReputation(pchar, -1);
		break;

		case "ResultChurch_1":
			dialog.text = StringFromKey("Common_Brothel_102");
			link.l1 = StringFromKey("Common_Brothel_103", pchar);
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 3);
			npchar.questChurch = ""; //нулим личный флаг квеста
		break;
		case "ResultChurch_2":
			dialog.text = StringFromKey("Common_Brothel_104", pchar);
			link.l1 = StringFromKey("Common_Brothel_105");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -2);
			npchar.questChurch = ""; //нулим личный флаг квеста
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
		break;
		//Квест Кольцо Жозефины Лодет
		case "PDM_PK_UvestiNaVerh":
			dialog.text = StringFromKey("Common_Brothel_106", pchar);
			link.l1 = StringFromKey("Common_Brothel_107");
			link.l1.go = "PDM_PK_UvestiNaVerh_2";
			link.l2 = StringFromKey("Common_Brothel_108", pchar);
			link.l2.go = "exit";
		break;
		case "PDM_PK_UvestiNaVerh_2":
			if (sti(pchar.Money) >= 3000)
			{
				dialog.text = StringFromKey("Common_Brothel_109", pchar);
				link.l1 = StringFromKey("Common_Brothel_110", pchar);
				link.l1.go = "PDM_PK_UvestiNaVerh_3";
				AddMoneyToCharacter(pchar, -3000);
			}
			else
			{
				dialog.text = "";
				link.l1 = StringFromKey("Common_Brothel_111");
				link.l1.go = "exit";
			}
		break;
		case "PDM_PK_UvestiNaVerh_3":
			DoQuestReloadToLocation("SantoDomingo_Brothel_room", "reload", "reload1_back", "");
			sld = CharacterFromID("PDM_PK_Francheska");
			ChangeCharacterAddressGroup(sld, "SantoDomingo_Brothel_room", "goto", "goto2");
			sld.dialog.filename = "Quest\PDM\Poteryanoe_Koltso.c";
			sld.dialog.currentnode = "NaVerhuSFrancheska";
			chrDisableReloadToLocation = true;
			DeleteAttribute(pchar, "questTemp.PDM_PK_UvestiNaVerh");
			RemoveLandQuestMark_Main(npchar, "PDM_Poteryanoe_Koltso");
		break;
		//поиски кольца губернатора
		case "TakeMayorsRing_H1":
			dialog.text = StringFromKey("Common_Brothel_112");
			link.l1 = StringFromKey("Common_Brothel_113");
			link.l1.go = "TakeMayorsRing_H2";
		break;
		case "TakeMayorsRing_H2":
			dialog.text = StringFromKey("Common_Brothel_114");
			link.l1 = StringFromKey("Common_Brothel_115");
			link.l1.go = "TakeMayorsRing_H3";
		break;
		case "TakeMayorsRing_H3":
			dialog.text = StringFromKey("Common_Brothel_116");
			link.l1 = StringFromKey("Common_Brothel_117", npchar.name);
			link.l1.go = "exit";
		break;
		//------- развод на секс ------------
		case "toHostessSex":
			dialog.text = StringFromKey("Common_Brothel_118");
			link.l1 = StringFromKey("Common_Brothel_119");
			link.l1.go = "toHostessSex_1";
			link.l2 = StringFromKey("Common_Brothel_120");
			link.l2.go = "toHostessSex_2";
			link.l3 = StringFromKey("Common_Brothel_121");
			link.l3.go = "toHostessSex_3";
		break;
		case "toHostessSex_1":
			dialog.text = StringFromKey("Common_Brothel_122");
			link.l1 = StringFromKey("Common_Brothel_123");
			link.l1.go = "exit";
		break;
		case "toHostessSex_2":
			if (rand(1))
			{
				dialog.text = StringFromKey("Common_Brothel_124");
				link.l1 = StringFromKey("Common_Brothel_125");
				link.l1.go = "SpeakHistory";
			}
			else
			{
				dialog.text = StringFromKey("Common_Brothel_126");
				link.l1 = StringFromKey("Common_Brothel_127");
				link.l1.go = "SpeakHistoryTwo";
			}
		break;
		case "toHostessSex_3":
			dialog.text = StringFromKey("Common_Brothel_128");
			link.l1 = StringFromKey("Common_Brothel_129");
			link.l1.go = "exit";
		break;
		//истории
		case "SpeakHistory":
			dialog.text = StringFromKey("Common_Brothel_130");
			if (rand(1))
			{
				link.l1 = StringFromKey("Common_Brothel_131");
				link.l1.go = "SpeakHistory_1";
			}
			else
			{
				link.l1 = StringFromKey("Common_Brothel_132");
				link.l1.go = "SpeakHistory_2";
			}
		break;
		case "SpeakHistory_1":
			dialog.text = StringFromKey("Common_Brothel_133");
			link.l1 = StringFromKey("Common_Brothel_134", GetAddress_Form(PChar));
			link.l1.go = "SpeakHistory_3";
		break;
		case "SpeakHistory_2":
			dialog.text = StringFromKey("Common_Brothel_135");
			link.l1 = StringFromKey("Common_Brothel_136");
			link.l1.go = "exit";
		break;
		case "SpeakHistory_3":
			dialog.text = StringFromKey("Common_Brothel_137");
			link.l1 = StringFromKey("Common_Brothel_138");
			link.l1.go = "SpeakHistory_4";
		break;
		case "SpeakHistory_4":
			dialog.text = StringFromKey("Common_Brothel_139");
			link.l1 = StringFromKey("Common_Brothel_140");
			link.l1.go = "SpeakHistory_5";
		break;
		case "SpeakHistory_5":
			dialog.text = StringFromKey("Common_Brothel_141");
			link.l1 = StringFromKey("Common_Brothel_142");
			link.l1.go = "SpeakHistory_6";
			link.l2 = StringFromKey("Common_Brothel_143");
			link.l2.go = "SpeakHistory_7";
		break;
		case "SpeakHistory_6":
			dialog.text = StringFromKey("Common_Brothel_144");
			link.l1 = StringFromKey("Common_Brothel_145");
			link.l1.go = "exit";
		break;
		case "SpeakHistory_7":
			dialog.text = StringFromKey("Common_Brothel_146");
			link.l1 = StringFromKey("Common_Brothel_147");
			link.l1.go = "SpeakHistory_8";
		break;
		case "SpeakHistory_8":
			dialog.text = StringFromKey("Common_Brothel_148");
			link.l1 = StringFromKey("Common_Brothel_149");
			link.l1.go = "SpeakHistory_9";
			link.l2 = StringFromKey("Common_Brothel_150");
			link.l2.go = "SpeakHistory_10";
		break;
		case "SpeakHistory_9":
			dialog.text = StringFromKey("Common_Brothel_151");
			link.l1 = StringFromKey("Common_Brothel_152");
			link.l1.go = "exit";
		break;
		case "SpeakHistory_10":
			dialog.text = StringFromKey("Common_Brothel_153");
			link.l1 = StringFromKey("Common_Brothel_154");
			link.l1.go = "exit";
			pchar.questTemp.different.HostessSex = "toRoom";
			pchar.questTemp.different.HostessSex.city = npchar.city;
			AddDialogExitQuestFunction("SexWithHostess_goToRoom");
			pchar.quest.SmallQuests_free.over = "yes";
			SetTimerFunction("SexWithHostess_null", 0, 0, 1); //возврат хозяйки на место, если ГГ не прийдет в комнату
		break;

		case "Hostess_inSexRoom":
			dialog.text = StringFromKey("Common_Brothel_155");
			link.l1 = StringFromKey("Common_Brothel_156");
			link.l1.go = "exit";
			pchar.quest.SexWithHostess_null.over = "yes"; //нулим таймер на не пришёл
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("SexWithHostess_fack");

			//pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1;
			Achievment_SetStat(ACH_Tsenitel_prekrasnogo, 1);

			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Fencing", -50);
			AddCharacterExpToSkill(pchar, "Pistol", -50);
			AddCharacterHealth(pchar, 10);
		break;

		case "SpeakHistoryTwo":
			dialog.text = StringFromKey("Common_Brothel_157");
			link.l1 = StringFromKey("Common_Brothel_158");
			link.l1.go = "SpeakHistoryTwo_1";
		break;
		case "SpeakHistoryTwo_1":
			dialog.text = StringFromKey("Common_Brothel_159");
			link.l1 = StringFromKey("Common_Brothel_160");
			link.l1.go = "SpeakHistoryTwo_2";
			link.l2 = StringFromKey("Common_Brothel_161");
			link.l2.go = "SpeakHistoryTwo_3";
		break;
		case "SpeakHistoryTwo_2":
			dialog.text = StringFromKey("Common_Brothel_162");
			link.l1 = StringFromKey("Common_Brothel_163");
			link.l1.go = "exit";
		break;
		case "SpeakHistoryTwo_3":
			dialog.text = StringFromKey("Common_Brothel_164");
			link.l1 = StringFromKey("Common_Brothel_165");
			link.l1.go = "SpeakHistoryTwo_4";
		break;
		case "SpeakHistoryTwo_4":
			dialog.text = StringFromKey("Common_Brothel_166");
			link.l1 = StringFromKey("Common_Brothel_167");
			link.l1.go = "SpeakHistoryTwo_5";
		break;
		case "SpeakHistoryTwo_5":
			dialog.text = StringFromKey("Common_Brothel_168");
			link.l1 = StringFromKey("Common_Brothel_169");
			link.l1.go = "SpeakHistoryTwo_6";
			link.l2 = StringFromKey("Common_Brothel_170");
			link.l2.go = "SpeakHistoryTwo_7";
		break;
		case "SpeakHistoryTwo_6":
			dialog.text = StringFromKey("Common_Brothel_171");
			link.l1 = StringFromKey("Common_Brothel_172");
			link.l1.go = "exit";
		break;
		case "SpeakHistoryTwo_7":
			dialog.text = StringFromKey("Common_Brothel_173");
			link.l1 = StringFromKey("Common_Brothel_174");
			link.l1.go = "SpeakHistoryTwo_8";
		break;
		case "SpeakHistoryTwo_8":
			dialog.text = StringFromKey("Common_Brothel_175");
			link.l1 = StringFromKey("Common_Brothel_176");
			link.l1.go = "SpeakHistoryTwo_9";
		break;
		case "SpeakHistoryTwo_9":
			dialog.text = StringFromKey("Common_Brothel_177");
			link.l1 = StringFromKey("Common_Brothel_178");
			link.l1.go = "SpeakHistoryTwo_10";
			link.l2 = StringFromKey("Common_Brothel_179");
			link.l2.go = "SpeakHistoryTwo_15";
		break;
		case "SpeakHistoryTwo_10":
			dialog.text = StringFromKey("Common_Brothel_180");
			link.l1 = StringFromKey("Common_Brothel_181");
			link.l1.go = "SpeakHistoryTwo_11";
		break;
		case "SpeakHistoryTwo_11":
			dialog.text = StringFromKey("Common_Brothel_182");
			link.l1 = StringFromKey("Common_Brothel_183");
			link.l1.go = "SpeakHistoryTwo_12";
		break;
		case "SpeakHistoryTwo_12":
			dialog.text = StringFromKey("Common_Brothel_184");
			link.l1 = StringFromKey("Common_Brothel_185");
			link.l1.go = "SpeakHistoryTwo_13";
		break;
		case "SpeakHistoryTwo_13":
			dialog.text = StringFromKey("Common_Brothel_186");
			link.l1 = StringFromKey("Common_Brothel_187");
			link.l1.go = "SpeakHistoryTwo_14";
		break;
		case "SpeakHistoryTwo_14":
			dialog.text = StringFromKey("Common_Brothel_188");
			link.l1 = StringFromKey("Common_Brothel_189");
			link.l1.go = "exit";
			pchar.questTemp.different.HostessSex = "toRoom";
			pchar.questTemp.different.HostessSex.city = npchar.city;
			AddDialogExitQuestFunction("SexWithHostess_goToRoom");
			pchar.quest.SmallQuests_free.over = "yes";
			SetTimerFunction("SexWithHostess_null", 0, 0, 1); //возврат хозяйки на место, если ГГ не прийдет в комнату
		break;

		case "SpeakHistoryTwo_15":
			dialog.text = StringFromKey("Common_Brothel_190");
			link.l1 = StringFromKey("Common_Brothel_191");
			link.l1.go = "SpeakHistoryTwo_16";
		break;
		case "SpeakHistoryTwo_16":
			dialog.text = StringFromKey("Common_Brothel_192");
			link.l1 = StringFromKey("Common_Brothel_193", npchar.name);
			link.l1.go = "exit";
		break;
		// ================================== рядовой состав =======================================
		case "Horse_talk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,
						StringFromKey("Common_Brothel_197", LinkRandPhrase(
								StringFromKey("Common_Brothel_194"),
								StringFromKey("Common_Brothel_195"),
								StringFromKey("Common_Brothel_196"))),
						StringFromKey("Common_Brothel_201", LinkRandPhrase(
								StringFromKey("Common_Brothel_198"),
								StringFromKey("Common_Brothel_199", pchar),
								StringFromKey("Common_Brothel_200", pchar))));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("Common_Brothel_204", RandPhraseSimple(
								StringFromKey("Common_Brothel_202"),
								StringFromKey("Common_Brothel_203"))),
						StringFromKey("Common_Brothel_207", RandPhraseSimple(
								StringFromKey("Common_Brothel_205"),
								StringFromKey("Common_Brothel_206"))));
				link.l1.go = "exit";
				break;
			}
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Common_Brothel_208", pchar, GetAddress_Form(NPChar)),
						StringFromKey("Common_Brothel_209"),
						StringFromKey("Common_Brothel_210", pchar, GetAddress_Form(NPChar)),
						StringFromKey("Common_Brothel_211", pchar, GetAddress_Form(NPChar)), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Common_Brothel_212", pchar),
						StringFromKey("Common_Brothel_213"),
						StringFromKey("Common_Brothel_214", pchar),
						StringFromKey("Common_Brothel_215", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			Link.l2 = StringFromKey("Common_Brothel_216");
			Link.l2.go = "Horse_1";
			Link.l3 = StringFromKey("Common_Brothel_220", LinkRandPhrase(
						StringFromKey("Common_Brothel_217", pchar),
						StringFromKey("Common_Brothel_218", pchar),
						StringFromKey("Common_Brothel_219", pchar)));
			if (!CheckAttribute(npchar, "quest.choice"))
			{
				Link.l3.go = "Horse_2";
			}
			else
			{
				Link.l3.go = "HorseChoice_" + npchar.quest.choice;
			}
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = StringFromKey("Common_Brothel_224", LinkRandPhrase(
							StringFromKey("Common_Brothel_221", pchar),
							StringFromKey("Common_Brothel_222"),
							StringFromKey("Common_Brothel_223", pchar)));
				link.l5.go = "TakeMayorsRing_S1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
			//--> Голл. линейка, квест №8. базар с девокой о Библиии.
			if (pchar.questTemp.State == "SeekBible_toFFBrothel" || pchar.questTemp.State == "SeekBible_toGirl")
			{
				if (npchar.id == "HorseGen_" + FindLocation("FortFrance_Brothel") + "_1")
				{
					if (!CheckAttribute(npchar, "quest.HolLineTalk"))
					{
						dialog.text = StringFromKey("Common_Brothel_225", pchar);
						link.l4 = StringFromKey("Common_Brothel_226");
						link.l4.go = "Step_Hol8_1";
					}
					else
					{
						dialog.text = StringFromKey("Common_Brothel_227", pchar);
						link.l4 = StringFromKey("Common_Brothel_228");
						link.l4.go = "Step_Hol8_5";
						AddMoneyToCharacter(pchar, -1000);
					}
				}
			}
			//<-- Голл. линейка, квест №8. базар с девокой о Библиии.
			NextDiag.TempNode = "Horse_talk";
		break;
		case "Horse_1":
			dialog.text = StringFromKey("Common_Brothel_229", characters[GetCharacterIndex(npchar.city + "_Hostess")].name);
			Link.l1 = StringFromKey("Common_Brothel_230", pchar);
			Link.l1.go = "exit";
		break;
		case "Horse_2":
			if (rand(1))
			{
				dialog.text = StringFromKey("Common_Brothel_234", LinkRandPhrase(
							StringFromKey("Common_Brothel_231"),
							StringFromKey("Common_Brothel_232", pchar),
							StringFromKey("Common_Brothel_233", pchar)));
				link.l1 = StringFromKey("Common_Brothel_235");
				Link.l1.go = "Horse_3";
				Link.l2 = StringFromKey("Common_Brothel_236", pchar);
				Link.l2.go = "exit";
				npchar.quest.choice = 0; //был базар, но ГГ потом отказался
			}
			else
			{
				dialog.text = StringFromKey("Common_Brothel_240", LinkRandPhrase(
							StringFromKey("Common_Brothel_237", pchar),
							StringFromKey("Common_Brothel_238", pchar),
							StringFromKey("Common_Brothel_239", pchar)));
				link.l1 = StringFromKey("Common_Brothel_241");
				Link.l1.go = "exit";
				npchar.quest.choice = 2; //ГГ послали
			}
		break;
		case "Horse_3":
			dialog.text = StringFromKey("Common_Brothel_242", pchar, characters[GetCharacterIndex(npchar.city + "_Hostess")].name, npchar.name);
			Link.l1 = StringFromKey("Common_Brothel_243");
			Link.l1.go = "exit";
			npchar.quest.choice = 1; //она согласная
			SetNPCQuestDate(npchar, "quest.choice");
		break;
		case "Horse_4":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Common_Brothel_244", pchar),
						StringFromKey("Common_Brothel_245"),
						StringFromKey("Common_Brothel_246"),
						StringFromKey("Common_Brothel_247"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Common_Brothel_248"),
						StringFromKey("Common_Brothel_249"),
						StringFromKey("Common_Brothel_250"),
						StringFromKey("Common_Brothel_251"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "Horse_4";
		break;
		//===>> реакция на попытки пофлиртовыть, если флирт уже был
		case "HorseChoice_0":
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("Common_Brothel_252", pchar),
							StringFromKey("Common_Brothel_253"),
							StringFromKey("Common_Brothel_254"),
							StringFromKey("Common_Brothel_255", pchar), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("Common_Brothel_256"),
							StringFromKey("Common_Brothel_257"),
							StringFromKey("Common_Brothel_258", pchar),
							StringFromKey("Common_Brothel_259"), npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Common_Brothel_260");
				Link.l1 = StringFromKey("Common_Brothel_261");
				Link.l1.go = "exit";
			}
		break;
		case "HorseChoice_1":
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				if (!CheckNPCQuestDate(npchar, "quest.choice"))
				{
					dialog.text = NPCStringReactionRepeat(
								StringFromKey("Common_Brothel_262", pchar),
								StringFromKey("Common_Brothel_263", pchar),
								StringFromKey("Common_Brothel_264"),
								StringFromKey("Common_Brothel_265"), "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(
								StringFromKey("Common_Brothel_266"),
								StringFromKey("Common_Brothel_267"),
								StringFromKey("Common_Brothel_268"),
								StringFromKey("Common_Brothel_269"), npchar, Dialog.CurrentNode);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("Common_Brothel_270", pchar);
					Link.l1 = StringFromKey("Common_Brothel_271");
					Link.l1.go = "exit";
					npchar.quest.choice = 0; //был базар, но ГГ потом отказался
				}
			}
			else
			{
				dialog.text = StringFromKey("Common_Brothel_272", pchar);
				Link.l1 = StringFromKey("Common_Brothel_273", pchar);
				Link.l1.go = "exit";
				Link.l2 = StringFromKey("Common_Brothel_274");
				Link.l2.go = "HorseChoice_1_Add";
			}
		break;
		case "HorseChoice_2":
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("Common_Brothel_275", pchar),
							StringFromKey("Common_Brothel_276", pchar),
							StringFromKey("Common_Brothel_277"),
							StringFromKey("Common_Brothel_278", pchar), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("Common_Brothel_279", pchar),
							StringFromKey("Common_Brothel_280"),
							StringFromKey("Common_Brothel_281"),
							StringFromKey("Common_Brothel_282", pchar), npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Common_Brothel_283", pchar);
				Link.l1 = StringFromKey("Common_Brothel_284");
				Link.l1.go = "exit";
			}
		break;
		case "HorseChoice_1_Add":
			dialog.text = StringFromKey("Common_Brothel_285");
			Link.l1 = StringFromKey("Common_Brothel_286");
			Link.l1.go = "exit";
			npchar.quest.choice = 0;
		break;
		//===>> секс
		case "Horse_ReadyFack":
			if (!CheckAttribute(npchar, "quest.choice")) npchar.quest.choice = 0;
			switch (npchar.quest.choice)
			{
				case "0":
					dialog.text = StringFromKey("Common_Brothel_289", RandPhraseSimple(
								StringFromKey("Common_Brothel_287", pchar),
								StringFromKey("Common_Brothel_288", pchar)));
					Link.l1 = StringFromKey("Common_Brothel_292", RandPhraseSimple(
								StringFromKey("Common_Brothel_290"),
								StringFromKey("Common_Brothel_291", pchar)));
				break;
				case "1":
					dialog.text = StringFromKey("Common_Brothel_293", pchar);
					Link.l1 = StringFromKey("Common_Brothel_294");
				break;
				case "2":
					dialog.text = StringFromKey("Common_Brothel_295", pchar);
					Link.l1 = StringFromKey("Common_Brothel_296", pchar);
				break;
			}
			Link.l1.go = "exit";
			//--> кол-во посещений
			if (!CheckAttribute(npchar, "quest.sexHappend")) npchar.quest.sexHappend = 1;
			else npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			Achievment_SetStat(ACH_Tsenitel_prekrasnogo, 1);
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
			NextDiag.TempNode = "Horse_AfterSex";
			AddDialogExitQuest("PlaySex_1");

			/// кач от борделя
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// изменение статусов
			ChangeCharacterReputation(pchar, -1);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Fencing", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;

		case "Horse_AfterSex":
			if (CheckAttribute(pchar, "questTemp.ReasonToFast") && pchar.questTemp.ReasonToFast == "Begin")
			{
				dialog.text = StringFromKey("Common_Brothel_297", pchar);
				link.l1 = StringFromKey("Common_Brothel_303", LinkRandPhrase(
							StringFromKey("Common_Brothel_298", pchar),
							StringFromKey("Common_Brothel_299"),
							StringFromKey("Common_Brothel_302", RandPhraseSimple(
									StringFromKey("Common_Brothel_300"),
									StringFromKey("Common_Brothel_301", pchar)))));
				link.l1.go = "exit";
				link.l2 = StringFromKey("Common_Brothel_304", pchar);
				link.l2.go = "Horse_ReasonToFast_1";
			}
			else
			{
				switch (npchar.quest.choice)
				{
					case "0":
						dialog.text = StringFromKey("Common_Brothel_308", LinkRandPhrase(
									StringFromKey("Common_Brothel_305"),
									StringFromKey("Common_Brothel_306"),
									StringFromKey("Common_Brothel_307", pchar)));
						Link.l1 = StringFromKey("Common_Brothel_311", RandPhraseSimple(
									StringFromKey("Common_Brothel_309", pchar),
									StringFromKey("Common_Brothel_310", pchar)));
						Link.l1.go = "exit";
					break;
					case "1":
						if (sti(npchar.quest.sexHappend) > (rand(4) + 5) && sti(pchar.questTemp.HorseLoot) < 3 && !CheckAttribute(npchar, "questTemp.HorseLoot"))
						{
							dialog.text = StringFromKey("Common_Brothel_312");
							Link.l1 = StringFromKey("Common_Brothel_313");
							Link.l1.go = "HorseQuest";
						}
						else
						{
							dialog.text = StringFromKey("Common_Brothel_317", LinkRandPhrase(
										StringFromKey("Common_Brothel_314"),
										StringFromKey("Common_Brothel_315", pchar),
										StringFromKey("Common_Brothel_316", pchar)));
							Link.l1 = StringFromKey("Common_Brothel_320", RandPhraseSimple(
										StringFromKey("Common_Brothel_318"),
										StringFromKey("Common_Brothel_319", pchar)));
							Link.l1.go = "exit";
						}
					break;
					case "2":
						dialog.text = StringFromKey("Common_Brothel_323", RandPhraseSimple(
									StringFromKey("Common_Brothel_321"),
									StringFromKey("Common_Brothel_322", pchar)));
						Link.l1 = StringFromKey("Common_Brothel_326", RandPhraseSimple(
									StringFromKey("Common_Brothel_324"),
									StringFromKey("Common_Brothel_325")));
						Link.l1.go = "exit";
					break;
				}
				NextDiag.TempNode = "Horse_AfterSex_2";
			}
		break;
		case "Horse_AfterSex_2":
			if (CheckAttribute(pchar, "GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "Bag_BrothelRoom" && !CheckCharacterItem(pchar, "leather_bag"))
			{
				dialog.text = StringFromKey("Common_Brothel_327");
				link.l1 = StringFromKey("Common_Brothel_328");
				link.l1.go = "EncGirl_GetBag";
			}
			else
			{
				dialog.text = StringFromKey("Common_Brothel_332", LinkRandPhrase(
							StringFromKey("Common_Brothel_329"),
							StringFromKey("Common_Brothel_330"),
							StringFromKey("Common_Brothel_331")));
				Link.l1 = StringFromKey("Common_Brothel_333");
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex_2";
			}
		break;

		case "EncGirl_GetBag":
			dialog.text = StringFromKey("Common_Brothel_334");
			link.l1 = StringFromKey("Common_Brothel_335");
			link.l1.go = "EncGirl_GetBag1";
		break;

		case "EncGirl_GetBag1":
			dialog.text = StringFromKey("Common_Brothel_336");
			link.l1 = StringFromKey("Common_Brothel_337");
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "Bag_BrothelHostess";
			NextDiag.TempNode = "Horse_AfterSex_2";
		break;
		//==> квест на лут
		case "HorseQuest":
			pchar.questTemp.HorseLoot = sti(pchar.questTemp.HorseLoot) + 1;
			npchar.questTemp.HorseLoot = true; //уже давала
			dialog.text = StringFromKey("Common_Brothel_338");
			Link.l1 = StringFromKey("Common_Brothel_339", pchar);
			Link.l1.go = "HorseQuest_1";
		break;
		case "HorseQuest_1":
			dialog.text = StringFromKey("Common_Brothel_340");
			Link.l1 = StringFromKey("Common_Brothel_341");
			Link.l1.go = "HorseQuest_2";
		break;
		case "HorseQuest_2":
			dialog.text = StringFromKey("Common_Brothel_342");
			Link.l1 = StringFromKey("Common_Brothel_343");
			Link.l1.go = "HorseQuest_3";
		break;
		case "HorseQuest_3":
			sTemp = LinkRandPhrase("Shore55", "Shore9", "Shore_ship2");
			if (sTemp == "Shore55")
			{
				str = StringFromKey("Common_Brothel_344");
				str1 = "box" + (rand(1) + 1);
			}
			if (sTemp == "Shore9")
			{
				str = StringFromKey("Common_Brothel_345");
				str1 = "box1";
			}
			if (sTemp == "Shore_ship2")
			{
				str = StringFromKey("Common_Brothel_346");
				str1 = "box2";
			}
			pchar.GenQuestBox.(sTemp) = true;
			switch (pchar.questTemp.HorseLoot)
			{
				case "1":
					pchar.GenQuestBox.(sTemp).(str1).items.spyglass2 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry1 = 4;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry5 = 6;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry10 = 2;
					pchar.GenQuestBox.(sTemp).(str1).items.indian11 = 1;
					pchar.GenQuestBox.(sTemp).(str1).money = 15000;
				break;
				case "2":
					pchar.GenQuestBox.(sTemp).(str1).items.spyglass3 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry14 = 3;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry16 = 2;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry18 = 4;
					pchar.GenQuestBox.(sTemp).(str1).items.indian17 = 1;
					pchar.GenQuestBox.(sTemp).(str1).money = 19000;
				break;
				case "3":
					pchar.GenQuestBox.(sTemp).(str1).items.indian20 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.indian5 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.indian10 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.spyglass4 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.indian19 = 1;
					pchar.GenQuestBox.(sTemp).(str1).money = 24000;
				break;
			}
			dialog.text = StringFromKey("Common_Brothel_347", str);
			Link.l1 = StringFromKey("Common_Brothel_348");
			Link.l1.go = "exit";
		break;

		// --> генератор - "Повод для спешки"
		case "Horse_ReasonToFast_1":
			dialog.text = StringFromKey("Common_Brothel_349", pchar);
			link.l1 = StringFromKey("Common_Brothel_350");
			link.l1.go = "Horse_ReasonToFast_2";
		break;

		case "Horse_ReasonToFast_2":
			pchar.questTemp.ReasonToFast.speakHorse = true;
			dialog.text = StringFromKey("Common_Brothel_351");
			link.l1 = StringFromKey("Common_Brothel_352", pchar);
			link.l1.go = "Horse_ReasonToFast_3";
		break;

		case "Horse_ReasonToFast_3":
			NextDiag.TempNode = "Horse_AfterSex_2";
			ReOpenQuestHeader("ReasonToFast");
			AddQuestRecord("ReasonToFast", "1");
			pchar.questTemp.ReasonToFast = "SpeakHorse";
			pchar.questTemp.ReasonToFast.GuardNation = npchar.nation;
			pchar.questTemp.ReasonToFast.cantSpeakOther = true;
			ReasonToFast_InitVariables();
			string TargetLocation = SelectQuestShoreLocation();
			if (TargetLocation != "")
			{
				locations[FindLocation(TargetLocation)].DisableEncounters = true;
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1 = "location";
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1.location = TargetLocation;
				pchar.quest.ReasonToFast_MeetPatrol.function = "ReasonToFast_MeetPatrolShore";
				pchar.questTemp.ReasonToFast.PatrolLocation = TargetLocation;
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// <-- генератор "Повод для спешки"

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//поиски кольца мэра
		case "TakeMayorsRing_S1":
			if (CheckAttribute(pchar, "questTemp.different.TakeMayorsRing.item")) //если валяется в итемах
			{
				dialog.text = StringFromKey("Common_Brothel_356", LinkRandPhrase(
							StringFromKey("Common_Brothel_353"),
							StringFromKey("Common_Brothel_354", pchar),
							StringFromKey("Common_Brothel_355")));
				link.l1 = StringFromKey("Common_Brothel_357");
				link.l1.go = "exit";
			}
			else
			{
				if (npchar.id == "HorseGen_" + reload_location_index + "_1")
				{
					dialog.text = StringFromKey("Common_Brothel_358");
					link.l1 = StringFromKey("Common_Brothel_359");
					link.l1.go = "TakeMayorsRing_S2";
				}
				else
				{
					dialog.text = StringFromKey("Common_Brothel_363", LinkRandPhrase(
								StringFromKey("Common_Brothel_360"),
								StringFromKey("Common_Brothel_361", pchar),
								StringFromKey("Common_Brothel_362")));
					link.l1 = StringFromKey("Common_Brothel_364");
					link.l1.go = "exit";
				}
			}
		break;

		case "TakeMayorsRing_S2":
			dialog.text = StringFromKey("Common_Brothel_365");
			link.l1 = StringFromKey("Common_Brothel_366");
			link.l1.go = "TakeMayorsRing_S3";
		break;
		case "TakeMayorsRing_S3":
			dialog.text = StringFromKey("Common_Brothel_367");
			link.l1 = StringFromKey("Common_Brothel_368");
			link.l1.go = "TakeMayorsRing_S4";
		break;
		case "TakeMayorsRing_S4":
			dialog.text = StringFromKey("Common_Brothel_369");
			link.l1 = StringFromKey("Common_Brothel_370");
			link.l1.go = "TakeMayorsRing_S5";
		break;
		case "TakeMayorsRing_S5":
			if (rand(1) && sti(pchar.money) > 5000)
			{
				dialog.text = StringFromKey("Common_Brothel_371");
				link.l1 = StringFromKey("Common_Brothel_372");
				link.l1.go = "TakeMayorsRing_S6";
			}
			else
			{
				dialog.text = StringFromKey("Common_Brothel_373");
				link.l1 = StringFromKey("Common_Brothel_374");
				link.l1.go = "exit";
				GiveItem2Character(pchar, "MayorsRing");
				pchar.questTemp.different.TakeMayorsRing = "HorseTakenRing";
				AddQuestRecord("SeekMayorsRing", "3");
				AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
				AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
			}
		break;
		case "TakeMayorsRing_S6":
			dialog.text = StringFromKey("Common_Brothel_375");
			link.l1 = StringFromKey("Common_Brothel_376");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -5000);
			GiveItem2Character(pchar, "MayorsRing");
			pchar.questTemp.different.TakeMayorsRing = "HorseTakenRingMoney";
			AddQuestRecord("SeekMayorsRing", "2");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
		break;

		//********************************* Диалоги девки из борделя ФФ **********************************
		case "Step_Hol8_1":
			dialog.text = StringFromKey("Common_Brothel_377");
			link.l1 = StringFromKey("Common_Brothel_378", pchar);
			link.l1.go = "Step_Hol8_2";
		break;
		case "Step_Hol8_2":
			dialog.text = StringFromKey("Common_Brothel_379", pchar);
			link.l1 = StringFromKey("Common_Brothel_380", pchar);
			link.l1.go = "Step_Hol8_3";
		break;
		case "Step_Hol8_3":
			dialog.text = StringFromKey("Common_Brothel_381", pchar);
			link.l1 = StringFromKey("Common_Brothel_382", pchar);
			link.l1.go = "Step_Hol8_4";
		break;
		case "Step_Hol8_4":
			dialog.text = StringFromKey("Common_Brothel_383", pchar);
			if (sti(pchar.money) >= 1000)
			{
				link.l1 = StringFromKey("Common_Brothel_384");
				link.l1.go = "Step_Hol8_5";
				AddMoneyToCharacter(pchar, -1000);
			}
			else
			{
				link.l1 = StringFromKey("Common_Brothel_385", pchar);
				link.l1.go = "exit";
				npchar.quest.HolLineTalk = true;
			}
			NextDiag.TempNode = "Horse_talk";
		break;
		case "Step_Hol8_5":
			dialog.text = StringFromKey("Common_Brothel_386");
			link.l1 = StringFromKey("Common_Brothel_387");
			link.l1.go = "Step_Hol8_6";
		break;
		case "Step_Hol8_6":
			dialog.text = StringFromKey("Common_Brothel_388");
			link.l1 = StringFromKey("Common_Brothel_389", pchar);
			link.l1.go = "Step_Hol8_7";
		break;
		case "Step_Hol8_7":
			dialog.text = StringFromKey("Common_Brothel_390");
			link.l1 = StringFromKey("Common_Brothel_391");
			link.l1.go = "Step_Hol8_8";
		break;
		case "Step_Hol8_8":
			dialog.text = StringFromKey("Common_Brothel_392");
			link.l1 = StringFromKey("Common_Brothel_393");
			link.l1.go = "Step_Hol8_9";
		break;
		case "Step_Hol8_9":
			dialog.text = StringFromKey("Common_Brothel_394");
			link.l1 = StringFromKey("Common_Brothel_395");
			link.l1.go = "exit";
			AddQuestRecord("Hol_Line_8_SeekBible", "4");
			AddQuestUserData("Hol_Line_8_SeekBible", "sSex", GetSexPhrase("", "а"));
			pchar.questTemp.State = "SeekBible_toTavern";
			NextDiag.TempNode = "Horse_talk";
			RemoveLandQuestmark_Main(CharacterFromID("FortFrance_hostess"), "Hol_Line");
			RemoveLandQuestmarkToFantoms_Main("Horse", "Hol_Line");
			AddLandQuestmark_Main(CharacterFromID("Tortuga_tavernkeeper"), "Hol_Line");
		break;

		// общие линки по квестам
		case "quests":
			if (pchar.questTemp.Sharp == "seekSharp" && GetNpcQuestPastDayWOInit(npchar, "quest.SharpTime") > 7 && !LAi_IsDead(&characters[GetCharacterIndex("Sharp")]))
			{
				link.l1 = StringFromKey("Common_Brothel_396", npchar.name);
				link.l1.go = "SharpPearl_1";
				SaveCurrentNpcQuestDateParam(npchar, "quest.SharpTime");
			}
		break;

		// капитан Шарп, грабеж жемчужных промыслов
		case "SharpPearl_1":
			if (drand(1) || bBettaTestMode)
			{
				if (sti(pchar.questTemp.Sharp.brothelChance) < 9)
				{
					//футболим геймера в город
					pchar.questTemp.Sharp.City = GetSharpCity();
					pchar.questTemp.Sharp.City.rumour = true; //флаг дачи слуха
					dialog.text = StringFromKey("Common_Brothel_397", XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc"));
					link.l1 = StringFromKey("Common_Brothel_398", npchar.name);
					link.l1.go = "exit";
					pchar.questTemp.Sharp = "toSharp_going"; //в бордели больше не заходить
					ReOpenQuestHeader("SharpPearl");
					AddQuestRecord("SharpPearl", "1");
					AddQuestUserData("SharpPearl", "sCity", XI_ConvertString("Colony" + npchar.city + "Pre"));
					AddQuestUserData("SharpPearl", "sTarget", XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc"));
					if (GetIslandNameByCity(pchar.questTemp.Sharp.City) != pchar.questTemp.Sharp.City)
					{
						AddQuestUserData("SharpPearl", "sAreal", StringFromKey("InfoMessages_6", XI_ConvertString(GetIslandNameByCity(pchar.questTemp.Sharp.City) + "Pre")));
					}
					//запускаем энкаунтер Шарпа на карте
					group_DeleteGroup("Sharp_Group");
					sld = characterFromId("Sharp");
					sld.DontRansackCaptain = true; //fix
					string sGroup = "Sharp_Group";
					Group_FindOrCreateGroup(sGroup);
					Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
					Group_LockTask(sGroup);
					Group_AddCharacter(sGroup, sld.id);
					Group_SetGroupCommander(sGroup, sld.id);
					sld.mapEnc.type = "trade";
					sld.mapEnc.worldMapShip = "quest_ship";
					sld.mapEnc.Name = FindPersonalName("Sharp_mapEnc");
					string sColony= SelectAnyColony(npchar.city); //колония, откуда плывет Шарп
					int daysQty = GetMaxDaysFromColony2Colony(sColony, pchar.questTemp.Sharp.City) + 3; //дней доехать даем с запасом
					Map_CreateTrader(sColony, pchar.questTemp.Sharp.City, sld.id, daysQty);
					Log_TestInfo("Шарпоносец установлен из " + sColony + "  в " + pchar.questTemp.Sharp.City + "");
				}
				else
				{
					//чудо, Шарп здесь, в борделе!
					dialog.text = StringFromKey("Common_Brothel_399");
					link.l1 = StringFromKey("Common_Brothel_400", npchar.name);
					link.l1.go = "SharpPearl_2";
				}

				if (pchar.questTemp.Sharp.SeekSpy == "begin") // если ищем в первый раз снимем мэйн-метки
				{
					SeaPearl_Hostess_DelQuestMarks();
					AddLandQuestmark_Main(CharacterFromID("Sharp"), "SharpPearl");
					AddLandQuestmarkToFantoms_Main("Citizen", "SharpPearl", "SharpPearl_SeekSharp_Citizen_QuestMarkCondition");
					AddLandQuestmarkToFantoms_Main("Commoner", "SharpPearl", "SharpPearl_SeekSharp_Citizen_QuestMarkCondition");
				}
			}
			else
			{
				dialog.text = StringFromKey("Common_Brothel_401");
				link.l1 = StringFromKey("Common_Brothel_402", npchar.name);
				link.l1.go = "exit";
			}
		break;
		case "SharpPearl_2":
			dialog.text = StringFromKey("Common_Brothel_403");
			link.l1 = StringFromKey("Common_Brothel_404");
			link.l1.go = "SharpPearl_3";
		break;
		case "SharpPearl_3":
			chrDisableReloadToLocation = true;
			pchar.questTemp.Sharp.count = 0; //счетчик нулим для след. раза
			pchar.questTemp.Sharp.price = 5000 + rand(20) * 1000; //цена за наводку
			pchar.questTemp.Sharp.price.evil = rand(1); //добрый или злой, для скидки
			sld = &characters[GetCharacterIndex("Sharp")];
			sld.dialog.currentnode = "BrothelSharp";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

ref GetFreeHorseRef(string City)
{
	ref rCharacter;
	int storeArray[8];
	int howStore = 0;
	for (int n = 0; n < MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City + "_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return &NullCharacter;
	return &characters[storeArray[rand(howStore - 1)]];
}

ref CheckHorsesName(string City, int num)
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[num]);
	for (int n = 0; n < MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City + "_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			sTemp = GetStrSmallRegister(rCharacter.lastname + " " + rCharacter.name);
			if (HasSubStr(sSeeked, sTemp))
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (HasSubStr(sSeeked, sTemp))
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.name);
			if (HasSubStr(sSeeked, sTemp))
				return rCharacter;
		}
	}
	return &NullCharacter;
}

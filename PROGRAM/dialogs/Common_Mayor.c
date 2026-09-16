// boal 25/04/04 общий диалог мэры
#include "DIALOGS\Rumours\Simple_rumors.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref aData;
	aref Link, NextDiag, arName;

	DeleteAttribute(&Dialog, "Links");

	ref FortChref; // фортовый командер
	ref arItem;

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\Mayor\" + NPChar.City + "_Mayor.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	FortChref = GetFortCommander(NPChar.City); // будет или фортовик или сам губернатор

	ref offref;
	int i, cn, iRank, iDay;
	int qty;
	string attrLoc, QuestName, sTemp;
	bool bOk;

	if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 5000 + (rand(10) + 1) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	// генератор ИДХ по кейсу -->
	attrLoc = Dialog.CurrentNode;
	if (HasSubStr(attrLoc, "GetPrisonerIdx_"))
	{
		i = findsubstr(attrLoc, "_", 0);
		pchar.GenQuest.GetPrisonerIdx = strcut(attrLoc, i + 1, strlen(attrLoc) - 1); // индех в конце
		Dialog.CurrentNode = "sell_prisoner_2";
	}
	// генератор ИДХ по кейсу <--
	// подставляем квестовую ноду при захвате города, если она есть
	/*if (LAi_IsCapturedLocation && CheckAttribute(NextDiag, "captureNode"))
	{
		Dialog.CurrentNode = NextDiag.captureNode;
		DeleteAttribute(NextDiag, "captureNode");
	}*/

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		//			AddDialogExitQuest("MainHeroFightModeOff"); // не актуально
		break;

		case "fight":
			Pchar.quest.ArestInResidenceEnd.win_condition.l1 = "ExitFromLocation";
			Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
			Pchar.quest.ArestInResidenceEnd.win_condition = "ArestInResidenceEnd";
			Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			// AlexBlade - Если идет осада FightMod не лочим
			if (!LAi_IsCapturedLocation)
			{
				LAi_LockFightMode(Pchar, true); // ножками путь убегает
			}
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
				LAi_group_Attack(&Characters[i], Pchar);
			}
		break;

		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,
						StringFromKey("Common_Mayor_4", LinkRandPhrase(
								StringFromKey("Common_Mayor_1"),
								StringFromKey("Common_Mayor_2"),
								StringFromKey("Common_Mayor_3", pchar))),
						StringFromKey("Common_Mayor_8", LinkRandPhrase(
								StringFromKey("Common_Mayor_5", pchar),
								StringFromKey("Common_Mayor_6", pchar),
								StringFromKey("Common_Mayor_7", pchar))));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("Common_Mayor_11", RandPhraseSimple(
								StringFromKey("Common_Mayor_9"),
								StringFromKey("Common_Mayor_10"))),
						StringFromKey("Common_Mayor_14", RandPhraseSimple(
								StringFromKey("Common_Mayor_12", GetWorkTypeOfMan(npchar, "")),
								StringFromKey("Common_Mayor_13"))));
				link.l1.go = "fight";
				break;
			}

			if (sti(NPChar.nation) == PIRATE)
			{
				if (CheckAttribute(pchar, "questTemp.Sharp") && StrStartsWith(pchar.questTemp.Sharp, "takeRumour"))
				{
					dialog.text = StringFromKey("Common_Mayor_15");
					link.l1 = StringFromKey("Common_Mayor_16");
					link.l1.go = "quests";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.mushket2x2") && !CheckCharacterItem(pchar, "mushket2x2"))
				{
					dialog.text = StringFromKey("Common_Mayor_17");
					link.l1 = StringFromKey("Common_Mayor_18");
					link.l1.go = "quests";
					break;
				}
				if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.PiratesCity") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
				{
					dialog.text = StringFromKey("Common_Mayor_19");
					link.l1 = StringFromKey("Common_Mayor_20");
					link.l1.go = "quests";
					break;
				}
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && NPChar.city == "LeFransua")
				{
					dialog.text = StringFromKey("Common_Mayor_21");
					link.l1 = StringFromKey("Common_Mayor_22");
					link.l1.go = "quests";
					break;
				}
				else
				{
					dialog.text = StringFromKey("Common_Mayor_23");
					link.l1 = StringFromKey("Common_Mayor_24");
					link.l1.go = "Exit";

					if (CheckAttribute(PChar, "questTemp.pSQ_Bacchus") && CheckAttribute(PChar, "questTemp.pirateStartQuest"))
					{
						if (pchar.questTemp.pSQ_Bacchus == "to_Baron" && npchar.city == pchar.questTemp.pirateStartQuest.City && GetSquadronGoods(pchar, GOOD_SLAVES) >= 200)
						{
							link.l99 = StringFromKey("Common_Mayor_25");
							link.l99.go = "pirateStartQuest_BacchusSlaves";
						}

						if (pchar.questTemp.pSQ_Bacchus == "to_Baron_noTalk" && npchar.city == pchar.questTemp.pirateStartQuest.City && GetSquadronGoods(pchar, GOOD_SLAVES) >= 200)
						{
							link.l99 = StringFromKey("Common_Mayor_26");
							link.l99.go = "pirateStartQuest_BacchusSlaves_NoTalk";
						}
					}

					//if (Pchar.BaseNation == PIRATE) // доступно всем. Konstrush
					//{
					if (!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
					{
						link.l2 = StringFromKey("Common_Mayor_27");
						link.l2.go = "pirateStartQuest";
					}
					else
					{
						if (pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many") && npchar.city == pchar.questTemp.pirateStartQuest.City)
						{
							link.l2 = StringFromKey("Common_Mayor_28", pchar);
							link.l2.go = "pirateStartQuest_many";
						}
						if (pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "pirateStartQuest") > 0 && npchar.city == pchar.questTemp.pirateStartQuest.City)
						{
							link.l2 = StringFromKey("Common_Mayor_29", pchar);
							link.l2.go = "pirateStartQuest_info_1";
						}
						if (pchar.questTemp.pirateStartQuest == "5" && npchar.city == pchar.questTemp.pirateStartQuest.City)
						{
							link.l2 = StringFromKey("Common_Mayor_30");
							link.l2.go = "pirateStartQuest_final";
						}
					}
					//}

					break;
				}
			}
			if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) >= 15)
			{
				dialog.text = StringFromKey("Common_Mayor_31", pchar, GetFullName(pchar));
				if (sti(pchar.Money) >= CharacterHunterRedemp(Pchar, NationShortName(sti(NPChar.nation))))
				{
					link.l1 = StringFromKey("Common_Mayor_32");
					link.l1.go = "arestFree_1";
				}
				link.l2 = StringFromKey("Common_Mayor_33");
				link.l2.go = "arest_1";
				/*if (CheckAttribute(NPChar, "NotHaveFort") && GetCharacterShipClass(PChar) <= 3) // TODO
				{
					link.l3 = "Разногласия? Вы шутите? Это мой город! Ну, или почти мой. Счас будет моим...";
					link.l3.go = "Town_Capture_1";
				} */
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = StringFromKey("Common_Mayor_34");
				link.l1 = StringFromKey("Common_Mayor_35");
				link.l1.go = "fight";
				break;
			}

			if (CheckAttribute(npchar, "Sp5LaVegaAttackDone")) //Капитан Купер
			{
				if (NPChar.quest.meeting == "0")
				{
					dialog.Text = StringFromKey("Common_Mayor_36", TimeGreeting(), GetFullName(NPChar));
					Link.l1 = StringFromKey("Common_Mayor_37", pchar, GetFullName(Pchar));
					Link.l1.go = "exit";
					NPChar.quest.meeting = "1";
				}
				else
				{
					dialog.Text = StringFromKey("Common_Mayor_38", TimeGreeting());
					Link.l1 = StringFromKey("Common_Mayor_39");
					Link.l1.go = "exit";
				}
				break;
			}

			if (npchar.quest.meeting == "0")
			{
				dialog.text = StringFromKey("Common_Mayor_40", GetFullName(npchar), GetCityName(NPChar.city), NationKingsName(npchar), GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Common_Mayor_41", GetFullName(pchar));
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				//ОСАДЫ homo
				if (CheckAttribute(&Colonies[FindColony(npchar.City)], "Siege"))
				{

					makearef(aData, NullCharacter.Siege);

					if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true)
					{
						dialog.text = StringFromKey("Common_Mayor_42");
						link.l1 = StringFromKey("Common_Mayor_43");
						link.l1.go = "exit";

					}
					else
					{
						dialog.text = StringFromKey("Common_Mayor_44", NationNamePeople(sti(aData.nation)));
						link.l1 = StringFromKey("Common_Mayor_45", pchar);
						link.l1.go = "siege_task";
						link.l2 = StringFromKey("Common_Mayor_46");
						link.l2.go = "exit";
					}
				}
				else
				{
					//->
					makearef(aData, NullCharacter.Siege);
					if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
					&& CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true)
					{
						AddMoneyToCharacter(Pchar, (sti(aData.iSquadronPower) * 1500));
						ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
						ChangeCharacterReputation(PChar, 10);
						AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
						AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
						AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
						AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
						//--> слухи
						SiegeRumour(
							StringFromKey("Common_Mayor_47", NationNameSK(sti(aData.nation)), GetAddress_Form(NPChar)), aData.Colony, sti(aData.conation), -1, 15, 3);
						//<-- слухи
						DeleteAttribute(aData, "PlayerHelpMayor");
						DeleteAttribute(aData, "HelpColony");
						dialog.text = StringFromKey("Common_Mayor_48", GetAddress_Form(NPChar), GetFullName(pchar), NationNameSK(sti(aData.nation)), FindMoneyString(sti(aData.iSquadronPower) * 1500));
						link.l1 = StringFromKey("Common_Mayor_49", GetAddress_FormToNPC(NPChar));
						link.l1.go = "exit";
					}
					else
					{
						//--> дача квеста найти кольцо в борделе
						if (rand(1) && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questTakeRing") > 100 && sti(pchar.questTemp.HorseQty) > 5)
						{
							if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga")
							{
								dialog.text = StringFromKey("Common_Mayor_50");
								link.l1 = StringFromKey("Common_Mayor_51");
								link.l1.go = "TakeRing_1";
								SaveCurrentNpcQuestDateParam(npchar, "questTakeRing");
								break;
							}
						}
						//<-- дача квеста найти кольцо в борделе    				
						dialog.text = StringFromKey("Common_Mayor_54", RandPhraseSimple(
									StringFromKey("Common_Mayor_52"),
									StringFromKey("Common_Mayor_53", GetAddress_Form(NPChar))));
						link.l1 = StringFromKey("Common_Mayor_55", NationNameGenitive(sti(NPChar.nation)));
						link.l1.go = "work";

						// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
						if (CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
						{
							link.l11 = StringFromKey("Common_Mayor_56", pchar, XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Gen"), FindPeoplesString(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount), "No"));
							link.l11.go = "PiratesOnUninhabited_1";
						}
						link.l2 = StringFromKey("Common_Mayor_57");
						if (CheckAttribute(pchar, "questTemp.ReasonToFast") && !CheckAttribute(pchar, "questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
						{
							link.l2.go = "ReasonToFast_Mayor1";
						}
						else
						{
							link.l2.go = "quests";   //(перессылка в файл города)
						}
						if (CheckAttribute(pchar, "GenQuest.CaptainComission.variant") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
						{
							if (pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar, "GenQuest.CaptainComission.SpeakMayor"))
							{
								link.l12 = StringFromKey("Common_Mayor_58", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")), pchar.GenQuest.CaptainComission.Name);
								link.l12.go = "CapComission_Mayor1";
							}
							if (CheckAttribute(pchar, "GenQuest.CaptainComission.PrisonFree"))
							{
								link.l12 = StringFromKey("Common_Mayor_59", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")), pchar.GenQuest.CaptainComission.Name);
								link.l12.go = "CapComission_Mayor9";
							}
							if (pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
							{
								link.l12 = StringFromKey("Common_Mayor_60", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")), pchar.GenQuest.CaptainComission.Name);
								link.l12.go = "CapComission_Mayor13";
							}
						}
						if (CheckAttribute(pchar, "GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
						{
							if (!CheckAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor"))
							{
								iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
								if (CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
								{
									link.l13 = StringFromKey("Common_Mayor_61", pchar, XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen"), pchar.GenQuest.ShipWreck.Name, pchar.GenQuest.ShipWreck.BadName, iDay);
									link.l13.go = "ShipWreck1";
								}
								else
								{
									link.l13 = StringFromKey("Common_Mayor_62", pchar, XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen"), pchar.GenQuest.ShipWreck.ShipTypeName, iDay);
									link.l13.go = "ShipWreck1";
								}
							}
						}
						if (GetPrisonerQty() > 0)
						{
							link.l3 = StringFromKey("Common_Mayor_63");
							link.l3.go = "sell_prisoner";
						}
						if (npchar.Default == npchar.location) // если не в тюрьме
						{
							if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
							{
								link.l4 = StringFromKey("Common_Mayor_64");
								link.l4.go = "LoanForAll";//(перессылка в кредитный генератор)
							}
						}
						//-->> сдача найденного в борделе кольца
						if (CheckCharacterItem(pchar, "MayorsRing"))
						{
							if (pchar.questTemp.different.TakeMayorsRing == "toBrothel")
							{
								link.l5 = StringFromKey("Common_Mayor_65");
								link.l5.go = "TakeRing_S1";
							}
							else
							{
								link.l5 = StringFromKey("Common_Mayor_66");
								link.l5.go = "TakeRing_S3";
							}
						}
						//<<-- сдача найденного в борделе кольца

						link.l7 = StringFromKey("Common_Mayor_67", pchar, NationNameGenitive(sti(NPChar.nation)));
						link.l7.go = "Where_guber";
						link.l8 = StringFromKey("Common_Mayor_68");
						link.l8.go = "Play_Game";
						// evganat - энциклопедия
						if (!ENCYCLOPEDIA_DISABLED)
						{
							if (CheckAttribute(npchar, "encyclopedia.tome"))
							{
								link.l9 = StringFromKey("Common_Mayor_69", pchar);
								link.l9.go = "Encyclopedia_Return";
							}
							else
							{
								if (GetMayorDisposition() > 5)
								{
									if (!CheckAttribute(npchar, "encyclopedia"))
									{
										link.l9 = StringFromKey("Common_Mayor_70", pchar);
										link.l9.go = "Encyclopedia_FirstTime";
									}
									else
									{
										link.l9 = StringFromKey("Common_Mayor_71");
										link.l9.go = "Encyclopedia_Check";
									}
								}
							}
						}
						link.l10 = StringFromKey("Common_Mayor_72");
						link.l10.go = "exit";
					}
				}//<-
			}
		break;

		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = StringFromKey("Common_Mayor_73", pchar);
			link.l1 = StringFromKey("Common_Mayor_74");
			link.l1.go = "pirateStartQuest_1";
			link.l2 = StringFromKey("Common_Mayor_75");
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
			pirateStartQuest_Begin_DelQuestMarks();
		break;
		case "pirateStartQuest_1":
			dialog.text = StringFromKey("Common_Mayor_76");
			link.l1 = StringFromKey("Common_Mayor_77", pchar);
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = StringFromKey("Common_Mayor_78");
			link.l1 = StringFromKey("Common_Mayor_79");
			link.l1.go = "pirateStartQuest_3";
			link.l2 = StringFromKey("Common_Mayor_80");
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = StringFromKey("Common_Mayor_81");
			link.l1 = StringFromKey("Common_Mayor_82");
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.BaronId = npchar.id;

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", GetFullName(npchar));

			AddLandQuestMark_Main(CharacterFromID("FortFrance_tavernkeeper"), "pSQ");
		break;
		case "pirateStartQuest_4":
			dialog.text = StringFromKey("Common_Mayor_83");
			link.l1 = StringFromKey("Common_Mayor_84");
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = StringFromKey("Common_Mayor_85");
			link.l1 = StringFromKey("Common_Mayor_86");
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = StringFromKey("Common_Mayor_87");
			link.l1 = StringFromKey("Common_Mayor_88");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
			RemoveLandQuestMark_Main(npchar, "pSQ");
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = StringFromKey("Common_Mayor_89");
			link.l1 = StringFromKey("Common_Mayor_90", pchar);
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "pirateStartQuest");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = StringFromKey("Common_Mayor_91", pchar);
			link.l1 = StringFromKey("Common_Mayor_92");
			if (!CheckAttribute(pchar, "questTemp.pSQ_Bacchus"))
			{
				link.l1.go = "pirateStartQuest_info_3_Bacchus";
			}
			else
			{
				link.l1.go = "pirateStartQuest_info_3";
			}
			link.l2 = StringFromKey("Common_Mayor_93");
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			RemoveLandQuestMark_Main(npchar, "pSQ");
		break;
		case "pirateStartQuest_info_3_Bacchus":
			dialog.text = StringFromKey("Common_Mayor_94");
			link.l1 = StringFromKey("Common_Mayor_95");
			link.l1.go = "pirateStartQuest_info_3_Bacchus_1";

			link.l2 = StringFromKey("Common_Mayor_96");
			link.l2.go = "pirateStartQuest_info_3_Bacchus_2";
		break;
		case "pirateStartQuest_info_3_Bacchus_1":
			dialog.text = StringFromKey("Common_Mayor_97");
			link.l1 = StringFromKey("Common_Mayor_98");
			link.l1.go = "pirateStartQuest_info_3";

			// СЖ запись
			pchar.questTemp.pSQ_Bacchus = "to_Bacchus";
			AddQuestRecord("pSQ_Bacchus", "1");
			AddQuestUserData("pSQ_Bacchus", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ_Bacchus", "sName", GetFullName(npchar));
		break;
		case "pirateStartQuest_info_3_Bacchus_2":
			dialog.text = StringFromKey("Common_Mayor_99");
			link.l1 = StringFromKey("Common_Mayor_100");
			link.l1.go = "pirateStartQuest_info_3";

			pchar.questTemp.pSQ_Bacchus = "over";
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", GetFullName(CharacterFromID(pchar.questTemp.pirateStartQuest.BaronId)));
			RemoveLandQuestMark_Main(npchar, "pSQ");

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = StringFromKey("Common_Mayor_101", pchar);
			link.l1 = StringFromKey("Common_Mayor_102", pchar);
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			AddQuestRecord("pSQ", "10");
			CloseQuestHeader("pSQ");
			RemoveLandQuestMark_Main(npchar, "pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
			Achievment_Set(ACH_Pervye_shagi_k_viselitse);
		break;

		case "pirateStartQuest_BacchusSlaves":
			dialog.text = StringFromKey("Common_Mayor_103");
			link.l1 = StringFromKey("Common_Mayor_104");
			link.l1.go = "exit";

			AddMoneyToCharacter(pchar, 200 * 250);
			RemoveCharacterGoods(pchar, GOOD_SLAVES, 200);

			pchar.questTemp.pSQ_Bacchus = "over";
			pchar.quest.pirateStartQuest_Bahus_Expired.over = "yes";
			AddQuestRecord("pSQ_Bacchus", "3");
			CloseQuestHeader("pSQ_Bacchus");
			RemoveLandQuestMark_Main(npchar, "pSQ_Bacchus");
		break;

		case "pirateStartQuest_BacchusSlaves_NoTalk":
			dialog.text = StringFromKey("Common_Mayor_105");
			link.l1 = StringFromKey("Common_Mayor_106");
			link.l1.go = "pirateStartQuest_BacchusSlaves_NoTalk_0";
		break;

		case "pirateStartQuest_BacchusSlaves_NoTalk_0":
			dialog.text = StringFromKey("Common_Mayor_107");
			link.l1 = StringFromKey("Common_Mayor_108");
			link.l1.go = "pirateStartQuest_BacchusSlaves_NoTalk_1";
		break;

		case "pirateStartQuest_BacchusSlaves_NoTalk_1":
			dialog.text = StringFromKey("Common_Mayor_109");
			link.l1 = StringFromKey("Common_Mayor_110");
			link.l1.go = "exit";

			AddMoneyToCharacter(pchar, 200 * 250);
			RemoveCharacterGoods(pchar, GOOD_SLAVES, 200);

			pchar.questTemp.pSQ_Bacchus = "over";
			pchar.quest.pirateStartQuest_Bahus_Expired.over = "yes";
			AddQuestRecord("pSQ_Bacchus", "3");
			CloseQuestHeader("pSQ_Bacchus");
			RemoveLandQuestMark_Main(npchar, "pSQ_Bacchus");
		break;

		// Warship Генер "Пираты на необитайке"
		case "PiratesOnUninhabited_1":
			offref = CharacterFromID("PirateOnUninhabited_0");
			qty = makeint(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) * (sti(offref.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(offref, "Leadership") * 500 + GetCharacterSkillToOld(PChar, "commerce") * 500) / 20);

			PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates = qty;

			dialog.text = StringFromKey("Common_Mayor_111", FindMoneyString(qty));
			link.l1 = StringFromKey("Common_Mayor_112", pchar);
			link.l1.go = "PiratesOnUninhabited_2";
			link.l2 = StringFromKey("Common_Mayor_113");
			link.l2.go = "exit";
		break;

		case "PiratesOnUninhabited_2":
			offref = CharacterFromID("PirateOnUninhabited_0");

			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates));

			RemovePassenger(PChar, offref);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);

			sTemp = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTemp, "PiratesOnUninhabited", "12");
			AddQuestUserData(sTemp, "sSex", GetSexPhrase("", "а"));
			AddQuestUserData(sTemp, "mayorName", GetFullName(NPChar));
			CloseQuestHeader(sTemp);

			PChar.Quest.PiratesOnUninhabited_OnShore.over = "yes";
			PChar.Quest.PiratesOnUninhabited_OnMayak.over = "yes";

			if (CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
			{
				PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
				PChar.Quest.PiratesOnUninhabited_ShipDeadline.over = "yes";

				PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
				Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
			}

			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");

			DialogExit();
		break;

		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Mayor1":
			dialog.text = StringFromKey("Common_Mayor_114");
			link.l1 = StringFromKey("Common_Mayor_115");
			if (sti(pchar.reputation) < 41)
			{
				link.l1.go = "ReasonToFast_BMayor";
			}
			else
			{
				link.l1.go = "ReasonToFast_GMayor";
			}
			pchar.questTemp.ReasonToFast.SpeakOther = true;
			if (CheckAttribute(pchar, "GenQuest.CannotWait"))    DeleteAttribute(pchar, "GenQuest.CannotWait");
		break;

		case "ReasonToFast_GMayor":
			if (pchar.questTemp.ReasonToFast == "PatrolSuccess_1")
			{
				// evganat - можно вставить отношение сюда
				IncreaseMayorDisposition(4);
				// вилка_А
				dialog.text = StringFromKey("Common_Mayor_116", pchar);
				link.l1 = StringFromKey("Common_Mayor_117", pchar);
				link.l1.go = "ReasonToFast_GMayor_11";
				if (pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if (pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if (pchar.questTemp.ReasonToFast == "PatrolSuccess_2")
			{
				// evganat - можно вставить отношение сюда
				IncreaseMayorDisposition(4);
				// получена карта
				dialog.text = StringFromKey("Common_Mayor_118", pchar);
				link.l2 = StringFromKey("Common_Mayor_119");
				link.l2.go = "ReasonToFast_GMayor_21";
			}
			if (pchar.questTemp.ReasonToFast == "PatrolDied")
			{
				// патруль перебит
				dialog.text = StringFromKey("Common_Mayor_120", pchar);
				link.l3 = StringFromKey("Common_Mayor_121", pchar);
				link.l3.go = "ReasonToFast_GMayor_31";
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}
		break;

		case "ReasonToFast_BMayor":
			if (pchar.questTemp.ReasonToFast == "PatrolSuccess_1")
			{
				dialog.text = StringFromKey("Common_Mayor_122", GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
				link.l1 = StringFromKey("Common_Mayor_123");
				link.l1.go = "ReasonToFast_BMayor_1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				if (pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if (pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if (pchar.questTemp.ReasonToFast == "PatrolSuccess_2")
			{
				// получена карта
				dialog.text = StringFromKey("Common_Mayor_124");
				link.l2 = StringFromKey("Common_Mayor_125");
				link.l2.go = "ReasonToFast_BMayor_1";
				TakeItemFromCharacter(pchar, "mapQuest");
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";
			}
			if (pchar.questTemp.ReasonToFast == "PatrolDied")
			{
				// патруль перебит
				dialog.text = StringFromKey("Common_Mayor_126");
				link.l3 = StringFromKey("Common_Mayor_127");
				link.l3.go = "ReasonToFast_BMayor_1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}
		break;

		case "ReasonToFast_GMayor_11":
			dialog.text = StringFromKey("Common_Mayor_128");
			link.l1 = StringFromKey("Common_Mayor_129");
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterReputation(pchar, 1);
			GiveItem2Character(pchar, "mapQuest");
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";
			ReasonToFast_SetHunterCoastal();
		break;

		case "ReasonToFast_GMayor_21":
			dialog.text = StringFromKey("Common_Mayor_130");
			link.l1 = StringFromKey("Common_Mayor_131");
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterReputation(pchar, 1);
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_GMayor_31":
			dialog.text = StringFromKey("Common_Mayor_132");
			link.l1 = StringFromKey("Common_Mayor_133");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 1);
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar, "ReasonToFast");
		break;

		case "ReasonToFast_BMayor_1":
		// evganat - можно вставить отношение сюда
			IncreaseMayorDisposition(-10);
			dialog.text = StringFromKey("Common_Mayor_134", pchar);
			link.l1 = StringFromKey("Common_Mayor_135");
			link.l1.go = "fight";

			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1 = "EnterToSea";
			pchar.quest.ReasonToFast_ExitFromTown.function = "ReasonToFast_ExitFromTownFight";
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;

		// ------------------------- Повод для спешки -----------------------------

		// --------------------------Операция 'Галеон'-----------------------------
		case "CapComission_Mayor1":
			dialog.text = StringFromKey("Common_Mayor_136");
			link.l1 = StringFromKey("Common_Mayor_137");
			link.l1.go = "CapComission_Mayor2";
		break;

		case "CapComission_Mayor2":
			dialog.text = StringFromKey("Common_Mayor_138");
			link.l1 = StringFromKey("Common_Mayor_139");
			link.l1.go = "CapComission_Mayor3";
		break;

		case "CapComission_Mayor3":
			dialog.text = StringFromKey("Common_Mayor_140", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name"))), pchar.GenQuest.CaptainComission.Name);
			link.l1 = StringFromKey("Common_Mayor_141");
			link.l1.go = "CapComission_Mayor4";
			pchar.GenQuest.CaptainComission.SpeakMayor = true;
		break;

		case "CapComission_Mayor4":
			dialog.text = StringFromKey("Common_Mayor_142", pchar.GenQuest.CaptainComission.Name);
			link.l1 = StringFromKey("Common_Mayor_143");
			link.l1.go = "CapComission_Mayor5";
			link.l2 = StringFromKey("Common_Mayor_144", pchar);
			link.l2.go = "CapComission_Mayor6";
		break;

		case "CapComission_Mayor5":
			AddQuestRecord("CaptainComission2", "49");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			ChangeCharacterReputation(pchar, -2);
			pchar.GenQuest.CaptainComission = "MayorTalkBad";
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;

		case "CapComission_Mayor6":
			dialog.text = StringFromKey("Common_Mayor_145");
			link.l1 = StringFromKey("Common_Mayor_146", pchar.GenQuest.CaptainComission.Name);
			link.l1.go = "CapComission_Mayor7";
		break;

		case "CapComission_Mayor7":
			dialog.text = StringFromKey("Common_Mayor_147");
			link.l1 = StringFromKey("Common_Mayor_148");
			link.l1.go = "CapComission_Mayor8";
		break;

		case "CapComission_Mayor8":
			AddQuestRecord("CaptainComission2", "50");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			OfficersReaction("good");
			pchar.GenQuest.CaptainComission.MayorTalkGood = true;
			pchar.GenQuest.CaptainComission = "MayorTalkGood";
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			SetFunctionTimerConditionParam("CaptainComission_GetSecretTimeIsOut", 0, 0, 2, MakeInt(24 - GetHour()), false);
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;

		case "CapComission_Mayor9":
			dialog.text = StringFromKey("Common_Mayor_149");
			link.l1 = StringFromKey("Common_Mayor_150");
			link.l1.go = "CapComission_Mayor10";
		break;

		case "CapComission_Mayor10":
			dialog.text = StringFromKey("Common_Mayor_151");
			link.l1 = StringFromKey("Common_Mayor_152");
			link.l1.go = "CapComission_Mayor11";
		break;

		case "CapComission_Mayor11":
		// evganat - можно вставить отношение сюда
			IncreaseMayorDisposition(-5);
			dialog.text = StringFromKey("Common_Mayor_153", GetFullName(pchar));
			link.l1 = StringFromKey("Common_Mayor_154");
			link.l1.go = "CapComission_Mayor12";
		break;

		case "CapComission_Mayor12":
			sld = CharacterFromID("CapComission_1");
			sld.lifeDay = 0;
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_DeletePrisonGroup.win_condition = "CaptainComission_DeletePrisonGroup";
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterReputation(pchar, -4);
			AddQuestRecord("CaptainComission2", "23");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DeleteAttribute(pchar, "TownEscape");
			DialogExit();
		break;

		case "CapComission_Mayor13":
			pchar.quest.CaptainComission_SpeakMayorGoods.over = "yes";
			dialog.text = StringFromKey("Common_Mayor_155");
			link.l1 = StringFromKey("Common_Mayor_162", RandPhraseSimple(
						StringFromKey("Common_Mayor_158", RandPhraseSimple(
								StringFromKey("Common_Mayor_156"),
								StringFromKey("Common_Mayor_157"))),
						StringFromKey("Common_Mayor_161", RandPhraseSimple(
								StringFromKey("Common_Mayor_159"),
								StringFromKey("Common_Mayor_160")))), XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen"));
			link.l1.go = "CapComission_Mayor14";
		break;

		case "CapComission_Mayor14":
			dialog.text = StringFromKey("Common_Mayor_163", pchar.GenQuest.CaptainComission.Name);
			link.l1 = StringFromKey("Common_Mayor_164");
			link.l1.go = "CapComission_Mayor15";
		break;

		case "CapComission_Mayor15":
		// evganat - можно вставить отношение сюда
			IncreaseMayorDisposition(5);
			dialog.text = StringFromKey("Common_Mayor_165", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("Common_Mayor_166", pchar);
			link.l1.go = "CapComission_Mayor16";
		break;

		case "CapComission_Mayor16":
			AddQuestRecord("CaptainComission2", "30");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			CloseQuestHeader("CaptainComission2");
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			// evganat - энциклопедия
			if (CheckRandomPage("questcaptain", "comission", 5))
			{
				GetPage(GetRandomTome(), 5);
			}
			ChangeCharacterReputation(pchar, 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			OfficersReaction("good");
			DeleteAttribute(pchar, "GenQuest.CaptainComission.MayorTalkGood");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		// --------------------------Операция 'Галеон'-----------------------------

		// -------------------------- Генератор "Кораблекрушенцы" ------------
		case "ShipWreck1":
			if (iDay > 15)
			{
				dialog.text = StringFromKey("Common_Mayor_169", RandPhraseSimple(
							StringFromKey("Common_Mayor_167"),
							StringFromKey("Common_Mayor_168", GetFullName(pchar))));
				link.l1 = StringFromKey("Common_Mayor_170");
				link.l1.go = "ShipWreck2";
			}
			else
			{
				dialog.text = StringFromKey("Common_Mayor_171", pchar.GenQuest.ShipWreck.Name);
				link.l1 = StringFromKey("Common_Mayor_172", pchar);
				link.l1.go = "ShipWreck3";
			}
			pchar.GenQuest.ShipWreck.SpeakMayor = true;
			pchar.quest.ShipWreck_MeetInShore.over = "yes";
		break;

		case "ShipWreck2":
		// evganat - можно вставить отношение сюда
			IncreaseMayorDisposition(-10);
			dialog.text = StringFromKey("Common_Mayor_173");
			link.l1 = StringFromKey("Common_Mayor_174", pchar);
			link.l1.go = "ShipWreck4";
		break;

		case "ShipWreck3":
			addMoneyToCharacter(pchar, sti(pchar.rank) * 300 + 3000 + rand(3000));
			ChangeCharacterReputation(pchar, 2);
			AddQuestRecord("ShipWrecked", "14");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString(NPChar.city + "Gen"));
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen"));
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;

		case "ShipWreck4":
			ChangeCharacterReputation(pchar, -5);
			AddQuestRecord("ShipWrecked", "13");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString(NPChar.city + "Gen"));
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen"));
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;
		// -------------------------- Генератор "Кораблекрушенцы" ------------

		// ---------------------- найти кольцо в борделе ----------------------------
		case "TakeRing_1":
			dialog.text = StringFromKey("Common_Mayor_175", pchar);
			link.l1 = StringFromKey("Common_Mayor_176");
			link.l1.go = "TakeRing_2";
		break;
		case "TakeRing_2":
			dialog.text = StringFromKey("Common_Mayor_177");
			link.l1 = StringFromKey("Common_Mayor_178");
			link.l1.go = "TakeRing_3";
		break;
		case "TakeRing_3":
			dialog.text = StringFromKey("Common_Mayor_179");
			link.l1 = StringFromKey("Common_Mayor_180");
			link.l1.go = "TakeRing_4";
		break;
		case "TakeRing_4":
			dialog.text = StringFromKey("Common_Mayor_181");
			link.l1 = StringFromKey("Common_Mayor_182");
			link.l1.go = "TakeRing_5";
			link.l2 = StringFromKey("Common_Mayor_183", GetAddress_FormToNPC(NPChar));
			link.l2.go = "TakeRing_6";
		break;
		case "TakeRing_5":
			dialog.text = StringFromKey("Common_Mayor_184");
			link.l1 = StringFromKey("Common_Mayor_185");
			link.l1.go = "exit";
			pchar.questTemp.different = "TakeMayorsRing";
			pchar.questTemp.different.TakeMayorsRing = "toBrothel";
			pchar.questTemp.different.TakeMayorsRing.Id = GetFullName(npchar);
			pchar.questTemp.different.TakeMayorsRing.city = npchar.city;
			pchar.questTemp.different.TakeMayorsRing.price = sti(pchar.rank) * 100 + 1000;
			sld = ItemsFromID("MayorsRing");
			sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
			//ложим кольцо в итем
			if (rand(3) != 2)
			{
				switch (rand(2))
				{
					case 0: sTemp = "_Brothel_room";  break;
					case 1: sTemp = "_Brothel";  break;
					case 2: sTemp = "_SecBrRoom";  break;
				}
				sld.shown = true;
				sld.startLocation = pchar.questTemp.different.TakeMayorsRing.city + sTemp;
				sld.startLocator = "item" + (rand(4) + 1);
				pchar.questTemp.different.TakeMayorsRing.item = true; //флаг кольцо валяется в итемах
				Log_QuestInfo("Кольцо находится в локации " + sld.startLocation + ", в локаторе " + sld.startLocator + "");
			}
			SetTimerFunction("TakeMayorsRing_null", 0, 0, 1); //освобождаем разрешалку на миниквесты 
			ReOpenQuestHeader("SeekMayorsRing");
			AddQuestRecord("SeekMayorsRing", "1");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", pchar.questTemp.different.TakeMayorsRing.Id);
		break;
		case "TakeRing_6":
		// evganat - можно вставить отношение сюда
			IncreaseMayorDisposition(-4);
			dialog.text = StringFromKey("Common_Mayor_186");
			link.l1 = StringFromKey("Common_Mayor_187");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -2);
		break;

		case "TakeRing_S1":
			dialog.text = StringFromKey("Common_Mayor_188");
			link.l1 = StringFromKey("Common_Mayor_189");
			link.l1.go = "TakeRing_S2";
			TakeItemFromCharacter(pchar, "MayorsRing");
		break;
		case "TakeRing_S2":
		// evganat - можно вставить отношение сюда
			IncreaseMayorDisposition(4);
			dialog.text = StringFromKey("Common_Mayor_190");
			link.l1 = StringFromKey("Common_Mayor_191");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		case "TakeRing_S3":
			dialog.text = StringFromKey("Common_Mayor_192");
			link.l1 = StringFromKey("Common_Mayor_193");
			link.l1.go = "TakeRing_S4";
		break;
		case "TakeRing_S4":
		// evganat - можно вставить отношение сюда
			IncreaseMayorDisposition(4);
			dialog.text = StringFromKey("Common_Mayor_194");
			link.l1 = StringFromKey("Common_Mayor_195", GetAddress_FormToNPC(NPChar));
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "MayorsRing");
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		// ---------------------- найти кольцо в борделе ----------------------------

		case "quests":
		// --> "Правосудие на продажу" (Warship, Rosarak)
			if (!CheckAttribute(NPChar, "JusticeOnSalePrize") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
			{
				link.l97 = StringFromKey("Common_Mayor_196", pchar, UpperFirst(GetAddress_FormToNPC(NPChar)), PChar.GenQuest.JusticeOnSale.ShipName, XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Gen"));
				link.l97.go = "JusticeOnSale_1";
			}
			if (CheckAttribute(NPChar, "JusticeOnSalePrize"))
			{
				link.l98 = StringFromKey("Common_Mayor_197", UpperFirst(GetAddress_FormToNPC(NPChar)));
				link.l98.go = "JusticeOnSale_7";
			}
		// <-- "Правосудие на продажу"
		break;

		case "node_1":
		//ОСАДЫ homo
			if (CheckAttribute(&Colonies[FindColony(npchar.City)], "Siege"))
			{

				makearef(aData, NullCharacter.Siege);

				if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true)
				{
					dialog.text = StringFromKey("Common_Mayor_198");
					link.l1 = StringFromKey("Common_Mayor_199");
					link.l1.go = "exit";

				}
				else
				{
					dialog.text = StringFromKey("Common_Mayor_200", NationNamePeople(sti(aData.nation)));
					link.l1 = StringFromKey("Common_Mayor_201", pchar);
					link.l1.go = "siege_task";
					link.l2 = StringFromKey("Common_Mayor_202");
					link.l2.go = "exit";
				}
			}
			else
			{
				//->
				makearef(aData, NullCharacter.Siege);
				if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
				&& CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true)
				{
					AddMoneyToCharacter(Pchar, (sti(aData.iSquadronPower) * 3000));
					ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
					ChangeCharacterReputation(PChar, 10);
					AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
					AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
					AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
					AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
					//--> слухи
					SiegeRumour(
						StringFromKey("Common_Mayor_203", NationNameSK(sti(aData.nation)), GetAddress_Form(NPChar)), aData.Colony, sti(aData.conation), -1, 15, 3);
					//<-- слухи
					DeleteAttribute(aData, "PlayerHelpMayor");
					DeleteAttribute(aData, "HelpColony");
					dialog.text = StringFromKey("Common_Mayor_204", GetAddress_Form(NPChar), GetFullName(pchar), NationNameSK(sti(aData.nation)), FindMoneyString(sti(aData.iSquadronPower) * 1500));
					link.l1 = StringFromKey("Common_Mayor_205", GetAddress_FormToNPC(NPChar));
					link.l1.go = "exit";
				}
				else
				{
					if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
					dialog.text = StringFromKey("Common_Mayor_206");
					link.l1 = StringFromKey("Common_Mayor_207", NationNameGenitive(sti(NPChar.nation)));
					link.l1.go = "work";

					// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
					if (CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = StringFromKey("Common_Mayor_208", pchar, XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Gen"), FindPeoplesString(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount), "No"));
						link.l11.go = "PiratesOnUninhabited_1";
					}

					link.l2 = StringFromKey("Common_Mayor_209");
					if (CheckAttribute(pchar, "questTemp.ReasonToFast") && !CheckAttribute(pchar, "questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					{
						link.l2.go = "ReasonToFast_Mayor1";
					}
					else
					{
						link.l2.go = "quests";
					}
					if (CheckAttribute(pchar, "GenQuest.CaptainComission.variant") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
					{
						if (pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar, "GenQuest.CaptainComission.SpeakMayor"))
						{
							link.l12 = StringFromKey("Common_Mayor_210", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")), pchar.GenQuest.CaptainComission.Name);
							link.l12.go = "CapComission_Mayor1";
						}
						if (CheckAttribute(pchar, "GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = StringFromKey("Common_Mayor_211", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")), pchar.GenQuest.CaptainComission.Name);
							link.l12.go = "CapComission_Mayor9";
						}
						if (pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = StringFromKey("Common_Mayor_212", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")), pchar.GenQuest.CaptainComission.Name);
							link.l12.go = "CapComission_Mayor13";
						}
					}
					if (CheckAttribute(pchar, "GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
					{
						if (!CheckAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor"))
						{
							iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
							if (CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
							{
								link.l13 = StringFromKey("Common_Mayor_213", pchar, UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Pre")), pchar.GenQuest.ShipWreck.Name, pchar.GenQuest.ShipWreck.BadName, iDay);
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = StringFromKey("Common_Mayor_214", pchar, UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Pre")), pchar.GenQuest.ShipWreck.ShipTypeName, iDay);
								link.l13.go = "ShipWreck1";
							}
						}
					}
					if (GetPrisonerQty() > 0)
					{
						link.l3 = StringFromKey("Common_Mayor_215");
						link.l3.go = "sell_prisoner";
					}
					link.l4 = StringFromKey("Common_Mayor_216", pchar, NationNameGenitive(sti(NPChar.nation)));
					link.l4.go = "Where_guber";
					link.l5 = StringFromKey("Common_Mayor_217");
					link.l5.go = "Play_Game";
					link.l10 = StringFromKey("Common_Mayor_218", GetAddress_FormToNPC(NPChar));
					link.l10.go = "node_2";
				}
			}//<-
		break;

		case "Play_Game":
			dialog.text = StringFromKey("Common_Mayor_219");
			link.l1 = StringFromKey("Common_Mayor_220");
			link.l1.go = "Card_Game";
			link.l2 = StringFromKey("Common_Mayor_221");
			link.l2.go = "Dice_Game";
			link.l10 = StringFromKey("Common_Mayor_222");
			link.l10.go = "exit";
		break;

		//  карты -->
		case "Card_Game":
		//            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
			if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || sti(PChar.rank) < 4 ||
			PlayerRPGCheck_BadReputation(50, false) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
			{
				PlayerRPGCheck_Skill_NotifyFail(SKILL_LEADERSHIP, false);
				SetNPCQuestDate(npchar, "Card_date_Yet");
				dialog.text = StringFromKey("Common_Mayor_223");
				link.l1 = StringFromKey("Common_Mayor_224");
				link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Card_date_begin"))
				{
					dialog.text = StringFromKey("Common_Mayor_225");
					link.l1 = StringFromKey("Common_Mayor_226");
					link.l1.go = "Cards_begin";
					link.l2 = StringFromKey("Common_Mayor_227");
					link.l2.go = "Cards_Rule";
				}
				else
				{
					dialog.text = StringFromKey("Common_Mayor_228");
					link.l1 = StringFromKey("Common_Mayor_229");
					link.l1.go = "exit";
				}
			}
		break;

		case "Cards_Rule":
			dialog.text = GlobalStringConvert("CARDS_RULE");
			link.l1 = StringFromKey("Common_Mayor_230");
			link.l1.go = "Cards_begin";
			link.l3 = StringFromKey("Common_Mayor_231");
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			dialog.text = StringFromKey("Common_Mayor_232");
			link.l1 = StringFromKey("Common_Mayor_233");
			link.l1.go = "Cards_Node_100";
			link.l2 = StringFromKey("Common_Mayor_234");
			link.l2.go = "Cards_Node_500";
			link.l3 = StringFromKey("Common_Mayor_235");
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
			if (!CheckCardsGameSmallRate())
			{
				dialog.text = StringFromKey("Common_Mayor_236");
				link.l1 = StringFromKey("Common_Mayor_237");
				link.l1.go = "exit";
				break;
			}

			if (sti(pchar.Money) < 3000)
			{
				dialog.text = StringFromKey("Common_Mayor_238", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Common_Mayor_239");
				link.l1.go = "exit";
				break;
			}
			if (sti(npchar.Money) < 3000)
			{
				dialog.text = StringFromKey("Common_Mayor_240");
				link.l1 = StringFromKey("Common_Mayor_241");
				link.l1.go = "exit";
				break;
			}
			dialog.text = StringFromKey("Common_Mayor_242");
			link.l1 = StringFromKey("Common_Mayor_243");
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate = 1000;
			pchar.GenQuest.Cards.SitType = false;
		break;

		case "Cards_Node_500":
			if (!CheckCardsGameSmallRate())
			{
				dialog.text = StringFromKey("Common_Mayor_244");
				link.l1 = StringFromKey("Common_Mayor_245");
				link.l1.go = "exit";
				break;
			}
			if (!CheckCardsGameBigRate())
			{
				dialog.text = StringFromKey("Common_Mayor_246");
				link.l1 = StringFromKey("Common_Mayor_247");
				link.l1.go = "Cards_Node_100";
				link.l2 = StringFromKey("Common_Mayor_248");
				link.l2.go = "exit";
				break;
			}

			if (sti(pchar.Money) < 15000)
			{
				dialog.text = StringFromKey("Common_Mayor_249", GetAddress_Form(npchar));
				link.l1 = StringFromKey("Common_Mayor_250");
				link.l1.go = "exit";
				break;
			}
			if (sti(npchar.Money) < 15000)
			{
				dialog.text = StringFromKey("Common_Mayor_251");
				link.l1 = StringFromKey("Common_Mayor_252");
				link.l1.go = "exit";
				break;
			}
			dialog.text = StringFromKey("Common_Mayor_253");
			link.l1 = StringFromKey("Common_Mayor_254");
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate = 5000;
			pchar.GenQuest.Cards.SitType = false;
		break;

		case "Cards_begin_go":
			SetNPCQuestDate(npchar, "Card_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchCardsGame();
		break;
		// карты <--

		//  Dice -->
		case "Dice_Game":
		//            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
			if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || sti(PChar.rank) < 4 ||
			PlayerRPGCheck_BadReputation(50, false) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
			{
				PlayerRPGCheck_Skill_NotifyFail(SKILL_LEADERSHIP, false);
				SetNPCQuestDate(npchar, "Dice_date_Yet");
				dialog.text = StringFromKey("Common_Mayor_255");
				link.l1 = StringFromKey("Common_Mayor_256");
				link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = StringFromKey("Common_Mayor_257");
					link.l1 = StringFromKey("Common_Mayor_258");
					link.l1.go = "Dice_begin";
					link.l2 = StringFromKey("Common_Mayor_259");
					link.l2.go = "Dice_Rule";
				}
				else
				{
					dialog.text = StringFromKey("Common_Mayor_260");
					link.l1 = StringFromKey("Common_Mayor_261");
					link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
			dialog.text = GlobalStringConvert("DICE_RULE");
			link.l1 = StringFromKey("Common_Mayor_262");
			link.l1.go = "Dice_begin";
			link.l3 = StringFromKey("Common_Mayor_263");
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			dialog.text = StringFromKey("Common_Mayor_264");
			link.l1 = StringFromKey("Common_Mayor_265");
			link.l1.go = "Dice_Node_100";
			link.l2 = StringFromKey("Common_Mayor_266");
			link.l2.go = "Dice_Node_500";
			link.l3 = StringFromKey("Common_Mayor_267");
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
			if (!CheckDiceGameSmallRate())
			{
				dialog.text = StringFromKey("Common_Mayor_268");
				link.l1 = StringFromKey("Common_Mayor_269");
				link.l1.go = "exit";
				break;
			}

			if (sti(pchar.Money) < 3000)
			{
				dialog.text = StringFromKey("Common_Mayor_270", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Common_Mayor_271");
				link.l1.go = "exit";
				break;
			}
			if (sti(npchar.Money) < 3000)
			{
				dialog.text = StringFromKey("Common_Mayor_272");
				link.l1 = StringFromKey("Common_Mayor_273");
				link.l1.go = "exit";
				break;
			}
			dialog.text = StringFromKey("Common_Mayor_274");
			link.l1 = StringFromKey("Common_Mayor_275");
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate = 500;
			pchar.GenQuest.Dice.SitType = false;
		break;

		case "Dice_Node_500":
			if (!CheckDiceGameSmallRate())
			{
				dialog.text = StringFromKey("Common_Mayor_276");
				link.l1 = StringFromKey("Common_Mayor_277");
				link.l1.go = "exit";
				break;
			}
			if (!CheckDiceGameBigRate())
			{
				dialog.text = StringFromKey("Common_Mayor_278");
				link.l1 = StringFromKey("Common_Mayor_279");
				link.l1.go = "Dice_Node_100";
				link.l2 = StringFromKey("Common_Mayor_280");
				link.l2.go = "exit";
				break;
			}

			if (sti(pchar.Money) < 15000)
			{
				dialog.text = StringFromKey("Common_Mayor_281", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Common_Mayor_282");
				link.l1.go = "exit";
				break;
			}
			if (sti(npchar.Money) < 15000)
			{
				dialog.text = StringFromKey("Common_Mayor_283");
				link.l1 = StringFromKey("Common_Mayor_284");
				link.l1.go = "exit";
				break;
			}
			dialog.text = StringFromKey("Common_Mayor_285");
			link.l1 = StringFromKey("Common_Mayor_286");
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate = 2000;
			pchar.GenQuest.Dice.SitType = false;
		break;

		case "Dice_begin_go":
			SetNPCQuestDate(npchar, "Dice_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchDiceGame();
		break;
		// Dice <--
		case "node_2":
			dialog.text = StringFromKey("Common_Mayor_287");
			link.l1 = StringFromKey("Common_Mayor_288", pchar);
			link.l1.go = "exit";
		break;

		case "Where_guber":
			offref = characterFromID(NationShortName(sti(NPChar.nation)) + "_guber");
			bool bVillemstad = npchar.location == "Villemstad_townhall" && offref.location == "Villemstad_townhall2";
			if (NPChar.location == offref.location || bVillemstad)
			{
				if (bVillemstad)
				{
					dialog.text = StringFromKey("Common_Mayor_291", RandPhraseSimple(
								StringFromKey("Common_Mayor_289"),
								StringFromKey("Common_Mayor_290")), NationNameGenitive(sti(NPChar.nation)), GetFullName(offref));
					link.l1 = StringFromKey("Common_Mayor_292");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("Common_Mayor_295", RandPhraseSimple(
								StringFromKey("Common_Mayor_293"),
								StringFromKey("Common_Mayor_294")), NationNameGenitive(sti(NPChar.nation)), GetFullName(offref));
					link.l1 = StringFromKey("Common_Mayor_296");
					link.l1.go = "exit";
				}
			}
			else
			{
				if (bBettaTestMode || GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) > rand(5) || CheckCharacterItem(Pchar, "patent_" + NationShortName(sti(NPChar.nation))))// когда патен всегда
				{
					cn = FindLocation(offref.location);
					if (cn <= 0)
					{
						attrLoc = "error";
						dialog.text = StringFromKey("Common_Mayor_299", RandPhraseSimple(
									StringFromKey("Common_Mayor_297"),
									StringFromKey("Common_Mayor_298")), NationNameGenitive(sti(NPChar.nation)), GetFullName(offref));
					}
					else
					{
						attrLoc = locations[cn].islandId;
						if (attrLoc == "Mein")
						{
							dialog.text = StringFromKey("Common_Mayor_305", RandPhraseSimple(
										StringFromKey("Common_Mayor_300"),
										StringFromKey("Common_Mayor_301")), NationNameGenitive(sti(NPChar.nation)), GetFullName(offref), LinkRandPhrase(
										StringFromKey("Common_Mayor_302"),
										StringFromKey("Common_Mayor_303"),
										StringFromKey("Common_Mayor_304")), GetConvertStr(locations[cn].fastreload + " Town", "LocLables.txt"));
						}
						else
						{
							dialog.text = StringFromKey("Common_Mayor_311", RandPhraseSimple(
										StringFromKey("Common_Mayor_306"),
										StringFromKey("Common_Mayor_307")), NationNameGenitive(sti(NPChar.nation)), GetFullName(offref), LinkRandPhrase(
										StringFromKey("Common_Mayor_308"),
										StringFromKey("Common_Mayor_309"),
										StringFromKey("Common_Mayor_310")), GetConvertStr(attrLoc, "LocLables.txt"), GetConvertStr(locations[cn].fastreload + " Town", "LocLables.txt"));
						}
					}
					link.l1 = StringFromKey("Common_Mayor_312");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("Common_Mayor_313");
					link.l1 = StringFromKey("Common_Mayor_314");
					link.l1.go = "exit";
				}
			}
		break;
		//---------------------------- генератор квестов мэра -------------------------------
		case "work":
			dialog.text = StringFromKey("Common_Mayor_315");
			link.l1 = StringFromKey("Common_Mayor_316");
			link.l1.go = "exit";
			// boal квесты от ВМЛ -->
			if (CheckAttribute(pchar, "GenQuest.GhostShipDone_" + NPChar.id))
			{
				dialog.text = StringFromKey("Common_Mayor_317");
				link.l1 = StringFromKey("Common_Mayor_318", pchar);
				link.l1.go = "GhostShipDone";
				break;
			}
			if (CheckAttribute(NPChar, "from_sea") && Pchar.location.from_sea == NPChar.from_sea)
			{
				if (!CheckAttribute(pchar, "GenQuest.GhostShip.LastBattle") &&
				CheckAttribute(pchar, "GenQuest.GhostShip.NeedCoins") &&
				GetNpcQuestPastDayWOInit(npchar, "GhostShipHelp") > 30 &&
				!CheckAttribute(pchar, "GenQuest.GhostShipWorkId") &&
				idRand(npchar.city + "GhostShipHelp", 2) == 1)
				{
					dialog.text = StringFromKey("Common_Mayor_321", GetAddress_Form(NPChar), RandPhraseSimple(
								StringFromKey("Common_Mayor_319"),
								StringFromKey("Common_Mayor_320")));
					link.l1 = StringFromKey("Common_Mayor_324", RandPhraseSimple(
								StringFromKey("Common_Mayor_322"),
								StringFromKey("Common_Mayor_323")));
					link.l1.go = "GhostShipHelp_1";
					break;
				}
			}
			// boal квесты от ВМЛ <--
			//==> взят ли какой-либо квест
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{
				//--> Федот, да не тот
				QuestName = pchar.GenQuest.questName;
				if (pchar.GenQuest.(QuestName).MayorId != npchar.id)
				{
					dialog.text = StringFromKey("Common_Mayor_327", RandPhraseSimple(
								StringFromKey("Common_Mayor_325", XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city + "Gen")),
								StringFromKey("Common_Mayor_326", XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city + "Pre"))));
					link.l1 = StringFromKey("Common_Mayor_330", RandPhraseSimple(
								StringFromKey("Common_Mayor_328"),
								StringFromKey("Common_Mayor_329", pchar, GetAddress_FormToNPC(NPChar))));
					link.l1.go = "exit";
					break;
				}
				//<--Федот, да не тот
				//-------- взят квест уничтожения банды ---------->>
				if (QuestName == "DestroyGang")
				{
					switch (pchar.GenQuest.DestroyGang)
					{
						makearef(arName, pchar.GenQuest.DestroyGang);
						case "":
							dialog.text = StringFromKey("Common_Mayor_334", LinkRandPhrase(
										StringFromKey("Common_Mayor_331", GetFullName(arName)),
										StringFromKey("Common_Mayor_332", GetFullName(arName)),
										StringFromKey("Common_Mayor_333", GetFullName(arName))));
							link.l1 = StringFromKey("Common_Mayor_337", RandPhraseSimple(
										StringFromKey("Common_Mayor_335", GetAddress_FormToNPC(NPChar)),
										StringFromKey("Common_Mayor_336", GetAddress_FormToNPC(NPChar))));
							link.l1.go = "exit";
						break;
						case "Late":
						// evganat - можно вставить отношение сюда
							IncreaseMayorDisposition(-4);
							dialog.text = StringFromKey("Common_Mayor_340", RandPhraseSimple(
										StringFromKey("Common_Mayor_338", GetFullName(arName), GetAddress_Form(NPChar)),
										StringFromKey("Common_Mayor_339", GetFullName(arName))));
							link.l1 = StringFromKey("Common_Mayor_341", pchar, GetAddress_FormToNPC(NPChar));
							link.l1.go = "All_Late";
						break;
						case "Found":
						// evganat - можно вставить отношение сюда
							IncreaseMayorDisposition(-3);
							dialog.text = StringFromKey("Common_Mayor_344", RandPhraseSimple(
										StringFromKey("Common_Mayor_342", GetFullName(arName)),
										StringFromKey("Common_Mayor_343", GetFullName(arName))));
							link.l1 = StringFromKey("Common_Mayor_345", GetAddress_FormToNPC(NPChar));
							link.l1.go = "All_Found";
						break;
						case "Execute":
						// evganat - можно вставить отношение сюда
							IncreaseMayorDisposition(3);
							dialog.text = StringFromKey("Common_Mayor_348", RandPhraseSimple(
										StringFromKey("Common_Mayor_346", GetFullName(arName)),
										StringFromKey("Common_Mayor_347", GetFullName(arName))));
							link.l1 = StringFromKey("Common_Mayor_349", GetAddress_FormToNPC(NPChar));
							link.l1.go = "All_Execute";
							AddCharacterExpToSkill(PChar, "Leadership", 50);
						break;
					}
				}
				//------ поиска шпиона ------------>>
				if (QuestName == "SeekSpy")
				{
					switch (pchar.GenQuest.SeekSpy)
					{
						case "":
							dialog.text = StringFromKey("Common_Mayor_353", LinkRandPhrase(
										StringFromKey("Common_Mayor_350"),
										StringFromKey("Common_Mayor_351"),
										StringFromKey("Common_Mayor_352")));
							link.l1 = StringFromKey("Common_Mayor_356", RandPhraseSimple(
										StringFromKey("Common_Mayor_354", GetAddress_FormToNPC(NPChar)),
										StringFromKey("Common_Mayor_355", GetAddress_FormToNPC(NPChar))));
							link.l1.go = "exit";
						break;
						case "Late":
						// evganat - можно вставить отношение сюда
							IncreaseMayorDisposition(-3);
							dialog.text = StringFromKey("Common_Mayor_359", RandPhraseSimple(
										StringFromKey("Common_Mayor_357"),
										StringFromKey("Common_Mayor_358")));
							link.l1 = StringFromKey("Common_Mayor_360", pchar, GetAddress_FormToNPC(NPChar));
							link.l1.go = "All_Late";
						break;
						case "Execute":
						// evganat - можно вставить отношение сюда
							IncreaseMayorDisposition(2);
							dialog.text = StringFromKey("Common_Mayor_363", RandPhraseSimple(
										StringFromKey("Common_Mayor_361"),
										StringFromKey("Common_Mayor_362")));
							link.l1 = StringFromKey("Common_Mayor_364", pchar);
							link.l1.go = "All_Execute";
							AddCharacterExpToSkill(PChar, "Leadership", 50);
						break;
						case "FoundSpy":
						// evganat - можно вставить отношение сюда
							IncreaseMayorDisposition(2);
							dialog.text = StringFromKey("Common_Mayor_367", RandPhraseSimple(
										StringFromKey("Common_Mayor_365"),
										StringFromKey("Common_Mayor_366")));
							link.l1 = StringFromKey("Common_Mayor_368", pchar);
							link.l1.go = "All_Execute";
							sld = characterFromId("MayorQuestSpy");
							sld.lifeDay = 0;
							ChangeCharacterAddress(sld, "none", "");
							LAi_SetStayType(sld);
							sTemp = npchar.city + "_town";
							LocatorReloadEnterDisable(sTemp, "gate_back", false);
							LocatorReloadEnterDisable(sTemp, "reload1_back", false);
							LocatorReloadEnterDisable(sTemp, "reload2_back", false);
							LocatorReloadEnterDisable(sTemp, "boat", false);
							AddCharacterExpToSkill(PChar, "Leadership", 70);
						break;
					}
				}
				//------ проникновение во враждебный город ------------>>
				if (QuestName == "Intelligence")
				{
					switch (pchar.GenQuest.Intelligence)
					{
						case "":
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								// evganat - можно вставить отношение сюда
								IncreaseMayorDisposition(-5);
								dialog.text = StringFromKey("Common_Mayor_371", RandPhraseSimple(
											StringFromKey("Common_Mayor_369"),
											StringFromKey("Common_Mayor_370")));
								link.l1 = StringFromKey("Common_Mayor_372", pchar, GetAddress_FormToNPC(NPChar));
								link.l1.go = "All_Late";
							}
							else
							{
								dialog.text = StringFromKey("Common_Mayor_376", LinkRandPhrase(
											StringFromKey("Common_Mayor_373"),
											StringFromKey("Common_Mayor_374"),
											StringFromKey("Common_Mayor_375")));
								link.l1 = StringFromKey("Common_Mayor_379", RandPhraseSimple(
											StringFromKey("Common_Mayor_377", GetAddress_FormToNPC(NPChar)),
											StringFromKey("Common_Mayor_378", GetAddress_FormToNPC(NPChar))));
								link.l1.go = "exit";
							}
						break;
						case "Execute":
						// evganat - можно вставить отношение сюда
							IncreaseMayorDisposition(5);
							dialog.text = StringFromKey("Common_Mayor_382", RandPhraseSimple(
										StringFromKey("Common_Mayor_380"),
										StringFromKey("Common_Mayor_381")));
							link.l1 = StringFromKey("Common_Mayor_383", pchar);
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								link.l1.go = "Intelligence_ExecuteLate";
								AddCharacterExpToSkill(PChar, "Sneak", 200);
							}
							else
							{
								link.l1.go = "All_Execute";
								AddCharacterExpToSkill(PChar, "Leadership", 100);
								AddCharacterExpToSkill(PChar, "Sneak", 200);
							}
							TakeItemFromCharacter(pchar, "sicretLetter");
							DeleteAttribute(ItemsFromID("sicretLetter"), "City");
							DeleteAttribute(ItemsFromID("sicretLetter"), "Mayor");
						break;
					}
				}
				//------ уничтожение контры ------------>>
				if (QuestName == "KillSmugglers")
				{
					switch (pchar.GenQuest.KillSmugglers)
					{
						case "":
							dialog.text = StringFromKey("Common_Mayor_387", LinkRandPhrase(
										StringFromKey("Common_Mayor_384"),
										StringFromKey("Common_Mayor_385"),
										StringFromKey("Common_Mayor_386")));
							link.l1 = StringFromKey("Common_Mayor_390", RandPhraseSimple(
										StringFromKey("Common_Mayor_388", GetAddress_FormToNPC(NPChar)),
										StringFromKey("Common_Mayor_389", GetAddress_FormToNPC(NPChar))));
							link.l1.go = "exit";
						break;
						case "Late":
						// evganat - можно вставить отношение сюда
							IncreaseMayorDisposition(-4);
							dialog.text = StringFromKey("Common_Mayor_393", RandPhraseSimple(
										StringFromKey("Common_Mayor_391"),
										StringFromKey("Common_Mayor_392")));
							link.l1 = StringFromKey("Common_Mayor_394", pchar, GetAddress_FormToNPC(NPChar));
							link.l1.go = "All_Late";
						break;
						case "Execute":
						// evganat - можно вставить отношение сюда
							IncreaseMayorDisposition(4);
							dialog.text = StringFromKey("Common_Mayor_397", RandPhraseSimple(
										StringFromKey("Common_Mayor_395"),
										StringFromKey("Common_Mayor_396")));
							link.l1 = StringFromKey("Common_Mayor_398", pchar, GetConvertStr(pchar.GenQuest.KillSmugglers.shoreId, "LocLables.txt"));
							link.l1.go = "All_Execute";
							AddCharacterExpToSkill(PChar, "Leadership", 50);
							AddCharacterExpToSkill(PChar, SKILL_SNEAK, 100);
						break;
					}
				}
				//------ найти пирата в море ------------>>
				if (QuestName == "DestroyPirate")
				{
					switch (pchar.GenQuest.DestroyPirate)
					{
						case "":
							dialog.text = StringFromKey("Common_Mayor_402", LinkRandPhrase(
										StringFromKey("Common_Mayor_399"),
										StringFromKey("Common_Mayor_400"),
										StringFromKey("Common_Mayor_401")));
							link.l1 = StringFromKey("Common_Mayor_405", RandPhraseSimple(
										StringFromKey("Common_Mayor_403", GetAddress_FormToNPC(NPChar)),
										StringFromKey("Common_Mayor_404", GetAddress_FormToNPC(NPChar))));
							link.l1.go = "exit";
						break;
						case "Late":
						// evganat - можно вставить отношение сюда
							IncreaseMayorDisposition(-4);
							dialog.text = StringFromKey("Common_Mayor_408", RandPhraseSimple(
										StringFromKey("Common_Mayor_406"),
										StringFromKey("Common_Mayor_407")));
							link.l1 = StringFromKey("Common_Mayor_409", GetAddress_FormToNPC(NPChar));
							link.l1.go = "All_Late";
						break;
						case "Execute":
						// evganat - можно вставить отношение сюда
							IncreaseMayorDisposition(4);
							dialog.text = StringFromKey("Common_Mayor_412", RandPhraseSimple(
										StringFromKey("Common_Mayor_410"),
										StringFromKey("Common_Mayor_411")));
							link.l1 = StringFromKey("Common_Mayor_413", GetAddress_FormToNPC(NPChar));
							link.l1.go = "All_Execute";
							AddCharacterExpToSkill(PChar, "Leadership", 50);
							AddCharacterExpToSkill(PChar, SKILL_FORTUNE, 50);
							//здесь снимаем торговцев
							for (i = 0; i < 5; i++)
							{
								Group_DeleteGroup("MQGroupAll_" + i);
							}
						break;
						case "Found":
						// evganat - можно вставить отношение сюда
							IncreaseMayorDisposition(-3);
							dialog.text = StringFromKey("Common_Mayor_416", RandPhraseSimple(
										StringFromKey("Common_Mayor_414"),
										StringFromKey("Common_Mayor_415")));
							link.l1 = StringFromKey("Common_Mayor_417", GetAddress_FormToNPC(NPChar));
							link.l1.go = "All_Found";
						break;
						case "PirateIsOut":
						// evganat - можно вставить отношение сюда
							IncreaseMayorDisposition(-3);
							dialog.text = StringFromKey("Common_Mayor_420", RandPhraseSimple(
										StringFromKey("Common_Mayor_418"),
										StringFromKey("Common_Mayor_419")));
							link.l1 = StringFromKey("Common_Mayor_421", pchar, GetAddress_FormToNPC(NPChar));
							link.l1.go = "All_Found";
						break;
					}
				}
				//<<------ взятые квесты ------------
				break;
			}
			//==> раздача патентов
			sTemp = npchar.city;
			if (CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp) && sti(pchar.GenQuest.MayorQuestsList.(sTemp)) > (5 + rand(5)) && !CheckCharacterItem(Pchar, "patent_" + NationShortName(sti(NPChar.nation))))
			{
				dialog.text = StringFromKey("Common_Mayor_422", GetAddress_Form(NPChar), NationNameGenitive(sti(NPChar.nation)));

				link.l1 = StringFromKey("Common_Mayor_423", pchar, NationNameGenitive(sti(NPChar.nation)));
				link.l1.go = "Patent_Give";
				if (isMainCharacterPatented())
				{
					link.l2 = StringFromKey("Common_Mayor_424");
				}
				else
				{
					link.l2 = StringFromKey("Common_Mayor_425");
				}
				link.l2.go = "exit";
				pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
				break;
			}
			//занят ПГГ
			i = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONMAYOR);
			if (i != -1)
			{
				dialog.text = StringFromKey("Common_Mayor_426", GetFullName(&Characters[i]));
				link.l1 = StringFromKey("Common_Mayor_427");
				link.l1.go = "exit";
				break;
			}
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") > 2 || bBettaTestMode)
			{
				SaveCurrentNpcQuestDateParam(npchar, "work_date");
				if (idRand(npchar.id + "mayorwork", 5) > 4 && !bBettaTestMode)
				{
					dialog.text = StringFromKey("Common_Mayor_431", LinkRandPhrase(
								StringFromKey("Common_Mayor_428"),
								StringFromKey("Common_Mayor_429"),
								StringFromKey("Common_Mayor_430")));
					link.l1 = StringFromKey("Common_Mayor_432", pchar, GetAddress_FormToNPC(NPChar));
					link.l1.go = "exit";
				}
				else
				{
					sTemp = GetSpyColony(npchar);
					// boal 02.09.06 -->
					if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
					{
						// если ПГГ контрит в этом городе, то мэр даёт задание на контру по факту - приятное с полезным, жаловаться не нужно, если задания другие были, то в сад, этот код не сработает
						i = 3;
					}
					else
					{
						//отсекаем возможность дать квест пирата в Панаме
						if (npchar.city == "Panama")
						{
							// не даём задание пробраться во вражеский город, если у нации ГГ нет врагов
							if (sTemp == "none")
								i = 1 + rand(1);
							else
								i = rand(2);
						}
						else
						{
							// не даём задание пробраться во вражеский город, если у нации ГГ нет врагов
							if (sTemp == "none")
								i = 1 + idRand(npchar.id + "SpyColony", 3);
							else
								i = idRand(npchar.id + "SpyColony", 4);
						}
					}
					// boal <--
					switch (i)
					{
						//========== пробраться во вражеский город ============
						case 0:
							pchar.GenQuest.Intelligence.Terms = idRand(npchar.id + "Intelligence", 10) + (42 - MOD_SKILL_ENEMY_RATE); //сроки выполнения задания
							pchar.GenQuest.Intelligence.Money = ((idRand(npchar.id + "Intelligence", 4) + 6) * 1000) + (sti(pchar.rank) * 1000 + 10000); //вознаграждение
							pchar.GenQuest.Intelligence.City = sTemp; //враждебная колония
							sTemp = StringFromKey("Common_Mayor_433", XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable + "Pre"));
							dialog.text = StringFromKey("Common_Mayor_434", XI_ConvertString("Colony" + pchar.GenQuest.Intelligence.City + "Acc"), sTemp);
							link.l1 = StringFromKey("Common_Mayor_435", pchar, XI_ConvertString("Colony" + pchar.GenQuest.Intelligence.City + "Pre"));
							link.l1.go = "Intelligence";
						break;
						//========== квест уничтожения банды ============
						case 1:
							pchar.GenQuest.DestroyGang.Terms = idRand(npchar.id + "DestroyGang", 2) + 2; //сроки выполнения задания
							pchar.GenQuest.DestroyGang.Money = ((idRand(npchar.id + "DestroyGang", 8) + 2) * 170) + (sti(pchar.rank) * 200 + 2000); //вознаграждение
							makearef(arName, pchar.GenQuest.DestroyGang);
							arName.nation = PIRATE;
							arName.sex = "man";
							SetRandomNameToCharacter(arName); //имя бандита в структуру квеста
							dialog.text = StringFromKey("Common_Mayor_436", XI_ConvertString("Colony" + npchar.city + "Gen"), GetFullName(arName));
							link.l1 = StringFromKey("Common_Mayor_437", pchar);
							link.l1.go = "DestroyGang";
						break;
						//========== розыска лазутчика ============
						case 2:
							pchar.GenQuest.SeekSpy.Terms = idRand(npchar.id + "SeekSpy", 2) + 3; //сроки выполнения задания
							pchar.GenQuest.SeekSpy.Money = ((idRand(npchar.id + "SeekSpy", 8) + 2) * 150) + (sti(pchar.rank) * 200 + 2000); //вознаграждение
							dialog.text = StringFromKey("Common_Mayor_438", XI_ConvertString("Colony" + npchar.city + "Pre"));
							link.l1 = StringFromKey("Common_Mayor_439", GetAddress_FormToNPC(NPChar));
							link.l1.go = "SeekSpy";
						break;
						//========== уничтожение контрабандистов ============
						case 3:
							dialog.text = StringFromKey("Common_Mayor_440");
							link.l1 = StringFromKey("Common_Mayor_441", pchar);
							link.l1.go = "KillSmugglers";
						break;
						//========== замочить пирата, что грабит суда ============
						case 4:
						//--> генерим ранг
							iRank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE;

							//<-- генерим ранг
							LAi_group_Delete("MayorPirateGroup");
							sld = GetCharacter(NPC_GenerateCharacter("MQPirate", "", "man", "man", iRank, sti(npchar.nation), -1, true));
							SetCaptanModelByEncType(sld, "pirate");
							DeleteAttribute(sld, "Ship");
							SetShipToFantom(sld, "pirate", false);
							sld.Ship.Mode = "Pirate";
							//sld.ShipTaskLock = true; //лочим таск
							sld.dialog.filename = "MayorQuests_dialog.c";
							sld.dialog.currentnode = "DestroyPirate_Abordage";
							sld.DeckDialogNode = "DestroyPirate_Deck";
							sld.DontRansackCaptain = true;
							sld.DontCheckFlag = true;  // не проверять флаг ГГ
							sld.SaveItemsForDead = true; // сохранять на трупе вещи
							sld.DontClearDead = true; // не убирать труп через 200с
							sld.AlwaysSandbankManeuver = true;
							sld.WatchFort = true; //видеть форты
							sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
							sld.greeting = "pirat_common";
							LAi_group_MoveCharacter(sld, "MayorPirateGroup");
							dialog.text = StringFromKey("Common_Mayor_442", XI_ConvertString("Colony" + npchar.city + "Gen"));
							link.l1 = StringFromKey("Common_Mayor_443", pchar, GetAddress_FormToNPC(NPChar));
							link.l1.go = "DestroyPirate";
						break;
					}
				}
			}
			else
			{
				dialog.text = StringFromKey("Common_Mayor_447", LinkRandPhrase(
							StringFromKey("Common_Mayor_444"),
							StringFromKey("Common_Mayor_445"),
							StringFromKey("Common_Mayor_446")));
				link.l1 = StringFromKey("Common_Mayor_450", RandPhraseSimple(
							StringFromKey("Common_Mayor_448"),
							StringFromKey("Common_Mayor_449", GetAddress_FormToNPC(NPChar))));
				link.l1.go = "exit";
			}
		//---------------------------- генератор квестов мэра -------------------------------
		break;

		case "Patent_Give":
			pchar.PatentNation = NationShortName(sti(NPChar.nation));
			pchar.PatentPrice = 0;
			dialog.text = StringFromKey("Common_Mayor_451");
			link.l1 = StringFromKey("Common_Mayor_452", GetAddress_FormToNPC(NPChar));
			link.l1.go = "exit";
			AddDialogExitQuest("any_patent_take");
			ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -100);
		break;

		case "sell_prisoner":
			dialog.text = StringFromKey("Common_Mayor_453");

			qty = 1;
			for (i = 0; i < GetPassengersQuantity(pchar); i++)
			{
				cn = GetPassenger(pchar, i);
				if (cn != -1)
				{
					offref = GetCharacter(cn);
					if (offref.id == "Sharp_Prisoner" && or(NPChar.nation != SPAIN, CheckAttribute(&TEV, "Sharp_Prisoner_DialogChoosen.PearlVillage"))) // Шарпа можно сдать только испанцам
						continue;
					if (CheckAttribute(offref, "prisoned"))
					{
						if (sti(offref.prisoned) == true && GetRemovable(offref)) // ставим только фантомов
						{
							attrLoc = "l" + qty;
							link.(attrLoc) = GetFullName(offref) + " - " + NationNameMan(sti(offref.nation)) + ".";
							link.(attrLoc).go = "GetPrisonerIdx_" + offref.index;
							qty++;
						}
					}
				}
			}
			link.l99 = StringFromKey("Common_Mayor_454");
			link.l99.go = "exit";
		break;

		case "sell_prisoner_2":
			offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));

			if (offref.id == "Sharp_Prisoner" && NPChar.nation == SPAIN)
			{
				sTemp = StringFromKey("Common_Mayor_455");
				if (NPChar.location == "Havana_townhall")
				{
					sTemp = StringFromKey("Common_Mayor_456"); // Для столицы
				}

				dialog.text = StringFromKey("Common_Mayor_457", sTemp);
				link.l1 = StringFromKey("Common_Mayor_458", GetFullName(NPChar));
				link.l1.go = "Exit_Sell_Sharp_Prisoner";
				break;
			}

			attrLoc = StringFromKey("Common_Mayor_459", GetFullName(offref), NationNameMan(sti(offref.nation)));
			// цена зависит от губернатора
			qty = makeint(sti(offref.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(offref, "Leadership") * 500 + GetCharacterSkillToOld(pchar, "commerce") * 500);
			if (sti(offref.nation) == sti(NPChar.nation))
			{
				attrLoc = StringFromKey("Common_Mayor_460", attrLoc, FindMoneyString(qty));
			}
			else
			{
				if (sti(offref.nation) == PIRATE)
				{
					qty = qty / 5;
					sTemp = FindMoneyString(qty);
					attrLoc = StringFromKey("Common_Mayor_467", attrLoc, RandPhraseSimple(
								StringFromKey("Common_Mayor_463", RandPhraseSimple(
										StringFromKey("Common_Mayor_461", sTemp),
										StringFromKey("Common_Mayor_462", sTemp))),
								StringFromKey("Common_Mayor_466", RandPhraseSimple(
										StringFromKey("Common_Mayor_464", sTemp),
										StringFromKey("Common_Mayor_465", sTemp)))));
					/*if (CheckAttribute(NPChar, "from_sea"))
					{
						link.l2 = "Казнить? А могу я на это полюбоваться?";
						link.l2.go = "sell_prisoner_DeathExec";
					} */
				}
				else
				{
					qty = qty / 2;
					attrLoc = StringFromKey("Common_Mayor_468", attrLoc, FindMoneyString(qty));
				}
			}
			dialog.text = attrLoc;
			pchar.PrisonerSellPrice = qty;
			link.l1 = StringFromKey("Common_Mayor_469", GetAddress_FormToNPC(NPChar));
			link.l1.go = "sell_prisoner_3";
			link.l3 = StringFromKey("Common_Mayor_470");
			link.l3.go = "exit";
		break;

		/*case "sell_prisoner_DeathExec":
			dialog.text = "Нет, это исключено!";
			link.l1 = "Ну а, скажем, вклад в казну города даст мне билет на шоу?";
			link.l1.go = "sell_prisoner_DeathExec_1";
			link.l2 = "Ну тогда забирайте его и давайте мои денежки...";
			link.l2.go = "sell_prisoner_3";
		break;

		case "sell_prisoner_DeathExec_1":
			dialog.text = "Хм... Интересная мысль. Что ж, 3000 пиастров - и вас проведут в форт, где состоится казнь. Но учтите: ваша команда может не понять действий капитана, и лояльность сильно упадет.";
			if (sti(pchar.Money) >= 3000)
			{
				link.l1 = "Я согласен. Вот ваш 'вклад'.";
				link.l1.go = "sell_prisoner_DeathExec_2";
			}
			link.l2 = "Нет. Я передумал"+ GetSexPhrase("","а") +".";
			link.l2.go = "exit";
		break;

		case "sell_prisoner_DeathExec_2":
			AddMoneyToCharacter(pchar, -3000);
			offref = characterFromID(pchar.prisonerToSellId);
			DeleteAttribute(offref,"prisoned"); // освободили пленника
			RemovePassenger(pchar, offref);
			offref.location = "";
			OfficersReaction("bad");
			ChangeCharacterReputation(pchar, -5);

			AddCharacterSkill(pchar, SKILL_LEADERSHIP, 0);
			AddCharacterSkill(pchar, SKILL_SNEAK, 0);

			Pchar.GenQuest.Death_Execution_location = NPChar.from_sea;
			DialogExit();
			NextDiag.CurrentNode = "First time";

		break;   */

		case "sell_prisoner_3":
			dialog.text = StringFromKey("Common_Mayor_471");
			link.l1 = StringFromKey("Common_Mayor_472");
			link.l1.go = "exit";
			OfficersReaction("bad");

			offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
			AddMoneyToCharacter(pchar, sti(pchar.PrisonerSellPrice));
			if (sti(offref.nation) == sti(NPChar.nation))
			{
				AddCharacterExpToSkill(pchar, "Commerce", 25);
			}
			else
			{
				if (sti(offref.nation) == PIRATE)
				{
					ChangeCharacterReputation(pchar, -2);
				}
				else
				{
					AddCharacterExpToSkill(pchar, "Commerce", 5);
				}
			}

			offref.location = "";
			ReleasePrisoner(offref); // освободили пленника
		break;
		////   CAPTURE //////////
		case "CAPTURE_Main":
			NextDiag.TempNode = "CAPTURE_Main";
			AfterTownBattle();  // все, все свободны

			// fix от грабежа 5 раз на дню -->
			if (!CheckNPCQuestDate(npchar, "GrabbingTownDate"))
			{
				dialog.Text = StringFromKey("Common_Mayor_473");
				Link.l1 = StringFromKey("Common_Mayor_474", pchar);
				Link.l1.go = "Exit_City";

				NPChar.NoGiveMoney = true;

				ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 20);
				// вернём диалог после разговора и спрячем
				SetReturn_Gover_Dialog_Exit(NPChar);
				break;
			}
			SetNPCQuestDate(npchar, "GrabbingTownDate");
			// fix от грабежа 5 раз на дню <--

			if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)
			{
				// а форт-то ЖИВ, значит с суши прошли
				// evganat - можно вставить отношение сюда
				IncreaseMayorDisposition(-20);
				dialog.Text = StringFromKey("Common_Mayor_475");
				Link.l2 = StringFromKey("Common_Mayor_476");
				Link.l2.go = "Summ";
				Pchar.HalfOfPaymentByCity = true; // токо половина денег
			}
			else
			{
				// evganat - можно вставить отношение сюда
				IncreaseMayorDisposition(-20);
				int iColony = FindColony(npchar.city);
				dialog.Text = StringFromKey("Common_Mayor_477");
				if (!bWorldAlivePause || bBettaTestMode)
				{
					iColony = FindColony(npchar.city);
					if (!CheckAttribute(&colonies[iColony], "notCaptured")) //незахватываемые города
					{
						if (CheckAttribute(FortChref, "Default.Prison"))
						{
							Link.l1 = StringFromKey("Common_Mayor_478");
						}
						else
						{
							Link.l1 = StringFromKey("Common_Mayor_479", pchar);
						}
						Link.l1.go = "City";
					}
				}
				if (!isCityHasFort(NPChar.City))
				{
					Link.l2 = StringFromKey("Common_Mayor_480");
				}
				else
				{
					Link.l2 = StringFromKey("Common_Mayor_481");
				}
				Link.l2.go = "Summ";

				bOk = !bWorldAlivePause || bBettaTestMode;
				if (isMainCharacterPatented() && bOk && !CheckAttribute(&colonies[iColony], "notCaptured")) //не даем захватить колонию
				{
					// восстановим нацию патента
					PChar.nation = GetBaseHeroNation();

					dialog.Text = StringFromKey("Common_Mayor_482", NationNameGenitive(sti(NPChar.nation)));
					Link.l1 = StringFromKey("Common_Mayor_483");
					Link.l1.go = "City_patent";
					Link.l2 = StringFromKey("Common_Mayor_484", NationNameGenitive(sti(PChar.nation)), NationKingsCrown(PChar));
					Link.l2.go = "City_nation";
					Link.l3 = StringFromKey("Common_Mayor_485");
					Link.l3.go = "Summ_patent";
				}
			}
		break;

		case "City":
			ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 40);
			AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 300);

			Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
			AddDialogExitQuest("Residence_Captured_Any");

			Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
			Achievement_AddStats_SturmColonies();
			// ремонт
			RepairAllShips();
			Log_Info(StringFromKey("InfoMessages_138"));
			//  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
			AddQuestRecord("Gen_CityCapture", "t3");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
			NextDiag.CurrentNode = "Prison";
			DialogExit();
		break;

		case "City_patent":
			ChangeCharacterReputation(GetMainCharacter(), -20); // пираты мы, но у нас патент
			dialog.Text = StringFromKey("Common_Mayor_486");
			Link.l1 = StringFromKey("Common_Mayor_487");
			Link.l1.go = "City";
		break;

		case "Exit_for_pay":
			dialog.Text = StringFromKey("Common_Mayor_488");
			Link.l1 = StringFromKey("Common_Mayor_489", pchar);
			Link.l1.go = "exit";

			NextDiag.TempNode = "Exit_for_pay";
		break;

		case "Exit_City":
			NextDiag.CurrentNode = "Exit_for_pay";
			Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
			if (sti(NPChar.NoGiveMoney) == false) // себе берем
			{
				// вернём диалог после разговора и спрячем
				SetReturn_Gover_Dialog_Exit(NPChar);
				AddDialogExitQuestFunction("TWN_ExitForPay");
			}
			DialogExit();
		break;

		case "Summ":
			dialog.Text = StringFromKey("Common_Mayor_490");
			Link.l1 = StringFromKey("Common_Mayor_491");
			Link.l1.go = "Exit_City";
			NPChar.NoGiveMoney = false;

			ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 30);
			AddCharacterExpToSkill(GetMainCharacter(), SKILL_FORTUNE, 200);
			AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 200);

			Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			Achievement_AddStats_SturmColonies();
			//  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
			AddQuestRecord("Gen_CityCapture", "t2");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--

			if (NPChar.City == "Villemstad")
			{
				pchar.quest.VillemstadResGatesLock.win_condition.l1 = "MapEnter";
				pchar.quest.VillemstadResGatesLock.function = "VillemstadResGatesLock";
			}
		break;

		case "Summ_patent":
			dialog.Text = StringFromKey("Common_Mayor_492");
			Link.l1 = StringFromKey("Common_Mayor_493");
			Link.l1.go = "Summ";
			ChangeCharacterReputation(GetMainCharacter(), -10); // не на службе
		break;

		case "City_nation":
			dialog.Text = StringFromKey("Common_Mayor_494");
			Link.l1 = StringFromKey("Common_Mayor_495");
			Link.l1.go = "Exit_City";
			NPChar.NoGiveMoney = true;

			ChangeCharacterReputation(GetMainCharacter(), 5);
			AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 500);
			AddCharacterExpToSkill(GetMainCharacter(), "Sneak", 300);
			SetNationRelationBoth(sti(PChar.nation), sti(NPChar.nation), RELATION_ENEMY);

			PChar.questTemp.DontSetNewDialogToMayor = true; // иначе может сменить диалог и сбойнуть
			PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
			SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
			DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
			AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // табличка
			//  СЖ -->
			sTemp = GetNationNameByType(sti(PChar.nation));
			ReOpenQuestHeader("Gen_CityCapture");
			AddQuestRecord("Gen_CityCapture", "t1");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
			//  СЖ <--
			AddTitleNextRate(sti(PChar.nation), 1);  // счетчик звания
			SetCharacterRelationBoth(sti(FortChref.index), GetMainCharacterIndex(), RELATION_FRIEND);// нечего не даёт, тк работает OtherChar - а это губер, но он и так друг
			UpdateRelations();

			// 22.03.05  fix вернём диалог после разговора и спрячем
			//  внутри диалога не работало
			SetReturn_Gover_Dialog_Exit(NPChar);

			/*   TODO
            ref rFortCh = FindSiegeFortCommander();
            if (rFortCh.id == FortChref.id)//это и есть форт обложенный эскадрой
            {
                if (sti(Characters[GetCharacterIndex("NatCapitan_1")].nation) == sti(rFortCh.nation)) //они этой же нации
                {
                    AddDialogExitQuest("CheckFortsEndSiege_02");
                }
            }
			  */
			Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
			Achievement_AddStats_SturmColonies();

			if (NPChar.City == "Villemstad")
			{
				pchar.quest.VillemstadResGatesLock.win_condition.l1 = "MapEnter";
				pchar.quest.VillemstadResGatesLock.function = "VillemstadResGatesLock";
			}
		break;

		case "Prison":
			dialog.Text = StringFromKey("Common_Mayor_496", pchar);
			/*Link.l1 = "Не дерзи мне, жирная скотина.";
			Link.l1.go = "Strike";
			if (!CheckAttribute(NPChar, "NotHaveFort"))
			{
			    Link.l2 = "За оказанное ранее сопротивление я решил вас расстрелять.";
			    Link.l2.go = "Death_Execution_1";
            }       */
			Link.l3 = StringFromKey("Common_Mayor_497", pchar);
			Link.l3.go = "exit";
			NextDiag.TempNode = "Prison";
		break;

		case "arestFree_1":
			dialog.text = StringFromKey("Common_Mayor_498");
			link.l1 = StringFromKey("Common_Mayor_499", FindMoneyString(CharacterHunterRedemp(Pchar, NationShortName(sti(NPChar.nation)))));
			link.l1.go = "arestFree_2";
			link.l2 = StringFromKey("Common_Mayor_500");
			link.l2.go = "arest_1";
		break;

		case "arestFree_2":
		//            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= rand(7))
			if (PlayerRPGCheck_Skill(SKILL_FORTUNE, rand(7) * 10, false))
			{
				dialog.text = StringFromKey("Common_Mayor_501");
				link.l1 = StringFromKey("Common_Mayor_502");
				link.l1.go = "Exit";
				AddMoneyToCharacter(pchar, -CharacterHunterRedemp(Pchar, NationShortName(sti(NPChar.nation))));
				ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
			}
			else
			{
				dialog.text = StringFromKey("Common_Mayor_503", pchar);
				link.l1 = StringFromKey("Common_Mayor_504");
				link.l1.go = "arest_2";
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 10);
			}
		break;

		case "arest_1":
			dialog.text = StringFromKey("Common_Mayor_505", pchar);
			//link.l1 = "Постойте!";
			//link.l1.go = "arest_2";
			link.l1 = StringFromKey("Common_Mayor_506");
			link.l1.go = "fight";
		break;

		case "arest_2":
			dialog.text = StringFromKey("Common_Mayor_507");
			link.l1 = StringFromKey("Common_Mayor_508");
			link.l1.go = "fight";
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Уничтожение банды
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "DestroyGang":
			dialog.text = StringFromKey("Common_Mayor_509", FindDaysString(sti(pchar.GenQuest.DestroyGang.Terms)), FindMoneyString(sti(pchar.GenQuest.DestroyGang.Money)));
			link.l1 = StringFromKey("Common_Mayor_510");
			link.l1.go = "DestroyGang_agree";
			link.l2 = StringFromKey("Common_Mayor_511");
			link.l2.go = "All_disagree";
		break;
		case "DestroyGang_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.questName = "DestroyGang"; //тип квеста
			pchar.GenQuest.DestroyGang.Location = GetGangLocation(npchar); //определяем локацию,где банда
			pchar.GenQuest.DestroyGang.MayorId = npchar.id; //Id мэра, чтобы знать, кто дал квест
			if (pchar.GenQuest.DestroyGang.Location == "none") //на всякий случай
			{
				dialog.text = StringFromKey("Common_Mayor_512");
				link.l1 = StringFromKey("Common_Mayor_513");
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
			else
			{
				dialog.text = StringFromKey("Common_Mayor_514");
				link.l1 = StringFromKey("Common_Mayor_515", GetAddress_FormToNPC(NPChar));
				link.l1.go = "exit";
				pchar.quest.DestroyGang.win_condition.l1 = "location";
				pchar.quest.DestroyGang.win_condition.l1.location = pchar.GenQuest.DestroyGang.Location;
				pchar.quest.DestroyGang.win_condition = "DestroyGang_fight";
				pchar.quest.DestroyGang.again = true; //тупо дожидаться своего часа бандиты не будут
				SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.DestroyGang.Terms), false);
				//==> энкаунтеров в квестовой локации не будет 
				locations[FindLocation(pchar.GenQuest.DestroyGang.Location)].DisableEncounters = true;
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "1");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				makearef(arName, pchar.GenQuest.DestroyGang);
				AddQuestUserData("MayorsQuestsList", "GangName", GetFullName(arName));
				AddQuestUserData("MayorsQuestsList", "sDay", FindDaysString(sti(pchar.GenQuest.DestroyGang.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindMoneyString(sti(pchar.GenQuest.DestroyGang.Money)));
			}
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Поиски лазутчика
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "SeekSpy":
			dialog.text = StringFromKey("Common_Mayor_516", FindDaysString(sti(pchar.GenQuest.SeekSpy.Terms)), FindMoneyString(sti(pchar.GenQuest.SeekSpy.Money)));
			link.l1 = StringFromKey("Common_Mayor_517");
			link.l1.go = "SeekSpy_agree";
			link.l2 = StringFromKey("Common_Mayor_518");
			link.l2.go = "All_disagree";
		break;
		case "SeekSpy_agree":
			if (rand(1))
			{
				//шпион в одной из общих локаций common
				pchar.GenQuest.SeekSpy.Location = GetRandomCommonLoc(npchar); //определяем локацию
				Log_QuestInfo(pchar.GenQuest.SeekSpy.Location); //чит
				if (pchar.GenQuest.SeekSpy.Location == "none") //на всякий случай
				{
					dialog.text = StringFromKey("Common_Mayor_519");
					link.l1 = StringFromKey("Common_Mayor_520");
					link.l1.go = "exit";
					DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
					break;
				}
				else
				{
					pchar.quest.SeekSpy_login.again = true; //на всякий случай
				}
			}
			else
			{
				//шпион гуляет по городу
				pchar.GenQuest.SeekSpy.Location = npchar.city + "_town"; //определяем локацию
				pchar.GenQuest.SeekSpy.City = rand(1); //флаг шпион в городе, ренд - кто будет подсказывать в таверне
			}
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.questName = "SeekSpy"; //тип квеста
			dialog.text = StringFromKey("Common_Mayor_521");
			link.l1 = StringFromKey("Common_Mayor_522", GetAddress_FormToNPC(NPChar));
			link.l1.go = "exit";
			pchar.GenQuest.SeekSpy.MayorId = npchar.id; //Id мэра, чтобы знать, кто дал квест
			pchar.quest.SeekSpy.win_condition.l1 = "location";
			pchar.quest.SeekSpy.win_condition.l1.location = pchar.GenQuest.SeekSpy.Location;
			pchar.quest.SeekSpy.win_condition = "SeekSpy_login";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.SeekSpy.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "3");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sDay", FindDaysString(sti(pchar.GenQuest.SeekSpy.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindMoneyString(sti(pchar.GenQuest.SeekSpy.Money)));
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Проникновение во враждебный город
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "Intelligence":
			dialog.text = StringFromKey("Common_Mayor_523", FindMoneyString(sti(pchar.GenQuest.Intelligence.Money)));
			link.l1 = StringFromKey("Common_Mayor_524");
			link.l1.go = "Intelligence_agree";
			link.l2 = StringFromKey("Common_Mayor_525");
			link.l2.go = "All_disagree";
		break;
		case "Intelligence_agree":
			if (pchar.GenQuest.Intelligence.City == "none" || PlayerRPGCheck_BadReputation(30, false)) //на всякий случай
			{
				dialog.text = StringFromKey("Common_Mayor_526");
				link.l1 = StringFromKey("Common_Mayor_527");
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
			}
			else
			{
				npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
				pchar.GenQuest.questName = "Intelligence"; //тип квеста
				sTemp = pchar.GenQuest.Intelligence.City;
				if (sTemp != "FortOrange") // теперь в Форт Оранж только трейдер во избежание багов Konstrush
				{
					switch (rand(4))
					{
						case 0:    sTemp += "_Priest";     break;
						case 1:    sTemp += "_trader";     break;
						case 2:    sTemp += "_shipyarder"; break;
						case 3:    sTemp += "_usurer";     break;
						case 4:    sTemp += "_PortMan";    break;
					}
				}
				else
				{
					sTemp += "_trader";
				}
				pchar.GenQuest.Intelligence.SpyId = sTemp; //Id нашего шпиона в городе
				dialog.text = StringFromKey("Common_Mayor_528", XI_ConvertString("Colony" + pchar.GenQuest.Intelligence.City + "Pre"), GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen"), GetFullName(&characters[GetCharacterIndex(sTemp)]), FindDaysString(sti(pchar.GenQuest.Intelligence.Terms)));
				link.l1 = StringFromKey("Common_Mayor_529", pchar, GetAddress_FormToNPC(NPChar));
				link.l1.go = "exit";
				pchar.GenQuest.Intelligence.MayorId = npchar.id; //Id мэра, чтобы знать, кто дал квест
				SaveCurrentQuestDateParam("GenQuest.Intelligence"); //запись даты получения квеста
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "6");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Intelligence.City + "Acc"));
				AddQuestUserData("MayorsQuestsList", "sIsland", XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable + "Pre"));
				AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen"));
				AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(sTemp)]));
				AddQuestUserData("MayorsQuestsList", "sDay", FindDaysString(sti(pchar.GenQuest.Intelligence.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindMoneyString(sti(pchar.GenQuest.Intelligence.Money)));
				AddQuestUserData("MayorsQuestsList", "sCity2", XI_ConvertString("Colony" + pchar.GenQuest.Intelligence.City + "Pre"));
			}
		break;
		case "Intelligence_ExecuteLate":
			QuestName = pchar.GenQuest.questName;
			pchar.GenQuest.(QuestName).Money = sti(pchar.GenQuest.(QuestName).Money) / 2;
			dialog.text = StringFromKey("Common_Mayor_532", RandPhraseSimple(
						StringFromKey("Common_Mayor_530", FindMoneyString(sti(pchar.GenQuest.(QuestName).Money))),
						StringFromKey("Common_Mayor_531", FindMoneyString(sti(pchar.GenQuest.(QuestName).Money)))));
			link.l1 = StringFromKey("Common_Mayor_533", pchar, GetAddress_FormToNPC(NPChar));
			link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(
						StringFromKey("Common_Mayor_536", RandPhraseSimple(
								StringFromKey("Common_Mayor_534", GetFullName(npchar), GetMainCharacterNameGen()),
								StringFromKey("Common_Mayor_535", pchar, GetFullName(npchar), GetMainCharacterNameDat()))), sti(npchar.nation), 5, 1);
		//<-- слухи
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Уничтожение контры
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "KillSmugglers":
			pchar.GenQuest.questName = "KillSmugglers"; //тип квеста
			pchar.GenQuest.KillSmugglers.Terms = rand(2) + 1; //сроки выполнения задания
			pchar.GenQuest.KillSmugglers.Money = ((rand(8) + 2) * 200) + (sti(pchar.rank) * 200); //вознаграждение
			dialog.text = StringFromKey("Common_Mayor_537", FindDaysString(sti(pchar.GenQuest.KillSmugglers.Terms)), FindMoneyString(sti(pchar.GenQuest.KillSmugglers.Money)));
			link.l1 = StringFromKey("Common_Mayor_538", GetAddress_FormToNPC(NPChar));
			link.l1.go = "KillSmugglers_agree";
			link.l2 = StringFromKey("Common_Mayor_539");
			link.l2.go = "All_disagree";
		break;
		case "KillSmugglers_agree":
			dialog.text = StringFromKey("Common_Mayor_540");
			link.l1 = StringFromKey("Common_Mayor_541", GetAddress_FormToNPC(NPChar));
			link.l1.go = "exit";
			pchar.GenQuest.KillSmugglers.MayorId = npchar.id; //Id мэра, чтобы знать, кто дал квест
			pchar.GenQuest.KillSmugglers.Areal = GetArealByCityName(npchar.city); //ареал, где нужно поработать
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				sld = &characters[i];
				if (sld.id == "Rand_Smug01" && pchar.GenQuest.KillSmugglers.Areal == GetArealByLocation(&locations[FindLocation(sld.location)]))
				{
					pchar.quest.KillSmugglers.win_condition.l1 = "NPC_Death";
					pchar.quest.KillSmugglers.win_condition.l1.character = "Rand_Smug01";
					pchar.quest.KillSmugglers.win_condition.l2 = "NPC_Death";
					pchar.quest.KillSmugglers.win_condition.l2.character = "Rand_Smug02";
					pchar.quest.KillSmugglers.win_condition.l3 = "NPC_Death";
					pchar.quest.KillSmugglers.win_condition.l3.character = "Rand_Smug03";
					pchar.quest.KillSmugglers.win_condition = "KillSmugglers_after";
					break;
				}
			}
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.KillSmugglers.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "8");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sDay", FindDaysString(sti(pchar.GenQuest.KillSmugglers.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindMoneyString(sti(pchar.GenQuest.KillSmugglers.Money)));
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Поиск и уничтожение пирата
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "DestroyPirate":
			pchar.GenQuest.questName = "DestroyPirate"; //тип квеста
			pchar.GenQuest.DestroyPirate.Terms = idRand(npchar.id + "DestroyPirate", 3) + (15 - MOD_SKILL_ENEMY_RATE); //сроки выполнения задания
			pchar.GenQuest.DestroyPirate.Money = ((idRand(npchar.id + "DestroyPirate", 5) + 5) * 500) + (sti(pchar.rank) * 200); //вознаграждение
			sld = characterFromId("MQPirate");
			dialog.text = StringFromKey("Common_Mayor_542", XI_ConvertString("Colony" + npchar.city + "Gen"), FindDaysString(sti(pchar.GenQuest.DestroyPirate.Terms)), FindMoneyString(sti(pchar.GenQuest.DestroyPirate.Money)));
			link.l1 = StringFromKey("Common_Mayor_543", GetAddress_FormToNPC(NPChar));
			link.l1.go = "DestroyPirate_agree";
			link.l2 = StringFromKey("Common_Mayor_544");
			link.l2.go = "All_disagree";
		break;
		case "DestroyPirate_agree":
			dialog.text = StringFromKey("Common_Mayor_545");
			link.l1 = StringFromKey("Common_Mayor_546", GetAddress_FormToNPC(NPChar));
			link.l1.go = "exit";
			pchar.GenQuest.DestroyPirate.MayorId = npchar.id; //Id мэра, чтобы знать, кто дал квест
			pchar.GenQuest.DestroyPirate.Areal = GetArealByCityName(npchar.city); //ареал, куда будем ставить пирата
			AddDialogExitQuest("DestroyPirate_Begin");
		break;
		// -------------- общий набор для всех квестов мэра ------------------
		case "All_disagree":
			dialog.text = StringFromKey("Common_Mayor_547");
			link.l1 = StringFromKey("Common_Mayor_548", GetAddress_FormToNPC(NPChar));
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -2);

			if (CheckAttribute(pchar, "GenQuest.questName"))
			{
				QuestName = pchar.GenQuest.questName;
				DeleteAttribute(pchar, "GenQuest." + QuestName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
		break;
		case "All_Late":
			QuestName = pchar.GenQuest.questName;
			dialog.text = StringFromKey("Common_Mayor_551", RandPhraseSimple(
						StringFromKey("Common_Mayor_549"),
						StringFromKey("Common_Mayor_550")));
			link.l1 = StringFromKey("Common_Mayor_552", pchar, GetAddress_FormToNPC(NPChar));
			link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(
						StringFromKey("Common_Mayor_556", LinkRandPhrase(
								StringFromKey("Common_Mayor_553", GetFullName(npchar), GetMainCharacterNameDat()),
								StringFromKey("Common_Mayor_554", GetFullName(npchar), GetFullName(pchar)),
								StringFromKey("Common_Mayor_555", GetFullName(npchar), GetFullName(pchar)))), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterReputation(pchar, -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу ещё один не даем
			CloseQuestHeader("MayorsQuestsList");
		break;
		case "All_Found":
			QuestName = pchar.GenQuest.questName;
			dialog.text = StringFromKey("Common_Mayor_559", RandPhraseSimple(
						StringFromKey("Common_Mayor_557"),
						StringFromKey("Common_Mayor_558")));
			link.l1 = StringFromKey("Common_Mayor_560", GetAddress_FormToNPC(NPChar));
			link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(
						StringFromKey("Common_Mayor_564", LinkRandPhrase(
								StringFromKey("Common_Mayor_561", pchar, GetFullName(npchar), GetMainCharacterNameDat()),
								StringFromKey("Common_Mayor_562", pchar, GetFullName(npchar), GetFullName(pchar)),
								StringFromKey("Common_Mayor_563", pchar, GetFullName(npchar), GetFullName(pchar)))), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterReputation(pchar, -6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу ещё один не даем
			CloseQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "21");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		break;
		case "All_Execute":
			QuestName = pchar.GenQuest.questName;
			dialog.text = StringFromKey("Common_Mayor_567", RandPhraseSimple(
						StringFromKey("Common_Mayor_565", FindMoneyString(sti(pchar.GenQuest.(QuestName).Money))),
						StringFromKey("Common_Mayor_566", FindMoneyString(sti(pchar.GenQuest.(QuestName).Money)))));
			link.l1 = StringFromKey("Common_Mayor_570", pchar, GetAddress_FormToNPC(NPChar), RandPhraseSimple(
						StringFromKey("Common_Mayor_568"),
						StringFromKey("Common_Mayor_569", pchar)));
			link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(
						StringFromKey("Common_Mayor_574", LinkRandPhrase(
								StringFromKey("Common_Mayor_571", pchar, GetFullName(npchar), GetMainCharacterNameGen()),
								StringFromKey("Common_Mayor_572", pchar, GetFullName(npchar), GetMainCharacterNameGen()),
								StringFromKey("Common_Mayor_573", GetFullName(npchar), GetFullName(pchar)))), sti(npchar.nation), 5, 1);
		//<-- слухи
		break;
		case "All_Execute_1":
			QuestName = pchar.GenQuest.questName;
			dialog.text = StringFromKey("Common_Mayor_577", RandPhraseSimple(
						StringFromKey("Common_Mayor_575"),
						StringFromKey("Common_Mayor_576")));
			link.l1 = StringFromKey("Common_Mayor_580", RandPhraseSimple(
						StringFromKey("Common_Mayor_578"),
						StringFromKey("Common_Mayor_579")));
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.(QuestName).Money));
			CloseQuestHeader("MayorsQuestsList");
			ChangeCharacterReputation(pchar, 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(PChar, "Leadership", 50);
			OfficersReaction("good");

			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу ещё один не даем
			// инкремент в базу заданий мэров
			sTemp = npchar.City;
			if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp)) pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
			pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1;
		break;
		//<-- осады homo
		case "siege_task":
			makearef(aData, NullCharacter.Siege);
			aData.HelpColony = true;
			dialog.text = StringFromKey("Common_Mayor_581");
			link.l1 = StringFromKey("Common_Mayor_582");
			link.l1.go = "exit";
		break;
		//  boal из ВМЛ -->
		case "GhostShipDone":
			SaveCurrentNpcQuestDateParam(npchar, "GhostShipHelp");

			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddMoneyToCharacter(pchar, 5000 + rand(10) * 1000);
			ChangeCharacterReputation(pchar, 4);
			ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -20);
			sTemp = npchar.City;
			if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp)) pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
			pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1;

			OfficersReaction("good");
			DeleteAttribute(pchar, "GenQuest.GhostShipWorkId");
			DeleteAttribute(pchar, "GenQuest.GhostShipDone_" + NPChar.id);
			SetCurrentQuestMark(npchar);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

		break;

		case "GhostShipHelp_1":
			SaveCurrentNpcQuestDateParam(npchar, "GhostShipHelp");
			pchar.GenQuest.GhostShipWorkId = NPChar.id;

			bDisableFastReload = true;

			SetLocationCapturedState(NPChar.Default, true);

			Pchar.quest.GhostShipHelp.win_condition.l1 = "location";
			Pchar.quest.GhostShipHelp.win_condition.l1.location = NPChar.from_sea;
			Pchar.quest.GhostShipHelp.win_condition = "GhostShipHelp";

			Pchar.GenQuest.Hunter2Pause = true;

			ReOpenQuestHeader("GhostShipQuest");
			AddQuestRecord("GhostShipQuest", "help_t1");
			AddQuestUserData("GhostShipQuest", "sCity", GetCityName(npchar.City));
			SetCurrentQuestMark(npchar);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// "Правосудие на продажу" (Warship, Rosarak)
		case "JusticeOnSale_1":
			dialog.text = StringFromKey("Common_Mayor_583", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Common_Mayor_584", pchar);
			link.l1.go = "JusticeOnSale_4";
			link.l2 = StringFromKey("Common_Mayor_585", pchar);
			link.l2.go = "JusticeOnSale_2";
		break;

		case "JusticeOnSale_2":
			dialog.text = StringFromKey("Common_Mayor_586");
			link.l1 = StringFromKey("Common_Mayor_587");
			link.l1.go = "JusticeOnSale_3";
		break;

		case "JusticeOnSale_3":
			IncreaseMayorDisposition(2);
			ChangeCharacterReputation(pchar, 2);
			AddMoneyToCharacter(PChar, 1000 + sti(PChar.rank) * 30 * idRand(npchar.id + "JusticeOnSale", 10));
			ChangeContrabandRelation(pchar, -20);
			AddQuestRecord("JusticeOnSale", "5");
			AddQuestUserData("JusticeOnSale", "sSex", GetSexPhrase("", "а"));
			JusticeOnSale_QuestEnd();

			DialogExit();
		break;

		case "JusticeOnSale_4":
			dialog.text = StringFromKey("Common_Mayor_588", pchar.name, XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Acc"));
			link.l1 = StringFromKey("Common_Mayor_589");
			link.l1.go = "JusticeOnSale_5";
		break;

		case "JusticeOnSale_5":
			dialog.text = StringFromKey("Common_Mayor_590");
			link.l1 = StringFromKey("Common_Mayor_591");
			link.l1.go = "JusticeOnSale_6";
		break;

		case "JusticeOnSale_6":
			sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
			sld.DisableEncounters = true;

			ChangeContrabandRelation(pchar, -10); //За донос
			JusticeOnSale_DeleteCaptain();

			AddQuestRecord("JusticeOnSale", "5_1");
			AddQuestUserData("JusticeOnSale", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("JusticeOnSale", "cityName", XI_ConvertString("Colony" + PChar.GenQuest.JusticeOnSale.CityId + "Gen"));

			PChar.GenQuest.JusticeOnSale.MayorQuest = true;
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.win_condition.l1 = "location";
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.function = "JusticeOnSale_ShoreEnterFromMayor";

			DialogExit();
		break;

		case "JusticeOnSale_7":
			IncreaseMayorDisposition(5);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
			DeleteAttribute(NPChar, "JusticeOnSalePrize");
			AddMoneyToCharacter(PChar, sti(PChar.rank) * 300 + idRand(npchar.id + "JusticeOnSale", 1000));
			CloseQuestHeader("JusticeOnSale");
			sTemp = npchar.city;
			if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp)) pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
			pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1; //считается как задание
			dialog.text = StringFromKey("Common_Mayor_592");
			link.l1 = StringFromKey("Common_Mayor_593");
			link.l1.go = "exit";
		break;
		//<-- Правосудие на продажу

		// Квест Шарпа
		case "Exit_Sell_Sharp_Prisoner":
			IncreaseMayorDisposition(10);
			if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp)) pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
			pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1; // Повысим расположение губера

			AddDialogExitQuestFunction("SeaPearl_SharpPrisoner_BetraySharpToSpainMayor");

			DialogExit();
		break;
		//<-- Квест Шарпа

		// evganat - энциклопедия
		case "Encyclopedia_FirstTime":
			dialog.text = StringFromKey("Common_Mayor_594");
			link.l1 = StringFromKey("Common_Mayor_595");
			link.l1.go = "Encyclopedia_FT2";
		break;

		case "Encyclopedia_FT2":
			if (CheckRandomPage("governor", npchar.city, sti(npchar.nation)))
			{
				npchar.encyclopedia.tome = GetRandomTome();
				npchar.encyclopedia.page = 4;
				dialog.text = StringFromKey("Common_Mayor_596");
				link.l1 = StringFromKey("Common_Mayor_597");
				link.l1.go = "Encyclopedia_Price";
			}
			else
			{
				SaveCurrentNpcQuestDateParam(npchar, "encyclopedia.last_date");
				dialog.text = StringFromKey("Common_Mayor_598");
				link.l1 = StringFromKey("Common_Mayor_599");
				link.l1.go = "exit";
			}
		break;

		case "Encyclopedia_Price":
			bool bDispG = (GetMayorDisposition() >= 10);    // отношение
			bool bRepG = (sti(pchar.reputation) > 70);        // репутация "человек чести" и выше
			bool bRepB = (sti(pchar.reputation) <= 40);        // репутация "мошенник" и ниже
			bool bLeadG = (GetCharacterSkill(pchar, SKILL_LEADERSHIP) >= 50);    // лидерство
			bool bLeadB = (GetCharacterSkill(pchar, SKILL_LEADERSHIP) <= 20);
			//			bool bNatG = (ChangeCharacterNationReputation(pchar, sti(npchar.nation), 0) > 50);	// отношение отличное и выше
			bool bNatG = (GetCharacterReputation_WithNation(pchar, sti(npchar.nation)) > 50);    // отношение отличное и выше
			int iScore = bDispG + bRepG - bRepB + bLeadG - bLeadB + bNatG;
			if (bRepB)
			{
				PlayerRPGCheck_Reputation_NotifyFail("good");
			}
			if (bLeadB)
			{
				PlayerRPGCheck_Skill_NotifyFail(SKILL_LEADERSHIP, false);
			}

			int iPrice;
			if (iScore == 4)    // всё идеально, бесплатно
			{
				iPrice = 0;
				dialog.text = StringFromKey("Common_Mayor_600", pchar);
				link.l1 = StringFromKey("Common_Mayor_601", pchar);
				link.l1.go = "Encyclopedia_AddPage";
				break;
			}

			if (iScore >= 0)    // так себе, по минимуму, цена 12000
			{
				iPrice = 12000;
				dialog.text = StringFromKey("Common_Mayor_602", FindMoneyString(iPrice));
			}

			if (iScore >= 2)    // неидеально, но плюсов больше, цена 4000
			{
				iPrice = 4000;
				dialog.text = StringFromKey("Common_Mayor_603", FindMoneyString(iPrice));
			}

			if (iScore < 0)    // ужас, 36000
			{
				iPrice = 36000;
				dialog.text = StringFromKey("Common_Mayor_604", FindMoneyString(iPrice));
			}
			npchar.encyclopedia.curPrice = iPrice;
			if (sti(pchar.money) >= iPrice)
			{
				link.l1 = StringFromKey("Common_Mayor_605");
				link.l1.go = "Encyclopedia_Buy";
			}
			link.l2 = StringFromKey("Common_Mayor_606");
			link.l2.go = "exit";
		break;

		case "Encyclopedia_Buy":
			AddMoneyToCharacter(pchar, -sti(npchar.encyclopedia.curPrice));
			DeleteAttribute(npchar, "encyclopedia.curPrice");
			dialog.text = StringFromKey("Common_Mayor_607");
			link.l1 = StringFromKey("Common_Mayor_608");
			link.l1.go = "Encyclopedia_AddPage";
		break;

		case "Encyclopedia_AddPage":
			GetPage(npchar.encyclopedia.tome, sti(npchar.encyclopedia.page));
			DeleteAttribute(npchar, "encyclopedia.tome");
			DeleteAttribute(npchar, "encyclopedia.page");
			SaveCurrentNpcQuestDateParam(npchar, "encyclopedia.last_date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Encyclopedia_Return":
			dialog.text = StringFromKey("Common_Mayor_609", FindMoneyString(sti(npchar.encyclopedia.curPrice)));
			if (sti(pchar.money) >= sti(npchar.encyclopedia.curPrice))
			{
				link.l1 = StringFromKey("Common_Mayor_610");
				link.l1.go = "Encyclopedia_Buy";
			}
			link.l2 = StringFromKey("Common_Mayor_611");
			link.l2.go = "exit";
		break;

		case "Encyclopedia_Check":
			if (CheckAttribute(pchar, "encyclopedia.gen.governor.colonies." + npchar.city) && sti(pchar.encyclopedia.gen.governor.colonies) < 6)
			{
				dialog.text = StringFromKey("Common_Mayor_612");
				link.l1 = StringFromKey("Common_Mayor_613");
				link.l1.go = "exit";
				break;
			}

			if (GetNpcQuestPastDayParam(npchar, "encyclopedia.last_date") < 7)
			{
				dialog.text = StringFromKey("Common_Mayor_614");
				link.l1 = StringFromKey("Common_Mayor_615", pchar);
				link.l1.go = "exit";
			}
			else
			{
				if (CheckRandomPage("governor", npchar.city, sti(npchar.nation)))
				{
					npchar.encyclopedia.tome = GetRandomTome();
					npchar.encyclopedia.page = 4;
					dialog.text = StringFromKey("Common_Mayor_616");
					link.l1 = StringFromKey("Common_Mayor_617", pchar);
					link.l1.go = "Encyclopedia_Price";
				}
				else
				{
					SaveCurrentNpcQuestDateParam(npchar, "encyclopedia.last_date");
					dialog.text = StringFromKey("Common_Mayor_618");
					link.l1 = StringFromKey("Common_Mayor_619");
					link.l1.go = "exit";
				}
			}
		break;
	}
}

string GetGangLocation(ref npchar)
{
	int n;
	string sAreal = GetRealmByCityName(npchar.city);
	string LocationId;
	string LocationType;
	int storeArray[MAX_LOCATIONS];
	int howStore = 0;

	for (n = 0; n < MAX_LOCATIONS; n++)
	{
		if (GetRealmByLocation(&locations[n]) == sAreal)
		{
			// На всякий случай
			if (CheckAttribute(&locations[n], "DisableEncounters")) continue;
			if (!CheckAttribute(&locations[n], "type")) continue;
			LocationType = locations[n].type;
			if (LocationType != "jungle" && LocationType != "seashore")
			{
				continue;
			}
			LocationId = locations[n].id;
			if (HasStrEx(LocationId, "jungle,Shore,CaveEntrance", "|"))
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	n = storeArray[dRand(howStore - 1)];
	return locations[n].id;
}

string GetSpyColony(ref NPChar)
{
	int storeArray[MAX_COLONIES];
	int howStore = 0;
	string sChrId;

	for (int n = 0; n < MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetRelation2BaseNation(sti(colonies[n].nation)) == RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != npchar.City && colonies[n].nation != npchar.nation)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[Rand(howStore - 1)]].id;
}

// evganat - отношение губернатора
void IncreaseMayorDisposition(int add)
{
	IncreaseNPCDisposition(CharacterRef, add);
}

int GetMayorDisposition()
{
	return GetNPCDisposition(CharacterRef);
}

/*
	Отношение:
	+4 успех в поводе для спешки
	-10 провал в поводе для спешки
	-5 провал в поручении капитана
	+5 успех в поручении капитана
	-10 провал в кораблекрушенцах
	-4 провал в поисках кольца
	+4 успех в поисках кольца
	-4 банда, опоздание
	-3 банда, провал
	+3 банда, успех
	-3 лазутчик, провал
	+2 лазутчик, успех
	-5 проникновение, провал
	+5 проникновение, успех
	-4 контрабандисты, провал
	+4 контрабандисты, успех
	-4 пират, опоздание
	-3 пират, провал
	+4 пират, успех
	-20 захват города
	+1 донос на тёмную личность
	+2 правосудие на продажу, донос
	+5 правосудие на продажу, уничтожение
	-3 правосудие на продажу, провал
	-5 правосудие на продажу, опоздание
	
	Нужно от 6
*/
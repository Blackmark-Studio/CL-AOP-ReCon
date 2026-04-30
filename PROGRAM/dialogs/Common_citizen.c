// boal 25/04/04 общий диалог горожан
#include "DIALOGS\Rumours\Simple_rumors.c"  //homo 25/06/06

string AppealThirdPerson(ref r3rdChar, ref rChar)
{
	if (r3rdChar.sex == "woman")
	{
		return GetFullName(r3rdChar);
	}
	else
	{
		return GetAddress_FormToNPC(rChar) + " " + r3rdChar.lastname;
	}
}

void ProcessDialogEvent()
{
	ref NPChar, sld;
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
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
	int iTest, iTemp, i;
	iTest = FindColony(NPChar.City); // город
	ref rColony;
	string sTemp, sCity, sTitle;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}

	string attrLoc = Dialog.CurrentNode;

	if (HasSubStr(attrLoc, "RumourAboutOwners_"))
	{
		NPChar.RumourOwnerType = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "RumourAboutOwners_TakeRumour";
	}

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
					dialog.text = StringFromKey("Common_citizen_3", RandPhraseSimple(
								StringFromKey("Common_citizen_1", pchar, GetAddress_Form(NPChar)),
								StringFromKey("Common_citizen_2", pchar)));
					link.l1 = StringFromKey("Common_citizen_6", RandPhraseSimple(
								StringFromKey("Common_citizen_4", pchar),
								StringFromKey("Common_citizen_5")));
					link.l1.go = "exit";
					link.l2 = StringFromKey("Common_citizen_9", RandPhraseSimple(
								StringFromKey("Common_citizen_7"),
								StringFromKey("Common_citizen_8")));
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
					{
						if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
						{
							link.l3 = StringFromKey("Common_citizen_12", RandPhraseSimple(
										StringFromKey("Common_citizen_10"),
										StringFromKey("Common_citizen_11")));
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{
					// пираты, не наши
					dialog.text = StringFromKey("Common_citizen_15", RandPhraseSimple(
								StringFromKey("Common_citizen_13"),
								StringFromKey("Common_citizen_14")));
					link.l1 = StringFromKey("Common_citizen_18", RandPhraseSimple(
								StringFromKey("Common_citizen_16"),
								StringFromKey("Common_citizen_17")));
					link.l1.go = "exit";
					link.l2 = StringFromKey("Common_citizen_21", RandPhraseSimple(
								StringFromKey("Common_citizen_19"),
								StringFromKey("Common_citizen_20")));
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
					{
						if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
						{
							link.l3 = StringFromKey("Common_citizen_24", RandPhraseSimple(
										StringFromKey("Common_citizen_22"),
										StringFromKey("Common_citizen_23")));
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
			}
			if (NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";

				if (CheckShipMooredInColony(rColony) && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Townpassenger") && sti(RealShips[sti(Pchar.Ship.Type)].Class) != 7) //горожанин-пассажир
				{
					dialog.text = StringFromKey("Common_citizen_25", GetAddress_Form(NPChar));
					link.l1 = StringFromKey("Common_citizen_26", GetAddress_FormToNPC(NPChar));
					link.l1.go = "passenger";
					link.l2 = StringFromKey("Common_citizen_27", GetAddress_FormToNPC(NPChar));
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}

				// homo 05/08/06
				dialog.Text = NPCharRepPhrase(npchar,
						StringFromKey("Common_citizen_34", LinkRandPhrase(
								StringFromKey("Common_citizen_28"),
								StringFromKey("Common_citizen_29"),
								StringFromKey("Common_citizen_30")), GetFullName(npchar), LinkRandPhrase(
								StringFromKey("Common_citizen_31"),
								StringFromKey("Common_citizen_32", npchar, pchar),
								StringFromKey("Common_citizen_33"))),
						StringFromKey("Common_citizen_38", LinkRandPhrase(
								StringFromKey("Common_citizen_35", GetAddress_Form(NPChar), GetFullName(npchar)),
								StringFromKey("Common_citizen_36", GetAddress_Form(NPChar), GetFullName(npchar)),
								StringFromKey("Common_citizen_37", GetAddress_Form(NPChar), GetFullName(npchar)))));

				Link.l1 = pcharrepphrase(
							StringFromKey("Common_citizen_45", LinkRandPhrase(
									StringFromKey("Common_citizen_39"),
									StringFromKey("Common_citizen_40"),
									StringFromKey("Common_citizen_41")), GetFullName(Pchar), LinkRandPhrase(
									StringFromKey("Common_citizen_42", npchar),
									" " + StringFromKey("Common_citizen_43", pchar),
									" " + StringFromKey("Common_citizen_44"))),
							StringFromKey("Common_citizen_49", LinkRandPhrase(
									StringFromKey("Common_citizen_46", GetFullName(Pchar)),
									StringFromKey("Common_citizen_47", GetFullName(Pchar)),
									StringFromKey("Common_citizen_48", GetFullName(Pchar)))));

				//LinkRandPhrase("Я " + GetFullName(Pchar) + ", капитан.", "Меня зовут " + GetFullName(Pchar) + ".", "Можешь называть меня капитан " + GetFullName(Pchar));
				Link.l1.go = "Meeting";
			}
			else
			{
				if (!CheckAttribute(NPChar, "CitizenFindItem.NoQuest") && rand(5) == 1 && NPChar.sex == "woman" && !CheckAttribute(PChar, "GenQuest.CitizenFindItem.StartQuest") && CheckAttribute(NPChar, "City"))
				{
					dialog.Text = StringFromKey("Common_citizen_50");
					link.l1 = StringFromKey("Common_citizen_54", LinkRandPhrase(
								StringFromKey("Common_citizen_51"),
								StringFromKey("Common_citizen_52"),
								StringFromKey("Common_citizen_53")));
					link.l1.go = "CitizenFindItem_NoQuest";
					link.l2 = StringFromKey("Common_citizen_58", LinkRandPhrase(
								StringFromKey("Common_citizen_55"),
								StringFromKey("Common_citizen_56"),
								StringFromKey("Common_citizen_57")));
					link.l2.go = "CitizenFindItem_1";
					NextDiag.TempNode = "First time";
					break;
				}
				NPChar.CitizenFindItem.NoQuest = true; // Эта девушка квест больше не даст, попытка всего одна

				if (CheckAttribute(PChar, "GenQuest.CitizenFindItem.CitizenID") && PChar.GenQuest.CitizenFindItem.CitizenID == NPChar.ID && CheckCharacterItem(PChar, "WeddingRing"))
				{
					dialog.Text = StringFromKey("Common_citizen_59");
					link.l1 = StringFromKey("Common_citizen_60", pchar, NPChar.name);
					link.l1.go = "CitizenFindItem_Complete_1";
					break;
				}

				link.l1 = PCharRepPhrase(
							StringFromKey("Common_citizen_61", pchar),
							StringFromKey("Common_citizen_62", pchar));
				link.l1.go = "new question";
				link.l2 = StringFromKey("Common_citizen_65", RandPhraseSimple(
							StringFromKey("Common_citizen_63"),
							StringFromKey("Common_citizen_64")));
				if (CheckCharacterItem(pchar, "CaptainBook"))
				{
					if ((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
					}
					else
					{
						link.l2.go = "quests";
					}
				}
				else
				{
					link.l2.go = "quests";//(перессылка в файл города)
				}
				if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
				{
					if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
					{
						link.l3 = StringFromKey("Common_citizen_68", RandPhraseSimple(
									StringFromKey("Common_citizen_66"),
									StringFromKey("Common_citizen_67")));
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
				if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
				{
					link.l4 = StringFromKey("Common_citizen_75", npchar, LinkRandPhrase(
								StringFromKey("Common_citizen_69"),
								StringFromKey("Common_citizen_70"),
								StringFromKey("Common_citizen_71")), LinkRandPhrase(
								StringFromKey("Common_citizen_72", XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city + "Gen")),
								StringFromKey("Common_citizen_73", XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city + "Gen")),
								StringFromKey("Common_citizen_74", characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname)));
					link.l4.go = "SitySpy";
				}
				// <-- квестовый генератор мэра, поиск шпиёна на улице

				// Квестовый генератор священника. Квест №2. Warship -->
				if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
				{
					link.l5 = StringFromKey("Common_citizen_79", LinkRandPhrase(
								StringFromKey("Common_citizen_76"),
								StringFromKey("Common_citizen_77"),
								StringFromKey("Common_citizen_78")));
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.

				dialog.Text = NPCharRepPhrase(npchar,
						PCharRepPhrase(
								StringFromKey("Common_citizen_89", LinkRandPhrase(
										StringFromKey("Common_citizen_80", pchar, GetFullName(Pchar)),
										StringFromKey("Common_citizen_81", pchar, Pchar.name),
										StringFromKey("Common_citizen_82", pchar, GetFullName(Pchar))), LinkRandPhrase(
										StringFromKey("Common_citizen_83"),
										StringFromKey("Common_citizen_84", pchar),
										StringFromKey("Common_citizen_85")), LinkRandPhrase(
										StringFromKey("Common_citizen_86"),
										StringFromKey("Common_citizen_87"),
										StringFromKey("Common_citizen_88"))),
								StringFromKey("Common_citizen_96", LinkRandPhrase(
										StringFromKey("Common_citizen_90", TimeGreeting()),
										StringFromKey("Common_citizen_91", GetAddress_Form(NPChar)),
										StringFromKey("Common_citizen_92")), GetFullName(Pchar), LinkRandPhrase(
										StringFromKey("Common_citizen_93", pchar),
										StringFromKey("Common_citizen_94"),
										StringFromKey("Common_citizen_95")))),
						PCharRepPhrase(
								StringFromKey("Common_citizen_106", LinkRandPhrase(
										StringFromKey("Common_citizen_97"),
										StringFromKey("Common_citizen_98", GetAddress_Form(NPChar)),
										StringFromKey("Common_citizen_99")), GetFullName(Pchar), LinkRandPhrase(
										StringFromKey("Common_citizen_100", npchar),
										StringFromKey("Common_citizen_101", npchar),
										StringFromKey("Common_citizen_102")), LinkRandPhrase(
										StringFromKey("Common_citizen_103"),
										StringFromKey("Common_citizen_104"),
										StringFromKey("Common_citizen_105", npchar))),
								StringFromKey("Common_citizen_110", LinkRandPhrase(
										StringFromKey("Common_citizen_107", TimeGreeting(), GetFullName(Pchar)),
										StringFromKey("Common_citizen_108", pchar, GetFullName(Pchar)),
										StringFromKey("Common_citizen_109", GetAddress_Form(NPChar), Pchar.lastname)))));
				link.l6 = PCharRepPhrase(
							StringFromKey("Common_citizen_113", RandPhraseSimple(
									StringFromKey("Common_citizen_111"),
									StringFromKey("Common_citizen_112", pchar))),
							StringFromKey("Common_citizen_116", RandPhraseSimple(
									StringFromKey("Common_citizen_114"),
									StringFromKey("Common_citizen_115"))));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "FollowGo":
			DialogExit();
			NextDiag.CurrentNode = "FollowDone";
			SetFunctionExitFromLocationCondition("NormalizeRoutedCitizen", pchar.location, false);
			LAi_SetActorType(npchar);
			TEV.CitizenHelpRoutes.follower = npchar.id;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", TEV.CitizenHelpRoutes.name, "FollowDone", -1);
		break;

		case "town":
		//бюргеры не будут показывать дорогу в 80% случаев, обычные граждане в 20%
		//если уже кто-то показывает дорогу и если уже сегодня отказал показывать дорогу так же шанса напроситься на экскурсию нет
			if (StrHasStr(npchar.model, "citiz_11,citiz_12,citiz_13,citiz_14,citiz_15,citiz_16,citiz_17,citiz_18,citiz_19,citiz_20", 1)) iTemp = 8;
			else iTemp = 2;
			if (CheckAttribute(&TEV, "CitizenHelpRoutes.follow_run") || !CheckNPCQuestDate(npchar, "very_busy_for_route") || rand(9) < iTemp)
			{
				SetNPCQuestDate(npchar, "very_busy_for_route");
				dialog.text = StringFromKey("Common_citizen_117");
				link.l1 = StringFromKey("Common_citizen_118");
				link.l1.go = "exit";
				link.l2 = StringFromKey("Common_citizen_119");
				link.l2.go = "new question";
			}
			else
			{
				dialog.text = StringFromKey("Common_citizen_120");
				Link.l1.edit = 3; // TODO ВВОД ТЕКСТА CN - Требует доработки, LocLabels на латинице, а текст может быть и на китайском
				link.l1 = "";
				link.l1.go = "NavigateRouteToThem";
			}
		break;

		case "SeekTown":
			DeleteAttribute(&TEV, "CitizenHelpRoutes");
			dialog.text = StringFromKey("Common_citizen_121");
			Link.l1.edit = 3; // TODO ВВОД ТЕКСТА CN - Требует доработки, LocLabels на латинице, а текст может быть и на китайском
			Link.l1 = "";
			Link.l1.go = "NavigateRouteToThem";
		break;

		case "NavigateRouteToThem":
			if (MakeNavigateRouteToThem())
			{
				dialog.text = StringFromKey("Common_citizen_122", TEV.CitizenHelpRoutes.placeName);
				link.l1 = StringFromKey("Common_citizen_123");
				link.l1.go = "FollowMe";
				link.l2 = StringFromKey("Common_citizen_124");
				link.l2.go = "SeekTown";
				link.l3 = StringFromKey("Common_citizen_125", pchar);
				link.l3.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Common_citizen_126");
				link.l1 = StringFromKey("Common_citizen_127");
				link.l1.go = "SeekTown";
				link.l2 = StringFromKey("Common_citizen_128");
				link.l2.go = "new question";
				link.l3 = StringFromKey("Common_citizen_129");
				link.l3.go = "exit";
			}
		break;

		case "FollowMe":
			dialog.text = StringFromKey("Common_citizen_130");
			link.l1 = StringFromKey("Common_citizen_131");
			link.l1.go = "FollowGo";
			TEV.CitizenHelpRoutes.follow_run = true;
		break;

		case "FollowDone":
			if (CheckAttribute(&TEV, "CitizenHelpRoutes.close_for_night") && TEV.CitizenHelpRoutes.close_for_night && GetTime() > 21.0 && GetTime() < 6.0)
			{
				dialog.text = StringFromKey("Common_citizen_132", TEV.CitizenHelpRoutes.placeName);
				link.l1 = StringFromKey("Common_citizen_133");
				link.l1.go = "FollowDone_1";
				link.l2 = StringFromKey("Common_citizen_134");
				link.l2.go = "new question";
				break;
			}
			if (npchar.location == "Villemstad_town" && TEV.CitizenHelpRoutes.name == "reload33")
				dialog.text = StringFromKey("Common_citizen_135");
			else
				dialog.text = StringFromKey("Common_citizen_136", TEV.CitizenHelpRoutes.placeName);
			link.l1 = StringFromKey("Common_citizen_137");
			link.l1.go = "FollowDone_1";
			link.l2 = StringFromKey("Common_citizen_138");
			link.l2.go = "new question";
		break;

		case "FollowDone_1":
			NormalizeRoutedCitizen("");
			DialogExit();
		break;

		case "ShipLetters_7":
			dialog.text = StringFromKey("Common_citizen_139");
			link.l1 = StringFromKey("Common_citizen_140");
			link.l1.go = "ShipLetters_8";
		break;

		case "ShipLetters_8":
			dialog.text = StringFromKey("Common_citizen_144", LinkRandPhrase(
						StringFromKey("Common_citizen_141"),
						StringFromKey("Common_citizen_142", GetFullName(Pchar)),
						StringFromKey("Common_citizen_143", GetFullName(Pchar))));
			link.l1 = StringFromKey("Common_citizen_145");
			link.l1.go = "exit";
		break;

		case "Meeting":
			dialog.Text = NPCharRepPhrase(npchar,
					StringFromKey("Common_citizen_149", LinkRandPhrase(
							StringFromKey("Common_citizen_146", GetFullName(Pchar)),
							StringFromKey("Common_citizen_147", PChar.name),
							StringFromKey("Common_citizen_148", GetFullName(Pchar)))),
					StringFromKey("Common_citizen_153", LinkRandPhrase(
							StringFromKey("Common_citizen_150", PChar.name),
							StringFromKey("Common_citizen_151", npchar, GetAddress_Form(NPChar), PChar.lastname),
							StringFromKey("Common_citizen_152", PChar.name))));

			link.l1 = PCharRepPhrase(
						StringFromKey("Common_citizen_154", pchar),
						StringFromKey("Common_citizen_155", pchar));
			link.l1.go = "new question";
			Link.l2 = StringFromKey("Common_citizen_158", RandPhraseSimple(
						StringFromKey("Common_citizen_156"),
						StringFromKey("Common_citizen_157")));
			if (CheckCharacterItem(pchar, "CaptainBook"))
			{
				if ((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
				}
				else
				{
					Link.l2.go = "quests";
				}
			}
			else
			{
				link.l2.go = "quests";//(перессылка в файл города)
			}
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
			{
				if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
				{
					link.l3 = StringFromKey("Common_citizen_161", RandPhraseSimple(
								StringFromKey("Common_citizen_159"),
								StringFromKey("Common_citizen_160")));
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
			{
				link.l4 = StringFromKey("Common_citizen_168", npchar, LinkRandPhrase(
							StringFromKey("Common_citizen_162"),
							StringFromKey("Common_citizen_163"),
							StringFromKey("Common_citizen_164")), LinkRandPhrase(
							StringFromKey("Common_citizen_165", XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city + "Gen")),
							StringFromKey("Common_citizen_166", XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city + "Gen")),
							StringFromKey("Common_citizen_167", characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname)));
				link.l4.go = "SitySpy";
			}
			// <-- квестовый генератор мэра, поиск шпиёна на улице
			// Квестовый генератор священника. Квест №2. Warship -->
			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
			{
				link.l5 = StringFromKey("Common_citizen_172", LinkRandPhrase(
							StringFromKey("Common_citizen_169"),
							StringFromKey("Common_citizen_170"),
							StringFromKey("Common_citizen_171")));
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.

			Link.l6 = PCharRepPhrase(
						StringFromKey("Common_citizen_175", RandPhraseSimple(
								StringFromKey("Common_citizen_173"),
								StringFromKey("Common_citizen_174", pchar))),
						StringFromKey("Common_citizen_178", RandPhraseSimple(
								StringFromKey("Common_citizen_176"),
								StringFromKey("Common_citizen_177"))));
			Link.l6.go = "exit";
		break;

		case "new question":
			dialog.text = NPCharRepPhrase(npchar,
					PCharRepPhrase(
							StringFromKey("Common_citizen_182", LinkRandPhrase(
									StringFromKey("Common_citizen_179", npchar),
									StringFromKey("Common_citizen_180"),
									StringFromKey("Common_citizen_181", PChar.name))),
							StringFromKey("Common_citizen_186", LinkRandPhrase(
									StringFromKey("Common_citizen_183"),
									StringFromKey("Common_citizen_184", pchar, PChar.name),
									StringFromKey("Common_citizen_185", pchar)))),
					PCharRepPhrase(
							StringFromKey("Common_citizen_190", LinkRandPhrase(
									StringFromKey("Common_citizen_187", GetAddress_Form(NPChar)),
									StringFromKey("Common_citizen_188"),
									StringFromKey("Common_citizen_189"))),
							StringFromKey("Common_citizen_194", LinkRandPhrase(
									StringFromKey("Common_citizen_191", npchar, GetAddress_Form(NPChar), PChar.lastname),
									StringFromKey("Common_citizen_192", GetAddress_Form(NPChar)),
									StringFromKey("Common_citizen_193")))));

			// homo 25/06/06
			link.l1 = StringFromKey("Common_citizen_198", LinkRandPhrase(
						StringFromKey("Common_citizen_195"),
						StringFromKey("Common_citizen_196"),
						StringFromKey("Common_citizen_197")));
			link.l1.go = "rumours_citizen";
			link.l2 = StringFromKey("Common_citizen_202", LinkRandPhrase(
						StringFromKey("Common_citizen_199"),
						StringFromKey("Common_citizen_200"),
						StringFromKey("Common_citizen_201")));
			link.l2.go = "town";
			if (Rand(1) == 0)
			{
				link.l3 = StringFromKey("Common_citizen_206", LinkRandPhrase(
							StringFromKey("Common_citizen_203"),
							StringFromKey("Common_citizen_204"),
							StringFromKey("Common_citizen_205")));
				if (rand(1) == 0 || PChar.location == "LaVega_Town" || PChar.location == "PuertoPrincipe_town"
				|| PChar.location == "Pirates_town" || PChar.location == "Panama_town" || !CheckAttribute(NPChar, "City"))
				{
					link.l3.go = "info"; //(перессылка в файл города)
				}
				else
				{
					link.l3.go = "RumourAboutOwners"; // Warship. Сделал по-другому - у жителя каждого города будет свой диалог.
				}
			}
			else
			{
				link.l3 = StringFromKey("Common_citizen_207");
				link.l3.go = "colony";
			}
			link.l4 = StringFromKey("Common_citizen_210", RandPhraseSimple(
						StringFromKey("Common_citizen_208"),
						StringFromKey("Common_citizen_209")));
			link.l4.go = "quests";  //(перессылка в файл города)
			link.l5 = PCharRepPhrase(
						StringFromKey("Common_citizen_213", RandPhraseSimple(
								StringFromKey("Common_citizen_211"),
								StringFromKey("Common_citizen_212", pchar))),
						StringFromKey("Common_citizen_216", RandPhraseSimple(
								StringFromKey("Common_citizen_214"),
								StringFromKey("Common_citizen_215"))));
			link.l5.go = "exit";
		break;

		case "RumourAboutOwners":
			Dialog.Text = StringFromKey("Common_citizen_217");
			if (GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = StringFromKey("Common_citizen_218");
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if (GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = StringFromKey("Common_citizen_219");
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if (GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = StringFromKey("Common_citizen_220");
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if (GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = StringFromKey("Common_citizen_221");
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = StringFromKey("Common_citizen_222");
			link.l9.go = "exit";
		break;

		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = StringFromKey("Common_citizen_223");
			link.l1.go = "exit";
			// Здесь можно делать проверка по квестам, какой слух выпал
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
		break;

		case "colony":
			dialog.text = StringFromKey("Common_citizen_227", LinkRandPhrase(
						StringFromKey("Common_citizen_224"),
						StringFromKey("Common_citizen_225"),
						StringFromKey("Common_citizen_226")));
			switch (Rand(1))
			{
				case 0:
					link.l1 = StringFromKey("Common_citizen_228");
					link.l1.go = "colony_town";
				break;

				case 1:
					link.l1 = StringFromKey("Common_citizen_229");
					link.l1.go = "fort";
				break;
			}
			link.l2 = StringFromKey("Common_citizen_230");
			link.l2.go = "new question";
		break;
		// TODO
		case "colony_town":
			dialog.text = StringFromKey("Common_citizen_231", UpperFirst(GetAddress_Form(NPChar)), XI_ConvertString("Colony" + NPChar.City));
			link.l1 = StringFromKey("Common_citizen_232");
			link.l1.go = "exit";
		break;

		case "fort":
			dialog.text = StringFromKey("Common_citizen_233");
			link.l1 = StringFromKey("Common_citizen_234");
			link.l1.go = "exit";
		break;
		//============================ Генератор мэра. Квест по розыску шпиона на улице ============================
		case "SitySpy":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Common_citizen_235", npchar),
						StringFromKey("Common_citizen_236", npchar),
						StringFromKey("Common_citizen_237", npchar),
						StringFromKey("Common_citizen_238", npchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Common_citizen_239"),
						StringFromKey("Common_citizen_240", pchar),
						StringFromKey("Common_citizen_241"),
						StringFromKey("Common_citizen_242"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SitySpy_1", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
			// ==> выбираем подтверждателя
			int num = FindNearCharacters(npchar, 20.0, -1.0, -1.0, 1.0, false, true);
			if (num > 0)
			{
				for (i = 0; i < num; i++)
				{
					iTemp = chrFindNearCharacters[i].index;
					if (CheckAttribute(&characters[iTemp], "CityType") && characters[iTemp].chr_ai.type != LAI_TYPE_CARRY)
					{
						if (characters[iTemp].CityType == "soldier" || characters[iTemp].CityType == "citizen")
						{
							if (!HasSubStr(characters[iTemp].dialog.filename, "Population")) break; //временно отключаем для новых типов; TODO: вернуть после адаптации
						}
					}
				}
				if (!CheckAttribute(&characters[iTemp], "CityType")) chrFindNearCharacters[i].index = -1;
				else if (characters[iTemp].CityType != "soldier" && characters[iTemp].CityType != "citizen") chrFindNearCharacters[i].index = -1; //не нашло
				else if (HasSubStr(characters[iTemp].dialog.filename, "Population")) chrFindNearCharacters[i].index = -1; //временно отключаем для новых типов
				pchar.GenQuest.SeekSpy.Idx = chrFindNearCharacters[i].index; //индекс выбранного
				pchar.GenQuest.SeekSpy.Type = characters[sti(pchar.GenQuest.SeekSpy.Idx)].chr_ai.type; //тип кто помог
				pchar.GenQuest.SeekSpy.BaseIdx = npchar.index; //индекс
			}
		break;
		case "SitySpy_1":
			if (sti(pchar.GenQuest.SeekSpy.Idx) == -1) //на всякий случай
			{
				dialog.text = StringFromKey("Common_citizen_243");
				link.l1 = StringFromKey("Common_citizen_244");
				link.l1.go = "exit";
				break;
			}

			dialog.text = StringFromKey("Common_citizen_247", RandPhraseSimple(
						StringFromKey("Common_citizen_245", &characters[sti(pchar.genquest.seekspy.idx)], UpperFirst(AppealThirdPerson(&characters[sti(pchar.GenQuest.SeekSpy.Idx)], NPChar))),
						StringFromKey("Common_citizen_246", UpperFirst(AppealThirdPerson(&characters[sti(pchar.GenQuest.SeekSpy.Idx)], NPChar)))));
			link.l1 = StringFromKey("Common_citizen_248");
			link.l1.go = "SitySpy_2";
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			sld.dialog.currentnode = "SeekSpy_Checking";
			pchar.GenQuest.SeekSpy.time = 4.0; //время на подбежать
			if (sld.chr_ai.type == "merchant") pchar.GenQuest.SeekSpy.time = 0.0; //мерчант базарит сразу
			LAi_SetActorTypeNoGroup(sld);
		break;
		case "SitySpy_2":
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorTurnToCharacter(npchar, sld);
			LAi_ActorDialog(sld, pchar, "", stf(pchar.GenQuest.SeekSpy.time), 0);
			DialogExit();
		break;

		// Мини квест на поиск обручального кольца -->
		case "CitizenFindItem_1":
			dialog.text = StringFromKey("Common_citizen_249", pchar);
			link.l1 = StringFromKey("Common_citizen_250", pchar);
			link.l1.go = "CitizenFindItem_2";
			link.l2 = StringFromKey("Common_citizen_254", LinkRandPhrase(
						StringFromKey("Common_citizen_251"),
						StringFromKey("Common_citizen_252", pchar),
						StringFromKey("Common_citizen_253")));
			link.l2.go = "CitizenFindItem_NoQuest";
		break;

		case "CitizenFindItem_2":
			dialog.text = StringFromKey("Common_citizen_255", pchar, sti(NPChar.LifeDay));
			link.l1 = StringFromKey("Common_citizen_258", RandPhraseSimple(
						StringFromKey("Common_citizen_256"),
						StringFromKey("Common_citizen_257")));
			link.l1.go = "CitizenFindItem_3";
		break;

		case "CitizenFindItem_3":
			dialog.text = StringFromKey("Common_citizen_259");
			link.l1 = StringFromKey("Common_citizen_260", pchar);
			link.l1.go = "CitizenFindItem_4";
		break;

		case "CitizenFindItem_4":
			dialog.text = StringFromKey("Common_citizen_261", sti(NPChar.LifeDay));
			link.l1 = StringFromKey("Common_citizen_262");
			link.l1.go = "exit";
			ReOpenQuestHeader("SeekCitizenRing");
			AddQuestRecord("SeekCitizenRing", "1");
			AddQuestUserData("SeekCitizenRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekCitizenRing", "sName", GetFullName(npchar));
			PChar.GenQuest.CitizenFindItem.StartQuest = true;
			PChar.GenQuest.CitizenFindItem.CitizenID = NPChar.ID;

			ref ring = ItemsFromID("WeddingRing");
			ring.shown = true;
			ring.startLocation = npchar.city + "_ExitTown";
			ring.startLocator = GetFreeRandomItemLocator(ring.startLocation);
			Log_TestInfo("Кольцо будет в локаторе - " + ring.startLocator + "");
			ring.City = XI_ConvertString("Colony" + NPChar.City + "Gen");
			SetFunctionTimerCondition("CitizenFindItemMiniQuest_Timer", 0, 0, sti(NPChar.LifeDay), false);
		break;

		case "CitizenFindItem_NoQuest":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			NPChar.CitizenFindItem.NoQuest = true; // Эта девушка квест больше не даст
		break;

		case "CitizenFindItem_Complete_1":
			dialog.text = StringFromKey("Common_citizen_263", pchar);
			link.l1 = StringFromKey("Common_citizen_264", pchar);
			link.l1.go = "CitizenFindItem_Complete_2";
			link.l2 = StringFromKey("Common_citizen_265");
			link.l2.go = "CitizenFindItem_Complete_3";
			CloseQuestHeader("SeekCitizenRing");
			RemoveItems(PChar, "WeddingRing", 1);
			DeleteAttribute(PChar, "GenQuest.CitizenFindItem");
			NPChar.CitizenFindItem.NoQuest = true;
			PChar.Quest.CitizenFindItemMiniQuest_Timer.over = "yes";
			DeleteAttribute(&items[FindItem("WeddingRing")], "City");
		break;

		case "CitizenFindItem_Complete_2":
			dialog.text = StringFromKey("Common_citizen_266", pchar);
			link.l1 = StringFromKey("Common_citizen_267", NPChar.name);
			link.l1.go = "exit";
			ChangeCharacterReputation(PChar, 1);
			AddCharacterExpToSkill(PChar, "Leadership", 10);
			AddCharacterExpToSkill(PChar, "Fortune", 10);
		break;

		case "CitizenFindItem_Complete_3":
			iTemp = (rand(3) + 1) * 50;
			dialog.text = StringFromKey("Common_citizen_268", FindMoneyString(iTemp));
			link.l1 = StringFromKey("Common_citizen_269", GetFullName(NPChar));
			link.l1.go = "exit";
			AddMoneyToCharacter(PChar, iTemp);
		break;
		// <-- Мини квест на поиск обручального кольца

		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if (rand(3) != 1)
			{
				dialog.text = StringFromKey("Common_citizen_273", LinkRandPhrase(
							StringFromKey("Common_citizen_270"),
							StringFromKey("Common_citizen_271"),
							StringFromKey("Common_citizen_272")));
				link.l1 = StringFromKey("Common_citizen_277", LinkRandPhrase(
							StringFromKey("Common_citizen_274"),
							StringFromKey("Common_citizen_275"),
							StringFromKey("Common_citizen_276")));
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Common_citizen_281", LinkRandPhrase(
							StringFromKey("Common_citizen_278"),
							StringFromKey("Common_citizen_279"),
							StringFromKey("Common_citizen_280")));
				link.l1 = StringFromKey("Common_citizen_282");
				link.l1.go = "exit";
			}

			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;

		//-------------------------------горожанин-пассажир----------------------------------------------
		case "passenger":
			if (idRand(npchar.id + "Townpassenger", 19) > 9) SetPassengerParameter("Townpassenger", false);
			else SetPassengerParameter("Townpassenger", true);
			dialog.text = StringFromKey("Common_citizen_283", XI_ConvertString("Colony" + pchar.GenQuest.Townpassenger.City), XI_ConvertString(GetIslandNameByCity(pchar.GenQuest.Townpassenger.City) + "Pre"), FindDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty)), FindMoneyString(sti(pchar.GenQuest.Townpassenger.Money)));
			link.l1 = StringFromKey("Common_citizen_284", pchar);
			link.l1.go = "passenger_1";
			link.l2 = StringFromKey("Common_citizen_285", GetAddress_FormToNPC(NPChar));
			link.l2.go = "passenger_exit";
		break;

		case "passenger_exit":
			dialog.text = StringFromKey("Common_citizen_286");
			link.l1 = StringFromKey("Common_citizen_287");
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Townpassenger");
		break;

		case "passenger_1":
			dialog.text = StringFromKey("Common_citizen_288");
			link.l1 = StringFromKey("Common_citizen_289", GetAddress_FormToNPC(NPChar));
			link.l1.go = "passenger_2";
		break;

		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Townpassenger.id = npchar.id;
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index + "Citizpassenger";

			// LDH 13Sep17 - do not add to an existing Citizpassenger record
			// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo." + sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle + sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo, pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo." + sTitle);

				Trace("Duplicate Citizpassenger record " + sTitle + " copied to " + sTitle1 + " **");
			}

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "горожанина");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = StringFromKey("Common_citizen_290", XI_ConvertString("Colony" + pchar.GenQuest.Townpassenger.City), XI_ConvertString(GetIslandNameByCity(pchar.GenQuest.Townpassenger.City) + "Pre"));
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty)));
			AddQuestUserData(sTitle, "sMoney", FindMoneyString(sti(pchar.GenQuest.Townpassenger.Money)));
			pchar.quest.Townpassenger.win_condition.l1 = "location";
			pchar.quest.Townpassenger.win_condition.l1.location = pchar.GenQuest.Townpassenger.City + "_town";
			pchar.quest.Townpassenger.function = "Townpassenger_complete";
			SetFunctionTimerCondition("Townpassenger_Over", 0, 0, sti(pchar.GenQuest.Townpassenger.DaysQty), false);
		break;

		case "passenger_3":
			pchar.quest.Townpassenger_Over.over = "yes"; //снять таймер
			dialog.text = StringFromKey("Common_citizen_291");
			link.l1 = StringFromKey("Common_citizen_292", GetAddress_FormToNPC(NPChar));
			link.l1.go = "passenger_4";
		break;

		case "passenger_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Townpassenger.Money));
			ChangeCharacterReputation(pchar, 2);
			OfficersReaction("good");
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity")) AddCharacterExpToSkill(pchar, "Sneak", 50);
			sTitle = npchar.index + "Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Townpassenger");
		break;
		//<-- горожанин-пассажир

		//замечение по обнаженному оружию
		/*case "CitizenNotBlade": //HardCoffee ref TODO подчистить, если всё норм
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, StringFromKey("Common_citizen_255"), StringFromKey("Common_citizen_256"));
				link.l1 = LinkRandPhrase(StringFromKey("Common_citizen_257"), StringFromKey("Common_citizen_258"), StringFromKey("Common_citizen_259"));
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, StringFromKey("Common_citizen_260", GetSexPhrase(StringFromKey("SexPhrase_130"),StringFromKey("SexPhrase_131"))), StringFromKey("Common_citizen_261", GetSexPhrase(StringFromKey("SexPhrase_191"),StringFromKey("SexPhrase_192"))));
				link.l1 = RandPhraseSimple(StringFromKey("Common_citizen_262", GetSexPhrase("",StringFromKey("SexEnding_1"))), StringFromKey("Common_citizen_263"));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;*/
	}
}

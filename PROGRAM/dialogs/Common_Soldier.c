// boal 25/04/04 общий диалог солдат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\Soldier\" + NPChar.City + "_Soldier.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--
	int iTest, iTemp;
	int iNPCharnation = sti(NPChar.nation);
	string sTemp;
	iTest = FindColony(NPChar.City); // город
	ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			//sTemp = npchar.location;
			//			if (HasSubStr(sTemp, "_townhall")) AddDialogExitQuest("MainHeroFightModeOff"); // не актуально
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(NPChar, "IWantAskYou");
			DialogExit();
		break;

		case "fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			DeleteAttribute(&TEV, "SneakFastReload");
			DeleteAttribute(NPChar, "IWantAskYou");
			NormalizeRoutedCitizen("");
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (Pchar.location == "Santiago_Incquisitio") StartIncquisitioAttack();
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;

		case "First time":
			NextDiag.TempNode = "First time";
			//HardCoffee ref
			//HardCoffee TODO: убрать greeting у солдат и перенести его в диалог, чтобы соответствовало диалогу
			if (sti(pchar.nation) == PIRATE && iNPCharnation != PIRATE) // заглушка на пирата
			{
				if (CheckAttribute(NPChar, "IWantAskYou")) LAi_CharacterPlaySound(NPChar, "soldier_arest");
				dialog.text = StringFromKey("Common_Soldier_3", RandPhraseSimple(
							StringFromKey("Common_Soldier_1", pchar),
							StringFromKey("Common_Soldier_2", pchar)));
				link.l1 = StringFromKey("Common_Soldier_6", RandPhraseSimple(
							StringFromKey("Common_Soldier_4"),
							StringFromKey("Common_Soldier_5")));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(iNPCharnation) == RELATION_ENEMY && iNPCharnation != PIRATE)
			{
				if (CheckAttribute(NPChar, "IWantAskYou")) LAi_CharacterPlaySound(NPChar, "soldier_arest");
				dialog.text = StringFromKey("Common_Soldier_9", RandPhraseSimple(
							StringFromKey("Common_Soldier_7"),
							StringFromKey("Common_Soldier_8", pchar)));
				link.l1 = StringFromKey("Common_Soldier_12", RandPhraseSimple(
							StringFromKey("Common_Soldier_10"),
							StringFromKey("Common_Soldier_11")));
				link.l1.go = "fight";
				// ==> eddy. Засада, если опознали в инквизиции.
				if (Pchar.location == "Santiago_Incquisitio") StartIncquisitioAttack();
				break;
			}
			else //HardCoffee TODO: убрать после тестов
			{
				// eddy. проверяем, не казачок ли -->
				if (GetNationRelation(iNPCharnation, GetBaseHeroNation()) == RELATION_ENEMY && iNPCharnation != PIRATE && !GetSneakFastReloadByGuardian(npchar.city))
				{
					if (CheckAttribute(NPChar, "IWantAskYou")) LAi_CharacterPlaySound(NPChar, "soldier_arest");
					if (loadedLocation.id == "Santiago_Incquisitio") dialog.text = StringFromKey("Common_Soldier_13");
					else dialog.text = StringFromKey("Common_Soldier_16", RandPhraseSimple(
					StringFromKey("Common_Soldier_14"),
					StringFromKey("Common_Soldier_15")));
					//==> по лицензии, если есть
					if (CheckNationLicence(iNPCharnation))
					{
						link.l1 = StringFromKey("Common_Soldier_17", GetRusNameNationLicence(iNPCharnation));
						link.l1.go = "LicenceOk";
					}
					//==> и по флагу в любом случае
					if (HasSubStr(pchar.location.from_sea, "_town")) //если причалил в городе
					{
						link.l2 = StringFromKey("Common_Soldier_18", NationNameGenitive(sti(pchar.nation)));
					}
					else //если причалил не в городе
					{
						link.l2 = StringFromKey("Common_Soldier_19", pchar, XI_ConvertString(GetIslandNameByCity(npchar.city) + "Gen"), NationNameGenitive(sti(pchar.nation)));
					}
					link.l2.go = CheckSneakByGuards(iNPCharnation);
					link.l2 = DeceptionChance_TextWrapper(link.l2);
				}
				//HardCoffee с начала проверяем гг на врага, потом, если всё норм, беседуем по этому квесту
				else if (CheckAttribute(pchar, "GenQuest.EncGirl.MeetSoldiers"))
				{
					LAi_TemporaryBlindGuards();
					if ("1" == pchar.GenQuest.EncGirl.MeetSoldiers)
					{
						dialog.text = StringFromKey("Common_Soldier_78", pchar.GenQuest.EncGirl.name);
						link.l1 = StringFromKey("Common_Soldier_79", pchar);
						link.l1.go = "GirlEnc_1";
						DeleteAttribute(pchar, "GenQuest.EncGirl.MeetSoldiers");
						break;
					}
					if ("2" == pchar.GenQuest.EncGirl.MeetSoldiers)
					{
						dialog.text = StringFromKey("Common_Soldier_80");
						link.l1 = StringFromKey("Common_Soldier_81");
						link.l1.go = "GirlEnc_2";
						DeleteAttribute(pchar, "GenQuest.EncGirl.MeetSoldiers");
						break;
					}
					else
					{
						NextDiag.CurrentNode = NextDiag.TempNode;
						//EncGirl_CloseQuestExit("close"); //HardCoffee TODO:
						//EncGirl_CloseQuestExit_func("");
						log_info("ERROR: pchar.GenQuest.EncGirl.MeetSoldiers");
						trace("ERROR: pchar.GenQuest.EncGirl.MeetSoldiers");
						DialogExit();
						break;
					}
				}
				else
				{
					if (iNPCharnation == PIRATE)
					{
						if (sti(rColony.HeroOwn) == true) // наш горожанин
						{
							switch (rand(10))
							{
								case 0:
									dialog.text = StringFromKey("Common_Soldier_20");
									link.l1 = StringFromKey("Common_Soldier_21");
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = StringFromKey("Common_Soldier_22");
									link.l1 = StringFromKey("Common_Soldier_23");
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = StringFromKey("Common_Soldier_24");
									link.l1 = StringFromKey("Common_Soldier_25");
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = StringFromKey("Common_Soldier_26");
									link.l1 = StringFromKey("Common_Soldier_27", pchar);
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = StringFromKey("Common_Soldier_28");
									link.l1 = StringFromKey("Common_Soldier_29");
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = StringFromKey("Common_Soldier_30");
									link.l1 = StringFromKey("Common_Soldier_31");
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = StringFromKey("Common_Soldier_32");
									link.l1 = StringFromKey("Common_Soldier_33");
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = StringFromKey("Common_Soldier_34");
									link.l1 = StringFromKey("Common_Soldier_35");
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = StringFromKey("Common_Soldier_36");
									link.l1 = StringFromKey("Common_Soldier_37");
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = StringFromKey("Common_Soldier_38");
									link.l1 = StringFromKey("Common_Soldier_39");
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = StringFromKey("Common_Soldier_40");
									link.l1 = StringFromKey("Common_Soldier_41");
									link.l1.go = "exit";
								break;
							}
							link.l2 = StringFromKey("Common_Soldier_44", RandPhraseSimple(
										StringFromKey("Common_Soldier_42"),
										StringFromKey("Common_Soldier_43")));
							link.l2.go = "quests";//(перессылка в файл города)
							break;
						}
						else
						{
							// пираты, не наши
							dialog.text = StringFromKey("Common_Soldier_52", LinkRandPhrase(
										StringFromKey("Common_Soldier_47", RandPhraseSimple(
												StringFromKey("Common_Soldier_45"),
												StringFromKey("Common_Soldier_46"))),
										StringFromKey("Common_Soldier_50", RandPhraseSimple(
												StringFromKey("Common_Soldier_48"),
												StringFromKey("Common_Soldier_49"))),
										StringFromKey("Common_Soldier_51")));
							link.l1 = StringFromKey("Common_Soldier_56", LinkRandPhrase(
										StringFromKey("Common_Soldier_53", pchar),
										StringFromKey("Common_Soldier_54"),
										StringFromKey("Common_Soldier_55")));
							link.l1.go = "exit";
							link.l2 = StringFromKey("Common_Soldier_64", LinkRandPhrase(
										StringFromKey("Common_Soldier_59", RandPhraseSimple(
												StringFromKey("Common_Soldier_57"),
												StringFromKey("Common_Soldier_58"))),
										StringFromKey("Common_Soldier_62", RandPhraseSimple(
												StringFromKey("Common_Soldier_60"),
												StringFromKey("Common_Soldier_61", pchar))),
										StringFromKey("Common_Soldier_63", pchar)));
							link.l2.go = "quests";//(перессылка в файл города)
							break;
						}
					}
					else
					{
						//если негодяй, имеющий НЗГ к дружественной или нейтральной нации
						if (GetCharacterReputation_WithNation(pchar, sti(NPChar.nation)) <= -15)
						{
							PlayerRPGCheck_NationReputation_NotifyFail(sti(NPChar.nation));
							dialog.text = StringFromKey("Common_Soldier_67", RandPhraseSimple(
										StringFromKey("Common_Soldier_65", pchar, XI_ConvertString("Colony" + npchar.city + "Acc")),
										StringFromKey("Common_Soldier_66", pchar)));
							link.l1 = StringFromKey("Common_Soldier_70", RandPhraseSimple(
										StringFromKey("Common_Soldier_68"),
										StringFromKey("Common_Soldier_69")));
							link.l1.go = "fight";
							break;
						}
					}
					//зачарованный город -->
					if (pchar.questTemp.MC == "toCaracas" && npchar.city == "Caracas")
					{
						dialog.text = StringFromKey("Common_Soldier_74", LinkRandPhrase(
									StringFromKey("Common_Soldier_71"),
									StringFromKey("Common_Soldier_72"),
									StringFromKey("Common_Soldier_73")));
						link.l1 = StringFromKey("Common_Soldier_75");
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.MC == "toCaracasPadre" || pchar.questTemp.MC == "toCaracasTavern")
					{
						dialog.text = StringFromKey("Common_Soldier_76");
						link.l1 = StringFromKey("Common_Soldier_77");
						link.l1.go = "exit";
						break;
					}
					//<-- зачарованный город

					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = StringFromKey("Common_Soldier_82");
							link.l1 = StringFromKey("Common_Soldier_83");
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = StringFromKey("Common_Soldier_84");
							link.l1 = StringFromKey("Common_Soldier_85");
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = StringFromKey("Common_Soldier_86");
							link.l1 = StringFromKey("Common_Soldier_87");
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = StringFromKey("Common_Soldier_88");
							link.l1 = StringFromKey("Common_Soldier_91", RandPhraseSimple(
										StringFromKey("Common_Soldier_89"),
										StringFromKey("Common_Soldier_90")));
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = StringFromKey("Common_Soldier_92");
							link.l1 = StringFromKey("Common_Soldier_93");
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = StringFromKey("Common_Soldier_94");
							link.l1 = StringFromKey("Common_Soldier_98", LinkRandPhrase(
										StringFromKey("Common_Soldier_95"),
										StringFromKey("Common_Soldier_96"),
										StringFromKey("Common_Soldier_97")));
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = StringFromKey("Common_Soldier_101", RandPhraseSimple(
										StringFromKey("Common_Soldier_99", GetAddress_Form(NPChar)),
										StringFromKey("Common_Soldier_100", GetAddress_Form(NPChar))));
							link.l1 = StringFromKey("Common_Soldier_102", pchar);
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = StringFromKey("Common_Soldier_103", GetAddress_Form(NPChar));
							link.l1 = StringFromKey("Common_Soldier_104");
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = StringFromKey("Common_Soldier_105", pchar);
							link.l1 = StringFromKey("Common_Soldier_108", RandPhraseSimple(
										StringFromKey("Common_Soldier_106"),
										StringFromKey("Common_Soldier_107")));
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = StringFromKey("Common_Soldier_109", pchar);
							link.l1 = StringFromKey("Common_Soldier_110", pchar);
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = StringFromKey("Common_Soldier_111");
							link.l1 = StringFromKey("Common_Soldier_114", RandPhraseSimple(
										StringFromKey("Common_Soldier_112"),
										StringFromKey("Common_Soldier_113")));
							link.l1.go = "exit";
						break;
					}
					link.l3 = StringFromKey("Common_Soldier_115", pchar);
					link.l3.go = "quests";//(перессылка в файл города)						
				}
			}
		break;
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = StringFromKey("Common_Soldier_118", RandPhraseSimple(
						StringFromKey("Common_Soldier_116", pchar),
						StringFromKey("Common_Soldier_117", pchar, GetAddress_Form(npchar))));
			link.l1 = StringFromKey("Common_Soldier_121", RandPhraseSimple(
						StringFromKey("Common_Soldier_119"),
						StringFromKey("Common_Soldier_120")));
			link.l1.go = "fight";
			if (CheckAttribute(NPChar, "IWantAskYou")) //HardCoffee ref exp
			{
				DeleteAttribute(NPChar, "IWantAskYou");
				if (isDay()) AddCharacterExpToSkill(pchar, SKILL_SNEAK, 20.0);
				else  AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40.0);
			}
			//Оставил на случай, если гг сам обратится к менту
			else if (!CheckAttribute(pchar, "questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		case "NotPegYou":
			dialog.text = StringFromKey("Common_Soldier_124", RandPhraseSimple(
						StringFromKey("Common_Soldier_122", GetAddress_Form(pchar)),
						StringFromKey("Common_Soldier_123", GetAddress_Form(pchar))));
			link.l1 = StringFromKey("Common_Soldier_125");
			link.l1.go = "exit";
			LAi_TemporaryBlindGuards();
			if (CheckAttribute(NPChar, "IWantAskYou")) //HardCoffee ref exp
			{
				DeleteAttribute(NPChar, "IWantAskYou");
				if (isDay()) AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40.0);
				else  AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80.0);
			}
			//Оставил на случай, если гг сам обратится к менту
			else if (!CheckAttribute(pchar, "questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(sti(npchar.nation));
			if (iTemp == -1)
			{
				dialog.text = StringFromKey("Common_Soldier_126");
				link.l1 = StringFromKey("Common_Soldier_129", RandPhraseSimple(
							StringFromKey("Common_Soldier_127"),
							StringFromKey("Common_Soldier_128")));
				link.l1.go = "fight";
				TakeNationLicence(sti(npchar.nation));
			}
			TEV.SneakFastReload = Colonies[FindColony(npchar.City)].id + GetDataDay() + GetDataMonth() + GetDataYear();
			if (iTemp == 0)
			{
				dialog.text = StringFromKey("Common_Soldier_130");
				link.l1 = StringFromKey("Common_Soldier_131");
				link.l1.go = "exit";
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = StringFromKey("Common_Soldier_132", FindDaysString(iTemp), GetAddress_Form(npchar));
				link.l1 = StringFromKey("Common_Soldier_133");
				link.l1.go = "exit";
			}
			if (iTemp > 10)
			{
				dialog.text = StringFromKey("Common_Soldier_137", LinkRandPhrase(
							StringFromKey("Common_Soldier_134", FindDaysString(iTemp)),
							StringFromKey("Common_Soldier_135", GetAddress_Form(npchar), FindDaysString(iTemp)),
							StringFromKey("Common_Soldier_136", GetAddress_Form(npchar))));
				link.l1 = StringFromKey("Common_Soldier_140", RandPhraseSimple(
							StringFromKey("Common_Soldier_138"),
							StringFromKey("Common_Soldier_139")));
				link.l1.go = "exit";
			}
		break;
		//============================== ноды маяка Порт-Ройал =========================
		case "PortRoyal_Mayak":
			dialog.text = StringFromKey("Common_Soldier_143", RandPhraseSimple(
						StringFromKey("Common_Soldier_141", pchar),
						StringFromKey("Common_Soldier_142", pchar)));
			link.l1 = StringFromKey("Common_Soldier_146", RandPhraseSimple(
						StringFromKey("Common_Soldier_144"),
						StringFromKey("Common_Soldier_145")));
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Mayak";
		break;
		case "PortRoyal_Gans":
			dialog.text = StringFromKey("Common_Soldier_150", LinkRandPhrase(
						StringFromKey("Common_Soldier_147"),
						StringFromKey("Common_Soldier_148"),
						StringFromKey("Common_Soldier_149")));
			link.l1 = StringFromKey("Common_Soldier_153", RandPhraseSimple(
						StringFromKey("Common_Soldier_151", pchar),
						StringFromKey("Common_Soldier_152", pchar)));
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Gans";
		break;
		//=================== ноды квеста мэра. поиск шпиона на улице ==================
		case "SeekSpy_Checking":
			dialog.text = StringFromKey("Common_Soldier_154", &characters[sti(pchar.genquest.seekspy.baseidx)]);
			link.l1 = StringFromKey("Common_Soldier_157", RandPhraseSimple(
						StringFromKey("Common_Soldier_155", pchar),
						StringFromKey("Common_Soldier_156")));
			link.l1.go = "SeekSpy_Checking_1";
		break;
		case "SeekSpy_Checking_1":
			switch (pchar.GenQuest.SeekSpy.Type)
			{
				case "guardian": LAi_SetGuardianTypeNoGroup(npchar); break;
				case "patrol":   LAi_SetPatrolTypeNoGroup(npchar);   break;
				case "citizen":  LAi_SetCitizenTypeNoGroup(npchar);  break;
				case "merchant": LAi_SetMerchantTypeNoGroup(npchar); break;
			}
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;

		// --> генератор "Девица в джунглях"
		case "GirlEnc_1":
			dialog.text = StringFromKey("Common_Soldier_158", pchar);
			link.l1 = StringFromKey("Common_Soldier_159", pchar);
			link.l1.go = "GirlEnc_11";
			link.l2 = StringFromKey("Common_Soldier_160", pchar);
			link.l2.go = "GirlEnc_12";
		break;

		case "GirlEnc_11":
			dialog.text = StringFromKey("Common_Soldier_161", pchar);
			link.l1 = StringFromKey("Common_Soldier_162");
			link.l1.go = "GirlEnc_11End";
		break;

		case "GirlEnc_11End":
			DialogExit();
			ChangeCharacterReputation(pchar, -2);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "GirlEnc_12":
			dialog.text = StringFromKey("Common_Soldier_163");
			link.l1 = StringFromKey("Common_Soldier_164");
			link.l1.go = "GirlEnc_12End";
		break;

		case "GirlEnc_12End":
			pchar.money = sti(pchar.money) - makeint(sti(pchar.money) / 20);
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;

		case "GirlEnc_2":
			dialog.text = StringFromKey("Common_Soldier_165", pchar);
			link.l1 = StringFromKey("Common_Soldier_166");
			link.l1.go = "GirlEnc_2End";
			link.l2 = StringFromKey("Common_Soldier_167");
			link.l2.go = "GirlEnc_21";
		break;

		case "GirlEnc_2End":
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;
			ChangeCharacterReputation(pchar, -2);
			AddQuestRecord("JungleGirl", "11");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;

		case "GirlEnc_21":
			ChangeCharacterReputation(pchar, 2);
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < rand(100))
			{
				PlayerRPGCheck_Skill_NotifyFail(SKILL_LEADERSHIP, false);
				dialog.text = StringFromKey("Common_Soldier_168");
				link.l1 = StringFromKey("Common_Soldier_169");
				link.l1.go = "GirlEnc_21End";
			}
			else
			{
				PlayerRPGCheck_Skill_NotifyPass(SKILL_LEADERSHIP);
				dialog.text = StringFromKey("Common_Soldier_170", pchar);
				link.l1 = StringFromKey("Common_Soldier_171");
				link.l1.go = "exit";
			}
		break;

		case "GirlEnc_21End":
			DialogExit();
			AddQuestRecord("JungleGirl", "12");
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			CloseQuestHeader("JungleGirl");
			ChangeCharacterReputation(pchar, -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		// <-- генератор "Девица в джунглях"

		//замечение по обнаженному оружию
		/*case "SoldierNotBlade": //HardCoffee ref SoldierNotBlade CitizenNotBlade
			if(GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if(sti(pchar.nation) == PIRATE)
				{
					dialog.text = RandPhraseSimple(StringFromKey("Common_Soldier_148", GetSexPhrase(StringFromKey("SexPhrase_54"), StringFromKey("SexPhrase_55"))), StringFromKey("Common_Soldier_149", GetSexPhrase(StringFromKey("SexPhrase_54"), StringFromKey("SexPhrase_55"))));
					link.l1 = RandPhraseSimple(StringFromKey("Common_Soldier_150"), StringFromKey("Common_Soldier_151"));
					link.l1.go = "fight";
					break;
				}
				dialog.text = RandPhraseSimple(StringFromKey("Common_Soldier_153"), StringFromKey("Common_Soldier_152", GetSexPhrase(StringFromKey("SexPhrase_54"), StringFromKey("SexPhrase_55"))));
				link.l1 = RandPhraseSimple(StringFromKey("Common_Soldier_154"), StringFromKey("Common_Soldier_155"));
				link.l1.go = "fight";
			}
			else
			{
				dialog.text = LinkRandPhrase(StringFromKey("Common_Soldier_157"), StringFromKey("Common_Soldier_158"), StringFromKey("Common_Soldier_156", GetAddress_Form(NPChar)));
				link.l1 = LinkRandPhrase(StringFromKey("Common_Soldier_160"), StringFromKey("Common_Soldier_159", GetSexPhrase("",StringFromKey("SexEnding_1"))), StringFromKey("Common_Soldier_161"));
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) != RELATION_ENEMY) link.l1.go = "exit";
				else link.l1.go = "First Time"; //Не миновать нам проверки!
				link.l2 = LinkRandPhrase(StringFromKey("Common_Soldier_162"), StringFromKey("Common_Soldier_163"), StringFromKey("Common_Soldier_164"));
				link.l2.go = "fight";
				NextDiag.TempNode = "First Time";
				if (CheckAttribute(NPChar, "protector")) NPChar.greeting = "soldier_arest";
				else NPChar.greeting = "soldier_common";
			}
		break;*/
	}
}

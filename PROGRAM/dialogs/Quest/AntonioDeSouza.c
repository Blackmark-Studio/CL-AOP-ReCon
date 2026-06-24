// диалоговый файл №1 на голландку
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	float locx, locy, locz;

	switch (Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("AntonioDeSouza_1", pchar),
						StringFromKey("AntonioDeSouza_2", pchar),
						StringFromKey("AntonioDeSouza_3", pchar),
						StringFromKey("AntonioDeSouza_4", GetFullName(pchar)), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("AntonioDeSouza_5"),
						StringFromKey("AntonioDeSouza_6"),
						StringFromKey("AntonioDeSouza_7"),
						StringFromKey("AntonioDeSouza_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//>>>>>>>>>>>>========= Разброс диалогов =====================
			if (CheckAttribute(pchar, "questTemp.PDM_ONV_OhotaNaVedmu"))	//Квест "Прокажённая"
			{
				link.l1 = StringFromKey("AntonioDeSouza_95");
				link.l1.go = "PDM_ONW_Inqizitor_1";
				break;
			}
			if (pchar.questTemp.MC == "toByeBye")	//Квест "Зачарованный город"
			{
				link.l1 = StringFromKey("AntonioDeSouza_96", pchar);
				link.l1.go = "MCIncq";
				pchar.questTemp.MC = "Incquisitio";
				break;
			}
			if (pchar.questTemp.State == "Inquisition_toDeSouza")//Квест №2, базар с гл.Инквизитором
			{
				dialog.text = StringFromKey("AntonioDeSouza_9", pchar);
				link.l1 = StringFromKey("AntonioDeSouza_10");
				link.l1.go = "Step_S2_1";
			}
			if (pchar.questTemp.State == "Inquisition_toCuracao")
			{
				if (CheckAttribute(pchar, "questTemp.State.Store") || CheckAttribute(pchar, "questTemp.State.Usurer"))
				{
					dialog.text = StringFromKey("AntonioDeSouza_11", pchar, GetFullName(pchar));
					link.l1 = StringFromKey("AntonioDeSouza_12", pchar);
					link.l1.go = "Step_S2_12";
					link.l2 = StringFromKey("AntonioDeSouza_13");
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("AntonioDeSouza_14", pchar);
					link.l1 = StringFromKey("AntonioDeSouza_15");
					link.l1.go = "exit";
				}
			}
			if (pchar.questTemp.State == "Inquisition_afterFrancisco")
			{
				if (CheckAttribute(pchar, "questTemp.State.Store") || CheckAttribute(pchar, "questTemp.State.Usurer"))
				{
					dialog.text = StringFromKey("AntonioDeSouza_16", pchar, GetFullName(pchar));
					link.l1 = StringFromKey("AntonioDeSouza_17", pchar);
					link.l1.go = "Step_S2_12";
					link.l2 = StringFromKey("AntonioDeSouza_18");
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("AntonioDeSouza_19", pchar);
					link.l1 = StringFromKey("AntonioDeSouza_20", pchar);
					link.l1.go = "Step_S2_11";
				}
			}
			if (HasStr(pchar.questTemp.State, "Inquisition_back"))
			{
				dialog.text = StringFromKey("AntonioDeSouza_21", pchar);
				link.l1 = StringFromKey("AntonioDeSouza_22");
				link.l1.go = "exit";
				DeSouzaCrossFree();
			}
			if (pchar.questTemp.State == "TakeRockBras_RockTaken")
			{
				dialog.text = StringFromKey("AntonioDeSouza_23", pchar);
				link.l1 = StringFromKey("AntonioDeSouza_24");
				link.l1.go = "Step_S3_1";
			}

		break;

		//<<<<<<<<<<<<===== Разброс диалогов  =====================
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//********************************* Задания Инквизиции. Квест №2 **********************************
		case "Step_S2_1":
			dialog.text = StringFromKey("AntonioDeSouza_25", pchar);
			link.l1 = StringFromKey("AntonioDeSouza_26");
			link.l1.go = "Step_S2_2";
		break;
		case "Step_S2_2":
			dialog.text = StringFromKey("AntonioDeSouza_27", pchar);
			link.l1 = StringFromKey("AntonioDeSouza_28", pchar);
			link.l1.go = "Step_S2_3";
		break;
		case "Step_S2_3":
			dialog.text = StringFromKey("AntonioDeSouza_29");
			link.l1 = StringFromKey("AntonioDeSouza_30");
			link.l1.go = "Step_S2_4";
		break;
		case "Step_S2_4":
			dialog.text = StringFromKey("AntonioDeSouza_31", pchar);
			link.l1 = StringFromKey("AntonioDeSouza_32", pchar);
			link.l1.go = "Step_S2_5";
		break;
		case "Step_S2_5":
			dialog.text = StringFromKey("AntonioDeSouza_33", pchar);
			link.l1 = StringFromKey("AntonioDeSouza_34");
			link.l1.go = "Step_S2_6";
		break;
		case "Step_S2_6":
			dialog.text = StringFromKey("AntonioDeSouza_35");
			link.l1 = StringFromKey("AntonioDeSouza_36");
			link.l1.go = "Step_S2_7";
		break;
		case "Step_S2_7":
			dialog.text = StringFromKey("AntonioDeSouza_37");
			link.l1 = StringFromKey("AntonioDeSouza_38");
			link.l1.go = "Step_S2_8";
		break;
		case "Step_S2_8":
			dialog.text = StringFromKey("AntonioDeSouza_39", pchar);
			link.l1 = StringFromKey("AntonioDeSouza_40", pchar);
			link.l1.go = "Step_S2_9";
		break;
		case "Step_S2_9":
			dialog.text = StringFromKey("AntonioDeSouza_41", pchar);
			link.l1 = StringFromKey("AntonioDeSouza_42");
			link.l1.go = "Step_S2_10";
		break;
		case "Step_S2_10":
			dialog.text = StringFromKey("AntonioDeSouza_43");
			link.l1 = StringFromKey("AntonioDeSouza_44");
			link.l1.go = "exit";
			pchar.questTemp.State = "Inquisition_toCuracao";
			AddQuestRecord("Spa_Line_2_Inquisition", "2");
			Pchar.quest.Inquisition_MeetFrancisco.win_condition.l1 = "location";
			Pchar.quest.Inquisition_MeetFrancisco.win_condition.l1.location = "Santiago_town";
			Pchar.quest.Inquisition_MeetFrancisco.win_condition = "Inquisition_MeetFrancisco";
			RemoveLandQuestmark_Main(CharacterFromID("Santiago_Priest"), "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("Villemstad_Trader"), "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("Villemstad_Usurer"), "Spa_Line");
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "SpaLine_2_DeSouzaTask_QuestMarkCondition");
		break;
		case "Step_S2_11":
			dialog.text = StringFromKey("AntonioDeSouza_45", pchar);
			link.l1 = StringFromKey("AntonioDeSouza_46");
			link.l1.go = "exit";
			pchar.questTemp.State = "Inquisition_toCuracao";
			GiveItem2Character(pchar, "DeSouzaCross");
			SetCurrentQuestmark(npchar); // обновим метку
		break;
		case "Step_S2_12":
			dialog.text = StringFromKey("AntonioDeSouza_47", pchar);
			link.l1 = StringFromKey("AntonioDeSouza_48");
			link.l1.go = "Step_S2_NotMoney";
			if (pchar.questTemp.State.Usurer == "Ok")
			{
				link.l1 = StringFromKey("AntonioDeSouza_49");
				link.l1.go = "Step_S2_OnlyUsurer";
			}
			if (pchar.questTemp.State.Store == "Ok")
			{
				link.l1 = StringFromKey("AntonioDeSouza_50");
				link.l1.go = "Step_S2_OnlyStore";
			}
			if (pchar.questTemp.State.Store == "Ok" && pchar.questTemp.State.Usurer == "Ok")
			{
				link.l1 = StringFromKey("AntonioDeSouza_51");
				link.l1.go = "Step_S2_All";
			}
		break;
		case "Step_S2_NotMoney":
			dialog.text = StringFromKey("AntonioDeSouza_52", pchar);
			link.l1 = StringFromKey("AntonioDeSouza_53", pchar);
			link.l1.go = "Step_S2_13";
		break;
		case "Step_S2_13":
			dialog.text = StringFromKey("AntonioDeSouza_54", pchar);
			link.l1 = StringFromKey("AntonioDeSouza_55");
			link.l1.go = "exit";
			pchar.questTemp.State = "Inquisition_backBad";
			AddQuestRecord("Spa_Line_2_Inquisition", "15");
			DeleteAttribute(pchar, "questTemp.State.Store");
			DeleteAttribute(pchar, "questTemp.State.Usurer");
			DeleteAttribute(pchar, "questTemp.State.SeekBible");
			DeSouzaCrossFree();
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("spa_guber"), "Spa_Line");
		break;
		case "Step_S2_OnlyUsurer":
			if (sti(pchar.money) >= 50000)
			{
				dialog.text = StringFromKey("AntonioDeSouza_56", pchar);
				link.l1 = StringFromKey("AntonioDeSouza_57", pchar);
				link.l1.go = "Step_S2_14";
			}
			else
			{
				dialog.text = StringFromKey("AntonioDeSouza_58", pchar);
				link.l1 = StringFromKey("AntonioDeSouza_59", pchar);
				link.l1.go = "exit";
				NextDiag.TempNode = "Step_S2_OnlyUsurer";
			}
		break;
		case "Step_S2_14":
			dialog.text = StringFromKey("AntonioDeSouza_60", pchar);
			link.l1 = StringFromKey("AntonioDeSouza_61");
			link.l1.go = "exit";
			if (CheckCharacterItem(pchar, "Bible"))
			{
				link.l2 = StringFromKey("AntonioDeSouza_62");
				link.l2.go = "Step_S2_17";
			}
			pchar.questTemp.State = "Inquisition_backPartGood";
			AddMoneyToCharacter(pchar, -41000);
			AddQuestRecord("Spa_Line_2_Inquisition", "16");
			DeleteAttribute(pchar, "questTemp.State.Store");
			DeleteAttribute(pchar, "questTemp.State.Usurer");
			DeleteAttribute(pchar, "questTemp.State.SeekBible");
			NextDiag.TempNode = "First time";
			DeSouzaCrossFree();
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("spa_guber"), "Spa_Line");
		break;
		case "Step_S2_OnlyStore":
			if (sti(pchar.money) >= 100000)
			{
				dialog.text = StringFromKey("AntonioDeSouza_63", pchar);
				link.l1 = StringFromKey("AntonioDeSouza_64", pchar);
				link.l1.go = "Step_S2_15";
			}
			else
			{
				dialog.text = StringFromKey("AntonioDeSouza_65", pchar);
				link.l1 = StringFromKey("AntonioDeSouza_66", pchar);
				link.l1.go = "exit";
				NextDiag.TempNode = "Step_S2_OnlyStore";
			}
		break;
		case "Step_S2_15":
			dialog.text = StringFromKey("AntonioDeSouza_67", pchar);
			link.l1 = StringFromKey("AntonioDeSouza_68");
			link.l1.go = "exit";
			if (CheckCharacterItem(pchar, "Bible"))
			{
				link.l2 = StringFromKey("AntonioDeSouza_69");
				link.l2.go = "Step_S2_17";
			}
			pchar.questTemp.State = "Inquisition_backPartGood";
			AddMoneyToCharacter(pchar, -82000);
			AddQuestRecord("Spa_Line_2_Inquisition", "16");
			DeleteAttribute(pchar, "questTemp.State.Store");
			DeleteAttribute(pchar, "questTemp.State.Usurer");
			DeleteAttribute(pchar, "questTemp.State.SeekBible");
			NextDiag.TempNode = "First time";
			DeSouzaCrossFree();
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("spa_guber"), "Spa_Line");
		break;
		case "Step_S2_All":
			if (sti(pchar.money) >= 150000)
			{
				dialog.text = StringFromKey("AntonioDeSouza_70", pchar);
				link.l1 = StringFromKey("AntonioDeSouza_71", pchar);
				link.l1.go = "Step_S2_16";
			}
			else
			{
				dialog.text = StringFromKey("AntonioDeSouza_72", pchar);
				link.l1 = StringFromKey("AntonioDeSouza_73", pchar);
				link.l1.go = "exit";
				NextDiag.TempNode = "Step_S2_All";
			}
		break;
		case "Step_S2_16":
			dialog.text = StringFromKey("AntonioDeSouza_74", pchar);
			link.l1 = StringFromKey("AntonioDeSouza_75");
			link.l1.go = "exit";
			if (CheckCharacterItem(pchar, "Bible"))
			{
				link.l2 = StringFromKey("AntonioDeSouza_76");
				link.l2.go = "Step_S2_17";
			}
			pchar.questTemp.State = "Inquisition_backAllGood";
			AddMoneyToCharacter(pchar, -123000);
			AddQuestRecord("Spa_Line_2_Inquisition", "17");
			DeleteAttribute(pchar, "questTemp.State.Store");
			DeleteAttribute(pchar, "questTemp.State.Usurer");
			DeleteAttribute(pchar, "questTemp.State.SeekBible");
			NextDiag.TempNode = "First time";
			DeSouzaCrossFree();
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("spa_guber"), "Spa_Line");
		break;
		case "Step_S2_17":
			dialog.text = StringFromKey("AntonioDeSouza_77", pchar);
			link.l1 = StringFromKey("AntonioDeSouza_78");
			link.l1.go = "Step_S2_18";
		break;
		case "Step_S2_18":
			dialog.text = StringFromKey("AntonioDeSouza_79");
			link.l1 = StringFromKey("AntonioDeSouza_80");
			link.l1.go = "Step_S2_19";
		break;
		case "Step_S2_19":
			dialog.text = StringFromKey("AntonioDeSouza_81", pchar);
			link.l1 = StringFromKey("AntonioDeSouza_82", pchar);
			link.l1.go = "Step_S2_20";
		break;
		case "Step_S2_20":
			dialog.text = StringFromKey("AntonioDeSouza_83", pchar);
			link.l1 = StringFromKey("AntonioDeSouza_84", pchar);
			link.l1.go = "Step_S2_21";
			TakeItemFromCharacter(pchar, "Bible");
		break;
		case "Step_S2_21":
			dialog.text = StringFromKey("AntonioDeSouza_85", pchar);
			link.l1 = StringFromKey("AntonioDeSouza_86");
			link.l1.go = "Step_S2_22";
		break;
		case "Step_S2_22":
			dialog.text = StringFromKey("AntonioDeSouza_87");
			link.l1 = StringFromKey("AntonioDeSouza_88");
			link.l1.go = "exit";
			GiveItem2Character(pchar, "cirass5");
		break;
		//********************************* Захват Рока Бразильца. Квест №3 **********************************
		case "Step_S3_1":
			if (CheckPassengerInCharacter(pchar, "RockBrasilian"))
			{
				dialog.text = StringFromKey("AntonioDeSouza_89", pchar);
				link.l1 = StringFromKey("AntonioDeSouza_90");
				link.l1.go = "Step_S3_2";
			}
			else
			{
				dialog.text = StringFromKey("AntonioDeSouza_91", pchar);
				link.l1 = StringFromKey("AntonioDeSouza_92");
				link.l1.go = "exit";
			}
		break;
		case "Step_S3_2":
			dialog.text = StringFromKey("AntonioDeSouza_93");
			link.l1 = StringFromKey("AntonioDeSouza_94");
			link.l1.go = "exit";
			AddQuestRecord("Spa_Line_3_RockBrasilian", "6");
			pchar.questTemp.State = "TakeRockBras_RockGiven";
			sld = characterFromId("RockBrasilian");
			ReleasePrisoner(sld);
			sld.LifeDay = 0; // уберем нпс
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("spa_guber"), "Spa_Line");
		break;
		//********************************* Квест "Прокажённая" **********************************
		case "PDM_ONW_Inqizitor_1":
			dialog.text = StringFromKey("AntonioDeSouza_97", pchar);
			link.l1 = StringFromKey("AntonioDeSouza_98");
			link.l1.go = "PDM_ONW_Inqizitor_2";
			DeleteAttribute(pchar, "questTemp.PDM_ONV_OhotaNaVedmu");
		break;

		case "PDM_ONW_Inqizitor_2":
			DialogExit();
			
			locations[FindLocation("Cuba_jungle_01")].DisableEncounters = true;
			TavernWaitDateEx(22);
			DoFunctionReloadToLocation("Cuba_jungle_01", "goto", "goto4", "PDM_ONW_Kino_1");
		break;
		//**************************** сдаём зачарованный Дес-Мойнес ********************************
		case "MCIncq":
			dialog.text = StringFromKey("Incquistors_dialog_66", pchar);
			link.l1 = StringFromKey("Incquistors_dialog_67");
			link.l1.go = "MCIncq_1";
		break;
		case "MCIncq_1":
			dialog.text = StringFromKey("Incquistors_dialog_68");
			link.l1 = StringFromKey("Incquistors_dialog_69");
			link.l1.go = "MCIncq_2";
		break;
		case "MCIncq_2":
			dialog.text = StringFromKey("Incquistors_dialog_70", pchar);
			link.l1 = StringFromKey("Incquistors_dialog_71", pchar);
			link.l1.go = "MCIncq_3";
		break;
		case "MCIncq_3":
			dialog.text = StringFromKey("Incquistors_dialog_72", pchar);
			link.l1 = StringFromKey("Incquistors_dialog_73", pchar);
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterReputation(pchar, -10);
			CloseQuestHeader("MagicCity");
			RemoveLandQuestmark_Main(CharacterFromID("Santiago_Inquisitor"), "MagicCity");
			Achievment_Set(ACH_Ya_vizhu_myortvykh_lyudey);
		break;
	}
}

void DeSouzaCrossFree()
{
	if (!CheckAttribute(&TEV, "DeSouzaCrossFree") && HasStr(pchar.questTemp.State, "Inquisition_back") && GetCharacterItem(pchar, "DeSouzaCross"))
	{
		ref itm = ItemsFromID("DeSouzaCross");
		itm.ItemType = "VARIETY";
		itm.price = 1478;
		TEV.DeSouzaCrossFree = 1;
	}
}

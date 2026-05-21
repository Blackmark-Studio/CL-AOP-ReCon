// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Villemstad_Tavern_1", GetCityName(npchar.city)),
						StringFromKey("Villemstad_Tavern_2"),
						StringFromKey("Villemstad_Tavern_3"),
						StringFromKey("Villemstad_Tavern_4", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Villemstad_Tavern_5", NPChar.name),
						StringFromKey("Villemstad_Tavern_6", pchar),
						StringFromKey("Villemstad_Tavern_7"),
						StringFromKey("Villemstad_Tavern_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "EscapeSlave_Villemstad")
			{
				link.l1 = StringFromKey("Villemstad_Tavern_9", pchar);
				link.l1.go = "EscapeSlaveVillemstad_T1";
			}
			// ==> Проверяем поле состояния квестов.
			switch (pchar.questTemp.State)
			{
				case "Intelligence_Curacao_tavern":
					link.l1 = StringFromKey("Villemstad_Tavern_10");
					link.l1.go = "Step_E4_1";
				break;
				case "Intelligence_Curacao_dWant_pay_tavern":
					dialog.text = StringFromKey("Villemstad_Tavern_11", pchar);
					link.l1 = StringFromKey("Villemstad_Tavern_12", pchar);
					link.l1.go = "E4_OK_pay";
					link.l2 = StringFromKey("Villemstad_Tavern_13");
					link.l2.go = "E4_dWant_pay";
				break;
				case "Intelligence_Curacao_NoMoney_tavern":
					dialog.text = StringFromKey("Villemstad_Tavern_14", pchar);
					link.l1 = StringFromKey("Villemstad_Tavern_15", pchar);
					link.l1.go = "E4_OK_pay";
				break;
				case "Inquisition_toCuracao":
					dialog.text = StringFromKey("Villemstad_Tavern_16");
					link.l1 = StringFromKey("Villemstad_Tavern_17");
					link.l1.go = "Step_S2_1";
				break;
				case "Inquisition_afterFrancisco":
					dialog.text = StringFromKey("Villemstad_Tavern_18");
					link.l1 = StringFromKey("Villemstad_Tavern_19");
					link.l1.go = "Step_S2_1";
				break;
				case "Fr2Letter_SeekProblems":
					dialog.text = StringFromKey("Villemstad_Tavern_20", pchar);
					link.l1 = StringFromKey("Villemstad_Tavern_21");
					link.l1.go = "Step_F2_1";
				break;
			}
			if (pchar.questTemp.LSC == "toVillemstadTavern")
			{
				dialog.text = StringFromKey("Villemstad_Tavern_22");
				link.l1 = StringFromKey("Villemstad_Tavern_23");
				link.l1.go = "MasterKeys";
			}
			if (pchar.questTemp.LSC == "toMasterKeysNoMoney")
			{
				dialog.text = StringFromKey("Villemstad_Tavern_24");
				link.l1 = StringFromKey("Villemstad_Tavern_25");
				link.l1.go = "MasterKeysNM";
			}
			if (pchar.questTemp.LSC == "toTalkStuvesant")
			{
				dialog.text = StringFromKey("Villemstad_Tavern_26");
				link.l1 = StringFromKey("Villemstad_Tavern_27");
				link.l1.go = "TizerFind";
			}
			// <== Проверяем поле состояния квестов.
			//ОЗГ, Хален
			if (pchar.questTemp.Headhunter == "hunt_halen")
			{
				link.l1 = StringFromKey("Villemstad_Tavern_28");
				link.l1.go = "Halen_tavern_1";
			}
			if (pchar.questTemp.Headhunter == "halen_still")
			{
				link.l1 = StringFromKey("Villemstad_Tavern_29");
				link.l1.go = "Halen_tavern_1_1";
			}
			if (pchar.questTemp.Headhunter == "halen_wait")
			{
				link.l1 = StringFromKey("Villemstad_Tavern_30");
				link.l1.go = "Halen_tavern_6_6";
			}
		//ОЗГ, Хален
		break;
		//*************************** Квест №4 английки, разведка в Кюрасао ***************************
		case "Step_E4_1":
			dialog.text = StringFromKey("Villemstad_Tavern_31");
			link.l1 = StringFromKey("Villemstad_Tavern_32");
			link.l1.go = "Step_E4_2";
		break;
		case "Step_E4_2":
			dialog.text = StringFromKey("Villemstad_Tavern_33");
			link.l1 = StringFromKey("Villemstad_Tavern_34");
			link.l1.go = "E4_dWant_pay";
			link.l2 = StringFromKey("Villemstad_Tavern_35");
			link.l2.go = "E4_OK_pay";
		break;
		case "E4_dWant_pay":
			dialog.text = StringFromKey("Villemstad_Tavern_36");
			link.l1 = StringFromKey("Villemstad_Tavern_37");
			link.l1.go = "exit";
			pchar.questTemp.State = "Intelligence_Curacao_dWant_pay_tavern";
		break;
		case "E4_OK_pay":
			if (sti(pchar.money) >= 1000)
			{
				dialog.text = StringFromKey("Villemstad_Tavern_38");
				link.l1 = StringFromKey("Villemstad_Tavern_39");
				link.l1.go = "Step_E4_3";
			}
			else
			{
				dialog.text = StringFromKey("Villemstad_Tavern_40", pchar);
				link.l1 = StringFromKey("Villemstad_Tavern_41");
				link.l1.go = "exit";
				pchar.questTemp.State = "Intelligence_Curacao_NoMoney_tavern";
				//ChangeCharacterReputation(pchar, -1); TODO eddy
			}
		break;
		case "Step_E4_3":
			dialog.text = StringFromKey("Villemstad_Tavern_42");
			link.l1 = StringFromKey("Villemstad_Tavern_43");
			link.l1.go = "Step_E4_4";
		break;
		case "Step_E4_4":
			dialog.text = StringFromKey("Villemstad_Tavern_44", pchar);
			link.l1 = StringFromKey("Villemstad_Tavern_45");
			link.l1.go = "exit";
			pchar.questTemp.State = "Intelligence_Curacao_toYozef";
			AddMoneyToCharacter(pchar, -1000);
			AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "2");
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			AddLandQuestmark_Main(CharacterFromID("Villemstad_usurer"), "Eng_Line");
		break;
		//*************************** Квест №2 испанки, задания Инквизиции ***************************
		case "Step_S2_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Villemstad_Tavern_46"),
						StringFromKey("Villemstad_Tavern_47"),
						StringFromKey("Villemstad_Tavern_48"),
						StringFromKey("Villemstad_Tavern_49"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Villemstad_Tavern_50"),
						StringFromKey("Villemstad_Tavern_51"),
						StringFromKey("Villemstad_Tavern_52"),
						StringFromKey("Villemstad_Tavern_53"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_S2_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_S2_2":
			dialog.text = StringFromKey("Villemstad_Tavern_54");
			link.l1 = StringFromKey("Villemstad_Tavern_55");
			link.l1.go = "exit";
		break;
		//*************************** Квест №2 фр.линейки, доставка письма Стэвезанту ***************************
		case "Step_F2_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Villemstad_Tavern_56"),
						StringFromKey("Villemstad_Tavern_57"),
						StringFromKey("Villemstad_Tavern_58"),
						StringFromKey("Villemstad_Tavern_59"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Villemstad_Tavern_60", pchar),
						StringFromKey("Villemstad_Tavern_61"),
						StringFromKey("Villemstad_Tavern_62"),
						StringFromKey("Villemstad_Tavern_63"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_F2_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_F2_2":
			dialog.text = StringFromKey("Villemstad_Tavern_64");
			link.l1 = StringFromKey("Villemstad_Tavern_65");
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;
		//*************************** ГПК, Мастер Ключей ***************************
		case "MasterKeys":
			dialog.text = StringFromKey("Villemstad_Tavern_66");
			link.l1 = StringFromKey("Villemstad_Tavern_67");
			link.l1.go = "MasterKeys_1";
		break;
		case "MasterKeys_1":
			dialog.text = StringFromKey("Villemstad_Tavern_68");
			link.l1 = StringFromKey("Villemstad_Tavern_69");
			link.l1.go = "MasterKeys_2";
		break;
		case "MasterKeys_2":
			dialog.text = StringFromKey("Villemstad_Tavern_70");
			link.l1 = StringFromKey("Villemstad_Tavern_71", pchar);
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toMasterKeys";
			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
			AddLandQuestMark_Main(CharacterFromID("GiveKeyMan"), "ISS_PoorsMurder");
		break;

		case "MasterKeysNM":
			dialog.text = StringFromKey("Villemstad_Tavern_72");
			link.l1 = StringFromKey("Villemstad_Tavern_73");
			link.l1.go = "exit";
			if (!LAi_CheckLocatorFree("sit", "sit1"))
			{
				FreeSitLocator("Villemstad_tavern", "sit1");
			}
			ChangeCharacterAddressGroup(&characters[GetCharacterIndex("GiveKeyMan")], "Villemstad_tavern", "sit", "sit1");

			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
			AddLandQuestMark_Main(CharacterFromID("GiveKeyMan"), "ISS_PoorsMurder");
		break;
		//ищем Тизера
		case "TizerFind":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Villemstad_Tavern_74"),
						StringFromKey("Villemstad_Tavern_75"),
						StringFromKey("Villemstad_Tavern_76"),
						StringFromKey("Villemstad_Tavern_77"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Villemstad_Tavern_78"),
						StringFromKey("Villemstad_Tavern_79"),
						StringFromKey("Villemstad_Tavern_80"),
						StringFromKey("Villemstad_Tavern_81"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("TizerFind_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "TizerFind_1":
			dialog.text = StringFromKey("Villemstad_Tavern_82");
			link.l1 = StringFromKey("Villemstad_Tavern_83");
			link.l1.go = "TizerFind_2";
		break;
		case "TizerFind_2":
			dialog.text = StringFromKey("Villemstad_Tavern_84");
			link.l1 = StringFromKey("Villemstad_Tavern_85");
			link.l1.go = "TizerFind_3";
		break;
		case "TizerFind_3":
			dialog.text = StringFromKey("Villemstad_Tavern_86");
			link.l1 = StringFromKey("Villemstad_Tavern_87");
			link.l1.go = "TizerFind_4";
		break;
		case "TizerFind_4":
			dialog.text = StringFromKey("Villemstad_Tavern_88");
			link.l1 = StringFromKey("Villemstad_Tavern_89");
			link.l1.go = "TizerFind_5";
		break;
		case "TizerFind_5":
			dialog.text = StringFromKey("Villemstad_Tavern_90");
			link.l1 = StringFromKey("Villemstad_Tavern_91");
			link.l1.go = "TizerFind_6";
		break;
		case "TizerFind_6":
			dialog.text = StringFromKey("Villemstad_Tavern_92");
			link.l1 = StringFromKey("Villemstad_Tavern_93");
			link.l1.go = "TizerFind_7";
		break;
		case "TizerFind_7":
			dialog.text = StringFromKey("Villemstad_Tavern_94");
			link.l1 = StringFromKey("Villemstad_Tavern_95");
			link.l1.go = "TizerFind_8";
		break;
		case "TizerFind_8":
			dialog.text = StringFromKey("Villemstad_Tavern_96");
			link.l1 = StringFromKey("Villemstad_Tavern_97");
			link.l1.go = "TizerFind_9";
		break;
		case "TizerFind_9":
			dialog.text = StringFromKey("Villemstad_Tavern_98");
			link.l1 = StringFromKey("Villemstad_Tavern_99");
			link.l1.go = "TizerFind_10";
		break;
		case "TizerFind_10":
			dialog.text = StringFromKey("Villemstad_Tavern_100");
			link.l1 = StringFromKey("Villemstad_Tavern_101");
			link.l1.go = "TizerFind_11";
		break;
		case "TizerFind_11":
			dialog.text = StringFromKey("Villemstad_Tavern_102", pchar);
			link.l1 = StringFromKey("Villemstad_Tavern_103", pchar);
			link.l1.go = "TizerFind_12";
		break;
		case "TizerFind_12":
			dialog.text = StringFromKey("Villemstad_Tavern_104");
			link.l1 = StringFromKey("Villemstad_Tavern_105");
			link.l1.go = "exit";
			AddQuestRecord("ISS_PoorsMurder", "8");
			AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("ISS_PoorsMurder", "sSex1", GetSexPhrase("", "ла"));

			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
		break;
		//работорговец
		case "EscapeSlaveVillemstad_T1":
			dialog.text = StringFromKey("Villemstad_Tavern_106");
			link.l1 = StringFromKey("Villemstad_Tavern_107");
			link.l1.go = "EscapeSlaveVillemstad_T2";
		break;

		case "EscapeSlaveVillemstad_T2":
			dialog.text = StringFromKey("Villemstad_Tavern_108");
			link.l1 = StringFromKey("Villemstad_Tavern_109");
			link.l1.go = "EscapeSlaveVillemstad_T3";
		break;

		case "EscapeSlaveVillemstad_T3":
			dialog.text = StringFromKey("Villemstad_Tavern_110", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Villemstad_Tavern_111");
			link.l1.go = "EscapeSlaveVillemstad_T4";
		break;

		case "EscapeSlaveVillemstad_T4":
			dialog.text = StringFromKey("Villemstad_Tavern_112");
			link.l1 = StringFromKey("Villemstad_Tavern_113");
			link.l1.go = "EscapeSlaveVillemstad_T5";
		break;

		case "EscapeSlaveVillemstad_T5":
			dialog.text = StringFromKey("Villemstad_Tavern_114", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Villemstad_Tavern_115", npchar.name);
			link.l1.go = "EscapeSlaveVillemstad_T6";
		break;

		case "EscapeSlaveVillemstad_T6":
			dialog.text = StringFromKey("Villemstad_Tavern_116");
			link.l1 = StringFromKey("Villemstad_Tavern_117", npchar.name);
			link.l1.go = "EscapeSlaveVillemstad_T7";
		break;

		case "EscapeSlaveVillemstad_T7":
			dialog.text = StringFromKey("Villemstad_Tavern_118", pchar.name);
			link.l1 = StringFromKey("Villemstad_Tavern_119");
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "22_2");
			pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_P";
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			AddLandQuestmark_Main(CharacterFromID("Villemstad_PortMan"), "Slavetrader");
		break;

		//ОЗГ, Хален
		case "Halen_tavern_1":
			dialog.text = StringFromKey("Villemstad_Tavern_120");
			link.l1 = StringFromKey("Villemstad_Tavern_121");
			link.l1.go = "Halen_tavern_2";
		break;

		case "Halen_tavern_2":
			dialog.text = StringFromKey("Villemstad_Tavern_122");
			link.l1 = StringFromKey("Villemstad_Tavern_123");
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "halen_room";
			LocatorReloadEnterDisable("Villemstad_tavern", "reload2_back", false);
			AddMoneyToCharacter(pchar, -100);
			Pchar.quest.Headhunter_inRoom.win_condition.l1 = "location";
			Pchar.quest.Headhunter_inRoom.win_condition.l1.location = "Villemstad_tavern_upstairs";
			Pchar.quest.Headhunter_inRoom.function = "RatHunters_inRoom";
			AddQuestRecord("Headhunt", "27");
			AddQuestUserData("Headhunt", "sSex", GetSexPhrase("", "а"));
			pchar.quest.Headhunter_HalenOver.over = "yes";
			SetFunctionTimerCondition("Headhunter_HalenOver_2", 0, 0, 10, false); //следующий таймер
			RemoveLandQuestMark_Main(npchar, "Headhunt");
		break;

		case "Halen_tavern_1_1":
			dialog.text = StringFromKey("Villemstad_Tavern_124");
			link.l1 = StringFromKey("Villemstad_Tavern_125", pchar);
			link.l1.go = "Halen_tavern_2_2";
		break;

		case "Halen_tavern_2_2":
			dialog.text = StringFromKey("Villemstad_Tavern_126");
			link.l1 = StringFromKey("Villemstad_Tavern_127");
			link.l1.go = "Halen_tavern_4_4";
		break;

		case "Halen_tavern_4_4":
			dialog.text = StringFromKey("Villemstad_Tavern_128");
			link.l1 = StringFromKey("Villemstad_Tavern_129", pchar);
			link.l1.go = "Halen_tavern_5_5";
		break;

		case "Halen_tavern_5_5":
			dialog.text = StringFromKey("Villemstad_Tavern_130", pchar);
			link.l1 = StringFromKey("Villemstad_Tavern_131");
			link.l1.go = "Halen_tavern_6_6";
		break;

		case "Halen_tavern_6_6":
			if (makeint(environment.time) > 18.0 || makeint(environment.time) < 6.0)
			{
				dialog.text = StringFromKey("Villemstad_Tavern_132");
				link.l1 = StringFromKey("Villemstad_Tavern_133");
				link.l1.go = "exit";
				pchar.questTemp.Headhunter = "halen_wait";
				break;
			}
			dialog.text = StringFromKey("Villemstad_Tavern_134");
			link.l1 = StringFromKey("Villemstad_Tavern_135");
			link.l1.go = "Halen_tavern_7_7";
		break;

		case "Halen_tavern_7_7":
			dialog.text = StringFromKey("Villemstad_Tavern_136");
			link.l1 = StringFromKey("Villemstad_Tavern_137", pchar);
			link.l1.go = "Halen_tavern_8_8";
		break;

		case "Halen_tavern_8_8":
			AddQuestRecord("Headhunt", "29");
			pchar.questTemp.Headhunter = "halen_town";
			pchar.quest.Headhunter_HalenOver_2.over = "yes";
			TEV.need_citizens = !isLocationHasCitizens("Villemstad_town");
			SetFunctionTimerCondition("Headhunter_HalenOver_3", 0, 0, 5, false); //последний таймер
			pchar.quest.Headhunter_SeekHalen.win_condition.l1 = "location";
			pchar.quest.Headhunter_SeekHalen.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Headhunter_SeekHalen.win_condition = "Headhunter_MissHalen";
			pchar.quest.Headhunter_HalenTimer.win_condition.l1 = "Timer";
			pchar.quest.Headhunter_HalenTimer.win_condition.l1.date.hour = sti(GetTime() + 1);
			pchar.quest.Headhunter_HalenTimer.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			pchar.quest.Headhunter_HalenTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Headhunter_HalenTimer.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			pchar.quest.Headhunter_HalenTimer.win_condition = "Headhunter_HalenOut";
			CreateHalen();
			RemoveLandQuestMark_Main(npchar, "Headhunt");
			DialogExit();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = StringFromKey("Beliz_Citizen_3", RandPhraseSimple(
						StringFromKey("Beliz_Citizen_1"),
						StringFromKey("Beliz_Citizen_2")));
			link.l1 = StringFromKey("Beliz_Citizen_6", RandPhraseSimple(
						StringFromKey("Beliz_Citizen_4", pchar),
						StringFromKey("Beliz_Citizen_5")));
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Jiteli_Beliz") && npchar.sex == "man" && !CheckAttribute(npchar, "PDM_ONV_Vopros"))
			{
				link.l1 = StringFromKey("Beliz_Citizen_12", RandPhraseSimple(
	StringFromKey("Beliz_Citizen_10"),
	StringFromKey("Beliz_Citizen_11")));
				link.l1.go = "PDM_ONV_MAN";
			}
		break;

		case "info":
		// заменить на описание неких НПС, по квестам
			dialog.text = StringFromKey("Beliz_Citizen_7", NationNameGenitive(sti(NPChar.nation)));
			link.l1 = StringFromKey("Beliz_Citizen_8");
			link.l1.go = "exit";
			link.l2 = StringFromKey("Beliz_Citizen_9");
			link.l2.go = "new question";
		break;
		
//**************************Квест "Прокажённая"*******************************
		case "PDM_ONV_MAN":
			dialog.text = StringFromKey("Beliz_Citizen_13", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Beliz_Citizen_14");
			link.l1.go = "PDM_ONV_MAN_1";
		break;

		case "PDM_ONV_MAN_1":
			dialog.text = StringFromKey("Beliz_Citizen_15");
			link.l1 = StringFromKey("Beliz_Citizen_16");
			link.l1.go = "PDM_ONV_MAN_2";
		break;

		case "PDM_ONV_MAN_2":
			dialog.text = StringFromKey("Beliz_Citizen_17", pchar, GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Beliz_Citizen_18");
			link.l1.go = "exit";
			link.l2 = StringFromKey("Beliz_Citizen_19");
			link.l2.go = "exit";
			AddQuestRecord("PDM_Ohota_na_vedmu", "7");
			if (LanguageGetLanguage() == "russian") AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Jiteli_Beliz");
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Oficiantka_Beliz");
			pchar.questTemp.PDM_ONV_Detectiv_Tavern_Da = true;
			AddLandQuestMark_Main(CharacterFromID("Beliz_tavernkeeper"), "PDM_Ohota_na_vedmu");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sBlade;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int Plata1 = 34000 * MOD_SKILL_ENEMY_RATE * 0.21;
	int Plata2 = 34000 * MOD_SKILL_ENEMY_RATE * 0.31;

	pchar.PDM_NK_Plata2.Money = 35000 * MOD_SKILL_ENEMY_RATE * 0.31;

	int Sila = 25 + MOD_SKILL_ENEMY_RATE * 2.8;
	int DopHP = 40 + MOD_SKILL_ENEMY_RATE * 10;
	int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE * 1.2;
	if (Rank < 1) Rank = 1;

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time": //Автор Sinistra
			PlayVoice("Voice\" + VoiceGetLanguage() + "\PDM\Chto_vi_hoteli.wav");
			dialog.text = StringFromKey("Neputyovy_kaznachey_1");
			link.l1 = StringFromKey("Neputyovy_kaznachey_2", pchar.name);
			link.l1.go = "Fickler_1";
			RemoveLandQuestMark_Main(npchar, "PDM_Neputyovy_kaznachey");
			RemoveMapQuestMark("Villemstad_town", "PDM_Neputyovy_kaznachey");
		break;

		case "Fickler_1":
			dialog.text = StringFromKey("Neputyovy_kaznachey_3");
			link.l1 = StringFromKey("Neputyovy_kaznachey_4");
			link.l1.go = "Fickler_2";
		break;

		case "Fickler_2":
			dialog.text = StringFromKey("Neputyovy_kaznachey_5");
			link.l1 = StringFromKey("Neputyovy_kaznachey_6");
			link.l1.go = "Fickler_3";
		break;

		case "Fickler_3":
			dialog.text = StringFromKey("Neputyovy_kaznachey_7", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Neputyovy_kaznachey_8");
			link.l1.go = "Fickler_4";
		break;

		case "Fickler_4":
			dialog.text = StringFromKey("Neputyovy_kaznachey_9");
			link.l1 = StringFromKey("Neputyovy_kaznachey_10");
			link.l1.go = "Fickler_5";
		break;

		case "Fickler_5":
			dialog.text = StringFromKey("Neputyovy_kaznachey_11");
			link.l1 = StringFromKey("Neputyovy_kaznachey_12");
			link.l1.go = "Fickler_6";
			link.l2 = StringFromKey("Neputyovy_kaznachey_13");
			link.l2.go = "exit";
			NextDiag.TempNode = "Fickler_8";
		break;

		case "Fickler_6":
			dialog.text = StringFromKey("Neputyovy_kaznachey_14");
			link.l1 = StringFromKey("Neputyovy_kaznachey_15");
			link.l1.go = "exit";
			NextDiag.TempNode = "Fickler_7";

			sld = GetCharacter(NPC_GenerateCharacter("PDM_NK_Viktor", "officer_20", "man", "man", sti(pchar.rank) - 1 + MOD_SKILL_ENEMY_RATE, PIRATE, -1, true));
			sld.name = FindPersonalName("PDM_NK_Viktor_name");
			sld.lastname = FindPersonalName("PDM_NK_Viktor_lastname");
			FreeSitLocator("Villemstad_tavern", "sit12");
			sld.city = "Villemstad";
			sld.location = "Villemstad_tavern";
			sld.location.group = "sit";
			sld.location.locator = "sit12";
			LAi_SetSitType(sld);
			sld.dialog.filename = "Quest\PDM\Neputyovy_kaznachey.c";
			sld.dialog.currentnode = "Viktor";
			AddLandQuestMark_Main(sld, "PDM_Neputyovy_kaznachey");

			SetQuestHeader("PDM_Neputyovy_kaznachey");
			AddQuestRecord("PDM_Neputyovy_kaznachey", "1");
		break;

		case "Fickler_7":
			PlayVoice("Voice\" + VoiceGetLanguage() + "\PDM\Chto_vi_hoteli.wav");
			dialog.text = StringFromKey("Neputyovy_kaznachey_16");
			link.l1 = StringFromKey("Neputyovy_kaznachey_17");
			link.l1.go = "exit";
			NextDiag.TempNode = "Fickler_7";
		break;

		case "Fickler_8":
			PlayVoice("Voice\" + VoiceGetLanguage() + "\PDM\Chto_vi_hoteli.wav");
			dialog.text = StringFromKey("Neputyovy_kaznachey_18");
			link.l1 = StringFromKey("Neputyovy_kaznachey_19");
			link.l1.go = "Fickler_6";
			link.l2 = StringFromKey("Neputyovy_kaznachey_20");
			link.l2.go = "exit";
			NextDiag.TempNode = "Fickler_8";
		break;

		case "Viktor":
			PlayVoice("Voice\" + VoiceGetLanguage() + "\PDM\U_menya_ruki_cheshutsya.wav");
			dialog.text = StringFromKey("Neputyovy_kaznachey_21");
			link.l1 = StringFromKey("Neputyovy_kaznachey_22");
			link.l1.go = "Viktor_2";
		break;

		case "Viktor_2":
			dialog.text = StringFromKey("Neputyovy_kaznachey_23");
			link.l1 = StringFromKey("Neputyovy_kaznachey_24");
			link.l1.go = "Viktor_3";
		break;

		case "Viktor_3":
			dialog.text = StringFromKey("Neputyovy_kaznachey_25", pchar);
			link.l1 = StringFromKey("Neputyovy_kaznachey_26", pchar.name);
			link.l1.go = "Viktor_4";
		break;

		case "Viktor_4":
			dialog.text = StringFromKey("Neputyovy_kaznachey_27", pchar);
			link.l1 = StringFromKey("Neputyovy_kaznachey_28");
			link.l1.go = "Viktor_5";
		break;

		case "Viktor_5":
			dialog.text = StringFromKey("Neputyovy_kaznachey_29", FindMoneyString(Plata1));
			if (sti(pchar.Money) >= Plata2)
			{
				link.l1 = StringFromKey("Neputyovy_kaznachey_31", FindMoneyString(Plata1));
				link.l1.go = "Zaplati_ED";
			}
			else
			{
				link.l1 = StringFromKey("Neputyovy_kaznachey_32", FindMoneyString(Plata1));
				link.l1.go = "Zaplati_ED";
			}
			link.l2 = StringFromKey("Neputyovy_kaznachey_30");
			link.l2.go = "Viktor_Bitva";
			link.l3 = StringFromKey("Neputyovy_kaznachey_33");
			link.l3.go = "Konec";
			NextDiag.TempNode = "Viktor_VernulsyDengi";
		break;

		case "Zaplati_ED":
			dialog.text = StringFromKey("Neputyovy_kaznachey_34", Plata1, Plata2);
			if (sti(pchar.Money) >= Plata2)
			{
				link.l1 = StringFromKey("Neputyovy_kaznachey_36");
				link.l1.go = "Zaplati_2";
			}
			else
			{
				link.l1 = StringFromKey("Neputyovy_kaznachey_37", FindMoneyString(Plata2));
				link.l1.go = "exit";
			}
			if (GetCharacterSkill(pchar, "Commerce") >= 35 || GetCharacterSPECIAL(pchar, "Charisma") >= 5 && sti(pchar.Money) >= Plata1)
			{
				link.l2 = StringFromKey("Neputyovy_kaznachey_57");
				link.l2.go = "Zaplati_1";
			}
			link.l3 = StringFromKey("Neputyovy_kaznachey_35");
			link.l3.go = "Viktor_Bitva";
			NextDiag.TempNode = "Viktor_VernulsyDengi";
			AddQuestRecord("PDM_Neputyovy_kaznachey", "2");
			AddQuestUserData("PDM_Neputyovy_kaznachey", "sMoney", FindMoneyString(sti(pchar.PDM_NK_Plata2.Money)));
		break;

		case "Konec":
			DialogExit();

			sld = CharacterFromID("PDM_NK_Viktor");
			sld.lifeday = 0;
			sld.dialog.filename = "Quest\PDM\Neputyovy_kaznachey.c";
			sld.dialog.currentnode = "Viktor_Poka";

			sld = CharacterFromID("Andreas_Fickler");
			sld.lifeday = 0;

			AddQuestRecord("PDM_Neputyovy_kaznachey", "7");
			AddQuestUserData("PDM_Neputyovy_kaznachey", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("PDM_Neputyovy_kaznachey");
		break;

		case "Zaplati_ND":
			dialog.text = "";
			link.l1 = StringFromKey("Neputyovy_kaznachey_38");
			link.l1.go = "Viktor_Bitva";
			link.l2 = StringFromKey("Neputyovy_kaznachey_39");
			link.l2.go = "exit";
			NextDiag.TempNode = "Zaplati_ND";
		break;

		case "Zaplati_1":
			AddMoneyToCharacter(pchar, -sti(Plata1));
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			AddCharacterExpToSkill(pchar, "Commerce", 250);
			AddCharacterExpToSkill(pchar, "Sneak", 150);
			sld = CharacterFromID("PDM_NK_Viktor");
			sld.dialog.filename = "Quest\PDM\Neputyovy_kaznachey.c";
			sld.dialog.currentnode = "Viktor_Poka";
			sld.lifeday = 0;
			RemoveLandQuestMark_Main(sld, "PDM_Neputyovy_kaznachey");
			sld = CharacterFromID("Andreas_Fickler");
			sld.dialog.filename = "Quest\PDM\Neputyovy_kaznachey.c";
			sld.dialog.currentnode = "Fickler_11";
			AddLandQuestMark_Main(sld, "PDM_Neputyovy_kaznachey");
			AddQuestRecord("PDM_Neputyovy_kaznachey", "3");
			AddQuestUserData("PDM_Neputyovy_kaznachey", "sSex", GetSexPhrase("", "а"));
			DialogExit();
		break;

		case "Zaplati_2":
			AddMoneyToCharacter(pchar, -sti(Plata2));
			AddCharacterExpToSkill(pchar, "Leadership", 160);
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			sld = CharacterFromID("PDM_NK_Viktor");
			sld.dialog.filename = "Quest\PDM\Neputyovy_kaznachey.c";
			sld.dialog.currentnode = "Viktor_Poka";
			sld.lifeday = 0;
			RemoveLandQuestMark_Main(sld, "PDM_Neputyovy_kaznachey");
			sld = CharacterFromID("Andreas_Fickler");
			sld.dialog.filename = "Quest\PDM\Neputyovy_kaznachey.c";
			sld.dialog.currentnode = "Fickler_11";
			AddLandQuestMark_Main(sld, "PDM_Neputyovy_kaznachey");
			AddQuestRecord("PDM_Neputyovy_kaznachey", "3");
			AddQuestUserData("PDM_Neputyovy_kaznachey", "sSex", GetSexPhrase("", "а"));
			DialogExit();
		break;

		case "Viktor_Poka":
			PlayVoice("Voice\" + VoiceGetLanguage() + "\PDM\U_menya_ruki_cheshutsya.wav");
			dialog.text = StringFromKey("Neputyovy_kaznachey_40");
			link.l1 = StringFromKey("Neputyovy_kaznachey_41");
			link.l1.go = "exit";
			NextDiag.TempNode = "Viktor_Poka";
		break;

		case "Viktor_VernulsyDengi":
			PlayVoice("Voice\" + VoiceGetLanguage() + "\PDM\U_menya_ruki_cheshutsya.wav");
			dialog.text = StringFromKey("Neputyovy_kaznachey_42");
			link.l1 = StringFromKey("Neputyovy_kaznachey_43");
			link.l1.go = "Viktor_VernulsyDengi_2";
		break;

		case "Viktor_VernulsyDengi_2":
			dialog.text = StringFromKey("Neputyovy_kaznachey_44", pchar);
			if (sti(pchar.Money) >= Plata2)
			{
				link.l1 = StringFromKey("Neputyovy_kaznachey_45", FindMoneyString(Plata2));
				link.l1.go = "Zaplati_2";
			}
			else
			{
				link.l1 = StringFromKey("Neputyovy_kaznachey_46");
				link.l1.go = "exit";
			}
			link.l2 = StringFromKey("Neputyovy_kaznachey_47");
			link.l2.go = "Konec";
			NextDiag.TempNode = "Viktor_VernulsyDengi";
		break;

		case "Viktor_Bitva":
			dialog.text = StringFromKey("Neputyovy_kaznachey_48");
			link.l1 = StringFromKey("Neputyovy_kaznachey_49");
			link.l1.go = "fight_right_now";
			sld = CharacterFromID("PDM_NK_Viktor");
			sld.SaveItemsForDead = true;
			AddMoneyToCharacter(sld, 2500);
			GiveItem2Character(sld, "Litsenzia");
			GiveItem2Character(sld, "mineral9");
			AddItems(sld, "lamp", 1);
			AddItems(sld, "indian17", 1);
			AddItems(sld, "spyglass2", 1);

			PChar.quest.PDM_NK_Viktor.win_condition.l1 = "NPC_Death";
			PChar.quest.PDM_NK_Viktor.win_condition.l1.character = "PDM_NK_Viktor";
			PChar.quest.PDM_NK_Viktor.win_condition = "PDM_NK_Viktor";

			PChar.quest.PDM_NK_Litsenzia.win_condition.l1 = "item";
			PChar.quest.PDM_NK_Litsenzia.win_condition.l1.item = "Litsenzia";
			PChar.quest.PDM_NK_Litsenzia.win_condition = "PDM_NK_Litsenzia";
		break;

		case "fight_right_now":
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			RemoveLandQuestMark_Main(npchar, "PDM_Neputyovy_kaznachey");
		break;

		case "Fickler_11":
			PlayVoice("Voice\" + VoiceGetLanguage() + "\PDM\Chto_vi_hoteli.wav");
			dialog.text = StringFromKey("Neputyovy_kaznachey_50", pchar.name, GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Neputyovy_kaznachey_51");
			link.l1.go = "Fickler_12";

			RemoveLandQuestMark_Main(npchar, "PDM_Neputyovy_kaznachey");
		break;

		case "Fickler_12":
			dialog.text = StringFromKey("Neputyovy_kaznachey_52");
			link.l1 = StringFromKey("Neputyovy_kaznachey_53");
			link.l1.go = "Fickler_13";
			link.l2 = StringFromKey("Neputyovy_kaznachey_54");
			link.l2.go = "Fickler_NeNujen";
		break;

		case "Fickler_13":
			dialog.text = StringFromKey("Neputyovy_kaznachey_55");
			link.l1 = StringFromKey("Neputyovy_kaznachey_56");
			link.l1.go = "Fickler_Nanyat";
			sld = CharacterFromID("Andreas_Fickler");
			sld.Dialog.Filename = "Officer_Man.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			ChangeCharacterReputation(sld, 40);
			sld.rank = 8;
			SetSPECIAL(sld, 1, 2, 2, 6, 10, 2, 1);   //(Сила, Воспр, Выносл, Обаяние, Обуч, Реак, Удача)
			SetSelfSkill(sld, 5, 5, 5, 5, 1);        //(ЛО, СО, ТО, пистолеты, фортуна)
			SetShipSkill(sld, 5, 45, 1, 1, 1, 1, 1, 1, 1);    //(лидер, торг, точн, пушки, навиг, ремонт, аборд, защита, скрыт)
			sld.loyality = MAX_LOYALITY;
			sld.CompanionDisable = true;
			sld.AllowedPosts = "treasurer";
			SetCharacterPerk(sld, "BasicCommerce");
			SetCharacterPerk(sld, "ArtOfDeals");
			SetCharacterPerk(sld, "QuickCalculation");
			SetCharacterPerk(sld, "AdvancedCommerce");
			//черты
			SetCharacterPerk(sld, "Monomania");
			SetCharacterPerk(sld, "Stuttering");
			SetCharacterPerk(sld, "NoCaptain");
			sld.greeting = "GR_Andreas_Fickler";
			LAi_SetImmortal(sld, false);
		break;

		case "Fickler_NeNujen":
			AddQuestRecord("PDM_Neputyovy_kaznachey", "6");
			AddQuestUserData("PDM_Neputyovy_kaznachey", "sSex", GetSexPhrase("ся", "ась"));
			CloseQuestHeader("PDM_Neputyovy_kaznachey");
			sld = CharacterFromID("Andreas_Fickler");
			sld.lifeday = 0;
			LAi_CharacterDisableDialog(sld);
			DialogExit();
			Achievment_Set(ACH_Neputyovyy_kaznachey);
		break;

		case "Fickler_Nanyat":
			sld = CharacterFromID("Andreas_Fickler");
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			sld.OfficerWantToGo.DontGo = true;
			//sld.quest.OfficerPrice = sti(pchar.rank)*50; TODO_salary
			//LAi_SetActorType(sld);
			//LAi_ActorRunToLocation(sld, "reload", "reload2_back", "", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("PDM_Neputyovy_kaznachey", "5");
			AddQuestUserData("PDM_Neputyovy_kaznachey", "sSex", GetSexPhrase("ся", "ась"));
			CloseQuestHeader("PDM_Neputyovy_kaznachey");
			LAi_SetRolyPoly(sld, true); //неваляха
			DialogExit();
			Achievment_Set(ACH_Neputyovyy_kaznachey);
		break;

	}
}

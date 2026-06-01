void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":                                //Автор Sinistra
			dialog.text = StringFromKey("Cursed_Idol_1", pchar);
			link.l1 = StringFromKey("Cursed_Idol_2", pchar);
			link.l1.go = "Vstrecha_2";
			link.l2 = StringFromKey("Cursed_Idol_3", pchar);
			link.l2.go = "exit";
		break;

		case "Vstrecha_2":
			dialog.text = StringFromKey("Cursed_Idol_4", pchar, pchar.name);
			link.l1 = StringFromKey("Cursed_Idol_5");
			link.l1.go = "Vstrecha_3";
		break;

		case "Vstrecha_3":
			dialog.text = StringFromKey("Cursed_Idol_6", pchar);
			link.l1 = StringFromKey("Cursed_Idol_7");
			link.l1.go = "Vstrecha_4";
			link.l2 = StringFromKey("Cursed_Idol_8");
			link.l2.go = "Ne_Veru_1";
		break;

		case "Ne_Veru_1":
			dialog.text = StringFromKey("Cursed_Idol_9", pchar);
			link.l1 = StringFromKey("Cursed_Idol_10");
			link.l1.go = "exit";
			NextDiag.TempNode = "VstrechNetAgain_1";
			npchar.lifeday = 0;
			RemoveLandQuestMark_Main(npchar, "PDM_Cursed_Idol");
			RemoveMapQuestMark("LaVega_town", "PDM_Cursed_Idol");
		break;

		case "Vstrecha_4":
			DialogExit();

			sld = CharacterFromID("James_Callow");
			sld.dialog.filename = "Quest\PDM\Cursed_Idol.c";
			sld.dialog.currentnode = "Vstrecha_4_1";
			LAi_Fade("PDM_Callow_sadis_na_stul", "");
			FreeSitLocator("LaVega_tavern", "sit_front3");
		break;

		case "Vstrecha_4_1":
			dialog.text = StringFromKey("Cursed_Idol_11");
			link.l1 = StringFromKey("Cursed_Idol_12");
			link.l1.go = "Vstrecha_5";
		break;

		case "Vstrecha_5":
			dialog.text = StringFromKey("Cursed_Idol_13", pchar.name);
			link.l1 = StringFromKey("Cursed_Idol_14");
			link.l1.go = "Vstrecha_6";
		break;

		case "Vstrecha_6":
			dialog.text = StringFromKey("Cursed_Idol_15");
			link.l1 = StringFromKey("Cursed_Idol_16");
			link.l1.go = "Vstrecha_7";
		break;

		case "Vstrecha_7":
			dialog.text = StringFromKey("Cursed_Idol_17", pchar);
			link.l1 = StringFromKey("Cursed_Idol_18");
			link.l1.go = "Vstrecha_8";
		break;

		case "Vstrecha_8":
			dialog.text = StringFromKey("Cursed_Idol_19", pchar);
			link.l1 = StringFromKey("Cursed_Idol_20");
			link.l1.go = "Vstrecha_9";
		break;

		case "Vstrecha_9":
			dialog.text = StringFromKey("Cursed_Idol_21");
			link.l1 = StringFromKey("Cursed_Idol_22");
			link.l1.go = "Vstrecha_10";
		break;

		case "Vstrecha_10":
			dialog.text = StringFromKey("Cursed_Idol_23");
			link.l1 = StringFromKey("Cursed_Idol_24");
			link.l1.go = "Vstrecha_11";
		break;

		case "Vstrecha_11":
			dialog.text = StringFromKey("Cursed_Idol_25", pchar);
			link.l1 = StringFromKey("Cursed_Idol_26");
			link.l1.go = "VstrechaDa_1";
			link.l2 = StringFromKey("Cursed_Idol_27");
			link.l2.go = "VstrechaNet_1";
			LAi_SetSitType(npchar);
		break;

		case "VstrechaDa_1":
			dialog.text = StringFromKey("Cursed_Idol_28", pchar);
			link.l1 = StringFromKey("Cursed_Idol_29");
			link.l1.go = "CodDa_1";
			AddItemLog(pchar, "Cursed_idol", "1", StringFromKey("InfoMessages_173"), "Important_item");
			NextDiag.TempNode = "VstrechDaAgain_1";
		break;

		case "VstrechaNet_1":
			dialog.text = StringFromKey("Cursed_Idol_30", pchar);
			link.l1 = StringFromKey("Cursed_Idol_31");
			link.l1.go = "CodNet_1";
			NextDiag.TempNode = "VstrechNetAgain_1";
			npchar.lifeday = 0;
			RemoveLandQuestMark_Main(npchar, "PDM_Cursed_Idol");
			RemoveMapQuestMark("LaVega_town", "PDM_Cursed_Idol");
		break;

		case "CodDa_1":
			LAi_Fade("PDM_Callow_vstaem", "");

			SetQuestHeader("PDM_Cursed_Idol");
			AddQuestRecord("PDM_Cursed_Idol", "1");
			AddQuestUserData("PDM_Cursed_Idol", "sSex", GetSexPhrase("", "а"));

			sld = CharacterFromID("Providencia_Mayor");   //ссылается на персонажа
			ChangeCharacterAddressGroup(sld, "Providencia_town", "none", "");
			sld = GetCharacter(NPC_GenerateCharacter("PDM_Providencia_Mayor_Klon", "Edward_Colier", "man", "man", 30, PIRATE, -1, false));   //ссылается на клона
			sld.name = FindPersonalName("Providencia_Mayor_name");
			sld.lastname = FindPersonalName("Providencia_Mayor_lastname");
			sld.nation = PIRATE;
			LAi_SetSitType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			LAi_SetImmortal(sld, true);
			GiveItem2Character(sld, GUN_COMMON);
			GiveItem2Character(sld, BLADE_LONG);
			LAi_SetHuberType(sld);
			SetRandSPECIAL(sld);
			SetSelfSkill(sld, 90, 90, 90, 60, 70);
			sld.standUp = true; //вставать и нападать на врага
			ChangeCharacterAddressGroup(sld, "Providencia_townhall", "sit", "sit1");
			sld.Dialog.Filename = "Quest\PDM\Cursed_Idol.c";
			sld.dialog.currentnode = "Colier_1";
			AddLandQuestMark_Main(sld, "PDM_Cursed_Idol");
			//pchar.questTemp.PDM_PI_Skelety_v_more = "PDM_PI_Skelety_v_more";
			//SetTimerFunction("PDM_PI_Skelety_v_more", 0, 0, 5);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			RemoveLandQuestMark_Main(npchar, "PDM_Cursed_Idol");
			RemoveMapQuestMark("LaVega_town", "PDM_Cursed_Idol");
		break;

		case "CodNet_1":
			LAi_Fade("PDM_Callow_vstaem", "");

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "VstrechDaAgain_1":
			dialog.text = StringFromKey("Cursed_Idol_32");
			link.l1 = StringFromKey("Cursed_Idol_33");
			link.l1.go = "exit";
		break;

		case "VstrechNetAgain_1":
			dialog.text = StringFromKey("Cursed_Idol_34");
			link.l1 = StringFromKey("Cursed_Idol_35");
			link.l1.go = "exit";
		break;

		case "Colier_1":
			PlayVoice("Voice\" + VoiceGetLanguage() + "\PDM\Prikusi_Yazik.wav");
			dialog.text = StringFromKey("Cursed_Idol_36", pchar);
			link.l1 = StringFromKey("Cursed_Idol_37");
			link.l1.go = "Colier_2";

			Pchar.quest.PDM_Callow_ColierProdolg.win_condition.l1 = "Location";
			Pchar.quest.PDM_Callow_ColierProdolg.win_condition.l1.location = "Providencia_town";
			pchar.quest.PDM_Callow_ColierProdolg.function = "PDM_Callow_ColierProdolg";

			bDisableFastReload = true;
			LAi_LocationFightDisable(&Locations[FindLocation("Providencia_town")], true);
			SetLocationCapturedState("Providencia_town", true);

			sld = GetCharacter(NPC_GenerateCharacter("Pablo_Loco_Idol", "Winnetou", "man", "man_b", 10, PIRATE, -1, false));
			sld.Ghost = 0.6;
			sld.name = FindPersonalName("Pablo_Loco_Idol_name");
			sld.lastname = "";
			sld.talker = 7;
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\PDM\Cursed_Idol.c";
			sld.dialog.currentnode = "Pablo_Loco_Idol_Alternativa";
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, "Providencia_town", "goto", "goto16");
			AddLandQuestMark_Main(sld, "PDM_Cursed_Idol");
		break;

		case "Colier_2":
			dialog.text = StringFromKey("Cursed_Idol_38");
			link.l1 = StringFromKey("Cursed_Idol_39");
			link.l1.go = "Colier_3";
		break;

		case "Colier_3":
			dialog.text = StringFromKey("Cursed_Idol_40");
			link.l1 = StringFromKey("Cursed_Idol_41");
			link.l1.go = "Colier_4";
		break;

		case "Colier_4":
			dialog.text = StringFromKey("Cursed_Idol_42");
			link.l1 = StringFromKey("Cursed_Idol_43", pchar);
			link.l1.go = "ColierDa_1";
			link.l2 = StringFromKey("Cursed_Idol_44");
			link.l2.go = "ColierPodozren_1";
		break;

		case "ColierPodozren_1":
			dialog.text = StringFromKey("Cursed_Idol_45", pchar);
			link.l1 = StringFromKey("Cursed_Idol_46");
			link.l1.go = "ColierPodozren_2";
			link.l2 = StringFromKey("Cursed_Idol_47");
			link.l2.go = "ColierDa_2";
		break;

		case "ColierPodozren_2":
			dialog.text = StringFromKey("Cursed_Idol_48", pchar);
			link.l1 = "...";
			link.l1.go = "ColierCod_2";
			NextDiag.TempNode = "ColierPokapoka_1";
			ChangeCharacterReputation(pchar, -4);
		break;

		case "ColierDa_1":
			dialog.text = StringFromKey("Cursed_Idol_49", pchar);
			link.l1 = StringFromKey("Cursed_Idol_50");
			link.l1.go = "ColierDa_2";
		break;

		case "ColierDa_2":
			dialog.text = StringFromKey("Cursed_Idol_51");
			link.l1 = StringFromKey("Cursed_Idol_52");
			link.l1.go = "ColierVar_1";
			link.l2 = StringFromKey("Cursed_Idol_53");
			link.l2.go = "ColierVar_2";
			AddItemLog(pchar, "Cursed_idol", "-1", StringFromKey("InfoMessages_174"), "Important_item");
		break;

		case "ColierVar_1":
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				dialog.text = StringFromKey("Cursed_Idol_54");
				link.l1 = StringFromKey("Cursed_Idol_55");
				link.l1.go = "Colier_ZabirauKorabl";
				link.l2 = StringFromKey("Cursed_Idol_56");
				link.l2.go = "Colier_NetKorablya";
			}
			else
			{
				dialog.text = StringFromKey("Cursed_Idol_57", pchar);
				link.l1 = StringFromKey("Cursed_Idol_58");
				link.l1.go = "ColierCod_1";
				AddMoneyToCharacter(pchar, 1000);
			}
			NextDiag.TempNode = "ColierPokapoka_1";
		break;

		case "ColierVar_2":
			dialog.text = StringFromKey("Cursed_Idol_59", pchar);
			link.l1 = StringFromKey("Cursed_Idol_60");
			link.l1.go = "ColierCod_2";
			AddItemLog(pchar, "Cursed_idol", "1", StringFromKey("InfoMessages_175"), "Important_item");
			NextDiag.TempNode = "ColierPokapoka_1";
		break;

		case "ColierPokapoka_1":
			dialog.text = StringFromKey("Cursed_Idol_61");
			link.l1 = StringFromKey("Cursed_Idol_62");
			link.l1.go = "exit";
			NextDiag.TempNode = "ColierPokapoka_1";
		break;

		case "Colier_NetKorablya":
			dialog.text = StringFromKey("Cursed_Idol_63");
			link.l1 = StringFromKey("Cursed_Idol_64");
			link.l1.go = "Colier_ZabirauKorabl";
		break;

		case "Colier_ZabirauKorabl":
			aref aShip;
			pchar.questTemp.PDM_PI_Ship = true;
			ChangeCharacterReputation(pchar, -2);

			//Корабль Севилия помещается в портовое управление
			ref refNPCPortman = characterFromId("Providencia_PortMan");

			sTemp = refNPCPortman.id + "COILER_SHIP_" + SHIP_GALEON_L;
			makearef(aShip, refNPCPortman.ShipInStockMan.(sTemp));
			aShip.nation = 2;
			aShip.Ship.Type = GenerateShipExt(SHIP_GALEON_L, true, aShip);
			aShip.Ship.Name = FindPersonalName("Providencia_PortMan_ship");
			aShip.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;

			SetBaseShipData(aShip);
			SetCrewQuantity(aShip, 0);

			aShip.MoneyForShip = GetPortManPriceExt(refNPCPortman, pchar);
			aShip.AltDate = GetQuestBookDataDigit(); // для печати

			RealShips[sti(aShip.ship.type)].StoreShip = true;

			refNPCPortman.Portman = sti(refNPCPortman.Portman) + 1;
			pchar.ShipInStock = sti(pchar.ShipInStock) + 1;

			AddQuestRecord("PDM_Cursed_Idol", "3");

			pchar.questTemp.PDM_PI_Dengi = true;
			ChangeCharacterReputation(pchar, -2);
			SetCurrentTime(23, 1);

			RemoveLandQuestMark_Main(npchar, "PDM_Cursed_Idol");

			sld = CharacterFromID("James_Callow");
			AddLandQuestMark_Main(sld, "PDM_Cursed_Idol");

			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "ColierCod_1":
			AddQuestRecord("PDM_Cursed_Idol", "2");

			pchar.questTemp.PDM_PI_Dengi = true;
			ChangeCharacterReputation(pchar, -2);
			SetCurrentTime(23, 1);

			RemoveLandQuestMark_Main(npchar, "PDM_Cursed_Idol");

			sld = CharacterFromID("James_Callow");
			AddLandQuestMark_Main(sld, "PDM_Cursed_Idol");

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ColierCod_2":
			AddQuestRecord("PDM_Cursed_Idol", "4");
			AddQuestUserData("PDM_Cursed_Idol", "sSex1", GetSexPhrase("ен", "на"));

			sld = CharacterFromId("Pablo_Loco_Idol");
			sld.dialog.currentnode = "Pablo_Loco_Idol";

			pchar.questTemp.PDM_PI_NeVzyl = true;
			ChangeCharacterReputation(pchar, 4);
			SetCurrentTime(23, 1);

			RemoveLandQuestMark_Main(npchar, "PDM_Cursed_Idol");
			sld = CharacterFromID("James_Callow");
			AddLandQuestMark_Main(sld, "PDM_Cursed_Idol");

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Pablo_Loco_Idol":
			dialog.text = StringFromKey("Cursed_Idol_65");
			link.l1 = StringFromKey("Cursed_Idol_66");
			link.l1.go = "Pablo_Loco_Idol_2";
		break;

		case "Pablo_Loco_Idol_2":
			dialog.text = StringFromKey("Cursed_Idol_67");
			link.l1 = StringFromKey("Cursed_Idol_68", pchar);
			link.l1.go = "Pablo_Loco_Idol_fight";
			AddQuestRecord("PDM_Cursed_Idol", "6");
			npchar.lifeday = 0;
		break;

		case "Pablo_Loco_Idol_Alternativa":
			dialog.text = StringFromKey("Cursed_Idol_69", pchar);
			link.l1 = StringFromKey("Cursed_Idol_70");
			link.l1.go = "Pablo_Loco_Idol_Alternativa_2";
		break;

		case "Pablo_Loco_Idol_Alternativa_2":
			dialog.text = StringFromKey("Cursed_Idol_71");
			link.l1 = StringFromKey("Cursed_Idol_72");
			link.l1.go = "Pablo_Loco_Idol_Alternativa_3";
		break;

		case "Pablo_Loco_Idol_Alternativa_3":
			dialog.text = StringFromKey("Cursed_Idol_73");
			link.l1 = StringFromKey("Cursed_Idol_74");
			link.l1.go = "Pablo_Loco_Idol_Alternativa_4";
		break;

		case "Pablo_Loco_Idol_Alternativa_4":
			dialog.text = StringFromKey("Cursed_Idol_75");
			link.l1 = StringFromKey("Cursed_Idol_76");
			link.l1.go = "Pablo_Loco_Idol_fight";
			npchar.lifeday = 0;
			AddQuestRecord("PDM_Cursed_Idol", "5");
			AddQuestUserData("PDM_Cursed_Idol", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("PDM_Cursed_Idol", "sSex1", GetSexPhrase("ен", "на"));
			AddItemLog(pchar, "Cursed_idol", "1", StringFromKey("InfoMessages_176"), "Important_item");
		break;

		case "Pablo_Loco_Idol_fight":
			DialogExit();

			sld = CharacterFromID("Pablo_Loco_Idol");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "houseV4", "none", "", "", "", -1);
			sld.lifeday = 0;
			RemoveLandQuestMark_Main(sld, "PDM_Cursed_Idol");

			if (IsCharacterPerkOn(Pchar, "WildCaribbean"))
			{
				sld = GetCharacter(NPC_GenerateCharacter("PDM_Pinki_Skelet", "skel2", "skeleton", "man", sti(pchar.rank), PIRATE, -1, true));
				sld.skeleton = "1";
				sld.name = FindPersonalName("PDM_Pinki_Skelet_name");
				sld.lastname = FindPersonalName("PDM_Pinki_Skelet_lastname");
				sld.SaveItemsForDead = true;
				sld.DontChangeBlade = true;
				sld.DeleteFood = true;
				LAi_LoginInCaptureTown(sld, true);
				TakeItemFromCharacter(sld, "spyglass3");
				AddMoneyToCharacter(sld, 1000);
				AddItems(sld, "jewelry2", 5);
				AddItems(sld, "jewelry5", 4);
				AddItems(sld, "jewelry17", 3);
				AddItems(sld, "mineral5", 2);
				sld.dialog.filename = "Quest\PDM\Cursed_Idol.c";
				sld.dialog.currentnode = "FraOff_1";
				ChangeCharacterAddressGroup(sld, "Providencia_town", "reload", "houseD2");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);

				for (i = 7; i <= 8; i++)
				{
					sTemp = "skel" + (rand(3) + 1);
					sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_skel_" + i, sTemp, "skeleton", "man", sti(pchar.rank), PIRATE, -1, true));
					sld.skeleton = "1";
					LAi_SetActorType(sld);
					LAi_LoginInCaptureTown(sld, true);
					sld.lifeday = 1;
					SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
					ChangeCharacterAddressGroup(sld, "Providencia_town", "goto", "goto" + i);
				}
				for (i = 29; i <= 30; i++)
				{
					sTemp = "skel" + (rand(3) + 1);
					sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_skel_" + i, sTemp, "skeleton", "man", sti(pchar.rank), PIRATE, -1, true));
					sld.skeleton = "1";
					LAi_SetActorType(sld);
					LAi_LoginInCaptureTown(sld, true);
					sld.lifeday = 1;
					SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
					ChangeCharacterAddressGroup(sld, "Providencia_town", "goto", "goto" + i);
				}
				for (i = 37; i <= 39; i++)
				{
					sTemp = "skel" + (rand(3) + 1);
					sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_skel_" + i, sTemp, "skeleton", "man", sti(pchar.rank), PIRATE, -1, true));
					sld.skeleton = "1";
					LAi_SetActorType(sld);
					LAi_LoginInCaptureTown(sld, true);
					sld.lifeday = 1;
					SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
					ChangeCharacterAddressGroup(sld, "Providencia_town", "goto", "goto" + i);
				}
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("PDM_Pinki_Skelet", "pirate_6", "man", "man", sti(pchar.rank), PIRATE, -1, true));
				sld.name = FindPersonalName("PDM_Pinki_Skelet2_name");
				sld.lastname = FindPersonalName("PDM_Pinki_Skelet2_lastname");
				sld.SaveItemsForDead = true;
				sld.DontChangeBlade = true;
				//sld.DeleteFood = true;
				LAi_LoginInCaptureTown(sld, true);
				TakeItemFromCharacter(sld, "spyglass3");
				AddMoneyToCharacter(sld, 1000);
				AddItems(sld, "jewelry2", 5);
				AddItems(sld, "jewelry5", 4);
				AddItems(sld, "jewelry17", 3);
				AddItems(sld, "mineral16", 2);
				sld.dialog.filename = "Quest\PDM\Cursed_Idol.c";
				sld.dialog.currentnode = "FraOff_1";
				ChangeCharacterAddressGroup(sld, "Providencia_town", "reload", "houseD2");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);

				for (i = 7; i <= 8; i++)
				{
					sTemp = "pirate_" + (rand(3) + 1);
					sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_skel_" + i, sTemp, "man", "man", sti(pchar.rank), PIRATE, -1, true));
					LAi_SetActorType(sld);
					LAi_LoginInCaptureTown(sld, true);
					sld.lifeday = 1;
					SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
					ChangeCharacterAddressGroup(sld, "Providencia_town", "goto", "goto" + i);
				}
				for (i = 29; i <= 30; i++)
				{
					sTemp = "pirate_" + (rand(3) + 1);
					sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_skel_" + i, sTemp, "man", "man", sti(pchar.rank), PIRATE, -1, true));
					LAi_SetActorType(sld);
					LAi_LoginInCaptureTown(sld, true);
					sld.lifeday = 1;
					SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
					ChangeCharacterAddressGroup(sld, "Providencia_town", "goto", "goto" + i);
				}
				for (i = 37; i <= 39; i++)
				{
					sTemp = "pirate_" + (rand(3) + 1);
					sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_skel_" + i, sTemp, "man", "man", sti(pchar.rank), PIRATE, -1, true));
					LAi_SetActorType(sld);
					LAi_LoginInCaptureTown(sld, true);
					sld.lifeday = 1;
					SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
					ChangeCharacterAddressGroup(sld, "Providencia_town", "goto", "goto" + i);
				}
			}
		break;

		case "FraOff_1":
			if (IsCharacterPerkOn(Pchar, "WildCaribbean"))
			{
				dialog.text = StringFromKey("Cursed_Idol_79", RandPhraseSimple(
							StringFromKey("Cursed_Idol_77"),
							StringFromKey("Cursed_Idol_78")));
				link.l1 = StringFromKey("Cursed_Idol_82", RandPhraseSimple(
							StringFromKey("Cursed_Idol_80"),
							StringFromKey("Cursed_Idol_81")));
				link.l1.go = "FraOff_Bitva_1";
			}
			else
			{
				dialog.text = StringFromKey("Cursed_Idol_83");
				link.l1 = StringFromKey("Cursed_Idol_84");
				link.l1.go = "FraOff_Bitva_1";
			}
		break;

		case "FraOff_Bitva_1":
			LAi_LocationFightDisable(loadedLocation, false); //Разрешаем оружие
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("PDM_Pinki_Skelet");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PDM_PI_Skelety");

			for (i = 7; i <= 8; i++)
			{
				sld = CharacterFromID("PDM_PI_skel_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "PDM_PI_Skelety");
			}
			for (i = 29; i <= 30; i++)
			{
				sld = CharacterFromID("PDM_PI_skel_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "PDM_PI_Skelety");
			}
			for (i = 37; i <= 39; i++)
			{
				sld = CharacterFromID("PDM_PI_skel_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "PDM_PI_Skelety");
			}

			PChar.quest.PDM_PI_PinkiSkelet.win_condition.l1 = "NPC_Death";
			PChar.quest.PDM_PI_PinkiSkelet.win_condition.l1.character = "PDM_Pinki_Skelet";
			PChar.quest.PDM_PI_PinkiSkelet.win_condition = "PDM_FraOff_Bitva_1_Posle";
			LAi_group_SetRelation("PDM_PI_Skelety", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("PDM_PI_Skelety", LAI_GROUP_PLAYER, false);
			LAi_group_SetLookRadius("PDM_PI_Skelety", 7.0);
			LAi_group_SetHearRadius("PDM_PI_Skelety", 2.0);
			LAi_group_SetSayRadius("PDM_PI_Skelety", 4.0);
			DialogExit();
		break;

		/*case "CollowRad_1":
			dialog.text = "Ах! Наконец-то ты вернул"+ GetSexPhrase("ся","ась") +". Как идут дела? Ты всё сделал"+ GetSexPhrase("","а") +"?";
			link.l1 = "Конечно. Жадный мерзавец при виде золота потерял последние остатки разума.";
			link.l1.go = "CollowRad_2";
		break;

		case "CollowRad_2":
			dialog.text = "Агггх! Какое облегчение! Ты и представить себе не можешь, каким тяжким грузом это было для меня.";
			link.l1 = "Теперь ты свободен от его влияния. Но, я вспоминаю, что ты обещал стать моим офицером... как насчёт этого?";
			link.l1.go = "CollowRad_3";
		break;

		case "CollowRad_3":
			dialog.text = "Сказать по чести... Я солгал тебе, чтобы убедить тебя помочь мне. Очень жаль, "+ GetSexPhrase("брат","сестра") +", но я не собираюсь становиться твоим офицером. Возьми себе 10000 пиастров, в уплату за твою услугу...  я негодяй, но меня нельзя назвать неблагодарным негодяем. Прощай, "+ GetSexPhrase("брат","сестра") +".";
			link.l1 = "Почему-то меня это не удивляет. Ну что же - попутного тебе ветра, Кэллоу.";
			link.l1.go = "CollowRadCod_1";
			NextDiag.TempNode = "CollowRadPoka_1";
			AddMoneyToCharacter(pchar, 10000);
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			AddCharacterExpToSkill(pchar, "Sneak", 40);
		break;

		case "CollowRadPoka_1":
			dialog.text = "Ещё раз спасибо, "+ GetSexPhrase("брат","сестра") +".";
			link.l1 = "До встречи, Кэллоу.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CollowRadPoka_1";
		break;

		case "CollowRadCod_1":
			Pchar.quest.PDM_Callow_RadPoka.win_condition.l1           = "ExitFromLocation";
        	Pchar.quest.PDM_Callow_RadPoka.win_condition.l1.location  = "LaVega_Tavern";
        	Pchar.quest.PDM_Callow_RadPoka.win_condition              = "PDM_Callow_RadPoka";
			AddQuestRecord("PDM_Cursed_Idol", "3");
			CloseQuestHeader("PDM_Cursed_Idol");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;*/

		case "CollowNeRad_1":
			dialog.text = StringFromKey("Cursed_Idol_85", pchar);
			if (CheckAttribute(pchar, "questTemp.PDM_PI_Ship"))
			{
				link.l1 = StringFromKey("Cursed_Idol_86", pchar);
				link.l1.go = "CollowNeRad_Ship_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_PI_Dengi"))
			{
				link.l1 = StringFromKey("Cursed_Idol_87", pchar);
				link.l1.go = "CollowNeRad_Ship_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_PI_NeVzyl"))
			{
				link.l1 = StringFromKey("Cursed_Idol_88");
				link.l1.go = "CollowNeRad_NeVzyl_1";
			}
		break;

		case "CollowNeRad_Ship_1":
			DialogExit();

			sld = CharacterFromID("James_Callow");
			sld.dialog.filename = "Quest\PDM\Cursed_Idol.c";
			sld.dialog.currentnode = "CollowNeRad_Ship_2";
			LAi_Fade("PDM_Callow_sadis_na_stul", "");
			FreeSitLocator("LaVega_tavern", "sit_front3");
		break;

		case "CollowNeRad_Ship_2":
			dialog.text = StringFromKey("Cursed_Idol_89", pchar);
			link.l1 = StringFromKey("Cursed_Idol_90");
			link.l1.go = "CollowNeRad_3";
		break;

		case "CollowNeRad_NeVzyl_1":
			DialogExit();

			sld = CharacterFromID("James_Callow");
			sld.dialog.filename = "Quest\PDM\Cursed_Idol.c";
			sld.dialog.currentnode = "CollowNeRad_NeVzyl_2";
			LAi_Fade("PDM_Callow_sadis_na_stul", "");
			FreeSitLocator("LaVega_tavern", "sit_front3");
		break;

		case "CollowNeRad_NeVzyl_2":
			dialog.text = StringFromKey("Cursed_Idol_91", pchar);
			link.l1 = StringFromKey("Cursed_Idol_92");
			link.l1.go = "CollowNeRad_3";
		break;

		case "CollowNeRad_3":
			dialog.text = StringFromKey("Cursed_Idol_93", pchar);
			link.l1 = StringFromKey("Cursed_Idol_94");
			link.l1.go = "CollowNeRad_4";
			LAi_SetSitType(npchar);
		break;

		case "CollowNeRad_4":
			dialog.text = StringFromKey("Cursed_Idol_95");
			link.l1 = StringFromKey("Cursed_Idol_96");
			link.l1.go = "CollowNeRad_5";
			link.l2 = StringFromKey("Cursed_Idol_97");
			link.l2.go = "CollowOchenNeRad_1";
		break;

		case "CollowNeRad_5":
			dialog.text = StringFromKey("Cursed_Idol_98");
			link.l1 = StringFromKey("Cursed_Idol_99");
			link.l1.go = "CollowNeRad_6";
		break;

		case "CollowNeRad_6":
			if (CheckCharacterItem(Pchar, "patent_fra"))
			{
				dialog.text = StringFromKey("Cursed_Idol_100", pchar);
				link.l1 = StringFromKey("Cursed_Idol_101");
				link.l1.go = "CollowNeRad_7";
			}
			else
			{
				dialog.text = StringFromKey("Cursed_Idol_102", pchar);
				link.l1 = StringFromKey("Cursed_Idol_103");
				link.l1.go = "CollowNeRad_7";
			}
		break;

		case "CollowNeRad_7":
			dialog.text = StringFromKey("Cursed_Idol_104", pchar);
			link.l1 = StringFromKey("Cursed_Idol_105");
			link.l1.go = "CollowNeRad_8";
			NextDiag.TempNode = "VstrechEsheAgain_2";
		break;

		case "CollowNeRad_8":
			LAi_Fade("PDM_Callow_vstaem", "");

			pchar.questTemp.PDM_PI_Rostov = "PDM_PI_Rostov";
			AddQuestRecord("PDM_Cursed_Idol", "10");

			RemoveLandQuestMark_Main(npchar, "PDM_Cursed_Idol");
			AddLandQuestMark_Main(CharacterFromID("Tortuga_Usurer"), "PDM_Cursed_Idol");

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "CollowOchenNeRad_1":
			dialog.text = StringFromKey("Cursed_Idol_106", pchar);
			link.l1 = StringFromKey("Cursed_Idol_107");
			link.l1.go = "CollowOchenNeRad_2";
		break;

		case "CollowOchenNeRad_2":
			dialog.text = StringFromKey("Cursed_Idol_108", pchar);
			link.l1 = StringFromKey("Cursed_Idol_109", pchar);
			link.l1.go = "CollowOchenNeRad_3";
			AddItemLog(pchar, "Cursed_idol", "-1", StringFromKey("InfoMessages_177"), "Important_item");
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddCharacterExpToSkill(pchar, "Sneak", -150);
		//DeleteAttribute(pchar, "questTemp.PDM_PI_Skelety_v_more");
		//ChangeCharacterReputation(pchar, 5);
		break;

		case "CollowOchenNeRad_3":
			dialog.text = "...";
			link.l1 = StringFromKey("Cursed_Idol_110");
			link.l1.go = "CollowOchenNeRad_4";
			sld = CharacterFromID("James_Callow");
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LaVega_tavern", "officers", "reload1_1");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3);
		break;

		case "CollowOchenNeRad_4":
			AddQuestRecord("PDM_Cursed_Idol", "7");
			AddQuestUserData("PDM_Cursed_Idol", "sSex", GetSexPhrase("ся", "ась"));
			ChangeCharacterAddressGroup(pchar, "LaVega_tavern", "tables", "stay1");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			ChangeCharacterAddressGroup(sld, "LaVega_town", "none", "");
			pchar.quest.PDM_Callow_Voina.win_condition.l1 = "location";
			pchar.quest.PDM_Callow_Voina.win_condition.l1.location = "Hispaniola1";
			PChar.quest.PDM_Callow_Voina.win_condition = "PDM_Callow_Voina";

			RemoveLandQuestMark_Main(npchar, "PDM_Cursed_Idol");

			DialogExit();
		break;

		case "VstrechEsheAgain_2":
			dialog.text = StringFromKey("Cursed_Idol_111");
			link.l1 = StringFromKey("Cursed_Idol_112");
			link.l1.go = "exit";
			NextDiag.TempNode = "VstrechEsheAgain_2";
		break;

		case "Rostovshik_Fra_Off_1":
			dialog.text = StringFromKey("Cursed_Idol_113");
			link.l1 = "";
			link.l1.go = "Rostovshik_Fra_Off_1a";
		break;

		case "Rostovshik_Fra_Off_1a":
			DialogExit();
			StartInstantDialog("Tortuga_usurer", "Rostovshik_Fra_Off_1b", "Quest\PDM\Cursed_Idol.c");
		break;

		case "Rostovshik_Fra_Off_1b":
			dialog.text = StringFromKey("Cursed_Idol_114", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Cursed_Idol_115");
			link.l1.go = "Rostovshik_Fra_Off_1c";
		break;

		case "Rostovshik_Fra_Off_1c":
			DialogExit();
			StartInstantDialog("PDM_PI_Bandit_1", "Rostovshik_Fra_Off_1_1", "Quest\PDM\Cursed_Idol.c");
		break;

		case "Rostovshik_Fra_Off_1_1":
			dialog.text = StringFromKey("Cursed_Idol_116");
			link.l1 = StringFromKey("Cursed_Idol_117");
			link.l1.go = "Rostovshik_Mochilovo_1";
			pchar.questTemp.PDM_CI_RostBlago = "PDM_CI_RostBlago";
		break;

		case "Rostovshik_Fra_Off_2":
			dialog.text = StringFromKey("Cursed_Idol_118");
			link.l1 = StringFromKey("Cursed_Idol_119");
			link.l1.go = "Rostovshik_Fra_Off_2_2";
		break;

		case "Rostovshik_Fra_Off_2_2":
			DialogExit();
			StartInstantDialog("Tortuga_usurer", "Rostovshik_Fra_Off_2_3", "Quest\PDM\Cursed_Idol.c");
		break;

		case "Rostovshik_Fra_Off_2_3":
			dialog.text = StringFromKey("Cursed_Idol_120");
			link.l1 = StringFromKey("Cursed_Idol_121", UpperFirst(GetAddress_FormToNPC(NPChar)));
			link.l1.go = "Rostovshik_Fra_Off_2_4";
		break;

		case "Rostovshik_Fra_Off_2_4":
			dialog.text = StringFromKey("Cursed_Idol_122");
			link.l1 = StringFromKey("Cursed_Idol_123");
			link.l1.go = "Rostovshik_Fra_Off_2_5";
		break;

		case "Rostovshik_Fra_Off_2_5":
			DialogExit();
			StartInstantDialog("PDM_PI_Bandit_1", "Rostovshik_Fra_Off_2_6", "Quest\PDM\Cursed_Idol.c");
		break;

		case "Rostovshik_Fra_Off_2_6":
			dialog.text = StringFromKey("Cursed_Idol_124");
			link.l1 = StringFromKey("Cursed_Idol_125");
			link.l1.go = "Rostovshik_Mochilovo_2";

			sld = characterFromID("Tortuga_usurer");
			sld.Dialog.Filename = "Common_Usurer.c";
			RemoveLandQuestMark_Main(sld, "PDM_Cursed_Idol");
		break;

		case "Rostovshik_Fra_Off_3":
			dialog.text = StringFromKey("Cursed_Idol_126", pchar);
			link.l1 = StringFromKey("Cursed_Idol_127");
			link.l1.go = "Rostovshik_Fra_Off_3_1";
		break;

		case "Rostovshik_Fra_Off_3_1":
			sld = characterFromID("Tortuga_usurer");
			ChangeCharacterAddressGroup(sld, "Tortuga_Town", "none", "");

			sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Skel_Rostov", "skel2", "skeleton", "man", 2, PIRATE, -1, true));
			sld.skeleton = "1";
			sld.name = FindPersonalName("whouserers");
			sld.lastname = "";
			ChangeCharacterAddressGroup(sld, "Tortuga_Bank", "barmen", "stay");
			sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Bandity_2", "skel4", "skeleton", "man", 2, PIRATE, -1, true));
			sld.skeleton = "1";
			ChangeCharacterAddressGroup(sld, "Tortuga_Bank", "reload", "reload2");

			DialogExit();
			StartInstantDialog("PDM_PI_Skel_Rostov", "Rostovshik_Fra_Off_3_2", "Quest\PDM\Cursed_Idol.c");
		break;

		case "Rostovshik_Fra_Off_3_2":
			dialog.text = StringFromKey("Cursed_Idol_128");
			link.l1 = StringFromKey("Cursed_Idol_129", UpperFirst(GetAddress_FormToNPC(NPChar)));
			link.l1.go = "Rostovshik_Mochilovo_3";
		break;

		case "Rostovshik_Mochilovo_1":
			LAi_LocationFightDisable(loadedLocation, false); //Разрешаем оружие
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("PDM_PI_Bandit_1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for (i = 1; i <= 2; i++)
			{
				sTemp = "pirate_" + (rand(9) + 1);
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Bandity_" + i, sTemp, "man", "man", 2, PIRATE, -1, true));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);        //стравливаем
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PDM_Callow_poradomoy");
			chrDisableReloadToLocation = true;
			LAi_SetFightMode(pchar, true);
			DialogExit();
		break;

		case "Rostovshik_Mochilovo_2":
			LAi_LocationFightDisable(loadedLocation, false); //Разрешаем оружие
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("PDM_PI_Bandit_1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for (i = 1; i <= 2; i++)
			{
				sTemp = "urban_fra_" + (rand(7) + 1);
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Bandity_" + i, sTemp, "man", "man", 2, PIRATE, -1, true));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);        //стравливаем
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PDM_Callow_poradomoy");
			chrDisableReloadToLocation = true;
			LAi_SetFightMode(pchar, true);
			DialogExit();
		break;

		case "Rostovshik_Mochilovo_3":
			LAi_LocationFightDisable(loadedLocation, false); //Разрешаем оружие
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("PDM_PI_Bandit_1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PDM_PI_Skel_Rostov");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PDM_PI_Bandity_2");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);        //стравливаем
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PDM_Callow_poradomoy");
			chrDisableReloadToLocation = true;
			LAi_SetFightMode(pchar, true);
			DialogExit();
		break;

		case "Callow_POBEDA_1":
			dialog.text = StringFromKey("Cursed_Idol_130", pchar);
			link.l1 = StringFromKey("Cursed_Idol_131");
			link.l1.go = "Callow_POBEDA_2";
		break;

		case "Callow_POBEDA_2":
			DialogExit();

			sld = CharacterFromID("James_Callow");
			sld.dialog.filename = "Quest\PDM\Cursed_Idol.c";
			sld.dialog.currentnode = "Callow_POBEDA_2_1";
			LAi_Fade("PDM_Callow_sadis_na_stul", "");
			FreeSitLocator("LaVega_tavern", "sit_front3");
		break;

		case "Callow_POBEDA_2_1":
			dialog.text = StringFromKey("Cursed_Idol_132");
			link.l1 = StringFromKey("Cursed_Idol_133");
			link.l1.go = "Callow_POBEDA_3";
			AddCharacterExpToSkill(pchar, "Leadership", 150);    //добавить опыт к лидерству
			AddCharacterExpToSkill(pchar, "Pistol", 100);            //добавить опыт к пистолетам
			AddCharacterExpToSkill(pchar, "Fortune", 100);            //добавить опыт к удаче
			AddCharacterExpToSkill(pchar, "Sneak", 100);            //добавить опыт к скрытности
			sld = CharacterFromID("Tortuga_usurer");                //возвращаем ростовщика, если на скелетах убили
			ChangeCharacterAddressGroup(sld, "Tortuga_Bank", "barmen", "stay");
		break;

		case "Callow_POBEDA_3":
			dialog.text = StringFromKey("Cursed_Idol_134", pchar);
			link.l1 = StringFromKey("Cursed_Idol_135");
			link.l1.go = "Callow_POBEDA_4";
		break;

		case "Callow_POBEDA_4":
			dialog.text = "";
			link.l1 = StringFromKey("Cursed_Idol_136");
			link.l1.go = "FINAL";
			sld = CharacterFromID("James_Callow");
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.rank = 8;
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "ByWorker");
			//черты
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "LoyalOff");
			SetCharacterPerk(sld, "Rebel");
			LAi_SetHP(sld, 250.0, 250.0);
			SetSPECIAL(sld, 9, 8, 9, 4, 10, 8, 8);        //(Сила, Воспр, Выносл, Лидер, Обуч, Реак, Удача)
			SetSelfSkill(sld, 14, 35, 15, 25, 0);        //(ЛО, СО, ТО, пистолеты, фортуна)
			SetShipSkill(sld, 5, 3, 55, 45, 25, 5, 15, 8, 10);    //(лидер, торг, точн, пушки, навиг, ремонт, аборд, защита, скрыт)
			sld.greeting = "GR_Jamescallow";
			sld.Dialog.Filename = "Officer_Man.c";
			sld.Payment = true;                                        //Оплата труда
			//sld.quest.OfficerPrice = sti(pchar.rank)*500; TODO_salary
			sld.OfficerWantToGo.DontGo = true;
			sld.reputation = -3;
			LAi_SetImmortal(sld, false);
			//sld.HalfImmortal = true; 							    //Контузия
			sld.loyality = MAX_LOYALITY;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			LAi_SetActorType(npchar);   //делает нпс актёром
			ChangeCharacterAddressGroup(npchar, "LaVega_tavern", "tables", "stay1");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3);  // идёт в определённый локатор.
		break;

		case "FINAL":
			LAi_Fade("PDM_Callow_vstaem", "");

			RemoveLandQuestMark_Main(npchar, "PDM_Cursed_Idol");

			AddQuestRecord("PDM_Cursed_Idol", "12");
			CloseQuestHeader("PDM_Cursed_Idol");
			sld = CharacterFromID("James_Callow");
			LAi_SetRolyPoly(sld, true); //неваляха
			ChangeCharacterAddressGroup(sld, "LaVega_town", "none", "");
			//AddSimpleRumourToAllNations("На Тортуге ростовщика нашли мёртвым в подсобке, доктор гарнизонный сказал, что от страха умер. Невероятно! А стены все измалёваны изображениями идола языческого.", 30, 1);
			DeleteAttribute(pchar, "questTemp.PDM_CI_RostBlago");

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			Achievment_Set(ACH_Proklyatyy_idol);
		break;

		case "Matros_preduprejdaet":
			dialog.text = StringFromKey("Cursed_Idol_137");
			link.l1 = StringFromKey("Cursed_Idol_138");
			link.l1.go = "exit";
			AddDialogExitQuest("PDM_PI_Skelety_on_Ship_3");
		break;
	}
}

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = StringFromKey("Marginpassenger_1");
			link.l1 = StringFromKey("Marginpassenger_2");
			link.l1.go = "exit";
		break;

		///КАПИТАН КОРАБЛЯ
		//разговор на палубе
		case "MarginCap":
			dialog.text = StringFromKey("Marginpassenger_3");
			link.l1 = StringFromKey("Marginpassenger_4", GetAddress_FormToNPC(NPChar), pchar.GenQuest.Marginpassenger.q1Name);
			link.l1.go = "MarginCap_1";
		break;

		case "MarginCap_1":
			dialog.text = StringFromKey("Marginpassenger_5");
			link.l1 = StringFromKey("Marginpassenger_6", GetAddress_FormToNPC(NPChar));
			link.l1.go = "MarginCap_2";
		break;

		case "MarginCap_2":
		//TODO: убеждение не только по сопоставлению сил, которое даже количество команды не учитывает, господи
		//6 оставлено, пусть за 7-ой класс вообще минус будет
			int MCparam = (6 - sti(RealShips[sti(pchar.ship.type)].Class)) * 100 + sti(pchar.ship.Crew.Morale) + sti(pchar.Ship.Crew.Exp.Sailors) + sti(pchar.Ship.Crew.Exp.Cannoners) + sti(pchar.Ship.Crew.Exp.Soldiers);
			int NPCparam = (6 - sti(RealShips[sti(npchar.ship.type)].Class)) * 100 + sti(npchar.ship.Crew.Morale) + sti(npchar.Ship.Crew.Exp.Sailors) + sti(npchar.Ship.Crew.Exp.Cannoners) + sti(npchar.Ship.Crew.Exp.Soldiers);
			if (MCparam > NPCparam)//отдаст сам
			{
				dialog.text = StringFromKey("Marginpassenger_7");
				link.l1 = StringFromKey("Marginpassenger_8");
				link.l1.go = "MarginCap_3";
			}
			else
			{
				dialog.text = StringFromKey("Marginpassenger_9", pchar);
				link.l1 = StringFromKey("Marginpassenger_10", pchar, GetAddress_FormToNPC(NPChar));
				link.l1.go = "MarginCap_4";
			}
		break;

		case "MarginCap_3":
			DialogExit();
			float locx, locy, locz;
			npchar.Dialog.CurrentNode = "MarginCap_repeat";
			//отдаем пассажира
			sld = GetCharacter(NPC_GenerateCharacter("MarginPass", pchar.GenQuest.Marginpassenger.model, pchar.GenQuest.Marginpassenger.sex, pchar.GenQuest.Marginpassenger.ani, 2, sti(pchar.GenQuest.Marginpassenger.Nation), -1, true));
			sld.Dialog.Filename = "Quest\Marginpassenger.c";
			sld.Dialog.currentnode = "MarginPass";
			sld.name = pchar.GenQuest.Marginpassenger.q1Name;
			sld.lastname = "";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			Map_ReleaseQuestEncounter(npchar.id);
			npchar.Abordage.Enable = false; // запрет абордажа
			npchar.ShipEnemyDisable = true;
			npchar.AlwaysFriend = true;
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;

		case "MarginCap_4":
			DialogExit();
			NextDiag.CurrentNode = "MarginCap_repeat";
			pchar.GenQuest.Marginpassenger.Mustboarding = "true";
			AddQuestRecord("Marginpassenger", "5");
			AddQuestUserData("Marginpassenger", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name") + "Acc")));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;

		case "MarginCap_repeat":
			dialog.text = StringFromKey("Marginpassenger_11");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarginCap_repeat";
		break;

		case "MarginCap_abordage":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Mustboarding"))
			{
				dialog.text = StringFromKey("Marginpassenger_12", pchar);
				link.l1 = StringFromKey("Marginpassenger_13", pchar);
				link.l1.go = "MarginCap_abordage_1";
			}
			else
			{
				dialog.text = StringFromKey("Marginpassenger_14", pchar);
				link.l1 = StringFromKey("Marginpassenger_15", pchar.GenQuest.Marginpassenger.q1Name);
				link.l1.go = "MarginCap_abordage_2";
			}
		break;

		case "MarginCap_abordage_1":
			dialog.text = StringFromKey("Marginpassenger_16", pchar);
			link.l1 = StringFromKey("Marginpassenger_17");
			link.l1.go = "MarginCap_abordage_3";
		break;

		case "MarginCap_abordage_2":
			dialog.text = StringFromKey("Marginpassenger_18", pchar);
			link.l1 = StringFromKey("Marginpassenger_19");
			link.l1.go = "MarginCap_abordage_3";
		break;

		case "MarginCap_abordage_3":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Marginpassenger_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		///ПЛЕННИК
		case "MarginPass":
			dialog.text = StringFromKey("Marginpassenger_20");
			link.l1 = StringFromKey("Marginpassenger_21", npchar);
			link.l1.go = "MarginPass_1";
		break;

		case "MarginPass_1":
			dialog.text = StringFromKey("Marginpassenger_22", npchar);
			link.l1 = StringFromKey("Marginpassenger_23", npchar);
			link.l1.go = "MarginPass_2";
		break;

		case "MarginPass_2":
			dialog.text = StringFromKey("Marginpassenger_24");
			link.l1 = StringFromKey("Marginpassenger_25", npchar);
			link.l1.go = "MarginPass_3";
		break;

		case "MarginPass_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "", "", "none", "", "", "", 1.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.Marginpassenger_InWorldOver.over = "yes"; //снять прерывание
			pchar.quest.Marginpassenger_Sink.over = "yes"; //снять прерывание
			pchar.GenQuest.Marginpassenger = "take";
			if (rand(2) == 1) pchar.GenQuest.Marginpassenger.lose = "true"; //33%, что выкупатель двинет коней
			else Marginpassenger_CreateNeedman();
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Boarding")) AddQuestRecord("Marginpassenger", "6");
			else AddQuestRecord("Marginpassenger", "4");
			AddQuestUserData("Marginpassenger", "sSex", GetSexPhrase("", "ла"));
			AddQuestUserData("Marginpassenger", "sSex1", GetSexPhrase("", "а"));
			AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name") + "Acc")));
		break;

		///ВЫКУПАТЕЛЬ
		case "MarginNeed":
			dialog.text = StringFromKey("Marginpassenger_26", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Marginpassenger_27", pchar.GenQuest.Marginpassenger.q2Name);
			link.l1.go = "MarginNeed_1";
		break;

		case "MarginNeed_1":
			dialog.text = StringFromKey("Marginpassenger_28");
			link.l1 = StringFromKey("Marginpassenger_29", pchar.GenQuest.Marginpassenger.q1Name);
			link.l1.go = "MarginNeed_2";
		break;

		case "MarginNeed_2":
			switch (pchar.GenQuest.Marginpassenger.sex)
			{
				case "woman":
					dialog.text = StringFromKey("Marginpassenger_30");
					link.l1 = StringFromKey("Marginpassenger_31", pchar);
					link.l1.go = "MarginNeed_woman";
				break;
				case "man":
					dialog.text = StringFromKey("Marginpassenger_32");
					link.l1 = StringFromKey("Marginpassenger_33", pchar);
					link.l1.go = "MarginNeed_man";
				break;
			}
		break;

		case "MarginNeed_woman":
			dialog.text = StringFromKey("Marginpassenger_34");
			link.l1 = StringFromKey("Marginpassenger_35", pchar);
			link.l1.go = "MarginNeed_woman_1";
		break;

		case "MarginNeed_woman_1":
			dialog.text = StringFromKey("Marginpassenger_36");
			link.l1 = StringFromKey("Marginpassenger_37");
			link.l1.go = "MarginNeed_money";
		break;

		case "MarginNeed_man":
			dialog.text = StringFromKey("Marginpassenger_38");
			link.l1 = StringFromKey("Marginpassenger_39", pchar);
			link.l1.go = "MarginNeed_man_1";
		break;

		case "MarginNeed_man_1":
			dialog.text = StringFromKey("Marginpassenger_40");
			link.l1 = StringFromKey("Marginpassenger_41");
			link.l1.go = "MarginNeed_money";
		break;

		case "MarginNeed_money":
			dialog.text = StringFromKey("Marginpassenger_42");
			Link.l1.edit = 1;
			link.l1 = "";
			link.l1.go = "MarginNeed_money_1";
		break;

		case "MarginNeed_money_1":
			iTemp = sti(stripblank(dialogEditStrings[1]));
			int iSum = makeint(sti(pchar.GenQuest.Marginpassenger.Money) * 5 * stf(pchar.GenQuest.Marginpassenger.Chance));
			if (iTemp <= 0)
			{
				dialog.text = StringFromKey("Marginpassenger_43");
				link.l1 = StringFromKey("Marginpassenger_44");
				link.l1.go = "MarginNeed_exit";
				break;
			}
			if (iTemp > 0 && iTemp <= iSum)
			{
				dialog.text = StringFromKey("Marginpassenger_45", pchar.GenQuest.Marginpassenger.q1Name);
				link.l1 = StringFromKey("Marginpassenger_46");
				link.l1.go = "MarginNeed_payment";
				break;
			}
			if (iTemp > iSum && iTemp <= 100000)
			{
				dialog.text = StringFromKey("Marginpassenger_47");
				link.l1 = StringFromKey("Marginpassenger_48");
				link.l1.go = "MarginNeed_exit";
				break;
			}
			if (iTemp > 100000 && iTemp <= 250000)
			{
				dialog.text = StringFromKey("Marginpassenger_49", pchar);
				link.l1 = StringFromKey("Marginpassenger_50");
				link.l1.go = "MarginNeed_exit";
				break;
			}
			dialog.text = StringFromKey("Marginpassenger_51", pchar);
			link.l1 = StringFromKey("Marginpassenger_52");
			link.l1.go = "MarginNeed_exit";
		break;

		case "MarginNeed_payment":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(stripblank(dialogEditStrings[1]));
			int iChestQty = makeint(iTemp / 12000);
			int iMoney = iTemp - iChestQty * 12000;
			if (iChestQty > 0)
			{
				AddItemLog(pchar, "chest", its(iChestQty), StringFromKey("InfoMessages_134"), "Important_item");
				AddQuestRecord("Marginpassenger", "9");
				AddQuestUserData("Marginpassenger", "sSum", GetTextChestsQuantity(iChestQty));
				sTemp = "";
				if (iMoney > 0)
					sTemp += StringFromKey("Marginpassenger_53", FindMoneyString(iMoney));
				AddQuestUserData("Marginpassenger", "sMoney", sTemp);
			}
			else
			{
				AddQuestRecord("Marginpassenger", "10");
				AddQuestUserData("Marginpassenger", "sSum", FindMoneyString(iTemp));
			}
			pchar.money = sti(pchar.money) + iMoney; //здесь лог не нужен
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 100); //везение
		break;

		case "MarginNeed_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Marginpassenger", "11");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.City));
			AddQuestUserData("Marginpassenger", "sBaron", FindCityMayorName("LeFransua")); //TODO: ветвление, если будет доступно смещение Роджерса
			pchar.GenQuest.Marginpassenger = "cabin";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

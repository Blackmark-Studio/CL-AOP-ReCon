// Тичингиту - индеец-офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, iTemp;
	string sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	sAttr = Dialog.CurrentNode;

	switch (Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = StringFromKey("Tichingitu_1");
			link.l1 = StringFromKey("Tichingitu_2");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "NiceDayLSC":
			if (pchar.questTemp.LSC == "over")
			{
				dialog.text = StringFromKey("Tichingitu_3");
				link.l1 = StringFromKey("Tichingitu_4");
			}
			else
			{
				dialog.text = StringFromKey("Tichingitu_5");
				link.l1 = StringFromKey("Tichingitu_6");
			}
			NextDiag.TempNode = "NiceDayLSC";
			link.l1.go = "exit";
		break;

		case "Tichingitu":
			dialog.text = StringFromKey("Tichingitu_7", pchar);
			link.l1 = StringFromKey("Tichingitu_8", pchar);
			link.l1.go = "Tichingitu_1";
		break;

		case "Tichingitu_1":
			dialog.text = "";
			link.l1 = StringFromKey("Tichingitu_9");
			link.l1.go = "Tichingitu_2";
		break;

		case "Tichingitu_2":
			dialog.text = StringFromKey("Tichingitu_10");
			link.l1 = StringFromKey("Tichingitu_11");
			link.l1.go = "Tichingitu_3";
		break;

		case "Tichingitu_3":
			dialog.text = StringFromKey("Tichingitu_12");
			link.l1 = StringFromKey("Tichingitu_13");
			link.l1.go = "Tichingitu_4";
		break;

		case "Tichingitu_4":
			dialog.text = StringFromKey("Tichingitu_14");
			link.l1 = StringFromKey("Tichingitu_15");
			link.l1.go = "Tichingitu_5";
		break;

		case "Tichingitu_5":
			dialog.text = StringFromKey("Tichingitu_16", pchar);
			link.l1 = StringFromKey("Tichingitu_17");
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
			pchar.questTemp.Tichingitu = "commandante";
		break;

		case "Tichingitu_wait":
			dialog.text = StringFromKey("Tichingitu_18");
			link.l1 = StringFromKey("Tichingitu_19");
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
		break;

		case "Tichingitu_6":
			dialog.text = StringFromKey("Tichingitu_20");
			link.l1 = StringFromKey("Tichingitu_21", pchar);
			link.l1.go = "Tichingitu_7";
		break;

		case "Tichingitu_7":
			dialog.text = StringFromKey("Tichingitu_22", pchar);
			link.l1 = StringFromKey("Tichingitu_23");
			link.l1.go = "Tichingitu_8";
		break;

		case "Tichingitu_8":
			DialogExit();
			bDisableLandEncounters = true;
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation("BasTer_exittown", "rld", "aloc9", "TichingituFree"); // 170712
			pchar.quest.FreeTichingituOver.over = "yes"; //снять таймер
			ChangeIndianRelation(8.0);
		break;

		case "Tichingitu_9":
			dialog.text = "";
			link.l1 = StringFromKey("Tichingitu_24");
			link.l1.go = "Tichingitu_10";
			bDisableLandEncounters = false;
			chrDisableReloadToLocation = false;
		break;

		case "Tichingitu_10":
			dialog.text = StringFromKey("Tichingitu_25", pchar);
			link.l1 = StringFromKey("Tichingitu_26", pchar);
			link.l1.go = "Tichingitu_11";
		break;

		case "Tichingitu_11":
			dialog.text = StringFromKey("Tichingitu_27", pchar);
			link.l1 = StringFromKey("Tichingitu_28", pchar);
			link.l1.go = "Tichingitu_12";
		break;

		case "Tichingitu_12":
			dialog.text = StringFromKey("Tichingitu_29", pchar);
			link.l1 = StringFromKey("Tichingitu_30");
			link.l1.go = "Tichingitu_13";
			link.l2 = StringFromKey("Tichingitu_31");
			link.l2.go = "Tichingitu_exit";
		break;

		case "Tichingitu_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Tichingitu");
		break;

		case "Tichingitu_13":
			dialog.text = StringFromKey("Tichingitu_32", pchar);
			link.l1 = StringFromKey("Tichingitu_33");
			link.l1.go = "Tichingitu_hire";
		break;

		case "Tichingitu_hire":
			ChangeIndianRelation(3.0);
			NextDiag.CurrentNode = "Hired";
			DeleteAttribute(pchar, "questTemp.Tichingitu");

			// приведение в порядок
			LAi_SetImmortal(npchar, false);
			DeleteAttribute(npchar, "LifeDay");
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			npchar.CompanionDisable = true;
			npchar.location = "none";
			npchar.DontClearDead = true;
			npchar.SaveItemsForDead = true;

			// делаем мушкетёром
            MakeOffMush(npchar, "mushket_indian", 50, 50);

			// делаем офицером
			npchar.Payment = false; // признак офицера для бонусов от предметов; false без требования зарплаты
			npchar.AllowedPosts = "fighter";
			npchar.AllShip = "";    // не отображать количество свободных корабельных очков
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			LAi_SetOfficerType(npchar);
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			npchar.greeting = "GR_Tichingitu";

			DialogExit();
		break;

		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Hired":
			NextDiag.TempNode = "Hired";
			dialog.text = StringFromKey("Tichingitu_34", pchar.name);
			Link.l1 = StringFromKey("Tichingitu_35");
			Link.l1.go = "stay_follow";
			link.l2 = StringFromKey("Tichingitu_36");
			link.l2.go = "exit";
		break;

		case "stay_follow":
			dialog.Text = StringFromKey("Tichingitu_37");
			if (CheckAttribute(npchar, "IsMushketer"))
			{
				Link.l3 = StringFromKey("Tichingitu_38");
				Link.l3.go = "TargetDistance";
			}
			Link.l1 = StringFromKey("Tichingitu_39");
			Link.l1.go = "Boal_Stay";
			Link.l2 = StringFromKey("Tichingitu_40");
			Link.l2.go = "Boal_Follow";
			if (!CheckAttribute(npchar, "AboardRestriction"))
			{
				Link.l4 = StringFromKey("Tichingitu_41");
				Link.l4.go = "AboardRestriction";
			}
			else
			{
				Link.l4 = StringFromKey("Tichingitu_42");
				Link.l4.go = "AboardAllowed";
			}
		break;

		case "AboardRestriction":
			npchar.AboardRestriction = true;
			dialog.text = StringFromKey("Tichingitu_43");
			Link.l1 = StringFromKey("Tichingitu_44");
			Link.l1.go = "exit";
		break;

		case "AboardAllowed":
			DeleteAttribute(npchar, "AboardRestriction");
			dialog.text = StringFromKey("Tichingitu_45");
			Link.l1 = StringFromKey("Tichingitu_46");
			Link.l1.go = "exit";
		break;

		case "Boal_Stay":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerStay");
			dialog.Text = StringFromKey("Tichingitu_47");
			Link.l1 = StringFromKey("Tichingitu_48");
			Link.l1.go = "Exit";
			Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
		break;

		case "Boal_Follow":
			SetCharacterTask_FollowCharacter(Npchar, PChar);
			dialog.Text = StringFromKey("Tichingitu_49");
			Link.l1 = StringFromKey("Tichingitu_50");
			Link.l1.go = "Exit";
		break;

		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = StringFromKey("Tichingitu_51");
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;

		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = StringFromKey("Tichingitu_52");
				link.l1 = StringFromKey("Tichingitu_53");
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = StringFromKey("Tichingitu_54");
				link.l1 = StringFromKey("Tichingitu_55");
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = StringFromKey("Tichingitu_56");
				link.l1 = StringFromKey("Tichingitu_57");
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = StringFromKey("Tichingitu_58");
			link.l1 = StringFromKey("Tichingitu_59");
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

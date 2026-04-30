void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool ok;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\Ammo\" + NPChar.City + "_Ammo.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		//---------------- Комендант форта ------------------
		case "First time":
			if (idRand(npchar.id + "questPrisonGun", 2) == 0 && GetNpcQuestPastDayWOInit(npchar, "questPrisonGun") > 365 && !CheckAttribute(pchar, "questTemp.PrisonGun"))
			{
				dialog.text = StringFromKey("Common_Ammo_7", RandPhraseSimple(
							StringFromKey("Common_Ammo_3", RandPhraseSimple(
									StringFromKey("Common_Ammo_1"),
									StringFromKey("Common_Ammo_2"))),
							StringFromKey("Common_Ammo_6", RandPhraseSimple(
									StringFromKey("Common_Ammo_4"),
									StringFromKey("Common_Ammo_5")))));
				link.l1 = StringFromKey("Common_Ammo_8");
				link.l1.go = "GiveTaskGun";
				npchar.quest.PrisonGun = "Target";
				SaveCurrentNpcQuestDateParam(npchar, "questPrisonGun");
				break;
			}
			dialog.text = StringFromKey("Common_Ammo_11", RandPhraseSimple(
						StringFromKey("Common_Ammo_9"),
						StringFromKey("Common_Ammo_10")));
			link.l1 = StringFromKey("Common_Ammo_12", pchar);
			link.l1.go = "exit";
			link.l2 = StringFromKey("Common_Ammo_13");
			link.l2.go = "quests";
			if (CheckAttribute(pchar, "questTemp.PrisonGun") && pchar.questTemp.PrisonGun.Id == npchar.location)
			{
				link.l3 = StringFromKey("Common_Ammo_14");
				link.l3.go = "CheckGun";
			}
			NextDiag.TempNode = "First time";
		break;

		case "GiveTaskGun":
			dialog.Text = StringFromKey("Common_Ammo_18", LinkRandPhrase(
						StringFromKey("Common_Ammo_15"),
						StringFromKey("Common_Ammo_16"),
						StringFromKey("Common_Ammo_17")));
			Link.l1 = StringFromKey("Common_Ammo_19");
			Link.l1.go = "GiveTaskGun_1";
			pchar.questTemp.PrisonGun = true;
			SaveCurrentQuestDateParam("pchar.questTemp.PrisonGun");
		break;

		case "GiveTaskGun_1":
			GetGunType();
			//iGunPrice = sti(pchar.questTemp.PrisonGun.Price);
			//iGunQty = pchar.questTemp.PrisonGun.Qty;
			pchar.questTemp.PrisonGun.Sum = makeint(sti(pchar.questTemp.PrisonGun.Price) * sti(pchar.questTemp.PrisonGun.Qty));
			pchar.questTemp.PrisonGun.Luck = rand(4);
			pchar.questTemp.PrisonGun.Id = npchar.location;
			//sText = pchar.questTemp.PrisonGun.Text;
			dialog.Text = StringFromKey("Common_Ammo_20", GetAddress_Form(NPChar), pchar.questTemp.PrisonGun.Text, sti(pchar.questTemp.PrisonGun.Qty), FindMoneyString(sti(pchar.questTemp.PrisonGun.Sum)), FindMoneyString(sti(pchar.questTemp.PrisonGun.Price)));
			Link.l1 = StringFromKey("Common_Ammo_23", RandPhraseSimple(
						StringFromKey("Common_Ammo_21"),
						StringFromKey("Common_Ammo_22")));
			Link.l1.go = "exit_gun";
			Link.l2 = StringFromKey("Common_Ammo_26", RandPhraseSimple(
						StringFromKey("Common_Ammo_24"),
						StringFromKey("Common_Ammo_25")));
			Link.l2.go = "GiveTaskGun_2";
		break;

		case "exit_gun":
			dialog.Text = StringFromKey("Common_Ammo_27");
			Link.l1 = StringFromKey("Common_Ammo_28");
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;

		case "GiveTaskGun_2":
			dialog.Text = StringFromKey("Common_Ammo_29");
			Link.l1 = StringFromKey("Common_Ammo_30");
			Link.l1.go = "exit";
			ReOpenQuestHeader("PrisonGun");
			AddQuestRecord("PrisonGun", "1");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			AddQuestUserData("PrisonGun", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("PrisonGun", "sQty", makeint(pchar.questTemp.PrisonGun.Qty));
			AddQuestUserData("PrisonGun", "sSum", FindMoneyString(makeint(pchar.questTemp.PrisonGun.Sum)));
			AddQuestUserData("PrisonGun", "sText", pchar.questTemp.PrisonGun.Text);
			NextDiag.TempNode = "First time";
		break;

		case "CheckGun":
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") < 30)
			{
				dialog.Text = StringFromKey("Common_Ammo_31");
				Link.l1 = StringFromKey("Common_Ammo_32", pchar);
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				break;
			}
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") > 180)
			{
				dialog.Text = StringFromKey("Common_Ammo_33");
				Link.l1 = StringFromKey("Common_Ammo_34");
				Link.l1.go = "TakeGun_late";
				break;
			}
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = GetSquadronGoods(Pchar, iGunGoods) - sti(pchar.questTemp.PrisonGun.Qty);
			sTemp = sti(pchar.questTemp.PrisonGun.Qty);
			iTest = FindColony(NPChar.City); // город

			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			if (CheckShipMooredInColony(rColony))
			{
				dialog.Text = StringFromKey("Common_Ammo_35");
				if (amount < 0)
				{
					Link.l1 = StringFromKey("Common_Ammo_36", pchar);
					Link.l1.go = "exit";
				}
				else
				{
					Link.l1 = StringFromKey("Common_Ammo_37", pchar, sTemp);
					Link.l1.go = "TakeGun";
				}
			}
			else
			{
				dialog.text = StringFromKey("Common_Ammo_38");
				link.l1 = StringFromKey("Common_Ammo_39");
				link.l1.go = "exit";
			}
		break;

		case "TakeGun":
			if (pchar.questTemp.PrisonGun.Luck == 4)
			{
				dialog.Text = StringFromKey("Common_Ammo_42", RandPhraseSimple(
							StringFromKey("Common_Ammo_40"),
							StringFromKey("Common_Ammo_41")));
				Link.l1 = StringFromKey("Common_Ammo_43");
				Link.l1.go = "TakeGun_no";
			}
			else
			{
				dialog.Text = StringFromKey("Common_Ammo_46", RandPhraseSimple(
							StringFromKey("Common_Ammo_44"),
							StringFromKey("Common_Ammo_45")));
				Link.l1 = StringFromKey("Common_Ammo_47");
				Link.l1.go = "TakeGun_1";
			}
		break;

		case "TakeGun_no":
			dialog.Text = StringFromKey("Common_Ammo_48");
			Link.l1 = StringFromKey("Common_Ammo_49");
			Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "3");
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			SaveCurrentNpcQuestDateParam(npchar, "questPrisonGun");
			NextDiag.TempNode = "First time";
		break;

		case "TakeGun_late":
			dialog.Text = StringFromKey("Common_Ammo_50");
			Link.l1 = StringFromKey("Common_Ammo_51", pchar);
			Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "4");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			SaveCurrentNpcQuestDateParam(npchar, "questPrisonGun");
			NextDiag.TempNode = "First time";
		break;

		case "TakeGun_1":
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = sti(pchar.questTemp.PrisonGun.Qty);
			iTemp = makeint(sti(pchar.questTemp.PrisonGun.Sum)) / 12000;
			dialog.Text = StringFromKey("Common_Ammo_54", RandPhraseSimple(
						StringFromKey("Common_Ammo_52", GetTextChestsQuantity(iTemp)),
						StringFromKey("Common_Ammo_53", iTemp)));
			Link.l1 = StringFromKey("Common_Ammo_55");
			Link.l1.go = "TakeGun_2";
			AddItemLog(pchar, "chest", its(iTemp), StringFromKey("InfoMessages_134"), "Important_item");
			RemoveCharacterGoods(Pchar, iGunGoods, amount);
		break;

		case "TakeGun_2":
			dialog.Text = StringFromKey("Common_Ammo_56");
			Link.l1 = StringFromKey("Common_Ammo_57");
			Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "2");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			SaveCurrentNpcQuestDateParam(npchar, "questPrisonGun");
			NextDiag.TempNode = "First time";
		break;
	}
}

void GetGunType()
{
	int iGunType;
	if (makeint(pchar.rank) < 5)
	{
		iGunType = rand(1);
	}    //24
	if (makeint(pchar.rank) >= 6 && makeint(pchar.rank) < 13)
	{
		iGunType = rand(3);
	} //24&&32
	if (makeint(pchar.rank) >= 13 && makeint(pchar.rank) < 20)
	{
		iGunType = rand(2) + 2;
	} //32&&42
	if (makeint(pchar.rank) >= 20)
	{
		iGunType = 4;
	} //42

	switch (iGunType)
	{
		case 0:
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_24;
			pchar.questTemp.PrisonGun.Price = 900 + GetCharacterSPECIALSimple(PChar, SPECIAL_C) * GetSummonSkillFromName(pchar, SKILL_COMMERCE) / 100 * 175;
			pchar.questTemp.PrisonGun.Qty = sti(makeint(pchar.rank) * 5 + 30 + rand(sti(pchar.rank)));
			pchar.questTemp.PrisonGun.Text = StringFromKey("Common_Ammo_58");
		break;
		case 1:
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_24;
			pchar.questTemp.PrisonGun.Price = 1100 + GetCharacterSPECIALSimple(PChar, SPECIAL_C) * GetSummonSkillFromName(pchar, SKILL_COMMERCE) / 100 * 225;
			pchar.questTemp.PrisonGun.Qty = sti(makeint(pchar.rank) * 5 + 20 + rand(sti(pchar.rank)));
			pchar.questTemp.PrisonGun.Text = StringFromKey("Common_Ammo_59");
		break;
		case 2:
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_32;
			pchar.questTemp.PrisonGun.Price = 1300 + GetCharacterSPECIALSimple(PChar, SPECIAL_C) * GetSummonSkillFromName(pchar, SKILL_COMMERCE) / 100 * 275;
			pchar.questTemp.PrisonGun.Qty = sti(makeint(pchar.rank) * 4 + 10 + rand(sti(pchar.rank)));
			pchar.questTemp.PrisonGun.Text = StringFromKey("Common_Ammo_60");
		break;
		case 3:
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_32;
			pchar.questTemp.PrisonGun.Price = 1500 + GetCharacterSPECIALSimple(PChar, SPECIAL_C) * GetSummonSkillFromName(pchar, SKILL_COMMERCE) / 100 * 325;
			pchar.questTemp.PrisonGun.Qty = sti(makeint(pchar.rank) * 4 + 10 + rand(sti(pchar.rank)));
			pchar.questTemp.PrisonGun.Text = StringFromKey("Common_Ammo_61");
		break;
		case 4:
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_42;
			pchar.questTemp.PrisonGun.Price = 2100 + GetCharacterSPECIALSimple(PChar, SPECIAL_C) * GetSummonSkillFromName(pchar, SKILL_COMMERCE) / 100 * 425;
			pchar.questTemp.PrisonGun.Qty = sti(makeint(pchar.rank) * 3 + 20 + rand(sti(pchar.rank)));
			pchar.questTemp.PrisonGun.Text = StringFromKey("Common_Ammo_62");
		break;
	}
}

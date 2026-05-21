void ProcessDialogEvent()
{
	ref NPChar, chr, rShip;
	aref Link, NextDiag;
	int i, iBonus, iGems, iItems, iGoods, iMoney, iCannons, iTemp;
	string sAttr, sBonus, sTemp, sTemp2, sTemp3, sItems;

	aref itms, itm;
	int n;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	sAttr = Dialog.CurrentNode;
	if (HasSubStr(sAttr, "Atlaua_ChooseShip-"))
	{
		npchar.shipidx = strright(sAttr, 1);
		Dialog.CurrentNode = "Atlaua_ChooseBonus";
	}
	if (HasSubStr(sAttr, "Atlaua_ChooseBonus-"))
	{
		i = findsubstr(sAttr, "-", 0);
		npchar.curbonus = strcut(sAttr, i + 1, strlen(sAttr) - 1);
		Dialog.CurrentNode = "Atlaua_Price";
	}
	if (HasSubStr(sAttr, "Huitzilopochtli_ChooseChr-"))
	{
		i = findsubstr(sAttr, "-", 0);
		npchar.damage.chridx = strcut(sAttr, i + 1, strlen(sAttr) - 1);
		Dialog.CurrentNode = "Huitzilopochtli_CheckChr";
	}

	switch (Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = StringFromKey("Easter_1");
			link.l1 = StringFromKey("Easter_2");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_dissapear":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;

		case "Huahuantli_1":
			dialog.text = StringFromKey("Easter_3");
			link.l1 = StringFromKey("Easter_4");
			link.l1.go = "Huahuantli_2";
		break;

		case "Huahuantli_2":
			dialog.text = StringFromKey("Easter_5", pchar);
			link.l1 = StringFromKey("Easter_6", pchar);
			link.l1.go = "Huahuantli_3";
		break;

		case "Huahuantli_3":
			dialog.text = StringFromKey("Easter_7", pchar);
			link.l1 = StringFromKey("Easter_8");
			link.l1.go = "Huahuantli_4";
		break;

		case "Huahuantli_4":
			dialog.text = StringFromKey("Easter_9", pchar);
			link.l1 = StringFromKey("Easter_10");
			link.l1.go = "Huahuantli_5";
		break;

		case "Huahuantli_5":
			AddQuestRecord("EasterGods", "CaveInfo");
			AddQuestUserData("EasterGods", "sSex", GetSexPhrase("", "а"));
			dialog.text = StringFromKey("Easter_11");
			link.l1 = StringFromKey("Easter_12");
			link.l1.go = "Huahuantli_6";
		break;

		case "Huahuantli_6":
			AddQuestRecord("EasterGods", "CaveWords");
			dialog.text = StringFromKey("Easter_13", pchar);
			link.l1 = StringFromKey("Easter_14");
			link.l1.go = "Huahuantli_7";
			link.l2 = StringFromKey("Easter_15", pchar);
			link.l2.go = "Huahuantli_later";
		break;

		case "Huahuantli_7":
			dialog.text = StringFromKey("Easter_16");
			link.l1 = "";
			Link.l1.edit = 3; // TODO ВВОД ТЕКСТА CN - Пасхалка отключена, но проблема ввода никуда не делась
			link.l1.go = "Huahuantli_8";
		break;

		case "Huahuantli_later":
			dialog.text = StringFromKey("Easter_17");
			link.l1 = StringFromKey("Easter_18");
			link.l1.go = "exit";
			LAi_SetStayType(npchar);
			NextDiag.TempNode = "Huahuantli_return";
		break;

		case "Huahuantli_return":
			dialog.text = StringFromKey("Easter_19", pchar);
			link.l1 = StringFromKey("Easter_20");
			link.l1.go = "Huahuantli_7";
			link.l2 = StringFromKey("Easter_21");
			link.l2.go = "Huahuantli_later";
		break;

		case "Huahuantli_8":
			if (GetStrSmallRegister(dialogEditStrings[3]) == GetStrSmallRegister(GetConvertStr("EasterText", "ReactionsTexts.txt")))
			{
				DialogExit();
				EasterOpenPassage();
				EasterReload();
				EasterGenerateGods();
			}
			else
			{
				dialog.text = StringFromKey("Easter_22");
				link.l1 = StringFromKey("Easter_23");
				link.l1.go = "exit";
				LAi_SetStayType(npchar);
				NextDiag.TempNode = "Huahuantli_return";
			}
		break;

		case "Huahuantli_final":
			AddQuestRecord("EasterGods", "CaveEnter");
			AddQuestUserData("EasterGods", "sSex", GetSexPhrase("ся", "ась"));
			dialog.text = StringFromKey("Easter_24", pchar);
			link.l1 = StringFromKey("Easter_25");
			link.l1.go = "exit_dissapear";
		break;

		case "Atlaua_1":
			dialog.text = StringFromKey("Easter_26", pchar);
			link.l1 = StringFromKey("Easter_27");
			link.l1.go = "Atlaua_2";
		break;

		case "Atlaua_2":
			dialog.text = StringFromKey("Easter_28");
			link.l1 = StringFromKey("Easter_29");
			link.l1.go = "Atlaua_3";
		break;

		case "Atlaua_3":
			dialog.text = StringFromKey("Easter_30");
			link.l1 = StringFromKey("Easter_31", pchar);
			link.l1.go = "Atlaua_4";
		break;

		case "Atlaua_4":
			dialog.text = StringFromKey("Easter_32");
			link.l1 = StringFromKey("Easter_33");
			link.l1.go = "Atlaua_5";
		break;

		case "Atlaua_5":
			AddQuestRecord("EasterGods", "AtlauaInfo");
			AddQuestUserData("EasterGods", "sSex", GetSexPhrase("", "а"));
			dialog.text = StringFromKey("Easter_34");
			for (i = 0; i < GetCompanionQuantity(PChar); i++)
			{
				chr = GetCharacter(GetCompanionIndex(PChar, i));
				sAttr = "l" + i;
				rShip = GetRealShip(sti(chr.Ship.Type));
				link.(sAttr) = xiStr(rShip.BaseName) + " '" + chr.Ship.Name + "'.";
				link.(sAttr).go = "Atlaua_ChooseShip-" + i;
			}
			link.l6 = StringFromKey("Easter_35", pchar);
			link.l6.go = "Atlaua_refusal";
		break;

		case "Atlaua_ChooseShip":
			dialog.text = StringFromKey("Easter_36", pchar);
			for (i = 0; i < GetCompanionQuantity(PChar); i++)
			{
				chr = GetCharacter(GetCompanionIndex(PChar, i));
				sAttr = "l" + i;
				rShip = GetRealShip(sti(chr.Ship.Type));
				link.(sAttr) = xiStr(rShip.BaseName) + " '" + chr.Ship.Name + "'.";
				link.(sAttr).go = "Atlaua_ChooseShip-" + i;
			}
			link.l6 = StringFromKey("Easter_37", pchar);
			link.l6.go = "Atlaua_refusal";
		break;

		case "Atlaua_refusal":
			dialog.text = StringFromKey("Easter_38", pchar);
			if (!CheckAttribute(pchar, "questTemp.easter.atlaua_date"))
			{
				AddQuestRecord("EasterGods", "AtlauaDate");
				pchar.questTemp.easter.atlaua_date = 1;
			}
			link.l1 = StringFromKey("Easter_39");
			link.l1.go = "exit";
			NextDiag.TempNode = "Atlaua_return";
		break;

		case "Atlaua_ChooseBonus":
			chr = GetCharacter(GetCompanionIndex(PChar, sti(npchar.shipidx)));
			rShip = GetRealShip(sti(chr.Ship.Type));
			if (CheckAttribute(rShip, "atlaua_bonus") && rShip.atlaua_bonus == "full")
			{
				dialog.text = StringFromKey("Easter_40");
				link.l1 = StringFromKey("Easter_41");
				link.l1.go = "Atlaua_ChooseShip";
				link.l2 = StringFromKey("Easter_42");
				link.l2.go = "Atlaua_refusal";
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.easter.atlaua_bonuslist"))
			{
				AddQuestRecord("EasterGods", "AtlauaBonusList");
				pchar.questTemp.easter.atlaua_bonuslist = 1;
			}
			dialog.text = StringFromKey("Easter_43");
			if (!CheckAttribute(rShip, "atlaua_bonus.HP") || rShip.atlaua_bonus.HP != "full")
			{
				link.l1 = StringFromKey("Easter_44");
				link.l1.go = "Atlaua_ChooseBonus-HP";
			}
			if (!CheckAttribute(rShip, "atlaua_bonus.MaxCrew") || rShip.atlaua_bonus.MaxCrew != "full")
			{
				link.l2 = StringFromKey("Easter_45");
				link.l2.go = "Atlaua_ChooseBonus-MaxCrew";
			}
			if (!CheckAttribute(rShip, "atlaua_bonus.Capacity") || rShip.atlaua_bonus.Capacity != "full")
			{
				link.l3 = StringFromKey("Easter_46");
				link.l3.go = "Atlaua_ChooseBonus-Capacity";
			}
			if (!CheckAttribute(rShip, "atlaua_bonus.SpeedRate") || rShip.atlaua_bonus.SpeedRate != "full")
			{
				link.l4 = StringFromKey("Easter_47");
				link.l4.go = "Atlaua_ChooseBonus-SpeedRate";
			}
			if (!CheckAttribute(rShip, "atlaua_bonus.TurnRate") || rShip.atlaua_bonus.TurnRate != "full")
			{
				link.l5 = StringFromKey("Easter_48");
				link.l5.go = "Atlaua_ChooseBonus-TurnRate";
			}
			link.l6 = StringFromKey("Easter_49", pchar);
			link.l6.go = "Atlaua_refusal";
		break;

		case "Atlaua_Price":
			chr = GetCharacter(GetCompanionIndex(PChar, sti(npchar.shipidx)));
			rShip = GetRealShip(sti(chr.Ship.Type));
			sAttr = npchar.curbonus;
			if (!CheckAttribute(rShip, "atlaua_bonus." + sAttr))
				rShip.atlaua_bonus.(sAttr) = 0;
			switch (sAttr)
			{
				case "HP":            sBonus = StringFromKey("Easter_50");            sItems = StringFromKey("Easter_51");            npchar.curitemstype = "mineral6";    break;
				case "MaxCrew":        sBonus = StringFromKey("Easter_52");        sItems = StringFromKey("Easter_53");        npchar.curitemstype = "mineral10";    break;
				case "Capacity":    sBonus = StringFromKey("Easter_54");            sItems = StringFromKey("Easter_55");    npchar.curitemstype = "indian4";    break;
				case "SpeedRate":    sBonus = StringFromKey("Easter_56");            sItems = StringFromKey("Easter_57");    npchar.curitemstype = "indian8";    break;
				case "TurnRate":    sBonus = StringFromKey("Easter_58");    sItems = StringFromKey("Easter_59");            npchar.curitemstype = "indian13";    break;
			}
			if (!CheckAttribute(pchar, "questTemp.easter.atlaua_Priceinfo." + sAttr))
			{
				AddQuestRecord("EasterGods", "AtlauaPriceInfo" + sAttr);
				pchar.questTemp.easter.atlaua_priceinfo.(sAttr) = 1;
			}
			iGems = 10 + sti(rShip.atlaua_bonus.(sAttr)) * 10;
			iItems = 5 + sti(rShip.atlaua_bonus.(sAttr)) * 5;
			iMoney = 50000 + sti(rShip.atlaua_bonus.(sAttr)) * 25000;
			npchar.curgems = iGems;
			npchar.curitems = iItems;
			npchar.curmoney = iMoney;
			dialog.text = StringFromKey("Easter_60", sBonus, iGems, iItems, sItems, FindMoneyString(iMoney));
			if (GetCharacterItem(pchar, "jewelry1") >= iGems && GetCharacterItem(pchar, npchar.curitemstype) >= iItems && sti(pchar.money) >= iMoney)
			{
				link.l1 = StringFromKey("Easter_61");
				link.l1.go = "Atlaua_GetBonus";
			}
			link.l2 = StringFromKey("Easter_62");
			link.l2.go = "Atlaua_refusal";
		break;

		case "Atlaua_GetBonus":
			sAttr = npchar.curbonus;
			chr = GetCharacter(GetCompanionIndex(PChar, sti(npchar.shipidx)));
			rShip = GetRealShip(sti(chr.Ship.Type));
			rShip.atlaua_bonus.(sAttr) = sti(rShip.atlaua_bonus.(sAttr)) + 1;
			TakeNItems(pchar, "jewelry1", -sti(npchar.curgems));
			TakeNItems(pchar, npchar.curitemstype, -sti(npchar.curitems));
			AddMoneyToCharacter(pchar, -makeint(sti(npchar.curmoney)));
			switch (sAttr)
			{
				case "HP":            rShip.HP = makeint(sti(rShip.HP) * 1.15);                        break;
				// по 15%
				case "MaxCrew":        rShip.OptCrew = makeint(sti(rShip.OptCrew) * 1.15);
					rShip.MaxCrew = makeint(sti(rShip.OptCrew) * 1.25 + 0.5);    break;
				// по 15%
				case "Capacity":    rShip.Capacity = makeint(sti(rShip.Capacity) * 1.2);            break;
				// по 20%
				case "SpeedRate":    rShip.SpeedRate = stf(rShip.SpeedRate) * 1.1;                    break;
				// по 10%
				case "TurnRate":    rShip.TurnRate = stf(rShip.TurnRate) * 1.1;                    break;
				// по 10%
			}
			sTemp = StringFromKey("Easter_63");
			if (!CheckAttribute(pchar, "questTemp.easter.atlaua_priceinfo"))
			{
				AddQuestRecord("EasterGods", "AtlauaPriceInfo");
				pchar.questTemp.easter.atlaua_priceinfo = 1;
			}
			if (!CheckAttribute(rShip, "atlaua_bonus"))
				rShip.atlaua_bonus = 0;
			if (sti(rShip.atlaua_bonus.(sAttr)) >= 3)
			{
				rShip.atlaua_bonus.(sAttr) = "full";
				sTemp = StringFromKey("Easter_64");
				rShip.atlaua_bonus = sti(rShip.atlaua_bonus) + 1;
				if (sti(rShip.atlaua_bonus) >= 5)
				{
					rShip.atlaua_bonus = "full";
					sTemp = StringFromKey("Easter_65");
				}
			}

			dialog.text = StringFromKey("Easter_66", pchar, sTemp);
			link.l1 = StringFromKey("Easter_67");
			link.l1.go = "exit";
			NextDiag.TempNode = "Atlaua_return";
		break;

		case "Atlaua_return":
			dialog.text = StringFromKey("Easter_68", pchar);
			link.l1 = StringFromKey("Easter_69");
			link.l1.go = "Atlaua_ChooseShip";
		break;

		case "Xiuhtecuhtli_1":
			dialog.text = StringFromKey("Easter_70");
			link.l1 = StringFromKey("Easter_71");
			link.l1.go = "Xiuhtecuhtli_2";
		break;

		case "Xiuhtecuhtli_2":
			dialog.text = StringFromKey("Easter_72", pchar);
			link.l1 = StringFromKey("Easter_73", pchar);
			link.l1.go = "Xiuhtecuhtli_melee";
			link.l2 = StringFromKey("Easter_74");
			link.l2.go = "Xiuhtecuhtli_3";
			link.l3 = StringFromKey("Easter_75");
			link.l3.go = "Xiuhtecuhtli_glory";
		break;

		case "Xiuhtecuhtli_melee":
			npchar.melee = 1;
			dialog.text = StringFromKey("Easter_76");
			link.l1 = StringFromKey("Easter_77");
			link.l1.go = "Xiuhtecuhtli_3";
			if (!CheckAttribute(npchar, "glory"))
			{
				link.l2 = StringFromKey("Easter_78");
				link.l2.go = "Xiuhtecuhtli_glory";
			}
		break;

		case "Xiuhtecuhtli_glory":
			npchar.glory = 1;
			dialog.text = StringFromKey("Easter_79");
			if (!CheckAttribute(npchar, "melee"))
			{
				link.l1 = StringFromKey("Easter_80", pchar);
				link.l1.go = "Xiuhtecuhtli_melee";
			}
			link.l2 = StringFromKey("Easter_81");
			link.l2.go = "Xiuhtecuhtli_3";
		break;

		case "Xiuhtecuhtli_3":
			dialog.text = StringFromKey("Easter_82");
			if (CheckCharacterItem(pchar, "GunPowder"))
			{
				link.l1 = StringFromKey("Easter_83");
				link.l1.go = "Xiuhtecuhtli_4";
				AddQuestRecord("EasterGods", "XiuhtecuhtliPowder");
				AddQuestUserData("EasterGods", "sSex", GetSexPhrase("", "а"));
			}
			else
			{
				link.l1 = StringFromKey("Easter_84");
				link.l1.go = "Xiuhtecuhtli_refusal_powder";
			}
		break;

		case "Xiuhtecuhtli_powder":
			dialog.text = StringFromKey("Easter_85", pchar);
			if (CheckCharacterItem(pchar, "GunPowder"))
			{
				link.l1 = StringFromKey("Easter_86");
				link.l1.go = "Xiuhtecuhtli_4";
			}
			else
			{
				link.l1 = StringFromKey("Easter_87", pchar);
				link.l1.go = "Xiuhtecuhtli_refusal_powder";
			}
		break;

		case "Xiuhtecuhtli_refusal_powder":
			dialog.text = StringFromKey("Easter_88", pchar);
			if (!CheckAttribute(pchar, "questTemp.easter.xiuhtecuhtli_date"))
			{
				AddQuestRecord("EasterGods", "XiuhtecuhtliPowderDate");
				AddQuestUserData("EasterGods", "sSex", GetSexPhrase("", "а"));
				pchar.questTemp.easter.xiuhtecuhtli_date = 1;
			}
			link.l1 = StringFromKey("Easter_89");
			link.l1.go = "exit";
			NextDiag.TempNode = "Xiuhtecuhtli_powder";
		break;

		case "Xiuhtecuhtli_refusal":
			dialog.text = StringFromKey("Easter_90", pchar);
			if (!CheckAttribute(pchar, "questTemp.easter.xiuhtecuhtli_date"))
			{
				AddQuestRecord("EasterGods", "XiuhtecuhtliDate");
				pchar.questTemp.easter.xiuhtecuhtli_date = 1;
			}
			link.l1 = StringFromKey("Easter_91");
			link.l1.go = "exit";
			NextDiag.TempNode = "Xiuhtecuhtli_return";
		break;

		case "Xiuhtecuhtli_4":
			TakeNItems(pchar, "GunPowder", -1);
			dialog.text = StringFromKey("Easter_92", pchar);
			link.l1 = StringFromKey("Easter_93");
			link.l1.go = "Xiuhtecuhtli_5";
		break;

		case "Xiuhtecuhtli_5":
			dialog.text = StringFromKey("Easter_94", pchar);
			link.l1 = StringFromKey("Easter_95");
			link.l1.go = "Xiuhtecuhtli_6";
		break;

		case "Xiuhtecuhtli_6":
			sTemp = "";
			npchar.shipfire = 0;
			npchar.powder_remain.goods = 50000;
			npchar.powder_remain.items = 500;
			if (GetCharacterShipClass(pchar) > 2)
			{
				sTemp = " " + StringFromKey("Easter_96");
				AddQuestRecord("EasterGods", "XiuhtecuhtliBargainShip");
				AddQuestUserData("EasterGods", "sSex", GetSexPhrase("ен", "на"));
			}
			else
			{
				AddQuestRecord("EasterGods", "XiuhtecuhtliBargain");
				AddQuestUserData("EasterGods", "sSex", GetSexPhrase("ен", "на"));
			}
			dialog.text = StringFromKey("Easter_97", sTemp);

			if (GetCharacterItem(pchar, "GunPowder") >= 500 && GetSquadronGoods(pchar, GOOD_POWDER) >= 50000)
			{
				link.l1 = StringFromKey("Easter_98");
				link.l1.go = "Xiuhtecuhtli_getallpowder";
			}
			if (GetCharacterItem(pchar, "GunPowder") > 0)
			{
				link.l2 = StringFromKey("Easter_99", pchar);
				link.l2.go = "Xiuhtecuhtli_getpowder_items";
			}
			if (GetSquadronGoods(pchar, GOOD_POWDER) > 0)
			{
				link.l3 = StringFromKey("Easter_100", pchar);
				link.l3.go = "Xiuhtecuhtli_getpowder_goods";
			}
			link.l4 = StringFromKey("Easter_101", pchar);
			link.l4.go = "Xiuhtecuhtli_refusal";
		break;

		case "Xiuhtecuhtli_getallpowder":
			TakeNItems(pchar, "GunPowder", -sti(npchar.powder_remain.items));
			RemoveCharacterGoods(pchar, GOOD_POWDER, sti(npchar.powder_remain.goods));
			npchar.powder_remain.items = 0;
			npchar.powder_remain.goods = 0;
			dialog.text = StringFromKey("Easter_102");
			if (GetCharacterItem(pchar, "jewelry3") >= 30 && sti(pchar.money) >= 100000)
			{
				link.l1 = StringFromKey("Easter_103");
				link.l1.go = "Xiuhtecuhtli_GetBonus";
			}
			link.l2 = StringFromKey("Easter_104");
			link.l2.go = "Xiuhtecuhtli_refusal";
		break;

		case "Xiuhtecuhtli_getpowder_items":
			dialog.text = StringFromKey("Easter_105", pchar);
			link.l1 = "";
			Link.l1.edit = 3; // TODO ВВОД ТЕКСТА CN - Пасхалка отключена, но проблема ввода никуда не делась
			link.l1.go = "Xiuhtecuhtli_checkpowder_items";
		break;

		case "Xiuhtecuhtli_getpowder_goods":
			dialog.text = StringFromKey("Easter_106", pchar);
			link.l1 = "";
			Link.l1.edit = 3; // TODO ВВОД ТЕКСТА CN - Пасхалка отключена, но проблема ввода никуда не делась
			link.l1.go = "Xiuhtecuhtli_checkpowder_goods";
		break;

		case "Xiuhtecuhtli_checkpowder_items":
			sTemp = "";
			iItems = sti(dialogEditStrings[3]);
			if (GetCharacterItem(pchar, "GunPowder") < iItems)
			{
				sTemp = StringFromKey("Easter_107");
				iItems = GetCharacterItem(pchar, "GunPowder");
			}
			if (iItems > sti(npchar.powder_remain.items))
			{
				sTemp += StringFromKey("Easter_108");
				iItems = sti(npchar.powder_remain.items);
			}
			if (sti(dialogEditStrings[3]) <= 0)
			{
				sTemp = StringFromKey("Easter_109");
				iItems = 0;
			}
			npchar.powder_remain.items = sti(npchar.powder_remain.items) - iItems;
			TakeNItems(pchar, "GunPowder", -iItems);
			if (sti(npchar.powder_remain.items) > 0)
			{
				dialog.text = StringFromKey("Easter_110", sTemp, npchar.powder_remain.items);
				link.l1 = StringFromKey("Easter_111");
				link.l1.go = "Xiuhtecuhtli_refusal";
			}
			else
			{
				dialog.text = StringFromKey("Easter_112", sTemp);
				if (sti(npchar.powder_remain.goods) > 0)
				{
					if (GetSquadronGoods(pchar, GOOD_POWDER) > 0)
					{
						link.l1 = StringFromKey("Easter_113", pchar);
						link.l1.go = "Xiuhtecuhtli_getpowder_goods";
					}
				}
				else
				{
					if (GetCharacterItem(pchar, "jewelry3") >= 30 && sti(pchar.money) >= 100000)
					{
						link.l1 = StringFromKey("Easter_114", pchar);
						link.l1.go = "Xiuhtecuhtli_GetBonus";
					}
				}
				link.l2 = StringFromKey("Easter_115");
				link.l2.go = "Xiuhtecuhtli_refusal";
			}
		break;

		case "Xiuhtecuhtli_checkpowder_goods":
			sTemp = "";
			iGoods = sti(dialogEditStrings[3]);
			if (GetSquadronGoods(pchar, GOOD_POWDER) < iGoods)
			{
				sTemp = StringFromKey("Easter_116");
				iGoods = GetSquadronGoods(pchar, GOOD_POWDER);
			}
			if (iGoods > sti(npchar.powder_remain.goods))
			{
				sTemp += StringFromKey("Easter_117");
				iGoods = sti(npchar.powder_remain.goods);
			}
			if (sti(dialogEditStrings[3]) <= 0)
			{
				sTemp = StringFromKey("Easter_118");
				iGoods = 0;
			}
			npchar.powder_remain.goods = sti(npchar.powder_remain.goods) - iGoods;
			RemoveCharacterGoods(pchar, GOOD_POWDER, iGoods);
			if (sti(npchar.powder_remain.goods) > 0)
			{
				dialog.text = StringFromKey("Easter_119", sTemp, npchar.powder_remain.goods);
				link.l1 = StringFromKey("Easter_120");
				link.l1.go = "Xiuhtecuhtli_refusal";
			}
			else
			{
				dialog.text = StringFromKey("Easter_121", sTemp);
				if (sti(npchar.powder_remain.items) > 0)
				{
					if (GetCharacterItem(pchar, "GunPowder") > 0)
					{
						link.l1 = StringFromKey("Easter_122", pchar);
						link.l1.go = "Xiuhtecuhtli_getpowder_items";
					}
				}
				else
				{
					if (GetCharacterItem(pchar, "jewelry3") >= 30 && sti(pchar.money) >= 100000)
					{
						link.l1 = StringFromKey("Easter_123", pchar);
						link.l1.go = "Xiuhtecuhtli_GetBonus";
					}
				}
				link.l2 = StringFromKey("Easter_124");
				link.l2.go = "Xiuhtecuhtli_refusal";
			}
		break;

		case "Xiuhtecuhtli_return":
			if (!CheckAttribute(npchar, "shipfire"))
			{
				dialog.text = StringFromKey("Easter_125", pchar);

			}
			if (!CheckAttribute(npchar, "powder_remain"))
			{
				dialog.text = StringFromKey("Easter_126");
				link.l1 = StringFromKey("Easter_127", pchar);
				link.l1.go = "Xiuhtecuhtli_deal";
			}
			else
			{
				dialog.text = StringFromKey("Easter_128", pchar);
				if (sti(npchar.powder_remain.items) <= 0 && sti(npchar.powder_remain.goods) <= 0)
				{
					if (GetCharacterItem(pchar, "jewelry3") >= 30 && sti(pchar.money) >= 100000)
					{
						link.l1 = StringFromKey("Easter_129", pchar);
						link.l1.go = "Xiuhtecuhtli_GetBonus";
					}
				}
				else
				{
					if (GetCharacterItem(pchar, "GunPowder") >= sti(npchar.powder_remain.items) && GetSquadronGoods(pchar, GOOD_POWDER) >= sti(npchar.powder_remain.goods))
					{
						link.l1 = StringFromKey("Easter_130");
						link.l1.go = "Xiuhtecuhtli_getallpowder";
					}
					if (sti(npchar.powder_remain.items) > 0 && GetCharacterItem(pchar, "GunPowder") > 0)
					{
						link.l2 = StringFromKey("Easter_131", pchar);
						link.l2.go = "Xiuhtecuhtli_getpowder_items";
					}
					if (sti(npchar.powder_remain.goods) > 0 && GetSquadronGoods(pchar, GOOD_POWDER) > 0)
					{
						link.l3 = StringFromKey("Easter_132", pchar);
						link.l3.go = "Xiuhtecuhtli_getpowder_goods";
					}
				}
			}
			link.l4 = StringFromKey("Easter_133", pchar);
			link.l4.go = "exit";
		break;

		case "Xiuhtecuhtli_deal":
			sTemp = "";
			npchar.powder_remain.goods = 50000 + sti(npchar.shipfire) * 25000;
			npchar.powder_remain.items = 500 + sti(npchar.shipfire) * 250;
			if (GetCharacterShipClass(pchar) > 2)
				sTemp = " " + StringFromKey("Easter_134");
			dialog.text = StringFromKey("Easter_135", pchar, npchar.powder_remain.goods, npchar.powder_remain.items, sTemp);
			if (!CheckAttribute(pchar, "questTemp.easter.xiuhtecuhtli_deal"))
			{
				AddQuestRecord("EasterGods", "XiuhtecuhtliDeal");
				pchar.questTemp.easter.xiuhtecuhtli_deal = 1;
			}
			if (GetCharacterItem(pchar, "GunPowder") >= sti(npchar.powder_remain.items) && GetSquadronGoods(pchar, GOOD_POWDER) >= sti(npchar.powder_remain.goods))
			{
				link.l1 = StringFromKey("Easter_136");
				link.l1.go = "Xiuhtecuhtli_getallpowder";
			}
			if (GetCharacterItem(pchar, "GunPowder") > 0)
			{
				link.l2 = StringFromKey("Easter_137", pchar);
				link.l2.go = "Xiuhtecuhtli_getpowder_items";
			}
			if (GetSquadronGoods(pchar, GOOD_POWDER) > 0)
			{
				link.l3 = StringFromKey("Easter_138", pchar);
				link.l3.go = "Xiuhtecuhtli_getpowder_goods";
			}
			link.l4 = StringFromKey("Easter_139", pchar);
			link.l4.go = "Xiuhtecuhtli_refusal";
		break;

		case "Xiuhtecuhtli_GetBonus":
			if (GetCharacterShipClass(pchar) > 2)
			{
				dialog.text = StringFromKey("Easter_140");
				link.l1 = StringFromKey("Easter_141", pchar);
				link.l1.go = "Xiuhtecuhtli_refusal";
			}
			else
			{
				rShip = GetRealShip(sti(pchar.Ship.Type));
				if (rShip.MaxCaliber == 48)
				{
					dialog.text = StringFromKey("Easter_142");
					link.l1 = StringFromKey("Easter_143", pchar);
					link.l1.go = "Xiuhtecuhtli_refusal";
				}
				else
				{
					npchar.shipfire = sti(npchar.shipfire) + 1;
					DeleteAttribute(npchar, "powder_remain");
					TakeNItems(pchar, "jewelry3", -30);
					AddMoneyToCharacter(pchar, -100000);
					rShip.MaxCaliber = 48;
					if (sti(npchar.shipfire) == 1)
					{
						dialog.text = StringFromKey("Easter_144");
						link.l1 = StringFromKey("Easter_145", pchar);
						link.l1.go = "Xiuhtecuhtli_Xolotl_1";
					}
					else
					{
						dialog.text = StringFromKey("Easter_146");
						link.l1 = StringFromKey("Easter_147");
						link.l1.go = "exit";
						NextDiag.TempNode = "Xiuhtecuhtli_return";
					}
				}
			}
		break;

		case "Xiuhtecuhtli_Xolotl_1":
			EasterGenerateXolotl();
			dialog.text = StringFromKey("Easter_148", pchar);
			link.l1 = StringFromKey("Easter_149");
			link.l1.go = "Xiuhtecuhtli_Xolotl_2";
		break;

		case "Xiuhtecuhtli_Xolotl_2":
			dialog.text = StringFromKey("Easter_150");
			link.l1 = StringFromKey("Easter_151", pchar);
			link.l1.go = "Xiuhtecuhtli_Xolotl_3";
		break;

		case "Xiuhtecuhtli_Xolotl_3":
			dialog.text = StringFromKey("Easter_152");
			AddQuestRecord("EasterGods", "XiuhtecuhtliXolotl");
			AddQuestUserData("EasterGods", "sSex", GetSexPhrase("", "а"));
			link.l1 = StringFromKey("Easter_153", pchar);
			link.l1.go = "Xiuhtecuhtli_refusal";
		break;

		case "Xolotl_1":
			dialog.text = StringFromKey("Easter_154", pchar);
			link.l1 = StringFromKey("Easter_155");
			link.l1.go = "Xolotl_2";
		break;

		case "Xolotl_2":
			dialog.text = StringFromKey("Easter_156", pchar);
			link.l1 = StringFromKey("Easter_157", pchar);
			link.l1.go = "Xolotl_noslaves";
			link.l2 = StringFromKey("Easter_158");
			link.l2.go = "Xolotl_3";
		break;

		case "Xolotl_noslaves":
			dialog.text = StringFromKey("Easter_159");
			link.l1 = StringFromKey("Easter_160", pchar);
			link.l1.go = "Xolotl_noslaves_yes";
			link.l2 = StringFromKey("Easter_161");
			link.l2.go = "Xolotl_noslaves_no";
		break;

		case "Xolotl_noslaves_yes":
			pchar.questTemp.easter.xolotl_noslaves = 1;
			dialog.text = StringFromKey("Easter_162", pchar);
			link.l1 = StringFromKey("Easter_163");
			link.l1.go = "Xolotl_3";
		break;

		case "Xolotl_noslaves_no":
			dialog.text = StringFromKey("Easter_164");
			link.l1 = StringFromKey("Easter_165");
			link.l1.go = "Xolotl_3";
		break;

		case "Xolotl_3":
			dialog.text = StringFromKey("Easter_166");
			link.l1 = StringFromKey("Easter_167");
			link.l1.go = "Xolotl_4";
		break;

		case "Xolotl_4":
			dialog.text = StringFromKey("Easter_168");
			link.l1 = StringFromKey("Easter_169");
			link.l1.go = "Xolotl_5";
		break;

		case "Xolotl_5":
			if (CheckAttribute(pchar, "questTemp.easter.xolotl_noslaves"))
			{
				AddQuestRecord("EasterGods", "XolotlInfoNoSlaves");
				AddQuestUserData("EasterGods", "sSex", GetSexPhrase("ся", "ась"));
			}
			else
			{
				AddQuestRecord("EasterGods", "XolotlInfo");
				AddQuestUserData("EasterGods", "sSex", GetSexPhrase("ся", "ась"));
			}
			dialog.text = StringFromKey("Easter_170");
			link.l1 = StringFromKey("Easter_171", pchar);
			link.l1.go = "Xolotl_refusal";
		break;

		case "Xolotl_refusal":
			dialog.text = StringFromKey("Easter_172");
			link.l1 = StringFromKey("Easter_173");
			link.l1.go = "exit";
			EasterDissapearXolotl();
			NextDiag.TempNode = "Xolotl_return";
		break;

		case "Xolotl_return":
			dialog.text = StringFromKey("Easter_174", pchar);
			link.l1 = StringFromKey("Easter_175");
			link.l1.go = "Xolotl_return2";
		break;

		case "Xolotl_return2":
			dialog.text = StringFromKey("Easter_176");
			link.l1 = "";
			link.l1.go = "Xolotl_trade";
		break;

		case "Xolotl_trade":
			dialog.text = StringFromKey("Easter_177");
			link.l1 = "";
			Link.l1.edit = 3; // TODO ВВОД ТЕКСТА CN - Пасхалка отключена, но проблема ввода никуда не делась
			link.l1.go = "Xolotl_tradecheck";
		break;

		case "Xolotl_tradecheck":
			iCannons = sti(dialogEditStrings[3]);
			if (iCannons <= 0)
			{
				dialog.text = StringFromKey("Easter_178", pchar);
				link.l1 = StringFromKey("Easter_179", pchar);
				link.l1.go = "Xolotl_refusal";
				break;
			}
			sTemp = "";
			sTemp2 = "";
			sTemp3 = "";
			// проверка рабов
			if (!CheckAttribute(pchar, "questTemp.easter.xolotl_noslaves"))
			{
				if (GetSquadronGoods(pchar, GOOD_SLAVES) < iCannons * 50)
				{
					sTemp = StringFromKey("Easter_180", pchar);
				}
			}
			else
			{
				if (GetSquadronGoods(pchar, GOOD_COFFEE) < iCannons * 200 || GetSquadronGoods(pchar, GOOD_TOBACCO) < iCannons * 200)
				{
					sTemp = StringFromKey("Easter_181", pchar);
				}
			}
			// древесина
			if (GetSquadronGoods(pchar, sti(pchar.questTemp.easter.xolotl_lumber)) < iCannons * 100)
			{
				sTemp2 = StringFromKey("Easter_182", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.questTemp.easter.xolotl_lumber)].Name + "Gen")));
			}
			// материя
			if (GetSquadronGoods(pchar, sti(pchar.questTemp.easter.xolotl_material)) < iCannons * 200)
			{
				sTemp3 = StringFromKey("Easter_183", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.questTemp.easter.xolotl_material)].Name + "Gen")));
			}
			if (sTemp != "" || sTemp2 != "" || sTemp3 != "")
			{
				dialog.text = StringFromKey("Easter_184", sTemp, sTemp2, sTemp3);
				link.l1 = StringFromKey("Easter_185");
				link.l1.go = "Xolotl_trade";
				link.l2 = StringFromKey("Easter_186");
				link.l2.go = "Xolotl_refusal";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.easter.xolotl_noslaves"))
				{
					RemoveCharacterGoods(pchar, GOOD_SLAVES, iCannons * 50);
				}
				else
				{
					RemoveCharacterGoods(pchar, GOOD_COFFEE, iCannons * 200);
					RemoveCharacterGoods(pchar, GOOD_TOBACCO, iCannons * 200);
				}
				RemoveCharacterGoods(pchar, sti(pchar.questTemp.easter.xolotl_lumber), iCannons * 100);
				RemoveCharacterGoods(pchar, sti(pchar.questTemp.easter.xolotl_material), iCannons * 200);
				SetCharacterGoods(pchar, GOOD_CANNON_48, iCannons + GetCargoGoods(pchar, GOOD_CANNON_48));
				dialog.text = StringFromKey("Easter_187");
				link.l1 = StringFromKey("Easter_188");
				link.l1.go = "Xolotl_refusal";
			}
		break;

		case "Huitzilopochtli_1":
			dialog.text = StringFromKey("Easter_189");
			link.l1 = StringFromKey("Easter_190");
			link.l1.go = "Huitzilopochtli_2";
		break;

		case "Huitzilopochtli_2":
			dialog.text = StringFromKey("Easter_191", pchar);
			link.l1 = StringFromKey("Easter_192");
			link.l1.go = "Huitzilopochtli_3";
		break;

		case "Huitzilopochtli_3":
			dialog.text = StringFromKey("Easter_193");
			link.l1 = StringFromKey("Easter_194");
			link.l1.go = "Huitzilopochtli_4";
		break;

		case "Huitzilopochtli_4":
			dialog.text = StringFromKey("Easter_195", pchar);
			link.l1 = StringFromKey("Easter_196");
			link.l1.go = "Huitzilopochtli_5";
		break;

		case "Huitzilopochtli_5":
			dialog.text = StringFromKey("Easter_197");
			AddQuestRecord("EasterGods", "HuitzilopochtliInfo");
			AddQuestUserData("EasterGods", "sSex", GetSexPhrase("", "а"));
			link.l1 = StringFromKey("Easter_198");
			link.l1.go = "Huitzilopochtli_speedinfo";
			link.l2 = StringFromKey("Easter_199");
			link.l2.go = "Huitzilopochtli_damageinfo";
		break;

		case "Huitzilopochtli_speedinfo":
			npchar.speedinfo = 1;
			npchar.speed.blade_remain = 100;
			npchar.speed.chest_remain = 10;
			npchar.speed.level = 1;
			npchar.speed.gems = 30;
			npchar.speed.money = 200000;
			npchar.speed.bladetype = "ordinary";
			dialog.text = StringFromKey("Easter_200");
			link.l1 = StringFromKey("Easter_201");
			link.l1.go = "Huitzilopochtli_speedinfo2";
		break;

		case "Huitzilopochtli_speedinfo2":
			AddQuestRecord("EasterGods", "HuitzilopochtliSpeedInfo");
			AddQuestUserData("EasterGods", "sSex", GetSexPhrase("ен", "на"));
			dialog.text = StringFromKey("Easter_202");
			if (!CheckAttribute(npchar, "damageinfo"))
			{
				link.l1 = StringFromKey("Easter_203");
				link.l1.go = "Huitzilopochtli_damageinfo";
			}
			else
			{
				link.l2 = StringFromKey("Easter_204", pchar);
				link.l2.go = "Huitzilopochtli_refusal";
			}
		break;

		case "Huitzilopochtli_damageinfo":
			AddQuestRecord("EasterGods", "HuitzilopochtliDamageInfo");
			npchar.damageinfo = 1;
			dialog.text = StringFromKey("Easter_205");
			if (!CheckAttribute(npchar, "speedinfo"))
			{
				link.l1 = StringFromKey("Easter_206");
				link.l1.go = "Huitzilopochtli_speedinfo";
			}
			else
			{
				link.l2 = StringFromKey("Easter_207", pchar);
				link.l2.go = "Huitzilopochtli_refusal";
			}
		break;

		case "Huitzilopochtli_refusal":
			if (!CheckAttribute(pchar, "questTemp.easter.huitzilopochtli_date"))
			{
				AddQuestRecord("EasterGods", "HuitzilopochtliDate");
				pchar.questTemp.easter.huitzilopochtli_date = 1;
			}
			dialog.text = StringFromKey("Easter_208");
			link.l1 = StringFromKey("Easter_209");
			link.l1.go = "exit";
			NextDiag.TempNode = "Huitzilopochtli_return";
		break;

		case "Huitzilopochtli_return":
			dialog.text = StringFromKey("Easter_210", pchar);
			if (CheckAttribute(npchar, "speed.blade_remain") && sti(npchar.speed.blade_remain) > 0)
			{
				link.l1 = StringFromKey("Easter_211", pchar);
				link.l1.go = "Huitzilopochtli_getblade";
			}
			if (CheckAttribute(npchar, "speed.chest_remain") && sti(npchar.speed.chest_remain) > 0)
			{
				link.l2 = StringFromKey("Easter_212", pchar);
				link.l2.go = "Huitzilopochtli_getchest";
			}
			if (!CheckAttribute(npchar, "speed.blade_remain") && !CheckAttribute(npchar, "speed.chest_remain") && GetCharacterItem(pchar, "jewelry2") >= sti(npchar.speed.gems) && sti(pchar.money) >= sti(npchar.speed.money))
			{
				link.l3 = StringFromKey("Easter_213", pchar);
				link.l3.go = "Huitzilopochtli_GetSpeed";
			}
			link.l4 = StringFromKey("Easter_214");
			link.l4.go = "Huitzilopochtli_ChooseChr";
			link.l5 = StringFromKey("Easter_215", pchar);
			link.l5.go = "Huitzilopochtli_refusal";
		break;

		case "Huitzilopochtli_getblade":
			sTemp = StringFromKey("Easter_216", pchar);
			makearef(itms, pchar.items);
			n = GetAttributesNum(itms);
			for (i = n - 1; i >= 0; i--)
			{
				iItems = 0;
				itm = GetAttributeN(itms, i);
				sItems = GetAttributeName(itm);
				iTemp = FindItem(sItems);
				if (CheckAttribute(&Items[iTemp], "groupID") && Items[iTemp].groupID == BLADE_ITEM_TYPE && CheckAttribute(&Items[iTemp], "quality") && Items[iTemp].quality == npchar.speed.bladetype)
				{
					iItems += sti(itm);
					if (IsEquipCharacterByItem(pchar, sItems))
						iItems--;
					if (iItems > sti(npchar.speed.blade_remain))
						iItems = sti(npchar.speed.blade_remain);
					RemoveItems(pchar, sItems, iItems);
					npchar.speed.blade_remain = sti(npchar.speed.blade_remain) - iItems;
				}
				if (iItems > 0)
					sTemp = "";
				if (sti(npchar.speed.blade_remain) <= 0)
					break;
			}
			if (sTemp != "")
			{
				dialog.text = sTemp;
				link.l1 = StringFromKey("Easter_217");
				link.l1.go = "Huitzilopochtli_refusal";
				break;
			}
			if (sti(npchar.speed.blade_remain) <= 0)
			{
				DeleteAttribute(npchar, "speed.blade_remain");
				dialog.text = StringFromKey("Easter_218");
			}
			else
			{
				dialog.text = StringFromKey("Easter_219", npchar.speed.blade_remain);
			}
			if (CheckAttribute(npchar, "speed.chest_remain") && GetCharacterItem(pchar, "Chest") > 0)
			{
				link.l1 = StringFromKey("Easter_220", pchar);
				link.l1.go = "Huitzilopochtli_getchest";
			}
			if (!CheckAttribute(npchar, "speed.blade_remain") && !CheckAttribute(npchar, "speed.chest_remain"))
			{
				if (GetCharacterItem(pchar, "jewelry2") >= sti(npchar.speed.gems) && sti(pchar.money) >= sti(npchar.speed.money))
				{
					link.l1 = StringFromKey("Easter_221");
					link.l1.go = "Huitzilopochtli_GetSpeed";
				}
			}
			link.l2 = StringFromKey("Easter_222");
			link.l2.go = "Huitzilopochtli_refusal";
		break;

		case "Huitzilopochtli_getchest":
			iItems = GetCharacterItem(pchar, "Chest");
			if (iItems > sti(npchar.speed.chest_remain))
				iItems = sti(npchar.speed.chest_remain);
			RemoveItems(pchar, "Chest", iItems);
			npchar.speed.chest_remain = sti(npchar.speed.chest_remain) - iItems;

			if (sti(npchar.speed.chest_remain) <= 0)
			{
				DeleteAttribute(npchar, "speed.chest_remain");
				dialog.text = StringFromKey("Easter_223", pchar);
			}
			else
			{
				dialog.text = StringFromKey("Easter_224", npchar.speed.chest_remain);
			}
			if (CheckAttribute(npchar, "speed.blade_remain"))
			{
				link.l1 = StringFromKey("Easter_225", pchar);
				link.l1.go = "Huitzilopochtli_getblade";
			}
			if (!CheckAttribute(npchar, "speed.blade_remain") && !CheckAttribute(npchar, "speed.chest_remain"))
			{
				if (GetCharacterItem(pchar, "jewelry2") >= sti(npchar.speed.gems) && sti(pchar.money) >= sti(npchar.speed.money))
				{
					link.l1 = StringFromKey("Easter_226");
					link.l1.go = "Huitzilopochtli_GetSpeed";
				}
			}
			link.l2 = StringFromKey("Easter_227");
			link.l2.go = "Huitzilopochtli_refusal";
		break;

		case "Huitzilopochtli_GetSpeed":
			TakeNItems(pchar, "jewelry2", -sti(npchar.speed.gems));
			AddMoneyToCharacter(pchar, -sti(npchar.speed.money));
			npchar.speed.level = sti(npchar.speed.level) + 1;
			if (npchar.speed.level == "2")
			{
				pchar.easter.speed = 1;
				npchar.speed.blade_remain = 100;
				npchar.speed.chest_remain = 20;
				npchar.speed.gems = 60;
				npchar.speed.money = 400000;
				npchar.speed.bladetype = "good";
				if (!CheckAttribute(pchar, "questTemp.easter.damage2info"))
				{
					AddQuestRecord("EasterGods", "HuitzilopochtliSpeedInfo2");
					pchar.questTemp.easter.damage2info = 1;
				}
				dialog.text = StringFromKey("Easter_228");
				link.l1 = StringFromKey("Easter_229");
			}
			else
			{
				DeleteAttribute(npchar, "speed.gems");
				DeleteAttribute(npchar, "speed.money");
				DeleteAttribute(npchar, "speed.bladetype");
				pchar.easter.speed = 2;
				dialog.text = StringFromKey("Easter_230");
				link.l1 = StringFromKey("Easter_231");
			}
			link.l1.go = "Huitzilopochtli_refusal";
		break;

		case "Huitzilopochtli_ChooseChr":
			dialog.text = StringFromKey("Easter_232");
			link.l1 = StringFromKey("Easter_233", GetFullName(pchar));
			link.l1.go = "Huitzilopochtli_ChooseChr-" + GetMainCharacterIndex();
			for (i = 2; i <= 4; i++)
			{
				iTemp = GetOfficersIndex(pchar, i - 1);
				if (iTemp != -1)
				{
					chr = GetCharacter(iTemp);
					sAttr = "l" + i;
					link.(sAttr) = GetFullName(chr) + ".";
					link.(sAttr).go = "Huitzilopochtli_ChooseChr-" + iTemp;
				}
			}
			link.l5 = StringFromKey("Easter_234", pchar);
			link.l5.go = "Huitzilopochtli_refusal";
		break;

		case "Huitzilopochtli_CheckChr":
			iTemp = sti(npchar.damage.chridx);
			chr = GetCharacter(iTemp);
			sItems = GetCharacterEquipByGroup(chr, BLADE_ITEM_TYPE);
			iItems = FindItem(sItems);
			makearef(itm, Items[iItems]);
			if (!CheckAttribute(chr, "easter.damage." + sItems))
			{
				dialog.text = StringFromKey("Easter_235", pchar, GetConvertStr(itm.name, "ItemsDescribe.txt"));
				if (GetCharacterItem(pchar, "incas_collection") >= 1 && GetCharacterItem(pchar, "jewelry2") >= 10 && sti(pchar.money) >= 50000)
				{
					link.l1 = StringFromKey("Easter_236", pchar);
					link.l1.go = "Huitzilopochtli_GetDamage1";
				}
				if (GetOfficersQuantity(pchar) > 0)
				{
					link.l2 = StringFromKey("Easter_237", pchar);
					link.l2.go = "Huitzilopochtli_ChooseChr";
				}
				link.l3 = StringFromKey("Easter_238", pchar);
				link.l3.go = "Huitzilopochtli_refusal";
			}
			else
			{
				if (sti(chr.easter.damage.(sItems)) < 2)
				{
					if (!CheckAttribute(pchar, "questTemp.easter.huitzilopochtli_damage2"))
					{
						AddQuestRecord("EasterGods", "HuitzilopochtliDamageInfo2");
					}
					dialog.text = StringFromKey("Easter_239", pchar, GetStrSmallRegister(GetConvertStr(itm.name, "ItemsDescribe.txt")));
					if (GetCharacterItem(pchar, "incas_collection") >= 2 && GetCharacterItem(pchar, "jewelry2") >= 20 && sti(pchar.money) >= 100000)
					{
						link.l1 = StringFromKey("Easter_240", pchar);
						link.l1.go = "Huitzilopochtli_GetDamage2";
					}
					if (GetOfficersQuantity(pchar) > 0)
					{
						link.l2 = StringFromKey("Easter_241", pchar);
						link.l2.go = "Huitzilopochtli_ChooseChr";
					}
					link.l3 = StringFromKey("Easter_242", pchar);
					link.l3.go = "Huitzilopochtli_refusal";
				}
				else
				{
					dialog.text = StringFromKey("Easter_243", GetStrSmallRegister(GetConvertStr(itm.name, "ItemsDescribe.txt")));
					if (GetOfficersQuantity(pchar) > 0)
					{
						link.l1 = StringFromKey("Easter_244");
						link.l1.go = "Huitzilopochtli_ChooseChr";
					}
					else
					{
						link.l1 = StringFromKey("Easter_245");
						link.l1.go = "Huitzilopochtli_refusal";
					}
				}
			}
		break;

		case "Huitzilopochtli_GetDamage1":
			iTemp = sti(npchar.damage.chridx);
			chr = GetCharacter(iTemp);
			sItems = GetCharacterEquipByGroup(chr, BLADE_ITEM_TYPE);
			TakeNItems(pchar, "incas_collection", -1);
			TakeNItems(pchar, "jewelry2", -10);
			AddMoneyToCharacter(pchar, -50000);
			chr.easter.damage.(sItems) = 1;
			DeleteAttribute(npchar, "damage.chridx");
			dialog.text = StringFromKey("Easter_246", pchar);
			link.l1 = StringFromKey("Easter_247");
			link.l1.go = "Huitzilopochtli_refusal";
		break;

		case "Huitzilopochtli_GetDamage2":
			iTemp = sti(npchar.damage.chridx);
			chr = GetCharacter(iTemp);
			sItems = GetCharacterEquipByGroup(chr, BLADE_ITEM_TYPE);
			TakeNItems(pchar, "incas_collection", -2);
			TakeNItems(pchar, "jewelry2", -20);
			AddMoneyToCharacter(pchar, -100000);
			chr.easter.damage.(sItems) = 2;
			DeleteAttribute(npchar, "damage.chridx");
			dialog.text = StringFromKey("Easter_248", pchar);
			link.l1 = StringFromKey("Easter_249");
			link.l1.go = "Huitzilopochtli_refusal";
		break;
	}
}
			
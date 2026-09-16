//===========================================================================================
//	ПОЛОЖНЯК:
//	pStore.StoreSize	- размер магазина ("large", "medium" или "small") влияет на кол-во товара
//	pStore.Colony		- колония, которй принадлежит магазин
//	pStore.Goods.имя_товара.NotUsed		- устанавливается в TRUE для тех товаров, которыми
//===========================================================================================

void StoreInit()
{
	for (int i = 0; i < STORE_QUANTITY; i++)
	{
		if (i != Pirates_STORE && i != Providencia_STORE)
			Stores[i].Trade.Contraband.id0 = GOOD_PINCTADA;
	}
	// Bridgetown
	Stores[Bridgetown_STORE].Colony = "Bridgetown";
	Stores[Bridgetown_STORE].group  = "Bridgetown";
	Stores[Bridgetown_STORE].StoreSize = "large";
	
	Stores[Bridgetown_STORE].Trade.Export.id1 = GOOD_SANDAL;
	Stores[Bridgetown_STORE].Trade.Export.id2 = GOOD_WEAPON;
	Stores[Bridgetown_STORE].Trade.Export.id3 = GOOD_COFFEE;
	Stores[Bridgetown_STORE].Trade.Export.id4 = GOOD_OIL;
	Stores[Bridgetown_STORE].Trade.Export.id5 = GOOD_SILVER;
	Stores[Bridgetown_STORE].Trade.Export.id6 = GOOD_SUGAR;
	Stores[Bridgetown_STORE].Trade.Export.id7 = GOOD_PAPRIKA;

	Stores[Bridgetown_STORE].Trade.Import.id1 = GOOD_CINNAMON;
	Stores[Bridgetown_STORE].Trade.Import.id2 = GOOD_FOOD;
	Stores[Bridgetown_STORE].Trade.Import.id3 = GOOD_BRICK;
	Stores[Bridgetown_STORE].Trade.Import.id4 = GOOD_FRUITS;
	Stores[Bridgetown_STORE].Trade.Import.id5 = GOOD_PLANKS;
	Stores[Bridgetown_STORE].Trade.Import.id6 = GOOD_COPRA;
	Stores[Bridgetown_STORE].Trade.Import.id7 = GOOD_ALE;

	Stores[Bridgetown_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[Bridgetown_STORE].Trade.Contraband.id2 = GOOD_LINEN;
	Stores[Bridgetown_STORE].Trade.Contraband.id3 = GOOD_CHOCOLATE;
	Stores[Bridgetown_STORE].Trade.Contraband.id4 = GOOD_SAILCLOTH;
	Stores[Bridgetown_STORE].Trade.Contraband.id5 = GOOD_CLOTHES;

	// PortRoyal
	Stores[PortRoyal_STORE].Colony = "PortRoyal";
	Stores[PortRoyal_STORE].group  = "PortRoyal";
	Stores[PortRoyal_STORE].StoreSize = "large";
	
	Stores[PortRoyal_STORE].Trade.Export.id1 = GOOD_CLOTHES;
	Stores[PortRoyal_STORE].Trade.Export.id2 = GOOD_BRICK;
	Stores[PortRoyal_STORE].Trade.Export.id3 = GOOD_POWDER;
	Stores[PortRoyal_STORE].Trade.Export.id4 = GOOD_ALE;
	Stores[PortRoyal_STORE].Trade.Export.id5 = GOOD_SUGAR;
	Stores[PortRoyal_STORE].Trade.Export.id6 = GOOD_COFFEE;
	Stores[PortRoyal_STORE].Trade.Export.id7 = GOOD_RUM;

	Stores[PortRoyal_STORE].Trade.Import.id1 = GOOD_MAHOGANY;
	Stores[PortRoyal_STORE].Trade.Import.id2 = GOOD_EBONY;
	Stores[PortRoyal_STORE].Trade.Import.id3 = GOOD_SANDAL;
	Stores[PortRoyal_STORE].Trade.Import.id4 = GOOD_SILK;
	Stores[PortRoyal_STORE].Trade.Import.id5 = GOOD_LEATHER;
	Stores[PortRoyal_STORE].Trade.Import.id6 = GOOD_SAILCLOTH;
	Stores[PortRoyal_STORE].Trade.Import.id7 = GOOD_MEDICAMENT;

	Stores[PortRoyal_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[PortRoyal_STORE].Trade.Contraband.id2 = GOOD_PLANKS;
	Stores[PortRoyal_STORE].Trade.Contraband.id3 = GOOD_WEAPON;
	Stores[PortRoyal_STORE].Trade.Contraband.id4 = GOOD_CHOCOLATE;
	Stores[PortRoyal_STORE].Trade.Contraband.id5 = GOOD_OIL;

	// FortOrange
	//TODO: Здесь всё копировано с PortRoyal, надо писать с 0
	Stores[FortOrange_STORE].Colony = "FortOrange";
	Stores[FortOrange_STORE].group  = "FortOrange";
	Stores[FortOrange_STORE].StoreSize = "medium";
	
	Stores[FortOrange_STORE].Trade.Export.id1 = GOOD_CLOTHES;
	Stores[FortOrange_STORE].Trade.Export.id2 = GOOD_BRICK;
	Stores[FortOrange_STORE].Trade.Export.id3 = GOOD_POWDER;
	Stores[FortOrange_STORE].Trade.Export.id4 = GOOD_ALE;
	Stores[FortOrange_STORE].Trade.Export.id5 = GOOD_SUGAR;
	Stores[FortOrange_STORE].Trade.Export.id6 = GOOD_COFFEE;
	Stores[FortOrange_STORE].Trade.Export.id7 = GOOD_RUM;

	Stores[FortOrange_STORE].Trade.Import.id1 = GOOD_MAHOGANY;
	Stores[FortOrange_STORE].Trade.Import.id2 = GOOD_EBONY;
	Stores[FortOrange_STORE].Trade.Import.id3 = GOOD_SANDAL;
	Stores[FortOrange_STORE].Trade.Import.id4 = GOOD_SILK;
	Stores[FortOrange_STORE].Trade.Import.id5 = GOOD_LEATHER;
	Stores[FortOrange_STORE].Trade.Import.id6 = GOOD_SAILCLOTH;
	Stores[FortOrange_STORE].Trade.Import.id7 = GOOD_MEDICAMENT;

	Stores[FortOrange_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[FortOrange_STORE].Trade.Contraband.id2 = GOOD_PLANKS;
	Stores[FortOrange_STORE].Trade.Contraband.id3 = GOOD_WEAPON;
	Stores[FortOrange_STORE].Trade.Contraband.id4 = GOOD_CHOCOLATE;
	Stores[FortOrange_STORE].Trade.Contraband.id5 = GOOD_OIL;
	
	// PuertoRico
	Stores[SanJuan_STORE].Colony = "SanJuan";
	Stores[SanJuan_STORE].group  = "SanJuan";
	Stores[SanJuan_STORE].StoreSize = "large";
	
	Stores[SanJuan_STORE].Trade.Export.id1 = GOOD_ALE;
	Stores[SanJuan_STORE].Trade.Export.id2 = GOOD_PLANKS;
	Stores[SanJuan_STORE].Trade.Export.id3 = GOOD_COFFEE;
	Stores[SanJuan_STORE].Trade.Export.id4 = GOOD_CINNAMON;
	Stores[SanJuan_STORE].Trade.Export.id5 = GOOD_LEATHER;
	Stores[SanJuan_STORE].Trade.Export.id6 = GOOD_SUGAR;
	Stores[SanJuan_STORE].Trade.Export.id7 = GOOD_LINEN;

	Stores[SanJuan_STORE].Trade.Import.id1 = GOOD_TOBACCO;
	Stores[SanJuan_STORE].Trade.Import.id2 = GOOD_BRICK;
	Stores[SanJuan_STORE].Trade.Import.id3 = GOOD_FRUITS;
	Stores[SanJuan_STORE].Trade.Import.id4 = GOOD_SAILCLOTH;
	Stores[SanJuan_STORE].Trade.Import.id5 = GOOD_WINE;
	Stores[SanJuan_STORE].Trade.Import.id6 = GOOD_WEAPON;
	Stores[SanJuan_STORE].Trade.Import.id7 = GOOD_POWDER;

	Stores[SanJuan_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[SanJuan_STORE].Trade.Contraband.id2 = GOOD_COTTON;
	Stores[SanJuan_STORE].Trade.Contraband.id3 = GOOD_SILK;
	Stores[SanJuan_STORE].Trade.Contraband.id4 = GOOD_COPRA;
	Stores[SanJuan_STORE].Trade.Contraband.id5 = GOOD_WHEAT;

	// Santiago
	Stores[Santiago_STORE].Colony = "Santiago";
	Stores[Santiago_STORE].group  = "Santiago";
	Stores[Santiago_STORE].StoreSize = "large";
	
	Stores[Santiago_STORE].Trade.Export.id1 = GOOD_COFFEE;
	Stores[Santiago_STORE].Trade.Export.id2 = GOOD_FRUITS;
	Stores[Santiago_STORE].Trade.Export.id3 = GOOD_CHOCOLATE;
	Stores[Santiago_STORE].Trade.Export.id4 = GOOD_LINEN;
	Stores[Santiago_STORE].Trade.Export.id5 = GOOD_SANDAL;
	Stores[Santiago_STORE].Trade.Export.id6 = GOOD_WHEAT;
	Stores[Santiago_STORE].Trade.Export.id7 = GOOD_PLANKS;

	Stores[Santiago_STORE].Trade.Import.id1 = GOOD_EBONY;
	Stores[Santiago_STORE].Trade.Import.id2 = GOOD_BRICK;
	Stores[Santiago_STORE].Trade.Import.id3 = GOOD_GOLD;
	Stores[Santiago_STORE].Trade.Import.id4 = GOOD_SAILCLOTH;
	Stores[Santiago_STORE].Trade.Import.id5 = GOOD_BALLS;
	Stores[Santiago_STORE].Trade.Import.id6 = GOOD_GRAPES;
	Stores[Santiago_STORE].Trade.Import.id7 = GOOD_OIL;

	Stores[Santiago_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[Santiago_STORE].Trade.Contraband.id2 = GOOD_TOBACCO;
	Stores[Santiago_STORE].Trade.Contraband.id3 = GOOD_POWDER;
	Stores[Santiago_STORE].Trade.Contraband.id4 = GOOD_WEAPON;
	Stores[Santiago_STORE].Trade.Contraband.id5 = GOOD_COTTON;

	// PuertoPrincipe
	//TODO: Здесь всё копировано с Santiago, надо писать с 0
	Stores[PuertoPrincipe_STORE].Colony = "PuertoPrincipe";
	Stores[PuertoPrincipe_STORE].group  = "PuertoPrincipe";
	Stores[PuertoPrincipe_STORE].StoreSize = "small";
	
	Stores[PuertoPrincipe_STORE].Trade.Export.id1 = GOOD_COFFEE;
	Stores[PuertoPrincipe_STORE].Trade.Export.id2 = GOOD_FRUITS;
	Stores[PuertoPrincipe_STORE].Trade.Export.id3 = GOOD_CHOCOLATE;
	Stores[PuertoPrincipe_STORE].Trade.Export.id4 = GOOD_LINEN;
	Stores[PuertoPrincipe_STORE].Trade.Export.id5 = GOOD_SANDAL;
	Stores[PuertoPrincipe_STORE].Trade.Export.id6 = GOOD_WHEAT;
	Stores[PuertoPrincipe_STORE].Trade.Export.id7 = GOOD_PLANKS;

	Stores[PuertoPrincipe_STORE].Trade.Import.id1 = GOOD_EBONY;
	Stores[PuertoPrincipe_STORE].Trade.Import.id2 = GOOD_BRICK;
	Stores[PuertoPrincipe_STORE].Trade.Import.id3 = GOOD_GOLD;
	Stores[PuertoPrincipe_STORE].Trade.Import.id4 = GOOD_SAILCLOTH;
	Stores[PuertoPrincipe_STORE].Trade.Import.id5 = GOOD_BALLS;
	Stores[PuertoPrincipe_STORE].Trade.Import.id6 = GOOD_GRAPES;
	Stores[PuertoPrincipe_STORE].Trade.Import.id7 = GOOD_OIL;

	Stores[PuertoPrincipe_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[PuertoPrincipe_STORE].Trade.Contraband.id2 = GOOD_TOBACCO;
	Stores[PuertoPrincipe_STORE].Trade.Contraband.id3 = GOOD_POWDER;
	Stores[PuertoPrincipe_STORE].Trade.Contraband.id4 = GOOD_WEAPON;
	Stores[PuertoPrincipe_STORE].Trade.Contraband.id5 = GOOD_COTTON;
	
	// Havana
	Stores[Havana_STORE].Colony = "Havana";
	Stores[Havana_STORE].group  = "Havana";
	Stores[Havana_STORE].StoreSize = "large";
	
	Stores[Havana_STORE].Trade.Export.id1 = GOOD_MAHOGANY;
	Stores[Havana_STORE].Trade.Export.id2 = GOOD_MEDICAMENT;
	Stores[Havana_STORE].Trade.Export.id3 = GOOD_LEATHER;
	Stores[Havana_STORE].Trade.Export.id4 = GOOD_FOOD;
	Stores[Havana_STORE].Trade.Export.id5 = GOOD_WINE;
	Stores[Havana_STORE].Trade.Export.id6 = GOOD_SUGAR;
	Stores[Havana_STORE].Trade.Export.id7 = GOOD_PAPRIKA;

	Stores[Havana_STORE].Trade.Import.id1 = GOOD_OIL;
	Stores[Havana_STORE].Trade.Import.id2 = GOOD_COPRA;
	Stores[Havana_STORE].Trade.Import.id3 = GOOD_BRICK;
	Stores[Havana_STORE].Trade.Import.id4 = GOOD_SAILCLOTH;
	Stores[Havana_STORE].Trade.Import.id5 = GOOD_GRAPES;
	Stores[Havana_STORE].Trade.Import.id6 = GOOD_SILVER;
	Stores[Havana_STORE].Trade.Import.id7 = GOOD_SILK;

	Stores[Havana_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[Havana_STORE].Trade.Contraband.id2 = GOOD_TOBACCO;
	Stores[Havana_STORE].Trade.Contraband.id3 = GOOD_POWDER;
	Stores[Havana_STORE].Trade.Contraband.id4 = GOOD_WEAPON;
	Stores[Havana_STORE].Trade.Contraband.id5 = GOOD_COTTON;

	// Villemstad
	Stores[Villemstad_STORE].Colony = "Villemstad";
	Stores[Villemstad_STORE].Group  = "Villemstad";
	Stores[Villemstad_STORE].StoreSize = "large";
	
	Stores[Villemstad_STORE].Trade.Export.id1 = GOOD_ALE;
	Stores[Villemstad_STORE].Trade.Export.id2 = GOOD_SANDAL;
	Stores[Villemstad_STORE].Trade.Export.id3 = GOOD_FOOD;
	Stores[Villemstad_STORE].Trade.Export.id4 = GOOD_MAHOGANY;
	Stores[Villemstad_STORE].Trade.Export.id5 = GOOD_OIL;
	Stores[Villemstad_STORE].Trade.Export.id6 = GOOD_LINEN;
	Stores[Villemstad_STORE].Trade.Export.id7 = GOOD_COTTON;

	Stores[Villemstad_STORE].Trade.Import.id1 = GOOD_SUGAR;
	Stores[Villemstad_STORE].Trade.Import.id2 = GOOD_BRICK;
	Stores[Villemstad_STORE].Trade.Import.id3 = GOOD_SAILCLOTH;
	Stores[Villemstad_STORE].Trade.Import.id4 = GOOD_FRUITS;
	Stores[Villemstad_STORE].Trade.Import.id5 = GOOD_WEAPON;
	Stores[Villemstad_STORE].Trade.Import.id6 = GOOD_CHOCOLATE;
	Stores[Villemstad_STORE].Trade.Import.id7 = GOOD_PAPRIKA;

	Stores[Villemstad_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[Villemstad_STORE].Trade.Contraband.id2 = GOOD_WINE;
	Stores[Villemstad_STORE].Trade.Contraband.id3 = GOOD_TOBACCO;
	Stores[Villemstad_STORE].Trade.Contraband.id4 = GOOD_CINNAMON;
	Stores[Villemstad_STORE].Trade.Contraband.id5 = GOOD_POWDER;

	// Tortuga
	Stores[Tortuga_STORE].Colony	= "Tortuga";
	Stores[Tortuga_STORE].Group		= "Tortuga";	
	Stores[Tortuga_STORE].StoreSize = "large";
	
	Stores[Tortuga_STORE].Trade.Export.id1 = GOOD_ALE;
	Stores[Tortuga_STORE].Trade.Export.id2 = GOOD_KNIPPELS;
	Stores[Tortuga_STORE].Trade.Export.id3 = GOOD_WHEAT;
	Stores[Tortuga_STORE].Trade.Export.id4 = GOOD_LEATHER;
	Stores[Tortuga_STORE].Trade.Export.id5 = GOOD_COFFEE;
	Stores[Tortuga_STORE].Trade.Export.id6 = GOOD_LINEN;
	Stores[Tortuga_STORE].Trade.Export.id7 = GOOD_PAPRIKA;

	Stores[Tortuga_STORE].Trade.Import.id1 = GOOD_SILVER;
	Stores[Tortuga_STORE].Trade.Import.id2 = GOOD_MEDICAMENT;
	Stores[Tortuga_STORE].Trade.Import.id3 = GOOD_TOBACCO;
	Stores[Tortuga_STORE].Trade.Import.id4 = GOOD_MAHOGANY;
	Stores[Tortuga_STORE].Trade.Import.id5 = GOOD_BALLS;
	Stores[Tortuga_STORE].Trade.Import.id6 = GOOD_SILK;
	Stores[Tortuga_STORE].Trade.Import.id7 = GOOD_WEAPON;

	Stores[Tortuga_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[Tortuga_STORE].Trade.Contraband.id2 = GOOD_COPRA;
	Stores[Tortuga_STORE].Trade.Contraband.id3 = GOOD_OIL;
	Stores[Tortuga_STORE].Trade.Contraband.id4 = GOOD_BRICK;
	Stores[Tortuga_STORE].Trade.Contraband.id5 = GOOD_EBONY;

	// Marigo
	Stores[Marigo_STORE].Colony = "Marigo";
	Stores[Marigo_STORE].Group  = "Marigo";
	Stores[Marigo_STORE].StoreSize = "large";
	
	Stores[Marigo_STORE].Trade.Export.id1 = GOOD_CHOCOLATE;
	Stores[Marigo_STORE].Trade.Export.id2 = GOOD_PLANKS;
	Stores[Marigo_STORE].Trade.Export.id3 = GOOD_MAHOGANY;
	Stores[Marigo_STORE].Trade.Export.id4 = GOOD_MEDICAMENT;
	Stores[Marigo_STORE].Trade.Export.id5 = GOOD_LINEN;
	Stores[Marigo_STORE].Trade.Export.id6 = GOOD_LEATHER;
	Stores[Marigo_STORE].Trade.Export.id7 = GOOD_OIL;

	Stores[Marigo_STORE].Trade.Import.id1 = GOOD_FOOD;
	Stores[Marigo_STORE].Trade.Import.id2 = GOOD_WHEAT;
	Stores[Marigo_STORE].Trade.Import.id3 = GOOD_GRAPES;
	Stores[Marigo_STORE].Trade.Import.id4 = GOOD_COPRA;
	Stores[Marigo_STORE].Trade.Import.id5 = GOOD_BRICK;
	Stores[Marigo_STORE].Trade.Import.id6 = GOOD_CLOTHES;
	Stores[Marigo_STORE].Trade.Import.id7 = GOOD_SAILCLOTH;

	Stores[Marigo_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[Marigo_STORE].Trade.Contraband.id2 = GOOD_TOBACCO;
	Stores[Marigo_STORE].Trade.Contraband.id3 = GOOD_WINE;
	Stores[Marigo_STORE].Trade.Contraband.id4 = GOOD_WEAPON;
	Stores[Marigo_STORE].Trade.Contraband.id5 = GOOD_SUGAR;
	
	// PortSpein
	Stores[PortSpein_STORE].Colony = "PortSpein";
	Stores[PortSpein_STORE].group  = "PortSpein";
	Stores[PortSpein_STORE].StoreSize = "large";
	
	Stores[PortSpein_STORE].Trade.Export.id1 = GOOD_GOLD;
	Stores[PortSpein_STORE].Trade.Export.id2 = GOOD_WINE;
	Stores[PortSpein_STORE].Trade.Export.id3 = GOOD_SANDAL;
	Stores[PortSpein_STORE].Trade.Export.id4 = GOOD_POWDER;
	Stores[PortSpein_STORE].Trade.Export.id5 = GOOD_TOBACCO;
	Stores[PortSpein_STORE].Trade.Export.id6 = GOOD_WHEAT;
	Stores[PortSpein_STORE].Trade.Export.id7 = GOOD_GRAPES;

	Stores[PortSpein_STORE].Trade.Import.id1 = GOOD_WEAPON;
	Stores[PortSpein_STORE].Trade.Import.id2 = GOOD_MEDICAMENT;
	Stores[PortSpein_STORE].Trade.Import.id3 = GOOD_COPRA;
	Stores[PortSpein_STORE].Trade.Import.id4 = GOOD_LEATHER;
	Stores[PortSpein_STORE].Trade.Import.id5 = GOOD_CHOCOLATE;
	Stores[PortSpein_STORE].Trade.Import.id6 = GOOD_CINNAMON;
	Stores[PortSpein_STORE].Trade.Import.id7 = GOOD_BRICK;

	Stores[PortSpein_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[PortSpein_STORE].Trade.Contraband.id2 = GOOD_ALE;
	Stores[PortSpein_STORE].Trade.Contraband.id3 = GOOD_SILK;
	Stores[PortSpein_STORE].Trade.Contraband.id4 = GOOD_SUGAR;
	Stores[PortSpein_STORE].Trade.Contraband.id5 = GOOD_MAHOGANY;
	
	// Charles
	Stores[Charles_STORE].Colony	= "Charles";
	Stores[Charles_STORE].group		= "Charles";
	Stores[Charles_STORE].StoreSize = "large";
	
	Stores[Charles_STORE].Trade.Export.id1 = GOOD_RUM;
	Stores[Charles_STORE].Trade.Export.id2 = GOOD_BRICK;
	Stores[Charles_STORE].Trade.Export.id3 = GOOD_BOMBS;
	Stores[Charles_STORE].Trade.Export.id4 = GOOD_PAPRIKA;
	Stores[Charles_STORE].Trade.Export.id5 = GOOD_MEDICAMENT;
	Stores[Charles_STORE].Trade.Export.id6 = GOOD_ALE;
	Stores[Charles_STORE].Trade.Export.id7 = GOOD_KNIPPELS;

	Stores[Charles_STORE].Trade.Import.id1 = GOOD_TOBACCO;
	Stores[Charles_STORE].Trade.Import.id2 = GOOD_WHEAT;
	Stores[Charles_STORE].Trade.Import.id3 = GOOD_COTTON;
	Stores[Charles_STORE].Trade.Import.id4 = GOOD_SILK;
	Stores[Charles_STORE].Trade.Import.id5 = GOOD_FOOD;
	Stores[Charles_STORE].Trade.Import.id6 = GOOD_SUGAR;
	Stores[Charles_STORE].Trade.Import.id7 = GOOD_SAILCLOTH;

	Stores[Charles_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[Charles_STORE].Trade.Contraband.id2 = GOOD_FRUITS;
	Stores[Charles_STORE].Trade.Contraband.id3 = GOOD_WINE;
	Stores[Charles_STORE].Trade.Contraband.id4 = GOOD_SANDAL;
	Stores[Charles_STORE].Trade.Contraband.id5 = GOOD_EBONY;

	// SentJons
	Stores[SentJons_STORE].Colony = "SentJons";
	Stores[SentJons_STORE].group  = "SentJons";
	Stores[SentJons_STORE].StoreSize = "large";
	
	Stores[SentJons_STORE].Trade.Export.id1 = GOOD_RUM;
	Stores[SentJons_STORE].Trade.Export.id2 = GOOD_BALLS;
	Stores[SentJons_STORE].Trade.Export.id3 = GOOD_LINEN;
	Stores[SentJons_STORE].Trade.Export.id4 = GOOD_POWDER;
	Stores[SentJons_STORE].Trade.Export.id5 = GOOD_CLOTHES;
	Stores[SentJons_STORE].Trade.Export.id6 = GOOD_ALE;
	Stores[SentJons_STORE].Trade.Export.id7 = GOOD_WEAPON;

	Stores[SentJons_STORE].Trade.Import.id1 = GOOD_SUGAR;
	Stores[SentJons_STORE].Trade.Import.id2 = GOOD_MEDICAMENT;
	Stores[SentJons_STORE].Trade.Import.id3 = GOOD_EBONY;
	Stores[SentJons_STORE].Trade.Import.id4 = GOOD_COPRA;
	Stores[SentJons_STORE].Trade.Import.id5 = GOOD_FRUITS;
	Stores[SentJons_STORE].Trade.Import.id6 = GOOD_WINE;
	Stores[SentJons_STORE].Trade.Import.id7 = GOOD_LEATHER;

	Stores[SentJons_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[SentJons_STORE].Trade.Contraband.id2 = GOOD_WHEAT;
	Stores[SentJons_STORE].Trade.Contraband.id3 = GOOD_COTTON;
	Stores[SentJons_STORE].Trade.Contraband.id4 = GOOD_OIL;
	Stores[SentJons_STORE].Trade.Contraband.id5 = GOOD_COFFEE;
	
	// BasTer
	Stores[BasTer_STORE].Colony = "BasTer";
	Stores[BasTer_STORE].group  = "BasTer";
	Stores[BasTer_STORE].StoreSize = "large";
	
	Stores[BasTer_STORE].Trade.Export.id1 = GOOD_PAPRIKA;
	Stores[BasTer_STORE].Trade.Export.id2 = GOOD_CINNAMON;
	Stores[BasTer_STORE].Trade.Export.id3 = GOOD_BRICK;
	Stores[BasTer_STORE].Trade.Export.id4 = GOOD_SILK;
	Stores[BasTer_STORE].Trade.Export.id5 = GOOD_POWDER;
	Stores[BasTer_STORE].Trade.Export.id6 = GOOD_WINE;
	Stores[BasTer_STORE].Trade.Export.id7 = GOOD_BALLS;

	Stores[BasTer_STORE].Trade.Import.id1 = GOOD_PLANKS;
	Stores[BasTer_STORE].Trade.Import.id2 = GOOD_EBONY;
	Stores[BasTer_STORE].Trade.Import.id3 = GOOD_MAHOGANY;
	Stores[BasTer_STORE].Trade.Import.id4 = GOOD_SANDAL;
	Stores[BasTer_STORE].Trade.Import.id5 = GOOD_CLOTHES;
	Stores[BasTer_STORE].Trade.Import.id6 = GOOD_OIL;
	Stores[BasTer_STORE].Trade.Import.id7 = GOOD_GRAPES;

	Stores[BasTer_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[BasTer_STORE].Trade.Contraband.id2 = GOOD_MEDICAMENT;
	Stores[BasTer_STORE].Trade.Contraband.id3 = GOOD_LEATHER;
	Stores[BasTer_STORE].Trade.Contraband.id4 = GOOD_CHOCOLATE;
	Stores[BasTer_STORE].Trade.Contraband.id5 = GOOD_COPRA;
	
	// FortFrance
	Stores[FortFrance_STORE].Colony = "FortFrance";
	Stores[FortFrance_STORE].group  = "FortFrance";
	Stores[FortFrance_STORE].StoreSize = "large";
	
	Stores[FortFrance_STORE].Trade.Export.id1 = GOOD_WINE;
	Stores[FortFrance_STORE].Trade.Export.id2 = GOOD_FOOD;
	Stores[FortFrance_STORE].Trade.Export.id3 = GOOD_WHEAT;
	Stores[FortFrance_STORE].Trade.Export.id4 = GOOD_SUGAR;
	Stores[FortFrance_STORE].Trade.Export.id5 = GOOD_TOBACCO;
	Stores[FortFrance_STORE].Trade.Export.id6 = GOOD_COTTON;
	Stores[FortFrance_STORE].Trade.Export.id7 = GOOD_KNIPPELS;

	Stores[FortFrance_STORE].Trade.Import.id1 = GOOD_RUM;
	Stores[FortFrance_STORE].Trade.Import.id2 = GOOD_MEDICAMENT;
	Stores[FortFrance_STORE].Trade.Import.id3 = GOOD_CLOTHES;
	Stores[FortFrance_STORE].Trade.Import.id4 = GOOD_BOMBS;
	Stores[FortFrance_STORE].Trade.Import.id5 = GOOD_CHOCOLATE;
	Stores[FortFrance_STORE].Trade.Import.id6 = GOOD_LEATHER;
	Stores[FortFrance_STORE].Trade.Import.id7 = GOOD_LINEN;

	Stores[FortFrance_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[FortFrance_STORE].Trade.Contraband.id2 = GOOD_PLANKS;
	Stores[FortFrance_STORE].Trade.Contraband.id3 = GOOD_FRUITS;
	Stores[FortFrance_STORE].Trade.Contraband.id4 = GOOD_MAHOGANY;
	Stores[FortFrance_STORE].Trade.Contraband.id5 = GOOD_EBONY;
	
	// LeFransua
	//TODO: Здесь всё копировано с FortFrance, надо писать с 0
	Stores[LeFransua_STORE].Colony = "LeFransua";
	Stores[LeFransua_STORE].group  = "LeFransua";
	Stores[LeFransua_STORE].StoreSize = "small";
	
	Stores[LeFransua_STORE].Trade.Export.id1 = GOOD_WINE;
	Stores[LeFransua_STORE].Trade.Export.id2 = GOOD_FOOD;
	Stores[LeFransua_STORE].Trade.Export.id3 = GOOD_WHEAT;
	Stores[LeFransua_STORE].Trade.Export.id4 = GOOD_SUGAR;
	Stores[LeFransua_STORE].Trade.Export.id5 = GOOD_TOBACCO;
	Stores[LeFransua_STORE].Trade.Export.id6 = GOOD_COTTON;
	Stores[LeFransua_STORE].Trade.Export.id7 = GOOD_KNIPPELS;

	Stores[LeFransua_STORE].Trade.Import.id1 = GOOD_RUM;
	Stores[LeFransua_STORE].Trade.Import.id2 = GOOD_MEDICAMENT;
	Stores[LeFransua_STORE].Trade.Import.id3 = GOOD_CLOTHES;
	Stores[LeFransua_STORE].Trade.Import.id4 = GOOD_BOMBS;
	Stores[LeFransua_STORE].Trade.Import.id5 = GOOD_CHOCOLATE;
	Stores[LeFransua_STORE].Trade.Import.id6 = GOOD_LEATHER;
	Stores[LeFransua_STORE].Trade.Import.id7 = GOOD_LINEN;

	Stores[LeFransua_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[LeFransua_STORE].Trade.Contraband.id2 = GOOD_PLANKS;
	Stores[LeFransua_STORE].Trade.Contraband.id3 = GOOD_FRUITS;
	Stores[LeFransua_STORE].Trade.Contraband.id4 = GOOD_MAHOGANY;
	Stores[LeFransua_STORE].Trade.Contraband.id5 = GOOD_EBONY;
	
	// SantoDomingo
	Stores[SantoDomingo_STORE].Colony = "SantoDomingo";
	Stores[SantoDomingo_STORE].group  = "SantoDomingo";
	Stores[SantoDomingo_STORE].StoreSize = "large";
	
	Stores[SantoDomingo_STORE].Trade.Export.id1 = GOOD_ALE;
	Stores[SantoDomingo_STORE].Trade.Export.id2 = GOOD_RUM;
	Stores[SantoDomingo_STORE].Trade.Export.id3 = GOOD_WINE;
	Stores[SantoDomingo_STORE].Trade.Export.id4 = GOOD_CHOCOLATE;
	Stores[SantoDomingo_STORE].Trade.Export.id5 = GOOD_CINNAMON;
	Stores[SantoDomingo_STORE].Trade.Export.id6 = GOOD_SANDAL;
	Stores[SantoDomingo_STORE].Trade.Export.id7 = GOOD_FOOD;

	Stores[SantoDomingo_STORE].Trade.Import.id1 = GOOD_FRUITS;
	Stores[SantoDomingo_STORE].Trade.Import.id2 = GOOD_MEDICAMENT;
	Stores[SantoDomingo_STORE].Trade.Import.id3 = GOOD_SAILCLOTH;
	Stores[SantoDomingo_STORE].Trade.Import.id4 = GOOD_TOBACCO;
	Stores[SantoDomingo_STORE].Trade.Import.id5 = GOOD_GRAPES;
	Stores[SantoDomingo_STORE].Trade.Import.id6 = GOOD_BALLS;
	Stores[SantoDomingo_STORE].Trade.Import.id7 = GOOD_WEAPON;

	Stores[SantoDomingo_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[SantoDomingo_STORE].Trade.Contraband.id2 = GOOD_OIL;
	Stores[SantoDomingo_STORE].Trade.Contraband.id3 = GOOD_COPRA;
	Stores[SantoDomingo_STORE].Trade.Contraband.id4 = GOOD_BRICK;
	Stores[SantoDomingo_STORE].Trade.Contraband.id5 = GOOD_EBONY;
	
	// LaVega
	//TODO: Здесь всё копировано с SantoDomingo, надо писать с 0
	Stores[LaVega_STORE].Colony = "LaVega";
	Stores[LaVega_STORE].group  = "LaVega";
	Stores[LaVega_STORE].StoreSize = "small";
	
	Stores[LaVega_STORE].Trade.Export.id1 = GOOD_ALE;
	Stores[LaVega_STORE].Trade.Export.id2 = GOOD_RUM;
	Stores[LaVega_STORE].Trade.Export.id3 = GOOD_WINE;
	Stores[LaVega_STORE].Trade.Export.id4 = GOOD_CHOCOLATE;
	Stores[LaVega_STORE].Trade.Export.id5 = GOOD_CINNAMON;
	Stores[LaVega_STORE].Trade.Export.id6 = GOOD_SANDAL;
	Stores[LaVega_STORE].Trade.Export.id7 = GOOD_FOOD;

	Stores[LaVega_STORE].Trade.Import.id1 = GOOD_FRUITS;
	Stores[LaVega_STORE].Trade.Import.id2 = GOOD_MEDICAMENT;
	Stores[LaVega_STORE].Trade.Import.id3 = GOOD_SAILCLOTH;
	Stores[LaVega_STORE].Trade.Import.id4 = GOOD_TOBACCO;
	Stores[LaVega_STORE].Trade.Import.id5 = GOOD_GRAPES;
	Stores[LaVega_STORE].Trade.Import.id6 = GOOD_BALLS;
	Stores[LaVega_STORE].Trade.Import.id7 = GOOD_WEAPON;

	Stores[LaVega_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[LaVega_STORE].Trade.Contraband.id2 = GOOD_OIL;
	Stores[LaVega_STORE].Trade.Contraband.id3 = GOOD_COPRA;
	Stores[LaVega_STORE].Trade.Contraband.id4 = GOOD_BRICK;
	Stores[LaVega_STORE].Trade.Contraband.id5 = GOOD_EBONY;
	
	// PortPax
	Stores[PortPax_STORE].Colony	= "PortPax";
	Stores[PortPax_STORE].group		= "PortPax";
	Stores[PortPax_STORE].StoreSize	= "large";
	
	Stores[PortPax_STORE].Trade.Export.id1 = GOOD_BOMBS;
	Stores[PortPax_STORE].Trade.Export.id2 = GOOD_RUM;
	Stores[PortPax_STORE].Trade.Export.id3 = GOOD_WINE;
	Stores[PortPax_STORE].Trade.Export.id4 = GOOD_SUGAR;
	Stores[PortPax_STORE].Trade.Export.id5 = GOOD_CLOTHES;
	Stores[PortPax_STORE].Trade.Export.id6 = GOOD_LINEN;
	Stores[PortPax_STORE].Trade.Export.id7 = GOOD_FOOD;

	Stores[PortPax_STORE].Trade.Import.id1 = GOOD_GOLD;
	Stores[PortPax_STORE].Trade.Import.id2 = GOOD_MEDICAMENT;
	Stores[PortPax_STORE].Trade.Import.id3 = GOOD_FRUITS;
	Stores[PortPax_STORE].Trade.Import.id4 = GOOD_COTTON;
	Stores[PortPax_STORE].Trade.Import.id5 = GOOD_GRAPES;
	Stores[PortPax_STORE].Trade.Import.id6 = GOOD_SILK;
	Stores[PortPax_STORE].Trade.Import.id7 = GOOD_POWDER;

	Stores[PortPax_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[PortPax_STORE].Trade.Contraband.id2 = GOOD_OIL;
	Stores[PortPax_STORE].Trade.Contraband.id3 = GOOD_COPRA;
	Stores[PortPax_STORE].Trade.Contraband.id4 = GOOD_BRICK;
	Stores[PortPax_STORE].Trade.Contraband.id5 = GOOD_EBONY;
	
	// Pirates Town
	Stores[Pirates_STORE].Colony	= "Pirates";
	Stores[Pirates_STORE].group		= "Pirates";
	Stores[Pirates_STORE].StoreSize = "medium";
	
	Stores[Pirates_STORE].Trade.Export.id1 = GOOD_RUM;
	Stores[Pirates_STORE].Trade.Export.id2 = GOOD_BOMBS;

	Stores[Pirates_STORE].Trade.Import.id1 = GOOD_SLAVES;
	Stores[Pirates_STORE].Trade.Import.id2 = GOOD_SAILCLOTH;
	Stores[Pirates_STORE].Trade.Import.id3 = GOOD_ALE;
	Stores[Pirates_STORE].Trade.Import.id4 = GOOD_SILVER;
	Stores[Pirates_STORE].Trade.Import.id5 = GOOD_POWDER;
	Stores[Pirates_STORE].Trade.Import.id6 = GOOD_ALE;
	Stores[Pirates_STORE].Trade.Import.id7 = GOOD_GOLD;
	
	// PortoBello
	Stores[PortoBello_STORE].Colony = "PortoBello";
	Stores[PortoBello_STORE].group  = "PortoBello";
	Stores[PortoBello_STORE].StoreSize = "large";
	
	Stores[PortoBello_STORE].Trade.Export.id1 = GOOD_MEDICAMENT;
	Stores[PortoBello_STORE].Trade.Export.id2 = GOOD_OIL;
	Stores[PortoBello_STORE].Trade.Export.id3 = GOOD_WINE;
	Stores[PortoBello_STORE].Trade.Export.id4 = GOOD_SUGAR;
	Stores[PortoBello_STORE].Trade.Export.id5 = GOOD_ALE;
	Stores[PortoBello_STORE].Trade.Export.id6 = GOOD_LINEN;
	Stores[PortoBello_STORE].Trade.Export.id7 = GOOD_CINNAMON;

	Stores[PortoBello_STORE].Trade.Import.id1 = GOOD_RUM;
	Stores[PortoBello_STORE].Trade.Import.id2 = GOOD_BALLS;
	Stores[PortoBello_STORE].Trade.Import.id3 = GOOD_SILK;
	Stores[PortoBello_STORE].Trade.Import.id4 = GOOD_PAPRIKA;
	Stores[PortoBello_STORE].Trade.Import.id5 = GOOD_SANDAL;
	Stores[PortoBello_STORE].Trade.Import.id6 = GOOD_LEATHER;
	Stores[PortoBello_STORE].Trade.Import.id7 = GOOD_SAILCLOTH;

	Stores[PortoBello_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[PortoBello_STORE].Trade.Contraband.id2 = GOOD_BRICK;
	Stores[PortoBello_STORE].Trade.Contraband.id3 = GOOD_COPRA;
	Stores[PortoBello_STORE].Trade.Contraband.id4 = GOOD_FRUITS;
	Stores[PortoBello_STORE].Trade.Contraband.id5 = GOOD_CLOTHES;

	// Panama
	// Магазин в городе пока не работает, поставил как у PortoBello
	Stores[Panama_STORE].Colony = "Panama";
	Stores[Panama_STORE].group  = "Panama";
	Stores[Panama_STORE].StoreSize = "large";
	
	Stores[Panama_STORE].Trade.Export.id1 = GOOD_MEDICAMENT;
	Stores[Panama_STORE].Trade.Export.id2 = GOOD_OIL;
	Stores[Panama_STORE].Trade.Export.id3 = GOOD_WINE;
	Stores[Panama_STORE].Trade.Export.id4 = GOOD_SUGAR;
	Stores[Panama_STORE].Trade.Export.id5 = GOOD_ALE;
	Stores[Panama_STORE].Trade.Export.id6 = GOOD_LINEN;
	Stores[Panama_STORE].Trade.Export.id7 = GOOD_CINNAMON;

	Stores[Panama_STORE].Trade.Import.id1 = GOOD_RUM;
	Stores[Panama_STORE].Trade.Import.id2 = GOOD_BALLS;
	Stores[Panama_STORE].Trade.Import.id3 = GOOD_SILK;
	Stores[Panama_STORE].Trade.Import.id4 = GOOD_PAPRIKA;
	Stores[Panama_STORE].Trade.Import.id5 = GOOD_SANDAL;
	Stores[Panama_STORE].Trade.Import.id6 = GOOD_LEATHER;
	Stores[Panama_STORE].Trade.Import.id7 = GOOD_SAILCLOTH;

	Stores[Panama_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[Panama_STORE].Trade.Contraband.id2 = GOOD_BRICK;
	Stores[Panama_STORE].Trade.Contraband.id3 = GOOD_COPRA;
	Stores[Panama_STORE].Trade.Contraband.id4 = GOOD_FRUITS;
	Stores[Panama_STORE].Trade.Contraband.id5 = GOOD_CLOTHES;

	// Cartahena
	Stores[Cartahena_STORE].Colony = "Cartahena";
	Stores[Cartahena_STORE].group  = "Cartahena";
	Stores[Cartahena_STORE].StoreSize = "large";
	
	Stores[Cartahena_STORE].Trade.Export.id1 = GOOD_WHEAT;
	Stores[Cartahena_STORE].Trade.Export.id2 = GOOD_CHOCOLATE;
	Stores[Cartahena_STORE].Trade.Export.id3 = GOOD_GRAPES;
	Stores[Cartahena_STORE].Trade.Export.id4 = GOOD_OIL;
	Stores[Cartahena_STORE].Trade.Export.id5 = GOOD_PLANKS;
	Stores[Cartahena_STORE].Trade.Export.id6 = GOOD_COTTON;
	Stores[Cartahena_STORE].Trade.Export.id7 = GOOD_EBONY;

	Stores[Cartahena_STORE].Trade.Import.id1 = GOOD_CLOTHES;
	Stores[Cartahena_STORE].Trade.Import.id2 = GOOD_COFFEE;
	Stores[Cartahena_STORE].Trade.Import.id3 = GOOD_MEDICAMENT;
	Stores[Cartahena_STORE].Trade.Import.id4 = GOOD_RUM;
	Stores[Cartahena_STORE].Trade.Import.id5 = GOOD_FRUITS;
	Stores[Cartahena_STORE].Trade.Import.id6 = GOOD_LEATHER;
	Stores[Cartahena_STORE].Trade.Import.id7 = GOOD_TOBACCO;

	Stores[Cartahena_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[Cartahena_STORE].Trade.Contraband.id2 = GOOD_BRICK;
	Stores[Cartahena_STORE].Trade.Contraband.id3 = GOOD_SAILCLOTH;
	Stores[Cartahena_STORE].Trade.Contraband.id4 = GOOD_PAPRIKA;
	Stores[Cartahena_STORE].Trade.Contraband.id5 = GOOD_SILK;

	// Maracaibo
	Stores[Maracaibo_STORE].Colony = "Maracaibo";
	Stores[Maracaibo_STORE].group  = "Maracaibo";
	Stores[Maracaibo_STORE].StoreSize = "large";
	
	Stores[Maracaibo_STORE].Trade.Export.id1 = GOOD_GOLD;
	Stores[Maracaibo_STORE].Trade.Export.id2 = GOOD_SILVER;
	Stores[Maracaibo_STORE].Trade.Export.id3 = GOOD_MAHOGANY;
	Stores[Maracaibo_STORE].Trade.Export.id4 = GOOD_EBONY;
	Stores[Maracaibo_STORE].Trade.Export.id5 = GOOD_PLANKS;
	Stores[Maracaibo_STORE].Trade.Export.id6 = GOOD_SANDAL;
	Stores[Maracaibo_STORE].Trade.Export.id7 = GOOD_SUGAR;

	Stores[Maracaibo_STORE].Trade.Import.id1 = GOOD_CLOTHES;
	Stores[Maracaibo_STORE].Trade.Import.id2 = GOOD_BRICK;
	Stores[Maracaibo_STORE].Trade.Import.id3 = GOOD_MEDICAMENT;
	Stores[Maracaibo_STORE].Trade.Import.id4 = GOOD_RUM;
	Stores[Maracaibo_STORE].Trade.Import.id5 = GOOD_POWDER;
	Stores[Maracaibo_STORE].Trade.Import.id6 = GOOD_WINE;
	Stores[Maracaibo_STORE].Trade.Import.id7 = GOOD_WHEAT;

	Stores[Maracaibo_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[Maracaibo_STORE].Trade.Contraband.id2 = GOOD_WEAPON;
	Stores[Maracaibo_STORE].Trade.Contraband.id3 = GOOD_FRUITS;
	Stores[Maracaibo_STORE].Trade.Contraband.id4 = GOOD_COTTON;
	Stores[Maracaibo_STORE].Trade.Contraband.id5 = GOOD_LEATHER;

	// Caracas
	Stores[Caracas_STORE].Colony	= "Caracas";
	Stores[Caracas_STORE].group		= "Caracas";
	Stores[Caracas_STORE].StoreSize = "large";
	
	Stores[Caracas_STORE].Trade.Export.id1 = GOOD_COFFEE;
	Stores[Caracas_STORE].Trade.Export.id2 = GOOD_COTTON;
	Stores[Caracas_STORE].Trade.Export.id3 = GOOD_CLOTHES;
	Stores[Caracas_STORE].Trade.Export.id4 = GOOD_SUGAR;
	Stores[Caracas_STORE].Trade.Export.id5 = GOOD_COPRA;
	Stores[Caracas_STORE].Trade.Export.id6 = GOOD_ALE;
	Stores[Caracas_STORE].Trade.Export.id7 = GOOD_PLANKS;

	Stores[Caracas_STORE].Trade.Import.id1 = GOOD_BALLS;
	Stores[Caracas_STORE].Trade.Import.id2 = GOOD_GRAPES;
	Stores[Caracas_STORE].Trade.Import.id3 = GOOD_KNIPPELS;
	Stores[Caracas_STORE].Trade.Import.id4 = GOOD_BOMBS;
	Stores[Caracas_STORE].Trade.Import.id5 = GOOD_POWDER;
	Stores[Caracas_STORE].Trade.Import.id6 = GOOD_MEDICAMENT;
	Stores[Caracas_STORE].Trade.Import.id7 = GOOD_WEAPON;

	Stores[Caracas_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[Caracas_STORE].Trade.Contraband.id2 = GOOD_LEATHER;
	Stores[Caracas_STORE].Trade.Contraband.id3 = GOOD_WINE;
	Stores[Caracas_STORE].Trade.Contraband.id4 = GOOD_RUM;
	Stores[Caracas_STORE].Trade.Contraband.id5 = GOOD_TOBACCO;

	// Cumana
	Stores[Cumana_STORE].Colony = "Cumana";
	Stores[Cumana_STORE].group  = "Cumana";
	Stores[Cumana_STORE].StoreSize = "large";
	
	Stores[Cumana_STORE].Trade.Export.id1 = GOOD_SAILCLOTH;
	Stores[Cumana_STORE].Trade.Export.id2 = GOOD_WHEAT;
	Stores[Cumana_STORE].Trade.Export.id3 = GOOD_LINEN;
	Stores[Cumana_STORE].Trade.Export.id4 = GOOD_SANDAL;
	Stores[Cumana_STORE].Trade.Export.id5 = GOOD_EBONY;
	Stores[Cumana_STORE].Trade.Export.id6 = GOOD_OIL;
	Stores[Cumana_STORE].Trade.Export.id7 = GOOD_COFFEE;

	Stores[Cumana_STORE].Trade.Import.id1 = GOOD_PLANKS;
	Stores[Cumana_STORE].Trade.Import.id2 = GOOD_WINE;
	Stores[Cumana_STORE].Trade.Import.id3 = GOOD_RUM;
	Stores[Cumana_STORE].Trade.Import.id4 = GOOD_CHOCOLATE;
	Stores[Cumana_STORE].Trade.Import.id5 = GOOD_PAPRIKA;
	Stores[Cumana_STORE].Trade.Import.id6 = GOOD_POWDER;
	Stores[Cumana_STORE].Trade.Import.id7 = GOOD_COTTON;

	Stores[Cumana_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[Cumana_STORE].Trade.Contraband.id2 = GOOD_CINNAMON;
	Stores[Cumana_STORE].Trade.Contraband.id3 = GOOD_MEDICAMENT;
	Stores[Cumana_STORE].Trade.Contraband.id4 = GOOD_SILK;
	Stores[Cumana_STORE].Trade.Contraband.id5 = GOOD_FRUITS;

	// SantaCatalina
	Stores[SantaCatalina_STORE].Colony = "SantaCatalina";
	Stores[SantaCatalina_STORE].group  = "SantaCatalina";
	Stores[SantaCatalina_STORE].StoreSize = "large";
	
	Stores[SantaCatalina_STORE].Trade.Export.id1 = GOOD_BALLS;
	Stores[SantaCatalina_STORE].Trade.Export.id2 = GOOD_GRAPES;
	Stores[SantaCatalina_STORE].Trade.Export.id3 = GOOD_KNIPPELS;
	Stores[SantaCatalina_STORE].Trade.Export.id4 = GOOD_BOMBS;
	Stores[SantaCatalina_STORE].Trade.Export.id5 = GOOD_POWDER;
	Stores[SantaCatalina_STORE].Trade.Export.id6 = GOOD_WINE;
	Stores[SantaCatalina_STORE].Trade.Export.id7 = GOOD_WEAPON;

	Stores[SantaCatalina_STORE].Trade.Import.id1 = GOOD_SILK;
	Stores[SantaCatalina_STORE].Trade.Import.id2 = GOOD_COTTON;
	Stores[SantaCatalina_STORE].Trade.Import.id3 = GOOD_SAILCLOTH;
	Stores[SantaCatalina_STORE].Trade.Import.id4 = GOOD_CLOTHES;
	Stores[SantaCatalina_STORE].Trade.Import.id5 = GOOD_TOBACCO;
	Stores[SantaCatalina_STORE].Trade.Import.id6 = GOOD_MAHOGANY;
	Stores[SantaCatalina_STORE].Trade.Import.id7 = GOOD_BRICK;

	Stores[SantaCatalina_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[SantaCatalina_STORE].Trade.Contraband.id2 = GOOD_COPRA;
	Stores[SantaCatalina_STORE].Trade.Contraband.id3 = GOOD_PAPRIKA;
	Stores[SantaCatalina_STORE].Trade.Contraband.id4 = GOOD_SANDAL;
	Stores[SantaCatalina_STORE].Trade.Contraband.id5 = GOOD_LEATHER;
	
	// Beliz
	Stores[Beliz_STORE].Colony = "Beliz";
	Stores[Beliz_STORE].group  = "Beliz";
	Stores[Beliz_STORE].StoreSize = "large";
	
	Stores[Beliz_STORE].Trade.Export.id1 = GOOD_PLANKS;
	Stores[Beliz_STORE].Trade.Export.id2 = GOOD_EBONY;
	Stores[Beliz_STORE].Trade.Export.id3 = GOOD_CINNAMON;
	Stores[Beliz_STORE].Trade.Export.id4 = GOOD_WINE;
	Stores[Beliz_STORE].Trade.Export.id5 = GOOD_RUM;
	Stores[Beliz_STORE].Trade.Export.id6 = GOOD_WHEAT;
	Stores[Beliz_STORE].Trade.Export.id7 = GOOD_COTTON;

	Stores[Beliz_STORE].Trade.Import.id1 = GOOD_SILVER;
	Stores[Beliz_STORE].Trade.Import.id2 = GOOD_WEAPON;
	Stores[Beliz_STORE].Trade.Import.id3 = GOOD_GOLD;
	Stores[Beliz_STORE].Trade.Import.id4 = GOOD_PAPRIKA;
	Stores[Beliz_STORE].Trade.Import.id5 = GOOD_TOBACCO;
	Stores[Beliz_STORE].Trade.Import.id6 = GOOD_LINEN;
	Stores[Beliz_STORE].Trade.Import.id7 = GOOD_CHOCOLATE;

	Stores[Beliz_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[Beliz_STORE].Trade.Contraband.id2 = GOOD_OIL;
	Stores[Beliz_STORE].Trade.Contraband.id3 = GOOD_SAILCLOTH;
	Stores[Beliz_STORE].Trade.Contraband.id4 = GOOD_COFFEE;
	Stores[Beliz_STORE].Trade.Contraband.id5 = GOOD_LEATHER;
	
	// Providence
	Stores[Providencia_STORE].Colony	= "Providencia";
	Stores[Providencia_STORE].group		= "Providencia";
	Stores[Providencia_STORE].StoreSize = "medium";
	
	Stores[Providencia_STORE].Trade.Import.id1 = GOOD_BRICK;
	Stores[Providencia_STORE].Trade.Import.id2 = GOOD_POWDER;
	Stores[Providencia_STORE].Trade.Import.id3 = GOOD_RUM;
	Stores[Providencia_STORE].Trade.Import.id4 = GOOD_PLANKS;
	Stores[Providencia_STORE].Trade.Import.id5 = GOOD_MEDICAMENT;
		
	Stores[Providencia_STORE].Trade.Export.id1 = GOOD_SLAVES;
	Stores[Providencia_STORE].Trade.Export.id2 = GOOD_WEAPON;
	Stores[Providencia_STORE].Trade.Export.id3 = GOOD_GOLD;
	Stores[Providencia_STORE].Trade.Export.id4 = GOOD_TOBACCO;

	// Gibraltar
	Stores[Gibraltar_STORE].Colony = "Gibraltar";
	Stores[Gibraltar_STORE].group  = "Gibraltar";
	Stores[Gibraltar_STORE].StoreSize = "medium";

	Stores[Gibraltar_STORE].Trade.Export.id1 = GOOD_GOLD;
	Stores[Gibraltar_STORE].Trade.Export.id2 = GOOD_SILVER;
	Stores[Gibraltar_STORE].Trade.Export.id3 = GOOD_MAHOGANY;
	Stores[Gibraltar_STORE].Trade.Export.id4 = GOOD_EBONY;
	Stores[Gibraltar_STORE].Trade.Export.id5 = GOOD_PLANKS;
	Stores[Gibraltar_STORE].Trade.Export.id6 = GOOD_SANDAL;
	Stores[Gibraltar_STORE].Trade.Export.id7 = GOOD_SUGAR;

	Stores[Gibraltar_STORE].Trade.Import.id1 = GOOD_CLOTHES;
	Stores[Gibraltar_STORE].Trade.Import.id2 = GOOD_BRICK;
	Stores[Gibraltar_STORE].Trade.Import.id3 = GOOD_MEDICAMENT;
	Stores[Gibraltar_STORE].Trade.Import.id4 = GOOD_RUM;
	Stores[Gibraltar_STORE].Trade.Import.id5 = GOOD_POWDER;
	Stores[Gibraltar_STORE].Trade.Import.id6 = GOOD_WINE;
	Stores[Gibraltar_STORE].Trade.Import.id7 = GOOD_WHEAT;

	Stores[Gibraltar_STORE].Trade.Contraband.id1 = GOOD_SLAVES;
	Stores[Gibraltar_STORE].Trade.Contraband.id2 = GOOD_WEAPON;
	Stores[Gibraltar_STORE].Trade.Contraband.id3 = GOOD_FRUITS;
	Stores[Gibraltar_STORE].Trade.Contraband.id4 = GOOD_COTTON;
	Stores[Gibraltar_STORE].Trade.Contraband.id5 = GOOD_LEATHER;
	
	// Заглушка
	Stores[SHIP_STORE].Colony = "none";
	Stores[SHIP_STORE].group  = "none";
	Stores[SHIP_STORE].StoreSize = "small";
}

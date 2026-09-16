extern void StoreInit();

void InitStores()
{
    int i;

    for(i=0; i<STORE_QUANTITY; i++)
    {
		stores[i].index = i;
		// KZ FreeStores > свободные слоты городским добром не наполняем
		if (IsFreeStoreNum(i)) continue;
        StoreVoidFill(&stores[i]);
    }

	if(LoadSegment("store\store_init.c"))
	{
		StoreInit();
		UnloadSegment("store\store_init.c");
	}

   for(i=0; i<STORE_QUANTITY; i++)
   {
       // FreeStores > чистка после StoreInit
       if (IsFreeStoreNum(i))
       {
           FreeStoreClear(i);
           continue;
       }
       FillStoreGoods(&stores[i]);
   }
}

void SetStoresTradeType(int StoreNum,int GoodsNum,int TradeType)
{
	string tmpstr = Goods[GoodsNum].Name;
	Stores[StoreNum].Goods.(tmpstr).TradeType = TradeType;
}

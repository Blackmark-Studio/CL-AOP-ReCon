
void ApplyMigration(ref migrationState)
{
	Locations[FindLocation("Beliz_CaveEntrance_3")].islandIdAreal = "Beliz";
 
	int iObject = FindItem("instrument1");
	if (iObject >= 0)
	{
		Items[iObject].price = 1000;
		Items[iObject].ItemType = "VARIETY";
	}

	aref arQuest; makearef(arQuest, pchar.questinfo.PDM_Cursed_Idol);
	if (CheckQuestRecordEx(&arQuest, "11", "PDM_Cursed_Idol"))
		RemoveLandQuestMark_Main(characterFromID("Tortuga_usurer"), "PDM_Cursed_Idol");

	iObject = FindLocation("Bridgetown_Plantation_Sp2");
	if (iObject >= 0)
		Locations[iObject].locators_radius.randitem.randitem1 = 1.1;

	if (CheckAttribute(pchar, "QuestInfo.ShipyardsMap") && CheckAttrValue(pchar, "questTemp.different.ShipyardsMap", "toClient") && !CheckCharacterItem(pchar, "ShipyardsMap") && GetCharacterIndex(pchar.questTemp.different.ShipyardsMap.Id) >= 0)
	{
		ref rChar = characterFromId(pchar.questTemp.different.ShipyardsMap.Id);
		AddQuestRecord("ShipyardsMap", "3");
		AddQuestUserData("ShipyardsMap", "sSex", GetSexPhrase("", "а"));
		AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + rChar.city + "Gen"));
		CloseQuestHeader("ShipyardsMap");
		DeleteAttribute(pchar, "questTemp.different.ShipyardsMap");
	}
}

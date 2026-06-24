
void ApplyMigration(ref migrationState)
{
	int iTemp;

	iTemp = FindLocation("CommonHut");
	if (iTemp >= 0)
	{
		Locations[iTemp].image = "loading\inside\hut1.tga";
		Trace("CommonHut" + " " + "loading fix applied");
	}
	iTemp = FindLocation("Vil_Hut");
	if (iTemp >= 0)
	{
		Locations[iTemp].image = "loading\inside\hut1.tga";
		Trace("Vil_Hut" + " " + "loading fix applied");
	}
	iTemp = FindLocation("FortFrance_HouseHut");
	if (iTemp >= 0)
	{
		Locations[iTemp].image = "loading\inside\hut1.tga";
		Trace("FortFrance_HouseHut" + " " + "loading fix applied");
	}
	iTemp = FindLocation("Providencia_HouseHut");
	if (iTemp >= 0)
	{
		Locations[iTemp].image = "loading\inside\hut1.tga";
		Trace("Providencia_HouseHut" + " " + "loading fix applied");
	}

	Trace("Migration LoadingImageFixes successfuly applied");
}

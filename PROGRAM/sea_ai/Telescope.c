void Telescope_Request()
{
	int nTelescopeIn = GetEventData();
	if (GetCharacterEquipByGroup(pchar, SPYGLASS_ITEM_TYPE) == "")
		return;
	if (SeaCameras.Camera == SEA_CAMERA_DECK || SeaCameras.Camera == SEA_CAMERA_FIRE)
		SendMessage(&objISpyGlass, "ll", MSG_TELESCOPE_REQUEST, !nTelescopeIn);
	else
		SendMessage(&objISpyGlass, "ll", MSG_TELESCOPE_REQUEST, 0);
}

void Telescope_Off()
{
	SendMessage(&objISpyGlass, "ll", MSG_TELESCOPE_REQUEST, 0);
}

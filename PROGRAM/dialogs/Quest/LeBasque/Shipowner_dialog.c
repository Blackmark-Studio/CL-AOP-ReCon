void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "First time":
			if (!CheckAttribute(npchar, "AoP.BuccaneerShipownerTalked"))
			{
				npchar.AoP.BuccaneerShipownerTalked = true;
				dialog.text = StringFromKey("Shipowner_dialog_1");
			}
			else
			{
				dialog.text = StringFromKey("Shipowner_dialog_2");
			}

			link.l1 = StringFromKey("Shipowner_dialog_3");
			link.l1.go = "ShipStock";

			if (sti(pchar.Ship.Type) != SHIP_NOTUSED)
			{
				link.l2 = StringFromKey("Shipowner_dialog_4");
				link.l2.go = "ShipRepair";
				link.l3 = StringFromKey("Shipowner_dialog_5");
				link.l3.go = "exit";
			}
			else
			{
				link.l2 = StringFromKey("Shipowner_dialog_5");
				link.l2.go = "exit";
			}
		break;

		case "ShipStock":
			NextDiag.CurrentNode = "First time";
			NextDiag.TempNode = "First time";
			DialogExit();
			LaunchPortman(npchar);
		break;

		case "ShipRepair":
			NextDiag.CurrentNode = "First time";
			NextDiag.TempNode = "First time";
			DialogExit();
			LaunchShipRepair(npchar);
		break;

		case "exit":
			NextDiag.CurrentNode = "First time";
			NextDiag.TempNode = "First time";
			DialogExit();
		break;
	}
}

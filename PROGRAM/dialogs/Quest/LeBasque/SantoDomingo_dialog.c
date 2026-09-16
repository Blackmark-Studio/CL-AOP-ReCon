void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int iTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "First Time":
			NextDiag.TempNode = "First Time";

			// ГГ в форме испанского офицера
			if (pchar.model == "off_spa_7")
			{
				iTemp = rand(4);

				switch (iTemp)
				{
					case 0:
						dialog.text = StringFromKey("SantoDomingo_dialog_1");
						link.l1 = StringFromKey("SantoDomingo_dialog_2");
						link.l1.go = "exit";
					break;

					case 1:
						dialog.text = StringFromKey("SantoDomingo_dialog_3");
						link.l1 = StringFromKey("SantoDomingo_dialog_4");
						link.l1.go = "exit";
					break;

					case 2:
						dialog.text = StringFromKey("SantoDomingo_dialog_5");
						link.l1 = StringFromKey("SantoDomingo_dialog_6");
						link.l1.go = "exit";
					break;

					case 3:
						dialog.text = StringFromKey("SantoDomingo_dialog_7");
						link.l1 = StringFromKey("SantoDomingo_dialog_8");
						link.l1.go = "exit";
					break;

					case 4:
						dialog.text = StringFromKey("SantoDomingo_dialog_9");
						link.l1 = StringFromKey("SantoDomingo_dialog_10");
						link.l1.go = "exit";
					break;
				}
			}
			else
			{
				// ГГ в форме испанского солдата sold_spa_8
				iTemp = rand(4);

				switch (iTemp)
				{
					case 0:
						dialog.text = StringFromKey("SantoDomingo_dialog_11");
						link.l1 = StringFromKey("SantoDomingo_dialog_12");
						link.l1.go = "exit";
					break;

					case 1:
						dialog.text = StringFromKey("SantoDomingo_dialog_13");
						link.l1 = StringFromKey("SantoDomingo_dialog_14");
						link.l1.go = "exit";
					break;

					case 2:
						dialog.text = StringFromKey("SantoDomingo_dialog_15");
						link.l1 = StringFromKey("SantoDomingo_dialog_16");
						link.l1.go = "exit";
					break;

					case 3:
						dialog.text = StringFromKey("SantoDomingo_dialog_17");
						link.l1 = StringFromKey("SantoDomingo_dialog_18");
						link.l1.go = "exit";
					break;

					case 4:
						dialog.text = StringFromKey("SantoDomingo_dialog_19");
						link.l1 = StringFromKey("SantoDomingo_dialog_20");
						link.l1.go = "exit";
					break;
				}
			}
		break;

		case "exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
	}
}
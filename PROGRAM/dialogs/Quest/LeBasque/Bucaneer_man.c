void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
        case "Buccaneer_Random_Start":
            if (CheckAttribute(pchar, "questTemp.AoP.Holiday"))
            {
                dialog.text = StringFromKey("Bucaneer_man_1");
                link.l1 = StringFromKey("Bucaneer_man_2");
                link.l1.go = "Men_Holiday";
            }
            else
            {
                int randomPhrase = rand(4);
                switch (randomPhrase)
                {
                    case 0: dialog.text = StringFromKey("Bucaneer_man_3"); break;
                    case 1: dialog.text = StringFromKey("Bucaneer_man_4"); break;
                    case 2: dialog.text = StringFromKey("Bucaneer_man_5"); break;
                    case 3: dialog.text = StringFromKey("Bucaneer_man_6"); break;
                    case 4: dialog.text = StringFromKey("Bucaneer_man_7"); break;
                }
                link.l1 = StringFromKey("Bucaneer_man_8");
                link.l1.go = "exit";
                link.l2 = StringFromKey("Bucaneer_man_9");
                link.l2.go = "exit";
            }
            NextDiag.TempNode = "Buccaneer_Random_Start";
        break;

        case "Men_Holiday":
            int holidayPhrase = rand(2);
            switch (holidayPhrase)
            {
                case 0:
                    dialog.text = StringFromKey("Bucaneer_man_10");
                    break;
                case 1:
                    dialog.text = StringFromKey("Bucaneer_man_11");
                    break;
                case 2:
                    dialog.text = StringFromKey("Bucaneer_man_12");
                    break;
            }
            
            link.l1 = StringFromKey("Bucaneer_man_13");
            link.l1.go = "exit";
            link.l2 = StringFromKey("Bucaneer_man_14");
            link.l2.go = "exit";
            NextDiag.TempNode = "Buccaneer_Random_Start";
        break;

        case "Standard":
            int standardPhrase = rand(4);
            switch (standardPhrase)
            {
                case 0:
                    dialog.text = StringFromKey("Bucaneer_man_15");
                    break;
                case 1:
                    dialog.text = StringFromKey("Bucaneer_man_16");
                    break;
                case 2:
                    dialog.text = StringFromKey("Bucaneer_man_17");
                    break;
                case 3:
                    dialog.text = StringFromKey("Bucaneer_man_18");
                    break;
                case 4:
                    dialog.text = StringFromKey("Bucaneer_man_19");
                    break;
            }
            
            link.l1 = StringFromKey("Bucaneer_man_20");
            link.l1.go = "exit";
            link.l2 = StringFromKey("Bucaneer_man_21");
            link.l2.go = "exit";
            NextDiag.TempNode = "Buccaneer_Random_Start";
        break;

        case "exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
    }
}
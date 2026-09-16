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
        case "First time":
            if (CheckAttribute(pchar, "questTemp.AoP.Holiday")) 
            {
                dialog.text = StringFromKey("Bucaneer_woman_1");
                link.l1 = StringFromKey("Bucaneer_woman_2");
                link.l1.go = "Girls_Holiday";
            }
            else
            {
                dialog.text = StringFromKey("Bucaneer_woman_3");
                link.l1 = StringFromKey("Bucaneer_woman_4");
                link.l1.go = "Standard"; 
            }
        break;

        case "Girls_Holiday":
            int holidayPhrase = rand(2);
            switch (holidayPhrase)
            {
                case 0:
                    dialog.text = StringFromKey("Bucaneer_woman_5");
                    break;
                case 1:
                    dialog.text = StringFromKey("Bucaneer_woman_6");
                    break;
                case 2:
                    dialog.text = StringFromKey("Bucaneer_woman_7");
                    break;
            }
            
            link.l1 = StringFromKey("Bucaneer_woman_8");
            link.l1.go = "exit";
            link.l2 = StringFromKey("Bucaneer_woman_9");
            link.l2.go = "exit";
            NextDiag.TempNode = "First time";
        break;

        case "Standard":
            int standardPhrase = rand(2);
            switch (standardPhrase)
            {
                case 0:
                    dialog.text = StringFromKey("Bucaneer_woman_10");
                    break;
                case 1:
                    dialog.text = StringFromKey("Bucaneer_woman_11");
                    break;
                case 2:
                    dialog.text = StringFromKey("Bucaneer_woman_12");
                    break;
            }
            
            link.l1 = StringFromKey("Bucaneer_woman_13");
            link.l1.go = "exit";
            link.l2 = StringFromKey("Bucaneer_woman_14");
            link.l2.go = "exit";
            NextDiag.TempNode = "First time";
        break;

        case "exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
    }
}
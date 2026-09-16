void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = StringFromKey("ArubaIndian_dialog_1");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "IndianMan":
			NextDiag.TempNode = "IndianMan";
			dialog.text = NPCStringReactionRepeat(GetSexPhrase(StringFromKey("ArubaIndian_dialog_2_m"), StringFromKey("ArubaIndian_dialog_2_f")),
				GetSexPhrase(StringFromKey("ArubaIndian_dialog_3_m"), StringFromKey("ArubaIndian_dialog_3_f")),
				GetSexPhrase(StringFromKey("ArubaIndian_dialog_4_m"), StringFromKey("ArubaIndian_dialog_4_f")),
				GetSexPhrase(StringFromKey("ArubaIndian_dialog_5_m"), StringFromKey("ArubaIndian_dialog_5_f")), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(StringFromKey("ArubaIndian_dialog_6"),
				StringFromKey("ArubaIndian_dialog_7"),
				StringFromKey("ArubaIndian_dialog_8"),
				GetSexPhrase(StringFromKey("ArubaIndian_dialog_9_m"), StringFromKey("ArubaIndian_dialog_9_f")), npchar, Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;

		case "IndPearlMan_1":
			dialog.text = GetSexPhrase(StringFromKey("ArubaIndian_dialog_10_m"), StringFromKey("ArubaIndian_dialog_10_f"));
			link.l1 = GetSexPhrase(StringFromKey("ArubaIndian_dialog_11_m"), StringFromKey("ArubaIndian_dialog_11_f"));
			link.l1.go = "exit";
		break;

		case "IndianWoman":
			NextDiag.TempNode = "IndianWoman";
			dialog.text = NPCStringReactionRepeat(GetSexPhrase(StringFromKey("ArubaIndian_dialog_12_m"), StringFromKey("ArubaIndian_dialog_12_f")),
				StringFromKey("ArubaIndian_dialog_13"),
				GetSexPhrase(StringFromKey("ArubaIndian_dialog_14_m"), StringFromKey("ArubaIndian_dialog_14_f")),
				GetSexPhrase(StringFromKey("ArubaIndian_dialog_15_m"), StringFromKey("ArubaIndian_dialog_15_f")), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(StringFromKey("ArubaIndian_dialog_6"),
				StringFromKey("ArubaIndian_dialog_7"),
				StringFromKey("ArubaIndian_dialog_8"),
				GetSexPhrase(StringFromKey("ArubaIndian_dialog_9_m"), StringFromKey("ArubaIndian_dialog_9_f")), npchar, Dialog.CurrentNode);
			link.l1.go = "IndianWoman_1";
		break;

		case "IndianWoman_1":
			dialog.text = LinkRandPhrase(GetSexPhrase(StringFromKey("ArubaIndian_dialog_16_m", npchar.name), StringFromKey("ArubaIndian_dialog_16_f", npchar.name)), GetSexPhrase(StringFromKey("ArubaIndian_dialog_17_m", npchar.name), StringFromKey("ArubaIndian_dialog_17_f", npchar.name)), GetSexPhrase(StringFromKey("ArubaIndian_dialog_18_m"), StringFromKey("ArubaIndian_dialog_18_f")));
			link.l1 = GetSexPhrase(StringFromKey("ArubaIndian_dialog_19_m"), StringFromKey("ArubaIndian_dialog_19_f"));
			link.l1.go = "exit";
		break;

		case "CitizenNotBlade":
			dialog.text = StringFromKey("ArubaIndian_dialog_20");
			link.l1 = LinkRandPhrase(StringFromKey("ArubaIndian_dialog_21"), StringFromKey("ArubaIndian_dialog_22"), StringFromKey("ArubaIndian_dialog_23"));
			link.l1.go = "exit";
		break;
	}
}

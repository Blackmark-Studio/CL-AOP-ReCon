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
	if (!CheckAttribute(npchar, "RimalierFriendMet"))
	{
		dialog.text = StringFromKey("Tavernkeeper_dialog_1", pchar.lastname);
		link.l1 = StringFromKey("Tavernkeeper_dialog_2");
		link.l1.go = "RimalierFriend_1";
	}
	else
	{
		dialog.text = StringFromKey("Tavernkeeper_dialog_6", LinkRandPhrase(
	StringFromKey("Tavernkeeper_dialog_3", pchar.lastname),
	StringFromKey("Tavernkeeper_dialog_4", pchar.lastname),
	StringFromKey("Tavernkeeper_dialog_5", pchar.lastname)));
		link.l1 = StringFromKey("Tavernkeeper_dialog_7");
		link.l1.go = "HireCrew";
		link.l2 = StringFromKey("Tavernkeeper_dialog_8");
		link.l2.go = "Exit";
	}
break;

case "RimalierFriend_1":
	dialog.text = StringFromKey("Tavernkeeper_dialog_9");
	link.l1 = StringFromKey("Tavernkeeper_dialog_10");
	link.l1.go = "RimalierFriend_2";
break;

case "RimalierFriend_2":
	dialog.text = StringFromKey("Tavernkeeper_dialog_11");
	link.l1 = StringFromKey("Tavernkeeper_dialog_12");
	link.l1.go = "HireCrew_First";
	link.l2 = StringFromKey("Tavernkeeper_dialog_13");
	link.l2.go = "RimalierFriend_Exit";
break;

case "HireCrew_First":
	npchar.RimalierFriendMet = true;
	DialogExit();
	LaunchBuccaneerHireCrew(npchar);
break;

case "RimalierFriend_Exit":
	npchar.RimalierFriendMet = true;
	NextDiag.CurrentNode = "First time";
	DialogExit();
break;

case "HireCrew":
	DialogExit();
	LaunchBuccaneerHireCrew(npchar);
break;

case "Exit":
	NextDiag.CurrentNode = "First time";
	DialogExit();
break;

	}
}
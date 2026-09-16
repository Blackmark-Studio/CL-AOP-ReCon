
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			if(!CheckAttrValue(npchar, "quest.Meeting", LastSpeakDate()))
			{
				dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_54");
				npchar.quest.Meeting = LastSpeakDate();
			}
			else
			{
				dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_55", GetAddress_Form(NPChar));
			}
			Link.l2 = StringFromKey("Common_Portman_55");
			link.l2.go = "quests";
			Link.l9 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_56");
			link.l9.go = "exit";
		break;
		
		case "quests":
			dialog.text = StringFromKey("SantoDomingo_PortMan_2", GetAddress_Form(NPChar)); 
			// Эммануэль Пардаль -->
			if (CheckAttrValue(pchar, "questTemp.EPL_DOSD", "Admiralty"))
			{
				Link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_50", pchar.name, FindPersonalName("Remedios_lastname"));
				link.l1.go = "EPL_DOSD_Pochta1";
			}
			// Эммануэль Пардаль <--
			Link.l9 = StringFromKey("SantoDomingo_PortMan_7" + GetSexPhrase("_m", "_f"));
			link.l9.go = "exit";
		break;
		
		// Эммануэль Пардаль -->
		case "EPL_DOSD_Pochta1":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_51", FindPersonalName("Remedios_lastname"));
			Link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_52");
			link.l1.go = "EPL_DOSD_Pochta2";
			RemoveLandQuestmark_Main(npchar, "EPL_Prologue");
		break;
		
		case "EPL_DOSD_Pochta2":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_53");
			Link.l1 = StringFromKey("Common_citizen_232");
			link.l1.go = "exit";
			pchar.questTemp.EPL_DOSD = "Admiralty_Hover";
			
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("SantoDomingo_Mayor"), -1));
			sld.id = "SantoDomingo_Mayor_Clone";
			sld.greeting = "";
			sld.Dialog.Filename = "Quest\EmmanuelPardalLine\EPL_2_DefenseOfSantoDomingo_dialog.c";
			sld.dialog.currentnode = "EPL_DOSD_Gubernator_1";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld,"SantoDomingo_Admiralty","quest","quest4");
			AddLandQuestMark_Main(sld, "EPL_Prologue");
			
			sld = GetCharacter(NPC_GenerateCharacter("EPL_DOSD_Off_Guber_1", "off_spa_1", "man", "man", 30, SPAIN, -1, false));
			LAi_SetActorType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld,"SantoDomingo_Admiralty","quest","quest8");
			
			sld = GetCharacter(NPC_GenerateCharacter("EPL_DOSD_Off_Guber_2", "off_spa_2", "man", "man", 30, SPAIN, -1, false));
			LAi_SetActorType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld,"SantoDomingo_Admiralty","quest","quest2");
		break;
		// Эммануэль Пардаль <--
	}
}

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
		dialog.text = StringFromKey("Marso_dialog_73", pchar);
		link.l1 = StringFromKey("Marso_dialog_74");
		link.l1.go = "dialog_1";
	break;

	case "dialog_1":
		dialog.text = StringFromKey("Marso_dialog_75");
		link.l1 = StringFromKey("Marso_dialog_76");
		link.l1.go = "dialog_2";
	break;

	case "dialog_2":
		dialog.text = StringFromKey("Marso_dialog_77");
		link.l1 = StringFromKey("Marso_dialog_78");
		link.l1.go = "dialog_3";
	break;

	case "dialog_3":
		dialog.text = StringFromKey("Marso_dialog_79");
		link.l1 = StringFromKey("Marso_dialog_80");
		link.l1.go = "dialog_4";
	break;

	case "dialog_4":
		dialog.text = StringFromKey("Marso_dialog_81");
		link.l1 = "...";
		link.l1.go = "dialog_5_exit";
	break;

	case "dialog_5_exit":
		AddDialogExitQuest("Shadow_of_a_big_deal_5");
		dialogexit();
	break;

	case "dialog_6":
		dialog.text = StringFromKey("Marso_dialog_82", pchar);
		link.l1 = StringFromKey("Marso_dialog_83");
		link.l1.go = "dialog_7";
	break;

	case "dialog_7":
		dialog.text = StringFromKey("Marso_dialog_84", pchar);
		link.l1 = StringFromKey("Marso_dialog_85");
		link.l1.go = "dialog_8";
	break;

	case "dialog_8":
		dialog.text = StringFromKey("Marso_dialog_86");
		link.l1 = StringFromKey("Marso_dialog_87");
		link.l1.go = "dialog_9";
	break;

	case "dialog_9":
		dialog.text = StringFromKey("Marso_dialog_88");
		link.l1 = "...";
		link.l1.go = "dialog_10";
	break;

	case "dialog_10":
		dialog.text = StringFromKey("Marso_dialog_89", pchar);
		link.l1 = StringFromKey("Marso_dialog_90");
		link.l1.go = "dialog_11";
	break;

	case "dialog_11":
		dialog.text = StringFromKey("Marso_dialog_91");
		link.l1 = StringFromKey("Marso_dialog_92");
		link.l1.go = "dialog_11_exit";
	break;

	case "dialog_11_exit":
		AddDialogExitQuest("Shadow_of_a_big_deal_8");
		dialogexit();
	break;

	case "dialog_21":
		dialog.text = StringFromKey("Marso_dialog_93");
		link.l1 = StringFromKey("Marso_dialog_94");
		link.l1.go = "dialog_22";
	break;

	case "dialog_22":
		dialog.text = StringFromKey("Marso_dialog_95");
		link.l1 = StringFromKey("Marso_dialog_96");
		link.l1.go = "dialog_23";
	break;

	case "dialog_23":
		dialog.text = StringFromKey("Marso_dialog_97");
		link.l1 = StringFromKey("Marso_dialog_98");
		link.l1.go = "dialog_24";
	break;

	case "dialog_24":
		dialog.text = StringFromKey("Marso_dialog_99");
		link.l1 = StringFromKey("Marso_dialog_100");
		link.l1.go = "dialog_25";
	break;

	case "dialog_25":
		dialog.text = StringFromKey("Marso_dialog_101");
		link.l1 = StringFromKey("Marso_dialog_102");
		link.l1.go = "dialog_26";
	break;

	case "dialog_26":
		dialog.text = StringFromKey("Marso_dialog_103");
		link.l1 = StringFromKey("Marso_dialog_104");
		link.l1.go = "dialog_27";
	break;

	case "dialog_27":
		dialog.text = StringFromKey("Marso_dialog_105");
		link.l1 = StringFromKey("Marso_dialog_106");
		link.l1.go = "dialog_27_wait_2";
		link.l2 = StringFromKey("Marso_dialog_107");
		link.l2.go = "dialog_27_wait";
	break;

	case "dialog_27_wait":
		dialog.text = StringFromKey("Marso_dialog_108", pchar);
		link.l1 = StringFromKey("Marso_dialog_109");
		link.l1.go = "dialog_27_wait_exit";
	break;

	case "dialog_27_wait_exit":
		sld = characterFromId("Etien_Marso");
		sld.DeckDialogNode = "dialog_27_wait_1";
		NextDiag.CurrentNode = "dialog_27_wait_1";
		dialogexit();
	break;

	case "dialog_27_wait_1":
		dialog.text = StringFromKey("Marso_dialog_110", pchar);
		link.l1 = StringFromKey("Marso_dialog_111");
		link.l1.go = "dialog_27_wait_2";
		link.l2 = StringFromKey("Marso_dialog_112");
		link.l2.go = "dialog_27_wait";
	break;

	case "dialog_27_wait_2":
		dialog.text = StringFromKey("Marso_dialog_113");
		link.l1 = StringFromKey("Marso_dialog_114");
		link.l1.go = "dialog_27_exit";
	break;

	case "dialog_27_exit":
		AddDialogExitQuest("Shadow_of_a_big_deal_25");
		dialogexit();
	break;

	case "dialog_29":
		dialog.text = StringFromKey("Marso_dialog_115");
		link.l1 = "...";
		link.l1.go = "dialog_29_exit";
	break;

	case "dialog_29_exit":
		AddDialogExitQuest("Shadow_of_a_big_deal_53_1");
		dialogexit();
	break;

	case "dialog_30":
		dialog.text = StringFromKey("Marso_dialog_116");
		link.l1 = StringFromKey("Marso_dialog_117");
		link.l1.go = "dialog_31";
	break;

	case "dialog_31":
		dialog.text = StringFromKey("Marso_dialog_118");
		link.l1 = StringFromKey("Marso_dialog_119");
		link.l1.go = "dialog_32";
	break;

	case "dialog_32":
		AddMoneyToCharacter(pchar, 10000);
		dialog.text = StringFromKey("Marso_dialog_120");
		link.l1 = StringFromKey("Marso_dialog_121", pchar);
		link.l1.go = "dialog_33";
	break;

	case "dialog_33":
		TakeItemFromCharacter(pchar, "letter_bask");
		dialog.text = StringFromKey("Marso_dialog_122");
		link.l1 = StringFromKey("Marso_dialog_123");
		link.l1.go = "dialog_34_exit";
	break;

	case "dialog_34_exit":
		AddDialogExitQuest("Shadow_of_a_big_deal_55");
		dialogexit();
	break;

// квест №2

	case "Old_campfire_1":
		dialog.text = StringFromKey("Marso_dialog_124");
		link.l1 = StringFromKey("Marso_dialog_125");
		link.l1.go = "Old_campfire_2";
	break;

	case "Old_campfire_2":
		dialog.text = StringFromKey("Marso_dialog_126");
		link.l1 = StringFromKey("Marso_dialog_127");
		link.l1.go = "Old_campfire_3";
	break;

	case "Old_campfire_3":
		dialog.text = StringFromKey("Marso_dialog_128");
		link.l1 = "...";
		link.l1.go = "Old_campfire_5_exit";
	break;

	case "Old_campfire_5_exit":
		AddDialogExitQuest("Old_campfire_1");
		dialogexit();
	break;

	case "Old_campfire_6":
		sld = characterFromID("Etien_Marso");
		LAi_ActorTurnToCharacter(sld, characterFromID("Mishel_le_Bask"));
		dialog.text = StringFromKey("Marso_dialog_129", pchar, GetFullName(pchar));
		link.l1 = "...";
		link.l1.go = "Old_campfire_6_exit";
	break;

	case "Old_campfire_6_exit":
		AddDialogExitQuest("Old_campfire_3");
		dialogexit();
	break;

	case "Old_campfire_7":
		CharacterTurnByChr(npchar, CharacterFromID("Mishel_le_Bask"));
		dialog.text = StringFromKey("Marso_dialog_130");
		link.l1 = "...";
		link.l1.go = "Old_campfire_7_exit";
	break;

	case "Old_campfire_7_exit":
		AddDialogExitQuest("Old_campfire_4_1");
		dialogexit();
	break;

	case "Old_campfire_7_1":
		dialog.text = StringFromKey("Marso_dialog_131");
		link.l1 = StringFromKey("Marso_dialog_132");
		link.l1.go = "Old_campfire_7_1_exit";
	break;

	case "Old_campfire_7_1_exit":
		AddDialogExitQuest("Old_campfire_5");
		dialogexit();
	break;

	case "Old_campfire_8":
		dialog.text = StringFromKey("Marso_dialog_133");
		link.l1 = StringFromKey("Marso_dialog_134");
		link.l1.go = "Old_campfire_8_exit";
	break;

	case "Old_campfire_8_exit":
		AddDialogExitQuest("Old_campfire_7");
		dialogexit();
	break;

	case "Old_campfire_9":
		dialog.text = StringFromKey("Marso_dialog_135");
		link.l1 = StringFromKey("Marso_dialog_136");
		link.l1.go = "Old_campfire_10";
	break;

	case "Old_campfire_10":
		dialog.text = StringFromKey("Marso_dialog_137");
		link.l1 = "...";
		link.l1.go = "Old_campfire_10_exit";
	break;

	case "Old_campfire_10_exit":
		AddDialogExitQuest("Old_campfire_10");
		dialogexit();
	break;

	case "Old_campfire_11":
		dialog.text = StringFromKey("Marso_dialog_138");
		link.l1 = StringFromKey("Marso_dialog_139");
		link.l1.go = "Old_campfire_12";
	break;

	case "Old_campfire_12":
		dialog.text = StringFromKey("Marso_dialog_140");
		link.l1 = StringFromKey("Marso_dialog_141");
		link.l1.go = "Old_campfire_13";
	break;

	case "Old_campfire_13":
		dialog.text = StringFromKey("Marso_dialog_142");
		link.l1 = StringFromKey("Marso_dialog_143");
		link.l1.go = "Old_campfire_13_exit";
	break;

	case "Old_campfire_13_exit":
		AddDialogExitQuest("Old_campfire_12");
		dialogexit();
	break;

	case "Old_campfire_Isabela_Check":
		if (CheckAttribute(pchar, "location.from_sea") && pchar.location.from_sea == "Shore32" && sti(pchar.Ship.Type) != SHIP_NOTUSED)
		{
			dialog.text = StringFromKey("Marso_dialog_144");
			link.l1 = StringFromKey("Marso_dialog_145");
			link.l1.go = "Old_campfire_Isabela_Sea_exit";
		}
		else
		{
			dialog.text = StringFromKey("Marso_dialog_146");
			link.l1 = StringFromKey("Marso_dialog_147", pchar);
			link.l1.go = "Old_campfire_Isabela_Land_exit";
		}
	break;

	case "Old_campfire_Isabela_Land_exit":
		dialogexit();
	break;

	case "Old_campfire_Isabela_Sea_exit":
		AddDialogExitQuest("Old_campfire_15");
		dialogexit();
	break;

	case "Old_campfire_14":
		dialog.text = StringFromKey("Marso_dialog_148");
		link.l1 = StringFromKey("Marso_dialog_149");
		link.l1.go = "Old_campfire_14_exit";
	break;

	case "Old_campfire_14_exit":
		AddDialogExitQuest("Old_campfire_17");
		dialogexit();
	break;

	case "Old_campfire_15":
		sld = characterFromId("Etien_Marso");
		LAi_ActorTurnToCharacter(sld, characterFromID("Rimalier"));
		dialog.text = StringFromKey("Marso_dialog_150");
		link.l1 = "...";
		link.l1.go = "Old_campfire_15_exit";
	break;

	case "Old_campfire_15_exit":
		sld = characterFromID("Rimalier");
		sld.Dialog.CurrentNode = "dialog_4";
		LAi_ActorDialogNow(sld, pchar, "", -1);
		dialogexit();
	break;

	case "Joke_1":
		dialog.text = StringFromKey("Marso_dialog_151");
		link.l1 = StringFromKey("Marso_dialog_152", pchar);
		link.l1.go = "Joke_2_exit";
	break;

	case "Joke_2_exit":
		AddDialogExitQuest("Old_campfire_42_9");
		dialogexit();
	break;

	case "Joke_3":
		dialog.text = StringFromKey("Marso_dialog_153");
		link.l1 = "...";
		link.l1.go = "Joke_3_exit";
	break;

	case "Joke_3_exit":
		sld = characterFromID("Rimalier");
		sld.Dialog.CurrentNode = "Joke_4";
		LAi_ActorDialogNow(sld, pchar, "", -1);
		dialogexit();
	break;

	case "Joke_4":
		dialog.text = StringFromKey("Marso_dialog_154");
		link.l1 = StringFromKey("Marso_dialog_155");
		link.l1.go = "Joke_4_exit";
	break;

	case "Joke_4_exit":
		sld = characterFromID("Rimalier");
		sld.Dialog.CurrentNode = "Joke_4_1";
		LAi_ActorDialogNow(sld, pchar, "", -1);
		dialogexit();
	break;

	case "Old_campfire_16":
		dialog.text = StringFromKey("Marso_dialog_156");
		link.l1 = StringFromKey("Marso_dialog_157");
		link.l1.go = "Old_campfire_17";
	break;

	case "Old_campfire_17":
		dialog.text = StringFromKey("Marso_dialog_158");
		link.l1 = StringFromKey("Marso_dialog_159");
		link.l1.go = "Old_campfire_18";
	break;

	case "Old_campfire_18":
		dialog.text = StringFromKey("Marso_dialog_160");
		link.l1 = StringFromKey("Marso_dialog_161");
		link.l1.go = "Old_campfire_18_exit";
	break;

	case "Old_campfire_18_exit":
		sld = characterFromID("Rimalier");
		ChangeCharacterAddressGroup(sld, "Shore59", "goto", "goto15");
		sld = characterFromID("Young_Boy_Bask");
		ChangeCharacterAddressGroup(sld, "Shore59", "goto", "goto15");
		AddDialogExitQuest("Old_campfire_47");
		dialogexit();
	break;

	case "Old_campfire_18_1":
		dialog.text = StringFromKey("Marso_dialog_162");
		link.l1 = "...";
		link.l1.go = "Old_campfire_18_1_exit";
	break;

	case "Old_campfire_18_1_exit":
		sld = characterFromID("Rimalier");
		sld.Dialog.CurrentNode = "dialog_17";
		LAi_ActorDialogNow(sld, pchar, "", -1);
		dialogexit();
	break;

	case "Old_campfire_19":
		dialog.text = StringFromKey("Marso_dialog_163");
		link.l1 = "...";
		link.l1.go = "Old_campfire_19_exit";
	break;

	case "Old_campfire_19_exit":
		sld = characterFromID("Etien_Marso");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "LeFransua_tavern", "tables", "stay2");
		LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
		sld = characterFromID("Rimalier");
		sld.Dialog.CurrentNode = "dialog_25";
		LAi_ActorDialogNow(sld, pchar, "", -1);
		dialogexit();
	break;

	case "La_Vega_1":
		dialog.text = StringFromKey("Marso_dialog_164");
		link.l1 = StringFromKey("Marso_dialog_165");
		link.l1.go = "La_Vega_1_exit";
	break;

	case "La_Vega_1_exit":
		AddDialogExitQuest("Old_campfire_56");
		dialogexit();
	break;

	case "Old_campfire_20":
		dialog.text = StringFromKey("Marso_dialog_166");
		link.l1 = StringFromKey("Marso_dialog_167");
		link.l1.go = "Old_campfire_21";
	break;

	case "Old_campfire_21":
		dialog.text = StringFromKey("Marso_dialog_168");
		link.l1 = "...";
		link.l1.go = "Old_campfire_22_exit";
	break;

	case "Old_campfire_22_exit":
		AddDialogExitQuest("Old_campfire_56");
		dialogexit();
	break;

	case "Old_campfire_22":
		dialog.text = StringFromKey("Marso_dialog_169");
		link.l1 = "...";
		link.l1.go = "Old_campfire_23";
	break;

	case "Old_campfire_23":
		dialog.text = StringFromKey("Marso_dialog_170", pchar.name);
		link.l1 = "...";
		link.l1.go = "Old_campfire_24";
	break;

	case "Old_campfire_24":
		dialog.text = StringFromKey("Marso_dialog_171");
		link.l1 = StringFromKey("Marso_dialog_172");
		link.l1.go = "Old_campfire_24_exit";
	break;

	case "Old_campfire_24_exit":
		AddDialogExitQuest("Old_campfire_62");
		dialogexit();
	break;

	// Рималье
	case "Old_campfire_25":
		dialog.text = StringFromKey("Marso_dialog_173");
		link.l1 = "...";
		link.l1.go = "Old_campfire_25_exit";
	break;

	case "Old_campfire_25_exit":
		AddDialogExitQuest("Old_campfire_63");
		dialogexit();
	break;

	// Жако
	case "Old_campfire_26":
		dialog.text = StringFromKey("Marso_dialog_174");
		link.l1 = "...";
		link.l1.go = "Old_campfire_26_exit";
	break;

	case "Old_campfire_26_exit":
		AddDialogExitQuest("Old_campfire_64");
		dialogexit();
	break;

	case "Old_campfire_27":
		dialog.text = StringFromKey("Marso_dialog_175");
		link.l1 = "...";
		link.l1.go = "Old_campfire_27_exit";
	break;

	case "Old_campfire_27_exit":
		AddDialogExitQuest("Old_campfire_65");
		dialogexit();
	break;

	case "Old_campfire_28":
		if (sti(pchar.nation) == SPAIN || sti(pchar.nation) == HOLLAND)
		{
			dialog.text = StringFromKey("Marso_dialog_176");
			link.l1 = StringFromKey("Marso_dialog_177");
		}
		else
		{
			dialog.text = StringFromKey("Marso_dialog_178");
			link.l1 = StringFromKey("Marso_dialog_179");
		}
		link.l1.go = "Old_campfire_28_exit";
	break;

	case "Old_campfire_28_exit":
		AddDialogExitQuest("Old_campfire_69");
		dialogexit();
		DoQuestFunctionDelay("MakeQuestAutoSaveDelay", 1.0);
	break;

	case "Old_campfire_33":
		dialog.text = StringFromKey("Marso_dialog_180");
		link.l1 = StringFromKey("Marso_dialog_181");
		link.l1.go = "Old_campfire_33_1";
	break;

	case "Old_campfire_33_1":
		dialog.text = StringFromKey("Marso_dialog_182");
		link.l1 = StringFromKey("Marso_dialog_183");
		link.l1.go = "Old_campfire_33_2";
	break;

	case "Old_campfire_33_2":
		dialog.text = StringFromKey("Marso_dialog_184");
		link.l1 = "...";
		link.l1.go = "Old_campfire_34";
	break;

	case "Old_campfire_34":
		dialog.text = StringFromKey("Marso_dialog_185");
		link.l1 = "...";
		link.l1.go = "Old_campfire_34_exit";
	break;

	case "Old_campfire_34_exit":
		AddDialogExitQuest("Old_campfire_79");
		dialogexit();
	break;

	case "Old_campfire_35":
		dialog.text = StringFromKey("Marso_dialog_186");
		link.l1 = StringFromKey("Marso_dialog_187");
		link.l1.go = "Old_campfire_35_exit";
	break;

	case "Old_campfire_35_exit":
		AddDialogExitQuest("Old_campfire_80_3");
		dialogexit();
	break;

	case "Old_campfire_36":
		dialog.text = StringFromKey("Marso_dialog_188");
		link.l1 = StringFromKey("Marso_dialog_189");
		link.l1.go = "Old_campfire_35_exit";
	break;

	case "Old_campfire_37":
		RemoveLandQuestmark_Main(npchar, "Old_campfire");
		dialog.text = StringFromKey("Marso_dialog_190");
		link.l1 = StringFromKey("Marso_dialog_191");
		link.l1.go = "Old_campfire_38";
	break;

	case "Old_campfire_38":
		dialog.text = StringFromKey("Marso_dialog_192");
		link.l1 = StringFromKey("Marso_dialog_193");
		link.l1.go = "Old_campfire_38_exit";
	break;

	case "Old_campfire_38_exit":
		AddDialogExitQuest("Old_campfire_82");
		dialogexit();
	break;

	case "Old_campfire_39":
		dialog.text = StringFromKey("Marso_dialog_194", pchar.name);
		link.l1 = StringFromKey("Marso_dialog_195");
		link.l1.go = "Old_campfire_40";
	break;

	case "Old_campfire_40":
		dialog.text = StringFromKey("Marso_dialog_196");
		link.l1 = "...";
		link.l1.go = "Old_campfire_41_exit";
	break;

	case "Old_campfire_41_exit":
		AddDialogExitQuest("Old_campfire_85");
		dialogexit();
	break;

	// третий квест
	case "Hunting_huntsman_1":
		dialog.text = StringFromKey("Marso_dialog_197");
		link.l1 = "...";
		link.l1.go = "Hunting_huntsman_1_exit";
	break;

	case "Hunting_huntsman_1_exit":
		AddDialogExitQuest("Hunting_huntsman_3");
		dialogexit();
	break;

	case "Hunting_huntsman_2":
		dialog.text = StringFromKey("Marso_dialog_198");
		link.l1 = StringFromKey("Marso_dialog_199");
		link.l1.go = "Hunting_huntsman_2_exit";
	break;

	case "Hunting_huntsman_2_exit":
		dialogexit();
	break;

	case "Hunting_huntsman_3":
		RemoveLandQuestmark_Main(npchar, "Hunting_huntsman");
		dialog.text = StringFromKey("Marso_dialog_200", pchar.name);
		link.l1 = StringFromKey("Marso_dialog_201");
		link.l1.go = "Hunting_huntsman_4";
	break;

	case "Hunting_huntsman_4":
		dialog.text = StringFromKey("Marso_dialog_202", pchar);
		link.l1 = StringFromKey("Marso_dialog_203");
		link.l1.go = "Hunting_huntsman_4_exit";
	break;

	case "Hunting_huntsman_4_exit":
		AddDialogExitQuest("Hunting_huntsman_20");
		dialogexit();
	break;

	case "Hunting_huntsman_5":
		dialog.text = StringFromKey("Marso_dialog_204");
		link.l1 = StringFromKey("Marso_dialog_205");
		link.l1.go = "Hunting_huntsman_6";
	break;

	case "Hunting_huntsman_6":
		dialog.text = StringFromKey("Marso_dialog_206");
		link.l1 = StringFromKey("Marso_dialog_207");
		link.l1.go = "Hunting_huntsman_6_exit";
	break;

	case "Hunting_huntsman_6_exit":
		AddDialogExitQuest("Hunting_huntsman_24");
		dialogexit();
	break;

	case "Hunting_huntsman_8":
		dialog.text = StringFromKey("Marso_dialog_208", pchar.name);
		link.l1 = StringFromKey("Marso_dialog_209");
		link.l1.go = "Hunting_huntsman_8_Authority";
		link.l2 = StringFromKey("Marso_dialog_210");
		link.l2.go = "Hunting_huntsman_8_Sneak";
	break;

	case "Hunting_huntsman_8_Authority":
		AddCharacterExpToSkill(pchar, "Leadership", 5);
		dialog.text = StringFromKey("Marso_dialog_211");
		link.l1 = StringFromKey("Marso_dialog_212");
		link.l1.go = "Hunting_huntsman_8_exit";
	break;

	case "Hunting_huntsman_8_Sneak":
		AddCharacterExpToSkill(pchar, "Sneak", 5);
		AddDialogExitQuest("Hunting_huntsman_32");
		dialogexit();
	break;

	case "Hunting_huntsman_8_exit":
		AddDialogExitQuest("Hunting_huntsman_32");
		dialogexit();
	break;

	case "Hunting_huntsman_9":
		dialog.text = "...";
		link.l1 = StringFromKey("Marso_dialog_213");
		link.l1.go = "Hunting_huntsman_10";
	break;

	case "Hunting_huntsman_10":
		dialog.text = StringFromKey("Marso_dialog_214");
		sld = CharacterFromID("Rimalier");
		if (IsOfficer(sld))
		{
			link.l1 = StringFromKey("Marso_dialog_215");
			link.l1.go = "Hunting_huntsman_11";
		}
		else
		{
			pchar.questTemp.AoP.RimalierSanJuan = true;
			link.l1 = StringFromKey("Marso_dialog_216");
			link.l1.go = "Hunting_huntsman_11_1";
		}
	break;

	case "Hunting_huntsman_11":
		dialog.text = StringFromKey("Marso_dialog_217");
		link.l1 = "...";
		link.l1.go = "Hunting_huntsman_11_exit";
	break;

	case "Hunting_huntsman_11_1":
		dialog.text = StringFromKey("Marso_dialog_218", pchar);
		link.l1 = "...";
		link.l1.go = "Hunting_huntsman_11_exit";
	break;

	case "Hunting_huntsman_11_exit":
		AddDialogExitQuest("Hunting_huntsman_38");
		dialogexit();
	break;

	case "Hunting_huntsman_12":
		dialog.text = StringFromKey("Marso_dialog_219", pchar.name);
		link.l1 = StringFromKey("Marso_dialog_220");
		link.l1.go = "Hunting_huntsman_13";
	break;

	case "Hunting_huntsman_13":
		dialog.text = StringFromKey("Marso_dialog_221");
		link.l1 = StringFromKey("Marso_dialog_222");
		link.l1.go = "Hunting_huntsman_13_exit";
	break;

	case "Hunting_huntsman_13_exit":
		AddDialogExitQuest("Hunting_huntsman_40");
		dialogexit();
	break;

	case "Hunting_huntsman_14":
		RemoveLandQuestmark_Main(npchar, "Hunting_huntsman");
		dialog.text = StringFromKey("Marso_dialog_223");
		link.l1 = "...";
		link.l1.go = "Hunting_huntsman_14_exit";
	break;

	case "Hunting_huntsman_14_exit":
		AddDialogExitQuest("Hunting_huntsman_43");
		dialogexit();
	break;

	case "Hunting_huntsman_15":
		dialog.text = StringFromKey("Marso_dialog_224");
		link.l1 = StringFromKey("Marso_dialog_225");
		link.l1.go = "Hunting_huntsman_16";
	break;

	case "Hunting_huntsman_16":
		RemoveItems(pchar, "blank", 1);
		dialog.text = StringFromKey("Marso_dialog_226");
		link.l1 = StringFromKey("Marso_dialog_227");
		link.l1.go = "Hunting_huntsman_16_exit";
	break;

	case "Hunting_huntsman_16_exit":
		AddDialogExitQuest("Hunting_huntsman_45");
		dialogexit();
	break;

	case "Hunting_huntsman_17":
		dialog.text = StringFromKey("Marso_dialog_228");
		link.l1 = StringFromKey("Marso_dialog_229");
		link.l1.go = "Hunting_huntsman_18";
	break;

	case "Hunting_huntsman_18":
		dialog.text = StringFromKey("Marso_dialog_230");
		link.l1 = StringFromKey("Marso_dialog_231");
		link.l1.go = "Hunting_huntsman_19";
	break;

	case "Hunting_huntsman_19":
		dialog.text = StringFromKey("Marso_dialog_232");
		link.l1 = StringFromKey("Marso_dialog_233");
		link.l1.go = "Hunting_huntsman_20";
	break;

	case "Hunting_huntsman_20":
		dialog.text = StringFromKey("Marso_dialog_234");
		link.l1 = StringFromKey("Marso_dialog_235");
		link.l1.go = "Hunting_huntsman_21";
	break;

	case "Hunting_huntsman_21":
		dialog.text = StringFromKey("Marso_dialog_236");
		link.l1 = StringFromKey("Marso_dialog_237", pchar);
		link.l1.go = "Hunting_huntsman_22";
	break;

	case "Hunting_huntsman_22":
		GiveItem2Character(pchar, "spa_lager");
		// Проверяем флаг главного героя
		if (sti(pchar.nation) == ENGLAND || sti(pchar.nation) == FRANCE)
		{
			dialog.text = StringFromKey("Marso_dialog_238");
			link.l1 = StringFromKey("Marso_dialog_239", pchar);
			link.l1.go = "Hunting_huntsman_23_exit";
		}
		else
		{
			dialog.text = StringFromKey("Marso_dialog_240");
			link.l1 = StringFromKey("Marso_dialog_241", pchar);
			link.l1.go = "Hunting_huntsman_23_1_exit";
		}
	break;

	case "Hunting_huntsman_23_exit":
		dialogexit();
		AddDialogExitQuest("Hunting_huntsman_74");
	break;

	case "Hunting_huntsman_23_1_exit":
		dialogexit();
		AddDialogExitQuest("Hunting_huntsman_77");
	break;

	case "Hunting_huntsman_24":
		dialog.text = StringFromKey("Marso_dialog_242");
		link.l1 = StringFromKey("Marso_dialog_243");
		link.l1.go = "Hunting_huntsman_25";
	break;

	case "Hunting_huntsman_25":
		dialog.text = StringFromKey("Marso_dialog_244");
		link.l1 = StringFromKey("Marso_dialog_245");
		link.l1.go = "Hunting_huntsman_26";
	break;

	case "Hunting_huntsman_26":
		dialog.text = StringFromKey("Marso_dialog_246");
		link.l1 = StringFromKey("Marso_dialog_247");
		link.l1.go = "Hunting_huntsman_26_exit";
		link.l2 = StringFromKey("Marso_dialog_248");
		link.l2.go = "Hunting_huntsman_26_1_exit";
	break;

	case "Hunting_huntsman_26_exit":
		RemoveLandQuestmark_Main(npchar, "Hunting_huntsman");
		AddDialogExitQuest("Hunting_huntsman_79");
		dialogexit();
	break;

	case "Hunting_huntsman_26_1_exit":
		NextDiag.CurrentNode = "Hunting_huntsman_27";
		dialogexit();
	break;

	case "Hunting_huntsman_27":
		dialog.text = StringFromKey("Marso_dialog_249", pchar);
		link.l1 = StringFromKey("Marso_dialog_250");
		link.l1.go = "Hunting_huntsman_26_exit";
		link.l2 = StringFromKey("Marso_dialog_251");
		link.l2.go = "Hunting_huntsman_26_1_exit";
	break;

	case "Hunting_huntsman_28":
		dialog.text = StringFromKey("Marso_dialog_252", pchar.name);
		link.l1 = StringFromKey("Marso_dialog_253");
		link.l1.go = "Hunting_huntsman_29";
	break;

	case "Hunting_huntsman_29":
		dialog.text = StringFromKey("Marso_dialog_254");
		link.l1 = StringFromKey("Marso_dialog_255");
		link.l1.go = "Hunting_huntsman_29_exit";
	break;

	case "Hunting_huntsman_29_exit":
		AddDialogExitQuest("Hunting_huntsman_95");
		dialogexit();
	break;

	case "Return_quest_3":
		dialog.text = StringFromKey("Marso_dialog_256");
		link.l1 = StringFromKey("Marso_dialog_257");
		link.l1.go = "Return_quest_3_exit";
	break;

	case "Return_quest_3_exit":
		NextDiag.CurrentNode = "Return_quest_3";
		dialogexit();
	break;

	case "Brides_Tortuga_1":
		dialog.text = StringFromKey("Marso_dialog_258", pchar);
		link.l1 = "...";
		link.l1.go = "Brides_Tortuga_1_exit";
	break;

	case "Brides_Tortuga_1_exit":
		AddDialogExitQuest("Brides_Tortuga_58");
		dialogexit();
	break;

	case "Brides_Tortuga_2":
		dialog.text = StringFromKey("Marso_dialog_259", pchar);
		link.l1 = StringFromKey("Marso_dialog_260", pchar);
		link.l1.go = "Brides_Tortuga_3";
	break;

	case "Brides_Tortuga_3":
		dialog.text = StringFromKey("Marso_dialog_261");
		link.l1 = StringFromKey("Marso_dialog_262", pchar);
		link.l1.go = "Brides_Tortuga_4";
	break;

	case "Brides_Tortuga_4":
		dialog.text = StringFromKey("Marso_dialog_263");
		link.l1 = StringFromKey("Marso_dialog_264");
		link.l1.go = "Brides_Tortuga_5";
	break;

	case "Brides_Tortuga_5":
		dialog.text = StringFromKey("Marso_dialog_265", pchar);
		link.l1 = StringFromKey("Marso_dialog_266");
		link.l1.go = "Brides_Tortuga_6";
	break;

	case "Brides_Tortuga_6":
		dialog.text = StringFromKey("Marso_dialog_267");
		link.l1 = StringFromKey("Marso_dialog_268");
		link.l1.go = "Brides_Tortuga_6_exit";
	break;

	case "Brides_Tortuga_6_exit":
		AddDialogExitQuest("Brides_Tortuga_60");
		dialogexit();
	break;

	case "Holiday_Marso_Start":
		RemoveLandQuestmark_Main(npchar, "Royal_jackpot");
		pchar.questTemp.AoP.HolidayTalk.Marso = true;
		dialog.text = StringFromKey("Marso_dialog_269");
		link.l1 = StringFromKey("Marso_dialog_270");
		link.l1.go = "Holiday_Marso_2";
	break;

	case "Holiday_Marso_2":
		dialog.text = StringFromKey("Marso_dialog_271");
		link.l1 = StringFromKey("Marso_dialog_272");
		link.l1.go = "Holiday_Marso_3";
	break;

	case "Holiday_Marso_3":
		dialog.text = StringFromKey("Marso_dialog_273");
		link.l1 = StringFromKey("Marso_dialog_274");
		link.l1.go = "Holiday_Marso_Exit";
	break;

	case "Holiday_Marso_Exit":
		if (CheckAttribute(pchar, "questTemp.AoP.HolidayTalk.Rimalier") && 
		CheckAttribute(pchar, "questTemp.AoP.HolidayTalk.Jako") &&
		CheckAttribute(pchar, "questTemp.AoP.HolidayTalk.Marso") &&
		CheckAttribute(pchar, "questTemp.AoP.HolidayTalk.Mary"))
		{
			LAi_SetActorType(pchar);
			DeleteAttribute(pchar, "questTemp.AoP.HolidayTalk");
			DoQuestCheckDelay("Royal_jackpot_3", 1.0);
		}
		NextDiag.CurrentNode = "Holiday_Marso_Repeat";
		DialogExit();
	break;

	case "Holiday_Marso_Repeat":
		dialog.text = StringFromKey("Marso_dialog_275");
		link.l1 = StringFromKey("Marso_dialog_276");
		link.l1.go = "Holiday_Marso_Exit";
	break;

	case "Deck_royal_dialog_1":
		RemoveLandQuestMark_Gen(npchar, "Royal_jackpot");
		dialog.text = StringFromKey("Marso_dialog_277");
		link.l1 = StringFromKey("Marso_dialog_278");
		link.l1.go = "Deck_royal_dialog_3_exit";
	break;

	case "Deck_royal_dialog_3_exit":
		NextDiag.CurrentNode = "Deck_royal_dialog_second";
		dialogexit();
	break;

	case "Deck_royal_dialog_second":
		dialog.text = StringFromKey("Marso_dialog_279", pchar.name);
		link.l1 = StringFromKey("Marso_dialog_280");
		link.l1.go = "exit";
	break;

	case "Deck_royal_dialog_4":
		dialog.text = StringFromKey("Marso_dialog_281");
		link.l1 = StringFromKey("Marso_dialog_282");
		link.l1.go = "Deck_royal_dialog_5";
	break;

	case "Deck_royal_dialog_5":
		dialog.text = StringFromKey("Marso_dialog_283");
		link.l1 = StringFromKey("Marso_dialog_284");
		link.l1.go = "Deck_royal_dialog_5_exit";
	break;

	case "Deck_royal_dialog_5_exit":
		PostEvent("LAi_event_boarding_EnableReload", 100);
		DialogExit();
	break;

	case "Royal_dialog_1":
		dialog.text = StringFromKey("Marso_dialog_285");
		link.l1 = StringFromKey("Marso_dialog_286");
		link.l1.go = "Royal_dialog_1_exit";
	break;

	case "Royal_dialog_1_exit":
		AddDialogExitQuest("Royal_jackpot_56");
		dialogexit();
	break;

	case "Marso_Bay_Walk":
		RemoveLandQuestMark_Gen(npchar, "Royal_jackpot");
		dialog.text = StringFromKey("Marso_dialog_287", pchar.name);
		link.l1 = StringFromKey("Marso_dialog_288");
		link.l1.go = "Marso_Bay_Walk_exit";
	break;

	case "Marso_Bay_Walk_exit":
		NextDiag.CurrentNode = "Marso_Bay_Walk";
		dialogexit();
	break;

	case "Marso_Bay_Walk_1":
		RemoveLandQuestMark_Gen(npchar, "Royal_jackpot");
		dialog.text = StringFromKey("Marso_dialog_289");
		link.l1 = StringFromKey("Marso_dialog_290");
		link.l1.go = "Marso_Bay_Walk_1_exit";
	break;

	case "Marso_Bay_Walk_1_exit":
		NextDiag.CurrentNode = "Marso_Bay_Walk_1";
		DialogExit();
	break;

	case "Marso_Bay_Walk_2":
		RemoveLandQuestMark_Gen(npchar, "Royal_jackpot");
		dialog.text = StringFromKey("Marso_dialog_291");
		link.l1 = StringFromKey("Marso_dialog_292");
		link.l1.go = "Marso_Bay_Walk_2_exit";
	break;

	case "Marso_Bay_Walk_2_exit":
		NextDiag.CurrentNode = "Marso_Bay_Walk_2";
		DialogExit();
	break;

	case "Royal_jackpot_1":
		dialog.text = StringFromKey("Marso_dialog_293");
		link.l1 = StringFromKey("Marso_dialog_294");
		link.l1.go = "Royal_jackpot_1_exit";
	break;

	case "Royal_jackpot_1_exit":
		AddDialogExitQuest("Royal_jackpot_61");
		DialogExit();
	break;

	case "Royal_jackpot_2":
		dialog.text = StringFromKey("Marso_dialog_295");
		link.l1 = StringFromKey("Marso_dialog_296");
		link.l1.go = "Royal_jackpot_3";
	break;

	case "Royal_jackpot_3":
		dialog.text = StringFromKey("Marso_dialog_297");
		link.l1 = StringFromKey("Marso_dialog_298");
		link.l1.go = "Royal_jackpot_exit";
	break;

	case "Royal_jackpot_exit":
		DialogExit();
		AddDialogExitQuest("Royal_jackpot_84");
	break;

	case "Royal_jackpot_8":
		AoP_RoyalDeckDialogTurn("Etien_Marso", pchar.id);
		dialog.text = StringFromKey("Marso_dialog_299");
		link.l1 = StringFromKey("Marso_dialog_300");
		link.l1.go = "Royal_jackpot_8_exit";
	break;

	case "Royal_jackpot_8_exit":
		sld = CharacterFromID("Fransua_Olone");
		LAi_SetActorType(sld);
		sld.Dialog.CurrentNode = "Royal_jackpot_5";
		LAi_ActorDialogNow(sld, pchar, "", -1);
		DialogExit();
	break;

	case "Royal_jackpot_12":
		RemoveLandQuestmark_Main(npchar, "Royal_jackpot");
		dialog.text = StringFromKey("Marso_dialog_301", pchar.name);
		if (!CheckAttribute(pchar, "questTemp.AoP.RoyalJackpot.Marso12_1"))
		{
		link.l1 = StringFromKey("Marso_dialog_302");
		link.l1.go = "Royal_jackpot_12_1";
		}
		if (!CheckAttribute(pchar, "questTemp.AoP.RoyalJackpot.Marso12_2"))
		{
		link.l2 = StringFromKey("Marso_dialog_303");
		link.l2.go = "Royal_jackpot_12_2";
		}
		if (!CheckAttribute(pchar, "questTemp.AoP.RoyalJackpot.Marso12_3"))
		{
		link.l3 = StringFromKey("Marso_dialog_304");
		link.l3.go = "Royal_jackpot_12_3";
		}
		link.l4 = StringFromKey("Marso_dialog_305");
		link.l4.go = "Royal_jackpot_12_exit";
	break;

	case "Royal_jackpot_12_1":
		pchar.questTemp.AoP.RoyalJackpot.Marso12_1 = true;
		dialog.text = StringFromKey("Marso_dialog_306");
		link.l1 = StringFromKey("Marso_dialog_307", pchar);
		link.l1.go = "Royal_jackpot_12";
	break;

	case "Royal_jackpot_12_2":
		pchar.questTemp.AoP.RoyalJackpot.Marso12_2 = true;
		dialog.text = StringFromKey("Marso_dialog_308");
		link.l1 = StringFromKey("Marso_dialog_309", pchar);
		link.l1.go = "Royal_jackpot_12";
	break;

	case "Royal_jackpot_12_3":
		pchar.questTemp.AoP.RoyalJackpot.Marso12_3 = true;
		dialog.text = StringFromKey("Marso_dialog_310", pchar);
		link.l1 = StringFromKey("Marso_dialog_311", pchar);
		link.l1.go = "Royal_jackpot_12";
	break;

	case "Royal_jackpot_12_exit":
		DialogExit();
	break;

	case "Royal_jackpot_final":
		dialog.text = StringFromKey("Marso_dialog_312");
		link.l1 = StringFromKey("Marso_dialog_313");
		link.l1.go = "Royal_jackpot_final_exit";
	break;

	case "Royal_jackpot_final_exit":
		LAi_CharacterDisableDialog(npchar);
		RemoveLandQuestMark_Gen(npchar, "Royal_jackpot");
		DialogExit();
	break;

	case "Marso_Tost":
		CharacterTurnByChr(npchar, pchar);
		dialog.text = StringFromKey("Marso_dialog_314");
		link.l1 = "...";
		link.l1.go = "Marso_Tost_Exit";
	break;

	case "Marso_Tost_Exit":
		StartInstantDialogNow("Fransua_Olone", "Olone_Tost", "Quest\LeBasque\Olone_dialog.c", true);
	break;

	case "Keys_lagoon_1":
		dialog.text = StringFromKey("Marso_dialog_315");
		link.l1 = "...";
		link.l1.go = "Keys_lagoon_1_exit";
	break;

	case "Keys_lagoon_1_exit":
		AddDialogExitQuest("Keys_lagoon_13");
		dialogexit();
	break;

	case "Keys_lagoon_Inspection_1":
		dialog.text = StringFromKey("Marso_dialog_316", pchar, pchar.name);
		link.l1 = StringFromKey("Marso_dialog_317");
		link.l1.go = "Keys_lagoon_Inspection_2";
	break;

	case "Keys_lagoon_Inspection_2":
		dialog.text = StringFromKey("Marso_dialog_318");
		link.l1 = StringFromKey("Marso_dialog_319");
		link.l1.go = "Keys_lagoon_Inspection_3";
	break;

	case "Keys_lagoon_Inspection_3":
		dialog.text = StringFromKey("Marso_dialog_320");
		link.l1 = StringFromKey("Marso_dialog_321");
		link.l1.go = "Keys_lagoon_Inspection_3_Exit";
	break;

	case "Keys_lagoon_Inspection_3_Exit":
		DialogExit();
		QuestPointerDelLoc("Maracaibo_town", "reload", "reload6_back");
		pchar.questTemp.AoP.KeysLagoonMaracaibo.Store = true;
		chrDisableReloadToLocation = false;
		LAi_SetCitizenType(npchar);
		LAi_CharacterDisableDialog(npchar);
	break;

	case "Keys_lagoon_2":
		dialog.text = StringFromKey("Marso_dialog_322");
		link.l1 = StringFromKey("Marso_dialog_323");
		link.l1.go = "Keys_lagoon_3";
	break;

	case "Keys_lagoon_3":
		dialog.text = StringFromKey("Marso_dialog_324");
		link.l1 = "...";
		link.l1.go = "Keys_lagoon_3_exit";
	break;

	case "Keys_lagoon_3_exit":
		AddDialogExitQuest("Keys_lagoon_133");
		DialogExit();
	break;

	case "Keys_lagoon_townhall_repeat":
		dialog.text = StringFromKey("Marso_dialog_325");
		link.l1 = "...";
		link.l1.go = "Keys_lagoon_townhall_repeat_exit";
	break;

	case "Keys_lagoon_townhall_repeat_exit":
		NextDiag.CurrentNode = "Keys_lagoon_townhall_repeat";
		dialogexit();
	break;

	case "Keys_lagoon_5":
		dialog.text = StringFromKey("Marso_dialog_326");
		link.l1 = StringFromKey("Marso_dialog_327");
		link.l1.go = "Keys_lagoon_6";
	break;

	case "Keys_lagoon_6":
		dialog.text = StringFromKey("Marso_dialog_328");
		link.l1 = StringFromKey("Marso_dialog_329", pchar);
		link.l1.go = "Keys_lagoon_6_exit";
	break;

	case "Keys_lagoon_6_exit":
		AddDialogExitQuest("Keys_lagoon_140");
		dialogexit();
	break;

	case "Keys_lagoon_townhall_repeat_2":
		dialog.text = StringFromKey("Marso_dialog_330");
		link.l1 = "...";
		link.l1.go = "Keys_lagoon_townhall_repeat_2_exit";
	break;

	case "Keys_lagoon_townhall_repeat_2_exit":
		NextDiag.CurrentNode = "Keys_lagoon_townhall_repeat_2";
		dialogexit();
	break;

	case "Keys_lagoon_11":
		dialog.text = StringFromKey("Marso_dialog_331");
		link.l1 = StringFromKey("Marso_dialog_332");
		link.l1.go = "Keys_lagoon_12";
	break;

	case "Keys_lagoon_12":
		dialog.text = StringFromKey("Marso_dialog_333");
		link.l1 = StringFromKey("Marso_dialog_334");
		link.l1.go = "Keys_lagoon_13";
	break;

	case "Keys_lagoon_13":
		dialog.text = StringFromKey("Marso_dialog_335");
		link.l1 = StringFromKey("Marso_dialog_336");
		link.l1.go = "Keys_lagoon_13_exit";
	break;

	case "Keys_lagoon_13_exit":
		DialogExit();
		AddDialogExitQuest("Keys_lagoon_220");
	break;

	case "Keys_lagoon_AfterVargas_1":
		CharacterTurnByChr(npchar, pchar);
		dialog.text = StringFromKey("Marso_dialog_337", pchar.name);
		link.l1 = StringFromKey("Marso_dialog_338");
		link.l1.go = "Keys_lagoon_AfterVargas_2";
	break;

	case "Keys_lagoon_AfterVargas_2":
		dialog.text = StringFromKey("Marso_dialog_339");
		link.l1 = StringFromKey("Marso_dialog_340");
		link.l1.go = "Keys_lagoon_AfterVargas_3";
	break;

	case "Keys_lagoon_AfterVargas_3":
		dialog.text = StringFromKey("Marso_dialog_341");
		link.l1 = "...";
		link.l1.go = "Keys_lagoon_AfterVargas_3_Exit";
	break;

	case "Keys_lagoon_AfterVargas_3_Exit":
		AddDialogExitQuest("Keys_lagoon_241");
		dialogexit();
	break;

	case "Keys_lagoon_15":
		dialog.text = StringFromKey("Marso_dialog_342");
		link.l1 = StringFromKey("Marso_dialog_343");
		link.l1.go = "Keys_lagoon_15_1";
	break;

	case "Keys_lagoon_15_1":
		dialog.text = StringFromKey("Marso_dialog_344");
		link.l1 = StringFromKey("Marso_dialog_345");
		link.l1.go = "Keys_lagoon_15_2";
	break;

	case "Keys_lagoon_15_2":
		dialog.text = StringFromKey("Marso_dialog_346", pchar);
		link.l1 = "...";
		link.l1.go = "Keys_lagoon_15_2_Exit";
	break;

	case "Keys_lagoon_15_2_Exit":
		AddDialogExitQuest("Keys_lagoon_291");
		DialogExit();
	break;


}
}

#include "dialog_func.c"

#define EVENT_DIALOG_START		"evntDialogStart"
#define EVENT_DIALOG_EXIT		"evntDialogExit"

#event_handler("dlgReady", "StartDialogWithMainCharacter");
#event_handler("EmergencyDialogExit","DialogExit");

extern void ProcessDialogEvent();
extern void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag); // метод, содержащий ветку квест и др ветки конкрентого НПС

bool dialogDisable = false;
object	Dialog;
ref		CharacterRef = &NullCharacter;
bool	dialogRun = false;

bool	dialogSelf = false;

string  FullDialogPath;
string	PathDlgLngExtn = "";//fix

string dialogEditStrings[10];

void ProcessCommonDialog(ref NPChar, aref Link, aref NextDiag)
{
    ProcessCommonDialogEvent(NPChar, Link, NextDiag);
}

//Инициализация
void DialogsInit()
{
	//Quest_Init();				//Инициализация начального состояния слухов и информации об NPC ------- Ренат
	Set_inDialog_Attributes(); // boal
}

#event_handler("DialogControls_Lock","DialogControls_Lock");
void DialogControls_Lock()
{
    LockControl("DlgAction", true);
    LockControl("DlgAction1", true); 
    LockControl("DlgAction2", true); 
    PostEvent("DialogControls_Unlock", 250);
}

#event_handler("DialogControls_Unlock","DialogControls_Unlock");
void DialogControls_Unlock()
{
    if(!dialogRun) return;
    LockControl("DlgAction", false);
    LockControl("DlgAction1", false);
    LockControl("DlgAction2", false);
}

//Начать диалог
bool DialogMain(ref Character, bool bPlayerInit)
{
	//Если диалог запущен, выходим
	if(dialogRun != false) return false;
	//Ссылка на главного персонажа
	ref mainChr = GetMainCharacter();
	//Если когото не заведено, выходим
	if(!IsEntity(mainChr)) return false;
	if(!IsEntity(Character)) return false;
	if(LAi_IsDead(mainChr)) return false;
	if(LAi_IsDead(Character)) return false;
	//Проверим на существование текущего нода
	if(!CheckAttribute(Character, "Dialog.CurrentNode"))
	{
		Trace("Dialog: Character <" + Character.id + "> can't have field Dialog.CurrentNode, exit from dialog!");
		return false;
	}
	//Если персонаж не готов говорить выходим
	if(!LAi_Character_CanDialog(mainChr, Character)) return false;
	if(!LAi_Character_CanDialog(Character, mainChr)) return false;
	//Сохраняем ссылку на того, с кем говорим
	CharacterRef = Character;
	
	// Попытка загрузить текст дилога
	if( !LoadDialogFiles(Character.Dialog.Filename) ) {
		// имеем ошибочный диалог
		if( !LoadDialogFiles("error_dialog.c") ) {
			return false;
		}
	}
	//Можем начинать диалог
	TimeScaleCounter = 0;
	DelPerkFromActiveList("TimeSpeed");
	dialogRun = true;
	dialogSelf = false;
    if (!bPlayerInit) PostEvent("DialogControls_Lock", 0);
	LAi_Character_StartDialog(mainChr, Character);
	LAi_Character_StartDialog(Character, mainChr);
	SendMessage(mainChr, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 1);
	SendMessage(Character, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 1);	
	//Запускаем диалог
	//Trace("Dialog: dialog path for character <" + Character.id + "> = " + FullDialogPath);
	Dialog.CurrentNode = CharacterRef.Dialog.CurrentNode;
	startDialogMainCounter = 0;
	SetEventHandler("frame", "StartDialogMain", 1);
	SetTimeScale(0.0);
	Log_SetActiveAction("Nothing");
	//TODO: проверить диалоги на кораблях, кажется что и без этого полет нормальный
	//	bool bLockCamAngle = CheckAttribute(loadedLocation, "lockCamAngle") && !isShipInside(loadedLocation.id);
	if (locCameraCurMode == LOCCAMERA_FOLLOW && mainChr.location.group != "sit") // для квестов
	{
		SetCameraDialogMode(Character);  // boal
	}
	// убираем прицел при старте диалога
	if(IsEntity(&objLandInterface))
	{
		SendMessage(&objLandInterface, "ll", MSG_BATTLE_LAND_CROSSHAIR_SHOW, 0);
	}
	//Для сидения в таверне
	pchar.turn_ang = 180.0;
//	SendMessage(&locCamera, "ll", MSG_CAMERA_SPECIALMODE, false);
	return true;	
}

int startDialogMainCounter = 0;
int dialogWaitGreetingSound = 0;
string dialogGreetingSound = "";

void StartDialogMain()
{
	startDialogMainCounter++;
	if(startDialogMainCounter < 3) return;

	SendMessage(pchar, "l", MSG_CHARACTER_STOPSTRAFE);
	DelEventHandler("frame", "StartDialogMain");

	CreateEntity(&Dialog, "dialog");
	Dialog.headModel = CharacterRef.headModel;
	Dialog.gender = CharacterRef.sex;

	DeleteAttribute(&Dialog,"Links");
	DeleteAttribute(&Dialog,"Text");
	DeleteAttribute(&TEV, "CT"); // > кейс локальных временных диалоговых атрибутов, чтобы не плодить переменные; автоматически трутся при старте и завершении любого диалога

	if(CheckAttribute(CharacterRef, "greeting"))
	{
		if(CharacterRef.greeting != "")
		{
			if (!CheckAttribute(CharacterRef, "greeting.minute"))
			{
				dialogGreetingSound = CharacterRef.greeting;
				dialogWaitGreetingSound = 0;
				SetEventHandler("frame", "DialogPlayGreeting", 1);
			}
			else
			{
				if (sti(CharacterRef.greeting.minute) != sti(Environment.date.min))
				{
					dialogGreetingSound = CharacterRef.greeting;
					dialogWaitGreetingSound = 0;
					SetEventHandler("frame", "DialogPlayGreeting", 1);
				}
			}
		}
	}

	object persRef = GetCharacterModel(&Characters[GetMainCharacterIndex()]);
	SendMessage(&Dialog, "lii", 0, &Characters[GetMainCharacterIndex()], &persRef);

	object charRef = GetCharacterModel(&Characters[makeint(CharacterRef.index)]);
	SendMessage(&Dialog, "lii", 1, &Characters[makeint(CharacterRef.index)], &charRef);

	LayerSetRealize(REALIZE);
	LayerAddObject(REALIZE,Dialog,-1256);
	Set_inDialog_Attributes();
	if (!ProcessDialogEventWithCheck()) return;
	SetEventHandler("DialogEvent","ProcessDialogEventWithCheck",0);
	//SetEventHandler("DialogCancel","DialogExit",0);

    AddDialogMeta();
    SetEventHandler("DialogEvent", "AddDialogMeta", 0);

	Event(EVENT_DIALOG_START,"");
}

void DialogPlayGreeting()
{
	dialogWaitGreetingSound++;
	if(dialogWaitGreetingSound < 10) return;
	dialogWaitGreetingSound = 0;
	DelEventHandler("frame", "DialogPlayGreeting");
	//Dialog.greeting = LanguageGetLanguage() + " " + CharacterRef.greeting;
	Dialog.greeting = CharacterRef.greeting;
	CharacterRef.greeting.minute = GetMinute();
	//Dialog.greeting = "Gr_Barmen";
}

//Начать диалог с самим собой
void SelfDialog(ref Character)
{
	//Если диалог запущен, выходим
	if(dialogRun != false) return false;
	//Если когото не заведено, выходим
	if(!IsEntity(Character)) return false;
	//Проверим на существование текущего нода
	if(!CheckAttribute(Character, "Dialog.CurrentNode"))
	{
		Trace("SelfDialog: Character <" + Character.id + "> can't have field Dialog.CurrentNode, exit from dialog!");
		return false;
	}
	//Сохраняем ссыклу на того с кем говорим
	CharacterRef = Character;
	// Попытка загрузить текст дилога
	if( !LoadDialogFiles(Character.Dialog.Filename) ) {
		// имеем ошибочный диалог
		if( !LoadDialogFiles("error_dialog.c") ) {
			return false;
		}
	}
	//Если персонаж не готов говорить выходим
	LAi_Character_CanDialog(Character, Character);
	//Можем начинать диалог
	SendMessage(pchar, "l", MSG_CHARACTER_STOPSTRAFE);
	DelPerkFromActiveList("TimeSpeed");
	dialogRun = true;
	dialogSelf = true;
	SendMessage(Character, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 1);
	//Запускаем диалог
	Dialog.CurrentNode = CharacterRef.Dialog.CurrentNode;
	//Trace("SelfDialog: dialog path for self character <" + Character.id + "> = " + FullDialogPath);
	CreateEntity(&Dialog, "dialog");
	Dialog.headModel = Character.headModel;
	Dialog.gender = Character.sex;

	object persRef = GetCharacterModel(&Characters[GetMainCharacterIndex()]);
	SendMessage(&Dialog, "lii", 0, Character, &persRef);
	SendMessage(&Dialog, "lii", 1, Character, &persRef);
	
	LayerSetRealize(REALIZE);
	LayerAddObject(REALIZE,Dialog,-1256);
	Set_inDialog_Attributes();
	if (!ProcessDialogEventWithCheck()) return;
	SetEventHandler("DialogEvent","ProcessDialogEventWithCheck",0);
	//SetEventHandler("DialogCancel","DialogExit",0);
	AddDialogMeta();
    SetEventHandler("DialogEvent", "AddDialogMeta", 0);

	Event(EVENT_DIALOG_START,"");
}

bool ProcessDialogEventWithCheck()
{	//HardCoffee крашфикс отлов несуществующих нод и отсутствующих вариантов ответов
    ProcessDialogEvent();
    if (!dialogRun) return true;
	aref arLink;
	makearef(arLink, Dialog.Links);
	//trace("CheckDialog: " +"DialogCurrentNode: " +Dialog.CurrentNode +"; Attributes: " +GetAttributesNum(arLink));
	//if (!CheckAttribute(&Dialog, "text") || !CheckAttribute(&Dialog, "Links") || !GetAttributesNum(arLink))
	if (GetAttributesNum(arLink)) return true;

	string sTemp = "DIALOG ERROR! chrID: " +CharacterRef.id +"; File: " +CharacterRef.Dialog.Filename;
	sTemp = sTemp +"; Node: " +CharacterRef.Dialog.CurrentNode +"; Dialog.CurrentNode: " +Dialog.CurrentNode;
	Log_info(sTemp);
	Trace(sTemp);
	DialogExit();
	if (CharacterRef.id == pchar.id) DeleteAttributeEx(&TEV, "LootingInfoMoney,LootingTempMode");
	return false;
}

//Закончить диалог
void DialogExit()
{
	if (CheckAttribute(&TEV, "NoDialogExit")) return; //TODO костыль на что бы не случилось, а диалог прерывать нельзя
	DeleteAttribute(&TEV, "CT"); // > кейс локальных временных диалоговых атрибутов
	ModifyTextHide();

	if (CheckAttribute(CharacterRef, "Dialog.Base_Filename"))
	{	//HardCoffee резервная подключалка оригинального диалогового файла, если гдето забыли его вернуть
		CharacterRef.Dialog.CurrentNode = CharacterRef.Dialog.TempNode;
		CharacterRef.Dialog.Filename = CharacterRef.Dialog.Base_Filename;
		DeleteAttribute(CharacterRef, "Dialog.Base_Filename");
	}
	if (CheckAttribute(CharacterRef, "greeting_base"))
	{	//HardCoffee этот атрибут присваивается когда патрульный или гвард сам обращается к гг по поводу оружия или проверки на шпиона
		CharacterRef.greeting = CharacterRef.greeting_base;
		DeleteAttribute(CharacterRef, "greeting_base");
	}
	if (CharacterRef.id == pchar.id) locCameraSleep(false); //HardCoffee если выход из селф-диалога произошёл с ошибкой
	//Если диалога уже не ведётся, выйдем
	if(!dialogRun) return;
	DelEventHandler("frame", "DialogPlayGreeting");
	//Освобождаем ресурсы
	DeleteClass(&Dialog);
	if(FullDialogPath!="")
	{
		if (CheckAttribute(CharacterRef, "FileDialog2"))
		{
		    UnloadSegment(CharacterRef.FileDialog2);
		    // мешало выходу в сегменте DeleteAttribute(CharacterRef, "FileDialog2");
		    //DeleteAttribute(CharacterRef, "FileDialog2Ready");
		}
		UnloadSegment(FullDialogPath);
	}
	if(PathDlgLngExtn!="") UnloadSegment(PathDlgLngExtn);
	if(dialogSelf == false)
	{
		//Ссылка на главного персонажа
		ref mainChr = GetMainCharacter();
		//Отметим, что персонажи освободились от диалога
		LAi_Character_EndDialog(mainChr, CharacterRef);
		LAi_Character_EndDialog(CharacterRef, mainChr);
		SendMessage(mainChr, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 0);
		SendMessage(CharacterRef, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 0);
		// boal
		if (locCameraCurMode != LOCCAMERA_FOLLOW)
		{
			locCameraTarget(mainChr);
			locCameraFollow();
		}
	}
	else
	{
		LAi_Character_EndDialog(CharacterRef, CharacterRef);
		SendMessage(CharacterRef, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 0);
	}
	dialogRun = false;
	//Сообщим об окончании диалога
	PostEvent(EVENT_DIALOG_EXIT, 1, "l", sti(CharacterRef.index));
	DelEventHandler("DialogEvent", "AddDialogMeta");
	pchar.turn_ang = 10.0;
//	SendMessage(&locCamera, "ll", MSG_CAMERA_SPECIALMODE, false);
}

//Это событие приходит от Player
void StartDialogWithMainCharacter()
{
	if(LAi_IsBoardingProcess()) return;
	if(dialogDisable) return;
	//С кем хотим говорить
	int person = GetEventData();
	//Сими с собой не беседуем
	if(person == GetMainCharacterIndex()) return;
	//С непрогруженными персонажами не беседуем
	if(!IsEntity(&Characters[person])) return;
	//Начинаем диалог
	DialogMain(&Characters[person], true);	
	//Trace("Dialog: start dialog " + person + " whith main character");
}

bool LoadDialogFiles(string dialogPath)
{
	//FullDialogPath = "dialogs/" + dialogPath;
	FullDialogPath = "dialogs\" + dialogPath;

	// Выбор директории с языковыми файлами
	//string sLanguageDir = "DIALOGS\";
	//Путь до текста диалога
	/*int iTmp = strlen(dialogPath);
	if(iTmp<3)
	{
		Trace("Dialog: Missing dialog file: " + dialogPath);
		return false;
	}*/
	//PathDlgLngExtn = strcut(dialogPath,0,iTmp-2) + "h";

	//bool retVal = LoadSegment(PathDlgLngExtn);
	bool retVal;
	
	if( !LoadSegment(FullDialogPath) )
	{
		Trace("Dialog: Missing dialog file: " + FullDialogPath);
		retVal = false;
		// лишнее это UnloadSegment(FullDialogPath);
	} else {
		if(!retVal) {
			retVal = true;
			PathDlgLngExtn = "";
		}
	}

	return retVal;
}

// boal -->
bool SetCameraDialogMode(ref chrRef)
{
	float x1,y1,z1, x2, y2, z2;
	if( false==GetCharacterPos(pchar,&x1,&y1,&z1) ) return false;
    if( false==GetCharacterPos(chrRef,&x2,&y2,&z2) ) return false;

    float a = 0.1;
    float len = GetDistance2D(x1,z1, x2,z2);
	float dx = x1*(1-a)+x2*a;
	float dz = z1*(1-a)+z2*a;
	len = 1;
	float s1 = (dx-x1)*len;
	float s2 = (dz-z1)*len;

    float xcam;
	float zcam;
	if (rand(1) == 0)
	{
		xcam = dx-s2;
		zcam = dz+s1;
	}
	else
	{
		xcam = dx+s2;
		zcam = dz-s1;
	}
	locCameraTarget(chrRef);
	float fH = 1.7;
	if (chrRef.location.group == "sit")
	{
	    fH = 1.15;
	}
	return locCameraToPos(xcam,y1+fH,zcam,false);
}
// boal <--

// mitrokosta возможность начать диалог
bool CanStartDialog()
{
	if(LAi_IsBoardingProcess() || dialogDisable || dialogRun) {
		return false;
	}

	ref mc = GetMainCharacter();

	if(!IsEntity(mc)) {
		return false;
	}

	int chrIndex = SendMessage(mc, "ls", MSG_CHARACTER_EX_MSG, "FindDialogCharacter");

	if(chrIndex < 0 || chrIndex == GetMainCharacterIndex()) {
		return false;
	}

	ref chr = GetCharacter(chrIndex);

	if(!IsEntity(chr) || LAi_IsDead(mc) || LAi_IsDead(chr) || !CheckAttribute(chr, "Dialog.CurrentNode") ||
		!LAi_Character_CanDialog(mc, chr) || !LAi_Character_CanDialog(chr, mc)) {
		return false;
	}

	// evganat - помечаем готового к диалогу персонажа
	SendMessage(pchar, "lsli", MSG_CHARACTER_EX_MSG, "MarkDialogCharacter", true, chr);
	
	return true;
}

string GetPersonPhrase(string chrId, string str1, string str2)
{
	if (CheckAttribute(CharacterRef, "id") && CharacterRef.id == chrId)
		return str1;
	
	return str2;
}

//Стереть ссылки всех языков
//TODO: заменить во всех ProcessDialogEvent
void DeleteLinks(ref rDialog)
{
	DeleteAttribute(rDialog,"Links");
	DeleteAttribute(rDialog,"Links_eng");
}

bool DialogHasEdit(aref link) {
	int linkCount = GetAttributesNum(link);
	for (int i = 0; i < linkCount; i++) {
		aref thisLink = GetAttributeN(link, i);
		if (CheckAttribute(thisLink, "edit")) {
			return true;
		}
	}

	return false;
}

void AddDialogMeta() {
	// if(dialog.text != "") dialog.text = GetFullName(CharacterRef) + ": " + dialog.text;
	aref link;
	makearef(link, dialog.links);
	bool hasEdit = DialogHasEdit(link);
	int linkCount = GetAttributesNum(link);
	for (int i = 0; i < linkCount; i++) {
		string linkName = GetAttributeName(GetAttributeN(link, i));
		if(link.(linkName) != "")
		{
			if(!hasEdit) link.(linkName) = "" + (i + 1) + ". " + link.(linkName);
		}
		else
		{
			if(!CheckAttribute(link, linkName + ".edit")) link.(linkName) = "...";
		}
	}
}


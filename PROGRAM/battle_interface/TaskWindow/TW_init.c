#define TW_DEF_HEADER   		6		// расстояние от основной точки до текста заголовка
#define TW_DEF_FIRSTSTRING 		60		// расстояние от основной точки до первой строки
#define TW_DEF_INTERVAL 		35		// расстояние между строками
#define TW_DEF_COUNTERVOFFSET 	4		// сдвиг для выравнивания правого столбца с другим размером текста
#define TW_DEF_BOTTOMSPACE		50		// расстояние между последней строкой и низом задника

#define TW_DEF_CAPTIONHEIGHT 	40		// толщина полосы для заголовка
#define TW_DEF_MARKSIZE 		50		// размер восклицательного знака
#define TW_DEF_MARKOFFSET 		12		// сдвиг восклицательного знака
#define TW_DEF_LINEHEIGHT 		2		// толщина линии под заголовком

#define TW_DEF_INDENT 			30		// стандартный отступ

#define TW_DEF_HEADER_SCALE		1.5
#define TW_DEF_STRING_SCALE		1.4
#define TW_DEF_COUNTER_SCALE	1.5

#define TW_TASK_TIMER			40

/*  Параметры для картинок:
    - .technique
    - .priority (по умолчанию 10k)
    - .color    (argb)
    - .pos      (по умолчанию для FullHD)
    - Через battle_interface.ini
        - .group
        - .picture
    - Без ini
        - .texture
        - .uv

    Параметры для текста:
    - .font
    - .scale (по умолчанию 1.0)
    - .color (argb)
    - .align (по умолчанию left)
    - .pos.x (переопределяется по максимальной ширине)
    - .pos.y (по умолчанию для FullHD)
    - .text

    Остальное скриптовое */

////////////////////////////////////////////////////////////////////////
//  HANDLERS
////////////////////////////////////////////////////////////////////////

// Счётчики
aref TW_SetTextCounter(string sTask, string sTarget, int max, bool bCopy)
{
    aref   arCnt, arTask, arText;
    string sName = sTarget + "_cnt";
    makearef(arTask, objTask.(sTask));
    makearef(arCnt,  arTask.texts.(sName));
    makearef(arText, arTask.texts.(sTarget));
	
	arCnt.text  = "0/" + max;
	
    if(bCopy)
    {
        arCnt.font  = arText.font;
        arCnt.color = arText.color;
        arCnt.base.pos.y = arText.base.pos.y;
        if(CheckAttribute(arText, "base.scale"))
            arCnt.base.scale = arText.base.scale;
    }
	
    // Скриптовое:
    arCnt.end    = 0;
    arCnt.count  = 0;
    arCnt.max    = max;
    arCnt.parent = sTarget;
    arTask.counters.(sName) = "";

    return arCnt;
}

// Проценты
aref TW_SetPercentCounter(string sTask, string sTarget, float max, bool bCopy)
{
    aref   arCnt, arTask, arText;
    string sName = sTarget + "_percents";
    makearef(arTask, objTask.(sTask));
    makearef(arCnt,  arTask.texts.(sName));
    makearef(arText, arTask.texts.(sTarget));

    arCnt.text  = "0%";
    if(bCopy)
    {
        arCnt.font  = arText.font;
        arCnt.color = arText.color;
        arCnt.base.pos.y = arText.base.pos.y;
        if(CheckAttribute(arText, "base.scale"))
            arCnt.base.scale = arText.base.scale;
    }

    // Скриптовое:
    arCnt.end    = 0;
    arCnt.count  = 0.0;
    arCnt.max    = max;
    arCnt.parent = sTarget;
    arTask.percents.(sName) = "";

    return arCnt;
}

////////////////////////////////////////////////////////////////////////
//  TUTORIALS
////////////////////////////////////////////////////////////////////////

// Блад - Назначение офицеров
void TW_Init_BloodLine_Officers()
{
	aref arTask, arImage, arText, arDef;
	makearef(arDef, objTask.defines);

	objTask.BloodLine_Officers = "Off1";
	makearef(arTask, objTask.BloodLine_Officers);
	TW_Reset(arTask);

	// параметры
	aref arBase;
	if(CheckAttribute(arTask, "base_text"))
		DeleteAttribute(arTask, "base_text");
	makearef(arBase, arTask.base_text);
	arBase.t0.text  = StringFromKey("Task1");
	arBase.t0.font  = "interface_normal";
	arBase.t0.scale = TW_DEF_HEADER_SCALE;
	arBase.t1.text  = StringFromKey("Task2");
	arBase.t1.font  = "interface_normal";
	arBase.t1.scale = TW_DEF_STRING_SCALE;
	arBase.t2.text  = StringFromKey("Task4");
	arBase.t2.font  = "interface_normal";
	arBase.t2.scale = TW_DEF_STRING_SCALE;
	arBase.t3.text  = "0/1";
	arBase.t3.font  = "interface_normal";
	arBase.t3.scale = TW_DEF_STRING_SCALE;
	arBase.t3.align = "right";
	arBase.t4.text  = StringFromKey("Task5");
	arBase.t4.font  = "interface_normal";
	arBase.t4.scale = TW_DEF_STRING_SCALE;
	arBase.t5.text  = "0/1";
	arBase.t5.font  = "interface_normal";
	arBase.t5.scale = TW_DEF_STRING_SCALE;
	arBase.t5.align = "right";
	arBase.t6.text  = StringFromKey("Task6");
	arBase.t6.font  = "interface_normal";
	arBase.t6.scale = TW_DEF_STRING_SCALE;
	arBase.t7.text  = "0/1";
	arBase.t7.font  = "interface_normal";
	arBase.t7.scale = TW_DEF_STRING_SCALE;
	arBase.t7.align = "right";
	arBase.t8.text  = StringFromKey("Task7");
	arBase.t8.font  = "interface_normal";
	arBase.t8.scale = TW_DEF_STRING_SCALE;
	arBase.t9.text  = "0/1";
	arBase.t9.font  = "interface_normal";
	arBase.t9.scale = TW_DEF_STRING_SCALE;
	arBase.t9.align = "right";
	arTask.fixWidth = true;

	// текст
	makearef(arText, arTask.texts.Off1_head);
	arText.font  = "interface_normal";
	arText.base.pos.y = TW_DEF_HEADER;
	arText.base.scale = TW_DEF_HEADER_SCALE;
	arText.text  = arBase.t0.text;
	arText.align = "center";
	TW_ColorHead(arText);

	makearef(arText, arTask.texts.Off1_text0);
	arText.font  = "interface_normal";
	arText.base.pos.y = TW_DEF_FIRSTSTRING;
	arText.base.scale = TW_DEF_STRING_SCALE;
	arText.text  = arBase.t1.text;
	TW_ColorDefault(arText);

	makearef(arText, arTask.texts.Off1_text2);
	arText.font  = "interface_normal";
	arText.base.pos.y = TW_DEF_FIRSTSTRING + TW_DEF_INTERVAL;
	arText.base.scale = TW_DEF_STRING_SCALE;
	arText.text  = arBase.t2.text;
	TW_ColorDefault(arText);

	arText = TW_SetTextCounter("BloodLine_Officers", "Off1_text2", 1, false);
	arText.font  = "interface_normal";
	arText.base.scale = TW_DEF_STRING_SCALE;
	arText.base.pos.y = TW_DEF_FIRSTSTRING + TW_DEF_INTERVAL;
	arText.align = "right";
	TW_ColorDefault(arText);

	makearef(arText, arTask.texts.Off1_text3);
	arText.font  = "interface_normal";
	arText.base.pos.y = TW_DEF_FIRSTSTRING + 2*TW_DEF_INTERVAL;
	arText.base.scale = TW_DEF_STRING_SCALE;
	arText.text  = arBase.t4.text;
	TW_ColorDefault(arText);

	arText = TW_SetTextCounter("BloodLine_Officers", "Off1_text3", 1, false);
	arText.font  = "interface_normal";
	arText.base.scale = TW_DEF_STRING_SCALE;
	arText.base.pos.y = TW_DEF_FIRSTSTRING + 2*TW_DEF_INTERVAL;
	arText.align = "right";
	TW_ColorDefault(arText);

	makearef(arText, arTask.texts.Off1_text4);
	arText.font  = "interface_normal";
	arText.base.pos.y = TW_DEF_FIRSTSTRING + 3*TW_DEF_INTERVAL;
	arText.base.scale = TW_DEF_STRING_SCALE;
	arText.text  = arBase.t6.text;
	TW_ColorDefault(arText);

	arText = TW_SetTextCounter("BloodLine_Officers", "Off1_text4", 1, false);
	arText.font  = "interface_normal";
	arText.base.scale = TW_DEF_STRING_SCALE;
	arText.base.pos.y = TW_DEF_FIRSTSTRING + 3*TW_DEF_INTERVAL;
	arText.align = "right";
	TW_ColorDefault(arText);

	makearef(arText, arTask.texts.Off1_text5);
	arText.font  = "interface_normal";
	arText.base.pos.y = TW_DEF_FIRSTSTRING + 4*TW_DEF_INTERVAL;
	arText.base.scale = TW_DEF_STRING_SCALE;
	arText.text  = arBase.t8.text;
	TW_ColorDefault(arText);
	TW_MarkBottom("BloodLine_Officers", "Off1_text5");

	arText = TW_SetTextCounter("BloodLine_Officers", "Off1_text5", 1, false);
	arText.font  = "interface_normal";
	arText.base.scale = TW_DEF_STRING_SCALE;
	arText.base.pos.y = TW_DEF_FIRSTSTRING + 4*TW_DEF_INTERVAL;
	arText.align = "right";
	TW_ColorDefault(arText);

	// обработчики
	arTask.handlers.TW_Handler_BloodLine_Officers = "";
}

void TW_Handler_BloodLine_Officers(aref arTask, float dTime)
{
	aref arCnt;
	makearef(arCnt, objTask.BloodLine_Officers.texts.Off1_text0);

	int iTemp = GetCharacterIndex("Ogl");
	if (iTemp != -1 && sti(pchar.Fellows.Passengers.cannoner) == iTemp)
	{
		TW_IncreaseCounter("BloodLine_Officers", "Off1_text2", 1);
	}
	else
	{
		TW_DecreaseCounter("BloodLine_Officers", "Off1_text2", 1);
	}

	if (sti(pchar.Fellows.Passengers.boatswain) >= 0)
	{
		TW_IncreaseCounter("BloodLine_Officers", "Off1_text3", 1);
	}
	else
	{
		TW_DecreaseCounter("BloodLine_Officers", "Off1_text3", 1);
	}

	if (sti(pchar.Fellows.Passengers.treasurer) >= 0)
	{
		TW_IncreaseCounter("BloodLine_Officers", "Off1_text4", 1);
	}
	else
	{
		TW_DecreaseCounter("BloodLine_Officers", "Off1_text4", 1);
	}

	if (sti(pchar.Fellows.Passengers.carpenter) >= 0)
	{
		TW_IncreaseCounter("BloodLine_Officers", "Off1_text5", 1);
	}
	else
	{
		TW_DecreaseCounter("BloodLine_Officers", "Off1_text5", 1);
	}

	bool bOk = TW_CheckCounter("BloodLine_Officers", "Off1_text2") &&
	TW_CheckCounter("BloodLine_Officers", "Off1_text3") &&
	TW_CheckCounter("BloodLine_Officers", "Off1_text4") &&
	TW_CheckCounter("BloodLine_Officers", "Off1_text5");

	if (!CheckAttribute(pchar, "questTemp.BloodLine_GTutor.OffDone"))
	{
		pchar.questTemp.BloodLine_GTutor.OffDone = false;
	}
	if (bOk)
	{
		if (sti(pchar.questTemp.BloodLine_GTutor.OffDone) == false)
		{
			TW_ColorWeak(arCnt);
			CapBlood_DoneOfficersRecruit_OpenExit();

			pchar.questTemp.BloodLine_GTutor.OffDone = true;
		}
	}
	else
	{
		if (sti(pchar.questTemp.BloodLine_GTutor.OffDone) == true)
		{
			TW_ColorDefault(arCnt);

			// CapBlood_DoneOfficersRecruit_CloseExit("");
			DeleteAttribute(pchar, "PostEventQuest.questDelay.CapBlood_DoneOfficersRecruit_OpenExit");
			pchar.questTemp.BloodLine_GTutor.OffDone = false;
		}
	}
}

void TW_Finish_BloodLine_Officers(string qName)
{
	DeleteAttribute(&objTask, "BloodLine_Officers.handlers");
    TW_Release();
}

// Блад - Битва в море
void TW_Init_BloodLine_SeaBattle1()
{
    aref arTask, arImage, arText, arDef;
	makearef(arDef, objTask.defines);

	objTask.BloodLine_SeaBattle1 = "SeaBattle1";
	makearef(arTask, objTask.BloodLine_SeaBattle1);
    TW_Reset(arTask);

	// параметры
	aref arBase;
	if(CheckAttribute(arTask, "base_text"))
		DeleteAttribute(arTask, "base_text");
	makearef(arBase, arTask.base_text);
    arBase.t0.text  = StringFromKey("Task8");
    arBase.t0.font  = "interface_normal";
	arBase.t0.scale = TW_DEF_HEADER_SCALE;
    arBase.t1.text  = StringFromKey("Task9");
    arBase.t1.font  = "interface_normal";
    arBase.t1.scale = TW_DEF_STRING_SCALE;
    arBase.t2.text  = StringFromKey("Task10");
    arBase.t2.font  = "interface_normal";
    arBase.t2.scale = TW_DEF_STRING_SCALE;
	arBase.t3.text = "0/2";
	arBase.t3.font  = "interface_normal";
    arBase.t3.scale = TW_DEF_STRING_SCALE;
	arBase.t3.align = "right";

	arTask.fixWidth = true;

	// текст
	makearef(arText, arTask.texts.SeaBattle1_head);
	arText.font  = "interface_normal";
    arText.base.pos.y = TW_DEF_HEADER;
	arText.base.scale = TW_DEF_HEADER_SCALE;
    arText.text  = arBase.t0.text;
    arText.align = "center";
    TW_ColorHead(arText);

	makearef(arText, arTask.texts.SeaBattle1_text0);
    arText.font  = "interface_normal";
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.text  = arBase.t1.text;
    TW_ColorDefault(arText);

	makearef(arText, arTask.texts.SeaBattle1_text1);
    arText.font  = "interface_normal";
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.base.pos.y = TW_DEF_FIRSTSTRING + TW_DEF_INTERVAL;
    arText.text  = arBase.t2.text;
    TW_ColorDefault(arText);
    TW_MarkBottom("BloodLine_SeaBattle1", "SeaBattle1_text1");

	arText = TW_SetTextCounter("BloodLine_SeaBattle1", "SeaBattle1_text1", 2, false);
	arText.font  = "interface_normal";
	arText.base.scale = TW_DEF_STRING_SCALE;
    arText.base.pos.y = TW_DEF_FIRSTSTRING + TW_DEF_INTERVAL;
    arText.align = "right";
	TW_ColorDefault(arText);
}

void TW_Finish_BloodLine_SeaBattle1(string qName)
{
	// чтобы таск сработал на время снимем лок
	bQuestDisableMapEnter = false;

    objTask.BloodLine_SeaBattle1 = "";
	// Tutorial_BloodPrologue_SeaEscape("");
	// TW_Init_BloodLine_SeaBattle2();
}

void TW_Init_BloodLine_SeaBattle2()
{
    aref arTask, arImage, arText, arDef;
	makearef(arDef, objTask.defines);

	objTask.BloodLine_SeaBattle1 = "SeaBattle2";
	makearef(arTask, objTask.BloodLine_SeaBattle1);
    TW_Reset(arTask);

	// параметры
	aref arBase;
	if(CheckAttribute(arTask, "base_text"))
		DeleteAttribute(arTask, "base_text");
	makearef(arBase, arTask.base_text);
    arBase.t0.text  = StringFromKey("Task11");
    arBase.t0.font  = "interface_normal";
	arBase.t0.scale = TW_DEF_HEADER_SCALE;
    arBase.t1.text  = StringFromKey("Task12");
    arBase.t1.font  = "interface_normal";
    arBase.t1.scale = TW_DEF_STRING_SCALE;
	arBase.t2.text  = "0/1";
	arBase.t2.font  = "interface_normal";
    arBase.t2.scale = TW_DEF_STRING_SCALE;
	arBase.t2.align = "right";

	arTask.fixWidth = true;

	// текст
	makearef(arText, arTask.texts.SeaBattle1_head);
	arText.font  = "interface_normal";
    arText.base.pos.y = TW_DEF_HEADER;
	arText.base.scale = TW_DEF_HEADER_SCALE;
    arText.text  = arBase.t0.text;
    arText.align = "center";
    TW_ColorHead(arText);

	makearef(arText, arTask.texts.SeaBattle1_text1);
    arText.font  = "interface_normal";
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.text  = arBase.t1.text;
    TW_ColorDefault(arText);
    TW_MarkBottom("BloodLine_SeaBattle1", "SeaBattle1_text1");

	arText = TW_SetTextCounter("BloodLine_SeaBattle1", "SeaBattle1_text1", 1, false);
	arText.font  = "interface_normal";
	arText.base.scale = TW_DEF_STRING_SCALE;
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.align = "right";
	TW_ColorDefault(arText);

	// обработчики
	arTask.handlers.TW_Handler_BloodLine_SeaBattle2 = "";
}

void TW_Handler_BloodLine_SeaBattle2(aref arTask, float dTime)
{
    if (bMapEnter)
	{
		TW_IncreaseCounter("BloodLine_SeaBattle1", "SeaBattle1_text1", 1);
	}

	if (TW_CheckCounter("BloodLine_SeaBattle1", "SeaBattle1_text1"))
	{
		bQuestDisableMapEnter = true;
		bMapEnter = false;
		DeleteAttribute(arTask, "handlers");
		DoQuestFunctionDelay("TW_Finish_BloodLine_SeaBattle2", 6.0);

		// поощрение за правильное выполнение задания
		int iChar = GetCharacterIndex("SpaBoat_1");
		if (iChar >= 0 && !LAi_IsDead(&characters[iChar]))
		{
			AddCharacterExpToSkill(pchar, "Sailing", 100); // опыт в навигацию
			AddCharacterExpToSkill(pchar, "Sneak", 100); // опыт в скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 100); // опыт в лидерство
		}
	}
}

void TW_Finish_BloodLine_SeaBattle2(string qName)
{
    TW_Release();
    DoQuestFunctionDelay("BloodLine_GlobalTutor_ReloadToCabinDialog", 3.0);
}

void TW_Init_BloodLine_NewShip()
{
    aref arTask, arImage, arText, arDef;
	makearef(arDef, objTask.defines);

	objTask.BloodLine_NewShip = "NewShip";
	makearef(arTask, objTask.BloodLine_NewShip);
    TW_Reset(arTask);

	// параметры
	aref arBase;
	if(CheckAttribute(arTask, "base_text"))
		DeleteAttribute(arTask, "base_text");
	makearef(arBase, arTask.base_text);
    arBase.t0.text  = StringFromKey("Task13");
    arBase.t0.font  = "interface_normal";
	arBase.t0.scale = TW_DEF_HEADER_SCALE;
    arBase.t1.text  = StringFromKey("Task14");
    arBase.t1.font  = "interface_normal";
    arBase.t1.scale = TW_DEF_STRING_SCALE;
	arBase.t2.text  = "0/1";
	arBase.t2.font  = "interface_normal";
    arBase.t2.scale = TW_DEF_STRING_SCALE;
	arBase.t2.align = "right";
    arBase.t3.text  = StringFromKey("Task15");
    arBase.t3.font  = "interface_normal";
    arBase.t3.scale = TW_DEF_STRING_SCALE;
	arBase.t4.text  = "0/1";
	arBase.t4.font  = "interface_normal";
    arBase.t4.scale = TW_DEF_STRING_SCALE;
	arBase.t4.align = "right";

	arTask.fixWidth = true;

	// текст
	makearef(arText, arTask.texts.NewShip_head);
	arText.font  = "interface_normal";
    arText.base.pos.y = TW_DEF_HEADER;
	arText.base.scale = TW_DEF_HEADER_SCALE;
    arText.text  = arBase.t0.text;
    arText.align = "center";
    TW_ColorHead(arText);

	makearef(arText, arTask.texts.NewShip_text1);
    arText.font  = "interface_normal";
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.text  = arBase.t1.text;
    TW_ColorDefault(arText);

	arText = TW_SetTextCounter("BloodLine_NewShip", "NewShip_text1", 1, false);
	arText.font  = "interface_normal";
	arText.base.scale = TW_DEF_STRING_SCALE;
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.align = "right";
	TW_ColorDefault(arText);

	makearef(arText, arTask.texts.NewShip_text2);
    arText.font  = "interface_normal";
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.base.pos.y = TW_DEF_FIRSTSTRING + TW_DEF_INTERVAL;
    arText.text  = arBase.t3.text;
    TW_ColorDefault(arText);
    TW_MarkBottom("BloodLine_NewShip", "NewShip_text2");

	arText = TW_SetTextCounter("BloodLine_NewShip", "NewShip_text2", 1, false);
	arText.font  = "interface_normal";
	arText.base.scale = TW_DEF_STRING_SCALE;
    arText.base.pos.y = TW_DEF_FIRSTSTRING + TW_DEF_INTERVAL;
    arText.align = "right";
	TW_ColorDefault(arText);

	// обработчики
	arTask.handlers.TW_Handler_BloodLine_NewShip = "";
}

void TW_Handler_BloodLine_NewShip(aref arTask, float dTime)
{
	int iTemp;

	iTemp = GetCompanionIndex(pchar, 1);
	if (iTemp != -1)
	{
		TW_IncreaseCounter("BloodLine_NewShip", "NewShip_text2", 1);
	}
	else
	{
	    TW_DecreaseCounter("BloodLine_NewShip", "NewShip_text2", 1);
	}

	bool bOk = TW_CheckCounter("BloodLine_NewShip", "NewShip_text2");

	if (bOk)
	{
		DeleteAttribute(arTask, "handlers");
		DoQuestFunctionDelay("TW_Finish_BloodLine_NewShip", 3.0);
	}
}

void TW_Finish_BloodLine_NewShip(string qName)
{
	objTask.BloodLine_NewShip = "";
	BloodLine_GlobalTutor_StartShipChangeTutorial("");
	TW_Init_BloodLine_NewShip1();
}

void TW_Init_BloodLine_NewShip1()
{
    aref arTask, arImage, arText, arDef;
	makearef(arDef, objTask.defines);

	objTask.BloodLine_NewShip = "NewShip1";
	makearef(arTask, objTask.BloodLine_NewShip);
    TW_Reset(arTask);

	// параметры
	aref arBase;
	if(CheckAttribute(arTask, "base_text"))
		DeleteAttribute(arTask, "base_text");
	makearef(arBase, arTask.base_text);
    arBase.t0.text  = StringFromKey("Task16");
    arBase.t0.font  = "interface_normal";
	arBase.t0.scale = TW_DEF_HEADER_SCALE;
    arBase.t1.text  = StringFromKey("Task17");
    arBase.t1.font  = "interface_normal";
    arBase.t1.scale = TW_DEF_STRING_SCALE;
	arBase.t2.text  = "0/1";
	arBase.t2.font  = "interface_normal";
    arBase.t2.scale = TW_DEF_STRING_SCALE;
	arBase.t2.align = "right";
    arBase.t3.text  = StringFromKey("Task18");
    arBase.t3.font  = "interface_normal";
    arBase.t3.scale = TW_DEF_STRING_SCALE;
	arBase.t4.text  = "0/1";
	arBase.t4.font  = "interface_normal";
    arBase.t4.scale = TW_DEF_STRING_SCALE;
	arBase.t4.align = "right";

	arTask.fixWidth = true;

	// текст
	makearef(arText, arTask.texts.NewShip_head);
	arText.font  = "interface_normal";
    arText.base.pos.y = TW_DEF_HEADER;
	arText.base.scale = TW_DEF_HEADER_SCALE;
    arText.text  = arBase.t0.text;
    arText.align = "center";
    TW_ColorHead(arText);

	makearef(arText, arTask.texts.NewShip_text1);
    arText.font  = "interface_normal";
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.text  = arBase.t1.text;
    TW_ColorDefault(arText);

	arText = TW_SetTextCounter("BloodLine_NewShip", "NewShip_text1", 1, false);
	arText.font  = "interface_normal";
	arText.base.scale = TW_DEF_STRING_SCALE;
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.align = "right";
	TW_ColorDefault(arText);

	makearef(arText, arTask.texts.NewShip_text2);
    arText.font  = "interface_normal";
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.base.pos.y = TW_DEF_FIRSTSTRING + TW_DEF_INTERVAL;
    arText.text  = arBase.t3.text;
    TW_ColorDefault(arText);
    TW_MarkBottom("BloodLine_NewShip", "NewShip_text2");

	arText = TW_SetTextCounter("BloodLine_NewShip", "NewShip_text2", 1, false);
	arText.font  = "interface_normal";
	arText.base.scale = TW_DEF_STRING_SCALE;
    arText.base.pos.y = TW_DEF_FIRSTSTRING + TW_DEF_INTERVAL;
    arText.align = "right";
	TW_ColorDefault(arText);

	// обработчики
	arTask.handlers.TW_Handler_BloodLine_NewShip1 = "";
}

void TW_Handler_BloodLine_NewShip1(aref arTask, float dTime)
{
	int iTemp, i;
	ref chref;

	iTemp = GetCompanionIndex(pchar, 1);
	int iShipType = SHIP_NOTUSED;
	int iShipBaseType = SHIP_NOTUSED;
	if (iTemp != -1)
	{
		chref = &Characters[iTemp];

		iShipType = GetCharacterShipType(chref);
		if (iShipType != SHIP_NOTUSED)
		{
			iShipBaseType = sti(RealShips[iShipType].basetype);
		}
	}

	if (iShipBaseType == SHIP_ARABELLA)
	{
		TW_IncreaseCounter("BloodLine_NewShip", "NewShip_text1", 1);
	}
	else
	{
	    TW_DecreaseCounter("BloodLine_NewShip", "NewShip_text1", 1);
	}

	bool bOk = false;
	if (iTemp != -1 && iShipBaseType == SHIP_ARABELLA)
	{
		bOk = true;
		for (i = 0; i < GOODS_QUANTITY; i++)
		{
			if (i >= GOOD_CANNON_3) continue;
			if (GetCargoGoods(chref, i) > 0)
			{
				bOk = false;
				break;
			}
		}
		if (!bOk)
		{
			bOk = GetCargoFreeSpace(pchar) < 10;
		}
		bOk = bOk && GetCrewQuantity(chref) == 0;
	}

	if (bOk)
	{
		TW_IncreaseCounter("BloodLine_NewShip", "NewShip_text2", 1);
	}
	else
	{
	    TW_DecreaseCounter("BloodLine_NewShip", "NewShip_text2", 1);
	}

	bOk = TW_CheckCounter("BloodLine_NewShip", "NewShip_text1") &&
		TW_CheckCounter("BloodLine_NewShip", "NewShip_text2");

	if (!CheckAttribute(pchar, "questTemp.BloodLine_GTutor.BuyShipDone"))
	{
		pchar.questTemp.BloodLine_GTutor.BuyShipDone = false;
	}
	if (bOk)
	{
		if (sti(pchar.questTemp.BloodLine_GTutor.BuyShipDone) == false)
		{
			DoQuestFunctionDelay("BloodLine_GlobalTutor_BuyShipDone_OpenExit", 1.0);
			TW_AddBottomText("NewShip_text3", StringFromKey("Task19"), "Default");
			TW_RecalculateLayout();
			pchar.questTemp.BloodLine_GTutor.BuyShipDone = true;
		}
	}
	else
	{
		if (sti(pchar.questTemp.BloodLine_GTutor.BuyShipDone) == true)
		{
			BloodLine_GlobalTutor_BuyShipDone_CloseExit("");
			DeleteAttribute(pchar, "PostEventQuest.questDelay.BloodLine_GlobalTutor_BuyShipDone_OpenExit");
			TW_RemoveBottomText();
			TW_RecalculateLayout();
			pchar.questTemp.BloodLine_GTutor.BuyShipDone = false;
		}
	}
}

void TW_Finish_BloodLine_NewShip1(string qName)
{
	DeleteAttribute(&objTask, "BloodLine_NewShip.handlers");
	objTask.BloodLine_NewShip = "";
	TW_Release();
}

void TW_Start_BloodLine_NewShip2(string qName)
{
	TW_Init_BloodLine_NewShip2();
	TW_Open("BloodLine_NewShip");
}

void TW_Init_BloodLine_NewShip2()
{
    aref arTask, arImage, arText, arDef;
	makearef(arDef, objTask.defines);

	objTask.BloodLine_NewShip = "NewShip2";
	makearef(arTask, objTask.BloodLine_NewShip);
    TW_Reset(arTask);

	// параметры
	aref arBase;
	if(CheckAttribute(arTask, "base_text"))
		DeleteAttribute(arTask, "base_text");
	makearef(arBase, arTask.base_text);
    arBase.t0.text  = StringFromKey("Task20");
    arBase.t0.font  = "interface_normal";
	arBase.t0.scale = TW_DEF_HEADER_SCALE;
    arBase.t1.text  = StringFromKey("Task21");
    arBase.t1.font  = "interface_normal";
    arBase.t1.scale = TW_DEF_STRING_SCALE;
	arBase.t2.text  = "0/1";
	arBase.t2.font  = "interface_normal";
    arBase.t2.scale = TW_DEF_STRING_SCALE;
	arBase.t2.align = "right";
    arBase.t3.text  = StringFromKey("Task22");
    arBase.t3.font  = "interface_normal";
    arBase.t3.scale = TW_DEF_STRING_SCALE;
	arBase.t4.text  = "0/1";
	arBase.t4.font  = "interface_normal";
    arBase.t4.scale = TW_DEF_STRING_SCALE;
	arBase.t4.align = "right";

	arTask.fixWidth = true;

	// текст
	makearef(arText, arTask.texts.NewShip_head);
	arText.font  = "interface_normal";
    arText.base.pos.y = TW_DEF_HEADER;
	arText.base.scale = TW_DEF_HEADER_SCALE;
    arText.text  = arBase.t0.text;
    arText.align = "center";
    TW_ColorHead(arText);

	makearef(arText, arTask.texts.NewShip_text1);
    arText.font  = "interface_normal";
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.text  = arBase.t1.text;
    TW_ColorDefault(arText);

	arText = TW_SetTextCounter("BloodLine_NewShip", "NewShip_text1", 1, false);
	arText.font  = "interface_normal";
	arText.base.scale = TW_DEF_STRING_SCALE;
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.align = "right";
	TW_ColorDefault(arText);

	makearef(arText, arTask.texts.NewShip_text2);
    arText.font  = "interface_normal";
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.base.pos.y = TW_DEF_FIRSTSTRING + TW_DEF_INTERVAL;
    arText.text  = arBase.t3.text;
    TW_ColorDefault(arText);
    TW_MarkBottom("BloodLine_NewShip", "NewShip_text2");

	arText = TW_SetTextCounter("BloodLine_NewShip", "NewShip_text2", 1, false);
	arText.font  = "interface_normal";
	arText.base.scale = TW_DEF_STRING_SCALE;
    arText.base.pos.y = TW_DEF_FIRSTSTRING + TW_DEF_INTERVAL;
    arText.align = "right";
	TW_ColorDefault(arText);

	// обработчики
	arTask.handlers.TW_Handler_BloodLine_NewShip2 = "";
}


void TW_Handler_BloodLine_NewShip2(aref arTask, float dTime)
{
	int iTemp;
	ref chref;
	aref aDock, aTemp;
	bool bOk = false;

	int iPortManIndx = GetCharacterIndex("Tortuga_PortMan");
	if (iPortManIndx != -1)
	{
		makeref(chref, Characters[iPortManIndx]);
		if (CheckAttribute(chref, "ShipInStockMan"))
		{
			makearef(aDock, chref.ShipInStockMan);
			for (int i = 0; i < GetAttributesNum(aDock); i++)
			{
				aTemp = GetAttributeN(aDock, i);
				iTemp = sti(RealShips[sti(aTemp.Ship.Type)].basetype);
				if (iTemp == SHIP_ARABELLA)
				{
				    bOk = true;
				    break;
				}
			}
		}
	}
	if (bOk)
	{
		TW_IncreaseCounter("BloodLine_NewShip", "NewShip_text2", 1);
	}
	else
	{
	    TW_DecreaseCounter("BloodLine_NewShip", "NewShip_text2", 1);
	}

	bOk = TW_CheckCounter("BloodLine_NewShip", "NewShip_text2");

	if (bOk)
	{
		DeleteAttribute(arTask, "handlers");
		TW_AddBottomText("NewShip_text3", StringFromKey("Task23"), "Default");
		TW_RecalculateLayout();
		DoQuestFunctionDelay("BloodLine_GlobalTutor_GiveShipDone_OpenExit", 3.0);
	}
}

void TW_Finish_BloodLine_NewShip2(string qName)
{
	TW_Release();
}

void TW_Init_BloodLine_NewShip3()
{
    aref arTask, arImage, arText, arDef;
	makearef(arDef, objTask.defines);

	objTask.BloodLine_NewShip = "NewShip3";
	makearef(arTask, objTask.BloodLine_NewShip);
    TW_Reset(arTask);

	// параметры
	aref arBase;
	if(CheckAttribute(arTask, "base_text"))
		DeleteAttribute(arTask, "base_text");
	makearef(arBase, arTask.base_text);
    arBase.t0.text  = StringFromKey("Task24");
    arBase.t0.font  = "interface_normal";
	arBase.t0.scale = TW_DEF_HEADER_SCALE;
    arBase.t1.text  = StringFromKey("Task25");
    arBase.t1.font  = "interface_normal";
    arBase.t1.scale = TW_DEF_STRING_SCALE;
	arBase.t2.text  = "0/1";
	arBase.t2.font  = "interface_normal";
    arBase.t2.scale = TW_DEF_STRING_SCALE;
	arBase.t2.align = "right";
    arBase.t3.text  = StringFromKey("Task26");
    arBase.t3.font  = "interface_normal";
    arBase.t3.scale = TW_DEF_STRING_SCALE;
	arBase.t4.text  = "0/1";
	arBase.t4.font  = "interface_normal";
    arBase.t4.scale = TW_DEF_STRING_SCALE;
	arBase.t4.align = "right";

	arTask.fixWidth = true;

	// текст
	makearef(arText, arTask.texts.NewShip_head);
	arText.font  = "interface_normal";
    arText.base.pos.y = TW_DEF_HEADER;
	arText.base.scale = TW_DEF_HEADER_SCALE;
    arText.text  = arBase.t0.text;
    arText.align = "center";
    TW_ColorHead(arText);

	makearef(arText, arTask.texts.NewShip_text1);
    arText.font  = "interface_normal";
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.text  = arBase.t1.text;
    TW_ColorDefault(arText);

	arText = TW_SetTextCounter("BloodLine_NewShip", "NewShip_text1", 1, false);
	arText.font  = "interface_normal";
	arText.base.scale = TW_DEF_STRING_SCALE;
    arText.base.pos.y = TW_DEF_FIRSTSTRING;
    arText.align = "right";
	TW_ColorDefault(arText);

	makearef(arText, arTask.texts.NewShip_text2);
    arText.font  = "interface_normal";
    arText.base.scale = TW_DEF_STRING_SCALE;
    arText.base.pos.y = TW_DEF_FIRSTSTRING + TW_DEF_INTERVAL;
    arText.text  = arBase.t3.text;
    TW_ColorDefault(arText);
    TW_MarkBottom("BloodLine_NewShip", "NewShip_text2");

	arText = TW_SetTextCounter("BloodLine_NewShip", "NewShip_text2", 1, false);
	arText.font  = "interface_normal";
	arText.base.scale = TW_DEF_STRING_SCALE;
    arText.base.pos.y = TW_DEF_FIRSTSTRING + TW_DEF_INTERVAL;
    arText.align = "right";
	TW_ColorDefault(arText);

	// обработчики
	arTask.handlers.TW_Handler_BloodLine_NewShip3 = "";
}


void TW_Handler_BloodLine_NewShip3(aref arTask, float dTime)
{
	int iTemp;
	ref chref;

	iTemp = FindColony("Tortuga");
	if (!TW_CheckCounter("BloodLine_NewShip", "NewShip_text1"))
	{
	    return;
	}

	bool bOk = false;
	if (iTemp != -1)
	{
		chref = GetColonyByIndex(iTemp);
		bOk = GetCrewQuantity(chref) == 0;
		if (!bOk)
		{
			bOk = GetCargoFreeSpace(pchar) < 10;
		}
	}

	if (bOk)
	{
		TW_IncreaseCounter("BloodLine_NewShip", "NewShip_text2", 1);
	}
	else
	{
	    TW_DecreaseCounter("BloodLine_NewShip", "NewShip_text2", 1);
	}

	bOk = TW_CheckCounter("BloodLine_NewShip", "NewShip_text2");

	if (!CheckAttribute(pchar, "questTemp.BloodLine_GTutor.HireCrewDone"))
	{
		pchar.questTemp.BloodLine_GTutor.HireCrewDone = false;
	}
	if (bOk)
	{
		if (sti(pchar.questTemp.BloodLine_GTutor.HireCrewDone) == false)
		{
			TW_AddBottomText("NewShip_text3", StringFromKey("Task27"), "Default");
			TW_RecalculateLayout();
			DoQuestFunctionDelay("BloodLine_GlobalTutor_HireCrew_OpenExit", 2.0);
			pchar.questTemp.BloodLine_GTutor.HireCrewDone = true;
		}
	}
	else
	{
		if (sti(pchar.questTemp.BloodLine_GTutor.HireCrewDone) == true)
		{
			TW_RemoveBottomText();
			TW_RecalculateLayout();
			BloodLine_GlobalTutor_HireCrew_CloseExit("");
			DeleteAttribute(pchar, "PostEventQuest.questDelay.BloodLine_GlobalTutor_HireCrew_OpenExit");
			pchar.questTemp.BloodLine_GTutor.HireCrewDone = false;
		}
	}
}

void TW_Finish_BloodLine_NewShip3(string qName)
{
	DeleteAttribute(&objTask, "BloodLine_NewShip.handlers");
	TW_Release();
}

void TW_Init_BloodLine_LeaveFort()
{
	aref arTask, arText, arBase;

	objTask.BloodLine_LeaveFort = "LeaveFort";
	makearef(arTask, objTask.BloodLine_LeaveFort);
	TW_Reset(arTask);

	if (CheckAttribute(arTask, "base_text"))
		DeleteAttribute(arTask, "base_text");

	makearef(arBase, arTask.base_text);

	arBase.t0.text = StringFromKey("Task28");
	arBase.t0.font = "interface_normal";
	arBase.t0.scale = TW_DEF_HEADER_SCALE;

	arBase.t1.text = StringFromKey("Task29");
	arBase.t1.font = "interface_normal";
	arBase.t1.scale = TW_DEF_STRING_SCALE;

	arBase.t2.text = "0/1";
	arBase.t2.font = "interface_normal";
	arBase.t2.scale = TW_DEF_STRING_SCALE;
	arBase.t2.align = "right";

	arTask.fixWidth = true;

	makearef(arText, arTask.texts.LeaveFort_head);
	arText.font = "interface_normal";
	arText.base.pos.y = TW_DEF_HEADER;
	arText.base.scale = TW_DEF_HEADER_SCALE;
	arText.text = arBase.t0.text;
	arText.align = "center";
	TW_ColorHead(arText);

	makearef(arText, arTask.texts.LeaveFort_text);
	arText.font = "interface_normal";
	arText.base.pos.y = TW_DEF_FIRSTSTRING;
	arText.base.scale = TW_DEF_STRING_SCALE;
	arText.text = arBase.t1.text;
	TW_ColorDefault(arText);
	TW_MarkBottom("BloodLine_LeaveFort", "LeaveFort_text");

	arText = TW_SetTextCounter("BloodLine_LeaveFort", "LeaveFort_text", 1, false);
	arText.font = "interface_normal";
	arText.base.pos.y = TW_DEF_FIRSTSTRING;
	arText.base.scale = TW_DEF_STRING_SCALE;
	arText.align = "right";
	TW_ColorDefault(arText);

	arTask.handlers.TW_Handler_BloodLine_LeaveFort = "";
}

void TW_Handler_BloodLine_LeaveFort(aref arTask, float dTime)
{
	ref fort = CharacterFromID("Bridgetown Fort Commander");

	if (Ship_GetDistance2D(pchar, fort) < 500.0) return;

	TW_IncreaseCounter("BloodLine_LeaveFort", "LeaveFort_text", 1);

	DeleteAttribute(arTask, "handlers");
	DoQuestFunctionDelay("TW_Finish_BloodLine_LeaveFort", 2.0);
}

void TW_Finish_BloodLine_LeaveFort(string qName)
{
	// bQuestDisableMapEnter = false;

	CapBloodLine_AddArabellaTrap();
	DoQuestReloadToLocation("Arabella_Deck", "reload", "reload1", "");
	SetFunctionLocationCondition("CapBloodLine_OfficersToPcharLocation", "Arabella_Deck", false);

	objTask.BloodLine_LeaveFort = "";
	TW_Release();
}

void TW_Init_BloodLine_Encarnacion()
{
	aref arTask, arText, arBase;

	objTask.BloodLine_Encarnacion = "Encarnacion";
	makearef(arTask, objTask.BloodLine_Encarnacion);
	TW_Reset(arTask);

	if (CheckAttribute(arTask, "base_text"))
		DeleteAttribute(arTask, "base_text");

	makearef(arBase, arTask.base_text);

	arBase.t0.text = FindPersonalName("Encarnacion_ship");
	arBase.t0.font = "interface_normal";
	arBase.t0.scale = TW_DEF_HEADER_SCALE;

	arBase.t1.text = StringFromKey("Task30");
	arBase.t1.font = "interface_normal";
	arBase.t1.scale = TW_DEF_STRING_SCALE;

	arBase.t2.text = "0/1";
	arBase.t2.font = "interface_normal";
	arBase.t2.scale = TW_DEF_STRING_SCALE;
	arBase.t2.align = "right";

	arTask.fixWidth = true;

	makearef(arText, arTask.texts.Encarnacion_head);
	arText.font = "interface_normal";
	arText.base.pos.y = TW_DEF_HEADER;
	arText.base.scale = TW_DEF_HEADER_SCALE;
	arText.text = arBase.t0.text;
	arText.align = "center";
	TW_ColorHead(arText);

	makearef(arText, arTask.texts.Encarnacion_text);
	arText.font = "interface_normal";
	arText.base.pos.y = TW_DEF_FIRSTSTRING;
	arText.base.scale = TW_DEF_STRING_SCALE;
	arText.text = arBase.t1.text;
	TW_ColorDefault(arText);
	TW_MarkBottom("BloodLine_Encarnacion", "Encarnacion_text");

	arText = TW_SetTextCounter("BloodLine_Encarnacion", "Encarnacion_text", 1, false);
	arText.font = "interface_normal";
	arText.base.pos.y = TW_DEF_FIRSTSTRING;
	arText.base.scale = TW_DEF_STRING_SCALE;
	arText.align = "right";
	TW_ColorDefault(arText);
}

void TW_Finish_BloodLine_Encarnacion(string qName)
{
	objTask.BloodLine_Encarnacion = "";
	TW_Release();
}

//ле баск, шестой квест
void TW_Init_KeysLagoon_Maracaibo()
{
	aref arTask, arText;

	objTask.KeysLagoon_Maracaibo = "Maracaibo";
	makearef(arTask, objTask.KeysLagoon_Maracaibo);
	TW_Reset(arTask);
	aref arBase;
	makearef(arBase, arTask.base_text);
	
	arBase.t0.text = StringFromKey("Task34");
	arBase.t0.font = "interface_normal";
	arBase.t0.scale = TW_DEF_STRING_SCALE;
	
	arBase.t1.text = "0/1";
	arBase.t1.font = "interface_normal";
	arBase.t1.scale = TW_DEF_STRING_SCALE;
	arBase.t1.align = "right";

	arTask.fixWidth = true;
	makearef(arText, arTask.texts.Maracaibo_head);
	arText.font = "interface_normal";
	arText.base.pos.y = TW_DEF_HEADER;
	arText.base.scale = TW_DEF_HEADER_SCALE;
	arText.text = StringFromKey("Task31");
	arText.align = "center";
	TW_ColorHead(arText);

	makearef(arText, arTask.texts.Maracaibo_store);
	arText.font = "interface_normal";
	arText.base.pos.y = TW_DEF_FIRSTSTRING;
	arText.base.scale = TW_DEF_STRING_SCALE;
	arText.text = StringFromKey("Task32");
	TW_ColorDefault(arText);

	arText = TW_SetTextCounter("KeysLagoon_Maracaibo", "Maracaibo_store", 1, false);
	arText.font = "interface_normal";
	arText.base.scale = TW_DEF_STRING_SCALE;
	arText.base.pos.y = TW_DEF_FIRSTSTRING;
	arText.align = "right";
	TW_ColorDefault(arText);

	makearef(arText, arTask.texts.Maracaibo_prison);
	arText.font = "interface_normal";
	arText.base.pos.y = TW_DEF_FIRSTSTRING + TW_DEF_INTERVAL;
	arText.base.scale = TW_DEF_STRING_SCALE;
	arText.text = StringFromKey("Task33");
	TW_ColorDefault(arText);

	arText = TW_SetTextCounter("KeysLagoon_Maracaibo", "Maracaibo_prison", 1, false);
	arText.font = "interface_normal";
	arText.base.scale = TW_DEF_STRING_SCALE;
	arText.base.pos.y = TW_DEF_FIRSTSTRING + TW_DEF_INTERVAL;
	arText.align = "right";
	TW_ColorDefault(arText);

	makearef(arText, arTask.texts.Maracaibo_vault);
	arText.font = "interface_normal";
	arText.base.pos.y = TW_DEF_FIRSTSTRING + 2*TW_DEF_INTERVAL;
	arText.base.scale = TW_DEF_STRING_SCALE;
	arText.text = StringFromKey("Task34");
	TW_ColorDefault(arText);

	arText = TW_SetTextCounter("KeysLagoon_Maracaibo", "Maracaibo_vault", 1, false);
	arText.font = "interface_normal";
	arText.base.scale = TW_DEF_STRING_SCALE;
	arText.base.pos.y = TW_DEF_FIRSTSTRING + 2*TW_DEF_INTERVAL;
	arText.align = "right";
	TW_ColorDefault(arText);

	makearef(arText, arTask.texts.Maracaibo_jungle);
	arText.font = "interface_normal";
	arText.base.pos.y = TW_DEF_FIRSTSTRING + 3*TW_DEF_INTERVAL;
	arText.base.scale = TW_DEF_STRING_SCALE;
	arText.text = StringFromKey("Task35");
	TW_ColorDefault(arText);
	TW_MarkBottom("KeysLagoon_Maracaibo", "Maracaibo_jungle");

	arText = TW_SetTextCounter("KeysLagoon_Maracaibo", "Maracaibo_jungle", 1, false);
	arText.font = "interface_normal";
	arText.base.scale = TW_DEF_STRING_SCALE;
	arText.base.pos.y = TW_DEF_FIRSTSTRING + 3*TW_DEF_INTERVAL;
	arText.align = "right";
	TW_ColorDefault(arText);

	arTask.handlers.TW_Handler_KeysLagoon_Maracaibo = "";
}

void TW_Handler_KeysLagoon_Maracaibo(aref arTask, float dTime)
{
	//ле баск, шестой квест
	if (CheckAttribute(pchar, "questTemp.AoP.KeysLagoonMaracaibo.Store"))
		TW_IncreaseCounter("KeysLagoon_Maracaibo", "Maracaibo_store", 1);

	if (CheckAttribute(pchar, "questTemp.AoP.KeysLagoonMaracaibo.Prison"))
		TW_IncreaseCounter("KeysLagoon_Maracaibo", "Maracaibo_prison", 1);

	if (CheckAttribute(pchar, "questTemp.AoP.KeysLagoonMaracaibo.Vault"))
		TW_IncreaseCounter("KeysLagoon_Maracaibo", "Maracaibo_vault", 1);

	if (CheckAttribute(pchar, "questTemp.AoP.KeysLagoonMaracaibo.Jungle"))
		TW_IncreaseCounter("KeysLagoon_Maracaibo", "Maracaibo_jungle", 1);

	if (CheckAttribute(pchar, "questTemp.AoP.KeysLagoonMaracaibo.Completed")) return;

	if (TW_CheckCounter("KeysLagoon_Maracaibo", "Maracaibo_store"))
	{
		if (TW_CheckCounter("KeysLagoon_Maracaibo", "Maracaibo_prison"))
		{
			if (TW_CheckCounter("KeysLagoon_Maracaibo", "Maracaibo_vault"))
			{
				if (TW_CheckCounter("KeysLagoon_Maracaibo", "Maracaibo_jungle"))
				{
					pchar.questTemp.AoP.KeysLagoonMaracaibo.Completed = true;
					PostEvent("TW_Release", 1000);
					DoQuestCheckDelay("Keys_lagoon_130", 1.1);
				}
			}
		}
	}
}

void TW_Finish_KeysLagoon_Maracaibo()
{
	DeleteAttribute(&objTask, "KeysLagoon_Maracaibo.handlers");
	TW_Release();
}
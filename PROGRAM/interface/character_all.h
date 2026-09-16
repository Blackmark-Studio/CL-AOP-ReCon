// общие методы
int nCurScrollNum;
ref xi_refCharacter;
string CurTable, CurRow;
string sPerkMode = "perks";	// evganat - черты
int iSelected; // курсор в таблице
bool bAllSelf = false;
bool bAllShip = false;

void FillCharactersScroll()
{
	int i;
	string attributeName;
	string PsgAttrName;
	int _curCharIdx;
	ref _refCurChar;
	aref pRef, pRef2, pScroll;

 	DeleteAttribute(&GameInterface, "CHARACTERS_SCROLL");
	makearef(pScroll, GameInterface.CHARACTERS_SCROLL);

	nCurScrollNum = -1;
	pScroll.current = 0;
	makearef(pRef,pchar.Fellows.Passengers);

	int nOffSize = 6;

	pScroll.NotUsed = 0;

	pScroll.ImagesGroup.t0 = "EMPTYFACE";

	FillFaceList("CHARACTERS_SCROLL.ImagesGroup", pchar, 0); // officers
	FillFaceList("CHARACTERS_SCROLL.ImagesGroup", pchar, 1); // companions
	FillFaceList("CHARACTERS_SCROLL.ImagesGroup", pchar, 2); // passengers

	pScroll.BadTex1 = 0;
	pScroll.BadPic1 = "emptyface";

	int m = 0;

	attributeName = "pic" + (m+1);
	makearef(pRef2, pScroll.(attributeName));
	pRef2.character = GetCharacterIndex(pchar.id);
	pRef2.img1 = GetFacePicName(pchar);
	pRef2.tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_"+pchar.FaceID);
	pRef2.str1 = "#" + XI_ConvertString("MainCharacter");

	//Rosarak нормальное имя с титулом в интерфейсах
	if(HasSubStr(pchar.name, GlobalStringConvert("BaronTitle")))				pRef2.str2 = "#" + FindStringAfterChar(pchar.name, " ");
	else if(HasSubStr(pchar.name, GlobalStringConvert("Address_Form_Eng") + " "))       pRef2.str2 = "#" + UpperFirst(pchar.name);
	else if(HasSubStr(pchar.name, GlobalStringConvert("Address_Form_EngWoman") + " "))  pRef2.str2 = "#" + UpperFirst(pchar.name);
	else pRef2.str2 = "#" + pchar.name;

	pRef2.str3 = "#" + pchar.lastname;
	//pRef2.str4 = "#" + pchar.quest.OfficerPrice;
	pRef2.str5 = "#" + pchar.rank;

	m = m + 1;

	for(i=0; i<nOffSize;i++)
	{
		attributeName = "pic" + (m+1);
		makearef(pRef2, pScroll.(attributeName));

		PsgAttrName = GetOfficerTypeByNum(i + 1);
		pRef2.str1 = "#" + XI_ConvertString(PsgAttrName);
		_curCharIdx = sti(pRef.(PsgAttrName));
		if(_curCharIdx!=-1)
		{
			_refCurChar = GetCharacter(_curCharIdx);
			pRef2.character = _curCharIdx;
			pRef2.img1 = GetFacePicName(_refCurChar);
			pRef2.tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_"+_refCurChar.FaceID);
			pRef2.str2 = "#" + _refCurChar.name;
			pRef2.str3 = "#" + _refCurChar.lastname;
			//pRef2.str4 = "#" + Characters[_curCharIdx].quest.OfficerPrice;
			pRef2.str5 = "#" + _refCurChar.rank;
		}
		else
		{
			pRef2.character = "0";
			pRef2.img1 = "face";//"FACE128_" + PsgAttrName;
			pRef2.tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_"+PsgAttrName);
			pRef2.str2 = "#" + " ";
			pRef2.str3 = "#" + " ";
			pRef2.str4 = "#" + XI_ConvertString("not assigned");
			pRef2.str5 = "#" + " ";
		}
		m++;
	}

	for(int k=1; k<4; k++)
	{
		attributeName = "pic" + (m+1);
		makearef(pRef2, pScroll.(attributeName));
		PsgAttrName = "fighter";
		pRef2.str1 = "#" + XI_ConvertString("fighter");
		_curCharIdx = GetOfficersIndex(pchar, k);
		if(_curCharIdx!=-1)
		{
			_refCurChar = GetCharacter(_curCharIdx);
			pRef2.character = _curCharIdx;
			pRef2.img1 = GetFacePicName(_refCurChar);
			pRef2.tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_"+_refCurChar.FaceID);
			pRef2.str2 = "#" + _refCurChar.name;
			pRef2.str3 = "#" + _refCurChar.lastname;
			//pRef2.str4 = "#" + Characters[_curCharIdx].quest.OfficerPrice;
			pRef2.str5 = "#" + _refCurChar.rank;
		}
		else
		{
			pRef2.character = "0";
			pRef2.img1 = "face";//"FACE128_" + PsgAttrName;
			pRef2.tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_"+PsgAttrName);
			pRef2.str2 = "#" + " ";
			pRef2.str3 = "#" + " ";
			pRef2.str4 = "#" + XI_ConvertString("not assigned");
			pRef2.str5 = "#" + " ";
		}
		m++;
	}

	int iCompanionQuantity = GetCompanionQuantity(pchar);
	if(iCompanionQuantity > 1)
	{
		for(int n=1; n<COMPANION_MAX; n++)
		{
			_curCharIdx = GetCompanionIndex(pchar, n);
			if(_curCharIdx == -1) continue;

			attributeName = "pic" + (m+1);
			makearef(pRef2, pScroll.(attributeName));
			pRef2.str1 = "#" + XI_ConvertString("companionship");
			_refCurChar = GetCharacter(_curCharIdx);
			pRef2.character = _curCharIdx;
			pRef2.img1 = GetFacePicName(_refCurChar);
			pRef2.tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_"+_refCurChar.FaceID);
			pRef2.str2 = "#" + _refCurChar.name;
			pRef2.str3 = "#" + _refCurChar.lastname;
			/*if(CheckAttribute(_refCurChar, "quest.OfficerPrice"))
			{
				//pRef2.str4 = "#" + sti(_refCurChar.quest.OfficerPrice);
			}
			if(CheckAttribute(_refCurChar, "quest.convoyquest.money"))
			{
				//pRef2.str4 = "#" + sti(_refCurChar.quest.convoyquest.money);
			}*/
			pRef2.str5 = "#" + _refCurChar.rank;
			m++;
		}
	}

	int nPsgQty = GetPassengersQuantity(pchar);
	for(i=0; i<nPsgQty; i++)
	{
		_curCharIdx = GetPassenger(pchar, i);

		if (_curCharIdx == -1) continue;
		if (CheckAttribute(&characters[_curCharIdx], "isfree")) continue; // нужно ставить isfree для офицеров, чтоб два раза не попадали.

		attributeName = "pic" + (m+1);
		makearef(pRef2, pScroll.(attributeName));
		_refCurChar = GetCharacter(_curCharIdx);
		pRef2.character = _curCharIdx;
		pRef2.img1 = GetFacePicName(_refCurChar);
		pRef2.tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_"+_refCurChar.FaceID);
		pRef2.str2 = "#" + _refCurChar.name;
		pRef2.str3 = "#" + _refCurChar.lastname;
		pRef2.str5 = "#" + _refCurChar.rank;
		if (CheckAttribute(_refCurChar, "prisoned") && sti(_refCurChar.prisoned) == true)
		{
			//pRef2.str4 = "#" + CalculateRansomPrice(&characters[_curCharIdx]);
			pRef2.str1 = "#" + XI_ConvertString("prisonership");
		}
		else
		{
			if(CheckAttribute(_refCurChar, "Capellan"))
				pRef2.str1 = "#" + XI_ConvertString("capellan");
			else
			{
				pRef2.str1 = "#" + XI_ConvertString("passengership");
				/*if(CheckAttribute(&Characters[_curCharIdx], "quest.OfficerPrice"))
				{
					pRef2.str4 = "#" + Characters[_curCharIdx].quest.OfficerPrice;
				}
				if(CheckAttribute(&Characters[_curCharIdx], "quest.deliverymoney"))
				{
					pRef2.str4 = "#" + Characters[_curCharIdx].quest.deliverymoney;
				}*/
			}
		}
		m++;
	}
	pScroll.ListSize = m;
}

void NullSelectTable(string sControl)
{
	if (sControl == CurTable) return;

	if (CheckAttribute(&GameInterface, sControl + ".select") && sti(GameInterface.(sControl).select) == 0) return;

	GameInterface.(sControl).select = 0;
	Table_UpdateWindow(sControl);
}
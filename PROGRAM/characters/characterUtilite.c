#define FELLOWTRAVEL_NO			0
#define FELLOWTRAVEL_CAPTIVE	1
#define FELLOWTRAVEL_PASSENGER	2
#define FELLOWTRAVEL_OFFICER	3
#define FELLOWTRAVEL_COMPANION	4

#define EVENT_CHANGE_OFFICERS	"EvntChangeOfficers"
#define EVENT_CHANGE_COMPANIONS	"EvntChangeCompanions"

#define MAX_ITEM_TAKE	5000

#define MSGICON_ACTIVE_TIME 10
#define MSGICON_LEVELUP	0
#define MSGICON_LOGBOOK	1
#define MSGICON_GETITEM	2

#event_handler("evnt_MsgIconTick","proc_MsgIconTick");

bool GetShipRemovable(ref _refCharacter)
{
	if( CheckAttribute(_refCharacter,"ShipRemovable") && sti(_refCharacter.ShipRemovable) == false ) 
	{
		return false;
	}
	return true;
}

bool GetShipRemovableEx(ref _refCharacter)
{
	if(GetShipRemovable(_refCharacter) == false && _refCharacter.id != pchar.id) 
	{
		return false;
	}
	return true;
}

void SetShipRemovable(ref _refCharacter, bool bRemovable)
{
	if(bRemovable)
	{
		DeleteAttribute(_refCharacter,"ShipRemovable");
	}
	else
	{
		_refCharacter.ShipRemovable = false;
	}
}

//ugeen --> проверка, является ли персонаж глав.героем
bool IsMainCharacter(ref chr)
{
	if(CheckAttribute(chr,"chr_ai.type") && chr.chr_ai.type == LAI_TYPE_PLAYER) return true;
	if(CheckAttribute(chr,"index") && sti(chr.index) == GetMainCharacterIndex()) return true;
	return false;
}
// <-- ugeen

//
bool CharacterIsDead(ref _refCharacter)
{
	return LAi_IsDead(_refCharacter);
}

bool IsCompanion(ref _refCharacter)
{
	int findIdx = sti(_refCharacter.index);
	ref mc = GetMainCharacter();
	for(int i=0; i<COMPANION_MAX; i++)
	{
		if(GetCompanionIndex(mc,i)==findIdx) return true;
	}
	return false;
}

// аналог IsCompanion(rCharacter) только без цикла и кучи иф
bool IsCompanionOptimized(ref _refCharacter)
{
	return (sti(_refCharacter.index) == GetMainCharacterIndex()) || CheckAttribute(_refCharacter, "Payment");
}

bool IsOfficer(ref _refCharacter)
{
	int findIdx = sti(_refCharacter.index);
	ref mc = GetMainCharacter();
	for(int i = 0; i < 4; i++)
	{
		if(GetOfficersIndex(mc,i)==findIdx) return true;
	}
	return false;
}

void SetCharacterRemovable(ref _refCharacter,bool removable)
{
	if(removable) DeleteAttribute(_refCharacter,"NonRemovable");
	else _refCharacter.NonRemovable = true;
}

bool GetRemovable(ref _refCharacter)
{
	if( CheckAttribute(_refCharacter,"NonRemovable") ) return !sti(_refCharacter.NonRemovable);
	return true;
}

// KZ > обшая bool-функция проверки наличия у ГГ офицера - от капеллана и до компаньона
bool CheckOfficer(string sOff)
{
	ref rOff = RefOfficer(sOff);
	
	if (CheckAttribute(rOff, "id") && rOff.id != "none")
		return true;
	
	return false;
}

// KZ > обшая ref-функция, возвращающая ссылку на указанного офицера ГГ - от капеллана и до компаньона
ref RefOfficer(string sOff)
{
	sOff = GetStrSmallRegister(stripblank(sOff));
	
	if (!StrHasStr(sOff, "navigator,boatswain,cannoner,doctor,treasurer,carpenter,fighter1,fighter2,fighter3,capellan,companion1,companion2,companion3,companion4", true))
		return &NullCharacter;
	
	int i = sti(strcut(sOff, strlen(&sOff) - 1, strlen(&sOff) - 1));
	ref rOff;
	
	if (HasStr(sOff, "fighter"))
		return GetCharacter(GetOfficersIndex(pchar, i));
	
	if (HasStr(sOff, "companion"))
		return GetCharacter(GetCompanionIndex(pchar, i));
	
	for (i = 0; i < GetPassengersQuantity(pchar); i++)
	{
		rOff = GetCharacter(GetPassenger(pchar, i));
		
		if (CheckAttribute(rOff, sOff) && or(sti(rOff.(sOff)) == 1, sOff == "capellan"))
			return rOff;
	}
	
	return &NullCharacter;
}

// KZ > альт. IsOfficer, только сразу без ГГ
bool IsFighter(ref chr)
{
	for (int i = 1; i < 4; i++)
	{
		if (GetOfficersIndex(pchar, i) == sti(chr.index))
			return 1;
	}
	
	return 0;
}

// AlexBlade > Есть ли офицеры-абордажники у ГГ
bool CheckFighterOfficers()
{
	for (int i = 1; i < 4; i++)
	{
		if (GetOfficersIndex(pchar, i) >= 0)
			return 1;
	}

	return 0;
}

// Cargo utilites
//------------------------------------------
int GetCargoLoad(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Ship.Cargo.Load")) return 0;
	int iLoad = sti(_refCharacter.Ship.Cargo.Load);
	return iLoad;
}

int GetCargoLoadEx(ref _refCharacter, int addGoods, int iGoods)
{
	int iGoodsQ = addGoods;
	if(iGoodsQ < 0)
	{
		iGoodsQ = -iGoodsQ;
	}
	iGoodsQ = GetGoodWeightByType(iGoods, iGoodsQ);//addGoods / sti(Goods[iGoods].units);

	int iLoad;
	
	if(addGoods < 0)
	{
		iLoad = GetCargoLoad(_refCharacter) - iGoodsQ;
	}
	else
	{
		iLoad = GetCargoLoad(_refCharacter) + iGoodsQ;
	}

	return iLoad;
}

int RecalculateCargoLoad(ref _refCharacter)
{
	int loadSpace = 0;
	// boal 27/07/06 учет орудий на борту -->
	if (sti(_refCharacter.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
	{
		ref Cannon = GetCannonByType(sti(_refCharacter.Ship.Cannons.Type));
		loadSpace = GetCannonsNum(_refCharacter) * sti(Cannon.Weight);
	}
	// учет орудий на борту <--
	// ugeen --> учет веса экипажа (1 тушка члена экипажа весит 1 ц.)
	loadSpace = loadSpace + GetCrewQuantity(_refCharacter);
	// <-- учет веса экипажа
	for(int i=0; i<GOODS_QUANTITY; i++)
	{
		loadSpace = loadSpace + GetGoodWeightByType(i,GetCargoGoods(_refCharacter,i));
	}
	_refCharacter.Ship.Cargo.Load = loadSpace;
	return loadSpace;
}

int GetCargoFreeSpace(ref _refCharacter)
{
	int freeSpace = GetCargoMaxSpace(_refCharacter) - GetCargoLoad(_refCharacter);
	if (freeSpace < 0) freeSpace = 0;  // fix
	return freeSpace;
}

int GetCargoSquadronFreeSpace(ref _refCharacter)
{
	int freeSpace = GetCargoMaxSpace(_refCharacter) - GetCargoLoad(_refCharacter);
	int i, cn;
	ref chref;
	for(i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
  		if(cn != -1 && GetRemovable(&Characters[cn]))
		{
			chref = GetCharacter(cn);
			freeSpace += GetCargoMaxSpace(chref) - GetCargoLoad(chref);
		}		
	}
	if (freeSpace < 0) freeSpace = 0;  // fix
	return freeSpace;	
}

int GetCargoMaxSpace(ref _refCharacter)
{
	if( !CheckAttribute(_refCharacter,"Ship.Type") ) return 0;
	int _ShipType = sti(_refCharacter.Ship.Type);
	if( _ShipType==SHIP_NOTUSED )
		return 0;
	
	float fBonus = 1.0;
	if (CheckOfficersPerk(_refCharacter, "Packer"))
		fBonus = 1.1;
	
	return makeint(fBonus * sti(RealShips[_ShipType].Capacity));
}

int GetCharacterFreeSpace(ref _refCharacter,int _Goods)
{
	int g = GetGoodQuantityByWeight( _Goods, GetCargoFreeSpace(_refCharacter) );
	if (g < 0) g = 0; // fix
	return g;
}

int GetSquadronFreeSpace(ref _refCharacter,int _Goods)
{
	float weight = stf(Goods[_Goods].weight);
	int unitQ = sti(Goods[_Goods].Units);

	int retVal = unitQ * (GetCargoFreeSpace(_refCharacter)/weight);
	int i,cn;
	ref chref;
	for(i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
  		if(cn!=-1 && GetRemovable(&Characters[cn]))//fix грузим токо своим
		{
			chref = GetCharacter(cn);
			//if(GetShipRemovableEx(chref))
			//{
				retVal = retVal + unitQ*(GetCargoFreeSpace(chref)/weight);
			//}
		}
	}	
	if (retVal < 0) retVal = 0; // fix
	return retVal;
}

int GetCargoGoods(ref _refCharacter,int _Goods)
{
	string goodsName = Goods[_Goods].name;
	if(!CheckAttribute(_refCharacter,"Ship.Cargo.Goods."+goodsName))
		return 0;
	return sti(_refCharacter.Ship.Cargo.Goods.(goodsName));
}

int GetSquadronGoods(ref _refCharacter,int _Goods)
{
	int i,cn;
	ref chref;
	int retVal = GetCargoGoods(_refCharacter,_Goods);
	for(i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if(cn!=-1 && GetRemovable(&Characters[cn]))//fix грузим токо своим
		{
			chref = GetCharacter(cn);
			if( GetShipRemovableEx(chref) )
			{
				retVal = retVal + GetCargoGoods(chref,_Goods);
			}
		}
	}
	return retVal;
}

void SetCharacterGoods(ref _refCharacter,int _Goods,int _Quantity)
{
	makeint(&_Quantity);
	string goodsName = Goods[_Goods].name;
	_refCharacter.Ship.Cargo.Goods.(goodsName) = _Quantity;
	int curLoad = RecalculateCargoLoad(_refCharacter);
	int maxLoad = GetCargoMaxSpace(_refCharacter);
	if(curLoad>maxLoad)
	{
		Trace("ERROR! Cargo space overup (character=" + _refCharacter.index + ",Quantity=" + _Quantity + ")");
	}
}

// boal -->
int RemoveCharacterGoodsSelf(ref _refCharacter,int _Goods,int _Quantity)
{
	makeint(&_Quantity);
	int    curQuantity;
	string goodsName = Goods[_Goods].name;

	curQuantity = sti( _refCharacter.Ship.Cargo.Goods.(goodsName) );
	if (curQuantity>=_Quantity)
	{
		_refCharacter.Ship.Cargo.Goods.(goodsName) = curQuantity - _Quantity;
		RecalculateCargoLoad(_refCharacter);
		return true;
	}
	_refCharacter.Ship.Cargo.Goods.(goodsName) = 0;
	//_Quantity = _Quantity - curQuantity;
	RecalculateCargoLoad(_refCharacter);
	return false;
}
// доработал метод, теперь возвращает сколько взял
int AddCharacterGoodsSimple(aref aCharacter, int iGood, int iQuantity)
{
	makeint(&iQuantity);
	string sGoodName = Goods[iGood].name;
	int    freeQuantity;

	freeQuantity = GetGoodQuantityByWeight(iGood, GetCargoFreeSpace(aCharacter));
	if (freeQuantity < 0) freeQuantity = 0; //fix
	if (freeQuantity > iQuantity)
	{
		freeQuantity = iQuantity;
	}
	aCharacter.Ship.Cargo.Goods.(sGoodName) = sti(aCharacter.Ship.Cargo.Goods.(sGoodName)) + freeQuantity;
	RecalculateCargoLoad(aCharacter);
	return freeQuantity;
}
// boal <--

int AddCharacterGoods(ref _refCharacter,int _Goods,int _Quantity)
{
	makeint(&_Quantity);
	int i,cn,freeQuantity;
	string goodsName = Goods[_Goods].name;

	for (i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if (cn!=-1 && GetRemovable(&Characters[cn]))//fix грузим токо своим
		{
			freeQuantity = GetGoodQuantityByWeight( _Goods, GetCargoFreeSpace(&Characters[cn]) );
			if(freeQuantity>=_Quantity)
			{
				Characters[cn].Ship.Cargo.Goods.(goodsName) = sti(Characters[cn].Ship.Cargo.Goods.(goodsName)) + _Quantity;
				RecalculateCargoLoad(&Characters[cn]);
				return true;
			}
			Characters[cn].Ship.Cargo.Goods.(goodsName) = sti(Characters[cn].Ship.Cargo.Goods.(goodsName)) + freeQuantity;
			_Quantity = _Quantity - freeQuantity;
			RecalculateCargoLoad(&Characters[cn]);
		}
	}
	Trace("Overup cargo space on "+_Quantity + " id = " + _refCharacter.id);
	return false;
}

int RemoveCharacterGoods(ref _refCharacter,int _Goods,int _Quantity)
{
	makeint(&_Quantity);
	int i,cn,curQuantity;
	string goodsName = Goods[_Goods].name;

	for(i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if (cn!=-1 && GetRemovable(&Characters[cn]))//fix грузим токо своим
		{
            if (CheckAttribute(&Characters[cn], "Ship.Cargo.Goods."+goodsName)) // boal fix 230804
            {
                curQuantity = sti( Characters[cn].Ship.Cargo.Goods.(goodsName) );
    			if(curQuantity>=_Quantity)
    			{
    				Characters[cn].Ship.Cargo.Goods.(goodsName) = curQuantity - _Quantity;
    				RecalculateCargoLoad(&Characters[cn]);
    				return true;
    			}
    			Characters[cn].Ship.Cargo.Goods.(goodsName) = 0;
    			_Quantity = _Quantity - curQuantity;
    			RecalculateCargoLoad(&Characters[cn]);
			}
			else
			{
                if (MOD_BETTATESTMODE == "On") Log_TestInfo("Проверка (не критично): RemoveCharacterGoods нет груза для characterID = "+ Characters[cn].id);
			}
		}
	}
	Trace("Overup cargo space on "+_Quantity);
	return false;
}
// Cannons utilite
int GetCaracterShipCannonsType(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Ship.Cannons.Type")) return CANNON_TYPE_NONECANNON;
	return sti(_refCharacter.Ship.Cannons.Type);
}
int GetCannonQuantity(ref refCharacter)
{
	int nShipType = GetCharacterShipType(refCharacter);
	if(nShipType==SHIP_NOTUSED) return 0;
	ref rShip = GetRealShip(nShipType);
	return sti(rShip.CannonsQuantity);
}

int GetIntactCannonQuantity(ref refCharacter)
{
	int nShipType = GetCharacterShipType(refCharacter);
	if(nShipType==SHIP_NOTUSED) return 0;
	ref refBaseShip = GetRealShip(nShipType);
		
	int canQ = GetBortIntactCannonsNum(refCharacter, "fcannon", sti(refBaseShip.fcannon)) + GetBortIntactCannonsNum(refCharacter, "bcannon", sti(refBaseShip.bcannon)) + GetBortIntactCannonsNum(refCharacter, "lcannon", sti(refBaseShip.lcannon)) + GetBortIntactCannonsNum(refCharacter, "rcannon", sti(refBaseShip.rcannon));
	return canQ;
}

int GetMaximumCaliber(ref refCharacter)
{
	int nShipType = GetCharacterShipType(refCharacter);
	if(nShipType==SHIP_NOTUSED) return 0;
	ref rShip = GetRealShip(nShipType);
	return sti(rShip.MaxCaliber);
}

// Ship utilite
int GetCharacterShipType(ref _refCharacter)
{
	if(CheckAttribute(_refCharacter,"Ship.Type"))
	{
		int iShipType = sti(_refCharacter.Ship.Type);
		if(iShipType != SHIP_NOTUSED)
		{
            return iShipType;
			/*
			int iRealShipType = sti(RealShips[iShipType].basetype);
			if(iRealShipType == SHIP_BOAT)
			{
				return iShipType;
			}
			if(iRealShipType >=0 && iRealShipType < SHIP_TYPES_QUANTITY_WITH_FORT)	
			{
				return iShipType;
			} */
		}
	}
	return SHIP_NOTUSED;
}

string GetShipTypeName(ref _refCharacter)
{
	int nShipType = GetCharacterShipType(_refCharacter);
	if(nShipType==SHIP_NOTUSED) 
	{
		return SHIP_NOTUSED_TYPE_NAME;
	}

	return ShipsTypes[sti(RealShips[nShipType].basetype)].name;
}
int GetCharacterShipClass(ref _refCharacter)
{
	int nShipType = GetCharacterShipType(_refCharacter);
	if( nShipType==SHIP_NOTUSED ) return 7; // -1 неправильно, иначе сравнение врет, нет кораля - это лодка
	return sti(RealShips[nShipType].Class);
}
int GetMaxCrewQuantity(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Ship.Type")) return 0;
	int shipType = sti(_refCharacter.Ship.Type);
	if(shipType<0) return 0;
    if(shipType>=REAL_SHIPS_QUANTITY) return 0;
	return sti(RealShips[shipType].MaxCrew);
}
//boal optimal crew
int GetOptCrewQuantity(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Ship.Type")) return 0;
	int shipType = sti(_refCharacter.Ship.Type);
	if(shipType<0) return 0;
	if(shipType>=REAL_SHIPS_QUANTITY) return 0;
	return sti(RealShips[shipType].OptCrew);
}

int GetMinCrewQuantity(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Ship.Type")) return 0;
	int shipType = sti(_refCharacter.Ship.Type);
	if(shipType<0) return 0;
	if(shipType>=REAL_SHIPS_QUANTITY) return 0;
	return sti(RealShips[shipType].MinCrew);
}
int GetFreeCrewQuantity(ref _refCharacter)
{
	return (GetMaxCrewQuantity(_refCharacter)-GetCrewQuantity(_refCharacter));
}
int GetFreePartyCrewQuantity(ref _refCharacter)
{
	int cn;
	int sumCrew = 0;
	for(int i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if(cn!=-1)
		{
			sumCrew = sumCrew + GetFreeCrewQuantity(GetCharacter(cn));
		}
	}
	return sumCrew;
}
int GetCrewQuantity(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Ship.Crew.Quantity")) return 0;
	if (sti(_refCharacter.Ship.Crew.Quantity) < 0) _refCharacter.Ship.Crew.Quantity = 0; // boal FIX 21.04.05
	
	return sti(_refCharacter.Ship.Crew.Quantity);
}
int SetCrewQuantity(ref _refCharacter,int num)
{
	int maxCrew = GetMaxCrewQuantity(_refCharacter);
	if(num>maxCrew)
	{
		Trace("Error!!! Overup maximum crew quantity (character=" + _refCharacter.index + ")");
		_refCharacter.Ship.Crew.Quantity = maxCrew;
		return false;
	}
	if (num < 0) num = 0; // boal fix
	_refCharacter.Ship.Crew.Quantity = num;
	return true;
}

// --> Eddy, пусть будет пока, а то неудобно в тестах.
void SetCrewQuantityFull(ref _refCharacter)
{
	SetCrewQuantity(_refCharacter, GetMaxCrewQuantity(_refCharacter)); // переделал в мах перегруз 01/08/06 boal
}
// <-- Eddy

// boal
int SetCrewQuantityOverMax(ref _refCharacter, int num)
{
    if (num < 0) num = 0; // boal fix
    _refCharacter.Ship.Crew.Quantity = num;
	return true;
}
int AddCharacterCrew(ref _refCharacter,int num)
{
	return SetCrewQuantity(_refCharacter,GetCrewQuantity(_refCharacter)+num);
}
int RemoveCharacterCrew(ref _refCharacter,int num)
{
	int curCrew = GetCrewQuantity(_refCharacter);
	if(curCrew<num)
	{
		//Trace("Error!!! Remove overup crew (character=" + _refCharacter.index + ")");
		SetCrewQuantity(_refCharacter,0);
		return false;
	}
	SetCrewQuantityOverMax(_refCharacter,curCrew-num);//fix
	return true;
}

// Fellowtravels utilites
// работа с пассажирами
int GetPassengersQuantity(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers.Quantity")) return 0;
	return sti(_refCharacter.Fellows.Passengers.Quantity);
}

// пассажиры без пленных и квестовых boal
int GetOfficerPassengerQuantity(ref _refCharacter)
{
	ref curChar;
	int cn;
	int how = 0;
	bool ok;
	
	for (int i = 0; i < GetPassengersQuantity(_refCharacter); i++)
	{
		cn = GetPassenger(_refCharacter, i);
		if (cn < 0) break;

		curChar = GetCharacter(cn);
		ok = CheckAttribute(curChar, "prisoned") && curChar.prisoned == true;
		if (!ok && GetRemovable(curChar))
		{
   			how++;
		}
	}
	return how;
}

int GetNotCaptivePassengersQuantity(ref _refCharacter)
{
	int result, idx;
	result = 0;
	idx = 0;
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers.Quantity")) return 0;
	for (int i=0; i <sti(_refCharacter.Fellows.Passengers.Quantity); i++)
	{
		if(sti(characters[idx].prisoned) != 1)
		{
			result = result+1;
			//idx = GetNotCaptivePassenger( _refCharacter,i);
			//if (idx >0) result = result+1;
		}
	}
	return result;
}

int GetFreePassengersQuantity(ref _refCharacter)
{
	int result, idx;
	result = 0;
	idx = 0;
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers.Quantity")) return 0;
	for (int i=0; i <sti(_refCharacter.Fellows.Passengers.Quantity); i++)
	{
		idx = GetPassenger( _refCharacter,i);
		if(!CheckAttribute(&characters[idx], "isfree"))
		{
			result = result+1;
		}
		//idx = GetFreePassenger( _refCharacter,i);
		//if (idx >0) result = result+1;
	}
	return result;
}


int GetNotQuestPassengersQuantity(ref _refCharacter)
{
	int result, idx;
	bool bOk;
	
	result = 0;
	idx = 0;
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers.Quantity")) return 0;
	for (int i=0; i <sti(_refCharacter.Fellows.Passengers.Quantity); i++)
	{
		idx = GetPassenger( _refCharacter,i);
		
		bOk =  CheckAttribute(&characters[idx], "prisoned") && sti(characters[idx].prisoned) == true;
		if (!bOk && !CheckAttribute(&characters[idx], "isquest"))
		{
			result = result+1;
		}
		/*idx = GetNotCaptivePassenger( _refCharacter,i);
		if (idx >0)
		{
			idx = GetNotQuestPassenger( _refCharacter,i);
		}
		if (idx >0) result = result+1;
		*/
	}
	return result;
}

int GetNotQuestFreePassengersQuantity(ref _refCharacter)
{
	int result, idx;
	result = 0;
	idx = 0;
	bool ok;
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers.Quantity")) return 0;
	for (int i=0; i <sti(_refCharacter.Fellows.Passengers.Quantity); i++)
	{
		idx = GetPassenger( _refCharacter,i);
		if (idx >0)
		{
			ok = !CheckAttribute(&characters[idx], "prisoned") || sti(characters[idx].prisoned) != true;
			if (ok && !CheckAttribute(&characters[idx], "isquest") && !CheckAttribute(&characters[idx], "isfree"))   //TODO  isquest?
			{
				result = result+1;
			}
		}
	}
	return result;
}

int GetPassenger(ref _refCharacter,int idx)
{
	if(idx<0) return -1;
	if(idx>=GetPassengersQuantity(_refCharacter)) return -1;

	string PsgAttrName = "id"+(idx+1);
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers."+PsgAttrName)) return -1;
	return sti(_refCharacter.Fellows.Passengers.(PsgAttrName));
}

int GetPassengerEx(ref _refCharacter,int idx)
{
	if(idx < 0) 
	{
		return -1;
	}
	if(idx > GetPassengersQuantity(_refCharacter)) 
	{
		return -1;
	}
	if(idx == 0)
	{
		return nMainCharacterIndex;
	}
	string PsgAttrName = "id" + (idx);
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers."+PsgAttrName)) 
	{
		return -1;
	}
	return sti(_refCharacter.Fellows.Passengers.(PsgAttrName));
}

int GetPassengerNumber(ref _refCharacter,int findCharacterIdx)
{
	int psgQuant = GetPassengersQuantity(_refCharacter);
	int cn;
	ref cr;
	for(int i=0; i<psgQuant; i++)
	{
		cn = GetPassenger(_refCharacter,i);
		if(cn==-1) break;
		cr = GetCharacter(cn);
		if(findCharacterIdx==sti(cr.index)) return i;
	}
	return -1;
}
int GetNotCaptivePassenger(ref _refCharacter,int idx)
{
	if(idx<0) return -1;
	int psgQuant = GetPassengersQuantity(_refCharacter);

	int curIdx=0;
	ref curChar;
	int cn;
	for(int i=0;i<psgQuant;i++)
	{
		cn = GetPassenger(_refCharacter,i);
		if(cn==-1) break;

		curChar = GetCharacter(cn);
		if(CheckAttribute(curChar,"prisoned"))
		{
			if(sti(curChar.prisoned)==true) continue;
		}
		if(curIdx==idx)	return sti(curChar.index);
		curIdx++;
	}
	return -1;
}

int GetFreePassenger(ref _refCharacter,int idx)
{
	if(idx<0) return -1;
	int psgQuant = GetPassengersQuantity(_refCharacter);

	int curIdx=0;
	ref curChar;
	int cn;
	for(int i=0;i<psgQuant;i++)
	{
		cn = GetPassenger(_refCharacter,i);
		if(cn==-1) break;

		curChar = GetCharacter(cn);
		if(CheckAttribute(curChar,"isfree"))
		{
			continue;
		}
		if(curIdx==idx)	return sti(curChar.index);
		curIdx++;
	}
	return -1;
}

int GetNotQuestPassenger(ref _refCharacter,int idx)
{
	if(idx<0) return -1;
	int psgQuant = GetPassengersQuantity(_refCharacter);

	int curIdx=0;
	ref curChar;
	int cn;
	for(int i=0;i<psgQuant;i++)
	{
		cn = GetPassenger(_refCharacter,i);
		if(cn==-1) break;

		curChar = GetCharacter(cn);
		if(CheckAttribute(curChar,"isquest") || CheckAttribute(curChar,"isfree"))
		{
			continue;
		}
		if(curIdx==idx)	return sti(curChar.index);
		curIdx++;
	}
	return -1;
}

int ChangePassenger(ref _refCharacter,int idx, int psngIdx)
{
	int retVal = GetPassenger(_refCharacter,idx);
	if(idx>=0)
	{
		string PsgAttrName = "id"+(idx+1);
		_refCharacter.Fellows.Passengers.(PsgAttrName) = psngIdx;
	}
	return retVal;
}
int AddPassenger(ref _refCharacter, ref _refPassenger, int prisonFlag)
{
	ref characterRef;
	int PsgQuantity = GetPassengersQuantity(_refCharacter);
	
	if(PsgQuantity<PASSENGERS_MAX)
	{
		aref tmpRef; makearef(tmpRef,_refCharacter.Fellows.Passengers);
		string PsgAttrName;
		for(int i=0;i<PsgQuantity;i++)
		{
			PsgAttrName = "id"+(i+1);	    
			characterRef = GetCharacter(sti(tmpRef.(PsgAttrName)));					
			if(tmpRef.(PsgAttrName) == _refPassenger.index && sti(characterRef.id) == 0) return PsgQuantity;
			//if(tmpRef.(PsgAttrName) == _refPassenger.index ) return PsgQuantity;
		}
		PsgQuantity++;
		tmpRef.Quantity = PsgQuantity;
		PsgAttrName = "id"+PsgQuantity;
		tmpRef.(PsgAttrName) = _refPassenger.index;
		if(prisonFlag == true) _refPassenger.prisoned = true;
	}
	else	trace("Overup maximum passengers quantity");
	return PsgQuantity;
}
int RemovePassenger(ref _refCharacter,ref _refPassenger)
{
 	if (sti(_refCharacter.index) == GetMainCharacterIndex())
	{
		CheckForReleaseOfficer(sti(_refPassenger.index));  // boal super fix
	}
	else
	{
	    RemoveOfficersIndex(_refCharacter,sti(_refPassenger.index));
	}
	int PsgQuantity = GetPassengersQuantity(_refCharacter);
	int psgNum = GetPassengerNumber(_refCharacter,sti(_refPassenger.index));
	if(psgNum==-1) return PsgQuantity;

	aref tmpRef;
	makearef(tmpRef,_refCharacter.Fellows.Passengers);
	string inPsgAttrName,outPsgAttrName;
	for(int i=(psgNum+1); i<PsgQuantity; i++)
	{
		inPsgAttrName = "id"+i;
		outPsgAttrName = "id"+(i+1);
		tmpRef.(inPsgAttrName) = tmpRef.(outPsgAttrName);
	}

	outPsgAttrName = "id"+PsgQuantity;
	DeleteAttribute(tmpRef,outPsgAttrName);
	PsgQuantity--;
	tmpRef.Quantity = PsgQuantity;
	return PsgQuantity;
}

int FindFellowtravellers(ref _refCharacter,ref _refFindCharacter)
{
	int i;
	string stmp;
	aref atmp;
	aref curref;

	if(sti(_refFindCharacter.index)==-1) return FELLOWTRAVEL_NO;
	if(CheckAttribute(_refFindCharacter,"prisoned"))
	{
		if(sti(_refFindCharacter.prisoned)==true) return FELLOWTRAVEL_CAPTIVE;
	}
	for(i=1;i<4;i++)
	{
		if( sti(_refFindCharacter.index) == GetOfficersIndex(_refCharacter,i) )	return FELLOWTRAVEL_OFFICER;
	}
	for(i=0;i<GetPassengersQuantity(_refCharacter);i++)
	{
		if(sti(_refFindCharacter.index)==GetPassenger(_refCharacter,i))	return FELLOWTRAVEL_PASSENGER;
	}
	for(i=1;i<COMPANION_MAX;i++)
	{
		if( GetCompanionIndex(_refCharacter,i)==sti(_refFindCharacter.index) )	
		{
			return FELLOWTRAVEL_COMPANION;
		}
	}
	return FELLOWTRAVEL_NO;
}

// ==> eddy
bool CheckPassengerInCharacter(ref _refBaseChar, string _seekId)
{
	int psgQuant = GetPassengersQuantity(_refBaseChar);
    if(psgQuant<0) return false;
	int cn;
	for(int i=0;i<psgQuant;i++)
	{
		cn = GetPassenger(_refBaseChar,i);
		if(cn==-1) continue;
		if (characters[cn].id == _seekId) return true;
	}
	return false;
}

// работа с компаньонами
int SetCompanionIndex(ref _refCharacter,int _CompanionNum, int _CompanionIdx)
{
  int i;
  if(_CompanionNum == -1)
	{
		for(i = 1; i < COMPANION_MAX; i++)
		{
			if (GetCompanionIndex(_refCharacter, i) == -1)
			{
				_CompanionNum = i;
				break;
			}
		}
	}
	if(_CompanionNum < 1) return _CompanionIdx;
	if(_CompanionNum > COMPANION_MAX - 1) return _CompanionIdx;

	if(_CompanionIdx!=-1)
	{
		for(i=0;i<COMPANION_MAX;i++)
		{
			if(GetCompanionIndex(_refCharacter,i)==_CompanionIdx) return -1;
		}
	}

	string compName = "id"+_CompanionNum;
	int retVal = GetCompanionIndex(_refCharacter,_CompanionNum);
	_refCharacter.Fellows.Companions.(compName) = _CompanionIdx;

	//Character_SetCompanionEnemyEnable(&characters[_CompanionIdx], true);

	if( _CompanionIdx>=0 && CheckAttribute(&Characters[_CompanionIdx],"nation") ) {
		Characters[_CompanionIdx].prev_nation = Characters[_CompanionIdx].nation;
		Characters[_CompanionIdx].nation = _refCharacter.nation;
		Characters[_CompanionIdx].location = "none";//fix
	}
	if( retVal>=0 && CheckAttribute(&Characters[retVal],"prev_nation") ) {
		Characters[retVal].nation = Characters[retVal].prev_nation;
		Characters[retVal].location = "none"; //fix
	}

	// TODO CheckCompanionSkillsUp(_CompanionIdx);
	Event(EVENT_CHANGE_COMPANIONS,"");
	return _CompanionIdx;
}
int RemoveCharacterCompanion(ref _refCharacter, ref refCompanion)
{
	string compName;
	int i;

	aref refComps;
	makearef(refComps,_refCharacter.Fellows.Companions);
	for(i=1; i<COMPANION_MAX; i++)  // был баг к3
	{
		compName = "id"+i;
		if(CheckAttribute(refComps,compName) && refComps.(compName)==refCompanion.index)
		{
			refComps.(compName) = -1;
			refCompanion.location = "none";
			refCompanion.location.group = _refCharacter.location.group;
			refCompanion.location.locator = _refCharacter.location.locator;
			Event(EVENT_CHANGE_COMPANIONS,"");

			return i;
		}
	}
	return -1;
}
int GetCompanionIndex(ref _refCharacter,int _CompanionNum)
{
	if(_CompanionNum < 0) 
	{
		return -1;
	}
	if(_CompanionNum > (COMPANION_MAX - 1)) 
	{
		return -1;
	}
	if(_CompanionNum==0) 
	{
		if (!CheckAttribute(_refCharacter,"index"))
		{
			//Log_Info("Error GetCompanionIndex");
			return -1;
		}
		return sti(_refCharacter.index);
	}

	string compName = "id"+_CompanionNum;
	if(!CheckAttribute(_refCharacter, "Fellows.Companions."+compName)) 
	{
		return -1;
	}
	if(sti(_refCharacter.Fellows.Companions.(compName)) < 1)
	{
		return -1;
	}
	if(sti(characters[sti(_refCharacter.Fellows.Companions.(compName))].ship.type) != SHIP_NOTUSED)
	{
		return sti(_refCharacter.Fellows.Companions.(compName));
	}
	return -1;
}
int GetCompanionNumber(ref _refCharacter,int _CompanionIdx)
{
	for(int i=0; i<COMPANION_MAX; i++)
	{
		if( GetCompanionIndex(_refCharacter,i) == _CompanionIdx ) return i;
	}
	return -1;
}
int GetCompanionQuantity(ref _refCharacter)
{
	int qn = 0;
	for(int i=0; i<COMPANION_MAX; i++)
	{
		if( GetCompanionIndex(_refCharacter,i)>=0 ) qn++;
	}
	return qn;
}
// нигде не юзается
int GetRemovableCompanionsNumber(ref _refCharacter)
{
	int qn = 0;
	int cn = 1;
	for(int i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if(cn > 0 && GetShipRemovable(&characters[cn]) == true)
		{
			qn++;
		}
	}
	return qn;
}

// ==> eddy
bool CheckCompanionInCharacter(ref _refBaseChar, string _seekId)
{
	int cn;
	for(int i=0;i<COMPANION_MAX;i++)
	{
		cn = GetCompanionIndex(_refBaseChar,i);
		if(cn==-1) continue;
		if (characters[cn].id == _seekId) return true;
	}
	return false;
}

// работа с офицерами
int GetOfficersQuantity(ref _refCharacter)
{
	int idx=0;
	for(int i=1; i<4; i++)
	{
		if( GetOfficersIndex(_refCharacter,i)!=-1 ) idx++;
	}
	return idx;
}
int GetOfficersIndex(ref _refCharacter,int _OfficerNum)
{
	if(_OfficerNum<0) return -1;
	if(_OfficerNum>3) return -1;
	if(_OfficerNum==0)
    {
        if(!CheckAttribute(_refCharacter,"index")) return -1; // boal fix
        return MakeInt(_refCharacter.index);
    }

	string compName = "id"+_OfficerNum;
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers.Officers."+compName)) return -1;
	if(sti(_refCharacter.Fellows.Passengers.Officers.(compName)) < 1)
	{
		return - 1;
	}
	return sti(_refCharacter.Fellows.Passengers.Officers.(compName));
}

int SetOfficersIndex(ref _refCharacter,int _OfficerNum, int _OfficerIdx)
{
	int i;
	bool bOk = false;
    if(_OfficerNum == -1)
	{
		for(i=1; i<4; i++)	
		{
			if(GetOfficersIndex(_refCharacter, i) == -1)
			{
				_OfficerNum = i;
				break;
			}
		}
        // fix
        if (_OfficerNum == -1)
        {
            _OfficerNum = 3; // нет места?? да пофиг
        }
	}
	if(_OfficerNum<1) return _OfficerIdx;
	if(_OfficerNum>3) return _OfficerIdx;

	if(_OfficerIdx!=-1)
	{
		for(i=1;i<4;i++)
		{
			if(GetOfficersIndex(_refCharacter,i)==_OfficerIdx) return -1;
		}
		AddPassenger(_refCharacter,GetCharacter(_OfficerIdx),false);
	}

	string compName = "id"+_OfficerNum;
	int retVal = GetOfficersIndex(_refCharacter,_OfficerNum);
	_refCharacter.Fellows.Passengers.Officers.(compName) = _OfficerIdx;
	if (IsEntity(loadedLocation) && loadedLocation.id != Get_My_Cabin()
	&& loadedLocation.id != "My_Campus" && loadedLocation.id != "My_Deck_Medium") bOk = true;
	if (_OfficerIdx >= 0)
	{	//HardCoffee фикс для вызова в каюту абордажника, при его назначаении на должность абордажника, находясь в каюте
		//HardCoffee фикс назначения на должность сидячих абордажников
		if (bOk || !IsEntity(loadedLocation)) LAi_SetOfficerType(GetCharacter(_OfficerIdx));
		if (bOk) Characters[_OfficerIdx].location = _refCharacter.location;
		//фикс ломания неваляшек
		StableRolyPoly(GetCharacter(_OfficerIdx));
	}
	if ( retVal >= 0)
	{	//HardCoffee фикс для вызова в каюту абордажника, при его смещении с должности абордажника, находясь в каюте
		if (bOk || !IsEntity(loadedLocation)) Characters[retVal].location = "none";
		if (bOk && loadedLocation.id != "PortSpein_houseH3") bOk = true;
		else bOk = false; //HardCoffee фикс для снятия с должности сидячих абордажников
		if (!Characters[retVal].id == "Douglas" || !IsEntity(loadedLocation) || bOk)
			LAi_SetCitizenTypeNoGroup(GetCharacter(retVal)); // Дугласу в его доме не поменяет тип до выхода
	}
	Event(EVENT_CHANGE_OFFICERS,"");

	return retVal;
}
bool RemoveOfficersIndex(ref _refCharacter, int _OfficerIdx)
{
	if(_OfficerIdx==-1) return false;
	for(int i=1; i<4; i++)
	{
		if(GetOfficersIndex(_refCharacter,i) == _OfficerIdx)
		{
			//фикс ломания неваляшек
			StableRolyPoly(GetCharacter(_OfficerIdx));
			SetOfficersIndex(_refCharacter,i,-1);
			return true;
		}
	}
	return false;
}

void StableRolyPoly(ref chr)
{
	if (CheckAttribute(chr, "chr_ai_back"))
	{
		aref arBack, arType;
		//возвращение телесности
		SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "IsIntangible", false);
		LAi_SetImmortal(chr, false);
		IgnoreCollision(chr, false);

		//возвращение анимации
		makearef(arBack, chr.actions_back);
		makearef(arType, chr.actions);
		CopyAttributes(arType, arBack);
		EndChangeCharacterActions(chr);

		//чистка
		DeleteAttribute(chr, "chr_ai_back");
		DeleteAttribute(chr, "actions_back");
	}
}

int AddMoneyToCharacter(ref _refCharacter,int _Money)
{
	// boal -->
	if (_Money < 0 && sti(_refCharacter.Money) < abs(_Money))
	{
	    _Money = -sti(_refCharacter.Money);
	}
	// boal <--
	int newMoney = sti(_refCharacter.Money) + _Money;
	if(newMoney<0) newMoney=0;
	_refCharacter.Money = newMoney;

    //boal -->
	if (sti(_refCharacter.index) == GetMainCharacterIndex()) // флаг лога
	{
		if (_Money > 0)
		{
//			Log_Info(XI_ConvertString("GetMoney") + " " + FindMoneyString(_Money));
			Notification(XI_ConvertString("GetMoney") + " " + FindMoneyString(_Money), "Money");
			Statistic_AddValue(Pchar, "Money_get", _Money);
		}
		else
		{
		    if (_Money < 0)
			{
//				Log_Info(XI_ConvertString("SpentMoney") + " " + FindMoneyString(abs(_Money)));
				Notification(XI_ConvertString("SpentMoney") + " " + FindMoneyString(abs(_Money)), "Money");
				Statistic_AddValue(Pchar, "Money_spend", abs(_Money));
			}
		}
	}
	// boal <--
	return newMoney;
}

int AddTaxes(int _Money)
{
	if(_Money > 0)
	{
		pchar.Money = sti(pchar.Money) + _Money;
		Log_Info(XI_ConvertString("TaxRecive") + " " + FindMoneyString(_Money));
		Statistic_AddValue(Pchar, "Money_get", _Money);
	}
	
	return sti(pchar.Money);
}

void SetBaseShipData(ref refCharacter)
{
    int  i;
    aref refShip;
    int  nShipType;
    ref  refBaseShip;

	if (CheckAttribute(refCharacter,"Ship"))
	{
		if(!CheckAttribute(refCharacter, "ship.upgrades"))
		{
			refCharacter.ship.upgrades.hull = 1;
			refCharacter.ship.upgrades.sails = 1;
			refCharacter.ship.upgrades.cannons = 1;
		}
		makearef(refShip,refCharacter.Ship);
		nShipType = GetCharacterShipType(refCharacter);
		if(nShipType==SHIP_NOTUSED) return;

		//trace (refCharacter.id);
		refBaseShip = GetRealShip(nShipType);

		if(!CheckAttribute(refBaseShip, "HP"))
		{
			trace ("ship have not HP.");
			return;
		}
		
		refShip.HP = refBaseShip.HP;
		refShip.SP = refBaseShip.SP;

		refShip.Pos.x = 0;
		refShip.Pos.y = 0;
		refShip.Pos.z = 0;
		refShip.Ang = "";
/*		
		refShip.Cannons.Borts = "";
		
		if (CheckAttribute(refShip, "Cannons.Borts.cannonf.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonf.damages"); }
		if (CheckAttribute(refShip, "Cannons.Borts.cannonb.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonb.damages"); }
		if (CheckAttribute(refShip, "Cannons.Borts.cannonl.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonl.damages"); }
		if (CheckAttribute(refShip, "Cannons.Borts.cannonr.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonr.damages"); }
		
		if (CheckAttribute(refShip, "Cannons.Borts.fcannon.damages")) { DeleteAttribute(refShip, "Cannons.Borts.fcannon.damages"); }
		if (CheckAttribute(refShip, "Cannons.Borts.bcannon.damages")) { DeleteAttribute(refShip, "Cannons.Borts.bcannon.damages"); }
		if (CheckAttribute(refShip, "Cannons.Borts.lcannon.damages")) { DeleteAttribute(refShip, "Cannons.Borts.lcannon.damages"); }
		if (CheckAttribute(refShip, "Cannons.Borts.rcannon.damages")) { DeleteAttribute(refShip, "Cannons.Borts.rcannon.damages"); }
*/		
		refShip.Cannons.Charge.Type = GOOD_BALLS;

		if (!CheckAttribute(refShip,"Cannons.Type")) 
		{ 
			refShip.Cannons.Type = GetCannonByTypeAndCaliber("cannon", sti(refBaseShip.MaxCaliber));
		}

		if (!CheckAttribute(refShip,"Crew.Morale"))	
		{ 
			refShip.Crew.Morale = 20 + rand(79);	
		}
		if (!CheckAttribute(refShip,"Crew.Quantity")) 
		{ 
			refShip.Crew.Quantity = refBaseShip.OptCrew; // оптимальная команда 
		}
        
		SetGoodsInitNull(refCharacter); // boal пееренс в метод
		// новый опыт
        if(!CheckAttribute(refCharacter, "ship.crew.Exp"))
		{
			refCharacter.Ship.Crew.Exp.Sailors   = 1 + rand(80);
			refCharacter.Ship.Crew.Exp.Cannoners = 1 + rand(80);
			refCharacter.Ship.Crew.Exp.Soldiers  = 1 + rand(80);
		}
		int iGoodN = 0;
		int iGoodR = 0;

		// boal -->
		i = GetCharacterFreeSpace(refCharacter,GOOD_POWDER) / 40;
        if(i>0)
        {
			if(i>=500)
            {
				SetCharacterGoods(refCharacter,GOOD_POWDER, 500 - rand(50));
			} else
            {
				SetCharacterGoods(refCharacter,GOOD_POWDER,i);
			}
		}
		// boal <--
		// bombs		
		i = GetCharacterFreeSpace(refCharacter,GOOD_BOMBS) / 42;
		if(i>0) 
		{
			if(i > 600)
			{
				i = 600;
			}
			iGoodN = 20;
			iGoodR = rand(i - iGoodN);
			if(iGoodR < 0)
			{
				iGoodR = 0;
			}
			iGoodN = iGoodN + iGoodR;
			SetCharacterGoods(refCharacter,GOOD_BOMBS,iGoodN);
		}

		// grapes
		i = GetCharacterFreeSpace(refCharacter,GOOD_GRAPES) / 60;
		if(i>0) 
		{
			if(i > 200)
			{
				i = 200;
			}
			iGoodN = 20;
			iGoodR = rand(i - iGoodN);
			if(iGoodR < 0)
			{
				iGoodR = 0;
			}
			iGoodN = iGoodN + iGoodR;
			SetCharacterGoods(refCharacter,GOOD_GRAPES,iGoodN);
		}

		// knippels
		i = GetCharacterFreeSpace(refCharacter,GOOD_KNIPPELS) / 60;
		if(i>0) 
		{
			if(i > 200)
			{
				i = 200;
			}
			iGoodN = 20;
			iGoodR = rand(i - iGoodN);
			if(iGoodR < 0)
			{
				iGoodR = 0;
			}
			iGoodN = iGoodN + iGoodR;
			SetCharacterGoods(refCharacter,GOOD_KNIPPELS,iGoodN);
		}

		// cannonballs
		i = GetCharacterFreeSpace(refCharacter,GOOD_BALLS) / 42;
		if(i>0) 
		{
			if(i > 800)
			{
				i = 800;
			}
			iGoodN = 20;
			iGoodR = rand(i - iGoodN);
			if(iGoodR < 0)
			{
				iGoodR = 0;
			}
			iGoodN = iGoodN + iGoodR;
			SetCharacterGoods(refCharacter,GOOD_BALLS,iGoodN);
		}

		//food
		i = GetCharacterFreeSpace(refCharacter,GOOD_FOOD) / 20;
		if(i>0) 
		{
            if(i > 300)
			{
				i = 300;
			}
			iGoodN = 5;
			iGoodR = rand(i - iGoodN);
			if(iGoodR < 0)
			{
				iGoodR = 0;
			}
			iGoodN = iGoodN + iGoodR;
			SetCharacterGoods(refCharacter,GOOD_FOOD,iGoodN);
		}
		//GOOD_WEAPON
		i = GetCharacterFreeSpace(refCharacter,GOOD_WEAPON) / 60;
		if(i>0) 
		{
            if(i > 300)
			{
				i = 300;
			}
			iGoodN = 5;
			iGoodR = rand(i - iGoodN);
			if(iGoodR < 0)
			{
				iGoodR = 0;
			}
			iGoodN = iGoodN + iGoodR;
			SetCharacterGoods(refCharacter,GOOD_WEAPON,iGoodN);
		}
		//
		i = GetCharacterFreeSpace(refCharacter,GOOD_MEDICAMENT) / 100;
		if(i>0) 
		{
            if(i > 300)
			{
				i = 300;
			}
			iGoodN = 5;
			iGoodR = rand(i - iGoodN);
			if(iGoodR < 0)
			{
				iGoodR = 0;
			}
			iGoodN = iGoodN + iGoodR;
			SetCharacterGoods(refCharacter,GOOD_MEDICAMENT,iGoodN);
		}
	}
	refCharacter.ship.crew.disease = 0;
}

void SetGoodsInitNull(ref refCharacter)
{
	NullCharacterGoods(refCharacter);
}

// Warship. Нулим все товары у персонажа. Так уж получилось, что два одинаковых метода
void NullCharacterGoods(ref rChar)
{
	string sGood;
	if(!CheckAttribute(rChar, "Ship")) return;
	
	rChar.Ship.Cargo.Load = 0;
	

	for(int i=0; i<GOODS_QUANTITY; i++)
	{
		sGood = Goods[i].Name;
		rChar.Ship.Cargo.Goods.(sGood) = 0;
	}
}

// метод рудимент от к1 видимо :D
void SetBaseFellows(object refCharacter)
{
	aref tmpRef;

	makearef(tmpRef,refCharacter.Fellows.Companions);
	tmpRef.id1 = -1;
	tmpRef.id2 = -1;
	tmpRef.id3 = -1;

	makearef(tmpRef,refCharacter.Fellows.Passengers);
	tmpRef.Quantity = 0;
	tmpRef.id1 = -1;
	tmpRef.id2 = -1;
	tmpRef.id3 = -1;
	tmpRef.id4 = -1;
	tmpRef.id5 = -1;
	tmpRef.id6 = -1;
	tmpRef.id7 = -1;
	tmpRef.id8 = -1;

	makearef(tmpRef,refCharacter.Fellows.Passengers.Officers);
	tmpRef.id1 = -1;
	tmpRef.id2 = -1;
	tmpRef.id3 = -1;
}

// Items Utilite
int GetChrItemQuantity(ref _refCharacter)
{
	aref ar; makearef(ar,_refCharacter.items);
	return GetAttributesNum(ar);
}
bool GiveItem2Character(ref _refCharacter,string itemName)
{
	if ("unarmed" == itemName)
	{
		if (CheckCharacterPerk(_refCharacter, "Dignity") || CheckCharacterItem(_refCharacter, "unarmed"))
			return true; //HardCoffee не выдавать кулаки тем, кто не умеет драться и тем, у кого они уже есть
	}
		
	return TakeNItems(_refCharacter,itemName,1);
}
void TakeItemFromCharacter(ref _refCharacter,string itemName)
{
	TakeNItems(_refCharacter,itemName,-1);
}

// Warship. Просто сокращения -->
void AddItems(ref _Chr, string _ItemID, int _Num)
{
	TakeNItems(_Chr, _ItemID, _Num);
}

void RemoveItems(ref _Chr, string _ItemID, int _Num)
{
	TakeNItems(_Chr, _ItemID, -1*_Num);
}
// <-- Просто сокращения

// Warship 11.05.09 Для новой системы предметов
void GenerateAndAddItems(ref _chr, string _itemID, int _qty)
{
	int i;
	string curItemID;

	for (i = 1; i <= _qty; i++)
	{
		curItemID = GetGeneratedItem(_itemID);
		AddItems(_chr, curItemID, 1);
	}
}

// Fixed by mitrokosta
bool CheckCharacterItem(ref _refCharacter, string itemName)
{
	if(CheckAttribute(_refCharacter, "Items." + itemName) && sti(_refCharacter.Items.(itemName)) > 0) {
		return true;
	}

	ref tmpRef;
	if (IsGenerableItem(itemName))
	{
		for (int i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
		{
			tmpRef = &Items[i];
			if (CheckAttribute(tmpRef, "DefItemID"))
			{
				if (tmpRef.DefItemID == itemName)
				{
					string sItm = tmpRef.ID;
					if (CheckAttribute(_refCharacter, "Items." + sItm) && (sti(_refCharacter.Items.(sItm)) > 0))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

int GetCharacterItem(ref _refCharacter,string itemName)
{
	if(CheckAttribute(_refCharacter,"Items."+itemName))
	{
		return sti(_refCharacter.Items.(itemName));
	}
	return 0;
}

int GetCharacterFreeItem(ref _refCharacter,string itemName)
{
	if(CheckAttribute(_refCharacter,"Items."+itemName))
	{
		int iItemQ = sti(_refCharacter.Items.(itemName));
		if(IsEquipCharacterByItem(_refCharacter, itemName) || IsEquipCharacterByMap(_refCharacter, itemName))
		{
			iItemQ = iItemQ - 1;
		}
		return iItemQ;
	}
	return 0;
}


bool ReplaceItem(ref _refTakingCharacter,ref _refGivingCharacter,string itemName)
{
	bool retVal = CheckCharacterItem(_refGivingCharacter,itemName);
	if( TakeNItems(_refTakingCharacter,itemName,1) )
		TakeNItems(_refGivingCharacter,itemName,-1);
	return retVal;
}

bool TakeNItems(ref _refCharacter, string itemName, int n)
{
    return TakeNItemsNotification(_refCharacter, itemName, n, "", "", "");
}
//HardCoffee возможность добавить кастомные картинки и сообщения в лог
bool TakeNItemsNotification(ref _refCharacter, string itemName, int n, string sNotification, string sIconName, string sSound)
{
	// sNotification == "default" пропустит проверку на стоимость предмета и позволит воспроизвести сообщение, картинку и звук по умолчанию
	// если sNotification или sIconName или sSound == "" то они будут использованы по умолчанию (в том случае если предмет квестовый или sNotification == "default")
	// если sNotification == "noMessage" то в сообщении будет только звук
	// если sSound == "noSound" то в сообщении не будет звука
	int q;
	aref arItm;
	
	if (Items_FindItem(itemName, &arItm) < 0)
	{
		trace("TakeNItems warning - can't find " + itemName + " item");
		return false;
	}
	
	
	if (CheckAttribute(arItm, "gold"))
	{
		if (CheckAttribute(_refCharacter, "Money"))
		{
			q = sti(_refCharacter.Money);
		}
		else
		{
			q = 0;
		}
		
		q += n * sti(arItm.gold);
		
		if(q < 0)
		{
			q = 0;
		}
		
		_refCharacter.Money = q;
		
		return true;
	}
	
	//блокируем получения тотемов вторично
	if (n > 0 && HasSubStr(itemName, "Totem_") && GetCharacterItem(_refCharacter,itemName) > 0 && !CheckAttribute(arItm, "shown.used"))
	{
		return true;
	}
	
	if (n > 0 && HasSubStr(itemName, "map_part") && GetCharacterItem(_refCharacter,itemName) > 0)
	{
		return true;
	}
	//HardCoffee TODO: отрефакторить
	bool isQuestItem = false;
	if (sNotification == "default") isQuestItem = true;
	// Warship. Для нового интерфейса обмена - проверка на золото
	if (!isQuestItem) isQuestItem = sNotification == "" && CheckAttribute(arItm, "price") && sti(arItm.price) == 0 && arItm.ID != "Gold"
		&& CheckAttribute(_refCharacter,"index") && sti(_refCharacter.index) == GetMainCharacterIndex() && IsEntity(_refCharacter);

	if (isQuestItem)
	{
		if (n > 0)
		{
			if (pchar.chr_ai.type == "player" && !LAi_IsDead(pchar))
			{
				if (sNotification == "" || sNotification == "default")
				{
					sNotification = XI_ConvertString("You take item")+": "+GetConvertStr(arItm.name, "ItemsDescribe.txt");
					if (n > 1)
						sNotification = sNotification +" (" +n +" " +XI_ConvertString("pcs") +")";
				}

				if (sIconName == "")
					sIconName = "BoxPlus";
			}

			AddMsgToCharacter(_refCharacter, MSGICON_GETITEM);
		}
		else if (n < 0)
		{
			if (dialogrun)
			{
				if (sNotification == ""|| sNotification == "default")
				{
					sNotification = XI_ConvertString("You give item")+": "+GetConvertStr(arItm.name, "ItemsDescribe.txt");
					if (n < -1)
						sNotification = sNotification +" (" +abs(n) +" " +XI_ConvertString("pcs") +")";
				}

				if (sIconName == "")
					sIconName = "BoxMinus";
			}
		}
		if (sSound == "")
			sSound = "interface\important_item.wav";
	}
	
	q = GetCharacterItem(_refCharacter, itemName);
	
	if(q + n <= 0)
	{
		DeleteAttribute(_refCharacter, "Items." + itemName);
	}
	else
	{
		if(q <= 0 && GetChrItemQuantity(_refCharacter) >= MAX_ITEM_TAKE)
		{
			return false;
		}
		
		_refCharacter.Items.(itemName) = q + n;
	}

    if (sNotification != "" && sNotification != "default" && sNotification != "noMessage")
		notification(sNotification, sIconName);
	if (sSound != "" && sSound != "noSound")
		notificationSound = PlayStereoSound(sSound);
	return true;
}

// > методы из CSP
int GetCharacterItemCabin(ref _refCharacter,string itemName,bool ignore, bool onlycabin)
{
	int qty = 0;
	if (!onlycabin)
	{
		if(CheckAttribute(_refCharacter,"Items."+itemName))	qty = qty + sti(_refCharacter.Items.(itemName));
		if (Get_My_Cabin() == "" || or(!ignore, loadedLocation.id != Get_My_Cabin()) || !CheckAttribute(&locations[FindLocation(Get_My_Cabin())], "box1")) return qty;
	}
	aref chests;
	int i, chestsnum = CheckCabinBoxes(&locations[FindLocation(Get_My_Cabin())]);
	string sBox;
	for(i = 1; i <= chestsnum; i++)
	{
		sBox = "box"+i;
		makearef(chests,locations[FindLocation(Get_My_Cabin())].(sBox));
		if(CheckAttribute(chests,"Items."+itemName))
		{
			qty = qty + sti(chests.Items.(itemName));
		}
	}
	return qty;
}

void TakeNItemsCabin(ref _refCharacter,string itemName,int quant, bool onlycabin)
{
	int qty = quant;
	if(!onlycabin && CheckAttribute(_refCharacter,"Items."+itemName) && sti(_refCharacter.Items.(itemName)) != 0)
	{
		if (sti(_refCharacter.Items.(itemName)) >= -qty) 
		{
			TakeNItems(_refCharacter,itemName,qty);
			return;
		}
		else 
		{
			qty += sti(_refCharacter.Items.(itemName));
			TakeNItems(_refCharacter,itemName,-sti(_refCharacter.Items.(itemName)));
			
			
		}
	}
	aref chests;
	ref rItem;
	int i, chestsnum = CheckCabinBoxes(locations[FindLocation(Get_My_Cabin())]);
	string sBox;
	for(i = 1; i <= chestsnum; i++)
	{
		sBox = "box"+i;
		makearef(chests,locations[FindLocation(Get_My_Cabin())].(sBox));
		if(CheckAttribute(chests,"Items."+itemName) && sti(chests.Items.(itemName)) != 0)
		{
			rItem = ItemsFromID(itemName);
			if (sti(chests.Items.(itemName)) >= -qty)
			{
				TakeNItems(chests,itemName,qty);
				return;
			}
			else 
			{
				qty += sti(chests.Items.(itemName));
				TakeNItems(chests,itemName,-sti(chests.Items.(itemName)));
			}
		}
	}
}

int CheckCabinBoxes(ref loca)
{
	int i, qty = 0;
	for(i = 1; i <= 4; i++)
	{
		if (CheckAttribute(loca,"box"+i)) qty++;
	}
	return qty;
}
// < методы из CSP

void SetRandomNameToCharacter(ref rCharacter)
{
	int iNation = sti(rCharacter.nation);
	if (iNation == -1) iNation = PIRATE;
	while (iNation == PIRATE) { iNation = rand(MAX_NATIONS - 2); }
	
	ref rNames, rLastNames;
    // fix -->
    rNames = &sEnManNames;
	if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sEnWomenNames;
	rLastNames = &sEnFamilies;
	// fix <--
	switch(iNation)
	{
		case ENGLAND:
			rNames = &sEnManNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sEnWomenNames;
			rLastNames = &sEnFamilies;
		break;
		case FRANCE:
			rNames = &sFrManNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sFrWomenNames;
			rLastNames = &sFrFamilies;
		break;
		case SPAIN:
			rNames = &sSpManNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sSpWomenNames;
			rLastNames = &sSpFamilies;
		break;
		case HOLLAND:
			rNames = &sHoManNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sHoWomenNames;
			rLastNames = &sHoFamilies;
		break;
		case PIRATE:
			rNames = &sEnManNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sEnWomenNames;
			rLastNames = &sEnFamilies;
		break;
	}
	
	// AlexBlade - Драуграм выдаем викингские имена
	if(CheckAttribute(rCharacter, "model") && StrStartsWith(rCharacter.model, "draugr"))
	{
		string _vName, _vLastname;
		GetVikingName(&_vName, &_vLastname);
		rCharacter.name = _vName;
		rCharacter.lastname = _vLastname;
		return;
	}

	rCharacter.name = GetRandSubString(rNames[rand(GetArraySize(rNames) - 2)]);
	rCharacter.lastname = GetRandSubString(rLastNames[rand(GetArraySize(rLastNames) - 2)]);
}

string GenerateRandomName(int iNation, string sSex)
{
	if (iNation == -1) iNation = PIRATE;
	while (iNation == PIRATE) { iNation = rand(MAX_NATIONS - 2); }
	
	ref rNames, rLastNames;

	switch(iNation)
	{
		case ENGLAND:
			rNames = &sEnManNames;
			if (sSex != "man") rNames = &sEnWomenNames;
			rLastNames = &sEnFamilies;
		break;
		case FRANCE:
			rNames = &sFrManNames;
			if (sSex != "man") rNames = &sFrWomenNames;
			rLastNames = &sFrFamilies;
		break;
		case SPAIN:
			rNames = &sSpManNames;
			if (sSex != "man") rNames = &sSpWomenNames;
			rLastNames = &sSpFamilies;
		break;
		case HOLLAND:
			rNames = &sHoManNames;
			if (sSex != "man") rNames = &sHoWomenNames;
			rLastNames = &sHoFamilies;
		break;
		case PIRATE:
			rNames = &sEnManNames;
			if (sSex != "man") rNames = &sEnWomenNames;
			rLastNames = &sEnFamilies;
		break;
	}

	string sname = GetRandSubString(rNames[rand(GetArraySize(rNames) - 2)]);
	string slastname = GetRandSubString(rLastNames[rand(GetArraySize(rLastNames) - 2)]);
	
	sname = sname + " " + slastName;
	return sName;
}

void SetRandomNameToCharacter_Generator(ref rCharacter)
{
	int iNation = sti(rCharacter.nation);
	if (iNation == -1) iNation = PIRATE;
	while (iNation == PIRATE) { iNation = rand(MAX_NATIONS - 2); }
	
	ref rNames, rLastNames;
    // fix -->
    rNames = &sEnManGenNames;
	if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sEnWomenGenNames;
	rLastNames = &sEnGenFamilies;
	// fix <--
	switch(iNation)
	{
		case ENGLAND:
			rNames = &sEnManGenNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sEnWomenGenNames;
			rLastNames = &sEnGenFamilies;
		break;
		case FRANCE:
			rNames = &sFrManGenNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sFrWomenGenNames;
			rLastNames = &sFrGenFamilies;
		break;
		case SPAIN:
			rNames = &sSpManGenNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sSpWomenGenNames;
			rLastNames = &sSpGenFamilies;
		break;
		case HOLLAND:
			rNames = &sHoManGenNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sHoWomenGenNames;
			rLastNames = &sHoGenFamilies;
		break;
		case PIRATE:
			rNames = &sEnManGenNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sEnWomenGenNames;
			rLastNames = &sEnGenFamilies;
		break;
	}

	rCharacter.name = GetRandSubString(rNames[rand(GetArraySize(rNames) - 2)]);
	rCharacter.lastname = GetRandSubString(rLastNames[rand(GetArraySize(rLastNames) - 2)]);
}

string GenerateRandomName_Generator(int iNation, string sSex)
{
	if (iNation == -1) iNation = PIRATE;
	while (iNation == PIRATE) { iNation = rand(MAX_NATIONS - 2); }
	
	ref rNames, rLastNames;

	switch(iNation)
	{
		case ENGLAND:
			rNames = &sEnManGenNames;
			if (sSex != "man") rNames = &sEnWomenGenNames;
			rLastNames = &sEnGenFamilies;
		break;
		case FRANCE:
			rNames = &sFrManGenNames;
			if (sSex != "man") rNames = &sFrWomenGenNames;
			rLastNames = &sFrGenFamilies;
		break;
		case SPAIN:
			rNames = &sSpManGenNames;
			if (sSex != "man") rNames = &sSpWomenGenNames;
			rLastNames = &sSpGenFamilies;
		break;
		case HOLLAND:
			rNames = &sHoManGenNames;
			if (sSex != "man") rNames = &sHoWomenGenNames;
			rLastNames = &sHoGenFamilies;
		break;
		case PIRATE:
			rNames = &sEnManGenNames;
			if (sSex != "man") rNames = &sEnWomenGenNames;
			rLastNames = &sEnGenFamilies;
		break;
	}

	string sname = GetRandSubString(rNames[rand(GetArraySize(rNames) - 2)]);
	string slastname = GetRandSubString(rLastNames[rand(GetArraySize(rLastNames) - 2)]);
	
	sname = sname + " " + slastName;
	return sName;
}

// Количество имен в группе
int GetNamesCount(string _nameType)
{
	aref typeNames;
	makearef(typeNames, Names.Pirates.(_nameType));
	
	return GetAttributesNum(typeNames);
}

// Случайное имя из определённой группы в определённом падеже
string GetRandName(string _nameType, string _case)
{
	string nameId;
	
	nameId = "l" + rand(GetNamesCount(_nameType) - 1);
	
	return GetName(_nameType, nameId, _case);
}

string GetIndianName(int Sex) //Jason имена индейцев
{
	string nameid;

	if (Sex == MAN) nameid = "l" + rand(99);
	else nameid = "l" + (100+rand(68));

	return Names.Indian.(nameId);
}

void GetVikingName(string name, string lastname) //AlexBlade имена викингов (по квесту Лейф Счастливый)
{
	string nameid;

	nameid = "l" + rand(19);
	name = Names.Viking.(nameId);
	nameid = "l" + (49+rand(19));
	lastname = Names.Viking.(nameId);
}

// Вернёт имя из группы с указаным Id и в указанном падеже
string GetName(string _nameType, string _nameId, string _nameCase)
{
	return Names.Pirates.(_nameType).(_nameId).(_nameCase);
}

// Вернёт указанное имя в другом падеже, поиск по именам группы _nameType
string ChangeNameCaseEx(string _nameType, string _name, string _fromCase, string _toCase)
{
	aref typeNames;
	string nameId;
	
	makearef(typeNames, Names.Pirates.(_nameType));
	
	for(int i = 0; i < GetAttributesNum(typeNames); i++)
	{
		nameId = "l" + i;
		
		if(GetName(_nameType, nameId, _fromCase) == _name)
		{
			return GetName(_nameType, nameId, _toCase);
		}
	}
	
	return "";
}

// Тоже самое, что и выше, только меньше параметров - ищет само
string ChangeNameCase(string _nameType, string _name, string _toCase)
{
	aref typeNames;
	string nameId;
	
	makearef(typeNames, Names.Pirates.(_nameType));
	
	for(int i = 0; i < GetAttributesNum(typeNames); i++)
	{
		nameId = "l" + i;
		
		if(GetName(_nameType, nameId, NAME_NOM) == _name || GetName(_nameType, nameId, NAME_GEN) == _name || GetName(_nameType, nameId, NAME_DAT) == _name ||
			GetName(_nameType, nameId, NAME_ACC) == _name || GetName(_nameType, nameId, NAME_INS) == _name || GetName(_nameType, nameId, NAME_PRE) == _name)
		{
			return GetName(_nameType, nameId, _toCase);
		}
	}
	
	return "";
}

//=============================================================================
//  EQUIP SECTION
//=============================================================================
string ForceFindCharacterItemByGroup(ref rChr, string groupID)
{
	aref arCurItem, arItem, arItems; makearef(arItems, rChr.items);
	int i, q = GetAttributesNum(arItems);

	for (i = 0; i < q; i++)
	{
		arCurItem = GetAttributeN(arItems, i);

		if (Items_FindItem(GetAttributeName(arCurItem), &arItem) >= 0)
		{
			if (!CheckAttribute(arItem, "groupID")) continue;
			if (arItem.groupID != groupID) continue;
			if (!CheckAttribute(rChr, "items." + arItem.id)) continue;
			return arItem.id;
		}
	}

	return "";
}

string FindCharacterItemByGroup(ref chref, string groupID)
{
	ref rGun;
	float  maxBladeValue, curBladeValue;
	string resultItemId, sAmmo, sGun;
	bool bMushket, bPistol, MushOfficer = CheckAttribute(chref, "MushForever");

	// Мушкетёры не берут лишнего
	if (MushOfficer && groupID != CIRASS_ITEM_TYPE && groupID != MUSKET_ITEM_TYPE) return "";

	// Офицерам даём кулаки (а у мушкетёров ретёрн выше)
	if (groupID == BLADE_ITEM_TYPE && IsOfficer(chref) && IsEquipCharacterByItem(chref, "unarmed"))
	{
		RemoveCharacterEquip(chref, BLADE_ITEM_TYPE);
		TakeItemFromCharacter(chref, "unarmed");
	}

	maxBladeValue = 0;
	resultItemId  = "";

	aref arCurItem, arItem, arItems; makearef(arItems, chref.items);
	int i, iCharges, q = GetAttributesNum(arItems);

	for (i = 0; i < q; i++)
	{
		arCurItem = GetAttributeN(arItems, i);

		if (Items_FindItem(GetAttributeName(arCurItem), &arItem) >= 0)
		{
			if (!CheckAttribute(arItem, "groupID")) continue;
			if (arItem.groupID != groupID) continue;
			if (!CheckAttribute(chref, "items." + arItem.id)) continue;

			bMushket = (groupID == MUSKET_ITEM_TYPE);
			bPistol  = (groupID == GUN_ITEM_TYPE);
			if (bMushket || bPistol)
			{
				//Заглушки, чтобы не портило подбор оружия -->
				if (bMushket)
				{
					if (!MushOfficer) continue;
					if (!IsCharacterPerkOn(chref, "MusketsTraining")) continue;
					if (arItem.id == "mushket_H2" && !IsCharacterPerkOn(chref, "GunProfessional")) continue;
					if (arItem.id == "mushket2x2" && chref.id != "Douglas") continue;
				}
				else if (MushOfficer) continue;
				//<-- Заглушки, чтобы не портило подбор оружия

				iCharges = sti(arItem.chargeQ);
				sAmmo = arItem.chargetype;

				if (sGun == "") // 1 раз гет
					sGun = GetCharacterEquipByGroup(chref, groupID);
				if (sGun != "")
				{
					rGun = ItemsFromID(sGun);
					if (sAmmo != rGun.chargetype && GetGunCharges(chref, rGun.id) > 0 && GetGunCharges(chref, arItem.id) < 1)
						continue;
				}

				if (HasStrEx(sAmmo, "grape,echin", "|") && !IsCharacterPerkOn(chref, "Gunman")) continue;
				if (or(iCharges == 2 && !IsCharacterPerkOn(chref, "GunAdvanced"), iCharges > 2 && !IsCharacterPerkOn(chref, "GunProfessional"))) continue;

				return arItem.id;
			}

			if (groupID == CIRASS_ITEM_TYPE)
			{
				if (IsCharacterPerkOn(chref, "Ciras")) return arItem.id;
				continue;
			}

			// перебор на лучшую саблю
			if (groupID == BLADE_ITEM_TYPE)
			{
				// формула лучшего выбора
				curBladeValue = (stf(arItem.dmg_min) * 3 + (stf(arItem.dmg_max) * GetCharacterSkill(chref, arItem.FencingType)) / SKILL_MAX) / GetEnergyBladeDrain(stf(arItem.Weight));// + stf(arItem.piercing) + stf(arItem.block);
				if (curBladeValue > maxBladeValue)
				{
					maxBladeValue = curBladeValue;
					resultItemId  = arItem.id;
				}
			}
			else
			{
				return arItem.id;
			}
		}
	}

	if (resultItemId != "")
	{
		return resultItemId;
	}

	// Офицерам даём кулаки (а у мушкетёров ретёрн выше)
	if (groupID == BLADE_ITEM_TYPE && IsOfficer(chref) && sti(chref.index) != GetMainCharacterIndex())
		ItemTakeEquip(chref, "unarmed", 0);

	return "";  //ничего не делать далее
}

bool IsEquipCharacterByItem(ref chref, string itemID)
{
	aref arEquip;
	makearef(arEquip,chref.equip);
	int q = GetAttributesNum(arEquip);
	for(int i=0; i<q; i++)
	{	if(GetAttributeValue(GetAttributeN(arEquip,i))==itemID) return true;
	}
	return false;
}

// ugeen. проверяем, есть ли карта в атласе
bool IsEquipCharacterByMap(ref chref, string itemID)
{
	aref arEquip;
	string groupID = MAPS_ITEM_TYPE;
	
	makearef(arEquip,chref.equip.(groupID));
	int q = GetAttributesNum(arEquip);
	for(int i=0; i<q; i++)
	{	
		if(GetAttributeValue(GetAttributeN(arEquip,i))==itemID) return true;
	}
	
	return false;
}

// получить суммарный вес экипированных предметов в зависимости от группы -> нужно для атласа карт
float GetEquippedItemsWeight(ref chref, string groupID)
{
	aref arCurItem, arItem, arItems; makearef(arItems, chref.items);
	int j, q = GetAttributesNum(arItems);
	float fEquipWeight = 0.0;
	string itemID;

	for (j = 0; j < q; j++)
	{
		arCurItem = GetAttributeN(arItems, j);

		if (Items_FindItem(GetAttributeName(arCurItem), &arItem) >= 0)
		{
			if (CheckAttribute(arItem, "ID"))
			{
				itemID = arItem.id;

				if (groupID == MAPS_ITEM_TYPE)
				{	
					if (!CheckAttribute(arItem, "mapSpecial"))
					{
						if (CheckAttribute(chref, "items." + itemID) && IsEquipCharacterByMap(chref, itemID))
						{
							fEquipWeight += stf(arItem.Weight);
						}
					}
				}
				else
				{
					if (CheckAttribute(chref, "items." + itemID) && IsEquipCharacterByItem(chref, itemID))
					{
						fEquipWeight += stf(arItem.Weight);
					}
				}
			}
		}
	}

	return fEquipWeight;
}
// <-- ugeen

string GetCharacterEquipByGroup(ref chref, string groupID)
{
	if( CheckAttribute(chref,"equip."+groupID) ) return chref.equip.(groupID);
	return "";
}

string GetCharacterEquipPictureByGroup(ref chref, string groupID)
{
	aref arCurItem, arItem, arItems; makearef(arItems, chref.items);
	int i, q = GetAttributesNum(arItems);
	string sItem = GetCharacterEquipByGroup(chref, groupID);

	for (i = 0; i < q; i++)
	{
		arCurItem = GetAttributeN(arItems, i);

		if (Items_FindItem(GetAttributeName(arCurItem), &arItem) >= 0)
		{
			if (CheckAttribute(arItem, "ID") && arItem.id == sItem)
			{
				if (arItem.id == "spyglass5")
				{
					arItem.picIndex = 4;
				}

				return groupID + arItem.picIndex;
			}
		}
	}

	return "";
}

void RemoveCharacterEquip(ref chref, string groupID)
{
	DeleteAttribute(chref,"equip."+groupID);
	SetEquipedItemToCharacter(chref,groupID,"");
	if (groupID == BLADE_ITEM_TYPE && !CheckCharacterPerk(chref, "Dignity")) //HardCoffee при снятии сабли выдадим кулаки
	{
		if (!CheckAttribute(chref, "questTemp.CapBloodLine") || chref.questTemp.CapBloodLine != true)
		{
			GiveItem2Character(chref, "unarmed");
			EquipCharacterByItem(chref, "unarmed");
		}
	}
	SetNewModelToChar(chref);
}

void RemoveOfficerEquip(ref chref, string groupID)
{
	string sItemID = chref.equip.(groupid);

	DeleteAttribute(chref,"equip."+groupID);
	SetEquipedItemToCharacter(chref,groupID,"");
	if (groupID == BLADE_ITEM_TYPE && !CheckCharacterPerk(chref, "Dignity"))
	{	//HardCoffee при снятии сабли выдадим кулаки
		GiveItem2Character(chref, "unarmed");	
		EquipCharacterByItem(chref, "unarmed");
	}
	TakeItemFromCharacter(chref, sItemID);
	GiveItem2Character(pchar, sItemID);
	SetNewModelToChar(chref);
}

void SetEquipedItemToCharacter(ref chref, string groupID, string itemID)
{
	object emptyItm;
	aref arItm;
	string modelName = "";
	makearef(arItm,emptyItm);
 	int itemNum; // boal 23.01.2004
	bool bEquip = (itemID != "");

	if (bEquip)
	{
		if (!CheckCharacterItem(chref,itemID)) return;
		itemNum = Items_FindItem(itemID, &arItm); // boal 23.01.2004
	}

	switch (groupID)
	{
		case AMMO_ITEM_TYPE:
			if (CheckAttribute(arItm, "id"))
            {
                if (CharUseMusket(chref)) LAi_SetCharacterUseBullet(chref, MUSKET_ITEM_TYPE, arItm.id); 
                else LAi_SetCharacterUseBullet(chref, GUN_ITEM_TYPE, arItm.id); 
            }
        break;

		case SPYGLASS_ITEM_TYPE:
			if(CheckAttribute(arItm,"id"))
			{
				SetTelescopeInitParameters(arItm);
			}
		break;

		case CIRASS_ITEM_TYPE:
			if (CheckAttribute(chref, "HeroModel")) // все, у кого есть что одеть
			{
				if (CheckAttribute(arItm, "model"))
				{
					if (arItm.model == "protocusto") // ГПК - надеваем скафандр
					{
						chref.model = arItm.model;
					}
					else
					{
						chref.model = GetSubStringByNum(chref.HeroModel, sti(arItm.model));
						if (!IsMainCharacter(chref) && IsMusketer(chref))
                            chref.model = chref.model + "_mush";
					}
					chref.cirassId = itemNum;
				}
				else
				{
					chref.model = GetSubStringByNum(chref.HeroModel, 0);
					DeleteAttribute(chref, "cirassId");
					if (!IsMainCharacter(chref) && IsMusketer(chref))
						chref.model = chref.model + "_mush";
				}
			}
			else
			{
				// тут анализ модели офицера или пирата
				if(CheckAttribute(arItm, "model"))
				{
					chref.cirassId = itemNum;
				}
				else
				{
					DeleteAttribute(chref, "cirassId");
				}
			}
			SetNewModelToChar(chref);//boal
		break;

		case PATENT_ITEM_TYPE:
			if(CheckAttribute(arItm,"quest"))
			{
				DoQuestCheckDelay(arItm.quest, 1.0);
				chref.EquipedPatentId = itemNum; // boal текущий патент
			}
			else
			{
				DeleteAttribute(chref, "EquipedPatentId");
			}
		break;

		case GUN_ITEM_TYPE:
            if(CheckAttribute(arItm, "model")) modelName = arItm.model;
			SendMessage(chref, "ls", MSG_CHARACTER_SETGUN, modelName);
			SetGunParameters(chref, GUN_ITEM_TYPE, itemID, bEquip);
        break;

		case MUSKET_ITEM_TYPE:
			if(CheckAttribute(arItm,"model")) modelName = arItm.model;
			MusketEquipOldLogic(chref, modelName, bEquip);
			SetGunParameters(chref, MUSKET_ITEM_TYPE, itemID, bEquip);
		break;

		case BLADE_ITEM_TYPE:
			float liveTime = 0.1;
			int colors = argb(64, 64, 64, 64);
			int colore = argb(0, 32, 32, 32);
			if(CheckAttribute(arItm,"model")) modelName = arItm.model;
			if(CheckAttribute(arItm, "blade.time")) liveTime = stf(arItm.blade.time);
			if(CheckAttribute(arItm, "blade.colorstart")) colors = sti(arItm.blade.colorstart);
			if(CheckAttribute(arItm, "blade.colorend")) colore = sti(arItm.blade.colorend);
			SendMessage(chref, "llsfll", MSG_CHARACTER_SETBLADE, 0, modelName, liveTime, colors, colore);

			if (CheckAttribute(arItm,"FencingType")) //boal
				LAi_BladeFencingType(chref, arItm.FencingType);
			else
				LAi_BladeFencingType(chref, "Fencing");

			if(CheckAttribute(arItm,"Weight")) //eddy.при загрузки локации если у ГГ нет оружия - ошибка
			{
				LAi_BladeEnergyType(chref, GetEnergyBladeDrain(stf(arItm.Weight)) );  // энергоемкость от веса
			}
		break;
	}
}

void SetGunParameters(ref chref, string sType, string itemID, bool bEquip)
{
	if(bEquip)
	{
		if(CheckAttribute(chref,"chr_ai." + sType + ".sGun") && itemID == chref.chr_ai.(sType).sGun)
		{
			if(CheckAttribute(chref,"chr_ai." + sType + ".bullet"))
			{
				LAi_SetCharacterUseBullet(chref, sType, chref.chr_ai.(sType).bullet);
			}
			else
			{
				LAi_SetCharacterDefaultBulletType(chref, sType);
				LAi_GunSetUnload(chref, sType);
			}
		}
		else
		{
			LAi_SetCharacterDefaultBulletType(chref, sType);
			LAi_GunSetUnload(chref, sType);
		}
	}
	else
	{
        DeleteAttributeMass(chref, "chr_ai." + sType, "sGun,bullet,charge_max,chargeprc");
        DeleteAttributeMass(chref, "chr_ai." + sType, "shards,width,height"); // ,basedmg
        if (sType == MUSKET_ITEM_TYPE && CheckAttribute(chref, "PriorityMode")) chref.PriorityMode = 1; //Сброс на сабельный
	}	
}

void MusketEquipOldLogic(ref chref, string modelName, bool bEquip)
{
    if (IsMainCharacter(chref))
    {
		SendMessage(chref, "ls", MSG_CHARACTER_SETMUS, modelName);
		return;
    }

	/*if (IsOfficer(chref))
	{
		if (!IsMainCharacter(chref))
		{
			if (CheckAttribute(chref, "PriorityMode"))
			{
				SendMessage(chref, "lsl", MSG_CHARACTER_EX_MSG, "SetMusketer", sti(chref.PriorityMode) == 2);
			}
			else SendMessage(chref, "lsl", MSG_CHARACTER_EX_MSG, "SetMusketer", bEquip);
		}
		SendMessage(chref, "ls", MSG_CHARACTER_SETMUS, modelName);
		return;
	}*/

	if (!bEquip)
	{
		if (CheckAttribute(chref, "equip.gun"))
		{
			aref arItm;
			Items_FindItem(chref.equip.gun, &arItm);
			modelName = arItm.model;
		}
		if (chref.model.animation == "mushketer")
		{
			chref.model = FindStringBeforeChar(chref.model, "_mush");
			chref.model.animation = "man"; //Можно и через резерв
		}
	}
	else
	{
		if (chref.model.animation != "mushketer")
		{
			chref.model = chref.model + "_mush";
			chref.model.animation = "mushketer";
		}
	}

	SendMessage(chref, "lss", MSG_CHARACTER_SETMODEL, chref.model, chref.model.animation);
	SendMessage(chref, "lsl", MSG_CHARACTER_EX_MSG, "SetMusketer", bEquip); //Флаг в движок на мушкетёрский ИИ
	SendMessage(chref, "ls",  MSG_CHARACTER_SETGUN, modelName);
}

// коэф траты энергии от веса сабли
float GetEnergyBladeDrain(float _weight)
{
	return _weight / 9.0 + 0.4;
}

void EquipCharacterByItem(ref chref, string itemID)
{
	if (itemID == "") return;
	if ("unarmed" == itemID && CheckCharacterPerk(chref, "Dignity")) return; //HardCoffee не умеющие драться не могут одеть кулаки
	aref arItm;

	if (!CheckCharacterItem(chref, itemID)) return;
	if (Items_FindItem(itemID, &arItm) < 0) return;
	if (!CheckAttribute(arItm, "groupID")) return;

	string groupName = arItm.groupID;

	if (groupName == BLADE_ITEM_TYPE && CheckAttribute(chref, "DontChangeBlade")) return;
	if (or(groupName == GUN_ITEM_TYPE, groupName == MUSKET_ITEM_TYPE) && CheckAttribute(chref, "DontChangeGun")) return;
	if (itemID == "mushket2x2" && chref.id != "Douglas") return;

	if (groupName != MAPS_ITEM_TYPE) // ugeen - для атласа карт  18.06.09
	{
		string oldItemID = GetCharacterEquipByGroup(chref, groupName);
		if(oldItemID == itemID) return;
	}

	if (HasSubStr(chref.model.animation, "mushketer"))
	{
		if (groupName == BLADE_ITEM_TYPE && itemID != "unarmed") return;
        if (groupName == MUSKET_ITEM_TYPE)
        {
            if (chref.id == "Douglas" && itemID != "mushket2x2") return;
        }
	}

	if (groupName != MAPS_ITEM_TYPE) // ugeen  18.06.09
	{
	    //проверка на то какое оружие снимаем\одеваем для того что бы понять надо ли перезагружать анимации
        //если меняем кулаки на другое оружие, то анимацию надо перезагружать
        bool alreadyUnarmed = CheckAttribute(chref,"equip.blade") && chref.equip.blade == "unarmed" && chref.equip.blade != itemID;
        //если экипируем кулаки или мушкет, то анимацию надо перезагружать
        bool wantUnarmed = itemID == "unarmed" || groupName == MUSKET_ITEM_TYPE;
        //даем персонажу другое оружее
        chref.equip.(groupName) = itemID;
        if (alreadyUnarmed || wantUnarmed)
        {
            //собственно сама перегрузка анимации
            SetDefaultFight(chref);
            EndChangeCharacterActions(chref);
        }
	}
	else
	{
		if (!CheckAttribute(arItm,"mapSpecial"))
		{
			chref.equip.(groupName).(itemID) = itemID;		
		}	
	}	

	if (IsEntity(chref) || groupName == CIRASS_ITEM_TYPE)
	{
		SetEquipedItemToCharacter(chref, groupName, itemID);
	}
    if (sti(chref.index) == GetMainCharacterIndex())
    {
        if(groupName == GUN_ITEM_TYPE || groupName == MUSKET_ITEM_TYPE)
            LAi_GunSetUnload(chref, groupName);
    }
	// boal -->
	/*if (groupName == SPYGLASS_ITEM_TYPE && sti(chref.index)==GetMainCharacterIndex())// && bSeaActive
	{
		FillISpyGlassParameters();
	}*/
	// boal <--
}

void ExecuteCharacterEquip(ref chref)
{
	string stmp = GetCharacterEquipByGroup(chref, BLADE_ITEM_TYPE);
	if(stmp!="") SetEquipedItemToCharacter(chref, BLADE_ITEM_TYPE, stmp);
	stmp = GetCharacterEquipByGroup(chref, GUN_ITEM_TYPE);
	if(stmp!="") SetEquipedItemToCharacter(chref, GUN_ITEM_TYPE, stmp);
    stmp = GetCharacterEquipByGroup(chref, MUSKET_ITEM_TYPE);
	if(stmp!="") SetEquipedItemToCharacter(chref, MUSKET_ITEM_TYPE, stmp);
}

///  репутация ГГ 06/06/06 boal new concept -->
//изменить репутацию персонажа в зависимости от текущей репутации.
//минус для плохого это рост в плюс
int ChangeCharacterReputationABS(ref chref, float incr)
{
	int curVal = REPUTATION_NEUTRAL;
	if (CheckAttribute(chref,"reputation") ) curVal = stf(chref.reputation);

	if (curVal < REPUTATION_NEUTRAL) incr = -incr;
	return ChangeCharacterReputation(chref , incr);
}

// репутация стремится к нейтральной
int ChangeCharacterReputationToNeutral(ref chref, float incr)
{
	int curVal = REPUTATION_NEUTRAL;
	if (CheckAttribute(chref,"reputation") ) curVal = stf(chref.reputation);
	
	if (curVal > REPUTATION_NEUTRAL) incr = -incr;
	return ChangeCharacterReputation(chref , incr);
}

int ChangeCharacterReputation(ref chref, float incr)
{
	if (CheckAttribute(chref, "GenQuest.ReputationNotChange")) return sti(chref.reputation); //eddy. нужен флаг
	float prevVal = REPUTATION_NEUTRAL;
	if (CheckAttribute(chref,"reputation") )	prevVal = stf(chref.reputation);

	float newVal = prevVal + incr;
	if (newVal<REPUTATION_MIN) newVal = REPUTATION_MIN;
	if (newVal>REPUTATION_MAX) newVal = REPUTATION_MAX;
	chref.reputation = newVal;

	if( sti(chref.index) != GetMainCharacterIndex() ) return makeint(newVal);

	string prevName = GetReputationName(makeint(prevVal));
	string newName = GetReputationName(makeint(newVal));
	if (prevName!=newName)
	{
		string outString = XI_ConvertString("Your reputation")+" ";
		if (incr>0)	{outString+=XI_ConvertString("increase");}
		else	{outString+=XI_ConvertString("decrease");}
		outString += " "+XI_ConvertString("to")+" "+XI_ConvertString(newName);
//		Log_SetStringToLog(outString);

        if (incr > 0) notification(outString, "RepUp");
        else notification(outString, "RepDown");
	}

	return makeint(newVal);
}
//    ChangeCharacterNationReputation(chref, iType, incr);

// метод вызывается ежедневно, уменьшает значение крайних репутаций - эффект забывания.
void UpdateFame()
{
	if (sti(pchar.reputation) < (REPUTATION_NEUTRAL - 10))  // плохиш
	{
		ChangeCharacterReputation(pchar, (MOD_SKILL_ENEMY_RATE / 40.0)); // медленнее
	}
	if (sti(pchar.reputation) > (REPUTATION_NEUTRAL + 10))  // кибальчиш
	{
		ChangeCharacterReputation(pchar, (-MOD_SKILL_ENEMY_RATE / 20.0));
	}
}
///  репутация ГГ 06/06/06 boal new concept <--

bool Character_IsAbordageEnable(ref rCharacter)
{
	if (CheckAttribute(rCharacter, "AlwaysFriend")) return false; // boal
	if (CheckAttribute(rCharacter, "Abordage.Enable")) { return sti(rCharacter.Abordage.Enable); }
	return true;
}

void Character_SetAbordageEnable(ref rCharacter, bool bEnable)
{
	rCharacter.Abordage.Enable = bEnable;
}

void Character_SetCompanionEnemyEnable(ref rCharacter, bool bEnable)
{
	rCharacter.CompanionEnemyEnable = bEnable;
}

void AddMsgToCharacter(ref chref, int nMsg)
{
	string msgName = "msg"+nMsg;
	bool bStartEvent = !CheckAttribute(chref,"MessageIcons."+msgName);
	chref.MessageIcons.(msgName).pic = nMsg;
	chref.MessageIcons.(msgName) = MSGICON_ACTIVE_TIME;
	if(bStartEvent) PostEvent("evnt_MsgIconTick",1000,"ll",nMsg,sti(chref.index));
}

void DelMsgFromCharacter(ref chref, int nMsg)
{
	DeleteAttribute(chref,"MessageIcons.msg"+nMsg);
}

void proc_MsgIconTick()
{
	int nMsg = GetEventData();
	int chrIdx = GetEventData();
	if(DialogRun!=0) {
		PostEvent("evnt_MsgIconTick",1000,"ll",nMsg,chrIdx);
		return;
	}
	ref chref = GetCharacter(chrIdx);
	string msgName = "msg"+nMsg;
	int nTime = 0;

	if( CheckAttribute(chref,"MessageIcons."+msgName) )
	{
		nTime = sti(chref.MessageIcons.(msgName));
		if(nTime>0)
		{
			chref.MessageIcons.(msgName) = nTime-1;
			PostEvent("evnt_MsgIconTick",1000,"ll",nMsg,chrIdx);
			return;
		}
		DelMsgFromCharacter(chref,nMsg);
	}
}

int GetCharacterReputation_WithNation(aref chr, int iNation)
{
	int iVal = 0;
	switch (iNation)
	{
		case ENGLAND:
			iVal = ChangeCharacterNationReputation(chr, ENGLAND, 0);
		break;

		case FRANCE:
			iVal = ChangeCharacterNationReputation(chr, FRANCE, 0);
		break;

		case SPAIN:
			iVal = ChangeCharacterNationReputation(chr, SPAIN, 0);
		break;

		case HOLLAND:
			iVal = ChangeCharacterNationReputation(chr, HOLLAND, 0);
		break;

		case PIRATE:
			iVal = ChangeCharacterNationReputation(chr, PIRATE, 0);
		break;

		case 5:
			iVal = sti(chr.reputation.smuggler);
		break;

		case 6:
			iVal = sti(chr.reputation.trader);
		break;
	}

	return iVal;
}

bool isPrisonedChar(aref chr)
{
	if(CheckAttribute(chr,"prisoned"))
	{
		if(sti(chr.prisoned) == 1)
		{
			return true;
		}
	}
	return false;
}

bool CheckForRank(aref chr, int iRank)
{
	if(CheckAttribute(chr, "rank"))
	{
		if(sti(chr.rank) >= iRank)
		{
			return true;
		}
	}
	return false;
}

/////////////////////////
string Get_My_Cabin()
{
	return Pchar.SystemInfo.CabinType;
}

bool isShipInside(string _id)
{
    bool   ret = false;

    if (_id == Get_My_Cabin() || _id == "My_Deck_Medium" || _id == "My_Campus" || _id == "My_Deck" || _id == "Deck_Near_Ship" || _id == "My_Orlop")
    {
        ret = true;
        if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && CheckAttribute(pchar, "GenQuest.CaptainId") && pchar.GenQuest.CaptainId == "MQPirate")
	    {
	        if (!CheckQuestAttribute("Munity", "Deads")) ret = false;
	    }
    }

    return ret;
}

void Set_My_Cabin()
{
    int     n, i;
    string  sTemp, newCab;
    ref     rShip;

    int nShipType = GetCharacterShipType(pchar);
	if (nShipType == SHIP_NOTUSED)
	{
        newCab = "My_Cabin";
	}
	else
	{
	    rShip = GetRealShip(nShipType);
	    newCab = "My_" + rShip.CabinType;  // превратим из каюты типа корабля
	}

    if (Pchar.SystemInfo.CabinType != newCab)
    {
        if (Pchar.SystemInfo.CabinType != "")
		{
			// переселить предметы
			ref		loc, locTo;
			aref	arFromBox, curItem, al, boxTo;
			string	attr, time, sat = "";

			loc		= &locations[FindLocation(Pchar.SystemInfo.CabinType)];
			locTo	= &locations[FindLocation(newCab)];

			if (IsDay())
				time = "day";
			else
				time = "night";

			if (CheckAttribute(locTo, "models." + time + ".locators"))
				sat = "models." + time + ".locators";
			else if (CheckAttribute(locTo, "models.always.locators"))
				sat = "models.always.locators";

			if (sat != "")
			{
				CreateEntity(locTo, "location");

				if (CheckAttribute(locTo, "filespath.models"))
					SendMessage(locTo, "ls", MSG_LOCATION_MODELSPATH, locTo.filespath.models);

				LocLoadModel(locTo, sat, "");
				SendMessage(locTo, "l", MSG_LOCATION_UPDATELOCATORS);
			}

			// полная зачистка
			for (n = 1; n <= 4; n++)
			{
				sTemp = "box" + n;
				DeleteAttribute(locTo, sTemp + ".items");
				locTo.(sTemp).items = "";
				locTo.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
				locTo.(sTemp).money = 0;
			}

			for (n = 1; n <= 4; n++)
			{
				sTemp = "box" + n;

				if (FindLocator(locTo.id, sTemp, &al, true))
					makearef(boxTo, locTo.(sTemp));
				else
					makearef(boxTo, locTo.box1);

				if (CheckAttribute(loc, sTemp + ".money"))
					boxTo.money = sti(boxTo.money) + sti(loc.(sTemp).money);

				makearef(arFromBox, loc.(sTemp).items);
				for (i = 0; i < GetAttributesNum(arFromBox); i++)
				{
					curItem = GetAttributeN(arFromBox, i);
					attr = GetAttributeName(curItem);

					if (attr != "")
					{
						if (!CheckAttribute(boxTo, "items." + attr))
							boxTo.items.(attr) = 0;

						boxTo.items.(attr) = makeint(sti(boxTo.items.(attr)) + makeint(GetAttributeValue(curItem)));
					}
				}
				// del
				DeleteAttribute(loc, sTemp + ".items");
				loc.(sTemp).items = "";
				loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
				loc.(sTemp).money = 0;
			}

			if (sat != "")
				DeleteClass(locTo);
		}

        Pchar.SystemInfo.CabinType = newCab;

        n = FindLocation("My_Deck");
        if (n != -1)
        {
            if (sti(rShip.Class) > 4)
            {
                Locations[n].reload.l1.go = Pchar.SystemInfo.CabinType;
                Locations[n].reload.l1.emerge = "reload1";
            }
            else
            {
                Locations[n].reload.l1.go = "My_Deck_Medium";
                Locations[n].reload.l1.emerge = "reload_hold";
            }
        }

        n = FindLocation(Pchar.SystemInfo.CabinType);
        if (n != -1)
        {
            if (sti(rShip.Class) > 4)
            {
                Locations[n].reload.l1.go = "My_Deck";
                Locations[n].reload.l1.emerge = "reload1";
            }
            else
            {
                Locations[n].reload.l1.go = "My_Deck_Medium";
                Locations[n].reload.l1.emerge = "reload_cabin";
            }
        }

        n = FindLocation("My_Deck_Medium");
        if (n != -1)
            Locations[n].reload.l1.go = Pchar.SystemInfo.CabinType;

		n = FindLocation("My_Orlop");
		if (n != -1)
			Locations[n].reload.l1.go = Pchar.SystemInfo.CabinType;
    }
}

// есть ли патент
bool isMainCharacterPatented()
{
    if(CheckAttribute(pchar, "EquipedPatentId") && CheckCharacterItem(pchar, Items[sti(pchar.EquipedPatentId)].id))
    {
        return true;
    }
    return false;
}

int GetPatentNation()
{
    if(CheckAttribute(pchar, "EquipedPatentId") && CheckCharacterItem(pchar, Items[sti(pchar.EquipedPatentId)].id))
    {
        return sti(Items[sti(pchar.EquipedPatentId)].Nation);
    }
    return -1;
}

// звания
void AddTitleNextRate(int nation, float num)
{
    if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].Nation) == nation)
    {
        Items[sti(pchar.EquipedPatentId)].TitulCurNext = stf(Items[sti(pchar.EquipedPatentId)].TitulCurNext) + num;
        if (stf(Items[sti(pchar.EquipedPatentId)].TitulCurNext) < 0) Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
        if (stf(Items[sti(pchar.EquipedPatentId)].TitulCurNext) > MAX_TITLENEXTRATE) Items[sti(pchar.EquipedPatentId)].TitulCurNext = MAX_TITLENEXTRATE;
        Log_TestInfo("TitleCurNext = " + stf(Items[sti(pchar.EquipedPatentId)].TitulCurNext));
    }
}
// присвоить следующее?
bool isReadyToNextTitle(int nation)
{
    bool    ret = false;

    if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].Nation) == nation)
    {
        if (sti(Items[sti(pchar.EquipedPatentId)].TitulCur) < MAX_TITLE && (stf(Items[sti(pchar.EquipedPatentId)].TitulCurNext) / sti(Items[sti(pchar.EquipedPatentId)].TitulCur)) >= 3)
        {
            ret = true;
        }
    }

    return ret;
}
// проверка на допустимость игры в карты и кости -->
float GetCardsGameCheckRate()
{
	float k;
	float   fWin, fLose;


	fWin  = makefloat(Statistic_AddValue(Pchar, "GameCards_Win", 0));
    fLose = makefloat(Statistic_AddValue(Pchar, "GameCards_Lose", 0));
    if (fLose < 1) fLose = 1.0;

    k = fWin / fLose;

	return k;
}
bool CheckCardsGameSmallRate()
{
	bool    ret = true;

    if (GetCardsGameCheckRate() >= 15)
    {
        ret = false;
    }
	return ret;
}

bool CheckCardsGameBigRate()
{
	bool    ret = true;

    if (GetCardsGameCheckRate() >= 7)
    {
        ret = false;
    }
	return ret;
}

float GetDiceGameCheckRate()
{
	float k;
	float   fWin, fLose;


	fWin  = makefloat(Statistic_AddValue(Pchar, "GameDice_Win", 0));
    fLose = makefloat(Statistic_AddValue(Pchar, "GameDice_Lose", 0));
    if (fLose < 1) fLose = 1.0;

    k = fWin / fLose;

	return k;
}
bool CheckDiceGameSmallRate()
{
	bool    ret = true;

    if (GetDiceGameCheckRate() >= 15)
    {
        ret = false;
    }
	return ret;
}

bool CheckDiceGameBigRate()
{
	bool    ret = true;

    if (GetDiceGameCheckRate() >= 7)
    {
        ret = false;
    }
	return ret;
}
// проверка на допустимость игры в карты и кости <--

// boal 08.01.05 -->
int GetPartyCrewQuantity(ref _refCharacter, bool _removable) // true - если только наши
{
	int cn;
	int sumCrew = 0;
	ref officer;

	for(int i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if (cn!=-1)
		{
            officer = GetCharacter(cn);
            if (!GetRemovable(officer) && _removable) continue; // только наши + ГГ
			sumCrew = sumCrew + GetCrewQuantity(officer);
		}
	}
	return sumCrew;
}

int GetTroopersCrewQuantity(ref _refCharacter)
{
	int cn, j;
	int compCrew;
	int sumCrew = 0;
	ref officer;

 	if (CheckOfficersPerk(_refCharacter, "Troopers"))
    {
        Log_TestInfo("-= GetTroopersCrewQuantit =-");
        for (j=1; j<COMPANION_MAX; j++) // ГГ отдельно
        {
	        cn = GetCompanionIndex(_refCharacter, j);
	        if (cn>0)
	        {
		        officer = GetCharacter(cn);
		        if (!GetRemovable(officer)) continue;

		        compCrew = GetCrewQuantity(officer) - GetMinCrewQuantity(officer);
		        if (compCrew < 0)
		        {
		           compCrew = 0;
		        }
				compCrew = GetWeaponCrew(officer, compCrew);  // без оружия просто не идут (как половина команды учет)

                if (compCrew > 0)
                {
	                RemoveCharacterGoodsSelf(officer, GOOD_WEAPON, makeint(compCrew/2 + 0.5));
	                SetCrewQuantity(officer, GetCrewQuantity(officer) - compCrew);
                	Log_SetStringToLog(StringFromKey("InfoMessages_1", officer.Ship.Name, FindPeoplesString(compCrew, "No")));
                	AddCharacterExpToSkill(officer, "Defence", makeint(compCrew / 2 + 0.5)); //качаем защиту
                	AddCharacterExpToSkill(officer, "Grappling", makeint(compCrew / 2 + 0.5));
                	sumCrew = sumCrew + compCrew;
                }
		    }
		}
    }
    // квестовый перк
    if (CheckAttribute(_refCharacter, "TempPerks.QuestTroopers"))
	{
        Log_TestInfo("-= QuestTroopers =-");
		for (j=1; j<COMPANION_MAX; j++) // ГГ отдельно
        {
	        cn = GetCompanionIndex(_refCharacter, j);
	        if (cn>0)
	        {
		        officer = GetCharacter(cn);
		        if (GetRemovable(officer)) continue;// токо квесты

		        compCrew = GetCrewQuantity(officer);
		        if (compCrew < 0)
		        {
		           compCrew = 0;
		        }
		        Log_SetStringToLog(StringFromKey("InfoMessages_1", officer.Ship.Name, FindPeoplesString(compCrew, "No")));
                if (compCrew > 0)
                {
                	sumCrew = sumCrew + compCrew;
                }
		    }
		}
		DeleteAttribute(_refCharacter, "TempPerks.QuestTroopers");
	}
	return sumCrew;
}
// распределить перегруз экипажа по кораблям ГГ
void AddTroopersCrewToOther(ref _refCharacter)
{
	int cn, j;
	int compCrew = 0;
	ref officer;

    if (GetOptCrewQuantity(_refCharacter) < GetCrewQuantity(_refCharacter))
    {
        compCrew = GetCrewQuantity(_refCharacter) - GetOptCrewQuantity(_refCharacter);
        SetCrewQuantity(_refCharacter, GetOptCrewQuantity(_refCharacter));
    }
	if (compCrew <= 0)
		return;
	
	int optTotal = 0;
	int maxTotal = 0;
	for (j=1; j<COMPANION_MAX; j++)
	{
		cn = GetCompanionIndex(_refCharacter, j);
		if (cn > 0)
		{
			officer = GetCharacter(cn);
			if (!GetRemovable(officer)) continue;
			
			maxTotal += GetMaxCrewQuantity(officer) - GetCrewQuantity(officer);
			optTotal += GetOptCrewQuantity(officer) - GetCrewQuantity(officer);
		}
	}
	
	int remCrew;
	if (optTotal - compCrew > 0)
	{
		remCrew = SpreadingCrewToCompanions(_refCharacter, compCrew, true);
	}
	else
	{
		float compMaxRatio = makefloat(compCrew) / makefloat(maxTotal);
		if (compMaxRatio > 1.0)
		{
			remCrew = SpreadingCrewToCompanions(_refCharacter, compCrew, false);
		}
		else
		{
			remCrew = SpreadingCrewToCompanions(_refCharacter, compCrew, true);
		}
	}
	
	// остатки отдаем ГГ
	if (remCrew > 0)
	{
		if (GetMaxCrewQuantity(_refCharacter) >= (GetCrewQuantity(_refCharacter) + remCrew))
		{
			SetCrewQuantity(_refCharacter, (GetCrewQuantity(_refCharacter) + remCrew));
		}
		else
		{
			SetCrewQuantity(_refCharacter, GetMaxCrewQuantity(_refCharacter));
		}
	}
}

int SpreadingCrewToCompanions(ref _refCharacter, int crewQty, bool useOpt)
{
	int cn, j, maxCrewQty, compCrew = crewQty;
	ref officer;
	
	for (j=1; j<COMPANION_MAX; j++)
	{
		cn = GetCompanionIndex(_refCharacter, j);
		if (cn>0)
		{
			officer = GetCharacter(cn);
			if (!GetRemovable(officer)) continue;
			
			if (useOpt)
				maxCrewQty = GetOptCrewQuantity(officer);
			else
				maxCrewQty = GetMaxCrewQuantity(officer);
			
			if (maxCrewQty >= (GetCrewQuantity(officer) + compCrew))
			{
				SetCrewQuantity(officer, (GetCrewQuantity(officer) + compCrew));
				compCrew = 0;
				break;  // все влезли
			}
			else
			{
				compCrew = (GetCrewQuantity(officer) + compCrew) - maxCrewQty;
				SetCrewQuantity(officer, maxCrewQty);
			}
		}
	}
	
	// Остатки
	return compCrew;
}
// boal 21.01.2004
int GetWeaponCrew(ref _char, int _crew)
{
    int weaponOnBoard = GetCargoGoods(_char, GOOD_WEAPON);
	if (_crew > weaponOnBoard)
	{
	    _crew = weaponOnBoard + makeint(( _crew - weaponOnBoard)/2.0 + 0.5);
	}
	return _crew;
}
// boal 08.01.05 <--

// ========================= eddy пока сюда перенесу
int GenerateNationTrade(int nation, bool bAny)
{
	int i = -1;
	// boal -->
	int   j = 0;
	bool  ok;

	while (i == -1 && j < 10)
	{
		i = rand(MAX_NATIONS - 1);
		ok = (GetNationRelation2MainCharacter(i) == RELATION_ENEMY) && (i != PIRATE); //fix 12.05.05
		if (ok || GetNationRelation(nation, i) == RELATION_ENEMY) // boal было nation == i || i == PIRATE- но сами себе можем!!!
		{
			if (bAny)
			{
				if (sti(pchar.nation) == PIRATE)
					i = PIRATE;
				else
					i = rand(PIRATE);
			}
			else
				i = -1;
		}
		j++;
	}
    // boal <--
	return i;
}

int RecalculateSquadronCargoLoad(ref _refCharacter)
{
	int i,cn;
	int retVal = RecalculateCargoLoad(_refCharacter);

	for(i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if(cn!=-1)
		{
			retVal = retVal + RecalculateCargoLoad(&Characters[cn]);
		}
	}
	return retVal;
}

// из Боф_реакшн
void LoansMoneyAvenger(ref _loan)
{
    Log_SetStringToLog(StringFromKey("InfoMessages_2"));

    LoansMoneyAvengerAmount(_loan, 25);
}

void LoansMoneyAvengerAmount(ref _loan, int _sum)
{
    string typeHunter = NationShortName(sti(_loan.nation)) + "hunter";
    ChangeCharacterReputation(Pchar, -20);
    OfficersReaction("bad");
    if ( _loan.nation == PIRATE)
    {
        typeHunter = "enghunter";  // за пиратов мстит англия
    }
    ChangeCharacterHunterScore(PChar, typeHunter, _sum);
}
//homo возращает нпс стоящего на локаторе
int GetCharacterbyLocation(string location, string group, string locator)
{
    ref sld;
    for(int i=0;i<MAX_CHARACTERS;i++)
	{
        sld = &characters[i];
        if (sld.location == location && sld.location.group == group && sld.location.locator == locator) return i;
	}
	return -1;
}

// Warship -->
// Сделать мушкетером или обычным фехтовальщиком
bool SetCharacterToMushketer(ref xi_refCharacter, string sMushket)
{
	if (sMushket != "")
	{
        EquipCharacterByItem(xi_refCharacter, sMushket);
        if (!CheckAttribute(xi_refCharacter, "MusketerDistance"))
            xi_refCharacter.MusketerDistance = 10.0;
	}
	else RemoveCharacterEquip(xi_refCharacter, MUSKET_ITEM_TYPE);

	return true;
}

// Создадим клона персонажа. Корабль не копируется
int CreateCharacterClone(ref Character, int iLifeDay)
{
	int iTemp = NPC_GeneratePhantomCharacter("citizen", sti(Character.Nation), MAN, iLifeDay);
	if(iTemp != -1)
	{
		ref rCloneChar = &Characters[iTemp];
		ChangeAttributesFromCharacter(rCloneChar, Character, true);
	}
	
	return iTemp;
}

// Получим ID надетой одежды
string GetCharacterEquipSuitID(ref rChar)
{
	ref rItem;
	string sItem = GetCharacterEquipByGroup(rChar, CIRASS_ITEM_TYPE);
	
	if(sItem == "") return INVALID_SUIT;
	
	rItem = ItemsFromID(sItem);
	
	if(sti(GetAttrValue(rItem, "Clothes"))) // Одежда
	{
		return sItem;
	}
	
	return INVALID_SUIT;
}
// <-- Warship
// --> ugeen   16.02.09
// Запомним офицеров во временном хранилище(нужно по Аскольду)
bool StoreOfficers_Ascold(ref refCh)
{	
	if (CheckAttribute(refCh, "Fellows.Old")) DeleteAttribute(refCh, "Fellows.Old");

	string sTmp;
	aref arTmp;
	int i, idx;
	// сохраним офицеров
	makearef( arTmp, refCh.Fellows.Old.Officers );
	for(i = 1; i < 4; i++ )
	{
		idx = GetOfficersIndex(refCh,i);
		if( idx == -1 ) continue;
		sTmp = "id"+i;
		arTmp.(sTmp) = idx;
		if(!CheckAttribute(refCh, arTmp.first_idx)) arTmp.first_idx = idx;
	}
	return true;
}

// Восстановить запомненных ранее офицеров
bool RestoreOfficers_Ascold(ref refCh)
{
	if (!CheckAttribute(refCh, "Fellows.Old")) return false;

	int i,idx;
	aref arTmp,arCur;

	// Восстановление офицеров
	makearef(arTmp, refCh.Fellows.Old.Officers);
	for(i=0; i<GetAttributesNum(arTmp); i++)
	{
		arCur = GetAttributeN(arTmp,i);
		idx = sti(GetAttributeValue(arCur));
		if( idx == -1 ) continue;
		SetOfficersIndex( refCh, -1 , idx );
	}

	return true;
}

void EquipCharacterByAtlas(ref chref)
{
	string groupID = MAPS_ITEM_TYPE;
	ref rLoc = ItemsFromID("MapsAtlas");
	chref.equip.(groupID) = rLoc.id;
}

// проверим наличие атласа и карты в нём
bool CheckMapForEquipped(ref refCh, string itemID)
{
	ref   arItem;

	arItem = ItemsFromID(itemID);

	if (sti(refCh.index) == GetMainCharacterIndex() && CheckCharacterItem(refCh, arItem.id))
	{
		if (!CheckCharacterItem(refCh, "MapsAtlas")) // тривиальная проверка на наличие атласа - если его нет,  то получите и распишитесь
		{
			GiveItem2Character(refCh, "MapsAtlas");
			EquipCharacterByAtlas(refCh);
		}

		if (!IsEquipCharacterByMap(refCh, itemID)) // проверяем, экипирован ли ГГ  этой картой
		{
			EquipCharacterByItem(refCh, itemID);
			ResetMapMakerAtlas();

			if (CheckAttribute(arItem, "MapIsland") && !ArrayIsEqualValue(&arMapMakerAtlas, itemID))
			{
				ArrayAddValue(&arMapMakerAtlas, itemID);

				if ((GetArraySize(&arMapMakerAtlas) - 2) == MAPS_IN_ATLAS && !CheckCharacterPerk(refCh, "MapMaker")) // даем скрытый перк если собрали все карты островов
					SetCharacterPerk(refCh, "MapMaker");
			}

			notification(StringFromKey("InfoMessages_185", GetConvertStr(arItem.name, "ItemsDescribe.txt")), "MapsAtlas");
			arItem = ItemsFromID("MapsAtlas");
			arItem.Weight = GetEquippedItemsWeight(refCh, MAPS_ITEM_TYPE);
		}
		else return false;
	}

	return true;
}

// проверка - есть ли новые карты для включения в атлас
void RefreshEquippedMaps(ref chref)
{
	aref arCurItem, arItem, arItems; makearef(arItems, chref.items);
	int i, q = GetAttributesNum(arItems);
	string  sItemID, sGroupID;

	for (i = 0; i < q; i++)
	{
		arCurItem = GetAttributeN(arItems, i);

		if (Items_FindItem(GetAttributeName(arCurItem), &arItem) >= 0)
		{
			if (CheckAttribute(arItem, "ID") && CheckAttribute(arItem, "groupID"))
			{
				sItemID = arItem.id;
				sGroupID = arItem.groupID;

				if (sGroupID == MAPS_ITEM_TYPE && !CheckAttribute(arItem, "mapSpecial"))
				{
					CheckMapForEquipped(chref, sItemID);
				}
			}
		}
	}
}

void StoreEquippedMaps(ref refCh)
{
    aref arItems;
	string  sName, groupID;
	ref rLoc;

	if (CheckAttribute(refCh, "Stored.Maps"))
		DeleteAttribute(refCh, "Stored.Maps");

	makearef(arItems, refCh.items);
    int	a, Qty = GetAttributesNum(arItems);

	for (a = 0; a < Qty; a++)
    {
        sName = GetAttributeName(GetAttributeN(arItems, a));
		rLoc = ItemsFromID(sName);
		if (CheckAttribute(rLoc, "GroupID"))
		{
			groupID = rLoc.groupID;
			if (groupID == MAPS_ITEM_TYPE)
			{
				if (IsEquipCharacterByMap(refCh, rLoc.id)) // проверяем, экипирован ли ГГ  этой картой
				{
					refCh.Stored.Maps.(sName) = refCh.items.(sName);
					ArrayRemoveValue(&arMapMakerAtlas, rLoc.id);
				}
			}
		}
    }

	ResetMapMakerAtlas();
}

void RestoreEquippedMaps(ref refCh)
{
    aref arItems;
	string sName;

	if (!CheckAttribute(refCh, "Stored.Maps")) return;

	makearef(arItems, refCh.Stored.Maps);
    int a, Qty = GetAttributesNum(arItems);

    for (a = 0; a < Qty; a++)
    {
        sName = GetAttributeName(GetAttributeN(arItems, a));
		TakeNItems(refCh, sName, 1);
    }
	DeleteAttribute(refCh, "Stored.Maps");
	RefreshEquippedMaps(refCh);
}
// <-- ugeen

void ResetMapMakerAtlas()
{
	if (GetArraySize(&arMapMakerAtlas) <= 2)
	{
		SetArraySize(&arMapMakerAtlas, 2);
		arMapMakerAtlas[0] = "hello";
		arMapMakerAtlas[1] = "world";
	}
}

void OfficersHold()
{
	int idx;
	for(int i=1; i<4; i++)
	{
		idx = GetOfficersIndex(PChar,i);
		if (idx != -1) {
			ref offchar = GetCharacter(idx);
			if (CheckAttribute(offchar, "chr_ai.type") && offchar.chr_ai.type == LAI_TYPE_INJURE)
				continue;
			SetCharacterTask_Stay(offchar);
		}
	}
}

void OfficersFollow()
{
	int idx;
	for(int i=1; i<4; i++)
	{
		idx = GetOfficersIndex(PChar,i);
		if (idx != -1) {
			ref offchar = GetCharacter(idx);
			if (CheckAttribute(offchar, "chr_ai.type") && offchar.chr_ai.type == LAI_TYPE_INJURE)
				continue;
			LAi_tmpl_SetFollow(offchar, GetMainCharacter(), -1.0);
		}
	}
}

void SetCapGreetByModel(ref NPChar) //TODO: особую озвучку адмиралам, например
{
	NPChar.Greeting = "Gr_Commander_pir";
	if(HasSubStr(NPChar.model, "merch_"))	NPChar.Greeting = "Gr_Commander_tra";
	if(HasSubStr(NPChar.model, "off_"))		NPChar.Greeting = "Gr_Commander_off";
}

void SetSailGreetByModel(ref NPChar)
{
	string MERCH_BOARD_TEAM = "citiz_42,citiz_41,citiz_43,citiz_48,citiz_49,citiz_50,barmen_1,barmen_9";
	NPChar.Greeting = "Gr_Soldier";
	if(HasSubStr(MERCH_BOARD_TEAM, NPChar.model)) NPChar.Greeting = "Gr_Soldier_tra";
	if(HasSubStr(NPChar.model, "navy_") || HasSubStr(NPChar.model, "sold_")) NPChar.Greeting = "soldier_common";
}

float ChangeIndianRelation(float _val) // Jason: репутация у индейцев
{
   pchar.questTemp.Indian.relation = stf(pchar.questTemp.Indian.relation) + _val;
   if (stf(pchar.questTemp.Indian.relation) > 100.0) pchar.questTemp.Indian.relation = 100.0;
   if (stf(pchar.questTemp.Indian.relation) < 0) pchar.questTemp.Indian.relation = 0;
//   log_testInfo("Отношение индейцев изменилось и равно "+stf(pchar.questTemp.Indian.relation)+" единицам");
    if (_val<0)
    {
        notification(StringFromKey("InfoMessages_221")+" ("+FloatToString(stf(pchar.questTemp.Indian.relation),1)+")", "Indians");
    }
    if (_val>0)
    {
        notification(StringFromKey("InfoMessages_222")+" ("+FloatToString(stf(pchar.questTemp.Indian.relation),1)+")", "Indians");
    }

   return stf(pchar.questTemp.Indian.relation);
}

//Пользуется ли персонаж мушкетом в данный момент?
bool CharUseMusket(ref rChar)
{
	//Либо это чистый мушкетёр на старой анимации, либо универсал в мушкетном режиме
	if(rChar.model.animation == "mushketer" || LAi_CheckFightMode(rChar) == 2) return true;
	return false;
}

// Приоритетный режим 0-сабля, 1-мушкет (для лэнд интерфейса надо вместо CharUseMusket)
bool MusketPriority(ref rChar)
{
	if(GetCharacterEquipByGroup(rChar, MUSKET_ITEM_TYPE) == "") return false;
	if(CheckAttribute(rChar, "PriorityMode") && sti(rChar.PriorityMode) == 2) return true;
	return false;
}

//Есть ли у персонажа мушкет?
bool IsMusketer(ref rChar)
{
    // GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE) != ""
	return CheckAttribute(rChar, "equip.musket");
}

void MakeOffMush(ref chr, string sMush, int iBullet, int iPowder)
{
    chr.HoldEquip = true;
    chr.SuperShooter = true;
	chr.MusketOutfit = true;
    chr.MushForever = ""; // Использовать только мушкет
    LAi_SetRolyPoly(chr, true);
    GiveItem2Character(chr, "unarmed");
	EquipCharacterbyItem(chr, "unarmed");
	GiveItem2Character(chr, sMush);
	SetCharacterToMushketer(chr, sMush);
    AddItems(chr, "bullet", iBullet);
	AddItems(chr, "GunPowder", iPowder);
}

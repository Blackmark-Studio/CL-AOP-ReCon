#define CANNON_TYPES_QUANTITY		16

#define CANNON_TYPE_CULVERINE_LBS8	0
#define CANNON_TYPE_CULVERINE_LBS12 1
#define CANNON_TYPE_CULVERINE_LBS16 2
#define CANNON_TYPE_CULVERINE_LBS24 3
#define CANNON_TYPE_CULVERINE_LBS32 4

#define CANNON_TYPE_CANNON_LBS3     5
#define CANNON_TYPE_CANNON_LBS6     6
#define CANNON_TYPE_CANNON_LBS8	    7
#define CANNON_TYPE_CANNON_LBS12    8
#define CANNON_TYPE_CANNON_LBS16    9
#define CANNON_TYPE_CANNON_LBS20    10
#define CANNON_TYPE_CANNON_LBS24    11
#define CANNON_TYPE_CANNON_LBS32    12
#define CANNON_TYPE_CANNON_LBS36	13
#define CANNON_TYPE_CANNON_LBS42    14
#define CANNON_TYPE_CANNON_LBS48    15
//#define CANNON_TYPE_MORTAR		12

#define CANNON_TYPE_NONECANNON		1000
#define CANNON_TYPE_LBS_BY_SHIP		1001

#define CANNON_NAME_CANNON              1
#define CANNON_NAME_CULVERINE           2
#define CANNON_NAME_SPECIAL_CANNON		3
//#define CANNON_NAME_MORTAR			4

object Cannon[CANNON_TYPES_QUANTITY];

ref GetCannonByType(int iCannonType) 
{ 
	if (iCannonType == CANNON_TYPE_NONECANNON) return &NullCharacter; // fix для тартант boal
	return &Cannon[iCannonType];
}

int GetCannonCaliber(int nCannon)
{
    switch(nCannon)
    {
		// --->>> пушки        
		case CANNON_TYPE_NONECANNON:   return 0;  break;
		case CANNON_TYPE_CANNON_LBS3:  return 3;  break;
		case CANNON_TYPE_CANNON_LBS6:  return 6;  break;
		case CANNON_TYPE_CANNON_LBS8:  return 8;  break;
		case CANNON_TYPE_CANNON_LBS12: return 12; break;
		case CANNON_TYPE_CANNON_LBS16: return 16; break;
		case CANNON_TYPE_CANNON_LBS20: return 20; break;
		case CANNON_TYPE_CANNON_LBS24: return 24; break;
		case CANNON_TYPE_CANNON_LBS32: return 32; break;
		case CANNON_TYPE_CANNON_LBS36: return 36; break;
		case CANNON_TYPE_CANNON_LBS42: return 42; break;
		case CANNON_TYPE_CANNON_LBS48: return 48; break;

		// --->>> кулеврины 
		case CANNON_TYPE_CULVERINE_LBS8:  return 8;  break;
		case CANNON_TYPE_CULVERINE_LBS12: return 12; break;
		case CANNON_TYPE_CULVERINE_LBS16: return 16; break;
		case CANNON_TYPE_CULVERINE_LBS24: return 24; break;
		case CANNON_TYPE_CULVERINE_LBS32: return 32; break;
    
	    //case CANNON_TYPE_MORTAR: return 92; break;
    }

	return 0;
}
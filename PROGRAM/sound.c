// KZ > ref 29.12.2023

// DEFINES
#define MUSIC_CHANGE_TIME		3000	// > нарастание громкости трека при старте воспроизведения
#define SOUNDS_FADE_TIME		200		// > затухание всех звуков при их глушении
#define MUSIC_PAUSE_MIN_ALARM	1		// > мин-ая пауза между треками в боевом режиме
#define MUSIC_PAUSE_MAX_ALARM	3		// > макс-ая пауза между треками в боевом режиме
#define MUSIC_PAUSE_MIN_PEACE	3		// > мин-ая пауза между треками в спокойном режиме
#define MUSIC_PAUSE_MAX_PEACE	7		// > макс-ая пауза между треками в спокойном режиме (в обоих случаях движок выберет случайное значение от *_MIN_* и до *_MAX_* включительно)
#define SOUND_DIR				"RESOURCE\\Sounds\\"

int musNum = 0;
string musList[2];
object oMusicCache; // > кэш результатов сканирования папок с музыкой

#event_handler("LoadSceneSound", "LoadSceneSound");
#event_handler("MusicNext", "KZ|OnMusicNext");

// PLAY
int Play3DSound(string name, float x, float y, float z)
{
	InitSound();
	return SendMessage(&Sound,"lsllllllfff",MSG_SOUND_PLAY, name, SOUND_WAV_3D, VOLUME_FX, false, false, false, 0, x, y, z);
}

int Play3DSoundCached(string name, float x, float y, float z)
{
	InitSound();
	return SendMessage(&Sound,"lsllllllfff",MSG_SOUND_PLAY, name, SOUND_WAV_3D, VOLUME_FX, false, false, true, 0, x, y, z);
}

int Play3DSoundComplex(string name, float x, float y, float z, bool bLooped, bool bCached)
{
	InitSound();
	return SendMessage(&Sound,"lsllllllfff",MSG_SOUND_PLAY, name, SOUND_WAV_3D, VOLUME_FX, false, bLooped, bCached, 0, x, y, z);
}

int PlayStereoSound(string name)
{
	InitSound();
	return SendMessage(&Sound,"lslllll",MSG_SOUND_PLAY, name, SOUND_WAV_STEREO, VOLUME_FX, false, false, false);
}

int PlayStereoSoundLooped(string name)
{
	InitSound();
	return SendMessage(&Sound,"lslllll",MSG_SOUND_PLAY, name, SOUND_WAV_STEREO, VOLUME_FX, false, true, false);
}

int PlayStereoSoundLooped_JustCache(string name)
{
	InitSound();
	return SendMessage(&Sound,"lslllll",MSG_SOUND_PLAY, name, SOUND_WAV_STEREO, VOLUME_FX, true, true, false);
}

// > при TEV.Music.Cached трек продолжит звучать с места позиции прошлой остановки (если уже звучал ранее в сессии), иначе при каждом запуске будет играть с самого начала
bool KZ|MusicCached()
{
	if (CheckAttribute(&TEV, "Music.Cached"))
	{
		DeleteAttribute(&TEV, "Music.Cached");
		return true;
	}

	return false;
}

int PlayStereoOGG(string name)
{
	InitSound();
	if (MusicIsPlaying())
		StopMusic(0);
	musicID = SendMessage(&Sound,"lsllllll",MSG_SOUND_PLAY, name, SOUND_MP3_STEREO, VOLUME_MUSIC, false, false, KZ|MusicCached(), 0);
	ResumeSound(musicID, 0);
	return musicID;
}

// OTHER METHODS
void StopSound(int _id, int _fade)
{
	InitSound();

	if (_id == 0 && CheckAttribute(&TEV, "Music.KeepPlaying"))
		StopSoundExceptMusic(0, _fade, musicID);
	else
		SendMessage(&Sound, "lll", MSG_SOUND_STOP, _id, _fade);
}

// KZ > глушит все звуки, кроме музыки
void StopSoundExceptMusic(int _id, int _fade, int _track)
{
	InitSound();
	SendMessage(&Sound, "llll", MSG_SOUND_STOP, _id, _fade, _track);
}

void ResumeSound(int id, int fade)
{
	InitSound();
	SendMessage(&Sound, "lll", MSG_SOUND_RESUME, id, fade);
}

void ReleaseSound(int id)
{
	InitSound();
	SendMessage(&Sound, "ll", MSG_SOUND_RELEASE, id);
}

// SOUND SCHEMES
void ResetSoundScheme()
{
	InitSound();
	SendMessage(&Sound, "l", MSG_SOUND_SCHEME_RESET);
	DeleteAttribute(&TEV, "CurrentSoundScheme");
}

void SetSoundScheme(string schemeName)
{
	InitSound();
	if (!BlockSoundScheme(schemeName))
	{
		TEV.CurrentSoundScheme = schemeName;
	    SendMessage(&Sound, "ls", MSG_SOUND_SCHEME_SET, schemeName);
	}
}

void AddSoundScheme(string schemeName)
{
	InitSound();
	SendMessage(&Sound, "ls", MSG_SOUND_SCHEME_ADD, schemeName);
}

bool BlockSoundScheme(string schemeName)
{
	if (HasStrEx(schemeName, "rain,storm", "|") && !HasStr(schemeName, "inside") && !StrStartsWith(schemeName, "mainmenu_"))
		return CheckAttrValue(loadedlocation, "lockWeather", "Inside") || CheckAttrValue(loadedlocation, "QuestlockWeather", "23 hour");

	return false;
}

//	Теперь эта функция опеределяет звуковые схемы в игре на СУШЕ! Внутри проверяется как погода, так и время. Сделано для того, что бы не было схем,
//	которые бы игрались независимо от погоды или времени, ибо это всё-таки неудобно в использовании
void SetWeatherScheme(string scheme)
{
	string time = "";

	if (Whr_IsStorm())
	{
		if (Whr_IsNight())
			time = "_night_storm";
		else
			time = "_day_storm";
	}
	else 
	{ 
		if (Whr_IsRain())
		{
			if (Whr_IsNight())
				time = "_night_rain";
			else
				time = "_day_rain";
		}
		else
		{
			if (Whr_IsNight())
				time = "_night";
			else
				time = "_day";
		}
	}

	if (scheme != "")
		SetSoundScheme(scheme + time);
}

void SetSchemeForLocation(ref loc)
{
	pchar.GenQuest.God_hit_us = false; // нефиг воровать :D (только в домах)
	int iColony = -1;
	int iParent = -1;
	string temp, music, sound, weather, type;

	if (CheckAttribute(loc, "fastreload"))
		iColony = FindColony(loc.fastreload);

	if (CheckAttribute(loc, "parent_colony"))
		iParent = FindColony(loc.parent_colony);

	if (CheckAttribute(loc, "type"))
	{
		ResetSoundScheme();

		type = loc.type;

		if (loc.id == "Secret_Fort")
			type = "fort";
		else if (loc.id == "Secret_Fort_ammo")
			type = "ammo";

		switch (type)
		{
			case "town":
				weather = "town";

				if (Whr_IsDay())
					music = "town_day";
				else
					music = "town_night";

				if (iColony != -1)
				{
					if (Whr_IsDay())
						temp = "_day";
					else
						temp = "_night";

					music = NationShortName(sti(Colonies[iColony].nation)) + temp;
				}
			break;

			case "land": // дуэльное поле, лэндфорт и так далее
				weather = "land";
				music = "jungle_exittown";
			break;

			case "Estate": // имение
				weather = "land";
				music = "lighthouse";
			break;

			case "jungle":
				weather = "land";

				if (Whr_IsDay())
					music = "jungle_day";
				else
					music = "jungle_night";

				switch (loc.id.label)
				{
					case "ExitTown":
						if (Whr_IsDay())
							music = "jungle_exittown";
						else
							music = "jungle_night";
					break;
					case "Graveyard":
						music = "graveyard";
					break;
					case "DesMoines":
						music = "desmoines";
					break;
					case "Village":
						music = "village";
					break;
				}
			break;

			case "mayak":
				weather = "seashore";
				music = "lighthouse";
			break;

			case "seashore": 
				weather = "seashore";
				music = "shore";
			break;

			case "cave": 
				sound = "cave";
				music = "cave";
				bMonstersGen = false; //сбросить флаг монстров

				if (loc.id.label == "Grot")
					music = "grotto";
			break;

			case "dungeon": 
				sound = "dungeon";
				music = "dungeon";
				bMonstersGen = false; //сбросить флаг монстров

				if (loc.id.label == "Crypt")
					music = "crypt";
				else if (CheckAttrValue(loc, "Maltains", "1"))
					music = "maltains";
			break;

			case "mine": // TODO > посмотреть
				sound = "mine";
				music = "cave";
			break;

			case "plantation":
				weather = "land";

				if (Whr_IsDay())
					music = "plantation_day";
				else
					music = "plantation_night";
			break;

			case "house":
				sound = "house";
				music = "house";

				if (CheckAttrValue(loc, "brothel", "1"))
					music = "brothel";
				else if (loc.id.label == "portoffice")
					music = "portoffice";
				else if (CheckAttrValue(loc, "packhouse", "1"))
					music = "packhouse";
				else if (CheckAttrValue(loc, "HWIC", "1"))
					music = "HWIC";
				else if (HasStr(loc.id.label, "Ascold House"))
					music = "ascold_house";

				pchar.GenQuest.God_hit_us = true; // нефиг воровать :D
			break;

			case "tavern":
				sound = "tavern";
				music = "tavern";

				if (iColony != -1)
					music = NationShortName(sti(Colonies[iColony].nation)) + "_tavern";
			break;

			case "shop":
				sound = "shop";
				music = "shop";

				if (loc.id.label == "Usurer House")
					music = "bank";
			break;

			case "residence":
				sound = "residence";

				if (iColony != -1)
					music = NationShortName(sti(Colonies[iColony].nation)) + "_gubernator";
				else
				{
					if (HasStrEx(loc.id.label, "residence,Cabinet", "|"))
						music = "residence";
					else
					{
						music = "deck";

						if (Whr_IsDay())
							sound = "ship_day";
						else
							sound = "ship_night";
					}
				}
			break;

			case "church":
				music = "church";

				if (isDay())
					sound = "church";

				if (iColony != -1)
				{
					temp = NationShortName(sti(Colonies[iColony].nation));

					if (temp != "pir")
						music = temp + "_church";
				}

				if (loc.id.label == "Chapel")
					music = "chapel";
			break;

			case "shipyard":
				sound = "shipyard";
				music = "shipyard";
			break;

			case "fort_attack": // атакуем форт, внутренняя локация			
				sound = "fort_attack";
				music = "bitva";
			break;

			case "fort": // форт для мирных прогулок
				weather = "seashore";
				music = "fort";

				if (iParent != -1)
				{
					temp = NationShortName(sti(Colonies[iParent].nation));

					if (temp != "pir")
						music = temp + "_fort";
				}
			break;

			case "deck": // мирная палуба
				sound = "deck";

				if (Whr_IsDay())
					music = "sea_day";
				else
					music = "sea_night";
			break;

			case "deck_fight": // боевая полуба
				sound = "deck_fight";
				music = "abordage";
			break;

			case "slave_deck": // квестовая палуба
				sound = "slave_deck";

				if (Whr_IsDay())
					music = "sea_day";
				else
					music = "sea_night";
			break;

			case "boarding_cabine":
				sound = "cabine";
				music = "abordage";
			break;

			case "sailing_cabine":
				sound = "sail_cabine";

				if (Whr_IsDay())
					music = "sea_day";
				else
					music = "sea_night";
			break;

			case "incquisitio":
				sound = "incquisitio";
				music = "incquisitio";
			break;

			case "jail":
				sound = "jail";
				music = "jail";
			break;

			case "ammo":
				sound = "jail";
				music = "ammo";

				if (iParent != -1)
				{
					temp = NationShortName(sti(Colonies[iParent].nation));

					if (temp != "pir")
						music = temp + "_ammo";
				}
			break;

			case "LostShipsCity":
				weather = "LostShipsCity";
				music = "LostShipsCity";
			break;

			case "LSC_inside":
				weather = "LSC_inside";
				music = "LostShipsCity_inside";
			break;

			case "underwater":
				sound = "underwater";
				music = "underwater";
			break;

			case "teno":
				weather = "land";
				music = "teno";

				if (loc.id.label == "Incas Temple")
					music = "pyramid";
			break;

			case "teno_inside":
				sound = "teno_inside";
				music = "teno_inside";

				if (loc.id.label == "Incas Temple")
					music = "pyramid_inside";
			break;

			case "clone":
				music = "tavern";
			break;
		}
	}

	if (CheckAttribute(loc, "AoP.MusicTrack"))
		PlayMusicQuest(loc.AoP.MusicTrack, 0, true);
	else if (music != "")
		SetMusicAlarm("music_" + music);

	if (sound != "")
		SetSoundScheme(sound);
	else if (weather != "")
		SetWeatherScheme(weather);

	if (IsEntity(loc))
		SetStaticSounds(loc);
}

void SetStaticSounds(ref loc)
{
	if (!CheckAttribute(loc, "locators.sound")) return;
	string locatorName, locatorType;
	aref locator, locatorGroup;
	makearef(locatorGroup, loc.locators.sound);
	int i, locatorNameLength, locatorCount = GetAttributesNum(locatorGroup);
	if (locatorCount <= 0) return;

	for (i = 0; i < locatorCount; i++)
	{
		locator = GetAttributeN(locatorGroup, i);
		locatorName = GetAttributeName(locator);
		locatorNameLength = strlen(locatorName);
		locatorType = strcut(locatorName, 0, locatorNameLength-3);

		if (locatorType == "windmill")
			continue;

		if (Whr_IsDay() && StrHasStr(locatorType, "nightinsects,torch", true) && !StrHasStr(loc.type, "Dungeon,cave,fort_attack", true))
			continue;

		if (Whr_IsNight() && StrHasStr(locatorType, "shipyard,church", true))
			continue;

		SendMessage(&Sound, "lsllllllfff", MSG_SOUND_PLAY, locatorType, SOUND_WAV_3D, VOLUME_FX, 0, 1, 0, 0, stf(locator.x), stf(locator.y), stf(locator.z));
	}
}

void SetSchemeForSea()
{
	string music, scheme;

	if (MusicIsPlaying())
		StopMusic(0);

	ResetSoundScheme();

	if (Whr_IsNight())
	{
		if (Whr_IsStorm())
		{
			scheme = "night_storm";
			music = "storm";
		}
		else 
		{ 
			if (pchar.Ship.POS.Mode == SHIP_WAR)
				music = "sea_battle";
			else
				music = "sea_night";

			if (Whr_IsRain())
				scheme = "night_rain";
			else
				scheme = "night";
		}
	}
	else
	{
		if (Whr_IsStorm())
		{
			scheme = "day_storm";
			music = "storm";
		}
		else 
		{ 
			if (pchar.Ship.POS.Mode == SHIP_WAR)
				music = "sea_battle";
			else
				music = "sea_day";

			if (Whr_IsRain())
				scheme = "day_rain";
			else
				scheme = "day";
		}
	}

	if (scheme != "")
		SetSoundScheme("sea_" + scheme);

	if (music != "")
		KZ|MusicSelect("music_" + music);

	ResumeAllSounds();
}

void SetSchemeForMap()
{
	if (MusicIsPlaying())
		StopMusic(0);

	ResetSoundScheme();
	SetSoundScheme("sea_map");
	KZ|MusicSelect("music_map");
	ResumeAllSounds();
	bFortCheckFlagYet = false;
}

int musicID = -1;
int boardM = -1;
int interfaceCommandSound = -1;
int notificationSound = -1;

void FadeOutMusic(int _time)
{
	if (_time < 100 && _time > 0)
		_time *= 1000;

	if (musicID >= 0)
		StopSound(musicID, _time);
}

// RELOAD
void PauseAllSounds()
{
	if (CheckAttribute(&TEV, "Music.KeepPlaying"))
		StopSoundExceptMusic(0, SOUNDS_FADE_TIME, musicID);
	else
		StopSound(0, SOUNDS_FADE_TIME);
}

void ResumeAllSounds()
{
	SendMessage(&Sound,"lll",MSG_SOUND_RESUME, 0, SOUNDS_FADE_TIME);
}

// OLD VERSIONS
int PlaySoundDist3D(string name, float x, float y, float z)
{
	return Play3DSound(name, x,y,z);
}

int PlaySoundLoc3D(string name, float x, float y, float z)
{
	return Play3DSoundCached(name, x,y,z);
}

int PlaySound3D(string name, float x, float y, float z)
{
	return Play3DSound(name, x,y,z);
}

void Sound_SetVolume(int iSoundID, float fVolume)
{
	SendMessage(&Sound, "llf", MSG_SOUND_SET_VOLUME, iSoundID, fVolume);
}

int PlaySound(string name)
{
	return PlayStereoSound(name);
}

void PlayInterfaceCommand(string name)
{
	if (!SendMessage(&Sound, "ll", MSG_SOUND_IS_PLAYING, interfaceCommandSound))
	{
		interfaceCommandSound =
		SendMessage(&Sound, "lslllll", MSG_SOUND_PLAY, name, SOUND_WAV_STEREO, VOLUME_FX, false, false, false);
	}
}

void PlayCharVoice(string name) //HardCoffee не прерывать предыдущую фразу
{
	if (!SendMessage(&Sound, "ll", MSG_SOUND_IS_PLAYING, CharVoice))
	{
		charVoice =
		SendMessage(&Sound, "lslllll", MSG_SOUND_PLAY, name, SOUND_WAV_STEREO, VOLUME_SPEECH, false, false, false);
	}
}

// KZ > звук "в голове" ГГ; name - кейсом из *.ini или прямым указанием нужного файла
int PlayVoice(string name)
{
	if (charVoice != -1)
	{
		StopSound(charVoice, 0);
		charVoice = -1;
	}

	charVoice = SendMessage(&Sound, "lslllll", MSG_SOUND_PLAY, name, SOUND_WAV_STEREO, VOLUME_SPEECH, false, false, false);
	return charVoice;
}

// KZ > звук от точки в пространстве; name - кейсом из *.ini или прямым указанием нужного файла
int PlayVoice3D(string name, float x, float y, float z)
{
	if (charVoice != -1)
	{
		StopSound(charVoice, 0);
		charVoice = -1;
	}

	charVoice = Play3DSound(name, x, y, z);
	return charVoice;
}

// KZ > звук исходит от говорящего chr; name только кейсом из *.ini
void PlaySpeech(aref chr, string name)
{
	SendMessage(chr, "s", name);
}

void StopMusic(int _iFadeOut)
{
	DeleteAttribute(&TEV, "Music.Volume");
	StopSound(musicID, _iFadeOut);
	musicID = -1;
	DeleteAttribute(&TEV, "Music.CurrentTrack");
}

void PlayMusic(string _sTrackName, int _iFadeInTime)
{
	float fTrackVolume = 0.5; // > режем громкость вдвое, иммитируя нормализацию

	Restrictor(&_iFadeInTime, 0, 10000);

	if (MusicIsPlaying())
		StopMusic(0);

	if (CheckAttribute(&TEV, "Music.LoopTrack"))
	{
		musicID = SendMessage(&Sound, "lslllllllf", MSG_SOUND_PLAY, _sTrackName, SOUND_MP3_STEREO, VOLUME_MUSIC, false, true, KZ|MusicCached(), _iFadeInTime, MUSIC_CHANGE_TIME, fTrackVolume);
		DeleteAttribute(&TEV, "Music.LoopTrack");
	}
	else
		musicID = SendMessage(&Sound, "lsllllllf", MSG_SOUND_PLAY, _sTrackName, SOUND_MP3_STEREO, VOLUME_MUSIC, false, false, KZ|MusicCached(), _iFadeInTime, fTrackVolume);

	ResumeSound(musicID, 0);
}

void PlayMusicQuest(string _sTrack, int _iFadeIn, bool bLoop)
{
	if (_sTrack == "")
	{
		DeleteAttributeMass(&TEV, "Music", "LoopTrack,QuestMusic");
		StopMusic(0);
		return;
	}

	if (bLoop)
	{
		TEV.Music.LoopTrack = "";
		TEV.Music.QuestMusic = _sTrack;
	}

	PlayMusic(_sTrack, _iFadeIn);
}

int MusicGetPosition()
{
	return SendMessage(&Sound, "ll", MSG_SOUND_GET_POSITION, musicID);
}

bool MusicIsPlaying()
{
	return SendMessage(&Sound, "ll", MSG_SOUND_IS_PLAYING, musicID);
}

int SoundGetPosition(int trackID)
{
	return SendMessage(&Sound, "ll", MSG_SOUND_GET_POSITION, trackID);
}

bool SoundIsPlaying(int trackID)
{
	return SendMessage(&Sound, "ll", MSG_SOUND_IS_PLAYING, trackID);
}

//HardCoffee global volume options
/*void GetMasterVolume(ref fFX, ref fMusic, ref fSpeech)
{
	float fMain;
	SendMessage(&Sound, "leeee", MSG_SOUND_READ_INI_MASTER_VOLUME, &fMain, &fFX, &fMusic, &fSpeech);
	fFX *= fMain; fMusic *= fMain; fSpeech *= fMain;
}*/
void GetMasterVolume(ref fS, ref fM, ref fD) //Выдаст реальные значения громкости, с учётом main volume
{
	SendMessage(&Sound, "leee", MSG_SOUND_GET_MASTER_VOLUME, &fS, &fM, &fD);
}
//Установит необходимые для конкретного случая значения громкости, но не изменит текущие настройки звука, установленные пользователем
void SetMasterVolume(float fS, float fM, float fD)
{
	SendMessage(&Sound, "lfff", MSG_SOUND_SET_MASTER_VOLUME, fS, fM, fD);
}

//--------------------------------------------------------------------
// Sound Section
//--------------------------------------------------------------------
object Sound;

int alarmed = 0;
int oldAlarmed = 0;
bool seaAlarmed = false;

void SetMusicAlarm(string name)
{
	if (pchar.location == "UnderWater")
		return;

	if (alarmed == 0)
		KZ|MusicSelect(name);
	else
	{
		if (LAi_boarding_process != 0)
		{
			if (!CheckAttribute(loadedLocation, "CabinType"))
				boardM = 1;
			
			KZ|MusicRandom("&Action\Boarding,Action");
		}
		else
			KZ|MusicRandom("&Action\Fight,Action");
	}
}

void Sound_OnAlarm(bool _alarmed)
{
	alarmed = _alarmed;

	if (alarmed == oldAlarmed || pchar.location == "UnderWater" || CheckAttribute(&TEV, "Music.QuestMusic"))
		return;

	DeleteAttribute(&TEV, "Music.KeepPlaying");

	if (MusicIsPlaying())
		StopMusic(100);

	if (alarmed != 0)
	{
		SetMusicPause(false);
		if (bSeaActive && bAbordageStarted && CheckAttrValue(pchar, "boarding_info.mode", "" + SHIP_ABORDAGE))
			KZ|MusicRandom("&Action\Boarding,Action");
		else
			KZ|MusicRandom("&Action\Fight,Action");
	}
	else
	{
		SetMusicPause(true);
		KZ|MusicSelect("");
	}

	oldAlarmed = alarmed;
}

void InitSound()
{
	if (!IsEntity(&Sound))
	{
		CreateEntity(&Sound, "Sound");
		SetMusicPause(true);
	}
}

void SetMusicPause(bool bPeace)
{
	int iMin = MUSIC_PAUSE_MIN_PEACE;
	int iMax = MUSIC_PAUSE_MAX_PEACE;

	if (!bPeace)
	{
		iMin = MUSIC_PAUSE_MIN_ALARM;
		iMax = MUSIC_PAUSE_MAX_ALARM;
	}

	SendMessage(&Sound, "lll", MSG_SOUND_SET_MUSIC_PAUSE, iMin * 1000, iMax * 1000);
}

void ResetSound()
{
	ResetSoundScheme();

	StopSoundExceptMusic(0, 0, musicID);

	if (!CheckAttribute(&TEV, "Music.KeepPlaying"))
	{
		FadeOutMusic(500);
		musicID = -1;
		DeleteAttribute(&TEV, "Music.CurrentTrack");
	}

	alarmed = false;
	seaAlarmed = false;
	DeleteAttributeMass(&TEV, "Music", "Volume,ForceKeepPlaying,ForcePlayTrack,LoopTrack,QuestMusic,SeaVictoryPending");
}

void LoadSceneSound()
{
	int i = FindLoadedLocation();
	if (i != -1)
		SetSchemeForLocation(&Locations[i]);
}

// Custom Music Mod © KZ > прожатие клавиши F10 принудительно остановит звучащий трек и запустит новый
bool CustomMusicDir = true;				// Вкл. и выкл. чтение треков из папки _CUSTOM
int CharVoice = -1;						// Переменная для озвучки реплик персонажей

void KZ|MusicPlay(string track)
{
	aref arFader;
	bool bForce = CheckAttribute(&TEV, "Music.ForcePlayTrack"); // > форс идёт и сквозь фейдер сцены, и сквозь непрерывную музыку

	if (!bForce && GetEntity(arFader, "fader"))
	{
		PostEvent("MusicNext", 1000);
		return;
	}

	float volume = 0.5; // режем громкость вдвое, иммитируя нормализацию

	if (bForce || !CheckAttribute(&TEV, "Music.KeepPlaying") || !MusicIsPlaying())
	{
		DeleteAttribute(&TEV, "Music.KeepPlaying");

		if (MusicIsPlaying())
			StopMusic(0);

		if (CheckAttribute(&TEV, "Music.LoopTrack"))
		{
			musicID = SendMessage(&Sound, "lslllllllf", MSG_SOUND_PLAY, track, SOUND_MP3_STEREO, VOLUME_MUSIC, false, true, KZ|MusicCached(), MUSIC_CHANGE_TIME, MUSIC_CHANGE_TIME, volume);
			DeleteAttribute(&TEV, "Music.LoopTrack");
		}
		else
			musicID = SendMessage(&Sound, "lsllllllf", MSG_SOUND_PLAY, track, SOUND_MP3_STEREO, VOLUME_MUSIC, false, false, KZ|MusicCached(), MUSIC_CHANGE_TIME, volume);

		ResumeSound(musicID, 0);
		TEV.Music.CurrentTrack = track;
	}

	TEV.Music.Volume = volume;
}

void KZ|OnMusicNext()
{
	aref arFader;
	if (GetEntity(arFader, "fader")) { PostEvent("MusicNext", 1000); return; } // > идёт переход сцены
	if (MusicIsPlaying()) return; // > за паузу музыку уже завели (бой/смена локи)

	DeleteAttribute(&TEV, "Music.SeaVictoryPending"); // > победный трек доиграл, дальше обычная музыка

	KZ|MusicSelect("");
}

bool KZ|MusicCheckFormat(string str)
{
	// > Судя по инфе про FMOD с wiki, далеко не каждый формат читается игрой. Протестировал все, работают только эти:
	return StrEndsWith(str, ".ogg") || StrEndsWith(str, ".mp3") || StrEndsWith(str, ".wav") || StrEndsWith(str, ".flac") || StrEndsWith(str, ".wma");
}

// KZ > поиск записи в кэше по ключу, если есть
bool KZ|MusicCacheFind(string key)
{
	return CheckAttribute(&oMusicCache, key);
}

// KZ > восстановить musList/musNum из кэша (не шуршим диск, если не нужно)
void KZ|MusicCacheLoad(string key)
{
	string name;
	aref e; makearef(e, oMusicCache.(key));

	int i, cnt = sti(e.n);

	SetArraySize(&musList, 2);
	musList[0] = "";
	musList[1] = "";

	if (cnt > 0)
	{
		SetArraySize(&musList, cnt);

		for (i = 0; i < cnt; i++)
		{
			name = "f" + i;
			musList[i] = e.(name);
		}
	}

	musNum = cnt;
	KZ|MusicArray();
}

// KZ > сохранить текущие musList/musNum в кэш
void KZ|MusicCacheStore(string key)
{
	int i;
	string fname;
	aref e; makearef(e, oMusicCache.(key));

	e.n = musNum;

	for (i = 0; i < musNum; i++)
	{
		fname = "f" + i;
		e.(fname) = musList[i];
	}
}

// KZ > сброс кэша
void KZ|MusicCacheClear()
{
	DeleteAttribute(&oMusicCache, "");
}

// KZ > быстрый случайный трек из кэша
string KZ|MusicCacheRandom(string key)
{
	aref e; makearef(e, oMusicCache.(key));

	int cnt = sti(e.n);

	if (cnt < 1)
		return "";

	string name = "f" + rand(cnt - 1);

	return e.(name);
}

bool KZ|MusicCheckDir(string dirs)
{
	// > Один раз отсканировали папки и дальше черпаем из кэша.
	string cacheKey = "0|" + dirs;

	if (CustomMusicDir)
		cacheKey = "1|" + dirs;

	if (KZ|MusicCacheFind(cacheKey))
	{
		KZ|MusicCacheLoad(cacheKey);
		return musNum > 0;
	}

	object fileFinder;
	aref fileList, file;
	int i, j, n, fileNum, q = KZ|Symbol(dirs, ",");
	string tmp, musName, subFolder, musFolder = "Music\";
	bool all = false;

	musNum = 0;
	SetArraySize(&musList, 2);

	for (i = 0; i < 2; i++)
	{
		musList[i] = "";
	}

	if (dirs != "")
	{
		if (HasStr(dirs, "&"))
		{
			dirs = strdel(dirs, "&");
			all = true;
		}

		if (GetSymbol(dirs, strlen(dirs) - 1) != "\")
			dirs += "\";
	}

	for (i = 0; i <= q; i++)
	{
		subFolder = GetSubStringByNum(dirs, i);

		if (GetSymbol(subFolder, strlen(subFolder) - 1) != "\")
			subFolder += "\";

		for (j = 0; j <= 1; j++)
		{
			if (j > 0)
			{
				if (!CustomMusicDir)
					continue;

				subFolder = "_CUSTOM\" + subFolder;
			}

			tmp = musFolder + subFolder;

			if (!XI_CheckFolder(SOUND_DIR + tmp))
				continue;

			DeleteAttribute(&fileFinder, "");
			fileFinder.dir = SOUND_DIR + tmp;
			CreateEntity(&fileFinder, "FINDFILESINTODIRECTORY");

			makearef(fileList, fileFinder.filelist);
			fileNum = GetAttributesNum(fileList);

			if (fileNum > 0)
			{
				SetArraySize(&musList, musNum + fileNum);

				for (n = 0; n < fileNum; n++)
				{
					file = GetAttributeN(fileList, n);
					musName = GetAttributeValue(file);

					if (KZ|MusicCheckFormat(musName))
					{
						musList[musNum] = tmp + musName;
						musNum++;
					}
				}
			}
			DeleteClass(&fileFinder);
		}

		if (musNum > 0 && !all)
		{
			SetArraySize(&musList, musNum);
			KZ|MusicArray();
			KZ|MusicCacheStore(cacheKey);
			return true;
		}
	}

	if (musNum > 0)
		SetArraySize(&musList, musNum);

	KZ|MusicArray();
	KZ|MusicCacheStore(cacheKey);

	return musNum > 0;
}

void KZ|MusicArray()
{
	int arSize = GetArraySize(&musList);

	if (arSize < 1)
	{
		SetArraySize(&musList, 2);
		musList[0] = "";
		musList[1] = "";
	}
	else if (arSize < 2)
	{
		SetArraySize(&musList, 2);
		musList[1] = musList[0];
	}
}

string KZ|MusicRandom(string folder)
{
	string track = "";

	// > Если папка уже отсканирована, то берём случайный трек из кэша
	string cacheKey = "0|" + folder;
	if (CustomMusicDir)
		cacheKey = "1|" + folder;

	if (KZ|MusicCacheFind(cacheKey))
		track = KZ|MusicCacheRandom(cacheKey);
	else if (KZ|MusicCheckDir(folder))
		track = musList[rand(musNum - 1)]; // > разовый скан для наполнения кэша

	if (track != "")
	{
		if (0) // > turn on 1\0 turn off logs
		{
			Log_Clear();
			string dir, file;

			if (SeparatePath(track, &file, &dir))
				Logs("dir: " + SOUND_DIR + "&folder: " + dir + "&file: " + file);
			else
				Logs("track: " + SOUND_DIR + track);
		}

		KZ|MusicPlay(track);
		return track;
	}

	return track;
}

// > трек из папки в обход фейдера сцены и непрерывной музыки; вернёт false, если папка пуста
bool KZ|MusicForce(string folder)
{
	TEV.Music.ForcePlayTrack = folder;
	string track = KZ|MusicRandom(folder);
	DeleteAttribute(&TEV, "Music.ForcePlayTrack");

	return track != "";
}

// > победный трек; только форсом - иначе его глотает фейдер или залипший Music.KeepPlaying
bool KZ|MusicVictory()
{
	return KZ|MusicForce("Action\Battle\Victory");
}

// KZ > идея непрерывной музыки реквизирована из ЧМ для КС от Cheatsurfer
bool KZ|MusicKeepOnReload()
{
	bool bKeepPlaying = false; // > в локах одинакового типа музыку можно не сбрасывать
	DeleteAttribute(&TEV, "Music.KeepPlaying");

	if (reload_location_index < 0 || reload_cur_location_index < 0)
		return bKeepPlaying;

	if (reload_location_index >= MAX_LOCATIONS || reload_cur_location_index >= MAX_LOCATIONS)
		return bKeepPlaying;

	if (HasAttrValue(&InterfaceStates, "ContinuousMusic", "1"))
	{
		if (CheckAttribute(&TEV, "Music.ForceKeepPlaying"))
			TEV.Music.KeepPlaying = "";
		else
		{
			bool bOk = LAi_grp_alarmactive && !LAi_boarding_process && !CheckAttribute(pchar, "GenQuestFort.StartAttack");

			if (!bOk)
			{
				ref rLocOut = &locations[reload_cur_location_index];
				ref rLocIn = &locations[reload_location_index];

				if (CheckAttribute(&TEV, "Music.CurrentTrack") && CheckAttributeEx(rLocOut, "type,id.label", "&") && CheckAttributeEx(rLocIn, "type,id.label", "&"))
				{
					string typeOut  = rLocOut.type;
					string typeIn   = rLocIn.type;
					string labelOut = rLocOut.id.label;
					string labelIn  = rLocIn.id.label;
					string idOut    = rLocOut.id;
					string idIn     = rLocIn.id;

					if (bSeaActive)
					{
						if (HasAttrValue(&InterfaceStates, "ContinuousMusic.Ship", "1") && typeIn == typeOut && !HasStr(labelOut, "Boarding deck"))
						{
							bKeepPlaying = true;
							TEV.Music.KeepPlaying = "";	// > на корабле
						}
					}
					else
					{
						if (reload_cur_location_index == reload_location_index)
						{
							if (CheckAttrValue(rLocOut, "lockWeather", "Inside") || CheckAttrValue(rLocOut, "QuestlockWeather", "23 Hour"))
							{
								bKeepPlaying = true;
								TEV.Music.KeepPlaying = "";	// > перезагрузка локации
							}
						}
						else if (HasAttrValue(&InterfaceStates, "ContinuousMusic.Jungle", "1") && typeOut == "jungle")
						{
							if (typeIn == typeOut && !HasStrEx(labelIn, "Graveyard,Village", "|") && !HasStrEx(labelOut, "Graveyard,Village", "|"))
							{
								bKeepPlaying = true;
								TEV.Music.KeepPlaying = "";	// > джунгли
							}
						}
						else if (StrStartsWith(labelOut, "Tavern") && StrStartsWith(labelIn, "Tavern"))
							TEV.Music.KeepPlaying = "";		// > таверна и комната отдыха // TODO KZ > добавить комнатам при тавернах амбиент приглушённых звуков из зала
						else if (or(labelOut == "Store" && !HasStrEx(labelIn, "portoffice,tavern,bank", "|"), labelIn == "Store" && !HasStrEx(labelOut, "portoffice,tavern,bank", "|")))
						{
							if (or(typeOut == "Shop" && typeIn == "House" && !CheckAttribute(rLocIn, "brothel") && !HasStr(labelOut, "Brothel"), typeOut == "House" && typeIn == "Shop") && !CheckAttribute(rLocOut, "brothel") && !HasStr(labelIn, "Brothel"))
								TEV.Music.KeepPlaying = "";	// > магазин, склад магазина
						}
						else if (labelOut == "portoffice" && labelIn == "portoffice")
						{
							bKeepPlaying = true;
							TEV.Music.KeepPlaying = "";		// > портовое управление Санто-Доминго
						}
						else if (HasAttrValue(&InterfaceStates, "ContinuousMusic.House", "1") && HasStr(typeOut, "house") && HasStr(typeIn, "house") && !HasStrEx(idIn, "PortOffice,brothel,SecBrRoom", "|") && !HasStrEx(idOut, "PortOffice,brothel,SecBrRoom", "|"))
						{
							bKeepPlaying = true;
							TEV.Music.KeepPlaying = "";		// > дома и комнаты в них
						}
						else if (typeOut == "residence" && typeIn == "residence")
						{
							bKeepPlaying = true;
							TEV.Music.KeepPlaying = "";		// > резиденция Виллемстада
						}
						else if (StrStartsWith(labelOut, "Packhouse") && StrStartsWith(labelIn, "Packhouse"))
							TEV.Music.KeepPlaying = "";		// > пакгаус, офис пакгауса
						else if (HasStr(idOut, "_Bank") && HasStr(idIn, "_Bank"))
						{
							bKeepPlaying = true;
							TEV.Music.KeepPlaying = "";		// > банк, хранилище банка
						}
						else if (HasAttrValue(&InterfaceStates, "ContinuousMusic.Brothel", "1") && HasStrEx(idOut, "brothel,SecBrRoom", "|") && HasStrEx(idIn, "brothel,SecBrRoom", "|"))
							TEV.Music.KeepPlaying = "";		// > бордель
						else if (HasAttrValue(&InterfaceStates, "ContinuousMusic.LSC", "1") && HasStrEx(typeOut, "LostShipsCity,LSC_inside", "|") && !HasStr(typeIn, "underwater"))
							TEV.Music.KeepPlaying = "";		// > улица и помещения ГПК
						else if (or(idOut == "Secret_Fort", idIn == "Secret_Fort") && or(idOut == "Secret_Fort_ammo", idIn == "Secret_Fort_ammo"))
							TEV.Music.KeepPlaying = "";		// > форт в джунглях и старый арсенал
						else if (StrStartsWith(idIn, "Estate") && StrStartsWith(idOut, "Estate"))
							TEV.Music.KeepPlaying = "";
					}
				}
			}
		}
	}

	return bKeepPlaying;
}

string KZ|MusicResolveLocDir(ref loc, int iColony, int iParent, bool bOwn, string sNatTypeC, string sNatTypeP)
{
	string tmp, s, dir = "";
	bool bOk;
	string sLocType = loc.type;

	bOk = reload_location_index >= 0 && reload_cur_location_index >= 0 && CheckAttribute(&locations[reload_cur_location_index], "id.label") && CheckAttribute(&locations[reload_location_index], "id.label");

	if (StrEndsWith(loc.id, "_tavern_upstairs") || and(sLocType == "clone", CheckAttribute(loc, "id.label") && HasStr(loc.id.label, "tavern")))
		sLocType = "tavern";
	else if (bOk && or(StrEndsWith(loc.id, "_store") && locations[reload_location_index].id.label == "Store", locations[reload_cur_location_index].id.label == "Store" && locations[reload_location_index].id.label == "Store"))
		sLocType = "shop";
	else if (loc.id == "Secret_Fort")
		sLocType = "fort";
	else if (loc.id == "Secret_Fort_ammo")
		sLocType = "ammo";
	else if (StrStartsWith(loc.id, "Estate"))
		sLocType = "Estate";

	switch (sLocType)
	{
		case "town":
			tmp = "Colony\Town\";
			dir = "&" + tmp;

			if (Whr_IsDay())
				dir += "," + tmp + "Day";
			else
				dir += "," + tmp + "Night";

			if (iColony >= 0)
			{
				if (bOwn)
				{
					tmp = "Special\OwnColony\Town\";
					dir = "&" + tmp;

					if (Whr_IsDay())
						dir += "," + tmp + "Day";
					else
						dir += "," + tmp + "Night";

					if (!KZ|MusicCheckDir(dir))
					{
						tmp = "Colony\Town\";
						dir = "&" + tmp;

						if (Whr_IsDay())
							dir += ",Colony\Town\Day";
						else
							dir += ",Colony\Town\Night";

						dir += ",Colony\Town\" + sNatTypeC;

						if (Whr_IsDay())
							dir += "\Day";
						else
							dir += "\Night";

						dir += ",Colony\Town\" + sNatTypeC;
					}
				}
				else
				{
					dir += ",Colony\Town\" + sNatTypeC;

					if (Whr_IsDay())
						dir += "\Day";
					else
						dir += "\Night";

					dir += ",Colony\Town\" + sNatTypeC;
				}
			}
		break;

		case "land":
			dir = "&Land\Jungle";

			if (Whr_IsDay())
				dir += ",Land\Jungle\Day";
			else
				dir += ",Land\Jungle\Night";
		break;

		case "Estate": // музыка в имении
			dir = "Land\Lighthouse";
		break;

		case "jungle":
			dir = "&Land\Jungle";

			if (Whr_IsDay())
				dir += ",Land\Jungle\Day";
			else
				dir += ",Land\Jungle\Night";

			if (CheckAttribute(loc, "id.label"))
			{
				switch (loc.id.label)
				{
					case "ExitTown":
						tmp = "Land\Jungle\ExitTown\";
						dir = "&" + tmp;

						if (Whr_IsDay())
							dir += "," + tmp + "Day";
						else
							dir += "," + tmp + "Night";

						if (!KZ|MusicCheckDir(dir))
						{
							dir = "&Land\Jungle";

							if (Whr_IsDay())
								dir += ",Land\Jungle\Day";
							else
								dir += ",Land\Jungle\Night";
						}
					break;

					case "Graveyard":
						dir = "Land\Graveyard";

						if (!KZ|MusicCheckDir(dir))
						{
							dir = "&Land\Jungle";

							if (Whr_IsDay())
								dir += ",Land\Jungle\Day";
							else
								dir += ",Land\Jungle\Night";
						}
					break;

					case "Bucaneer_outpost":
						if (CheckAttribute(&TEV, "YoHoMusic"))
							dir = "Colony\Inside\Tavern\Pirate";
					break;

					case "DesMoines":
						dir = "Special\DesMoines";

						if (!KZ|MusicCheckDir(dir))
						{
							dir = "&Land\Jungle";

							if (Whr_IsDay())
								dir += ",Land\Jungle\Day";
							else
								dir += ",Land\Jungle\Night";
						}
					break;

					case "Village":
						dir = "Land\Village";
					break;
				}
			}
		break;

		case "mayak":
			dir = "Land\Lighthouse";
		break;

		case "seashore":
			dir = "Land\Shore";
		break;

		case "cave":
			dir = "&Land\Underground";

			if (loc.id.label == "Grot")
				dir += ",Land\Underground\Grotto";
			else
				dir += ",Land\Underground\Cave";
		break;

		case "dungeon":
			tmp = "Land\Underground\";
			dir = "&" + tmp + "," + tmp + "Dungeon";

			if (loc.id.label == "Crypt")
				dir = tmp + "Crypt," + tmp + "Dungeon," + tmp;
			else
			{
				if (CheckAttrValue(loc, "Maltains", "1"))
					dir = "Special\Malta," + tmp + "Dungeon," + tmp;
			}
		break;

		case "mine":
			dir = "Land\Mine";
		break;

		case "plantation":
			dir = "&Land\Plantation";

			if (Whr_IsDay())
				dir += ",Land\Plantation\Day";
			else
				dir += ",Land\Plantation\Night";
		break;

		case "house": // TODO > убрать это месиво и раскидать все локи по типу
			tmp = "Colony\Inside\";
			dir = tmp + "House";

			if (loc.id.label == "portoffice")
				dir = tmp + "Portoffice," + dir;
			else
			{
				if (CheckAttrValue(loc, "brothel", "1"))
				{
					tmp += "Brothel\";

					if (HasAttrValue(&InterfaceStates, "ContinuousMusic.Brothel", "1"))
					{
						dir = "&" + tmp + "Hall," + tmp + "Madam," + tmp + "Room," + tmp;

						if (!KZ|MusicCheckDir(dir))
							dir = tmp + "House";
					}
					else
					{
						dir = tmp + "Hall," + tmp + ",Colony\Inside\House";

						if (HasStr(loc.id, "SecBrRoom") && KZ|MusicCheckDir(tmp + "Madam"))
							dir = tmp + "Madam," + tmp + "Hall," + tmp + ",Colony\Inside\House";
					}
				}
				else
				{
					if (HasStr(loc.id.label, "Brothel Room"))
					{
						tmp += "Brothel\";

						if (HasAttrValue(&InterfaceStates, "ContinuousMusic.Brothel", "1"))
							dir = "&" + tmp + "Hall," + tmp + "Madam," + tmp + "Room," + tmp;
						else
							dir = tmp + "Room," + tmp + "," + dir;
					}
					else
					{
						if (HasStr(loc.id.label, "PackhouseOffice") || CheckAttrValue(loc, "packhouse", "1"))
							dir = tmp + "Packhouse," + dir;
						else
						{
							if (CheckAttrValue(loc, "HWIC", "1"))
								dir = "Special\HWIC," + dir;
						}
					}
				}
			}

			s = "Colony\Inside\House\Personal\";
			tmp = "Colony\Inside\House";

			if (loc.id.label == "Ascold House")
				dir = s + "Ascold," + s + "," + tmp;
			else
			{
				if (loc.id.label == "Morgan's House")
					dir = s + "Morgan," + s + "," + tmp;
				else
				{
					if (HasStrEx(loc.id.label, "Apteka,Farmacia,Drugstore", "|"))
						dir = s + "Drugstore," + s + "," + tmp;
				}
			}
		break;
		
		case "tavern":
			dir = "&Colony\Inside\Tavern";

			if (iColony >= 0)
			{
				if (bOwn)
					dir = "Special\OwnColony\Inside\Tavern,Colony\Inside\Tavern\" + sNatTypeC + ",Colony\Inside\Tavern";
				else
					dir += ",Colony\Inside\Tavern\" + sNatTypeC;
			}
			else
				dir += "\Pirate";
		break;
		
		case "shop":
			dir = "Colony\Inside\Store";

			if (loc.id.label == "Usurer House")
				dir = "Colony\Inside\Bank";
		break;
		
		case "residence":
			if (HasStrEx(loc.id.label, "cabine,Campus,Deck", "|") && loc.id.label != "cabinet")
			{
				if (HasAttrValue(&InterfaceStates, "ContinuousMusic.Ship", "1"))
					dir = "&Sea\Ship,Sea\Ship\Cabin,Sea\Ship\Campus,Sea\Ship\Deck";
				else
				{
					if (HasStr(loc.id.label, "cabine"))
						dir = "&Sea\Ship\Cabin,Sea\Ship";
					else
					{
						if (HasStr(loc.id.label, "Campus"))
							dir = "&Sea\Ship\Campus,Sea\Ship";
						else
						{
							if (HasStr(loc.id.label, "Deck"))
								dir = "&Sea\Ship\Deck,Sea\Ship";
						}
					}
				}
			}
			else
			{
				dir = "&Colony\Inside\Governor";

				if (iColony >= 0)
				{
					if (bOwn)
						dir = "Special\OwnColony\Inside\Governor,Colony\Inside\Governor\" + sNatTypeC + ",Colony\Inside\Governor";
					else
						dir += ",Colony\Inside\Governor\" + sNatTypeC;
				}

				if (!KZ|MusicCheckDir(dir))
					dir = "Colony\Inside\House";
			}
		break;
		
		case "church":
			dir = "&Colony\Inside\Church";

			if (iColony >= 0)
				dir += ",Colony\Inside\Church\" + sNatTypeC;
		break;

		case "shipyard":
			dir = "Colony\Inside\Shipyard";

			if (CheckAttrValue(loc, "packhouse", "1"))
				dir = "Colony\Inside\Packhouse,Colony\Inside\Shipyard";
		break;

		case "fort_attack":
			dir = "&Action\Boarding,Boarding";
		break;

		case "fort":
			dir = "&Land\Fort";

			if (iParent >= 0)
				dir += ",Land\Fort\" + sNatTypeP;
		break;

		case "deck":
			dir = "Sea\Ship\Deck,Sea\Ship";
		break;

		case "deck_fight":
			dir = "Action\Boarding,Action";
		break;

		case "slave_deck":
			dir = "Sea\Ship\Deck,Sea\Ship";
		break;

		case "boarding_cabine":
			dir = "Action\Boarding,Action";
		break;

		case "sailing_cabine":
			dir = "Sea\Ship\Cabin,Sea\Ship";
		break;

		case "incquisitio":
			dir = "Special\Inquisition,Colony\Inside\Jail";
		break;

		case "jail":
			dir = "Colony\Inside\Jail";
		break;

		case "ammo":
			dir = "&Land\Fort\Armory";

			if (iParent >= 0)
			{
				dir += ",Land\Fort\Armory\" + sNatTypeP;

				if (!KZ|MusicCheckDir(dir))
					dir = "&Land\Fort\" + sNatTypeP + ",Land\Fort";
			}
			else
			{
				if (!KZ|MusicCheckDir(dir))
					dir = "Land\Fort";
			}
		break;

		case "LostShipsCity":
			dir = "Special\LSC";

			if (CheckAttribute(&TEV, "FinalMusicLSC"))
			{
				tmp = "Special\LSC\Final";

				if (KZ|MusicCheckDir(tmp))
					dir = tmp + "," + dir;
			}
		break;

		case "LSC_inside":
			dir = "Special\LSC\Inside,Special\LSC";

			if (CheckAttribute(loc, "id.label") && HasStrEx(loc.id.label, "EsmeraldaStoreBig,FleuronTavern,GloriaChurch,SanAugustineResidence,TartarusPrison", "|"))
			{
				tmp = FindStringBeforeSubStr(loc.id.label, " ");

				switch (tmp)
				{
					case "GloriaChurch": tmp = "Church"; break;
					case "TartarusPrison": tmp = "Prison"; break;
					case "SanAugustineResidence": tmp = "Governor"; break;
					case "EsmeraldaStoreBig": tmp = "Store"; break;
					case "FleuronTavern": tmp = "Tavern"; break;
				}

				tmp = "Special\LSC\Inside\" + tmp;

				if (KZ|MusicCheckDir(tmp))
					dir = tmp + "," + dir;
			}
		break;

		case "underwater":
			dir = "Special\Underwater";
		break;

		case "teno":
			dir = "Land\Teno";

			if (loc.id.label == "Incas Temple")
				dir = "Land\Pyramid," + dir;
		break;

		case "teno_inside":
			dir = "Land\Teno\Inside,Land\Teno";

			if (HasStrEx(loc.id.label, "Incas Temple,TempleTreasure", "|"))
				dir = "Land\Pyramid\Inside,Land\Pyramid," + dir;
		break;
	}

	return dir;
}

bool KZ|MusicSelect(string str)
{
	int iLoc = FindLoadedLocation();
	int iColony = -1;
	int iParent = -1;
	bool bOk, bOwn = false;
	string s, sNatShortC, sNatTypeC, sNatShortP, sNatTypeP, tmp, dir = "";
	ref loc;

	if (CheckAttribute(&TEV, "Music.ForcePlayTrack"))
	{
		KZ|MusicRandom(TEV.Music.ForcePlayTrack);
		DeleteAttribute(&TEV, "Music.ForcePlayTrack");
		return true;
	}

	if (InterfaceStates.Launched == "1")
	{
		if (CheckAttribute(&TEV, "MAINMENU") || CurrentInterface == INTERFACE_MAINMENU || CurrentInterface == INTERFACE_CHARACTER_SELECT)
		{
			KZ|MusicRandom("Menu");
			return true;
		}

		switch (CurrentInterface)
		{
			case INTERFACE_FRAMEFORM: // TODO > check
				return true;
			break;

			case INTERFACE_RANSACK_MAIN:
				KZ|MusicRandom("Action\Boarding\Plunder");
				return true;
			break;
		}
	}

	// > бой только что кончился: победный трек звучит до конца, а не подменяется обычным морским
	if (CheckAttribute(&TEV, "Music.SeaVictoryPending"))
	{
		if (bSeaActive && !bAbordageStarted && !IsEntity(&worldMap))
		{
			if (KZ|MusicVictory())
				return true;
		}

		DeleteAttribute(&TEV, "Music.SeaVictoryPending"); // > трека нет или мы уже не в море - заявку снимаем
	}

/*	if (str != "") // TODO > if (HasStr(str, "dir")) KZ|MusicRandom(dir);
	{
		if (HasStr(str, "storm_end"))
		{
			KZ|MusicRandom("Sea\Storm\End");
			return true;
		}
		else if (HasStr(str, "ship_victory"))
		{
			KZ|MusicRandom("Action\Battle\Victory");
			return true;
		}
	}*/

	if (IsEntity(&worldMap))
		dir = "Sea\Map";
	else
	{
		if (bSeaActive && !bAbordageStarted)
		{
			switch (sti(pchar.Ship.POS.Mode))
			{
				case SHIP_SAIL:
					if (Whr_IsStorm() && bStorm)
						dir = "Sea\Storm";
					else
					{
						if (Whr_IsDay())
							dir = "&Sea\Day,Sea";
						else
							dir = "&Sea\Night,Sea";
					}
				break;

				case SHIP_WAR:
					dir = "&Action\Battle,Action";
				break;

				case SHIP_STORM:
					if (Whr_IsStorm() && bStorm)
						dir = "Sea\Storm";
					else
					{
						// > шторм кончился, а режим ещё штормовой: пустая папка оставляла тишину и залипший Music.KeepPlaying
						if (Whr_IsDay())
							dir = "&Sea\Day,Sea";
						else
							dir = "&Sea\Night,Sea";
					}
				break;
			}
		}
		else
		{
			if (alarmed > 0)
			{
				if (LAi_boarding_process)
					dir = "&Action\Boarding,Action";
				else
				{
					if (iLoc >= 0)
					{
						loc = &Locations[iLoc];
						
						if (CheckAttribute(loc, "type"))
						{
							if (HasStr(loc.type, "underwater"))
								dir = "Special\Underwater";
							else
								dir = "&Action\Fight,Action";
						}
					}
				}
			}
			else
			{
				if (iLoc >= 0)
				{
					loc = &Locations[iLoc];

					if (CheckAttribute(loc, "fastreload"))
					{
						iColony = FindColony(loc.fastreload);
						if (iColony >= 0)
						{
							sNatShortC = NationShortName(sti(Colonies[iColony].nation));
							sNatTypeC = GetNationNameByType(sti(Colonies[iColony].nation));
							bOwn = sti(colonies[iColony].HeroOwn) == true;
						}
					}

					if (CheckAttribute(loc, "parent_colony"))
					{
						iParent = FindColony(loc.parent_colony);
						if (iParent >= 0)
						{
							sNatShortP = NationShortName(sti(Colonies[iParent].nation));
							sNatTypeP = GetNationNameByType(sti(Colonies[iParent].nation));
						}
					}

					if (CheckAttribute(loc, "type"))
						dir = KZ|MusicResolveLocDir(loc, iColony, iParent, bOwn, sNatTypeC, sNatTypeP);
				}
			}
		}
	}

	if (KZ|MusicRandom(dir) != "")
		return true;

	return false;
}

void KZ|Mute(bool mute)
{
	float v = !mute;

	Sound_SetVolume(0, v);

	if (v > 0.0 && CheckAttribute(&TEV, "Music.Volume"))
		Sound_SetVolume(musicID, stf(TEV.Music.Volume));
}

void KZ|Volume(float m, float s)
{	
	Restrictor(&m, 0.0, 1.0);
	Restrictor(&s, 0.0, 1.0);

	SendMessage(&Sound, "llf", MSG_SOUND_SET_VOLUME, 0, s);
	if (musicID > 0)
		SendMessage(&Sound, "llf", MSG_SOUND_SET_VOLUME, musicID, m);
}

int KZ|Symbol(string str, string sym)
{
	if (sym == "")
		return 0;

	int len = strlen(&str);
	int symLen = strlen(&sym);

	if (len < symLen)
		return 0;

	int q = 0;
	int n = findSubStr(&str, sym, 0);

	while (n >= 0)
	{
		q++;
		n = findSubStr(&str, sym, n + symLen);
	}

	return q;
}

void KZ|MusicCreateFolders()
{
	int i = 0;
	string s, dir = SOUND_DIR + "Music\\";

	while (i < 2)
	{
		if (i == 1)
			dir = SOUND_DIR + "Music\_CUSTOM\\";

		XI_CreateFolder(dir + "Menu");
		XI_CreateFolder(dir + "Action\Battle\Victory");
		XI_CreateFolder(dir + "Action\Boarding\Plunder");
		XI_CreateFolder(dir + "Action\Fight");

		s = dir + "Colony\Inside\\";
		XI_CreateFolder(s + "Bank");
		XI_CreateFolder(s + "Brothel\Madam");
		XI_CreateFolder(s + "Brothel\Room");
		XI_CreateFolder(s + "Church\England");
		XI_CreateFolder(s + "Church\France");
		XI_CreateFolder(s + "Church\Holland");
		XI_CreateFolder(s + "Church\Spain");
		XI_CreateFolder(s + "Governor\England");
		XI_CreateFolder(s + "Governor\France");
		XI_CreateFolder(s + "Governor\Holland");
		XI_CreateFolder(s + "Governor\Pirate");
		XI_CreateFolder(s + "Governor\Spain");
		XI_CreateFolder(s + "Jail");
		XI_CreateFolder(s + "Packhouse");
		XI_CreateFolder(s + "Portoffice");
		XI_CreateFolder(s + "Shipyard");
		XI_CreateFolder(s + "Store");
		XI_CreateFolder(s + "Tavern\England");
		XI_CreateFolder(s + "Tavern\France");
		XI_CreateFolder(s + "Tavern\Holland");
		XI_CreateFolder(s + "Tavern\Pirate");
		XI_CreateFolder(s + "Tavern\Spain");

		s = dir + "Land\\";
		XI_CreateFolder(s + "Fort\Armory\England");
		XI_CreateFolder(s + "Fort\Armory\France");
		XI_CreateFolder(s + "Fort\Armory\Holland");
		XI_CreateFolder(s + "Fort\Armory\Spain");
		XI_CreateFolder(s + "Fort\England");
		XI_CreateFolder(s + "Fort\France");
		XI_CreateFolder(s + "Fort\Holland");
		XI_CreateFolder(s + "Fort\Spain");
		XI_CreateFolder(s + "Graveyard");
		XI_CreateFolder(s + "Jungle\Day");
		XI_CreateFolder(s + "Jungle\ExitTown\Day");
		XI_CreateFolder(s + "Jungle\ExitTown\Night");
		XI_CreateFolder(s + "Jungle\Night");
		XI_CreateFolder(s + "Lighthouse");
		XI_CreateFolder(s + "Plantation\Day");
		XI_CreateFolder(s + "Plantation\Night");
		XI_CreateFolder(s + "Pyramid\Inside");
		XI_CreateFolder(s + "Shore");
		XI_CreateFolder(s + "Teno\Inside");
		XI_CreateFolder(s + "Underground\Cave");
		XI_CreateFolder(s + "Underground\Crypt");
		XI_CreateFolder(s + "Underground\Dungeon");
		XI_CreateFolder(s + "Underground\Grotto");
		XI_CreateFolder(s + "Village");

		XI_CreateFolder(dir + "Sea\Day");
		XI_CreateFolder(dir + "Sea\Map");
		XI_CreateFolder(dir + "Sea\Night");
		XI_CreateFolder(dir + "Sea\Storm\End");
		XI_CreateFolder(dir + "Sea\Ship\Cabin");
		XI_CreateFolder(dir + "Sea\Ship\Campus");
		XI_CreateFolder(dir + "Sea\Ship\Deck");

		s = dir + "Special\OwnColony\Inside\\";
		XI_CreateFolder(s + "Governor");
		XI_CreateFolder(s + "Tavern");

		s = dir + "Special\\";
		XI_CreateFolder(s + "HWIC");
		XI_CreateFolder(s + "Inquisition");
		XI_CreateFolder(s + "Malta");
		XI_CreateFolder(s + "OwnColony\Town\Day");
		XI_CreateFolder(s + "OwnColony\Town\Night");

		s = dir + "Special\LSC\Inside\\";
		XI_CreateFolder(s + "Church");
		XI_CreateFolder(s + "Governor");
		XI_CreateFolder(s + "Prison");
		XI_CreateFolder(s + "Store");
		XI_CreateFolder(s + "Tavern");
		XI_CreateFolder(dir + "Special\LSC\Underwater");

		s = dir + "Colony\Town\\";
		XI_CreateFolder(s + "Day");
		XI_CreateFolder(s + "England\Day");
		XI_CreateFolder(s + "England\Night");
		XI_CreateFolder(s + "France\Day");
		XI_CreateFolder(s + "France\Night");
		XI_CreateFolder(s + "Holland\Day");
		XI_CreateFolder(s + "Holland\Night");
		XI_CreateFolder(s + "Night");
		XI_CreateFolder(s + "Pirate\Day");
		XI_CreateFolder(s + "Pirate\Night");
		XI_CreateFolder(s + "Spain\Day");
		XI_CreateFolder(s + "Spain\Night");

		s = dir + "Colony\Inside\House\Personal\\";
		XI_CreateFolder(s + "Drugstore");
		XI_CreateFolder(s + "Ascold");
		XI_CreateFolder(s + "Morgan");
		XI_CreateFolder(dir + "Special\DesMoines");
		XI_CreateFolder(dir + "Special\Quest\PDM");

		i++;
	}
}

string VoiceGetLanguage()
{
	string vLang = "russian";
	if (LanguageGetLanguage() != vLang)
		vLang = "english";
	return vLang;
}

// DEFINES
#define MUSIC_CHANGE_TIME  3000
#define MUSIC_SILENCE_TIME 180000.0
#define SOUNDS_FADE_TIME   200

#event_handler("LoadSceneSound", "LoadSceneSound");

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
	return SendMessage(&Sound,"lsllll",MSG_SOUND_PLAY, name, SOUND_WAV_STEREO, VOLUME_FX, false, true, false);
}

int PlayStereoSoundLooped_JustCache(string name)
{
	InitSound();
	return SendMessage(&Sound,"lslllll",MSG_SOUND_PLAY, name, SOUND_WAV_STEREO, VOLUME_FX, true, true, false);
}

int PlayStereoOGG(string name)
{
	InitSound();
	StopMusic();
	musicID = SendMessage(&Sound,"lsllllll",MSG_SOUND_PLAY, name, SOUND_MP3_STEREO, VOLUME_MUSIC, false, false, false, 0); //fix boal
	KZ|MusicRestart(musicID);
	return musicID;
}

// OTHER METHODS
void StopSound(int id, int fade)
{
	InitSound();
	SendMessage(&Sound, "lll", MSG_SOUND_STOP, id, fade);
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
	if(CheckAttribute(&TEV, "CurrentSoundScheme"))
	{
		DeleteAttribute(&TEV, "CurrentSoundScheme");
	}
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
	{
		if (or(CheckAttribute(loadedlocation, "lockWeather") && loadedlocation.lockWeather == "Inside", CheckAttribute(loadedlocation, "QuestlockWeather") && loadedlocation.QuestlockWeather == "23 hour"))
			return true;
	}

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
				else if (CheckAttribute(loc, "Maltains") && sti(loc.Maltains) == true)
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

				if (CheckAttribute(loc, "brothel") && sti(loc.brothel) == true)
					music = "brothel";
				else if (loc.id.label == "portoffice")
					music = "portoffice";
				else if (CheckAttribute(loc, "packhouse") && sti(loc.packhouse) == true)
					music = "packhouse";
				else if (CheckAttribute(loc, "HWIC") && sti(loc.HWIC) == true)
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

	if (music != "")
		SetMusicAlarm("music_" + music);

	if (sound != "")
		SetSoundScheme(sound);
	else if (weather != "")
		SetWeatherScheme(weather);

	if (loc)
		SetStaticSounds(loc);
}

void SetStaticSounds(ref loc)
{
	if (!IsEntity(loc)) return;
	string locatorName, locatorType;
	if (!CheckAttribute(loadedLocation, "locators.sound")) return;
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

		if (Whr_IsDay() && StrHasStr(locatorType, "nightinsects,torch", 1) && !StrHasStr(loc.type, "Dungeon,cave,fort_attack", 1))
			continue;

		if (Whr_IsNight() && StrHasStr(locatorType, "shipyard,church", 1))
			continue;

		SendMessage(&Sound, "lsllllllfff", MSG_SOUND_PLAY, locatorType, SOUND_WAV_3D, VOLUME_FX, 0, 1, 0, 0, stf(locator.x), stf(locator.y), stf(locator.z));
	}
}

void SetSchemeForSea()
{
	string music, scheme;

	StopMusic();
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
			{
				if (Whr_IsDay())
					music = "sea_day";
				else
					music = "sea_night";
			}

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
			{
				if (Whr_IsDay())
					music = "sea_day";
				else
					music = "sea_night";
			}

			if (Whr_IsRain())
				scheme = "day_rain";
			else
				scheme = "day";
		}
	}

	if (scheme != "")
		SetSoundScheme("sea_" + scheme);

	if (music != "")
	{
		if (CheckAttribute(&TEV, "Music.ForcePlayTrack"))
		{
			music = TEV.Music.ForcePlayTrack;
			DeleteAttribute(&TEV, "Music.ForcePlayTrack");
		}

		KZ|Select("music_" + music);
	}

	ResumeAllSounds();
}

void SetSchemeForMap()
{
	StopMusic();
	ResetSoundScheme();
	SetSoundScheme("sea_map");
	KZ|Select("music_map");
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
	SendMessage(&Sound,"lll",MSG_SOUND_STOP, 0, SOUNDS_FADE_TIME);
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

int PlaySoundComplex(string sSoundName, bool bSimpleCache, bool bLooped, bool bCached, int iFadeTime)
{
	return SendMessage(&Sound,"lsllllll",MSG_SOUND_PLAY,VOLUME_FX,sSoundName,SOUND_WAV_3D,bSimpleCache,bLooped,bCached,iFadeTime);
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

void StopMusic()
{
	DeleteAttribute(&TEV, "Music.Volume");
	StopSound(musicID, 0);

	// > TODO restart OR keep playing
/*	if (!CheckAttribute(&TEV, "Music.KeepPlaying"))
	{
		ReleaseSound(musicID);
		musicID = -1;
	}*/
}

void PlayMusic(string _sTrackName, int _iFadeTime)
{
	float fTrackVolume = 0.5; // > режем громкость вдвое, иммитируя нормализацию

	Restrictor(&_iFadeTime, 0, 10000);
	StopMusic();

	if (CheckAttribute(&TEV, "Music.LoopTrack"))
	{
		musicID = SendMessage(&Sound, "lslllllllf", MSG_SOUND_PLAY, _sTrackName, SOUND_MP3_STEREO, VOLUME_MUSIC, true, true, false, _iFadeTime, MUSIC_CHANGE_TIME, fTrackVolume);
		DeleteAttribute(&TEV, "Music.LoopTrack");
	}
	else
		musicID = SendMessage(&Sound, "lsllllllf", MSG_SOUND_PLAY, _sTrackName, SOUND_MP3_STEREO, VOLUME_MUSIC, true, false, false, _iFadeTime, fTrackVolume);

	KZ|MusicRestart(musicID);
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

void GetMasterVolume(ref fS, ref fM, ref fD)
{
	SendMessage(&Sound, "leee", MSG_SOUND_GET_MASTER_VOLUME, &fS, &fM, &fD);
}

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
		KZ|Select(name);
	else
	{
		if (LAi_boarding_process != 0)
		{
			if (!CheckAttribute(loadedLocation, "CabinType"))
				boardM = 1;
			
			KZ|Random("&Action\Boarding,Action");
		}
		else
			KZ|Random("&Action\Fight,Action");
	}
}

void Sound_OnAllarm()
{
	Sound_OnAlarm(GetEventData());
}

void Sound_OnAlarm(bool _alarmed)
{
	alarmed = _alarmed;

	if (alarmed == oldAlarmed || pchar.location == "UnderWater" || CheckAttribute(&TEV, "Music.QuestMusic"))
		return;

	DeleteAttribute(&TEV, "Music.KeepPlaying");
	StopMusic();

	if (alarmed != 0)
	{
		if (bSeaActive && bAbordageStarted && CheckAttrValue(pchar, "boarding_info.mode", "" + SHIP_ABORDAGE))
			KZ|Random("&Action\Boarding,Action");
		else
			KZ|Random("&Action\Fight,Action");
	}
	else
		KZ|Select("");

	oldAlarmed = alarmed;
}

void InitSound()
{
	if (!IsEntity(&Sound))
	{
		CreateEntity(&Sound, "Sound");
		SetEventHandler("eventAllarm", "Sound_OnAllarm", 0);
	}
}

void ResetSound()
{
	ResetSoundScheme();
	StopSound(0, 0);
	PauseAllSounds();

	if (!CheckAttribute(&TEV, "Music.KeepPlaying") || !CheckAttribute(&TEV, "Music.CurrentTrack"))
	{
		if (musicID > 0) StopSound(musicID, 0);
		musicID = -1;
		DeleteAttribute(&TEV, "Music.CurrentTrack");
	}
	else
	{
		if (!CheckAttribute(&TEV, "Music.CurrentTrack"))
			KZ|Select("");
		else
		{
			if (!CheckAttribute(&TEV, "Music.Volume"))
				TEV.Music.Volume = "0.5";

			musicID = SendMessage(&Sound, "lsllllllf", MSG_SOUND_PLAY, TEV.Music.CurrentTrack, SOUND_MP3_STEREO, VOLUME_MUSIC, false, false, true, 500, stf(TEV.Music.Volume));
			SendMessage(&Sound, "ll", MSG_SOUND_RESTART, musicID);
		}
	}

	alarmed = false;
	seaAlarmed = false;
	DeleteAttributeMass(&TEV, "Music", "Volume,ForceKeepPlaying,ForcePlayTrack,LoopTrack,QuestMusic");
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

void KZ|Music(string track)
{
	DelEventHandler("MusicUpdateSea", "KZ|MusicUpdateSea");

	aref arFader;
	if (!CheckAttribute(&TEV, "Music.ForcePlayTrack") && GetEntity(arFader, "fader"))
	{
		KZ|MusicRefresh(1000);
		return;
	}

	float volume = 0.5; // режем громкость вдвое, иммитируя нормализацию

	if (!CheckAttribute(&TEV, "Music.KeepPlaying"))
	{
		StopMusic();

		if (CheckAttribute(&TEV, "Music.LoopTrack"))
		{
			musicID = SendMessage(&Sound, "lslllllllf", MSG_SOUND_PLAY, track, SOUND_MP3_STEREO, VOLUME_MUSIC, true, true, false, 3000, MUSIC_CHANGE_TIME, volume);
			DeleteAttribute(&TEV, "Music.LoopTrack");
		}
		else
			musicID = SendMessage(&Sound, "lsllllllf", MSG_SOUND_PLAY, track, SOUND_MP3_STEREO, VOLUME_MUSIC, true, false, false, 3000, volume);

		KZ|MusicRestart(musicID);
		TEV.Music.CurrentTrack = track;
	}

	KZ|MusicRefresh(0);

	TEV.Music.Volume = volume;
}

void KZ|MusicRestart(int iTrackID)
{
	SendMessage(&Sound, "ll", MSG_SOUND_RESTART, iTrackID);
	SendMessage(&Sound, "lll", MSG_SOUND_RESUME, iTrackID, MUSIC_CHANGE_TIME);
}

void KZ|MusicRefresh(int iRefreshTime)
{
	int iTime = 8000;
	float fTime = 8.0;

	if (iRefreshTime > 0)
	{
		iTime = iRefreshTime;
		fTime = makefloat(iRefreshTime * 0.001);
	}

	if (and(bSeaActive, !bAbordageStarted) || IsEntity(&worldMap) || CheckAttribute(&TEV, "MAINMENU") || CurrentInterface == INTERFACE_MAINMENU)
	{
		SetEventHandler("MusicUpdateSea", "KZ|MusicUpdateSea", 0);
		PostEvent("MusicUpdateSea", iTime);
	}
	else
	{
		DeleteAttribute(&lai_questdelays, "KZ|MusicUpdateLoc");
		LAi_MethodDelay("KZ|MusicUpdateLoc", fTime);
	}
}

void KZ|MusicUpdate()
{
	aref arFader; if (GetEntity(arFader, "fader")) return;

	if (!MusicIsPlaying())
	{
		DeleteAttribute(&TEV, "Music.KeepPlaying");
		StopMusic();
		KZ|Select("");
	}
}

void KZ|MusicUpdateLoc()
{
	DeleteAttribute(&lai_questdelays, "KZ|MusicUpdateLoc");

	if (sti(InterfaceStates.Launched) && CurrentInterface == INTERFACE_FRAMEFORM)
	{
		LAi_MethodDelay("KZ|MusicUpdateLoc", 5.0);
		return;
	}

	LAi_MethodDelay("KZ|MusicUpdateLoc", 8.0);
	KZ|MusicUpdate();
}

void KZ|MusicUpdateSea()
{
	if (and(bSeaActive, !bAbordageStarted) || IsEntity(&worldMap))
	{
		KZ|MusicUpdate();
		PostEvent("MusicUpdateSea", 5000);
	}
}

bool KZ|Format(string str)
{
	// Судя по инфе про FMOD с wiki, далеко не каждый формат читается игрой. Протестировал все, работают только эти:
	if (StrEndsWith(str, ".ogg") || StrEndsWith(str, ".mp3") || StrEndsWith(str, ".wav") || StrEndsWith(str, ".flac") || StrEndsWith(str, ".wma"))
		return true;
	
	return false;
}

#define SOUND_DIR "RESOURCE\\Sounds\\"
int musNum = 0;
string musList[2];

bool KZ|Check(string dirs)
{
	object fileFinder;
	aref fileList, file;
	int i, j, n, fileNum, q = KZ|Symbol(dirs, ",");
	string tmp, musName, subFolder, musFolder = "Music\";
	bool all = false;

	musNum = 0;
	musList[2];
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
				for (n = 0; n < fileNum; n++)
				{
					file = GetAttributeN(fileList, n);
					musName = GetAttributeValue(file);

					if (KZ|Format(musName))
					{
						musNum++;
						SetArraySize(&musList, musNum);
						musList[musNum - 1] = tmp + musName;
					}
				}
			}
			DeleteClass(&fileFinder);
		}

		if (musNum > 0 && !all)
		{
			KZ|MusicArray();
			return true;
		}
	}

	KZ|MusicArray();

	if (musNum > 0)
		return true;

	return false;
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

string KZ|Random(string folder)
{
	string track;

	if (KZ|Check(folder))
	{
		musNum = rand(musNum - 1);
		track = musList[musNum];

		if (track != "")
		{
			if (0)
			{
				Log_Clear();
				string dir, file;

				if (SeparatePath(track, &file, &dir))
					Logs("dir: " + SOUND_DIR + "&folder: " + dir + "&file: " + file);
				else
					Logs("track: " + SOUND_DIR + track);
			}

			KZ|Music(track);
			return track;
		}
	}

	return "";
}

bool KZ|Select(string str)
{
	int iLoc = FindLoadedLocation();
	int iColony = -1;
	int iParent = -1;
	bool bOk, bOwn = false;
	string s, sNatShortC, sNatTypeC, sNatShortP, sNatTypeP, tmp, dir = "";
	ref loc;

	if (sti(InterfaceStates.Launched))
	{
		if (CheckAttribute(&TEV, "MAINMENU") || CurrentInterface == INTERFACE_MAINMENU || CurrentInterface == INTERFACE_CHARACTER_SELECT)
		{
			KZ|Random("Menu");
			return true;
		}

		switch (CurrentInterface)
		{
			case INTERFACE_FRAMEFORM: // TODO > check
				return true;
			break;

			case INTERFACE_RANSACK_MAIN:
				KZ|Random("Action\Boarding\Plunder");
				return true;
			break;
		}
	}

	if (str != "")
	{
		if (HasStr(str, "storm_end"))
		{
			KZ|Random("Sea\Storm\End");
			return true;
		}
		else if (HasStr(str, "ship_victory"))
		{
			KZ|Random("Action\Battle\Victory");
			return true;
		}
	}

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
						sNatShortC = NationShortName(sti(Colonies[iColony].nation));
						sNatTypeC = GetNationNameByType(sti(Colonies[iColony].nation));
						bOwn = sti(colonies[iColony].HeroOwn) == true;
					}

					if (CheckAttribute(loc, "parent_colony"))
					{
						iParent = FindColony(loc.parent_colony);
						sNatShortP = NationShortName(sti(Colonies[iParent].nation));
						sNatTypeP = GetNationNameByType(sti(Colonies[iParent].nation));
					}

					if (CheckAttribute(loc, "type"))
					{
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

										if (!KZ|Check(dir))
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

											if (!KZ|Check(dir))
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

											if (!KZ|Check(dir))
											{
												dir = "&Land\Jungle";

												if (Whr_IsDay())
													dir += ",Land\Jungle\Day";
												else
													dir += ",Land\Jungle\Night";
											}
										break;

										case "DesMoines":
											dir = "Special\DesMoines";

											if (!KZ|Check(dir))
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
									if (CheckAttribute(loc, "Maltains") && sti(loc.Maltains) == true)
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
									if (CheckAttribute(loc, "brothel") && sti(loc.brothel) == true)
									{
										tmp += "Brothel\";

										if (HasAttrValue(&InterfaceStates, "ContinuousMusic.Brothel", "1"))
										{
											dir = "&" + tmp + "Hall," + tmp + "Madam," + tmp + "Room," + tmp;

											if (!KZ|Check(dir))
												dir = tmp + "House";
										}
										else
										{
											dir = tmp + "Hall," + tmp + ",Colony\Inside\House";

											if (HasStr(loc.id, "SecBrRoom") && KZ|Check(tmp + "Madam"))
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
											if (HasStr(loc.id.label, "PackhouseOffice") || and(CheckAttribute(loc, "packhouse") && sti(loc.packhouse) == 1, true))
												dir = tmp + "Packhouse," + dir;
											else
											{
												if (CheckAttribute(loc, "HWIC") && sti(loc.HWIC) == true)
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

									if (!KZ|Check(dir))
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

								if (CheckAttribute(loc, "packhouse") && sti(loc.packhouse) == true)
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

									if (!KZ|Check(dir))
										dir = "&Land\Fort\" + sNatTypeP + ",Land\Fort";
								}
								else
								{
									if (!KZ|Check(dir))
										dir = "Land\Fort";
								}
							break;

							case "LostShipsCity":
								dir = "Special\LSC";

								if (CheckAttribute(&TEV, "FinalMusicLSC"))
								{
									tmp = "Special\LSC\Final";

									if (KZ|Check(tmp))
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

									if (KZ|Check(tmp))
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
					}
				}
			}
		}
	}

	if (KZ|Random(dir) != "")
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

	int n, q = 0;
	int len = strlen(str);
	string tmp;

	if (len > 0)
	{
		for (n = 0; n < len; n++)
		{
			tmp = GetSymbol(&str, n);

			if (tmp == sym)
				q++;
		}
	}

	return q;
}

void KZ|Folder()
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

// mitrokosta переработка контроля версий

#define COMMON_MIGRATION_FOLDER "migrations"
#define MOD_MIGRATION_FOLDER "mod_migrations"

extern void ApplyMigration(ref migrationState); // функция которую нужно переопределить в файле конкретной миграции

void ApplyMigrations() {
	PurgeLostMigrations(COMMON_MIGRATION_FOLDER);
	ApplyMigrationsForFolder(COMMON_MIGRATION_FOLDER, "");
	//CheckForUninstalledMods();
	//ApplyModResources();
}

// чистка журнала миграций (запись в стеке есть, а файла в папке нет)
int PurgeLostMigrations(string migrationDir)
{
	aref   migrations, migration;
	int    i = 0;
	int    q = 0;
	int    iDropped = 0;
	string sFolder = "";
	string sName = "";
	string sValue = "";
	string sNum = "";

	sFolder = "Program\" + migrationDir;

	if (!XI_CheckFileByMask(sFolder, "????_*.c", 0))
	{
		trace("PurgeLostMigrations: no migration files found in " + sFolder + ", migration log skipped");
		return 0;
	}

	if (!CheckAttribute(&TEV, "ClearLostMigrations")) return 0;
	DeleteAttribute(&TEV, "ClearLostMigrations");

	makearef(migrations, pchar.migrations);
	q = GetAttributesNum(migrations);

	for (i = q - 1; i >= 0; i--)
	{
		migration = GetAttributeN(migrations, i);
		sName  = GetAttributeName(migration);
		sValue = GetAttributeValue(migration);

		// ключ короче "idN" - не наша запись
		if (strlen(sName) < 3) continue;

		// мод-миграции лежат в своих папках, эта чистка их не касается
		if (IsMigrationFromMod(sName)) continue;

		// имя файла собирается обратно из записи
		sNum = strcut(sName, 2, strlen(sName) - 1);
		sNum = "" + sti(sNum);
		while (strlen(sNum) < 4) { sNum = "0" + sNum; }

		if (XI_CheckFileByMask(sFolder, sNum + "_" + sValue + ".c", 0)) continue;

		trace("PurgeLostMigrations: file " + sNum + "_" + sValue + ".c not found, record " + sName + " removed");
		DeleteAttribute(migrations, sName);
		iDropped++;
	}

	if (iDropped > 0)
		trace("PurgeLostMigrations: removed records of missing migrations - " + iDropped);

	return iDropped;
}

// проверяем, что не удалены моды, миграции из которых есть в сейве
void CheckForUninstalledMods() {
  trace("Checking for uninstalled mods...");

  aref migrations, migration;
  makearef(migrations, pchar.migrations);
  int migrationsLength = GetAttributesNum(migrations);
  object ObsoleteState; //сюда сохраним все ненайденные моды
  ref ObsoleteMods;
  string modName;
  makeref(ObsoleteMods, ObsoleteState);

  // идём по всем миграциям в сейве
  for (int i = 0; i < migrationsLength; i++) {
		migration = GetAttributeN(migrations, i);
    string migName = GetAttributeName(migration);
    string exactMigName = GetAttributeValue(migration);
    if (!IsMigrationFromMod(migName)) continue;               // это миграция не из мода, пропускаем
    if (IsReversableMigration(exactMigName)) continue;        // миграция обратима, пропускаем

    migName = strcut(migName, 3, strlen(migName) - 2);        // режем "_id"
    modName = GetModeNameByMigName(migName, 0);        // получаем название мода
    if (!IsModInstalled(modName)) ObsoleteMods.(modName) = 1; // записываем название
  }


  int modsNumber = GetAttributesNum(ObsoleteMods);
  trace("can't found mods number:" + modsNumber);

  string modsList;
  for (int j = 0; j < modsNumber; j++)
  {
    modName = GetAttributeName(GetAttributeN(ObsoleteMods, j));
    trace("can't found mod: " + modName);
    modsList = modsList + modName + " ";
  }

  // выводим предупреждение
  string messageText = GetConvertStr("Uninstalled_Mods_Founded", "migrations.txt") + "~" + modsList;
  //if(modsNumber > 0) LaunchMessage(messageText);
}

void ApplyModAliases(string modFolder, string processingFolder) 
{
	object fileFinderRes;
	aref fileResList;

	fileFinderRes.dir = processingFolder + modFolder;
	fileFinderRes.mask = "Greetings_alias.ini";
	CreateEntity(&fileFinderRes, "FINDFILESINTODIRECTORY");
	DeleteClass(&fileFinderRes);
	makearef(fileResList, fileFinderRes.filelist);
	if (GetAttributesNum(fileResList) > 0)
	{
		string loc = LanguageGetLanguage();
		string path = loc + "\mods\" + modFolder + "\Greetings_alias.ini";
		SendMessage( &Sound, "ls", MSG_SOUND_ALIAS_ADD,  path);
		trace("Applied alias file: "+path);
	}
	DeleteAttribute(&fileFinderRes, ""); 
}

void ApplyModStrings(string modFolder, string processingFolder) 
{
	object fileFinderRes;
	aref fileResList;

	fileFinderRes.dir = processingFolder + modFolder;
	fileFinderRes.mask = "common.ini";
	CreateEntity(&fileFinderRes, "FINDFILESINTODIRECTORY");
	DeleteClass(&fileFinderRes);
	makearef(fileResList, fileFinderRes.filelist);
	if (GetAttributesNum(fileResList) > 0)
	{
		string path = "mods\" + modFolder + "\common.ini";
		SendMessage(&GameInterface, "ls", MSG_INTERFACE_LOAD_STRINGS_INI_FILE, path);
		trace("Applied mod common.ini: "+path);
	}
	DeleteAttribute(&fileFinderRes, ""); 
}

void ApplyModPictures(string modFolder, string processingFolder) 
{
	object fileFinderRes;
	aref fileResList;

	fileFinderRes.dir = processingFolder + modFolder;
	fileFinderRes.mask = "pictures.ini";
	CreateEntity(&fileFinderRes, "FINDFILESINTODIRECTORY");
	DeleteClass(&fileFinderRes);
	makearef(fileResList, fileFinderRes.filelist);
	if (GetAttributesNum(fileResList) > 0)
	{
		string path = "mods\" + modFolder + "\pictures.ini";
		SendMessage(&GameInterface, "ls", MSG_INTERFACE_LOAD_PICTURES_INI_FILE, path);
		trace("Applied mod pictures.ini: "+path);
	}
	DeleteAttribute(&fileFinderRes, ""); 
}


void ApplyModMigrations(string modFolder, string processingFolder) 
{
	ApplyMigrationsForFolder(MOD_MIGRATION_FOLDER, modFolder);
}

void ApplyModResourcesForFolder(string folder, string processFunction) 
{
	trace("Applying mod resources for: "+processFunction);
	
	object fileFinder;
	fileFinder.dir = folder;
	fileFinder.mask = "*";
	fileFinder.onlydirs = "1";
	fileFinder.onlyfiles = "0";
	CreateEntity(&fileFinder, "FINDFILESINTODIRECTORY");
	DeleteClass(&fileFinder);
	
	aref fileList;
	makearef(fileList, fileFinder.filelist);
	int filesNum = GetAttributesNum(fileList);
	trace("Applying mod resources ("+folder+")... found:"+filesNum);
	object mods;
	
	for (int i = 0; i < filesNum; i++) {
		aref file = GetAttributeN(fileList, i);
		string fileName = GetAttributeValue(file);
		call processFunction(fileName, folder);
	}
}

void ApplyModResources()
{
	string loc = LanguageGetLanguage();
	
	string modGrAliasPath = "Resource\INI\aliases\" + loc + "\mods\";
	string modStringCommonPath = "Resource\INI\texts\" + loc + "\mods\";
	string modPicturesPath = "Resource\INI\interfaces\mods\";
	string modMigrationsPath = "Program\"+MOD_MIGRATION_FOLDER+"\";

	ApplyModResourcesForFolder(modGrAliasPath, "ApplyModAliases");
	ApplyModResourcesForFolder(modStringCommonPath, "ApplyModStrings");
	ApplyModResourcesForFolder(modPicturesPath, "ApplyModPictures");
	ApplyModResourcesForFolder(modMigrationsPath, "ApplyModMigrations");
}


void ApplyMigrationsForFolder(string migrationDir, string modName) {
	trace("Applying migrations ("+migrationDir + "/" + modName+")...");
	// построение списка миграций
	int i, migrationsNum = 0;

    object fileFinder;
	if (modName != "")
	{
		migrationDir = migrationDir + "\" + modName;
	}
	fileFinder.dir = "Program\"+migrationDir;
	fileFinder.mask = "????_*.c";
	CreateEntity(&fileFinder, "FINDFILESINTODIRECTORY");
	DeleteClass(&fileFinder);
	
	aref fileList;
	makearef(fileList, fileFinder.filelist);
	int filesNum = GetAttributesNum(fileList);
	trace("ApplyMigrationsForFolder filesNum: " +filesNum);
	if (filesNum < 1) return;

	aref file;
	string fileName;
	string numString;
	int migrationIndex;

	// размер списка по наибольшему номеру, а не по числу файлов
	int maxIndex = 0;
	for (i = 0; i < filesNum; i++)
	{
		file = GetAttributeN(fileList, i);
		fileName = GetAttributeValue(file);
		numString = strcut(&fileName, 0, 3);
		migrationIndex = sti(numString);
		if (migrationIndex > maxIndex) maxIndex = migrationIndex;
	}
	if (maxIndex < 1)
	{
		trace("ApplyMigrationsForFolder: no valid migration numbers found");
		return;
	}

    string migrationsList[2];
    SetArraySize(&migrationsList, maxIndex);

	for (i = 0; i < filesNum; i++) {
		file = GetAttributeN(fileList, i);
		fileName = GetAttributeValue(file);
		//fileName = strcut(&fileName, 0, strlen(&fileName) - 3) + ".c";
		trace("ApplyMigrationsForFolder fileName: " + fileName);

		numString = strcut(&fileName, 0, 3);
		migrationIndex = sti(numString);
		
		// индексы пусть с 1 начинаются, т.к. 0 - признак облома
		if (migrationIndex < 1)
		{
			trace("Found invalid migration file " + fileName);
			continue;
		}

		// номер уже занят другим файлом - иначе один из двух пропал бы молча
		if (migrationsList[migrationIndex - 1] != "")
		{
			trace("Duplicate migration number in " + fileName + ", slot taken by " + migrationsList[migrationIndex - 1]);
		}

		migrationsList[migrationIndex - 1] = migrationDir + "\" + fileName;
	}
	
	// последовательное применение миграций с сохранением загруженных сегментов
	object migrationState;
	aref migrations;
	makearef(migrations, pchar.migrations);
	for (i = 0; i < maxIndex; i++)
	{
		fileName = migrationsList[i];
		if (fileName == "") continue;
		
		string migrationName = strcut(&fileName, strlen(migrationDir) + 6, strlen(fileName) - 3);
		
		// миграция уже применена
		string migrationId = "id" + (i + 1);
		if (modName != "") 
		{
			migrationId = "id_" + modName + (i + 1);
		}
		if (CheckAttribute(migrations, migrationId) && migrations.(migrationId) == migrationName)
		{
			trace("Migration " + migrationName + " already applied");
			continue;
		}
		
		if (!LoadSegment(fileName))
		{
			trace("Error! Can't load migration file " + fileName);
			continue;
		}
		
		trace("ApplyMigrationsForFolder Applying " + fileName + "...");
		
		ApplyMigration(&migrationState);
		migrations.(migrationId) = migrationName;
		UnloadSegment(fileName);
		
		trace("ApplyMigrationsForFolder Success...");
	}
	
	Migration_UnloadSegments(&migrationState);
}

// действуем в предположении того, что все имеющиеся миграции есть в инитах, как и должно быть по-хорошему

void InitMigrations()
{
	InitMigrationsForFolder(COMMON_MIGRATION_FOLDER);
	// Моды - всегда в миграциях, моды не меняют иниты
	//ApplyModResources();
}

void InitMigrationsForFolder(string migrationDir) {
	trace("Initializing migrations...");
	
	object fileFinder;
	fileFinder.dir = "Program\"+migrationDir;
	fileFinder.mask = "????_*.c";
	CreateEntity(&fileFinder, "FINDFILESINTODIRECTORY");
	DeleteClass(&fileFinder);
	
	aref fileList;
	makearef(fileList, fileFinder.filelist);
	int filesNum = GetAttributesNum(fileList);
	trace("InitMigrationsForFolder filesNum: " +filesNum);
	if (filesNum < 1) return;

	aref migrations;
	makearef(migrations, pchar.migrations);
	for (int i = 0; i < filesNum; i++) {
		aref file = GetAttributeN(fileList, i);
		string fileName = GetAttributeValue(file);
		//fileName = strcut(&fileName, 0, strlen(&fileName) - 3) + ".c";
		trace("InitMigrationsForFolder fileName: " + fileName);
		
		string numString = strcut(&fileName, 0, 3);
		int migrationIndex = sti(numString);
		
		// индексы пусть с 1 начинаются, т.к. 0 - признак облома
		if (migrationIndex < 1) {
			trace("Found invalid migration file " + fileName);
			continue;
		}
		
		string migrationId = "id" + migrationIndex;
		string migrationName = strcut(&fileName, 5, strlen(fileName) - 3);
		migrations.(migrationId) = migrationName;
		
		trace("Marked migration " + fileName + " as complete...");
	}
}

bool Migration_LoadSegment(ref migrationState, string fileName) {
	aref segments;
	makearef(segments, migrationState.segments);
	
	int segmentsCount = GetAttributesNum(segments);
	for (int i = 0; i < segmentsCount; i++) {
		// сегмент уже загружен
		if (fileName == GetAttributeValue(GetAttributeN(segments, i))) {
			return true;
		}
	}
	
	if (!LoadSegment(fileName)) {
		return false;
	}
	
	string attr = "id" + (segmentsCount + 1);
	segments.(attr) = fileName;
	trace("Loaded segment " + fileName);
	return true;
}

void Migration_UnloadSegments(ref migrationState) {
	aref segments;
	makearef(segments, migrationState.segments);
	
	int segmentsCount = GetAttributesNum(segments);
	for (int i = 0; i < segmentsCount; i++) {
		string fileName = GetAttributeValue(GetAttributeN(segments, i));
		UnloadSegment(fileName);
		trace("Unloaded segment " + fileName);
	}
}

// получаем название мода из миграции
string GetModeNameByMigName(string currentMigName, int iteration){
  // если на конце уже не цифра, значит это и есть папка мода
  string lastChar = strcut(currentMigName, strlen(currentMigName) - 1, strlen(currentMigName) - 1);
  if (lastChar != "0" && sti(lastChar) == 0) return currentMigName;
  
  // режем последний символ
  string tempName1 = strcut(currentMigName, 0, strlen(currentMigName) - 2);

  // ррррекурррррсивное прогррррамиррррование
  return GetModeNameByMigName(tempName1, iteration + 1); // следующая итерация
}

// есть ли папка с модом?
bool IsModInstalled(string folderName)
{
	string searchPath = "Program\"+MOD_MIGRATION_FOLDER;
	object fileFinder;
	fileFinder.dir = searchPath;
	fileFinder.mask = "*";
	fileFinder.onlydirs = "1";
	fileFinder.onlyfiles = "0";
	CreateEntity(&fileFinder, "FINDFILESINTODIRECTORY");
	DeleteClass(&fileFinder);
	
	aref fileList;
	makearef(fileList, fileFinder.filelist);
	int filesNum = GetAttributesNum(fileList);
	
  bool foundedMod = false;
	for (int i = 0; i < filesNum; i++) {
		aref file = GetAttributeN(fileList, i);
		string fileName = GetAttributeValue(file);
		if (fileName == folderName) foundedMod = true;
	}
  return foundedMod;
}

// Миграция добавлена модом
bool IsMigrationFromMod(string migrationName)
{
  return strcut(migrationName, 2, 2) == "_";
}

// В названии миграции есть ключевое слово revers, она не должна добавлять новые предметы, корабли и проч.
// Например, она выдаёт кому-то уже существующий в оригинальной игре предмет или меняет характеристики персонажей.
// Таким образом удаление мода с этой миграцией ничего не ломает.
bool IsReversableMigration(string exactMigName)
{
  if (strlen(exactMigName) < 7) return false;

  return strcut(exactMigName, 0, 6) == "revers_";
}

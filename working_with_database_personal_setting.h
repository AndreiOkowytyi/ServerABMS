#pragma once

#ifndef WORKING_WITH_DATABASE_SETTING
#define WORKING_WITH_DATABASE_SETTING

#include <string>

/*
Работа с СУБД - информация о личных настройках персонала.
*/

class PersonalSettingDatabaseWrite {
 public:
	virtual std::string workingDatabase() = 0;
	virtual ~PersonalSettingDatabaseWrite() {}
};

class PersonalSettingDatabaseRecord {
 public:
	virtual std::string workingDatabase() = 0;
	virtual ~PersonalSettingDatabaseRecord() {}
};

#endif // WORKING_WITH_DATABASE_SETTING
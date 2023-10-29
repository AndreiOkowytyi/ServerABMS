#pragma once

#ifndef WORKING_WITH_DATABASE_SETTING
#define WORKING_WITH_DATABASE_SETTING

#include <string>

class  PersonalSettingDatabaseWrite {
	virtual void workingDatabase(std::string& request) = 0;
	virtual ~PersonalSettingDatabaseWrite() {}
};

class  PersonalSettingDatabaseRecord {
	virtual void workingDatabase(std::string& request) = 0;
	virtual ~PersonalSettingDatabaseRecord() {}
};

#endif // WORKING_WITH_DATABASE_SETTING
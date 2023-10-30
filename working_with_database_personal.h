#pragma once

#ifndef WORKING_WITH_DATABASE_PERSONAL
#define WORKING_WITH_DATABASE_PERSONAL

#include <string>

class PersonalDatabaseWrite {
 public:
	virtual void workingDatabase(std::string& request) = 0;
	virtual ~PersonalDatabaseWrite() {}
};

class  PersonalDatabaseRecord {
 public:
	virtual void workingDatabase(std::string& request) = 0;
	virtual ~PersonalDatabaseRecord() {}
};

#endif // WORKING_WITH_DATABASE_PERSONAL
#pragma once

#ifndef WORKING_WITH_DATABASE_PERSONAL
#define WORKING_WITH_DATABASE_PERSONAL

#include <string>

/*
Работа с СУБД - информация о персонале.
*/

class PersonalDatabaseWrite {
 public:
	virtual std::string workingDatabase() = 0;
	virtual ~PersonalDatabaseWrite() {}
};

class  PersonalDatabaseRecord {
 public:
	virtual std::string workingDatabase() = 0;
	virtual ~PersonalDatabaseRecord() {}
};

#endif // WORKING_WITH_DATABASE_PERSONAL
#pragma once

#ifndef WORKING_WITH_DATABASE_CLIENT_INFORMATION
#define WORKING_WITH_DATABASE_CLIENT_INFORMATION

#include <string>

/*
Работа с СУБД - информация о клиенте.
*/

class ClientInormationDatabaseWrite {
 public:
	virtual std::string workingDatabase() = 0;
	virtual ~ClientInormationDatabaseWrite() {}
};

class ClientInformationDatabaseRecord {
 public:
	virtual std::string workingDatabase() = 0;
	virtual ~ClientInformationDatabaseRecord() {}
};

#endif // WORKING_WITH_DATABASE_CLIENT_INFORMATION

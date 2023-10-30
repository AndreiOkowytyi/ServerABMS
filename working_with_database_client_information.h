#pragma once

#ifndef WORKING_WITH_DATABASE_CLIENT_INFORMATION
#define WORKING_WITH_DATABASE_CLIENT_INFORMATION

#include <string>

class ClientInormationDatabaseWrite {
 public:
	virtual void workingDatabase(std::string& request) = 0;
	virtual ~ClientInormationDatabaseWrite() {}
};

class ClientInformationDatabaseRecord {
 public:
	virtual void workingDatabase(std::string& request) = 0;
	virtual ~ClientInformationDatabaseRecord() {}
};

#endif // WORKING_WITH_DATABASE_CLIENT_INFORMATION

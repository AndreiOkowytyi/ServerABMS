#pragma once

#ifndef WORKING_WITH_DATABASE_PRODUCT
#define WORKING_WITH_DATABASE_PRODUCT

#include <string>

class ProductionDatabaseWrite {
 public:
	virtual void workingDatabase(std::string& request) = 0;
	virtual ~ProductionDatabaseWrite() {}
};

class ProductionDatabaseRecord {
 public:
	virtual void workingDatabase(std::string& request) = 0;
	virtual ~ProductionDatabaseRecord() {}
};

#endif // WORKING_WITH_DATABASE_PRODUCT
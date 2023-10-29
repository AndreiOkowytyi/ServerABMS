#pragma once

#ifndef WORKING_WITH_DATABASE
#define WORKING_WITH_DATABASE

#include <string>

class StockDatabaseWrite {
public:
	virtual void workingDatabase(std::string& request) = 0;
	virtual ~StockDatabaseWrite() {}
};

class StockDatabaseRecord {
public:
	virtual void workingDatabase(std::string& request) = 0;
	virtual ~StockDatabaseRecord() {}
};

#endif //WORKING_WITH_DATABASE
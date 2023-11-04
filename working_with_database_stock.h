#pragma once

#ifndef WORKING_WITH_DATABASE
#define WORKING_WITH_DATABASE

#include <string>

/*
Работа с СУБД -  склад.
*/

class StockDatabaseWrite {
 public:
	virtual std::string workingDatabase() = 0;
	virtual ~StockDatabaseWrite() {}
};

class StockDatabaseRecord {
 public:
	virtual std::string workingDatabase() = 0;
	virtual ~StockDatabaseRecord() {}
};

#endif //WORKING_WITH_DATABASE
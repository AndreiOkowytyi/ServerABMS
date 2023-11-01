#pragma once

#ifndef REQUEST_CONTROL_BLOCK
#define REQUEST_CONTROL_BLOCK

#include <vector>
#include <memory>

#include "working_with_database_stock.h"
#include "working_with_database_product.h"
#include "working_with_database_personal.h"
#include "working_with_database_personal_setting.h"
#include "working_with_database_client_information.h"

// Вопрос о возвращении значения.

///////////////////////////////////////

class RequestDatabase {
 public:
	virtual std::string getRequest(const short index) = 0;
	virtual ~RequestDatabase() {}
};

class RequestStock : public RequestDatabase {
 public:
	RequestStock();
	std::string getRequest(const short index) override;
 
 private:
	 std::vector<std::unique_ptr<StockDatabaseRecord>>m_v_RequestStock;
};

class RequestProduction : public RequestDatabase {
 public:
	RequestProduction();
	std::string getRequest(const short index) override;

 private:
	std::vector<std::unique_ptr<ProductionDatabaseRecord>>m_v_RequestProduction;
};

class RequestPersonal : public RequestDatabase {
 public:
	RequestPersonal();
	std::string getRequest(const short index) override;

 private:
	std::vector<std::unique_ptr<PersonalDatabaseRecord>>m_v_RequestPersonal;
};

class RequestPersonalSetting : public RequestDatabase {
 public:
	RequestPersonalSetting();
	std::string getRequest(const short index) override;

 private:
	std::vector<std::unique_ptr<PersonalSettingDatabaseRecord>>m_v_RequestPersonalSetting;
};

class RequestClientInformation : public RequestDatabase {
 public:
	RequestClientInformation();
	std::string getRequest(const short index) override;

 private:
	std::vector<std::unique_ptr<ClientInformationDatabaseRecord>>m_v_RequestClientInformation;
};

//////////////////////////////////////////////////

class WriteDatabase {
 public:
	virtual std::string writeDatabase(const short index) = 0;
	virtual ~WriteDatabase() {}
};

class WriteStock : public WriteDatabase {
 public:
	WriteStock();
	std::string writeDatabase(const short index) override;

 private:
	std::vector<std::unique_ptr<StockDatabaseWrite>>m_v_WriteStock;
};

class WriteProduction : public WriteDatabase {
 public:
	WriteProduction();
	std::string writeDatabase(const short index) override;

 private:
	std::vector<std::unique_ptr<ProductionDatabaseWrite>>m_v_WriteProduction;
};

class WritePersonal : public WriteDatabase {
 public:
	WritePersonal();
	std::string writeDatabase(const short index) override;

 private:
	std::vector<std::unique_ptr<PersonalDatabaseWrite>>m_v_WritePersonal;
};

class WritePersonalSetting : public WriteDatabase {
 public:
	WritePersonalSetting();
	std::string writeDatabase(const short index) override;

 private:
	std::vector<std::unique_ptr<PersonalSettingDatabaseWrite>>m_v_WritePersonalSetting;
};

class WriteClientInformation : public WriteDatabase {
 public:
	WriteClientInformation();
	std::string writeDatabase(const short index) override;

 private:
	std::vector<std::unique_ptr<ClientInormationDatabaseWrite>>m_v_WriteClientInformation;
};

//////////////////////////////////////////////////////////////////////

class BlockRequestDatabase {
 public:
	 BlockRequestDatabase();
	 std::string requestDatabase(const short index_group, const short index_request);

 private:
	 std::vector<std::unique_ptr<RequestDatabase>>m_v_BlockRequestDatabase;
};


class BlockWriteDatabase {
 public:
	 BlockWriteDatabase();
	 std::string writeDatabase(const short index_group, const short index_request);

 private:
	 std::vector<std::unique_ptr<WriteDatabase>>m_v_BlockWriteDatabase;
};


class RequestControlBlockDatabase {
 public:
	 std::string requestDatabase(const short index_group, const short index_request);
	 std::string writeDatabase(const short index_group, const short index_request);

 private:
	 BlockRequestDatabase m_RequestDatabase;
	 BlockWriteDatabase m_WriteDatabase;
};

#endif // REQUEST_CONTROL_BLOCK
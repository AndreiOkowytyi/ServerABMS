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


class RequestDatabase {
 public:
	virtual void getRequest(std::string &request) = 0;
	virtual ~RequestDatabase() {}
};

class RequestStock : public RequestDatabase {
 public:
	RequestStock();
	void getRequest(std::string& request) override;
 
 private:
	 std::vector<std::unique_ptr<StockDatabaseRecord>>m_v_RequestStock;
};

class RequestProduction : public RequestDatabase {
 public:
	RequestProduction();
	void getRequest(std::string& request) override;

 private:
	std::vector<std::unique_ptr<ProductionDatabaseRecord>>m_v_RequestProduction;
};

class RequestPersonal : public RequestDatabase {
 public:
	RequestPersonal();
	void getRequest(std::string& request) override;

 private:
	std::vector<std::unique_ptr<PersonalDatabaseRecord>>m_v_RequestPersonal;
};

class RequestPersonalSetting : public RequestDatabase {
 public:
	RequestPersonalSetting();
	void getRequest(std::string& request) override;

 private:
	std::vector<std::unique_ptr<PersonalSettingDatabaseRecord>>m_v_RequestPersonalSetting;
};

class RequestClientInformation : public RequestDatabase {
 public:
	RequestClientInformation();
	void getRequest(std::string& request) override;

 private:
	std::vector<std::unique_ptr<ClientInformationDatabaseRecord>>m_v_RequestClientInformation;
};


class WriteDatabase {
 public:
	virtual void writeDatabase(std::string& request) = 0;
	virtual ~WriteDatabase() {}
};

class WriteStock : public WriteDatabase {
 public:
	WriteStock();
	void writeDatabase(std::string& request) override;

 private:
	std::vector<std::unique_ptr<StockDatabaseWrite>>m_v_WriteStock;
};

class WriteProduction : public WriteDatabase {
 public:
	WriteProduction();
	void writeDatabase(std::string& request) override;

 private:
	std::vector<std::unique_ptr<ProductionDatabaseWrite>>m_v_WriteProduction;
};

class WritePersonal : public WriteDatabase {
 public:
	WritePersonal();
	void writeDatabase(std::string& request) override;

 private:
	std::vector<std::unique_ptr<PersonalDatabaseWrite>>m_v_WritePersonal;
};

class WritePersonalSetting : public WriteDatabase {
 public:
	WritePersonalSetting();
	void writeDatabase(std::string& request) override;

 private:
	std::vector<std::unique_ptr<PersonalSettingDatabaseWrite>>m_v_WritePersonalSetting;
};

class WriteClientInformation : public WriteDatabase {
 public:
	WriteClientInformation();
	void writeDatabase(std::string& request) override;

 private:
	std::vector<std::unique_ptr<ClientInormationDatabaseWrite>>m_v_WriteClientInformation;
};


class BlockRequestDatabase {
 public:
	 BlockRequestDatabase();
	 void requestDatabase(std::string& request);

 private:
	 std::vector<std::unique_ptr<RequestDatabase>>m_v_BlockRequestDatabase;
};


class BlockWriteDatabase {
 public:
	 BlockWriteDatabase();
	 void writeDatabase(std::string& request);

 private:
	 std::vector<std::unique_ptr<WriteDatabase>>m_v_BlockWriteDatabase;
};


class RequestControlBlockDatabase {
 public:
	 void requestDatabase(std::string& request);
	 void writeDatabase(std::string& request);

 private:
	 BlockRequestDatabase m_RequestDatabase;
	 BlockWriteDatabase m_WriteDatabase;
};

#endif // REQUEST_CONTROL_BLOCK
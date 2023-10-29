#pragma once

#ifndef REQUEST_CONTROL_BLOCK
#define REQUEST_CONTROL_BLOCK

#include <vector>

#include "working_with_database_stock.h"
#include "working_with_database_product.h"
#include "working_with_database_personal.h"
#include "working_with_database_personal_setting.h"
#include "working_with_database_client_information.h"

class RequestDatabase {
public:
	virtual void getRequest() = 0;
	virtual ~RequestDatabase() {}
};

class RequestStock : public RequestDatabase {
public:
	void getRequest() override;
};

class RequestProduction : public RequestDatabase {
public:
	void getRequest() override;
};

class RequestPersonal : public RequestDatabase {
public:
	void getRequest() override;
};

class RequestPersonalSetting : public RequestDatabase {
public:
	void getRequest() override;
};

class RequestClientInformation : public RequestDatabase {
public:
	void getRequest() override;
};


class WriteDatabase {
public:
	virtual void writeDatabase() = 0;
	virtual ~WriteDatabase() {}
};

class WriteStock : public WriteDatabase {
public:
	void writeDatabase() override;
};

class WriteProduction : public WriteDatabase {
public:
	void writeDatabase() override;
};

class WritePersonal : public WriteDatabase {
public:
	void writeDatabase() override;
};

class WritePersonalSetting : public WriteDatabase {
public:
	void writeDatabase() override;
};

class WriteClientInformation : public WriteDatabase {
public:
	void writeDatabase() override;
};


class BlockRequestDatabase {
 public:

 private:

};

class BlockWriteDatabase {
 public:

 private:

};

class RequestControlBlockDatabase {
 public:

 private:

};

#endif // REQUEST_CONTROL_BLOCK
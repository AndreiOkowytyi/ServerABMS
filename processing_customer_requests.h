#pragma once

#ifndef PROCESSING_CUSTOMER_REQUESTS
#define PROCESSING_CUSTOMER_REQUESTS

#include "request_control_block.h"


class Verification {
 public:
	 virtual void procedure(std::string& request) = 0;
	 virtual ~Verification() = 0;
};

class Entrance : public Verification { // Вход в систему.
 public:
	 void procedure(std::string& request) override;
};

class NewRegistration : public Verification { // Новый пользователь.
 public:
	void procedure(std::string& request) override;
};


//////////////////////////////////////////////////////


class ComplexQueries {
 public:
	 virtual ~ComplexQueries();
	 virtual void procedure(std::string& request) = 0;
};


/////////////////////////////////////////////////////


class Processing {
public:
	virtual ~Processing();
	virtual void work(std::string& request) = 0;
};

class ProcessingVerification : public Processing {
 public:
	ProcessingVerification();
	void work(std::string& request) override;

 private:
	std::vector<std::unique_ptr<Verification>>m_v_Processing;
};

class SimpleQueries :  public Processing {
 public:
	 void work(std::string& request) override;
};

class ProcessingComplexQueries : public Processing {
public:
	ProcessingComplexQueries();
	void work(std::string& request) override;

private:
	std::vector<std::unique_ptr<ComplexQueries>>m_v_ComplexQueries;
};


////////////////////////////////////////////////////


class ProcessingCustomerRequests {
public:
	void startProcessing(std::string& request);

private:
	std::vector<std::unique_ptr<Processing>>m_v_Processing;
	RequestControlBlockDatabase m_ReauestControlBlock;
};

#endif // PROCESSING_CUSTOMER_REQUESTS
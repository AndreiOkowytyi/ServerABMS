#include <processing_customer_requests.h>


void Entrance::procedure(std::string& request) {


}

void NewRegistration::procedure(std::string& request) {


}


/*BLOCK*/


ProcessingVerification::ProcessingVerification() {

	m_v_Processing.emplace_back(std::make_unique<Entrance>());
	m_v_Processing.emplace_back(std::make_unique<NewRegistration>());
}

void ProcessingVerification::work(std::string& request) {


}


void SimpleQueries::work(std::string& request) {


}


ProcessingComplexQueries::ProcessingComplexQueries() {


}

void ProcessingComplexQueries::work(std::string& request) {


}


/*BLOCK*/


void ProcessingCustomerRequests::startProcessing(std::string& request) {


}
#include "request_control_block.h"


RequestStock::RequestStock() {


}

std::string RequestStock::getRequest(const short index) {

	return "";
}


RequestProduction::RequestProduction() {


}

std::string RequestProduction::getRequest(const short index) {

	return "";
}


RequestPersonal::RequestPersonal() {


}

std::string RequestPersonal::getRequest(const short index) {

	return "";
}


RequestPersonalSetting::RequestPersonalSetting() {

}

std::string RequestPersonalSetting::getRequest(const short index) {

	return "";
}


RequestClientInformation::RequestClientInformation() {


}

std::string RequestClientInformation::getRequest(const short index) {

	return "";
}


/*BLOCK*/

WriteStock::WriteStock() {


}

std::string WriteStock::writeDatabase(const short index) {

	return "";
}


WriteProduction::WriteProduction() {


}

std::string WriteProduction::writeDatabase(const short index) {

	return "";
}


WritePersonal::WritePersonal() {


}

std::string WritePersonal::writeDatabase(const short index) {

	return "";
}


WritePersonalSetting::WritePersonalSetting() {


}

std::string WritePersonalSetting::writeDatabase(const short index) {

	return "";
}


WriteClientInformation::WriteClientInformation() {


}

std::string WriteClientInformation::writeDatabase(const short index) {

	return "";
}


/*BLOCK*/

BlockRequestDatabase::BlockRequestDatabase() {

	this->m_v_BlockRequestDatabase.emplace_back(std::make_unique<RequestStock>());
	this->m_v_BlockRequestDatabase.emplace_back(std::make_unique<RequestProduction>());
	this->m_v_BlockRequestDatabase.emplace_back(std::make_unique<RequestPersonal>());
	this->m_v_BlockRequestDatabase.emplace_back(std::make_unique<RequestPersonalSetting>());
	this->m_v_BlockRequestDatabase.emplace_back(std::make_unique<RequestClientInformation>());
}

std::string BlockRequestDatabase::requestDatabase(const short index_group, const short index_request) {

	return "";
}


BlockWriteDatabase::BlockWriteDatabase() {

	this->m_v_BlockWriteDatabase.emplace_back(std::make_unique<WriteStock>());
	this->m_v_BlockWriteDatabase.emplace_back(std::make_unique<WriteProduction>());
	this->m_v_BlockWriteDatabase.emplace_back(std::make_unique<WritePersonal>());
	this->m_v_BlockWriteDatabase.emplace_back(std::make_unique<WritePersonalSetting>());
	this->m_v_BlockWriteDatabase.emplace_back(std::make_unique<WriteClientInformation>());
}

std::string BlockWriteDatabase::writeDatabase(const short index_group, const short index_request) {

	return "";
}


/*BLOCK*/

std::string RequestControlBlockDatabase::requestDatabase(const short index_group, const short index_request) {

	return "";
}

std::string RequestControlBlockDatabase::writeDatabase(const short index_group, const short index_request) {

	return "";
}

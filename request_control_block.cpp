#include "request_control_block.h"

RequestStock::RequestStock() {


}

void RequestStock::getRequest(std::string& request) {


}


RequestProduction::RequestProduction() {


}

void RequestProduction::getRequest(std::string& request) {


}


RequestPersonal::RequestPersonal() {


}

void RequestPersonal::getRequest(std::string& request) {


}


RequestPersonalSetting::RequestPersonalSetting() {


}

void RequestPersonalSetting::getRequest(std::string& request) {


}


RequestClientInformation::RequestClientInformation() {


}

void RequestClientInformation::getRequest(std::string& request) {


}


WriteStock::WriteStock() {


}

void WriteStock::writeDatabase(std::string& request) {


}


WriteProduction::WriteProduction() {


}

void WriteProduction::writeDatabase(std::string& request) {


}


WritePersonal::WritePersonal() {


}

void WritePersonal::writeDatabase(std::string& request) {


}


WritePersonalSetting::WritePersonalSetting() {


}

void WritePersonalSetting::writeDatabase(std::string& request) {


}


WriteClientInformation::WriteClientInformation() {


}

void WriteClientInformation::writeDatabase(std::string& request) {


}


BlockRequestDatabase::BlockRequestDatabase() {

	this->m_v_BlockRequestDatabase.emplace_back(std::make_unique<RequestStock>());
	this->m_v_BlockRequestDatabase.emplace_back(std::make_unique<RequestProduction>());
	this->m_v_BlockRequestDatabase.emplace_back(std::make_unique<RequestPersonal>());
	this->m_v_BlockRequestDatabase.emplace_back(std::make_unique<RequestPersonalSetting>());
	this->m_v_BlockRequestDatabase.emplace_back(std::make_unique<RequestClientInformation>());
}

void BlockRequestDatabase::requestDatabase(std::string& request) {


}


BlockWriteDatabase::BlockWriteDatabase() {

	this->m_v_BlockWriteDatabase.emplace_back(std::make_unique<WriteStock>());
	this->m_v_BlockWriteDatabase.emplace_back(std::make_unique<WriteProduction>());
	this->m_v_BlockWriteDatabase.emplace_back(std::make_unique<WritePersonal>());
	this->m_v_BlockWriteDatabase.emplace_back(std::make_unique<WritePersonalSetting>());
	this->m_v_BlockWriteDatabase.emplace_back(std::make_unique<WriteClientInformation>());
}

void BlockWriteDatabase::writeDatabase(std::string& request) {


}


void RequestControlBlockDatabase::requestDatabase(std::string& request) {


}

void RequestControlBlockDatabase::writeDatabase(std::string& request) {


}

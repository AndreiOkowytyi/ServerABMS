#include "working_with_data.h"

ClientData::ClientData(qintptr key, QTcpSocket* MapSocket, int id) {

    this->m_key = key;
    this->p_Socket = MapSocket;

    QObject::connect(p_Socket, &QTcpSocket::destroyed, this, [this]() {

        emit delete_();
        });
}

unsigned int ClientData::getKey() {

    return this->m_key;
}

QTcpSocket* ClientData::getSocket() {

    return this->p_Socket;
}

int ClientData::getId() {

    return this->m_id;
}

ClientData* ClientData::getThis() { return this; }


void Data::emplace(const int id, ClientData* data) {

	std::unique_lock<std::mutex> temp_lock(this->m_mut);
	this->m_map.emplace(std::pair<int, ClientData*>(id, data));
	temp_lock.unlock();
	m_cv.notify_all();
}

void Data::erase(const int key) {

	std::unique_lock<std::mutex> temp_lock(this->m_mut);
	this->m_map.erase(key);
	temp_lock.unlock();
	m_cv.notify_all();
}

ClientData* Data::operator[] (const int id) {

	std::unique_lock<std::mutex> temp_lock(this->m_mut);
	auto it_map = this->m_map.find(id);
	if (it_map != this->m_map.end()) return it_map->second;
	else return nullptr;
}

bool Data::empty() {

	std::unique_lock<std::mutex> temp_lock(this->m_mut);
	return this->m_map.empty();
}
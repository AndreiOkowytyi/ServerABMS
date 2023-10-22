#pragma once

#ifndef WORKINGWITHDATA
#define WORKINGWITHDATA

#include <QObject>
#include <qtcpsocket.h>
#include <mutex>
#include <condition_variable>

class ClientData : public QObject {
	Q_OBJECT
public:
	ClientData(qintptr key, QTcpSocket* Socket, int id = 0);

	unsigned int getKey();
	QTcpSocket* getSocket();
	int getId();
	ClientData* getThis();

private:
	qintptr m_key = 0;
	QTcpSocket* p_Socket = nullptr;
	int m_id = 0;

signals:
	void delete_();
};


class Data {
public:
	void emplace(const int id, ClientData* data);
	void erase(const int key);
	ClientData* operator[] (const int id);
	bool empty();

private:
	std::map<int, ClientData*>m_map;
	std::mutex                m_mut;
	std::condition_variable   m_cv;
};


#endif //WORKINGWITHDATA

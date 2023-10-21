#pragma once

#ifndef WORKING_THREAD
#define WORKING_THREAD

#define TEST // Вывод дополнительной информации.

#include <qtcpsocket.h>
#include <map>
#include <qbytearray.h>
#include <QObject>
#include <QThread>
#include <QTimer>
#include <qdatastream.h>

#include "queue_for_working_with_threads.h"
#include "secondary_task_control_unit.h"

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

class WorkingThread {
 public:
	 void setWorkibg() {}

 protected:
	 // Указатель на данные, и работа с ними.
};

class FlowOfIncomingRequestsThread : public QObject { // Класс отвечающий за прием новых клиентов, и подготовку запросов.
	Q_OBJECT
 public:
	 FlowOfIncomingRequestsThread(Queue<QByteArray> &QueueRequest,
		 Queue<qintptr>*descriptor, Data<ClientData> &data);
	 ~FlowOfIncomingRequestsThread();

     void newConnection(qintptr descriptor);
	 int countClient();
	 Queue<qintptr>* getQueue();

 private:
     Queue<qintptr>    *p_Queue        = nullptr; // Очередь запросов на добавления подключения.
	 Queue<QByteArray> *p_QueueRequest = nullptr; // Очередь для добавления готовых запросов для последующих потоков.
	 QTcpSocket        *p_socket       = nullptr; // Указатель для работы с сокетом.
	 Data<ClientData>  *p_Data         = nullptr;

	 std::map<qintptr, std::unique_ptr<ClientData>>m_Data;

	 QByteArray m_data;
	 quint16 m_buffer = 0;

     bool m_v = true;
	 bool m_a = true;
	 int m_count_client = 0; // Количество активных соед. 

	 QTimer* p_timer = nullptr;

 public slots:
	 void slotReadyRead();
	 void discSocket();
     void run();
	 void workClientData();
};


class RequestProcessingThread : public WorkingThread { // Обработка запросов
 public:
	 RequestProcessingThread(Queue<QByteArray> &QueueRequest, Queue<QByteArray> &QueueResult);
	 void run();

 private:
	 Queue<QByteArray> *p_QueueRequest = nullptr;
	 Queue<QByteArray> *p_QueueResult  = nullptr;
};


class MessageThread : public WorkingThread { // Отправка готовых звпросов
 public:
	 MessageThread(Queue<QByteArray> &QueueResult, Data<ClientData> &data);
	 void run();

 private:
	Queue<QByteArray> *p_QueueResult = nullptr;
	QTcpSocket *p_socket             = nullptr;
	Data<ClientData> *p_Data         = nullptr;
};
#endif //WORKING_THREAD
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

class WorkingThread {
 public:
	 void setWorkibg() {}

 protected:
	 // Указатель на данные, и работа с ними.
};

class FlowOfIncomingRequestsThread : public QObject { // Класс отвечающий за прием новых клиентов, и подготовку запросов.
	Q_OBJECT
 public:
	 FlowOfIncomingRequestsThread(Queue<QByteArray> &QueueRequest, std::map<qintptr, std::unique_ptr<QTcpSocket>> &MapSocket,
		 Queue<qintptr>*descriptor);
	 ~FlowOfIncomingRequestsThread();

     void newConnection(qintptr descriptor);
	 int countClient();
	 Queue<qintptr>* getQueue();

 private:
     Queue<qintptr>    *p_Queue        = nullptr; // Очередь запросов на добавления подключения.
	 Queue<QByteArray> *p_QueueRequest = nullptr; // Очередь для добавления готовых запросов для последующих потоков.
	 QTcpSocket        *p_socket       = nullptr; // Указатель для работы с сокетом.

     std::map<qintptr, std::unique_ptr<QTcpSocket>> *m_MapSocket = nullptr; // Для быстрого доступа к сокетам через дискриптор

	 QByteArray m_data;
	 quint16 m_buffer = 0;

     bool m_v = true;
	 int m_count_client = 0; // Количество активных соед. 

	 QTimer* p_timer = nullptr;

 public slots:
	 void slotReadyRead();
	 void discSocket();
     void run();
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
	 MessageThread(Queue<QByteArray> &QueueResult, std::map<qintptr, std::unique_ptr<QTcpSocket>> &MapSocket);
	 void run();

 private:
	std::map<qintptr, std::unique_ptr<QTcpSocket>>* p_MapSocket = nullptr;
	Queue<QByteArray> *p_QueueResult = nullptr;
	QTcpSocket *p_socket             = nullptr;
};
#endif //WORKING_THREAD
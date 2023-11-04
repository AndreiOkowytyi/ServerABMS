#pragma once

#ifndef WORKING_THREAD
#define WORKING_THREAD

#define TEST   // Вывод дополнительной информации для тестирования.
//#define TEST_1 // Вывод дополнительной информации для тестирования.

#include <map>
#include <qbytearray.h>
#include <QThread>
#include <QTimer>
#include <qdatastream.h>

#include "queue_for_working_with_threads.h" // Потокобезопасная очередь.
#include "secondary_task_control_unit.h"    // Работа с дополнительными задачами.
#include "working_with_data.h"              // Контейнер для сокетов.

class WorkingThread { // Реализация логики выполнения дополнительных задач.
 public:
	 void setWorkibg() {}

 protected:
	 // Указатель на данные, и работа с ними.
};

class FlowOfIncomingRequestsThread : public QObject { // Класс отвечающий за прием новых клиентов, и подготовку запросов.
	Q_OBJECT
 public:
	 FlowOfIncomingRequestsThread(Queue<QByteArray> &QueueRequest, Queue<qintptr>*descriptor, Data &data);
	 ~FlowOfIncomingRequestsThread();

     void newConnection(qintptr descriptor); // Новый клиент.
	 int countClient();                      // Возврашает количиство клиентов.
	 Queue<qintptr>* getQueue();             // У каждого потока своя очередь с клиентами.

 private:
     Queue<qintptr>    *p_Queue        = nullptr; // Очередь запросов на добавления подключения.
	 Queue<QByteArray> *p_QueueRequest = nullptr; // Очередь для добавления готовых запросов для последующих потоков.
	 QTcpSocket        *p_socket       = nullptr; // Указатель для работы с сокетом.
	 Data              *p_Data         = nullptr; // Общий контейнер что связывает все активные клиенты и их информацию.

	 std::map<qintptr, std::unique_ptr<ClientData>>m_Data; // Контейнер для правильной работы с сокетами, и информацию о них.

	 QByteArray m_data;
	 quint16 m_buffer = 0;

     bool m_v = true;        // Флаг для прпавильного старта потока.
	 bool m_a = true;        // Флаг для работы с таймером при новом клиенте.
	 int m_count_client = 0; // Количество активных соед. 

	 QTimer* p_timer = nullptr;

 public slots:
	 void slotReadyRead();  // Чтения из сокета.
	 void discSocket();     // Удаления сокета.
     void run();            // Запуск потока.
	 void workClientData(); // Реализация очищения m_Data.
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
	 MessageThread(Queue<QByteArray> &QueueResult, Data &data);
	 void run();

 private:
	Queue<QByteArray> *p_QueueResult = nullptr;
	QTcpSocket *p_socket             = nullptr;
	Data       *p_Data               = nullptr;
};
#endif //WORKING_THREAD
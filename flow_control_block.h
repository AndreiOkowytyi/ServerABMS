#pragma once

#ifndef FLOW_CONTROL_BLOCK
#define FLOW_CONTROL_BLOCK

#define COUNT_THREAD 3             // Ветки потоков сервера
#define COUNT_DEFAULT_THREADS 32   // Количество потоков по умолчанию.

#include <thread>
#include <vector>
#include <qdebug.h>

#include "working_thread.h" // Реализация работы потоков.

class FlowControlBlock : public QObject {
    Q_OBJECT
 public:
	 FlowControlBlock();
	 ~FlowControlBlock();

	 void newClient(qintptr socketDescriptor); // Обработка новых подключений.

 private:
	 void allocationThread(short* const thread_work);   // Выделение ресурсов под создание потоков основываясь на возможностях системы.
	 void createThread(const short* const thread_work); // Запуск потоков.
	 Queue<qintptr>* threadLoad();                      // Оценка загрузки входных потоков FlowOfIncomingRequestsThread.

	 RequestProcessingThread *p_procassingThread = nullptr;   // Поток для обработки сообщений, и работа с СУБД.
	 MessageThread *p_mesThread                  = nullptr;   // Поток для отправки сообщений.

	 Data<ClientData>m_Data;

	 Queue<QByteArray> m_QueueRequest;                           // Очередь для работы с базой данных.
	 Queue<QByteArray> m_QueueResult;                            // Очередь для работы с результатом запроса к базе данных.

     std::vector<std::unique_ptr<QThread>>m_v_thread;                                            // Работа с потоками.
	 std::vector<std::unique_ptr<FlowOfIncomingRequestsThread>>m_v_FlowOfIncomingRequestsThread; // Вектор для работы с классом что принимает подключения.
	 std::vector<std::unique_ptr<Queue<qintptr>>> m_v_QueueDescriptor;                           // Очередь для обработки новых подключений.
};

#endif //FLOW_CONTROL_BLOCK
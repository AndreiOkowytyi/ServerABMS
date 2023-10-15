#include "flow_control_block.h"

FlowControlBlock::FlowControlBlock() {

	/* 
	Массив thread_work создание pool - потоков.
	*/

	short thread_work[COUNT_THREAD]; 

	allocationThread(thread_work);

	p_procassingThread = new RequestProcessingThread(m_QueueRequest, m_QueueResult);
	p_mesThread        = new MessageThread(m_QueueResult, m_MapSocket);

	if (p_procassingThread != nullptr && p_mesThread != nullptr) createThread(thread_work);
	else qDebug() << "Error Start Server";
}

FlowControlBlock::~FlowControlBlock() {

	if (p_procassingThread != nullptr) delete p_procassingThread;
	if (p_mesThread        != nullptr) delete p_mesThread;
}

void FlowControlBlock::newClient(qintptr socketDescriptor) {

    this->m_MapSocket.emplace(std::pair<qintptr, std::unique_ptr<QTcpSocket>>(socketDescriptor, std::make_unique<QTcpSocket>()));
    m_MapSocket.at(socketDescriptor).get()->setSocketDescriptor(socketDescriptor);
	threadLoad()->emplace(socketDescriptor);
}

void FlowControlBlock::allocationThread(short* const thread_work) {

	short count_thread = std::thread::hardware_concurrency();

	if (count_thread == 0 || count_thread == 2) count_thread = COUNT_DEFAULT_THREADS;

	thread_work[0] = count_thread * 0.25; // Количество потоков приема запросов.
	thread_work[1] = count_thread * 0.5;  // Количество потоков работы с СУБД.
	thread_work[2] = count_thread * 0.25; // Количество потоков обработки результата и его отправки.

	short sum_thread = 0; // Переменная для проверки правильного распределения ресурсов.

	auto lambda = [&]() {

		sum_thread = 0;
		for (short x = 0; x < COUNT_THREAD; ++x) sum_thread += thread_work[x];
		return sum_thread;
	};

	while (count_thread != lambda()) { // Проверка, и распределение потоков.

		if (sum_thread > count_thread) {
			for (short x = 0; x < COUNT_THREAD; ++x)
				if (thread_work[x] > 1) thread_work[x]--;

		} else {

			for (short x = 0; x < COUNT_THREAD; ++x)
				if (thread_work[x] < 1) thread_work[x]++;

				else {
					thread_work[0]++;
					if (count_thread != lambda()) thread_work[1]++;
					if (count_thread != lambda()) thread_work[2]++;
				}
		}
	}
}

void FlowControlBlock::createThread(const short* const thread_work) {

	std::vector<std::thread>v_thread;

    for (short x = 0; x < thread_work[0]; ++x) {

		this->m_v_QueueDescriptor.emplace_back(std::make_unique<Queue<qintptr>>());

		this->m_v_FlowOfIncomingRequestsThread.emplace_back(std::make_unique<FlowOfIncomingRequestsThread>
			                                  (this->m_QueueRequest, this->m_MapSocket, m_v_QueueDescriptor[x].get()));

		this->m_v_thread.emplace_back(std::make_unique<QThread>());
		this->m_v_FlowOfIncomingRequestsThread[x].get()->moveToThread(this->m_v_thread[x].get());

		QObject::connect(m_v_thread[x].get(), SIGNAL(started()), m_v_FlowOfIncomingRequestsThread[x].get(), SLOT(run()));

		this->m_v_thread[x].get()->start();
	}

	for (short y = 0; y < thread_work[1]; ++y) v_thread.push_back(std::thread([=]() { p_procassingThread->run(); }));

	for (short u = 0; u < thread_work[2]; ++u) v_thread.push_back(std::thread([=]() { p_mesThread->run(); }));

	for (short a = 0; a < v_thread.size(); ++a) v_thread[a].detach();
}

Queue<qintptr>* FlowControlBlock::threadLoad() {

	return (std::min_element(this->m_v_FlowOfIncomingRequestsThread.begin(), this->m_v_FlowOfIncomingRequestsThread.end(),
		[=](std::unique_ptr<FlowOfIncomingRequestsThread>& ob_1, std::unique_ptr<FlowOfIncomingRequestsThread>& ob_2) {
		
			return ob_1.get()->countClient() < ob_2.get()->countClient();

		}))->get()->getQueue();
}
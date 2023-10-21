#pragma once

#ifndef FLOW_CONTROL_BLOCK
#define FLOW_CONTROL_BLOCK

#define COUNT_THREAD 3             // ����� ������� �������
#define COUNT_DEFAULT_THREADS 32   // ���������� ������� �� ���������.

#include <thread>
#include <vector>
#include <qdebug.h>

#include "working_thread.h" // ���������� ������ �������.

class FlowControlBlock : public QObject {
    Q_OBJECT
 public:
	 FlowControlBlock();
	 ~FlowControlBlock();

	 void newClient(qintptr socketDescriptor); // ��������� ����� �����������.

 private:
	 void allocationThread(short* const thread_work);   // ��������� �������� ��� �������� ������� ����������� �� ������������ �������.
	 void createThread(const short* const thread_work); // ������ �������.
	 Queue<qintptr>* threadLoad();                      // ������ �������� ������� ������� FlowOfIncomingRequestsThread.

	 RequestProcessingThread *p_procassingThread = nullptr;   // ����� ��� ��������� ���������, � ������ � ����.
	 MessageThread *p_mesThread                  = nullptr;   // ����� ��� �������� ���������.

	 Data<ClientData>m_Data;

	 Queue<QByteArray> m_QueueRequest;                           // ������� ��� ������ � ����� ������.
	 Queue<QByteArray> m_QueueResult;                            // ������� ��� ������ � ����������� ������� � ���� ������.

     std::vector<std::unique_ptr<QThread>>m_v_thread;                                            // ������ � ��������.
	 std::vector<std::unique_ptr<FlowOfIncomingRequestsThread>>m_v_FlowOfIncomingRequestsThread; // ������ ��� ������ � ������� ��� ��������� �����������.
	 std::vector<std::unique_ptr<Queue<qintptr>>> m_v_QueueDescriptor;                           // ������� ��� ��������� ����� �����������.
};

#endif //FLOW_CONTROL_BLOCK
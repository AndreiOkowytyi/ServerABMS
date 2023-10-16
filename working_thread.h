#pragma once

#ifndef WORKING_THREAD
#define WORKING_THREAD

#define TEST // ����� �������������� ����������.

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
	 // ��������� �� ������, � ������ � ����.
};

class FlowOfIncomingRequestsThread : public QObject { // ����� ���������� �� ����� ����� ��������, � ���������� ��������.
	Q_OBJECT
 public:
	 FlowOfIncomingRequestsThread(Queue<QByteArray> &QueueRequest, std::map<qintptr, std::unique_ptr<QTcpSocket>> &MapSocket,
		 Queue<qintptr>*descriptor);
	 ~FlowOfIncomingRequestsThread();

     void newConnection(qintptr descriptor);
	 int countClient();
	 Queue<qintptr>* getQueue();

 private:
     Queue<qintptr>    *p_Queue        = nullptr; // ������� �������� �� ���������� �����������.
	 Queue<QByteArray> *p_QueueRequest = nullptr; // ������� ��� ���������� ������� �������� ��� ����������� �������.
	 QTcpSocket        *p_socket       = nullptr; // ��������� ��� ������ � �������.

     std::map<qintptr, std::unique_ptr<QTcpSocket>> *m_MapSocket = nullptr; // ��� �������� ������� � ������� ����� ����������

	 QByteArray m_data;
	 quint16 m_buffer = 0;

     bool m_v = true;
	 int m_count_client = 0; // ���������� �������� ����. 

	 QTimer* p_timer = nullptr;

 public slots:
	 void slotReadyRead();
	 void discSocket();
     void run();
};


class RequestProcessingThread : public WorkingThread { // ��������� ��������
 public:
	 RequestProcessingThread(Queue<QByteArray> &QueueRequest, Queue<QByteArray> &QueueResult);
	 void run();

 private:
	 Queue<QByteArray> *p_QueueRequest = nullptr;
	 Queue<QByteArray> *p_QueueResult  = nullptr;
};


class MessageThread : public WorkingThread { // �������� ������� ��������
 public:
	 MessageThread(Queue<QByteArray> &QueueResult, std::map<qintptr, std::unique_ptr<QTcpSocket>> &MapSocket);
	 void run();

 private:
	std::map<qintptr, std::unique_ptr<QTcpSocket>>* p_MapSocket = nullptr;
	Queue<QByteArray> *p_QueueResult = nullptr;
	QTcpSocket *p_socket             = nullptr;
};
#endif //WORKING_THREAD
#include "working_thread.h"
#include <qdebug.h>

#include <thread>
#include <chrono>
#include <iostream>

FlowOfIncomingRequestsThread::FlowOfIncomingRequestsThread(Queue<QByteArray>& QueueRequest, std::map<qintptr, std::unique_ptr<QTcpSocket>> &MapSocket,
    Queue<qintptr>* descriptor) {

    this->p_QueueRequest = &QueueRequest;
    this->p_Queue = descriptor;
    this->m_MapSocket = &MapSocket;

    QTimer *p = new QTimer;

    QObject::connect(p, &QTimer::timeout, this, &FlowOfIncomingRequestsThread::run );
    p->start(1000);
}

FlowOfIncomingRequestsThread::~FlowOfIncomingRequestsThread() { if(this->p_timer != nullptr) delete this->p_timer; }

void FlowOfIncomingRequestsThread::newConnection(qintptr descriptor) {

    QObject::connect(m_MapSocket->at(descriptor).get(), &QTcpSocket::readyRead, this, &FlowOfIncomingRequestsThread::slotReadyRead, Qt::QueuedConnection);
    QObject::connect(m_MapSocket->at(descriptor).get(), &QTcpSocket::disconnected, this, &FlowOfIncomingRequestsThread::discSocket, Qt::QueuedConnection);

    m_count_client++;

#ifdef TEST
    qDebug() << "New connect: " << m_count_client;
    std::cout << "ID thread: " << std::this_thread::get_id() << ";" << std::endl << "Descriptor: " << descriptor << ";" << std::endl;
#endif

    if(!this->p_Queue->empty()) run();
}

void FlowOfIncomingRequestsThread::slotReadyRead() {

    this->p_socket = (QTcpSocket*)sender();

    QDataStream in(this->p_socket);
    in.setVersion(QDataStream::Version::Qt_5_5);
    if (in.status() == QDataStream::Ok) {

        for (;;) {

            if (this->m_buffer == 0) {

                if (this->p_socket->bytesAvailable() < 2) break;
                else in >> this->m_buffer;
            }
            if (this->p_socket->bytesAvailable() < this->m_buffer) break;

            QString message;
            in >> message;

#ifdef TEST
            qDebug() << "Massege socket :" << message + " " + QString::number(p_socket->socketDescriptor());
            std::cout << "Thread id slotReadyRead: " << std::this_thread::get_id() << std::endl;
#endif
            this->m_buffer = 0;
            break;
        }
    }
    else qDebug() << "Fail read";
    this->m_MapSocket->erase(p_socket->socketDescriptor());
    if(!this->p_Queue->empty()) run();
}

void FlowOfIncomingRequestsThread::discSocket() {

    this->p_socket = (QTcpSocket*)sender();
    std::cout << p_socket->socketDescriptor();

#ifdef TEST
    qDebug() << "Disc :" +  QString::number(p_socket->socketDescriptor()) << m_MapSocket->size();
#endif

    this->m_MapSocket->erase(p_socket->socketDescriptor());
    m_count_client--;
}

void FlowOfIncomingRequestsThread::run() {

#ifdef TEST
    std::cout << "RequestsThread run. Thread ID: " << std::this_thread::get_id() << std::endl;
#endif

    if (this->m_v) {

        this->newConnection(this->p_Queue->back());
        this->m_v = false;
    }
    else if (!this->p_Queue->empty()) this->newConnection(this->p_Queue->back());;
}

int FlowOfIncomingRequestsThread::countClient() { return this->m_count_client; }

Queue<qintptr>* FlowOfIncomingRequestsThread::getQueue() { return this->p_Queue; }


RequestProcessingThread::RequestProcessingThread(Queue<QByteArray> &QueueRequest, Queue<QByteArray> &QueueResult){

    this->p_QueueRequest = &QueueRequest;
    this->p_QueueResult  = &QueueResult;
}

void RequestProcessingThread::run() {

    for (;;) {


    }
}


MessageThread::MessageThread(Queue<QByteArray>& QueueResult, std::map<qintptr, std::unique_ptr<QTcpSocket>>& MapSocket) {

    this->p_QueueResult = &QueueResult;
    this->p_MapSocket   = &MapSocket;
}

void MessageThread::run() {

    for (;;) {


    }
}
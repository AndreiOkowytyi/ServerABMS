#include "working_thread.h"
#include <qdebug.h>

#include <thread>
#include <chrono>
#include <iostream>
#include <QTimer>

FlowOfIncomingRequestsThread::FlowOfIncomingRequestsThread(Queue<QByteArray>& QueueRequest, std::map<qintptr, std::unique_ptr<QTcpSocket>> &MapSocket,
    Queue<qintptr>* descriptor) {

    this->p_QueueRequest = &QueueRequest;
    this->m_Queue = descriptor;
    this->m_MapSocket = &MapSocket;

    QTimer *p = new QTimer;

    QObject::connect(p, &QTimer::timeout, this, &FlowOfIncomingRequestsThread::run );
    p->start(1000);
}

void FlowOfIncomingRequestsThread::newConnection(qintptr descriptor) {

    qDebug() << "new connect ";
    std::cout << "ID thread:" <<std::this_thread::get_id() << "; Descroptor" << descriptor << std::endl;

    QObject::connect(m_MapSocket->at(descriptor).get(), &QTcpSocket::readyRead, this, &FlowOfIncomingRequestsThread::slotReadyRead, Qt::QueuedConnection);
    QObject::connect(m_MapSocket->at(descriptor).get(), &QTcpSocket::disconnected, this, &FlowOfIncomingRequestsThread::discSocket, Qt::QueuedConnection);

    m_count_client++;

    if(!this->m_Queue->empty()) run();

}

void FlowOfIncomingRequestsThread::slotReadyRead() {

    qDebug() << "ASD";
    this->m_socket = (QTcpSocket*)sender();
    qDebug() << "ASD";
    std::cout << "Thread message" << std::this_thread::get_id();
    QDataStream in(this->m_socket);
    in.setVersion(QDataStream::Version::Qt_6_0);
    if (in.status() == QDataStream::Ok) {

        for (;;) {

            if (this->m_buffer == 0) {

                if (this->m_socket->bytesAvailable() < 2) break;
                else in >> this->m_buffer;
            }

            if (this->m_socket->bytesAvailable() < this->m_buffer) break;

            QString str_;
            in >> str_;
            qDebug() << str_ + " " + QString::number(m_socket->socketDescriptor());
            std::cout << "Thread message" << std::this_thread::get_id();
            this->m_buffer = 0;
            break;
        }
    }
    else qDebug() << "Fail read";

    if(!this->m_Queue->empty()) run();
}

void FlowOfIncomingRequestsThread::discSocket() {

    m_count_client--;
    qDebug() << "disc";
    this->m_socket = (QTcpSocket*)sender();
    this->m_MapSocket->erase(m_socket->socketDescriptor());
}

void FlowOfIncomingRequestsThread::run() {

    qDebug() << "Work";
    std::cout << std::this_thread::get_id() << " END" << std::endl;

    if (this->m_v) {

        this->newConnection(this->m_Queue->back());
        this->m_v = false;
    }
    else if (!this->m_Queue->empty()) this->newConnection(this->m_Queue->back());;
}

int FlowOfIncomingRequestsThread::countClient() { return this->m_count_client; }

Queue<qintptr>* FlowOfIncomingRequestsThread::getQueue() { return this->m_Queue; }


RequestProcessingThread::RequestProcessingThread(Queue<QByteArray> &QueueRequest, Queue<QByteArray> &QueueResult){

    this->p_QueueRequest = &QueueRequest;
    this->p_QueueResult  = &QueueResult;
}


MessageThread::MessageThread(Queue<QByteArray> &QueueResult, std::map<qintptr, std::unique_ptr<QTcpSocket>> &MapSocket) {

    this->p_QueueResult = &QueueResult;
    this->p_MapSocket   = &MapSocket;

}



void RequestProcessingThread::run() {

    for (;;) {


    }
}

void MessageThread::run() {

    for (;;) {


    }
}

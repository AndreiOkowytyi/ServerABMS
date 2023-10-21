#include "working_thread.h"
#include <qdebug.h>

#include <thread>
#include <chrono>
#include <iostream>


ClientData::ClientData(qintptr key, QTcpSocket* MapSocket, int id) {

    this->m_key = key;
    this->p_Socket = MapSocket;

    QObject::connect(p_Socket, &QTcpSocket::destroyed, this, [this]() {

        emit delete_();
        });
}

unsigned int ClientData::getKey() {

    return this->m_key;
}

QTcpSocket* ClientData::getSocket() {

    return this->p_Socket;
}

int ClientData::getId() {

    return this->m_id;
}

ClientData* ClientData::getThis() { return this; }


FlowOfIncomingRequestsThread::FlowOfIncomingRequestsThread(Queue<QByteArray>& QueueRequest, Queue<qintptr>* descriptor, 
    Data<ClientData>& data) {

    this->p_QueueRequest = &QueueRequest;
    this->p_Queue = descriptor;
    this->p_Data = &data;
}

FlowOfIncomingRequestsThread::~FlowOfIncomingRequestsThread() { if(this->p_timer != nullptr) delete this->p_timer; }

void FlowOfIncomingRequestsThread::newConnection(qintptr descriptor) {

    this->p_socket = new QTcpSocket;
    p_socket->setSocketDescriptor(descriptor);

    m_Data.emplace(std::pair<qintptr, std::unique_ptr<ClientData>>(descriptor, std::make_unique<ClientData>(descriptor, p_socket)));

    this->p_Data->emplace(m_Data.at(descriptor).get()->getId(), m_Data.at(descriptor).get()->getThis());

    if (m_a) {
        p_timer = new QTimer;
        QObject::connect(p_timer, &QTimer::timeout, this, &FlowOfIncomingRequestsThread::run);
        p_timer->start(1000);
        m_a = false;
    }

    QObject::connect(p_socket, &QTcpSocket::readyRead, this, &FlowOfIncomingRequestsThread::slotReadyRead, Qt::QueuedConnection);
    QObject::connect(p_socket, &QTcpSocket::disconnected, this, &FlowOfIncomingRequestsThread::discSocket, Qt::QueuedConnection);
    QObject::connect(p_socket, &QTcpSocket::destroyed, this, [this]() { 

#ifdef TEST
        qDebug() << "DELETE ";
#endif
        p_timer = new QTimer;
        QObject::connect(p_timer, &QTimer::timeout, this, &FlowOfIncomingRequestsThread::run);
        p_timer->start(1000);
        });

    QObject::connect(m_Data.at(descriptor).get(), &ClientData::delete_, this, &FlowOfIncomingRequestsThread::workClientData, Qt::QueuedConnection);

    m_count_client++;

#ifdef TEST
    qDebug() << "New connect: " << m_count_client;
    std::cout << "ID thread: " << std::this_thread::get_id() << ";" << std::endl << "Descriptor: " << descriptor << ";" << std::endl;
#endif
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
}

void FlowOfIncomingRequestsThread::discSocket() {

    delete p_timer;
    p_timer = nullptr;

    this->p_socket = (QTcpSocket*)sender();
    this->p_socket->deleteLater();

#ifdef TEST
    qDebug() << "Disc socket";
#endif
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

void FlowOfIncomingRequestsThread::workClientData() {

    ClientData *p_tenp = (ClientData*)sender();

    qDebug() << m_Data.size();

    this->m_Data.erase(p_tenp->getKey());

    qDebug() << m_Data.size();

    qDebug() << "workClientData";
}


RequestProcessingThread::RequestProcessingThread(Queue<QByteArray> &QueueRequest, Queue<QByteArray> &QueueResult){

    this->p_QueueRequest = &QueueRequest;
    this->p_QueueResult  = &QueueResult;
}

void RequestProcessingThread::run() {

    for (;;) {


    }
}


MessageThread::MessageThread(Queue<QByteArray>& QueueResult, Data<ClientData> &data) {

    this->p_QueueResult = &QueueResult;
    this->p_Data        = &data;
}

void MessageThread::run() {

    for (;;) {


    }
}
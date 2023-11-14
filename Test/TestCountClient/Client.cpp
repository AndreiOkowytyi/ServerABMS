#include "Clinet.h"

Client::Client(QString ip) {

    this->m_socket = new QTcpSocket(this);
    m_time = new QTimer;
    m_time->setInterval(1000);

    this->m_socket->connectToHost(ip, 80);
    this->m_time->start();

    QObject::connect(this->m_time, SIGNAL(timeout()), this, SLOT(mes()));
}

Client::~Client()
{
    delete m_socket;
}

void Client::mes() {

    this->sendToServer("!!!---THIS MESSAGE CLIENT TO SERVER---!!!");
}

void Client::sendToServer(QString message) {


    qDebug() << "111";
    QDataStream out(&m_data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Version::Qt_6_0);
    out << quint16(0) << message;
    out.device()->seek(0);
    out << quint16(m_data.size() - sizeof(quint16));

    if(m_socket->isOpen())

    this->m_socket->write(m_data);
}

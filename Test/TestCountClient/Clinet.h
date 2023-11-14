#pragma once

#ifndef CLINET_H
#define CLINET_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTimer>
#include <vector>

class Client : public QObject {
    Q_OBJECT
public:
    Client(QString ip);
    ~Client();
    void sendToServer(QString message);
private:
    void func();

    QTcpSocket* m_socket = nullptr;
    QByteArray m_data;
    quint16 bufer = 0;
    QTimer* m_time = nullptr;
signals:
    void clic();

private slots:
    void mes();
};

#endif // CLINET_H

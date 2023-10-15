#pragma once

#ifndef SERVER
#define SERVER

#include <qtcpserver.h>

#include "flow_control_block.h"

class Server : public QTcpServer {
	Q_OBJECT
 public:
	 Server();
	 ~Server();

 private:
	 FlowControlBlock* p_ControlBlock = nullptr;

 public slots:
	 void incomingConnection(qintptr socketDescriptor) override;
};

#endif //SERVER

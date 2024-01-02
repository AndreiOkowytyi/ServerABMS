#include "server.h"

Server::Server() {

    if (this->listen(QHostAddress("192.168.0.107"), 80)) {
		this->p_ControlBlock = new FlowControlBlock;
		qDebug() << "Start Server";
	}
}

Server::~Server() {

    if (this->p_ControlBlock != nullptr) delete p_ControlBlock;
}

void Server::incomingConnection(qintptr socketDescriptor) {

	this->p_ControlBlock->newClient(socketDescriptor);
}

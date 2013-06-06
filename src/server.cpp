#include "server.h"

Server::Server(QObject *parent) :
    QTcpServer(parent)
{
    host = QHostAddress::Any;
    port = 1328;
}

void Server::startServer()
{
    if ( !this->listen(host, port)) {
        qDebug() << "Could not start server";
    }
    else {
        qDebug() << "Server successfull started";
    }
}

void Server::incomingConnection(int handle)
{
    qDebug() << handle << " Connecting...";
    ClientThread *thread = new ClientThread(handle, this);

    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

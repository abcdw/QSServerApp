#include "server.h"

Server::Server(QObject *parent)
    : QTcpServer(parent)
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

void Server::clientDisconnected(int ID)
{
    //qDebug() << "message from server: client disconnected" << ID;
}

void Server::incomingConnection(int handle)
{
    qDebug() << handle << " Connecting...";
    ClientThread *thread = new ClientThread(handle, this);

    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(terminated(int)), this, SLOT(clientDisconnected(int)));
    thread->start();
}

#include "clientthread.h"

ClientThread::ClientThread(int ID, QObject *parent) :
    QThread(parent)
{
    socketDescriptor = ID;
}

void ClientThread::run()
{
    qDebug() << socketDescriptor << " Starting thread";
    socket = new QTcpSocket();

    if ( !socket->setSocketDescriptor(this->socketDescriptor) ) {
        emit error(socket->error());
        return;
    }

    qDebug() << socketDescriptor << " Waiting for authentication";

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);

    qDebug() << socketDescriptor << " Client connected";

    exec();
}

bool ClientThread::authenticateClient()
{
    socket->waitForReadyRead();
    QByteArray user = socket->readAll();
    socket->waitForReadyRead();
    QByteArray pass = socket->readAll();

    qDebug() << "user: [" << user << "]";
    qDebug() << "pass: [" << pass << "]";
}

void ClientThread::readyRead()
{
    QByteArray data = socket->readAll();
    qDebug() << socketDescriptor << " Data in: " << data;
}

void ClientThread::disconnected()
{
    socket->deleteLater();
    emit terminated(socketDescriptor);

    qDebug() << socketDescriptor << " Thread ended";

    exit(0);
}

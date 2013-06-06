#include "clientthread.h"

ClientThread::ClientThread(int ID, QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = ID;
}

void ClientThread::run()
{
    qDebug() << socketDescriptor << " Starting thread";
    socket = new QTcpSocket();
    if ( !socket->setSocketDescriptor(this->socketDescriptor) ) {
        emit error(socket->error());
        return;
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);
    qDebug() << socketDescriptor << " Client connected";

    exec();
}

void ClientThread::readyRead()
{
    QByteArray data = socket->readAll();
    qDebug() << socketDescriptor << " Data in: " << data;
}

void ClientThread::disconnected()
{
    socket->deleteLater();
    qDebug() << socketDescriptor << " Thread ended";
    exit(0);
}

#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class ClientThread : public QThread
{
    Q_OBJECT
private:
    QTcpSocket        *socket;

    int socketDescriptor;
    bool authenticateClient();
public:
    explicit ClientThread(int ID, QObject *parent = 0);
    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);
    void terminated(int ID);

public slots:
    void readyRead();
    void disconnected();
    
};

#endif // CLIENTTHREAD_H

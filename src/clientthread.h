#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>
#include <QCryptographicHash>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "src/userlistmodel.h"

class ClientThread : public QThread
{
    Q_OBJECT
private:
    QTcpSocket *socket;
    User       *user;

    int  socketDescriptor;
    bool authenticateClient();
public:
    explicit ClientThread(int ID, QObject *parent = 0);
    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);
    void clientAuthenticated(User *user_);
    void clientDisconnected(User  *user_);

public slots:
    void readyRead();
    void disconnected();

};

#endif // CLIENTTHREAD_H

#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QDebug>

#include "src/clientthread.h"
#include "src/userlistmodel.h"

class Server : public QTcpServer
{
    Q_OBJECT

private:

    QHostAddress host;
    int          port;

protected:
    void incomingConnection(int handle);

public:
    explicit Server(QObject *parent = 0);
    void startServer();

signals:
    void clientAuthenticated(User *user_);
    void clientDisconnected(User  *user_);

public slots:
    void clientTerminated(int ID);

};

#endif // SERVER_H

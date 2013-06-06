#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QDebug>
#include "clientthread.h"

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
    
public slots:
    
};

#endif // SERVER_H

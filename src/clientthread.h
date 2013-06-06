#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>

class ClientThread : public QThread
{
    Q_OBJECT
public:
    explicit ClientThread(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // CLIENTTHREAD_H

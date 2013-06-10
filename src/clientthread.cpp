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

    user = new User(socketDescriptor, "bob", QHostAddress::LocalHost);
    socket->write("please enter your login:password\n");
    if (authenticateClient())
    {
        qDebug() << socketDescriptor << " Client authenticated";
        socket->write("authenticated\n");
        emit clientAuthenticated(user);
    }
    else {
        socket->write("authentication failed\n");
        qDebug() << socketDescriptor << " Authentication failed";
        QTimer::singleShot(1, socket, SLOT(disconnectFromHostImplementation()));
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);

    exec();
}

bool ClientThread::authenticateClient()
{
    socket->waitForReadyRead();
    QByteArray authData = socket->readAll();
    QString authString(authData);
    QStringList authStrs = authString.split(":");
    if (authStrs.count() < 2)
        return 0;
    QString login(authStrs[0].simplified());
    QString pass(authStrs[1].simplified());
    QString encryptedPass = QString(QCryptographicHash::hash((pass.toAscii()), QCryptographicHash::Md5).toHex());

    user->name = login;
    user->host = socket->peerAddress();
    QSqlDatabase authDB = QSqlDatabase::database("auth");

    QSqlQuery query(authDB);

    query.prepare("SELECT id, password FROM account WHERE username = :login");
    query.bindValue(":login", login);
    query.exec();

    if (query.size() < 1)
        return 0;
    query.next();

//    qDebug() << "query: " << query.value(0).toString() << " " << query.value(1).toString();
//    qDebug() << "user: [" << login << "]";
//    qDebug() << "pass: [" << encryptedPass << ", " << pass << "]";

    return query.value(1).toString() == encryptedPass;

    return 1;
}

void ClientThread::readyRead()
{
    QByteArray data = socket->readAll();
    qDebug() << socketDescriptor << " Data in: " << data;
}

void ClientThread::disconnected()
{
    qDebug() << socketDescriptor << " Client disconnected";

    socket->deleteLater();
    emit clientDisconnected(user);

    QTimer::singleShot(1, this, SLOT(quit()));
}

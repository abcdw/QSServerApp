#ifndef USERLISTMODEL_H
#define USERLISTMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QDebug>
#include <QBrush>
#include <QFont>
#include <QHostAddress>

struct User
{
    User(int socketID_, const QString &name_, QHostAddress host_);
    int socketID;
    QString name;
    QHostAddress host;
};

class UserListModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    QList<User> users;

public:
    explicit UserListModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

signals:
    
public slots:

};

#endif // USERLISTMODEL_H

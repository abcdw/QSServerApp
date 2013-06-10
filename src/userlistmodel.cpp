#include "userlistmodel.h"

UserListModel::UserListModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

User::User(int socketID_, const QString &name_, QHostAddress host_)
    : socketID(socketID_), name(name_), host(host_)
{

}

bool User::operator==(const User &user_) const
{
    return socketID == user_.socketID;
}

void UserListModel::addUser(User *user_)
{
    users << User(*user_);
    emit layoutChanged();
}

void UserListModel::delUser(User *user_)
{
    users.removeOne(User(*user_));
    emit layoutChanged();
}

QVariant UserListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return QString("id");
            case 1:
                return QString("name");
            case 2:
                return QString("host");
            }
        }
    }
    return QVariant();
}

int UserListModel::rowCount(const QModelIndex & /* parent */) const
{
    return users.count();
}

int UserListModel::columnCount(const QModelIndex & /* parent */) const
{
    return 3;
}

QVariant UserListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    switch(role) {
    case Qt::DisplayRole:
        switch(col) {
        case 0:
            return users[row].socketID;
        case 1:
            return users[row].name;
        case 2:
            return users[row].host.toString();
        }
        break;
    case Qt::FontRole:
//        if (row == 0 && col == 0) //change font only for cell(0,0)
//        {
//            QFont boldFont;
//            boldFont.setBold(true);
//        //    return boldFont;
//        }
        break;
    case Qt::BackgroundRole:

//        if (row == 1 && col == 2)  //change background only for cell(1,2)
//        {
//            QBrush redBackground(Qt::red);
//        //    return redBackground;
//        }
        break;
    case Qt::TextAlignmentRole:

//        if (row == 1 && col == 1) //change text alignment only for cell(1,1)
//        {
//        //    return Qt::AlignRight + Qt::AlignVCenter;
//        }
        break;
    case Qt::CheckStateRole:

        if (row == 1 && col == 0) //add a checkbox to cell(1,0)
        {
        //    return Qt::Checked;
        }
    }
    return QVariant();
}

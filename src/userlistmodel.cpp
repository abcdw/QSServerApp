#include "userlistmodel.h"

UserListModel::UserListModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant UserListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("id");
            case 1:
                return QString("name");
            case 2:
                return QString("ip");
            }
        }
    }
    return QVariant();
}

int UserListModel::rowCount(const QModelIndex & /* parent */) const
{
    return 10;
}

int UserListModel::columnCount(const QModelIndex & /* parent */) const
{
    return 3;
}

QVariant UserListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
//    qDebug() << QString("row %1, col%2, role %3")
            .arg(row).arg(col).arg(role);

    switch(role) {
    case Qt::DisplayRole:
        if (row == 0 && col == 1)
            return QString("<--left");
        if (row == 1 && col == 1)
            return QString("right-->");

        return QString("Row%1, Column%2")
                .arg(row + 1)
                .arg(col +1);
        break;
    case Qt::FontRole:
        if (row == 0 && col == 0) //change font only for cell(0,0)
        {
            QFont boldFont;
            boldFont.setBold(true);
            return boldFont;
        }
        break;
    case Qt::BackgroundRole:

        if (row == 1 && col == 2)  //change background only for cell(1,2)
        {
            QBrush redBackground(Qt::red);
            return redBackground;
        }
        break;
    case Qt::TextAlignmentRole:

        if (row == 1 && col == 1) //change text alignment only for cell(1,1)
        {
            return Qt::AlignRight + Qt::AlignVCenter;
        }
        break;
    case Qt::CheckStateRole:

        if (row == 1 && col == 0) //add a checkbox to cell(1,0)
        {
            return Qt::Checked;
        }
    }
    return QVariant();
}

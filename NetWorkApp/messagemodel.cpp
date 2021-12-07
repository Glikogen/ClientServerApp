#include "messagemodel.h"

MessagesModel::MessagesModel(QObject *parent) : QStringListModel(parent)
{
}

void MessagesModel::setMessageModel(QList<QString> list)
{
    setStringList(list);
}

void MessagesModel::addMessage(QString message)
{
    if (message.contains("->") && message.contains(":"))
    {
        QStringList mylist = message.split("->");
        QStringList wow = mylist.at(1).split(':');
        message = wow.at(0) + "|" + wow.at(1) + "|" + mylist.at(0);
    }
    messages.append(message);
    setStringList(messages);
}

int MessagesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;

    return messages.count();
}

QVariant MessagesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    if (index.row() < 0 || index.row() > messages.size()) return QVariant();


    auto mes = stringList().at(index.row());
    QString name;
    QString line;
    QString time;
    QStringList list = mes.split('|');
    if (list.count() == 3)
    {
        name = list.at(0);
        line = list.at(1);
        time = list.at(2);
    }
    else line = mes;



    if (role == Qt::UserRole) {
        return name;
    }
    if (role == Qt::UserRole+1) {
        return line;
    }
    if (role == Qt::UserRole+2) {
        return time;
    }



    if (role == Qt::DisplayRole) return mes;
    return QVariant();
}


QHash<int, QByteArray> MessagesModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();

    roles.insert(Qt::UserRole, "name");
    roles.insert(Qt::UserRole + 1, "line");
    roles.insert(Qt::UserRole + 2, "time");

    qDebug() << roles;
    return roles;
}

bool MessagesModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid()) return false;

    beginInsertRows(QModelIndex(), row, row + count - 1);
    messages.insert(row, "soo");
    endInsertRows();

    return true;
}

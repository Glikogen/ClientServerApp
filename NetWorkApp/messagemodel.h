#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QList>
#include <QVariant>
#include <QVariantMap>
#include <QHash>
#include <QDebug>
#include <QStringListModel>

class MessagesModel : public QStringListModel
{
    Q_OBJECT
public:
    explicit MessagesModel(QObject *parent = nullptr);
    QList<QString> messages;
    void setMessageModel(QList<QString> list);
public slots:
    void addMessage(QString message);
private:
    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    // QAbstractItemModel interface
public:
    bool insertRows(int row, int count, const QModelIndex &parent);
};

#endif // MESSAGEMODEL_H

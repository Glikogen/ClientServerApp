#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>
#include <QtCore>
#include "client.h"
#include <QAbstractListModel>
#include <QList>
#include "messagemodel.h"

class ViewModel : public QObject
{
    Q_OBJECT

    MessagesModel *m_messagesModel;

public:
    explicit ViewModel(QObject *parent = nullptr);

    Q_PROPERTY(MessagesModel* messagesModel READ messagesModel WRITE setMessagesModel NOTIFY messagesModelChanged)

    bool isConnected = false;
    Q_INVOKABLE bool isConnect();
    Client *client;

    MessagesModel *messagesModel() const;
    void setMessagesModel(MessagesModel *newMessagesModel);
public slots:
    void connectToServer(QString name, QString IP, int port);
    //void forceDisconnection();
    void disconnectFromServer();
    void sendMessage(QString message);
signals:
    void addMessageToChat(QString);
    void clientDisconnected();
    void messagesModelChanged();
};

#endif // VIEWMODEL_H

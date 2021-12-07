#include "viewmodel.h"

ViewModel::ViewModel(QObject *parent) : QObject(parent)
{
    m_messagesModel = new MessagesModel();
}

bool ViewModel::isConnect()
{
    return isConnected;
}

void ViewModel::connectToServer(QString name, QString IP, int port)
{
    //подключаем клиента к серверу
    client = new Client(name, IP, port);
    connect(client, SIGNAL(addMessageToClientChat(QString)), m_messagesModel, SLOT(addMessage(QString)));
    connect(this, SIGNAL(clientDisconnected()), client, SLOT(slotDisconnect()));
    connect(client, &Client::clientConnectedSuccessfully, [=]() { isConnected = true; });
    connect(client, SIGNAL(clientWasForciblyDisconnected()), this, SLOT(disconnectFromServer()));
}

//void ViewModel::forceDisconnection()
//{
//    //отключаем клиента от сервера
//    isConnected = false;
//    emit addMessageToChat("Вас отключили от сервера!");
//}

void ViewModel::disconnectFromServer()
{
    //отключаем клиента от сервера
    isConnected = false;
    emit clientDisconnected();
    disconnect(this, SIGNAL(clientDisconnected()), client, SLOT(slotDisconnect()));
}

void ViewModel::sendMessage(QString message)
{
    //отправляем на сервак
    client->slotSendToServer(message);
}

MessagesModel *ViewModel::messagesModel() const
{
    return m_messagesModel;
}

void ViewModel::setMessagesModel(MessagesModel *newMessagesModel)
{
    if (m_messagesModel == newMessagesModel)
        return;
    m_messagesModel = newMessagesModel;
    emit messagesModelChanged();
}

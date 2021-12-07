#include "server.h"

Server::Server(QObject *parent) : QObject(parent) { }

void Server::OpenServer(QString name, int port)
{
    server = new QTcpServer();
    serverName = name;
    if (!server->listen(QHostAddress::Any, port))
    {
        //мб прокинем ошибку куда-нить
        QString error = "Server error! Unable to start server: " + server->errorString();
        emit ErrorHappened(error);
    }

    connect(server, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    emit MessageForServerChat("Server " + serverName + " is open now!");
}

void Server::sendToClients(const QString &line)
{
    if (clientsList.count() == 0) return;
    //задротный метод
//    QByteArray arrBlock;
//    QDataStream dataToSend(&arrBlock, QIODevice::WriteOnly);
//    dataToSend.setVersion(QDataStream::Qt_5_15);
//    dataToSend << quint16(0) << line;
//    dataToSend.device()->seek(0);
//    dataToSend << quint16(arrBlock.size() - sizeof(quint16));
//    client->socket->write(arrBlock);
    /////////разделение
    QByteArray sendingData = line.toUtf8();
    for(auto client : qAsConst(clientsList))
    {
        client->socket->write(sendingData);
        client->socket->waitForBytesWritten(50);
    }
}

void Server::slotNewConnection()
{
    QTcpSocket *newSocket = server->nextPendingConnection();
    Client *newClient = new Client(newSocket);
    connect(newClient, SIGNAL(ReadSocket(Client*)), this, SLOT(slotReadClient(Client*)));
    connect(newClient, SIGNAL(clientDisconnected(QString)), this, SLOT(clientDisconect(QString)));
}

void Server::slotReadClient(Client *client)
{
    QString line = client->socket->readAll();
    qDebug() << line;
    if (line.left(6) == "[NAME]")
    {
        line.remove(0, 6);
        client->Name = line;
        emit newClientConnected(client->Name);
        QString message = client->Name + " joined our chat!";
        emit MessageForServerChat(message);
        sendToClients(message);
        clientsList.append(client);
        return;
    }

    QString message = QTime::currentTime().toString("hh:mm:ss") + "->" + client->Name + ": " + line;
    emit MessageForServerChat(message);
    sendToClients(message);
    /////////разделение
    //задротный метод
//    QDataStream receivedData(client->socket);
//    receivedData.setVersion(QDataStr    /////test
//    for(;;)
//    {
//        if (!nextBlockSize) {
//            if (client->socket->bytesAvailable() < sizeof(quint16)) break;
//            receivedData >> nextBlockSize;
//        }
//        if (client->socket->bytesAvailable() < nextBlockSize) break;

//        QString line;
//        receivedData >> line;

//        if (line.left(6) == "[NAME]")
//        {
//            line.remove(0, 6);
//            client->Name = line;
//            emit newClientConnected(client->Name);
//            emit MessageForServerChat(client->Name + " joined our chat!");
//            nextBlockSize = 0;
//            return;
//        }

//        QString message = QTime::currentTime().toString("hh:mm:ss") + "->" + client->Name + ": " + line;
//        emit MessageForServerChat(message);
//        nextBlockSize = 0;
//        sendToClient(client, message);
//    }
}

void Server::slotClose()
{
    emit MessageForServerChat(serverName + " is closed.");
    server->close();
}

void Server::clientDisconect(QString name)
{
    for(Client* client : qAsConst(clientsList))
    {
        if (client->Name == name && client->socket->isOpen())
        {
            client->socket->disconnectFromHost();
            clientsList.removeOne(client);
            QString message = name + " disconnected.";
            sendToClients(message);
            emit MessageForServerChat(message);
            emit clientQuitted(name);
            return;
        }
    }
}

void Server::clientForcedDisconnect(QString name)
{
    for(Client* client : qAsConst(clientsList))
    {
        if (client->Name == name && client->socket->isOpen())
        {
            client->socket->disconnectFromHost();
            return;
        }
    }
}

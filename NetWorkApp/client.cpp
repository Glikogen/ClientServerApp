#include "client.h"

Client::Client(QString name, const QString &HostName, int port, QObject *parent) : QObject(parent),
    nextBlockSize(0)
{
    client = new QTcpSocket();
    Name = name;

    client->connectToHost(HostName, port);
    connect(client, SIGNAL(connected()), this, SLOT(slotConnected()));
    connect(client, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(client, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
}

void Client::slotReadyRead()
{
    QString message = client->readAll();
    emit addMessageToClientChat(message);
    /////////разделение
    //задротный метод
//    QDataStream receivedData(client);
//    receivedData.setVersion(QDataStream::Qt_5_15);
//    for(;;)
//    {
//        if (!nextBlockSize)
//        {
//            if (client->bytesAvailable() < sizeof(quint16)) break;
//            receivedData >> nextBlockSize;
//        }

//        if (client->bytesAvailable() < nextBlockSize) break;

//        QString line;
//        receivedData >> line;

//        emit addMessageToClientChat(line);
//        nextBlockSize = 0;
//    }
}

void Client::slotError(QAbstractSocket::SocketError err)
{
    QString error = "Error: " + client->errorString();
    if (err == QAbstractSocket::RemoteHostClosedError)
    {
        error = "Вас отключили от сервера! бывает же(( (но возможно сервер упал, страшные вещи происходят)";
        qDebug() << error;
        emit clientWasForciblyDisconnected();
    }
    //подробные ошибки в этой конструкции не работают ... фак ит
//    QString error = "Error: " + (err == QAbstractSocket::HostNotFoundError ?
//                "the host was not found." : err = QAbstractSocket::RemoteHostClosedError ?
//                "the remote host is closed." : err == QAbstractSocket::ConnectionRefusedError ?
//                "the connection was refused." : QString(client->errorString()));
    emit addMessageToClientChat(error);
}

void Client::slotSendToServer(QString line)
{
    //задротный метод
//    QByteArray arrBlock;
//    QDataStream dataToSend(&arrBlock, QIODevice::WriteOnly);
//    dataToSend.setVersion(QDataStream::Qt_5_15);
//    dataToSend << quint16(0) << line;
//    dataToSend.device()->seek(0);
//    dataToSend << quint16(arrBlock.size() - sizeof(quint16));
//    client->write(arrBlock);
        /////////разделение
    QByteArray sendingData = line.toUtf8();
    client->write(sendingData);
    client->waitForBytesWritten(50);
}

void Client::slotConnected()
{
    emit clientConnectedSuccessfully();
    //на всякий
    QThread::msleep(50);
    slotSendToServer("[NAME]" + Name);
    addMessageToClientChat("You connected");
}

void Client::slotDisconnect()
{
    emit addMessageToClientChat("You disconnected from server");
    client->close();
}

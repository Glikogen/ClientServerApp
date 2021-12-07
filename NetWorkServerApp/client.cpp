#include "client.h"

Client::Client(QTcpSocket *_socket, QObject *parent) : QObject(parent)
{
    socket = _socket;
    connect(socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadSocket()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(slotClientDisconnected()));
}

void Client::slotReadSocket()
{
    emit ReadSocket(this);
}

void Client::slotClientDisconnected()
{
    emit clientDisconnected(Name);
}

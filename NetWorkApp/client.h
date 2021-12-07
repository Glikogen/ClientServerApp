#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QtCore>
#include <QByteArray>
#include <QDataStream>
#include <QTextStream>
#include <QDebug>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QString name, const QString& HostName, int port, QObject *parent = nullptr);

    QString Name;
private:
    QTcpSocket *client;
    quint16 nextBlockSize;
private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError err);
    void slotConnected();
public slots:
    void slotDisconnect();
    void slotSendToServer(QString line);
signals:
    void addMessageToClientChat(QString);
    void clientConnectedSuccessfully();
    void clientWasForciblyDisconnected();
};

#endif // CLIENT_H

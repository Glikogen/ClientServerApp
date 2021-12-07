#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtCore>
#include "client.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QByteArray>
#include <QTextStream>
#include <QDebug>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    void OpenServer(QString name, int port);
    QList<Client*> clientsList;
private:
    QString serverName;
    QTcpServer *server;
    quint16 nextBlockSize;

    void sendToClients(const QString &line);
signals:
    void ErrorHappened(QString);
    void MessageForServerChat(QString);
    void newClientConnected(QString);
    void clientQuitted(QString);
public slots:
    virtual void slotNewConnection();
    void slotReadClient(Client *client);
    void slotClose();
    void clientDisconect(QString name);
    void clientForcedDisconnect(QString name);
};

#endif // SERVER_H

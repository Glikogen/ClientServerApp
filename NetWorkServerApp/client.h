#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QTcpSocket *_socket, QObject *parent = nullptr);

    QString Name;
    QTcpSocket *socket;
public slots:
    void slotReadSocket();
    void slotClientDisconnected();
signals:
    void sendMessageToServer(QString);
    void ReadSocket(Client*);
    void clientDisconnected(QString);
};

#endif // CLIENT_H

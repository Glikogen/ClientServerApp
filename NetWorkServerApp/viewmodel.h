#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>
#include <QtCore>
#include <QStringList>
#include <QStringListModel>
#include "client.h"
#include "server.h"
#include <QFile>

class ViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isOpen READ isOpen WRITE setIsOpen NOTIFY isOpenChanged)
    Q_PROPERTY(QStringListModel* clientsListModel READ clientsListModel NOTIFY clientsListModelChanged)
private:
    bool m_isOpen;

    QStringListModel *m_clientsListModel;

public:
    explicit ViewModel(QObject *parent = nullptr);

    bool isOpen() const;
    void setIsOpen(bool newIsOpen);

    Server *server;
    QStringList clients;
    QStringListModel *clientsListModel() const;
    QString fileName;
public slots:
    void openServer(QString nameOfServer, int port);
    void closeServer();
    void clientConnected(QString clientName);
    void clientDisconnected(QString clientName);
    void forcedClientDisconnect(int index);
    void chooseFolderToSaveChat(QString path);
    void writeMessageToFile(QString message);
signals:
    void addMessagetoChat(QString);
    void isOpenChanged();
    void newClient(Client*);
    void clientsListModelChanged();
};

#endif // VIEWMODEL_H

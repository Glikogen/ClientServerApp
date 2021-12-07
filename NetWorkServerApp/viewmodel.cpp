#include "viewmodel.h"

ViewModel::ViewModel(QObject *parent) : QObject(parent)
{
    m_isOpen = false;
    m_clientsListModel = new QStringListModel();
}

bool ViewModel::isOpen() const
{
    return m_isOpen;
}

void ViewModel::setIsOpen(bool newIsOpen)
{
    if (m_isOpen == newIsOpen)
        return;
    m_isOpen = newIsOpen;
    emit isOpenChanged();
}

void ViewModel::openServer(QString nameOfServer, int port)
{
    server = new Server();
    setIsOpen(true);
    connect(server, SIGNAL(MessageForServerChat(QString)), this, SIGNAL(addMessagetoChat(QString)));
    connect(server, SIGNAL(ErrorHappened(QString)), this, SIGNAL(addMessagetoChat(QString)));
    connect(server, SIGNAL(newClientConnected(QString)), this, SLOT(clientConnected(QString)));
    connect(server, SIGNAL(clientQuitted(QString)), this, SLOT(clientDisconnected(QString)));
    connect(server, SIGNAL(MessageForServerChat(QString)), this, SLOT(writeMessageToFile(QString)));

    server->OpenServer(nameOfServer, port);
}

void ViewModel::closeServer()
{
    //закрыть сервер
    setIsOpen(false);
    server->slotClose();
    disconnect(server, SIGNAL(MessageForServerChat(QString)), this, SLOT(writeMessageToFile(QString)));
}

void ViewModel::clientConnected(QString clientName)
{
    clients.append(clientName);
    m_clientsListModel->setStringList(clients);
}

void ViewModel::clientDisconnected(QString clientName)
{
    clients.removeOne(clientName);
    m_clientsListModel->setStringList(clients);
}

void ViewModel::forcedClientDisconnect(int index)
{
    QString name = clients.at(index);
    server->clientForcedDisconnect(name);
}

void ViewModel::chooseFolderToSaveChat(QString path)
{
    path = path.remove(0, 7);
    fileName = path + "/Chat_" + QDateTime::currentDateTime().toString("dd.mm.yyyy") +
            "_" + QTime::currentTime().toString("hh:mm") + ".txt";
    qDebug() << fileName;
}

void ViewModel::writeMessageToFile(QString message)
{
    if (fileName == "") return;

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream(&file) << message << endl;
        file.close();
    }
}

QStringListModel *ViewModel::clientsListModel() const
{
    return m_clientsListModel;
}

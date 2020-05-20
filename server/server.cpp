#include <QTcpSocket>
#include <QDataStream>
#include <QDebug>
#include "server.h"
#include "client.h"

using namespace std;

Server::Server(QObject *parent)
    : QObject(parent),
    tcpServer(this)
{
    connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

bool Server::start(int port)
{
    return tcpServer.listen(QHostAddress::Any, port);
}

void Server::onNewConnection()
{
    qDebug() << "# Got new connection.";

    QTcpSocket * clientSocket = tcpServer.nextPendingConnection();
    
    Client * client = new Client(clientSocket, this);
    connect(client, SIGNAL(gotMessage(QByteArray)), this, SLOT(onMessageReceived(QByteArray)));
    connect(client, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));
    
    //connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    //connect(clientSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(onBytesWritten(qint64)));
    //connect(clientSocket, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));
}

void Server::onMessageReceived(QByteArray message)
{
    qDebug() << "# Client received a message.";

    Client * client = static_cast<Client*>(sender());
    client->sendMessage(message);  // echo server
}

void Server::onClientDisconnected()
{
    qDebug() << "# Client disconnected.";

    Client * client = static_cast<Client*>(sender());

    client->deleteLater();
}


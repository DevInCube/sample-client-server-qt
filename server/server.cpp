#include <QTcpSocket>
#include <QDataStream>
#include <QDebug>
#include "server.h"

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
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(clientSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(onBytesWritten(qint64)));
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));
}

void Server::onReadyRead()
{
    qDebug() << "# Receiving request data:";

    QTcpSocket * clientSocket = static_cast<QTcpSocket*>(sender());

    QByteArray data = clientSocket->readAll();

    qDebug() << "# Received " << data.length() << " bytes:";
    qDebug() << data;

    if (request.length() == 0) // first part
        request = data;
    else
        request.append(data);

    QDataStream stream(&request, QIODevice::ReadOnly);
    int32_t message_length = 0;
    stream >> message_length;

    qDebug() << "# Received data length: " << request.length();
    qDebug() << "# Total message length: " << message_length;

    if (message_length == request.length())
    {
        qDebug() << "# Got full request here.";

        QString responseStr = "Hello from server!";

        qDebug() << "# Sending response: ";
        qDebug() << responseStr;

        clientSocket->write(responseStr.toUtf8());
        clientSocket->flush();

        request.clear();
    }
}

void Server::onBytesWritten(qint64 n)
{
    qDebug() << "#" << n << "bytes sent.";

    QTcpSocket * clientSocket = static_cast<QTcpSocket*>(sender());
    clientSocket->close();
}

void Server::onClientDisconnected()
{
    qDebug() << "# Client disconnected.";

    QTcpSocket * clientSocket = static_cast<QTcpSocket*>(sender());
    clientSocket->deleteLater();
}

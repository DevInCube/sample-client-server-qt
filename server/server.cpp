#include <QTcpSocket>
#include <QDebug>
#include "server.h"

using namespace std;

Server::Server(QObject *parent) : QObject(parent)
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    int PORT = 3000;
    if (!tcpServer->listen(QHostAddress::Any, PORT)) {
        qDebug() << "error listen ";
    } else {
        qDebug() << "started at " << PORT;
    }
}

void Server::onNewConnection() {
    qDebug() << "got new connection";
    QTcpSocket * clientSocket = tcpServer->nextPendingConnection();
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(clientSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(onBytesWritten(qint64)));
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));
}

void Server::onReadyRead() {
    QTcpSocket * clientSocket = static_cast<QTcpSocket*>(sender());
    qDebug() << "receiving data";
    QByteArray data = clientSocket->readAll();
    qDebug() << "Received " << data.length() << " bytes:";
    qDebug() << data;
    //
    QString responseStr = "Hello from server!";
    qDebug() << "Sending: ";
    qDebug() << responseStr;
    clientSocket->write(responseStr.toUtf8());
    clientSocket->flush();
}

void Server::onBytesWritten(qint64 n) {
    qDebug() << n << "bytes written";
    QTcpSocket * clientSocket = static_cast<QTcpSocket*>(sender());
    clientSocket->close();
}

void Server::onClientDisconnected() {
    qDebug() << "Client disconnected ";
    QTcpSocket * clientSocket = static_cast<QTcpSocket*>(sender());
    delete clientSocket;
}

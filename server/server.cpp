#include "server.h"
#include <iostream>
#include <QTcpSocket>

using namespace std;

Server::Server(QObject *parent) : QObject(parent)
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    int PORT = 3000;
    if (!tcpServer->listen(QHostAddress::Any, PORT)) {
        cerr << "error listen " << endl;
    } else {
        cout << "started at " << PORT << endl;
    }
}

void Server::onNewConnection() {
    cout << "got new connection" << endl;
    QTcpSocket * clientSocket = tcpServer->nextPendingConnection();
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(clientSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(onBytesWritten(qint64)));
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));
}

void Server::onReadyRead() {
    QTcpSocket * clientSocket = static_cast<QTcpSocket*>(sender());
    cout << "receiving data" << endl;
    QByteArray data = clientSocket->readAll();
    cout << "Received:" << endl << data.toStdString() << endl;
    //
    QString responseStr = "Hello from server!";
    cout << "Sending: " << endl << responseStr.toStdString() << endl;
    clientSocket->write(responseStr.toUtf8());
    clientSocket->flush();
}

void Server::onBytesWritten(qint64 n) {
    cout << "bytes written" << endl;
    QTcpSocket * clientSocket = static_cast<QTcpSocket*>(sender());
    clientSocket->close();
    //
}

void Server::onClientDisconnected() {
    cout << "Client disconnected " << endl;
    QTcpSocket * clientSocket = static_cast<QTcpSocket*>(sender());
    delete clientSocket;
}

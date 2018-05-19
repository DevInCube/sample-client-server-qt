#include "client.h"
#include <QTcpSocket>
#include <iostream>
#include <QHostAddress>

using namespace std;

Client::Client(QObject *parent) : QObject(parent)
{
    QTcpSocket * client = new QTcpSocket(this);
    connect(client, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(client, SIGNAL(bytesWritten(qint64)), this, SLOT(onBytesWritten(qint64)));
    connect(client, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(client, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    QHostAddress serverAddress("127.0.0.1");
    int PORT = 3000;
    cout << "connecting to server at port " << PORT << endl;
    client->connectToHost(serverAddress, PORT);
}

void Client::onConnected() {
    cout << "connected" << endl;
    QTcpSocket * clientSocket = static_cast<QTcpSocket*>(sender());
    QString requestStr = "Hello!";
    cout << "Sending: " << endl << requestStr.toStdString() << endl;
    clientSocket->write(requestStr.toUtf8());
    clientSocket->flush();
}

void Client::onReadyRead() {
    cout << "ready to read" << endl;
    QTcpSocket * clientSocket = static_cast<QTcpSocket*>(sender());
    QByteArray data = clientSocket->readAll();
    cout << "Received:" << endl << data.toStdString() << endl;
    clientSocket->disconnectFromHost();
}

void Client::onBytesWritten(qint64 n) {
    cout << "bytes  written " << endl;
}

void Client::onDisconnected() {
    cout << "disconnected" << endl;
    QTcpSocket * clientSocket = static_cast<QTcpSocket*>(sender());
    delete clientSocket;
}

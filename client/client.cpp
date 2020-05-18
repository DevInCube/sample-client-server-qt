#include "client.h"
#include <QTcpSocket>
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
    qDebug() << "connecting to server at port " << PORT;
    client->connectToHost(serverAddress, PORT);
}

void Client::onConnected() {
    qDebug() << "connected" << endl;
    QTcpSocket * clientSocket = static_cast<QTcpSocket*>(sender());
    QString requestStr = "Hello!";
    qDebug() << "Sending: ";
    qDebug() << requestStr;
    clientSocket->write(requestStr.toUtf8());
    clientSocket->flush();
}

void Client::onReadyRead() {
    qDebug() << "ready to read" << endl;
    QTcpSocket * clientSocket = static_cast<QTcpSocket*>(sender());
    QByteArray data = clientSocket->readAll();
    qDebug() << "Received " << data.length() << " bytes:";
    qDebug() << data;
    clientSocket->disconnectFromHost();
}

void Client::onBytesWritten(qint64 n) {
    qDebug() << n << " bytes  written";
}

void Client::onDisconnected() {
    qDebug() << "disconnected";
    QTcpSocket * clientSocket = static_cast<QTcpSocket*>(sender());
    delete clientSocket;
}

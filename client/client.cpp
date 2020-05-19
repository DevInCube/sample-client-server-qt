#include "client.h"
#include <QTcpSocket>
#include <QHostAddress>

using namespace std;

Client::Client(int port, QObject *parent)
    : port(port),
      QObject(parent),
      socket(this)
{
    connect(&socket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(&socket, SIGNAL(bytesWritten(qint64)), this, SLOT(onBytesWritten(qint64)));
    connect(&socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(&socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

void Client::sendRequest(QByteArray data)
{
    qDebug() << "connecting to server at port " << port;

    request = data;
    socket.connectToHost(QHostAddress::LocalHost, port);
}

void Client::onConnected()
{
    qDebug() << "connected";
    qDebug() << "Sending " << request.length() << " bytes:";
    qDebug() << QString::fromUtf8(request);

    socket.write(request);
    socket.flush();

    request.clear();
}

void Client::onReadyRead()
{
    qDebug() << "ready to read";

    QByteArray data = socket.readAll();

    qDebug() << "Received " << data.length() << " bytes:";
    qDebug() << data;

    emit gotResponse(data);

    socket.disconnectFromHost();
}

void Client::onBytesWritten(qint64 n)
{
    qDebug() << n << " bytes  written";
}

void Client::onDisconnected()
{
    qDebug() << "disconnected from server";
}

#include <QHostAddress>

#include "client.h"

Client::Client(int port, QObject *parent)
    : QObject(parent),
      port(port),
      socket(this)
{
    connect(&socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));

    connect(&socket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(&socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

    connect(&socket, SIGNAL(bytesWritten(qint64)), this, SLOT(onBytesWritten(qint64)));
    connect(&socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void Client::sendRequest(QByteArray data)
{
    qDebug() << "# Connecting to server at port " << port << "...";

    request = data;
    socket.connectToHost(QHostAddress::LocalHost, port);
}

void Client::onError(QAbstractSocket::SocketError error)
{
    qDebug() << "# Got error: " << error;

    socket.close();
}

void Client::onConnected()
{
    qDebug() << "# Connected to server.";
    qDebug() << "# Sending " << request.length() << " bytes:";
    qDebug() << QString::fromUtf8(request);

    socket.write(request);
    socket.flush();

    request.clear();
}

void Client::onDisconnected()
{
    qDebug() << "# Disconnected from server.";
}

void Client::onReadyRead()
{
    qDebug() << "# Ready to read response.";

    QByteArray data = socket.readAll();

    qDebug() << "# Received " << data.length() << " bytes:";
    qDebug() << data;

    emit gotResponse(data);

    socket.disconnectFromHost();
    socket.close();
}

void Client::onBytesWritten(qint64 n)
{
    qDebug() << "#" << n << " bytes sent.";
}

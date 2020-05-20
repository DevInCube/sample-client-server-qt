#include <QHostAddress>
#include <QDataStream>

#include "client.h"

Client::Client(QObject *parent)
    : QObject(parent),
      socket(this)
{
    connect(&socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onError(QAbstractSocket::SocketError)));

    connect(&socket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(&socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

    connect(&socket, SIGNAL(bytesWritten(qint64)), this, SLOT(onBytesWritten(qint64)));
    connect(&socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void Client::sendMessage(int port, const QByteArray & data)
{
    qDebug() << "# Connecting to server at port " << port << "...";

    outgoingMessage = data;
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
    qDebug() << "# Sending " << outgoingMessage.length() << " bytes:";
    qDebug() << QString::fromUtf8(outgoingMessage);

    socket.write(outgoingMessage);
    socket.flush();

    outgoingMessage.clear();
}

void Client::onDisconnected()
{
    qDebug() << "# Disconnected from server.";
}

void Client::onReadyRead()
{
    qDebug() << "# New imcoming data available:";

    QByteArray data = socket.readAll();

    qDebug() << "# Received " << data.length() << " bytes:";
    qDebug() << data;

    if (incomingMessage.length() == 0) // first part
        incomingMessage = data;
    else
        incomingMessage.append(data);

    QDataStream stream(&incomingMessage, QIODevice::ReadOnly);
    int32_t message_length = 0;
    stream >> message_length;

    qDebug() << "# Received total data length: " << incomingMessage.length();
    qDebug() << "# Total message length: " << message_length;

    if (message_length == incomingMessage.length())  // condition
    {
        qDebug() << "# Got full request here.";

        emit gotMessage(incomingMessage);

        incomingMessage.clear();

        // close connection
        socket.disconnectFromHost();
        socket.close();
    }
}

void Client::onBytesWritten(qint64 n)
{
    qDebug() << "#" << n << " bytes sent.";
}

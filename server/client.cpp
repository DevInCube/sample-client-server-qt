#include "client.h"
#include <QDataStream>

Client::Client(QTcpSocket * socket, QObject *parent)
    : QObject(parent),
      socket(socket)
{
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onError(QAbstractSocket::SocketError)));

    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(onBytesWritten(qint64)));

    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

void Client::onError(QAbstractSocket::SocketError error)
{
    qDebug() << "# Client error:" << error;

    socket->close();
}

void Client::onReadyRead()
{
    qDebug() << "# New incoming data available:";

    QByteArray data = socket->readAll();

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
    }
}

void Client::sendMessage(const QByteArray & response)
{
    qDebug() << "# Sending message: ";

    socket->write(response);
    socket->flush();
}

void Client::onBytesWritten(qint64 n)
{
    qDebug() << "#" << n << "bytes sent.";

    socket->close();
}

void Client::onDisconnected()
{
    qDebug() << "# Socket disconnected.";

    socket->deleteLater();

    emit disconnected();
}

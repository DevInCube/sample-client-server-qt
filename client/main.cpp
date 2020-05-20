#include <QCoreApplication>
#include <QDataStream>

#include "client.h"

void onResponse(QByteArray data);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client(&a);
    // subscribe to response
    QObject::connect(&client, &Client::gotMessage, &onResponse);
    // create request with length
    int32_t header_length = 4;
    int32_t data_length = 100000;
    QByteArray big_data(data_length, 'A');
    QByteArray header;
    QDataStream stream(&header, QIODevice::WriteOnly);  // QDataStream
    stream << header_length + data_length;
    qDebug() << header;
    qDebug() << header.length();
    big_data.prepend(header);
    qDebug() << big_data.length();
    // send request
    const int SERVER_PORT = 3000;
    client.sendMessage(SERVER_PORT, big_data);

    return a.exec();
}

void onResponse(QByteArray data)
{
    qDebug() << QString::fromUtf8(data);
}

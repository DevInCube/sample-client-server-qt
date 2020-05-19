#include <QCoreApplication>

#include "client.h"

void onResponse(QByteArray data);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client(3000, &a);  // set server port
    // subscribe to response
    QObject::connect(&client, &Client::gotResponse, &onResponse);
    // send request
    client.sendRequest(QString("A request string").toUtf8());

    return a.exec();
}

void onResponse(QByteArray data)
{
    qDebug() << QString::fromUtf8(data);
}

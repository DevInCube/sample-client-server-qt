#include <QCoreApplication>
#include <iostream>
#include "client.h"

using namespace std;

void onResponse(QByteArray data)
{
    qDebug() << QString::fromUtf8(data);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client(3000, &a);
    QObject::connect(&client, &Client::gotResponse, &onResponse);
    client.sendRequest(QString("A request string").toUtf8());

    return a.exec();
}

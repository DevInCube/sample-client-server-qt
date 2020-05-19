#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <iostream>
#include <server.h>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server(&a);

    int PORT = 3000;
    if (!server.start(PORT)) {
        qDebug() << "error listen ";
    } else {
        qDebug() << "started at " << PORT;
    }

    return a.exec();
}

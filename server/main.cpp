#include <QCoreApplication>

#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server(&a);

    const int PORT = 3000;
    if (!server.start(PORT)) {
        qDebug() << "[ERROR] Can't start server at port " << PORT;
    } else {
        qDebug() << "Server started at port " << PORT;
    }

    return a.exec();
}

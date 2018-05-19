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
//    QTcpServer server(&a);
//    const int PORT = 3000;
//    if (!server.listen(QHostAddress::Any, PORT)) {
//        cerr << "cant start" << endl;
//        return 1;
//    }
//    cout << "server started at port " << PORT << endl;
//    while (true) {
//        cout << "waiting for new connections" << endl;
//        if (server.waitForNewConnection(2000)) {
//            QTcpSocket * client = server.nextPendingConnection();
//            cout << "got new connection" << endl;
//            if (client->waitForReadyRead(2000)) {
//                QByteArray data = client->readAll();
//                cout << "Received:" << endl << data.toStdString() << endl;
//                //
//                QString responseStr = "Hello from server!";
//                cout << "Sending: " << endl << responseStr.toStdString() << endl;
//                client->write(responseStr.toUtf8());
//                client->flush();
//                client->waitForBytesWritten(2000);
//                cout << "response sent." << endl;
//            }
//            client->close();
//            cout << "client disconnected" << endl;
//        }
//    }
//    server.close();

    return a.exec();
}

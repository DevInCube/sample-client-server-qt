#include <QCoreApplication>
#include <QTcpSocket>
#include <iostream>
#include <QHostAddress>
#include <client.h>
#include <QAbstractSocket>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client(&a);

//    QTcpSocket client(&a);
//    QHostAddress serverAddress("127.0.0.1");
//    int PORT = 3000;
//    cout << "connecting to server at port " << PORT << endl;
//    client.connectToHost(serverAddress, PORT);
//    client.waitForConnected(2000);
//    if (client.state() != QAbstractSocket::SocketState::ConnectedState) {
//        cerr << "connection error" << endl;
//        return 1;
//    }
//    cout << "connected to server " << endl;
//    //
//    QString requestStr = "Hello from server!";
//    cout << "Sending: " << endl << requestStr.toStdString() << endl;
//    client.write(requestStr.toUtf8());
//    client.flush();
//    client.waitForBytesWritten(2000);
//    cout << "response sent." << endl;
//    //
//    if (!client.waitForReadyRead(2000)) {
//        cerr << "read err " << endl;
//        // @todo
//    }
//    //
//    QByteArray data = client.readAll();
//    cout << "Received:" << endl << data.toStdString() << endl;
//    //
//    client.disconnectFromHost();
//    cout << "disconnected" << endl;

    return a.exec();
}

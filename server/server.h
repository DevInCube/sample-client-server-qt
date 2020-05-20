#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QByteArray>

class Server : public QObject
{
    QTcpServer tcpServer;
    // QByteArray request;

    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    bool start(int port);

signals:

public slots:
    void onNewConnection();
    // void onReadyRead();
    // void onBytesWritten(qint64);
    void onClientDisconnected();

    void onMessageReceived(QByteArray);
};

#endif // SERVER_H

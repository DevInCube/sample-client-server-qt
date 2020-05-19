#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>

#include <QObject>

class Server : public QObject
{
    QTcpServer tcpServer;

    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    bool start(int port);

signals:

public slots:
    void onNewConnection();
    void onReadyRead();
    void onBytesWritten(qint64);
    void onClientDisconnected();
};

#endif // SERVER_H

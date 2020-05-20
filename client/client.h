#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class Client : public QObject
{
    QTcpSocket socket;
    QByteArray request;

    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

    void sendRequest(int, QByteArray);

signals:
    void gotResponse(QByteArray);

public slots:
    void onConnected();
    void onError(QAbstractSocket::SocketError);
    void onReadyRead();
    void onBytesWritten(qint64);
    void onDisconnected();
};

#endif // CLIENT_H

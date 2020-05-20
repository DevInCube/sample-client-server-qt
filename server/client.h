#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>

class Client : public QObject
{
    QTcpSocket * socket;
    QByteArray incomingMessage;

    Q_OBJECT
public:
    explicit Client(QTcpSocket * socket, QObject *parent = nullptr);

    void sendMessage(const QByteArray &);

signals:
    void gotMessage(QByteArray);  // copy
    void disconnected();

public slots:
    void onError(QAbstractSocket::SocketError);
    void onReadyRead();
    void onBytesWritten(qint64);
    void onDisconnected();
};

#endif // CLIENT_H

#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

signals:

public slots:
    void onConnected();
    void onReadyRead();
    void onBytesWritten(qint64);
    void onDisconnected();
};

#endif // CLIENT_H

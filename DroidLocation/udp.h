#ifndef UDP_H
#define UDP_H

#include <QObject>
#include <QUdpSocket>
#include <QDebug>

class UDP : public QObject
{
    Q_OBJECT
public:
    explicit UDP(QObject *parent = nullptr);
    explicit UDP(QObject *parent = nullptr, int myPort = 5000, int senderPort = 6000, QString senderIp = "192.168.100.93");

    void sendMessage(QByteArray message);

signals:
    void messageReceived(QByteArray);

public slots:
    void receiveMessage();

private:
    QUdpSocket* udpClient;

    int _myPort;
    int _senderPort;
    QString _senderIp;
};

#endif // UDP_H

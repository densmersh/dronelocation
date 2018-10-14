#include "udp.h"

UDP::UDP(QObject *parent, int myPort, int senderPort, QString senderIp): QObject(parent)
{
    _myPort = myPort;
    _senderPort = senderPort;
    _senderIp = senderIp;

    udpClient = new QUdpSocket(this);
    udpClient->bind(_myPort);

    connect(udpClient, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
    qDebug()<<"UDP created";

}

void UDP::sendMessage(QByteArray message)
{
    udpClient->writeDatagram(message, QHostAddress::Broadcast,_senderPort);
}

void UDP::receiveMessage()
{
    QByteArray datagram;
    datagram.resize(udpClient->pendingDatagramSize());
    QHostAddress *address = new QHostAddress();
    udpClient->readDatagram(datagram.data(), datagram.size(), address);

    qDebug()<<"Recieved data is: "<<datagram;
    emit messageReceived(datagram);
}


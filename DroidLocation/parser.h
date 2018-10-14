#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QDebug>
#include <udp.h>

#define CHECK_CONNECTION 0x00
#define GPS_CONNECTION 0x01
#define INERTIAL_CONNECTION 0x02

#define CHECK_CONNECTION_RESPONSE 0x02

#define GPS_DIAGNOSTIC 0x00
#define LATITUDE 0x01
#define LONGTITUDE 0x02
#define ALTITUDE 0x03
#define SATELLITE_INFO 0x04

#define INERTIAL_DIAGNOSTIC 0x00
#define ACCEL_HYRO 0x01
#define MAGNETOMETER 0x02
#define ALTIMETER 0x03

class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = nullptr);

signals:


public slots:
    void recievePackageFromDrone(QByteArray dronePackage);

private:
    UDP* udp;

    double parseCoordinate(short sign, double first, double second, double third, double fourth);

};

#endif // PARSER_H

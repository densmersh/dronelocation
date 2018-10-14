#ifndef LOCATION_H
#define LOCATION_H

#include <QObject>
#include "gps.h"
#include "parser.h"

class Location : public QObject
{
    Q_OBJECT
public:
    explicit Location(QObject *parent = nullptr);

    Q_PROPERTY(double droneLatitude READ droneLatitude WRITE setDroneLatitude NOTIFY droneLatitudeChanged)
    Q_PROPERTY(double droneLongtitude READ droneLongtitude WRITE setDroneLongtitude NOTIFY droneLongtitudeChanged)
    Q_PROPERTY(double droneAltitude READ droneAltitude WRITE setDroneAltitude NOTIFY droneAltitudeChanged)
    Q_PROPERTY(double hpLatitude READ hpLatitude WRITE setHpLatitude NOTIFY hpLatitudeChanged)
    Q_PROPERTY(double hpLongtitude READ hpLongtitude WRITE setHpLongtitude NOTIFY hpLongtitudeChanged)
    Q_PROPERTY(double hpAltitude READ hpAltitude WRITE setHpAltitude NOTIFY hpAltitudeChanged)
    Q_PROPERTY(int hpSatellitesInUse READ hpSatellitesInUse WRITE sethpSatellitesInUse NOTIFY hpSatellitesInUseChanged)
    Q_PROPERTY(int distanceToDrone READ distanceToDrone WRITE setDistanceToDrone NOTIFY distanceToDroneChanged)

    double droneLatitude() const;
    double droneLongtitude() const;
    double droneAltitude() const;
    double hpLatitude() const;
    double hpLongtitude() const;
    double hpAltitude() const;

    int hpSatellitesInUse() const;

    int distanceToDrone() const;

signals:
    void coordinatesHPUpdated();
    void sendSatellitesInUseCount(int count);
    void sendDistanceToDrone(int distance);

    void droneLatitudeChanged(double droneLatitude);
    void droneLongtitudeChanged(double droneLongtitude);
    void droneAltitudeChanged(double droneAltitude);
    void hpLatitudeChanged(double hpLatitude);
    void hpLongtitudeChanged(double hpLongtitude);
    void hpAltitudeChanged(double hpAltitude);

    void hpSatellitesInUseChanged(int hpSatellitesInUse);
    void distanceToDroneChanged(int distanceToDrone);
    void initializedGPSPhone();

public slots:
    void receiveSatellitesInUseCount(int count);
    void receiveDistanceToDrone(int distance);

    void updateHPCoordinates(double latitude, double longtitude, double altitude);

    void setDroneLatitude(double droneLatitude);
    void setDroneLongtitude(double droneLongtitude);
    void setDroneAltitude(double droneAltitude);
    void setHpLatitude(double hpLatitude);
    void setHpLongtitude(double hpLongtitude);
    void setHpAltitude(double hpAltitude);
    void sethpSatellitesInUse(int hpSatellitesInUse);
    void setDistanceToDrone(int distanceToDrone);

private:

    double m_droneLatitude;
    double m_droneLongtitude;
    double m_droneAltitude;
    double m_hpLatitude;
    double m_hpLongtitude;
    double m_hpAltitude;

    GPS* gps;
    QTimer timer;
    Parser* parser;
    int m_hpSatellitesInUse;
    int m_distanceToDrone;

    bool _initializegGPSPhone;
};

#endif // LOCATION_H

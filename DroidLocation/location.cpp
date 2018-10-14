#include "location.h"

Location::Location(QObject *parent) : QObject(parent)
{
    gps = new GPS;
    parser = new Parser;
    setDroneLatitude(53.87842);
    setDroneLongtitude(27.53489);
    setDroneAltitude(400) ;
    setHpLatitude(52.87842);
    setHpLongtitude(23.53489);
    setHpAltitude(200);

    _initializegGPSPhone = false;

    connect(gps, SIGNAL(sendToMap(double,double,double)),this, SLOT(updateHPCoordinates(double,double,double)));
    connect(gps, SIGNAL(sendSatelliteInUseCount(int)),this,SLOT(sethpSatellitesInUse(int)));


}

double Location::droneLatitude() const
{
    return m_droneLatitude;
}

double Location::droneLongtitude() const
{
    return m_droneLongtitude;
}

double Location::droneAltitude() const
{
    return m_droneAltitude;
}

double Location::hpLatitude() const
{
    return m_hpLatitude;
}

double Location::hpLongtitude() const
{
    return m_hpLongtitude;
}

double Location::hpAltitude() const
{
    return m_hpAltitude;
}

int Location::hpSatellitesInUse() const
{
    return m_hpSatellitesInUse;
}

int Location::distanceToDrone() const
{
    return m_distanceToDrone;
}

void Location::receiveSatellitesInUseCount(int count)
{
    emit sendSatellitesInUseCount(count);
}

void Location::receiveDistanceToDrone(int distance)
{
    emit sendDistanceToDrone(distance);
}

void Location::updateHPCoordinates(double latitude, double longtitude, double altitude)
{
    setHpLatitude(latitude);
    setHpLongtitude(longtitude);
    setHpAltitude(altitude);
    emit coordinatesHPUpdated();
    if (!_initializegGPSPhone)
    {
        emit initializedGPSPhone();
        _initializegGPSPhone = true;
    }

    setDistanceToDrone(gps->distanceToDrone(hpLatitude(), hpLongtitude(), droneLatitude(), droneLongtitude()));
}

void Location::setDroneLatitude(double droneLatitude)
{
    if (qFuzzyCompare(m_droneLatitude, droneLatitude))
        return;

    m_droneLatitude = droneLatitude;
    emit droneLatitudeChanged(m_droneLatitude);
}

void Location::setDroneLongtitude(double droneLongtitude)
{
    if (qFuzzyCompare(m_droneLongtitude, droneLongtitude))
        return;

    m_droneLongtitude = droneLongtitude;
    emit droneLongtitudeChanged(m_droneLongtitude);
}

void Location::setDroneAltitude(double droneAltitude)
{
    if (qFuzzyCompare(m_droneAltitude, droneAltitude))
        return;

    m_droneAltitude = droneAltitude;
    emit droneAltitudeChanged(m_droneAltitude);
}

void Location::setHpLatitude(double hpLatitude)
{
    if (qFuzzyCompare(m_hpLatitude, hpLatitude))
        return;

    m_hpLatitude = hpLatitude;
    emit hpLatitudeChanged(m_hpLatitude);
}

void Location::setHpLongtitude(double hpLongtitude)
{

    if (qFuzzyCompare(m_hpLongtitude, hpLongtitude))
        return;

    m_hpLongtitude = hpLongtitude;
    emit hpLongtitudeChanged(m_hpLongtitude);
}

void Location::setHpAltitude(double hpAltitude)
{
    if (qFuzzyCompare(m_hpAltitude, hpAltitude))
        return;

    m_hpAltitude = hpAltitude;
    emit hpAltitudeChanged(m_hpAltitude);
}

void Location::sethpSatellitesInUse(int hpSatellitesInUse)
{
    if (m_hpSatellitesInUse == hpSatellitesInUse)
        return;

    m_hpSatellitesInUse = hpSatellitesInUse;
    emit hpSatellitesInUseChanged(m_hpSatellitesInUse);
}

void Location::setDistanceToDrone(int distanceToDrone)
{
    if (m_distanceToDrone == distanceToDrone)
        return;

    m_distanceToDrone = distanceToDrone;
    emit distanceToDroneChanged(m_distanceToDrone);
}

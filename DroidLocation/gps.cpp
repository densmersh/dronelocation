#include "gps.h"

GPS::GPS(QObject *parent) : QObject(parent)
{
    _isValid = false;

    QGeoPositionInfoSource *source = QGeoPositionInfoSource::createDefaultSource(0);
    QGeoSatelliteInfoSource* satellite = QGeoSatelliteInfoSource::createDefaultSource(0);
    satellite->setUpdateInterval(2000);
    source->setUpdateInterval(200);
    source->setPreferredPositioningMethods(QGeoPositionInfoSource::SatellitePositioningMethods);
    if (source)
    {
       connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)),
               this, SLOT(positionUpdated(QGeoPositionInfo)));
       source->startUpdates();
    }

    if(satellite){
        connect( satellite,SIGNAL( satellitesInUseUpdated(const QList<QGeoSatelliteInfo>& ) ),
        this,SLOT( sateliteInseUpdated(const QList<QGeoSatelliteInfo>& ) ) );
//        connect(satellite,SIGNAL( satellitesInViewUpdated(QList<QGeoSatelliteInfo>)),
//        this,SLOT(sateliteInViewUpdated(const QList<QGeoSatelliteInfo>)));
        satellite->startUpdates();
    }
}

int GPS::distanceToDrone(double hpLatitude, double hpLongtitude,double dpLatitude, double dpLongtitude)
{
    QGeoCoordinate coordinatesHome(hpLatitude, hpLongtitude);
    if(coordinatesHome.isValid())
    {
        QGeoCoordinate coordinatesDrone(dpLatitude ,dpLongtitude);
        if(coordinatesDrone.isValid())
        {
            int distance = coordinatesHome.distanceTo(coordinatesDrone);
            if(distance)
                return distance;
        }
    }
    return 0;
}

bool GPS::coordinatesIsValid()
{
    return _isValid;
}


void GPS::positionUpdated(const QGeoPositionInfo &info)
{
       if(info.coordinate().isValid())
       {
//            qDebug() << "Position updated:" << info.coordinate().latitude()<<info.coordinate().longitude()<<info.coordinate().altitude();
            emit sendToMap(info.coordinate().latitude(), info.coordinate().longitude(), info.coordinate().altitude());
            _isValid = true;
       }
}

void GPS::sateliteInViewUpdated(const QList<QGeoSatelliteInfo> &satInView)
{

}

void GPS::sateliteInseUpdated(const QList<QGeoSatelliteInfo> &satInUse)
{
    emit sendSatelliteInUseCount(satInUse.count());
//    qDebug()<<"SAT COUNT"<<satInUse.count();
//    if(satInUse.count())
//    for(int i = 0; i < satInUse.count();i++)
//    {
//        qDebug()<< "SIGNAL LEVEL: "<<satInUse.at(i).signalStrength()<<satInUse.at(i).satelliteSystem();
//    }
}


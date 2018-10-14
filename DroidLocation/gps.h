#ifndef GPS_H
#define GPS_H

#include <QObject>
#include <QGeoCoordinate>
#include <QTimer>
#include <QDebug>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QGeoSatelliteInfoSource>
#include <QGeoCoordinate>


class GPS : public QObject
{
    Q_OBJECT
public:
    explicit GPS(QObject *parent = nullptr);

    int distanceToDrone(double hpLatitude, double hpLongtitude, double dpLatitude, double dpLongtitude);
    bool coordinatesIsValid();

signals:
    void sendToMap(double, double, double);
    void sendSatelliteInUseCount(int);

public slots:

private slots:
    void positionUpdated(const QGeoPositionInfo &info);
    void sateliteInViewUpdated(const QList<QGeoSatelliteInfo> &satInView);
    void sateliteInseUpdated(const QList<QGeoSatelliteInfo> &satInUse);


private:
    bool _isValid;
};

#endif // GPS_H

#include "parser.h"

Parser::Parser(QObject *parent) : QObject(parent)
{
    udp = new UDP(NULL, 5000, 6000, "192.168.1.3");
    connect(udp, SIGNAL(messageReceived(QByteArray)),this, SLOT(recievePackageFromDrone(QByteArray)));
}

void Parser::recievePackageFromDrone(QByteArray dronePackage)
{
    int command = dronePackage.at(1);
    int subcommand = dronePackage.at(2);

    if(command == CHECK_CONNECTION)
    {
        if(subcommand == CHECK_CONNECTION_RESPONSE)
        {
            qDebug()<<"CHECK_CONNECTION_RESPONSE";
        }
        else
        {
            qDebug()<<"Subcommand not founded";
            return;
        }
    }
    else if(command == GPS_CONNECTION)
    {
        if(subcommand == GPS_DIAGNOSTIC)
        {
            qDebug()<<"GPS_DIAGNOSTIC";
        }
        else if(subcommand == LATITUDE)
        {
            parseCoordinate(dronePackage.at(3), dronePackage.at(4),dronePackage.at(5),dronePackage.at(6),dronePackage.at(7));
        }
        else if(subcommand == LONGTITUDE)
        {
            parseCoordinate(dronePackage.at(3), dronePackage.at(4),dronePackage.at(5),dronePackage.at(6),dronePackage.at(7));
        }
        else if(subcommand == ALTITUDE)
        {
           (dronePackage.at(3) << 8) + dronePackage.at(4);
        }
        else if(subcommand == SATELLITE_INFO)
        {
            qDebug()<<"SATELLITE_INFO";
        }
        else
        {
            qDebug()<<"Subcommand not founded";
            return;
        }
    }
    else if(command == INERTIAL_CONNECTION)
    {
        if(subcommand == INERTIAL_DIAGNOSTIC)
        {
            qDebug()<<"INERTIAL_DIAGNOSTIC";
        }
        else if(subcommand == ACCEL_HYRO)
        {
            qDebug()<<"ACCEL_HYRO";
        }
        else if(subcommand == MAGNETOMETER)
        {
            qDebug()<<"MAGNETOMETER";
        }
        else if(subcommand == ALTIMETER)
        {
            qDebug()<<"ALTIMETER";
        }
        else
        {
            qDebug()<<"Subcommand not founded";
            return;
        }
    }
    else
    {
        qDebug()<<"Command not founded";
        return;
    }
}

double Parser::parseCoordinate(short int sign, double first, double second, double third, double fourth)
{
    sign ? sign : sign -= 1;
    double degree = sign * (first + second/100 + third/10000 + fourth/1000000);
    //qDebug()<<" BIN IS"<<bin;
    return degree;

}

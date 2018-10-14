#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include "location.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterType<Location>("Location",1,0,"Location");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

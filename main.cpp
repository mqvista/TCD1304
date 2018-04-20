#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QMetaObject>

#include "services.h"
#include "chartsource.h"
#include "controlpanelmodule.h"
#include "ployfit.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    // Qt Charts uses Qt Graphics View Framework for drawing, therefore QApplication must be used.
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    ChartSource chartSource;
    engine.rootContext()->setContextProperty("ChartSource", &chartSource);
    Services services;    
    QObject::connect(Worker::Instance(), &Worker::getNewData, &chartSource, &ChartSource::processFromWorker);
    ControlPanelModule controlPanelModule;
    engine.rootContext()->setContextProperty("ControlPanelModule", &controlPanelModule);
    QObject::connect(Worker::Instance(), &Worker::sendMeasureLength, &controlPanelModule, &ControlPanelModule::setMeasureLength);
    QObject::connect(Worker::Instance(), &Worker::sendPolyValue, &controlPanelModule, &ControlPanelModule::setPolyValue);

    //
    //PloyFit ployFit;
    //ployFit.test();
    //

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}

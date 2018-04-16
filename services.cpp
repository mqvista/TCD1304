#include "services.h"

Services::Services(QObject *parent) : QObject(parent)
{
    Worker::Instance()->moveToThread(&workerThread);
    workerThread.start();
    QMetaObject::invokeMethod(Worker::Instance(), "sendData", Qt::QueuedConnection, Q_ARG(QString, "#CCDInt:001%"));
    //QMetaObject::invokeMethod(Worker::Instance(), "sendData", Qt::QueuedConnection, Q_ARG(QString, "#Text:0%"));


    QMetaObject::invokeMethod(Worker::Instance(), "startAutoAcq", Qt::QueuedConnection, Q_ARG(quint16, 100));
}

Services::~Services()
{
    QMetaObject::invokeMethod(Worker::Instance(), "stopAutoAcq", Qt::QueuedConnection);
    workerThread.quit();
    workerThread.wait();
}

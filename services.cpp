#include "services.h"

Services::Services(QObject *parent) : QObject(parent)
{
    Worker::Instance()->moveToThread(&workerThread);
    workerThread.start();
    //QMetaObject::invokeMethod(Worker::Instance(), "runOnce", Qt::QueuedConnection);
    //QMetaObject::invokeMethod(Worker::Instance(), "sendData", Qt::QueuedConnection, Q_ARG(QString, "#CCDInt:001%"));

    QMetaObject::invokeMethod(Worker::Instance(), "startAutoAcq", Qt::QueuedConnection, Q_ARG(quint16, 1000));
//    QMetaObject::invokeMethod(Worker::Instance(), "runOnce", Qt::QueuedConnection);
}

Services::~Services()
{
    workerThread.quit();
    workerThread.wait();
}

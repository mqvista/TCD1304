#include "services.h"

Services::Services(QObject *parent) : QObject(parent)
{
    Worker::Instance()->moveToThread(&workerThread);
    workerThread.start();
    m_tcpServer.moveToThread(&tcpThread);
    tcpThread.start();

    QMetaObject::invokeMethod(Worker::Instance(), "sendData", Qt::QueuedConnection, Q_ARG(QString, "#CCDInt:001%"));


    QMetaObject::invokeMethod(Worker::Instance(), "startAutoAcq", Qt::QueuedConnection, Q_ARG(quint16, 100));

    QObject::connect(Worker::Instance(), &Worker::SendDataToTCPClient, &m_tcpServer, &TCPServer::sendNewData);
}

Services::~Services()
{
    QMetaObject::invokeMethod(Worker::Instance(), "stopAutoAcq", Qt::QueuedConnection);
    tcpThread.quit();
    tcpThread.wait();
    workerThread.quit();
    workerThread.wait();
}

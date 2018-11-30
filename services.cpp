#include "services.h"

Services::Services(QObject *parent) : QObject(parent)
{
    Worker::Instance()->moveToThread(&workerThread);
    workerThread.start();
    m_tcpServer.moveToThread(&tcpThread);
    tcpThread.start();

    QObject::connect(Worker::Instance(), &Worker::SendDataToTCPClient, &m_tcpServer, &TCPServer::sendNewData);
}

Services::~Services()
{
    tcpThread.quit();
    tcpThread.wait();
    workerThread.quit();
    workerThread.wait();
}

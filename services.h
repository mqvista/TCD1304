#ifndef SERVICES_H
#define SERVICES_H

#include <QObject>
#include <QThread>
#include "worker.h"
#include <QMetaObject>
#include "tcpserver.h"

class Services : public QObject
{
    Q_OBJECT
public:
    explicit Services(QObject *parent = nullptr);
    ~Services();

signals:

public slots:

private:
    QThread workerThread;
    TCPServer m_tcpServer;
    QThread tcpThread;
};

#endif // SERVICES_H

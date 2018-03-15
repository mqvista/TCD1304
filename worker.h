#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include "ftdi/ftdicontrol.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    static Worker *Instance();
    Q_INVOKABLE bool runOnce();
    Q_INVOKABLE void startAutoAcq(quint16 time);
    Q_INVOKABLE void stopAutoAcq();
    Q_INVOKABLE bool sendData(QString strData);
    bool runAlways();


signals:

private:
    explicit Worker(QObject *parent = nullptr);
    QTimer *m_acqTimer;

};

#endif // WORKER_H

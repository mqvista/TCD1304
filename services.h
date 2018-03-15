#ifndef SERVICES_H
#define SERVICES_H

#include <QObject>
#include <QThread>
#include "worker.h"
#include <QMetaObject>
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
};

#endif // SERVICES_H

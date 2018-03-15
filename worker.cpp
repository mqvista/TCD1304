#include "worker.h"

Worker::Worker(QObject *parent) : QObject(parent)
{
}

Worker *Worker::Instance()
{
    static QMutex mutex;
        static QScopedPointer<Worker> instance;
        if (Q_UNLIKELY(!instance)) {
            mutex.lock();
            if (!instance) {
                instance.reset(new Worker);
            }
            mutex.unlock();
        }
        return instance.data();
}

bool Worker::runOnce()
{
    FtdiControl::Instance()->sendData("#?data%");
    quint16 dts[3648];
    if (FtdiControl::Instance()->getSenserData(dts))
    {
        qDebug() << dts;
        return true;
    }
    else
    {
        return false;
    }
}

bool Worker::runAlways()
{
    FtdiControl::Instance()->sendData("#?data%");
    quint16 dts[3648];
    if (FtdiControl::Instance()->getSenserData(dts))
    {
        qDebug() << "sometings" <<dts;
        return true;
    }
}

//启动自动获取ccd数据
//使用定时器刷新
//参数为ms
void Worker::startAutoAcq(quint16 time)
{
    m_acqTimer = new QTimer(this);
    connect(m_acqTimer, &QTimer::timeout, this, &Worker::runAlways);
    m_acqTimer->start(time);
}

void Worker::stopAutoAcq()
{
    m_acqTimer->stop();
}

bool Worker::sendData(QString strData)
{
    if (FtdiControl::Instance()->sendData(strData))
    {
        return true;
    }
    return false;
}




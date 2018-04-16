#include "worker.h"

Worker::Worker(QObject *parent) : QObject(parent), filter(10)
{
    m_ThresholdValue = 25000;
    m_NeedToSetParams = false;
}

quint16 Worker::getThresholdValue() const
{
    return m_ThresholdValue;
}

void Worker::setThresholdValue(const quint16 &value)
{
    m_ThresholdValue = value;
}

void Worker::setIntergral(quint8 value)
{
    m_IntergralValue = value;
    m_NeedToSetParams  = true;
}

QString Worker::converyIntergralData()
{
    QString intValueStr;
    if (m_IntergralValue > 0 && m_IntergralValue < 10)
    {
        intValueStr = QString::number(m_IntergralValue, 10);
        intValueStr = "#CCDInt:00" + intValueStr + "%";
    }
    else if (m_IntergralValue >= 10 && m_IntergralValue < 100)
    {
        intValueStr = QString::number(m_IntergralValue, 10);
        intValueStr = "#CCDInt:0" + intValueStr + "%";
    }
    else if (m_IntergralValue == 100)
    {
        intValueStr = QString::number(m_IntergralValue, 10);
        intValueStr = "#CCDInt:100%";
    }
    return intValueStr;
}

//循环数组，并从左右两边向内靠拢
//用于计算触发的CCD长度
void Worker::calcuLength()
{
    quint16 startPoint = 0 , endPoint = 0;
    bool startFlag = true, endFlag = true;
    for (quint16 i=0; i<3648; i++)
    {
        if ((m_SenserThresholdData[i] > m_SenserThresholdData[i+1]) && startFlag)
        {
            startPoint = i+1;
            startFlag = false;
        }
        if ((m_SenserThresholdData[3647-i] > m_SenserThresholdData[3646 -i]) && endFlag)
        {
            endPoint = 3646 - i;
            endFlag = false;
        }
        if( startFlag == false && endFlag == false)
            break;
    }
    m_MeasureLength = endPoint-startPoint;
}

//填充首尾激光无法照射的区域， 参数一 长度， 参数二 数值（建议48000）
void Worker::fillHeadTail(quint16 length, quint16 value)
{
    for(quint16 i=0; i<length; i++)
    {
        m_SenserData[i] = value;
        m_SenserData[3647-i] = value;
    }
}

void Worker::getLeftRight(quint16 minCutValue, quint16 maxCutValue, quint16 *leftOffset, quint16 *leftLength, quint16 *rightOffset, quint16 *rightLength)
{
    bool startFlagA = true, startFlagB = true, stopFlagA = true, stopFlagB = true;
    quint16 tmpBvalue;
    for (quint16 i=0; i<1824; i++)
    {
        if((m_SenserData[i] <= maxCutValue) && startFlagA)
        {
            *leftOffset = i;
            startFlagA = false;
        }
        if((m_SenserData[i] <= minCutValue) && stopFlagA)
        {
            *leftLength = i - *leftOffset;
            stopFlagA = false;
        }
        if((m_SenserData[3647-i] <= maxCutValue) && startFlagB)
        {
            //从尾到头数， 先取得尾部的maxValue；
            tmpBvalue = 3647-i;
            startFlagB = false;
        }
        if((m_SenserData[3747-i] <= minCutValue) && stopFlagB)
        {
            *rightOffset = 3647-i;
            *rightLength = tmpBvalue - *rightOffset;
            stopFlagB = false;
        }
        if(startFlagA == false && startFlagB == false && stopFlagA == false && stopFlagB == false)
        {
            break;
        }
    }
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

Worker::~Worker()
{
    m_acqTimer->stop();
}

bool Worker::ftdiInit()
{
    FtdiControl::Instance()->init();
    return true;
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

//循环采集，和runOnce一样其实
bool Worker::runAlways()
{
    //先看看有没有需要设置的参数在任务队列里面
    if (m_NeedToSetParams)
    {
        FtdiControl::Instance()->sendData(converyIntergralData());
    }

    FtdiControl::Instance()->sendData("#?data%");
    //判断数据是否采集回来
    if (FtdiControl::Instance()->getSenserData(m_SenserData))
    {
        //填充CCD 激光照射不到的数据
        fillHeadTail(600, 48000);
        //先做二值化
        thresholding(m_ThresholdValue, 10000, 20000);
        //取截距
        calcuLength();
        //取出来的数值做滤波
        m_MeasureLength = filter.get(m_MeasureLength);

        //测试用拟合

        quint16 leftOffset, leftLength, rightOffset, rightLength;
        getLeftRight(12500, 40000, &leftOffset, &leftLength, &rightOffset, &rightLength );
        qDebug()<<"leftOffset:" << leftOffset;
        qDebug()<<"leftLength:" << leftLength;
        qDebug()<<"rightOffset:" << rightOffset;
        qDebug()<<"rightLength:" << rightLength;

        //ployFit.calc(m_SenserData, 3648, 5);
        //
        emit getNewData(m_SenserData, m_SenserThresholdData, 3648);
        emit sendMeasureLength(m_MeasureLength);
        return true;
    }
    return false;
}

//二值化处理，threshold为二值化的阈值，min和max是二值化的高和低的数值，其实没啥大用
void Worker::thresholding(quint16 threshold, quint16 min, quint16 max)
{
    for (quint16 i=0; i<3648; i++)
    {
        if(m_SenserData[i] >= threshold)
        {
            m_SenserThresholdData[i] = max;
        }
        else
        {
            m_SenserThresholdData[i] = min;
        }
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

void Worker::saveRawData(QString dataUrl)
{
    saveFile.saveCurrentData(m_SenserData, 3648 ,dataUrl);
}




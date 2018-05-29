#include "worker.h"

Worker::Worker(QObject *parent) : QObject(parent), uWindowFilter(20), lengthFilterWithoutPloy(20)
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

//填充首尾激光无法照射的区域， 参数一 长度， 参数二 数值（建议48000）
void Worker::fillHeadTail(quint16 length, quint16 value)
{
    for(quint16 i=0; i<length; i++)
    {
        m_OriginalSenserData[i] = value;
        m_OriginalSenserData[3647-i] = value;
    }
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


// 获取左右两边的数据，比较陡的左右两个边沿
// 为了后面做拟合使用，取值一个范围
// 参数一 范围的最小值
// 参数二 范围的最大值
// 参数三 指针参数，为了把数据丢出来
void Worker::getLeftRight(quint16* senserData, quint16 minCutValue, quint16 maxCutValue, quint16 *leftOffset, quint16 *leftLength, quint16 *rightOffset, quint16 *rightLength)
{
    bool startFlagA = true, startFlagB = true, stopFlagA = true, stopFlagB = true;
    quint16 tmpBvalue;
    for (quint16 i=0; i<3648; i++)
    {
        if((senserData[i] <= maxCutValue) && startFlagA)
        {
            *leftOffset = i;
            startFlagA = false;
        }
        if((senserData[i] <= minCutValue) && stopFlagA)
        {
            *leftLength = i - *leftOffset;
            stopFlagA = false;
        }
        if((senserData[3647-i] <= maxCutValue) && startFlagB)
        {
            //从尾到头数， 先取得尾部的maxValue；
            tmpBvalue = 3647-i;
            startFlagB = false;
        }
        if((senserData[3647-i] <= minCutValue) && stopFlagB)
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
    if (*leftLength >= 50 || *rightLength >=50)
    {
        *leftOffset = 0;
        *leftLength = 0;
        *rightOffset = 0;
        *rightLength = 0;
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
    if (FtdiControl::Instance()->getSenserData(m_OriginalSenserData))
    {
        //填充CCD 激光照射不到的数据
        fillHeadTail(600, 48000);
        //像素滑动平均
        filter.get(m_OriginalSenserData, m_FilterSenserData);
        //先做二值化
        thresholding(m_ThresholdValue, 10000, 20000);
        //取截距
        calcuLength();
        //取出来的数值做滤波（直接取截距的测量）
        m_MeasureLength = lengthFilterWithoutPloy.Get(m_MeasureLength);




        ///////////
        //测试用拟合
        quint16 leftOffset, leftLength, rightOffset, rightLength;
        //获取左右两边的数据
        getLeftRight(m_FilterSenserData, 20000, 40000, &leftOffset, &leftLength, &rightOffset, &rightLength);

        qDebug()<<"①leftOffset"<<leftOffset;
        qDebug()<<"②leftLength"<<leftLength;
        qDebug()<<"③rightOffset"<<rightOffset;
        qDebug()<<"④rightLength"<<rightLength;

        // 计算出X的数据
        quint16 dataAX[leftLength];
        quint16 dataBX[rightLength];
        for(quint16 i=0; i<leftLength; i++)
        {
            dataAX[i] = leftOffset+i+1;
        }
        for(quint16 i=0; i<rightLength; i++)
        {
            dataBX[i] = rightOffset+i+1;
        }
        // 二乘法多项式拟合（2项）
        // 申请两个数组，存放拟合结果数据
        double tmpLeftValue[3], tmpRightValue[3];
        double calcLeft=0, calcRight=0;
        double calcPolyLength=0;
        // 判断是否是垃圾数据
        // 是的话就不进行拟合
        if(leftLength != 0 && rightLength != 0)
        {
            //执行拟合
            ployFit.calc(m_FilterSenserData+leftOffset, dataAX, leftLength, 3, tmpLeftValue);
            ployFit.calc(m_FilterSenserData+rightOffset, dataBX, rightLength, 3, tmpRightValue);

            //拟合好后把阈值带入求解;
            calcLeft =  ployFit.slove(tmpLeftValue[2], tmpLeftValue[1], tmpLeftValue[0], m_ThresholdValue);
            calcRight = ployFit.slove(tmpRightValue[2], tmpRightValue[1], tmpRightValue[0], m_ThresholdValue);
            //qDebug() << "CalcLeft" <<calcLeft;
            //qDebug() << "CalcRight" <<calcRight;
        }

        // 因为拟合的是左右两个边，所以需要相减求出大小
        calcPolyLength = calcRight-calcLeft;
        // 窗口滤波
        calcPolyLength = uWindowFilter.Get(calcPolyLength);

        // 丢给界面处理过后的数据
        emit sendPolyValue(QString::number(calcPolyLength, 'f', 4));
        emit getNewData(m_FilterSenserData, m_SenserThresholdData, 3648);
        emit sendMeasureLength(m_MeasureLength);
        return true;
    }
    return false;
}

//二值化处理，threshold为二值化的阈值，min和max是二值化的高和低的数值，其实没啥大用，就是显示给界面用
void Worker::thresholding(quint16 threshold, quint16 min, quint16 max)
{
    for (quint16 i=0; i<3648; i++)
    {
        if(m_FilterSenserData[i] >= threshold)
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
    //saveFile.saveCurrentData(m_FilterSenserData, 3648 ,dataUrl);
    saveFile.saveAllData(m_OriginalSenserData, m_FilterSenserData, 3648, dataUrl);
}




#include "ftdicontrol.h"

FtdiControl* FtdiControl::Instance()
{
    static QMutex mutex;
    static QScopedPointer<FtdiControl> instance;
    if (Q_UNLIKELY(!instance)) {
        mutex.lock();
        if (!instance) {
            instance.reset(new FtdiControl);
        }
        mutex.unlock();
    }
    return instance.data();
}

FtdiControl::FtdiControl(QObject* parent)
    : QObject(parent)
{
}

void FtdiControl::printDevicesInfo()
{
    m_ftStatus = FT_CreateDeviceInfoList(&m_numDevs);
    if (m_ftStatus == FT_OK) {
        if (m_numDevs > 0) {
            m_devInfo = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE) * m_numDevs);
            m_ftStatus = FT_GetDeviceInfoList(m_devInfo, &m_numDevs);
            if (m_ftStatus == FT_OK) {
                for (quint32 i = 0; i < m_numDevs; i++) {
                    qDebug() << "numdevs->" << i;
                    qDebug() << "Flags->" << m_devInfo[i].Flags;
                    qDebug() << "SerialNumber->" << m_devInfo[i].SerialNumber;
                    qDebug() << "Description->" << m_devInfo[i].Description;
                }
            }
        } else {
            qDebug() << "No devices found";
        }
    } else {
        qDebug() << "Driver error";
    }
}

bool FtdiControl::getSenserData(quint16 *senserData)
{
    if (! m_isOpened)
    {
        return false;
    }

    bool loopFlag = true;
    quint16 currentPoint = 0;
    QDateTime startTime;
    QDateTime stopTime;

    startTime = QDateTime::currentDateTime();

    FT_SetTimeouts(m_ftHandle,100,0);
    while (loopFlag)
    {
        m_ftStatus = FT_Read(m_ftHandle, (quint8*)(m_RxBuffer+currentPoint), 128, &m_Bytereceived);
        if (m_ftStatus != FT_OK)
        {
            return false;
        }
        else if (m_Bytereceived !=128)
        {
            //error_loop++;
            FT_Purge(m_ftHandle, FT_PURGE_TX | FT_PURGE_RX);
            qDebug() << "max loop times error";
            return false;
        }
        else
        {

            currentPoint += m_Bytereceived;
        }
        if (currentPoint >= 7296)
        {
            loopFlag = false;
        }
    }

    for(quint16 i=0; i<3648; i++)
    {
        quint16 tmpData;
        tmpData = (m_RxBuffer[i*2] << 8) | m_RxBuffer[i*2+1];
        senserData[i] = tmpData;
    }

    stopTime = QDateTime::currentDateTime();
    qDebug() << "timers:" << startTime.msecsTo(stopTime);
    return true;
}

bool FtdiControl::sendData(QString strData)
{
    if (! m_isOpened)
    {
        return false;
    }
    memset(m_TxBuffer, 0, sizeof(m_TxBuffer));
    for (quint16 i = 0; i < strData.size(); i++) {
        m_TxBuffer[i] = strData.toStdString()[i];
    }
    m_ftStatus = FT_Write(m_ftHandle, m_TxBuffer, strData.size(), &m_ByteWritten);
    if (m_ftStatus == FT_OK) {
        return true;
    }
    return false;
}

bool FtdiControl::init()
{
    m_ftStatus = FT_ResetDevice(m_ftHandle);
    if (m_ftStatus != FT_OK) {
        qDebug()<< "FT_ResetDevice error";
        return false;
    }
    m_ftStatus = FT_SetBaudRate(m_ftHandle, 1400000);
    if (m_ftStatus != FT_OK) {
        qDebug()<< "ftdi init error 3";
        return false;
    }
    m_ftStatus = FT_SetDataCharacteristics(m_ftHandle, FT_BITS_8 + FT_BITS_7, FT_STOP_BITS_1, FT_PARITY_NONE);
    if (m_ftStatus != FT_OK) {
        qDebug()<< "ftdi init error 4";
        return false;
    }
    m_ftStatus = FT_SetFlowControl(m_ftHandle, FT_FLOW_NONE, 0, 0);
    if (m_ftStatus != FT_OK) {
        qDebug()<< "ftdi init error 5";
        return false;
    }
    m_ftStatus = FT_SetTimeouts(m_ftHandle, FT_DEFAULT_RX_TIMEOUT, FT_DEFAULT_TX_TIMEOUT);
    if (m_ftStatus != FT_OK) {
        qDebug()<< "ftdi init error 7";
        return false;
    }
    m_ftStatus = FT_Purge(m_ftHandle, FT_PURGE_TX | FT_PURGE_RX);
    if (m_ftStatus != FT_OK) {
        qDebug()<< "ftdi init error 8";
        return false;
    }
    qDebug()<< "ftdi init successful";
    return true;
}

bool FtdiControl::openPort(int deviceNum)
{
    m_isOpened = false;
    m_ftStatus = FT_Open(deviceNum, &m_ftHandle);
    if (m_ftStatus != FT_OK)
    {
        qDebug()<< m_ftStatus;
        qDebug() << "openfailed";
        return false;
    }
    else
    {
        m_isOpened = true;
        emit deviceOpenStatusChanged(true);
        return true;
    }
}

bool FtdiControl::colsePort()
{
    m_isOpened = false;
    emit deviceOpenStatusChanged(false);
    FT_Close(m_ftHandle);
    return true;
}

bool FtdiControl::getOpenStatus()
{
    return m_isOpened;
}

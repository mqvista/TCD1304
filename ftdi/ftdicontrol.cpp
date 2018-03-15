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
    bool loopFlag = true;
    quint16 currentPoint = 0;
    quint8 error_loop = 0;

    qDebug() << "Start:" << QTime::currentTime();
    m_ftStatus = FT_Open(0, &m_ftHandle);
    if (m_ftStatus != FT_OK) {
        return false;
    }
//    FT_SetTimeouts(m_ftHandle, 100, 0);
    while (loopFlag)
    {
//        FT_GetStatus(m_ftHandle, &m_RxBytes, &m_TxBytes, &m_Event);
//        if (m_RxBytes > 0)
//        {
//            quint8 tmp_buf[7296];
//            m_ftStatus = FT_Read(m_ftHandle, tmp_buf, m_RxBytes, &m_Bytereceived);
//            if (m_ftStatus == FT_OK)
//            {
//                memcpy(&m_RxBuffer[currentPoint], tmp_buf, m_RxBytes);
//                currentPoint += m_RxBytes;
//            }
//        }
        quint8 tmp_buf[256];
        m_ftStatus = FT_Read(m_ftHandle, tmp_buf, 128, &m_Bytereceived);
        if (m_ftStatus == FT_OK)
        {
            if (m_Bytereceived >0)
            {
                qDebug()<< m_Bytereceived;
                memcpy(&m_RxBuffer[currentPoint], tmp_buf, m_Bytereceived);
                currentPoint += m_Bytereceived;
            }
            else
            {
                error_loop++;
            }

        }
        else
        {
            qDebug() << "Time out";
            error_loop++;
        }

        if (error_loop >= 10)
        {
            FT_Close(m_ftHandle);
            qDebug() << "error";
            return false;
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

    FT_Close(m_ftHandle);
    qDebug() << "Stop:" << QTime::currentTime();
    return true;
}

bool FtdiControl::sendData(QString strData)
{
    memset(m_TxBuffer, 0, sizeof(m_TxBuffer));
    for (quint16 i = 0; i < strData.size(); i++) {
        m_TxBuffer[i] = strData.toStdString()[i];
    }
    m_ftStatus = FT_Open(0, &m_ftHandle);
    if (m_ftStatus != FT_OK) {
        return false;
    }
    m_ftStatus = FT_Write(m_ftHandle, m_TxBuffer, strData.size(), &m_ByteWritten);
    if (m_ftStatus == FT_OK) {
        FT_Close(m_ftHandle);
        return true;
    }
    FT_Close(m_ftHandle);
    return false;
}

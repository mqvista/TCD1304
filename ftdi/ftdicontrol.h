#ifndef FTDICONTROL_H
#define FTDICONTROL_H

#include <QObject>
#include <QMutex>
#include <QDebug>
#include <QDateTime>
#include "ftd2xx.h"

class FtdiControl : public QObject
{
    Q_OBJECT
public:
    static FtdiControl *Instance();
    void printDevicesInfo();
    bool getSenserData(quint16 *senserData);
    bool sendData(QString strData);
    bool init();
    bool openPort(int deviceNum=0);
    bool colsePort();
    bool getOpenStatus();

signals:
    void deviceOpenStatusChanged(bool status);

private:
    FT_STATUS m_ftStatus;
    FT_HANDLE m_ftHandle;
    FT_DEVICE_LIST_INFO_NODE *m_devInfo;
    DWORD m_numDevs;
    quint32 m_RxBytes;
    quint32 m_TxBytes;
    quint8 m_RxBuffer[7300];
    quint8 m_TxBuffer[128];
    quint32 m_Event;
    DWORD m_Bytereceived;
    DWORD m_ByteWritten;
    bool m_isOpened;


    explicit FtdiControl(QObject *parent = nullptr);

};

#endif // FTDICONTROL_H

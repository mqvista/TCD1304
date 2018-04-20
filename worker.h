#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include "ftdi/ftdicontrol.h"
#include "filter.h"
#include "savefile.h"
#include "ployfit.h"
#include "windowfilter.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    static Worker *Instance();
    ~Worker();
    Q_INVOKABLE bool ftdiInit();
    Q_INVOKABLE bool runOnce();
    Q_INVOKABLE void startAutoAcq(quint16 time);
    Q_INVOKABLE void stopAutoAcq();
    Q_INVOKABLE bool sendData(QString strData);
    Q_INVOKABLE void saveRawData(QString dataUrl);
    bool runAlways();
    void thresholding(quint16 threshold, quint16 min, quint16 max);
    quint16 getThresholdValue() const;
    Q_INVOKABLE void setThresholdValue(const quint16 &value);
    Q_INVOKABLE void setIntergral(quint8 value);
    QString converyIntergralData();
    void calcuLength();
    void fillHeadTail(quint16 length, quint16 value);
    void getLeftRight(quint16 minCutValue, quint16 maxCutValue, quint16* leftOffset, quint16* leftLength, quint16* rightOffset, quint16* rightLength);

signals:
    void getNewData(quint16 *dts0, quint16 *dts1, quint16 length);
    void sendMeasureLength(quint16 length);
    void sendPolyValue(QString value);

private:
    explicit Worker(QObject *parent = nullptr);
    QTimer *m_acqTimer;
    quint16 m_SenserData[3648];
    quint16 m_SenserThresholdData[3648];
    quint16 m_ThresholdValue;
    quint16 m_MeasureLength;
    Filter filter;
    UWindowFilter<double> uWindowFilter;
    UWindowFilter<quint32> lengthFilterWithoutPloy;

    SaveFile saveFile;
    PloyFit ployFit;

    bool m_NeedToSetParams;
    quint8 m_IntergralValue;

};

#endif // WORKER_H

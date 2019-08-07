#ifndef CONTROLPANELMODULE_H
#define CONTROLPANELMODULE_H

#include <QObject>
#include "worker.h"
#include "QString"

class ControlPanelModule : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint16 measureLength READ getMeasureLength WRITE setMeasureLength NOTIFY measureLengthChanged)
    Q_PROPERTY(QString realLength READ getRealLength NOTIFY realLengthChanged)
    Q_PROPERTY(QString polyValue READ getPolyValue WRITE setPolyValue NOTIFY polyValueChanged)
    Q_PROPERTY(bool deviceStatus READ getDeviceStatus NOTIFY deviceStatusChanged)
    Q_PROPERTY(QString relativelyLength READ getRelativeLength WRITE setRelativelyLength NOTIFY relativelyLengthChanged)
public:
    explicit ControlPanelModule(QObject *parent = nullptr);
    Q_INVOKABLE void updateThresholdValue(quint16 value);
    Q_INVOKABLE void setMeasureLength(quint16 length);
    Q_INVOKABLE void setIntergral(quint8 percent);
    Q_INVOKABLE void openDevice();
    Q_INVOKABLE void closeDevice();
    Q_INVOKABLE void saveData(QString dataUrl);
    Q_INVOKABLE void setPolyValue(QString value);
    Q_INVOKABLE void setPolyRealValue(QString value);
    Q_INVOKABLE void setRelativelyLength(QString value);
    quint16 getMeasureLength();
    QString getRealLength();
    QString getPolyValue();
    bool getDeviceStatus();
    QString getRelativeLength();
    Q_INVOKABLE void setResetRelativelyValue();

signals:
    void measureLengthChanged();
    void realLengthChanged();
    void polyValueChanged();
    void deviceStatusChanged();
    void relativelyLengthChanged();

public slots:
    void getDeviceOpenStatus(bool status);

private:
    quint16 m_MeasureLength;
    QString m_RealLength;
    QString m_polyValue;
    bool m_DeviceStatus;
    QString m_RelativeLength;
};

#endif // CONTROLPANELMODULE_H

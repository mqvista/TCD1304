#ifndef CONTROLPANELMODULE_H
#define CONTROLPANELMODULE_H

#include <QObject>
#include "worker.h"
#include "QString"

class ControlPanelModule : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint16 measureLength READ getMeasureLength WRITE setMeasureLength  NOTIFY measureLengthChanged)
    Q_PROPERTY(QString realLength READ getRealLength NOTIFY realLengthChanged)
public:
    explicit ControlPanelModule(QObject *parent = nullptr);
    Q_INVOKABLE void updateThresholdValue(quint16 value);
    Q_INVOKABLE void setMeasureLength(quint16 length);
    Q_INVOKABLE void setIntergral(quint8 percent);
    Q_INVOKABLE void closeDevice();
    Q_INVOKABLE void saveData(QString dataUrl);
    quint16 getMeasureLength();
    QString getRealLength();

signals:
    void measureLengthChanged();
    void realLengthChanged();

private:
    quint16 m_MeasureLength;
    QString m_RealLength;
};

#endif // CONTROLPANELMODULE_H

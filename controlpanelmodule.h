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
    quint16 getMeasureLength();
    QString getRealLength();
    QString getPolyValue();

signals:
    void measureLengthChanged();
    void realLengthChanged();
    void polyValueChanged();


private:
    quint16 m_MeasureLength;
    QString m_RealLength;
    QString m_polyValue;
};

#endif // CONTROLPANELMODULE_H

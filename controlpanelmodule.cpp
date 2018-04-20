#include "controlpanelmodule.h"

ControlPanelModule::ControlPanelModule(QObject *parent) : QObject(parent)
{

}

//从界面更新阈值
void ControlPanelModule::updateThresholdValue(quint16 value)
{
    QMetaObject::invokeMethod(Worker::Instance(), "setThresholdValue", Qt::QueuedConnection, Q_ARG(quint16, value));
}

//获取测量长度，由属性功能自动操作
quint16 ControlPanelModule::getMeasureLength()
{
    return m_MeasureLength;
}

//返回给界面实际
void ControlPanelModule::setMeasureLength(quint16 length)
{
    m_MeasureLength = length;
    float realLength = 0.0068321917808218426*length + 1.6360616438356983;
    m_RealLength = QString::number(realLength, 10 , 4 );
    emit measureLengthChanged();
    emit realLengthChanged();
}

void ControlPanelModule::setIntergral(quint8 percent)
{
    QMetaObject::invokeMethod(Worker::Instance(), "setIntergral", Qt::QueuedConnection, Q_ARG(quint8, percent));
}

void ControlPanelModule::closeDevice()
{
    QMetaObject::invokeMethod(Worker::Instance(), "stopAutoAcq", Qt::QueuedConnection);
}

//保存原始数据
void ControlPanelModule::saveData(QString dataUrl)
{
    QMetaObject::invokeMethod(Worker::Instance(), "saveRawData", Qt::QueuedConnection, Q_ARG(QString, dataUrl));
}

void ControlPanelModule::setPolyValue(QString value)
{
    m_polyValue = value;
    emit polyValueChanged();
}

QString ControlPanelModule::getRealLength()
{
    return m_RealLength;
}

QString ControlPanelModule::getPolyValue()
{
    return m_polyValue;
}




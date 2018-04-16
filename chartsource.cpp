#include "chartsource.h"

ChartSource::ChartSource(QObject *parent) : QObject(parent)
{

}

void ChartSource::generateData(quint8 num, quint16 *data, quint16 length)
{
    // Remove previous data
    if (num == 0)
    {
        m_data0.clear();
        for(int i=0; i<length; i++)
        {
            m_data0.append(QPointF(i, data[i]));
        }
    }

    else if (num == 1)
    {
        m_data1.clear();
        for(int i=0; i<length; i++)
        {
            m_data1.append(QPointF(i, data[i]));
        }
    }

}

void ChartSource::update(QAbstractSeries *series0, QAbstractSeries *series1)
{
    if (series0 && series1) {
        QXYSeries *xySeries0 = static_cast<QXYSeries *>(series0);
        QXYSeries *xySeries1 = static_cast<QXYSeries *>(series1);
        // Use replace instead of clear + append, it's optimized for performance
        xySeries0->replace(m_data0);
        xySeries1->replace(m_data1);
    }
}

void ChartSource::processFromWorker(quint16 *data0, quint16 *data1, quint16 length)
{
    generateData(0, data0, length);
    generateData(1, data1, length);
    emit updateChart();
}

//void ChartSource::update(QAbstractSeries *series)
//{

//}

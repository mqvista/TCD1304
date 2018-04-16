#ifndef CHARTSOURCE_H
#define CHARTSOURCE_H

#include <QObject>
#include <QPointF>
#include <QVector>
#include <QtCharts/QAbstractSeries>
#include <QXYSeries>

QT_BEGIN_NAMESPACE
class QQuickView;
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class ChartSource : public QObject
{
    Q_OBJECT
public:
    explicit ChartSource(QObject *parent = nullptr);
    void generateData(quint8 num, quint16 *data, quint16 length);
    Q_INVOKABLE void update(QAbstractSeries *series0, QAbstractSeries *series1);



private:
    QVector<QPointF> m_data0;
    QVector<QPointF> m_data1;

signals:
    void updateChart();

public slots:
    void processFromWorker(quint16 *data0, quint16 *data1, quint16 length);
};

#endif // CHARTSOURCE_H

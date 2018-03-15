#ifndef CHARTSOURCE_H
#define CHARTSOURCE_H

#include <QObject>

class ChartSource : public QObject
{
    Q_OBJECT
public:
    explicit ChartSource(QObject *parent = nullptr);

public slots:
//    void generateData(int type, int rowCount, int colCount);
//    void update(QAbstractSeries *series);

private:
//    QQuickView *m_appViewer;
//    QList<QVector<QPointF> > m_data;
};

#endif // CHARTSOURCE_H

#ifndef SORTINGFILTER_H
#define SORTINGFILTER_H

#include <QObject>

class SortingFilter : public QObject
{
    Q_OBJECT
public:
    explicit SortingFilter(QObject *parent = nullptr);
    double get(double value);
signals:

public slots:

private:
    double m_Data[20];
    double m_sotredData[20];

    static int comp(const void *a, const void *b);

};

#endif // SORTINGFILTER_H

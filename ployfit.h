#ifndef PLOYFIT_H
#define PLOYFIT_H

#include <QObject>
#include <QDebug>
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_cdf.h>
//#include <QtMath>
#include <math.h>



class PloyFit : public QObject
{
    Q_OBJECT
public:
    explicit PloyFit(QObject *parent = nullptr);
    void test();
    void calc(quint16 *dataX, quint16 *dataY, quint16 dataLength, quint8 polyN, double *value);
    double slove(double a, double b, double c, double x);

signals:

public slots:

private:
};

#endif // PLOYFIT_H

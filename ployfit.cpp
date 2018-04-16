#include "ployfit.h"

PloyFit::PloyFit(QObject *parent) : QObject(parent)
{

}

void PloyFit::test()
{


}

void PloyFit::calc(quint16 *senserData, quint16 dataLength, quint8 polyN)
{
    //先准备参数
    //准备 gsl_mutifit_liner 参数 X, y, c
    //准备一个系数矩阵X，定义一个参数是输入数据的数量，第二个参数为拟合次数
    gsl_matrix *X = gsl_matrix_alloc(dataLength, polyN);
    //准备一个观测值y， 参数为数据数量
    gsl_vector *y = gsl_vector_alloc(dataLength);
    //准备待拟合确定的参数, 参数为拟合次数
    gsl_vector *c = gsl_vector_alloc(polyN);
    //协方差矩阵, 参数为拟合次数
    gsl_matrix *cov = gsl_matrix_alloc(polyN, polyN);
    //拟合曲线与数据点的优值函数最小值， 返回的
    double chisq;
    //数据丢进去
    for(quint16 i=0; i<dataLength; i++)
    {
        gsl_matrix_set(X, i, 0, 1.0);
        gsl_vector_set(y, i, senserData[i]);
        for(quint8 j = 1; j< polyN; j++)
        {
            gsl_matrix_set(X, i, j, pow(i ,j));
        }
    }
    //准备工作空间, 参数一为数据长度， 二为拟合次数
    gsl_multifit_linear_workspace *work_space = gsl_multifit_linear_alloc(dataLength, polyN);
    gsl_multifit_linear(X, y, c, cov, &chisq, work_space);
    gsl_multifit_linear_free(work_space);
    //计算最优度
    double Q = gsl_cdf_chisq_Q(chisq/2.0, (dataLength-2)/2.0);

    //输出
    for(quint8 i=0; i<polyN; i++)
    {
        qDebug()<< "Num" << i << "==" << c->data[i];
    }
    qDebug() << "Chisqp:" << chisq;
    qDebug() << "Q=" << Q;
    qDebug()<<"Finish";

    //内存回收
    gsl_matrix_free(X);
    gsl_vector_free(y);
    gsl_vector_free(c);
    gsl_matrix_free(cov);
}

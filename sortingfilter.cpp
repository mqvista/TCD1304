#include "sortingfilter.h"

SortingFilter::SortingFilter(QObject *parent) : QObject(parent)
{
    // 先初始化里面的数据， 免得取到奇奇怪怪的东西
    for (quint8 i=0; i<20; i++)
    {
        m_Data[i] = 0;
        m_sotredData[i] = 0;
    }
}

double SortingFilter::get(double value)
{
    // 数组向左移位一格
    for (quint8 i=0; i<19; i++)
    {
        m_Data[i] = m_Data[i+1];
    }

    // 存入数据
    m_Data[19] = value;

    // 拷贝数组
    std::copy(std::begin(m_Data), std::end(m_Data), std::begin(m_sotredData));

    // 排序
    std::qsort(m_sotredData, 20, sizeof(m_sotredData[0]), comp);

    return (m_sotredData[8] + m_sotredData[9] + m_sotredData[10] + m_sotredData[11] + m_sotredData[12]) / 5;
}

int SortingFilter::comp(const void* a, const void* b)
{
    return *(double*)a > *(double*)b ? 1: -1;
}


#include "filter.h"

Filter::Filter(quint16 wsize, QObject *parent) : QObject(parent)
{
    m_size = wsize;
    m_nums = new quint16[m_size];
    m_num_sp = 0;
}

Filter::~Filter()
{
    delete[] m_nums;
}

quint16 Filter::get(quint16 value)
{
    uint64_t sum=0;
    m_nums[m_num_sp++] = value;
    m_num_sp = m_num_sp % m_size;
    for (quint8 i=0; i<m_size; i++)
    {
        sum += m_nums[i];
    }
    return sum/m_size;
}

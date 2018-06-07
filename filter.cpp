#include "filter.h"

Filter::Filter(QObject *parent) : QObject(parent)
{
    uFilter = new UWindowFilter<quint32>[3648];
}

Filter::~Filter()
{
}

void Filter::get(quint16* originalValue, quint16* filterValue)
{
    for(quint16 i=0; i<3648; i++)
    {
        filterValue[i] = uFilter[i].Get(originalValue[i]);
    }
}


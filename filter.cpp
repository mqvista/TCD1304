#include "filter.h"

Filter::Filter(QObject *parent) : QObject(parent)
{
    uFilter = new UWindowFilter<quint32>[3648];
   // for(quint16 i=0;i<3648;++i){
    //    uFilter[i]=new UWindowFilter<quint32>(15);
    //}
}

Filter::~Filter()
{
}

void Filter::get(quint16 *value)
{
    for(quint16 i=0; i<3648; i++)
    {
        value[i] = uFilter[i].Get(value[i]);
    }
}


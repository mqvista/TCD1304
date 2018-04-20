#ifndef WINDOWFILTER_H
#define WINDOWFILTER_H

#include <QObject>


template<typename T>
class UWindowFilter {
public:
    UWindowFilter(quint8 size=10) {
        _Size = size;
        _Sp = 0;
        Buffer = new T[size]();
    }
    ~UWindowFilter() {
        delete[] Buffer;
    }

    T Get(T input) {
        //建立临时变量用于存储和
        T sum = 0;
        //将当前数据移入缓冲
        Buffer[_Sp++] = input;
        //移动缓冲指针
        _Sp %= _Size;
        //累计求和
        for (quint8 i = 0; i < _Size; ++i) {
            sum += Buffer[i];
        }
        //返回平均数
        return sum / _Size;
    }
private:
    T *Buffer;
    quint8 _Size;
    quint8 _Sp;
};

#endif // WINDOWFILTER_H

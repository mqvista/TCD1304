#ifndef FILTER_H
#define FILTER_H

#include <QObject>
#include <QDebug>

class Filter : public QObject
{
    Q_OBJECT
public:
    explicit Filter(quint16 wsize ,QObject *parent = nullptr);
    ~Filter();
    quint16 get(quint16 value);

signals:

public slots:

private:
    //窗口指针
    quint16* m_nums;
    //当前位置
    quint8 m_num_sp;
    //窗口大小
    quint8 m_size;

};

#endif // FILTER_H

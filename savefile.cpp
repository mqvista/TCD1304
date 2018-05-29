#include "savefile.h"

SaveFile::SaveFile(QObject *parent) : QObject(parent)
{

}

void SaveFile::saveCurrentData(quint16 *senserData, quint16 length, QString saveUrl)
{
    saveUrl = saveUrl.mid(7) + ".txt";
    qDebug()<< saveUrl;
    QFile *file = new QFile(saveUrl);
    if(!file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "open filed";
        qDebug() << file->errorString();
        return;
    }
    else
    {
        QTextStream out(file);
        for(quint16 i=0; i<length; i++)
        {
            out << senserData[i];
            out << "\n";
        }
        out.flush();
        file->close();
    }
}

void SaveFile::saveAllData(quint16 *origData, quint16 *filterData, quint16 length, QString saveUrl)
{
    saveUrl = saveUrl.mid(7) + ".csv";
    qDebug()<< saveUrl;
    QFile *file = new QFile(saveUrl);
    if(!file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "open filed";
        qDebug() << file->errorString();
        return;
    }
    else
    {
        QTextStream out(file);
        for(quint16 i=0; i<length; i++)
        {
            out << origData[i] << ",";
            out <<filterData[i];
            out << "\r\n";
        }
        out.flush();
        file->close();
    }
}










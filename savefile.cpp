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

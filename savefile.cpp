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

void SaveFile::saveAllData(quint16* origData, quint16* filterData,
                           quint16 leftLength, quint16 leftOffset, quint16 rightLength, quint16 rightOffset,
                           double *leftPoly, double *rightPoly, quint16 length, QString saveUrl,
                           double calcLeft, double calcRight, double calcPolyLength, double calcPolyLengthFilter)
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
        // tittle
        out << "origData" << "," << "filterData" << "\r\n";
        for(quint16 i=0; i<length; i++)
        {
            out << origData[i] << ",";
            out <<filterData[i];
            out << "\r\n";
        }
        out << "\r\n";
        out << "leftLength," << "leftOffset," << "rightLength," << "rightOffset" << "\r\n";
        out << leftLength << "," << leftOffset << "," << rightLength << "," << rightOffset << "\r\n";
        out << "leftPoly1" << "," << "leftPoly2" << "," << "leftPoly3" << "\r\n";
        out << leftPoly[0] << "," << leftPoly[1] << "," << leftPoly[2] << "\r\n";
        out << "rightPoly1" << "," << "rightPoly2" << "," << "rightPoly3" << "\r\n";
        out << rightPoly[0] << "," << rightPoly[1] << "," << rightPoly[2] << "\r\n";
        out << "calcLeft" << "," << "calcRight" << "\r\n";
        out << calcLeft << "," << calcRight << "\r\n";
        out << "calcPolyLenght" << "," << "calcPolyLengthFilter" << "\r\n";
        out << calcPolyLength << "," << calcPolyLengthFilter << "\r\n";

        out.flush();
        file->close();
    }
}










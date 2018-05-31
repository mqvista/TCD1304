#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QFileDialog>

class SaveFile : public QObject
{
    Q_OBJECT
public:
    explicit SaveFile(QObject *parent = nullptr);
    void saveCurrentData(quint16 *senserData, quint16 length ,QString saveUrl);
    void saveAllData(quint16* origData, quint16* filterData,
                     quint16 leftLength, quint16 leftOffset, quint16 rightLength, quint16 rightOffset,
                     double* leftPoly, double* rightPoly, quint16 length, QString saveUrl,
                     double calcLeft, double calcRight, double calcPolyLength, double calcPolyLengthFilter);

signals:

public slots:
};

#endif // SAVEFILE_H

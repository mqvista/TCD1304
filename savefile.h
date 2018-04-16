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

signals:

public slots:
};

#endif // SAVEFILE_H

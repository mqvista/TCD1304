QT += qml
QT += quick
CONFIG += c++11
QT += charts
QT += network
CONFIG +=console

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    ftdi/ftdicontrol.cpp \
    worker.cpp \
    services.cpp \
    chartsource.cpp \
    controlpanelmodule.cpp \
    filter.cpp \
    savefile.cpp \
    ployfit.cpp \
    sortingfilter.cpp \
    tcpserver.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ftd2xx.h \
    WinTypes.h \
    ftdi/ftdicontrol.h \
    worker.h \
    services.h \
    chartsource.h \
    controlpanelmodule.h \
    filter.h \
    savefile.h \
    ployfit.h \
    windowfilter.h \
    config.h \
    sortingfilter.h \
    tcpserver.h

# include for ftdi
macx: LIBS += -L$$PWD/D2XX/mac/ -lftd2xx.1.4.4
contains(QT_ARCH, i386) {
    LIBS += -L$$PWD/D2XX/win32/ -lftd2xx
}else {
    LIBS += -L$$PWD/D2XX/win64/ -lftd2xx
}
INCLUDEPATH += $$PWD/D2XX/include/
DEPENDPATH += $$PWD/D2XX/include/




# include for GNU Scientific Library
macx: LIBS += -L$$PWD/GSL/mac/lib/ -lgsl.23
macx: LIBS += -L$$PWD/GSL/mac/lib/ -lgslcblas
# for windows
contains(QT_ARCH, i386) {
    LIBS += -L$$PWD/GSL/win32/lib/ -llibgsl
    LIBS += -L$$PWD/GSL/win32/lib/ -llibgslcblas
}else {
    LIBS += -L$$PWD/GSL/win64/lib/ -lgsl
    LIBS += -L$$PWD/GSL/win64/lib/ -lgslcblas
}
INCLUDEPATH += $$PWD/GSL/include/
DEPENDPATH += $$PWD/GSL/include/


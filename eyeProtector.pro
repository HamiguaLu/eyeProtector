#-------------------------------------------------
#
# Project created by QtCreator 2015-12-11T15:22:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eyeProtector
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qresttimecounter.cpp \
    time2restdlg.cpp

HEADERS  += mainwindow.h \
    qresttimecounter.h \
    time2restdlg.h

FORMS    += mainwindow.ui \
    qresttimecounter.ui \
    time2restdlg.ui

RESOURCES += \
    icon.qrc

LIBS += -lX11

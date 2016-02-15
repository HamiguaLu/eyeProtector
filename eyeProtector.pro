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
    qresttimecounter.cpp

HEADERS  += mainwindow.h \
    qresttimecounter.h

FORMS    += mainwindow.ui \
    qresttimecounter.ui

RESOURCES += \
    icon.qrc

LIBS += -lX11

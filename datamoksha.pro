#-------------------------------------------------
#
# Project created by QtCreator 2016-11-10T17:23:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = datamoksha
TEMPLATE = app

QT_CONFIG -= no-pkg-config

SOURCES += main.cpp\
        mainwindow.cpp \
    pixelsort.cpp \
    operation.cpp

HEADERS  += mainwindow.h \
    pixelsort.h \
    operation.h

FORMS    += mainwindow.ui

unix {
   CONFIG += link_pkgconfig
   PKGCONFIG += opencv
}

#-------------------------------------------------
#
# Project created by QtCreator 2016-11-10T17:23:46
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = datamoksha
TEMPLATE = app

CONFIG += c++11
QT_CONFIG -= no-pkg-config

SOURCES = main.cpp\
        mainwindow.cpp \
        pixelsort.cpp \
        operation.cpp \
        cvutil.cpp

HEADERS = mainwindow.h \
    pixelsort.h \
    operation.h \
    cvutil.h

FORMS = mainwindow.ui

linux {
   PKG_CONFIG_PATH += /usr/lib/x86_64-linux-gnu/pkgconfig/
   CONFIG += link_pkgconfig
   PKGCONFIG += opencv
}

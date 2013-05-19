#-------------------------------------------------
#
# Project created by QtCreator 2013-05-17T18:24:15
#
#-------------------------------------------------

QT       += core gui
QT       += sql

TARGET = gui
TEMPLATE = app

INCLUDEPATH += "../cmdline"
DEPENDPATH  += "../cmdline"

SOURCES += main.cpp\
           mainwindow.cpp \
           ../cmdline/globals.cpp \
           ../cmdline/enigmadatabase.cpp \
           ../cmdline/enigmaexception.cpp

HEADERS  += mainwindow.h \
            ../cmdline/globals.h \
           ../cmdline/enigmadatabase.h \
           ../cmdline/enigmaexception.h

FORMS    += mainwindow.ui

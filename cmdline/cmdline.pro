#-------------------------------------------------
#
# Project created by QtCreator 2013-05-17T18:21:11
#
#-------------------------------------------------

QT       += core
QT       += sql

QT       -= gui

TARGET = cmdline
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    globals.cpp \
    entrypoint.cpp \
    enigmadatabase.cpp \
    rotor.cpp

HEADERS += \
    globals.h \
    entrypoint.h \
    enigmadatabase.h \
    rotor.h

#-------------------------------------------------
#
# Project created by QtCreator 2013-05-21T15:59:47
#
#-------------------------------------------------

QT       += sql testlib

QT       -= gui

TARGET = tst_unittest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


INCLUDEPATH += "../cmdline"
DEPENDPATH  += "../cmdline"

SOURCES += tst_unittest.cpp \
    ../cmdline/steckerboard.cpp \
    ../cmdline/rotor.cpp \
    ../cmdline/reflector.cpp \
    ../cmdline/keyboard.cpp \
    ../cmdline/globals.cpp \
    ../cmdline/genlib.cpp \
    ../cmdline/entry.cpp \
    ../cmdline/enigmaexception.cpp \
    ../cmdline/enigmadatabase.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../cmdline/steckerboard.h \
    ../cmdline/rotor.h \
    ../cmdline/reflector.h \
    ../cmdline/keyboard.h \
    ../cmdline/globals.h \
    ../cmdline/genlib.h \
    ../cmdline/entry.h \
    ../cmdline/enigmaexception.h \
    ../cmdline/enigmadatabase.h

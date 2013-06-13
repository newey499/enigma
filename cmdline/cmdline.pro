########################################################################
#
# Copyright Chris Newey 2013
#
# enigmasim@hotmail.com
#
# This file is part of enigma.
#
# Enigma is distributed under the terms of the GNU General Public License
#
# Enigma is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# enigma is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Enigma.  If not, see <http://www.gnu.org/licenses/>.
#
###########################################################################


#-------------------------------------------------
#
# Project created by QtCreator 2013-05-17T18:21:11
#
#-------------------------------------------------

DEFINES -= BUILD_GUI

QT       += core
QT       += sql

QT       -= gui

TARGET = cmdline
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    globals.cpp \
    enigmadatabase.cpp \
    rotor.cpp \
    enigmaexception.cpp \
    genlib.cpp \
    reflector.cpp \
    entry.cpp \
    keyboard.cpp \
    steckerboard.cpp \
    testharness.cpp \
    messagehandler.cpp \
    lampboard.cpp \
    machine.cpp \
    testdatabasevalidation.cpp \
    alphabet.cpp \
    componentbase.cpp \
    entrydata.cpp \
    reflectordata.cpp \
    rotordata.cpp \
    machinedata.cpp \
    alphabetdata.cpp \
    wheellist.cpp \
    mysql.cpp \
    wheelbasedata.cpp

HEADERS += \
    globals.h \
    enigmadatabase.h \
    rotor.h \
    enigmaexception.h \
    genlib.h \
    reflector.h \
    entry.h \
    keyboard.h \
    steckerboard.h \
    testharness.h \
    messagehandler.h \
    lampboard.h \
    machine.h \
    testdatabasevalidation.h \
    alphabet.h \
    componentbase.h \
    entrydata.h \
    reflectordata.h \
    rotordata.h \
    machinedata.h \
    alphabetdata.h \
    wheellist.h \
    mysql.h \
    wheelbasedata.h

OTHER_FILES += \
    ../README.md \
    ../license.txt \
    machine-validation-notes.txt

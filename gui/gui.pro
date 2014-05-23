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
# along with Qiptables.  If not, see <http://www.gnu.org/licenses/>.
#
###########################################################################


#-------------------------------------------------
#
# Project created by QtCreator 2013-05-17T18:24:15
#
#-------------------------------------------------

DEFINES += BUILD_GUI

QT       += core gui widgets
QT       += sql

TARGET = gui
TEMPLATE = app

INCLUDEPATH += "../cmdline"
DEPENDPATH  += "../cmdline"

SOURCES += main.cpp\
           mainwindow.cpp \
           ../cmdline/globals.cpp \
           ../cmdline/enigmadatabase.cpp \
           ../cmdline/enigmaexception.cpp \
           ../cmdline/rotor.cpp \
           ../cmdline/reflector.cpp \
           ../cmdline/genlib.cpp \
           ../cmdline/entry.cpp \
    ../cmdline/steckerboard.cpp \
    ../cmdline/alphabet.cpp \
    ../cmdline/componentbase.cpp \
    ../cmdline/entrydata.cpp \
    ../cmdline/reflectordata.cpp \
    ../cmdline/rotordata.cpp \
    ../cmdline/alphabetdata.cpp \
    ../cmdline/wheellist.cpp \
    ../cmdline/wheelbasedata.cpp \
    enigmaaction.cpp \
    ../cmdline/testharness.cpp \
    ../cmdline/keyboard.cpp \
    ../cmdline/testdatabasevalidation.cpp \
    ../cmdline/machine.cpp \
    ../cmdline/mysql.cpp \
    ../cmdline/lampboard.cpp \
    ../cmdline/machinedata.cpp \
    formmachine.cpp \
    formtestcomponents.cpp \
    emitstring.cpp \
    guimessagehandler.cpp \
    rotorcombobox.cpp \
    rotorsetupdialog.cpp \
    ../cmdline/messagehandler.cpp



HEADERS  += mainwindow.h \
            ../cmdline/globals.h \
           ../cmdline/enigmadatabase.h \
           ../cmdline/enigmaexception.h \
           ../cmdline/enigmaexception.h \
           ../cmdline/rotor.h \
           ../cmdline/reflector.h \
           ../cmdline/genlib.h \
           ../cmdline/entry.h \
    ../cmdline/steckerboard.h \
    ../cmdline/alphabet.h \
    ../cmdline/componentbase.h \
    ../cmdline/entrydata.h \
    ../cmdline/reflectordata.h \
    ../cmdline/rotordata.h \
    ../cmdline/alphabetdata.h \
    ../cmdline/wheellist.h \
    ../cmdline/wheelbasedata.h \
    enigmaaction.h \
    ../cmdline/testharness.h \
    ../cmdline/keyboard.h \
    ../cmdline/testdatabasevalidation.h \
    ../cmdline/machine.h \
    ../cmdline/mysql.h \
    ../cmdline/lampboard.h \
    ../cmdline/machinedata.h \
    formmachine.h \
    formtestcomponents.h \
    emitstring.h \
    guimessagehandler.h \
    rotorcombobox.h \
    rotorsetupdialog.h \
    ../cmdline/messagehandler.h



FORMS    += mainwindow.ui \
    formmachine.ui \
    formtestcomponents.ui \
    rotorsetupdialog.ui

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
           ../cmdline/enigmaexception.cpp \
           ../cmdline/rotor.cpp \
           ../cmdline/reflector.cpp \
           ../cmdline/genlib.cpp \
           ../cmdline/entry.cpp


HEADERS  += mainwindow.h \
            ../cmdline/globals.h \
           ../cmdline/enigmadatabase.h \
           ../cmdline/enigmaexception.h \
           ../cmdline/enigmaexception.h \
           ../cmdline/rotor.h \
           ../cmdline/reflector.h \
           ../cmdline/genlib.h \
           ../cmdline/entry.h


FORMS    += mainwindow.ui

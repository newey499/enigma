/************************************************************************
Copyright Chris Newey 2013

enigmasim@outlook.com

This file is part of enigma.

Enigma is distributed under the terms of the GNU General Public License

Enigma is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Qiptables is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Qiptables.  If not, see <http://www.gnu.org/licenses/>.

***************************************************************************/

#include "entrypoint.h"

EntryPoint::EntryPoint(QObject *parent) :
    QObject(parent)
{
}


int EntryPoint::exec()
{
    int result = 0;

    qDebug("EntryPoint::exec()");

    try
    {
        edb = EnigmaDatabase::getInstance();

        //testMapping();
        //testReflector();
        testEntry();
    }
    catch (EnigmaException &e)
    {
        qDebug("\n%s", e.what().toAscii().data());
        qApp->exit(1); // exit with error exit code
    }

    return result;
}


void EntryPoint::testMapping()
{
    //Rotor rotor("NOMAP", this);
    Rotor rotor("REVERSE", this);

    int pinIn;

    pinIn = 1;
    rotor.setRingSetting(1);
    rotor.setLetterSetting("A");
    rotor.mapLeftToRight(pinIn);
    rotor.rotate();
    rotor.rotate();
    rotor.rotate();
    pinIn = 1;
    rotor.setRingSetting(1);
    rotor.setLetterSetting("Y");
    rotor.mapLeftToRight(pinIn);
    rotor.rotate();
    rotor.rotate();
    rotor.rotate();
    rotor.rotate();
    rotor.rotate();
}


void EntryPoint::testReflector()
{
    qDebug("EntryPoint::testReflector()");

    //Reflector reflector("REFLECTORNOMAP", this);
    Reflector reflector("REFLECTORREVERSE", this);

    int pinIn;
    int pinOut;


    pinIn = 1;
    pinOut = reflector.map(pinIn);
    qDebug("Reflector::map  pinIn [%d] pinOut [%d]",
           pinIn, pinOut);

    pinIn = 2;
    pinOut = reflector.map(pinIn);
    qDebug("Reflector::map  pinIn [%d] pinOut [%d]",
           pinIn, pinOut);

    pinIn = 25;
    pinOut = reflector.map(pinIn);
    qDebug("Reflector::map  pinIn [%d] pinOut [%d]",
           pinIn, pinOut);

    pinIn = 26;
    pinOut = reflector.map(pinIn);
    qDebug("Reflector::map  pinIn [%d] pinOut [%d]",
           pinIn, pinOut);

    /***************
    pinIn = 27;
    pinOut = reflector.map(pinIn);
    qDebug("Reflector::map  pinIn [%d] pinOut [%d]",
           pinIn, pinOut);
    ******************/
}


void EntryPoint::testEntry()
{
    qDebug("EntryPoint::testEntry()");

    //Entry entry("ENTRYNOMAP", this);
    Entry entry("ENTRYREVERSE", this);

    int pinIn;
    int pinOut;


    pinIn = 1;
    pinOut = entry.map(pinIn);
    qDebug("Entry::map  pinIn [%d] pinOut [%d]",
           pinIn, pinOut);

    pinIn = 2;
    pinOut = entry.map(pinIn);
    qDebug("Entry::map  pinIn [%d] pinOut [%d]",
           pinIn, pinOut);

    pinIn = 25;
    pinOut = entry.map(pinIn);
    qDebug("Entry::map  pinIn [%d] pinOut [%d]",
           pinIn, pinOut);

    pinIn = 26;
    pinOut = entry.map(pinIn);
    qDebug("Entry::map  pinIn [%d] pinOut [%d]",
           pinIn, pinOut);

    /***************
    pinIn = 27;
    pinOut = entry.map(pinIn);
    qDebug("Entry::map  pinIn [%d] pinOut [%d]",
           pinIn, pinOut);
    ******************/
}

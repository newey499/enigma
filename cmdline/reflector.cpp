/************************************************************************
Copyright Chris Newey 2013

enigmasim@outlook.com

This file is part of enigma.

Enigma is distributed under the terms of the GNU General Public License

Enigma is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Enigma is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Enigma.  If not, see <http://www.gnu.org/licenses/>.

***************************************************************************/

#include "reflector.h"


Reflector::Reflector(QString reflectorName, QObject *parent) :
    QObject(parent)
{
    recReflector = ReflectorData().getReflector(reflectorName);
    commonConstructor();
}


Reflector::Reflector(int reflectorId, QObject *parent):
    QObject(parent)
{
    recReflector = ReflectorData().getReflector(reflectorId);
    commonConstructor();
}


void Reflector::commonConstructor()
{
    try
    {
        oAlphabet = new Alphabet(recReflector.value("alphabetid").toInt(), this);
        recAlphabet = oAlphabet->getAlphabetRec();

        alphabetMap = oAlphabet->getAlphabetMap();
        // This has to be set before a space is prepended
        alphabetSize = alphabetMap.size();

        // Place a space at the start of the string so that pin
        // numbers need not be zero based.
        alphabetMap.prepend(" ");
        alphabetName = oAlphabet->getAlphabetName();

        reflectorMap = recReflector.value("pinright").toString();
        // Place a space at the start of the string so that pin
        // numbers need not be zero based.
        reflectorMap.prepend(" ");
        reflectorName = recReflector.value("name").toString();


        qDebug("reflector [%s] alphabet [%s]",
               recReflector.value("name").toString().toAscii().data(),
               recAlphabet.value("name").toString().toAscii().data());

        sanityCheck();
    }
    catch (EnigmaException &e)
    {
        throw e;
    }
}


Reflector::~Reflector()
{

}


QString Reflector::getId()
{
    return recReflector.value("id").toString();
}


bool Reflector::sanityCheck()
{
    bool result = true;

    result = GenLib::alphabetSanityCheck(alphabetName, alphabetMap, reflectorName, reflectorMap);

    return result;
}


bool Reflector::isValidPinNo(int pinNo)
{
    bool result = true;

    if ((pinNo < 1) || (pinNo > getAlphabetSize()))
    {
        result = false;
    }

    return result;
}


int Reflector::getAlphabetSize()
{
    return alphabetSize;
}


/*******************
Assume the right side of the reflector is in alphabet order
and the left side of the reflector to be in mapping order.
********************/
int Reflector::map(int pinIn)
{
    int result = Globals::INVALID_PIN_NUMBER;
    int origPinIn = pinIn;


    if (! isValidPinNo(pinIn))
    {
        result = Globals::INVALID_PIN_NUMBER;
        qDebug("requested pin [%d] not in valid range [%d...%d]",
               pinIn,
               1,
               getAlphabetSize());
        return result;
    }

    QString x = alphabetMap.at(pinIn);
    result = reflectorMap.indexOf(x, 0, Qt::CaseSensitive );


    if (result == -1)
    {
        result = Globals::INVALID_PIN_NUMBER;
        qDebug("reflector map pin number [%d] not found",
                pinIn);
        return result;
    }

    qDebug("map origPinIn [%d] calcPinIn [%d] pinOut [%d]",
           origPinIn, pinIn, result);

    return result;
}





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


#include "entry.h"


Entry::Entry(QString entryName, QObject *parent) :
    ComponentBase(parent)
{

    try
    {

        recEntry = EntryData().getEntry(entryName);
        oAlphabet = new Alphabet(recEntry.value("alphabetid").toInt(), this);
        recAlphabet = oAlphabet->getAlphabetRec();

        alphabetMap = oAlphabet->getAlphabetMap();
        // This has to be set before a space is prepended
        alphabetSize = alphabetMap.size();

        // Place a space at the start of the string so that pin
        // numbers need not be zero based.
        alphabetMap.prepend(" ");
        alphabetName = oAlphabet->getAlphabetName();

        entryMap = recEntry.value("pinright").toString();
        // Place a space at the start of the string so that pin
        // numbers need not be zero based.
        entryMap.prepend(" ");
        this->entryName = recEntry.value("name").toString();


        qDebug("entry [%s] alphabet [%s]",
               recEntry.value("name").toString().toAscii().data(),
               recAlphabet.value("name").toString().toAscii().data());

        sanityCheck();
    }
    catch (EnigmaException &e)
    {
        throw e;
    }

}


Entry::~Entry()
{

}


bool Entry::sanityCheck()
{
    bool result = true;

    result = GenLib::alphabetSanityCheck(alphabetName, alphabetMap, entryName, entryMap);

    return result;
}


bool Entry::isValidPinNo(int pinNo)
{
    bool result = true;

    if ((pinNo < 1) || (pinNo > getAlphabetSize()))
    {
        result = false;
    }

    return result;
}


bool Entry::isValidKey(QString keyIn)
{
    return alphabetMap.contains(keyIn, Qt::CaseSensitive);
}


int Entry::getAlphabetSize()
{
    return alphabetSize;
}


int Entry::mapCharToPin(QString keyIn)
{
    int result = Globals::INVALID_PIN_NUMBER;

    if (! isValidKey(keyIn))
    {
        result = Globals::INVALID_PIN_NUMBER;
        qDebug("requested key [%s] not in alphabet [%s] [%s]",
               keyIn.toAscii().data(),
               alphabetName.toAscii().data(),
               alphabetMap.toAscii().data());
    }

    result = entryMap.indexOf(keyIn, 0, Qt::CaseSensitive);
    /*******************
    qDebug("charIn [%s] pinOut [%d] [%s] [%s]",
           keyIn.toAscii().data(),
           result,
           entryName.toAscii().data(),
           entryMap.toAscii().data() );
    ***********************/

    if (result == -1)
    {
        result = Globals::INVALID_PIN_NUMBER;
        qDebug("requested key [%s] not in entry mapping [%s] [%s]",
               keyIn.toAscii().data(),
               entryName.toAscii().data(),
               entryMap.toAscii().data());
    }

    return result;
}

QString Entry::mapPinToChar(int pinIn)
{
    if (! isValidPinNo(pinIn))
    {
         qDebug("requested pin [%d] not in valid range [%d...%d]",
                pinIn,
                1,
                getAlphabetSize());
         return "";
    }

    return entryMap.at(pinIn);
}

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


#include "entry.h"


Entry::Entry(QString entryName, QObject *parent) :
    QObject(parent)
{

    edb = EnigmaDatabase::getInstance();

    try
    {
        recEntry = edb->getEntry(entryName);
        recAlphabet = edb->getAlphabet(recEntry.value("alphabetid").toInt());

        alphabetMap = recAlphabet.value("alphabet").toString();
        // This has to be set before a space is prepended
        alphabetSize = alphabetMap.size();

        // Place a space at the start of the string so that pin
        // numbers need not be zero based.
        alphabetMap.prepend(" ");
        alphabetName = recAlphabet.value("name").toString();

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"
    int result = -99;

    if (! isValidKey(keyIn))
    {
        QString msg = QString("requested key [%1] not in alphabet [%2] [%3]").
                           arg(keyIn).
                           arg(alphabetName).
                           arg(alphabetMap);
        throw EnigmaException(msg.toAscii().data(),__FILE__, __LINE__);
    }

    result = entryMap.indexOf(keyIn, 0, Qt::CaseSensitive);
    qDebug("charIn [%s] pinOut [%d] [%s] [%s]",
           keyIn.toAscii().data(),
           result,
           entryName.toAscii().data(),
           entryMap.toAscii().data() );

    if (result == -1)
    {
        QString msg = QString("requested key [%1] not in entry mapping [%2] [%3]").
                           arg(keyIn).
                           arg(entryName).
                           arg(entryMap);
        throw EnigmaException(msg.toAscii().data(),__FILE__, __LINE__);
    }

    return result;

#pragma GCC diagnostic pop
}

QString Entry::mapPinToChar(int pinIn)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"

    if (! isValidPinNo(pinIn))
    {
         QString msg = QString("requested pin [%1] not in valid range [%2...%3]").
                            arg(pinIn).
                            arg(1).
                            arg(getAlphabetSize());
         throw EnigmaException(msg.toAscii().data(),__FILE__, __LINE__);
    }

    return entryMap.at(pinIn);

#pragma GCC diagnostic pop
}

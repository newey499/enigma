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

#include "lampboard.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"

Lampboard::Lampboard(QString alphabetName, QObject *parent) :
    QObject(parent)
{
    edb = EnigmaDatabase::getInstance();


    try
    {
        recAlphabet = edb->getAlphabet(alphabetName);

        alphabetMap = recAlphabet.value("alphabet").toString();
        // This has to be set before a space is prepended
        alphabetSize = alphabetMap.size();

        // Place a space at the start of the string so that pin
        // numbers need not be zero based.
        alphabetMap.prepend(" ");
        this->alphabetName = recAlphabet.value("name").toString();

        qDebug("alphabet [%s]",
               recAlphabet.value("name").toString().toAscii().data());

    }
    catch (EnigmaException &e)
    {
        throw e;
    }

}


Lampboard::Lampboard(int alphabetId, QObject *parent) :
    QObject(parent)
{
    edb = EnigmaDatabase::getInstance();

    try
    {
        recAlphabet = edb->getAlphabet(alphabetId);

        alphabetMap = recAlphabet.value("alphabet").toString();
        // This has to be set before a space is prepended
        alphabetSize = alphabetMap.size();

        // Place a space at the start of the string so that pin
        // numbers need not be zero based.
        alphabetMap.prepend(" ");
        this->alphabetName = recAlphabet.value("name").toString();

        qDebug("alphabet [%s]",
               recAlphabet.value("name").toString().toAscii().data());

    }
    catch (EnigmaException &e)
    {
        throw e;
    }

}


Lampboard::~Lampboard()
{

}


void Lampboard::illuminate(QString charIn)
{
    qDebug("Lampboard::illuminate(QString charIn)\n"
           "does nothing apart from validate <charIn>");

    try
    {
        if (alphabetMap.indexOf(charIn, Qt::CaseSensitive) == -1)
        {
            QString msg = QString("Lampboard::illuminate - [%1] not in alphabet [%2] [%3]").
                                    arg(charIn.toAscii().data()).
                                    arg(alphabetName.toAscii().data()).
                                    arg(alphabetMap.toAscii().data());

            throw EnigmaException(msg.toAscii().data(), __FILE__, __LINE__);
        }

    }
    catch (EnigmaException &e)
    {
        throw e;
    }
}

#pragma GCC diagnostic pop

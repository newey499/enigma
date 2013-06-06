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
    ComponentBase(parent)
{
    oAlphabet = new Alphabet(alphabetName, this);
    commonConstructor();
}


Lampboard::Lampboard(int alphabetId, QObject *parent) :
    ComponentBase(parent)
{
    oAlphabet = new Alphabet(alphabetId, this);
    commonConstructor();
}


void Lampboard::commonConstructor()
{

    recAlphabet = oAlphabet->getAlphabetRec();

    alphabetMap = oAlphabet->getAlphabetMap();
    // This has to be set before a space is prepended
    alphabetSize = alphabetMap.size();

    // Place a space at the start of the string so that pin
    // numbers need not be zero based.
    alphabetMap.prepend(" ");
    alphabetName = oAlphabet->getAlphabetName();

    qDebug("alphabet [%s]",
           recAlphabet.value("name").toString().toAscii().data());
}


Lampboard::~Lampboard()
{

}


void Lampboard::illuminate(QString charIn)
{
    qDebug("Lampboard::illuminate(QString charIn)");

    if (charIn.length() != 1)
    {
        qDebug("Length of input char [%s] should be 1 not %d",
               charIn.toAscii().data(),
               charIn.length());
        return;
    }

    if (oAlphabet->getAlphabetMap().contains(charIn))
    {
        qDebug("%s is a valid char", charIn.toAscii().data());
    }
    else
    {
        qDebug("%s is not a valid char - not in alphabet [%s]",
               charIn.toAscii().data(),
               oAlphabet->getAlphabetMap().toAscii().data());
        return;
    }


}

#pragma GCC diagnostic pop

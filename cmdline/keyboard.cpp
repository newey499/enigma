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

#include "keyboard.h"


Keyboard::Keyboard(QString name, QObject *parent) :
    ComponentBase(parent)
{
    oAlphabet = new Alphabet(name, this);
    commonConstructor();
}


Keyboard::Keyboard(int alphabetId, QObject *parent) :
    ComponentBase(parent)
{
    oAlphabet = new Alphabet(alphabetId, this);
    commonConstructor();
}


void Keyboard::commonConstructor()
{
    recAlphabet = oAlphabet->getAlphabetRec();
    alphabetMap = oAlphabet->getAlphabetMap();

    // This has to be set before a space is prepended
    alphabetSize = alphabetMap.size();

    // Place a space at the start of the string so that pin
    // numbers need not be zero based.
    alphabetMap.prepend(" ");
    alphabetName = oAlphabet->getAlphabetName();

    forceToUpper = false;

    qDebug("keyboard alphabet [%s]",
           alphabetName.toAscii().data());
}


Keyboard::~Keyboard()
{

}


bool Keyboard::isValidKey(QString keyIn)
{
    bool result = true;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"

    if (keyIn.size() != 1)
    {
        result = false;
        qDebug("Keyboard - input key must be one character key passed [%s]",
                keyIn.toAscii().data());
    }

    if (! alphabetMap.contains(keyIn, Qt::CaseSensitive))
    {
        result = false;
        qDebug("Keyboard - input key [%s] is not in alphabet [%s]",
                 keyIn.toAscii().data(),
                 alphabetMap.trimmed().toAscii().data());
    }


#pragma GCC diagnostic pop

    return result;
}


QString Keyboard::keyIn(QString keyIn)
{
    if (! isValidKey(keyIn))
    {
        keyIn = "";
    }
    else
    {
        if (forceToUpper)
        {
            keyIn = keyIn.toUpper();
        }
    }

    return keyIn;
}

QPointer<Alphabet> Keyboard::getAlphabetObj()
{
    return oAlphabet;
}



bool Keyboard::getForceToUpper()
{
    return forceToUpper;
}


void Keyboard::setForceToUpper(bool toUpper)
{
    forceToUpper = toUpper;
}

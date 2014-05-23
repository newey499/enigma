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

#include "steckerboard.h"

Steckerboard::Steckerboard(QString alphabetName, QObject *parent) :
    ComponentBase(parent)
{
    map.clear();
    oAlphabet = new Alphabet(alphabetName, this);

    recAlphabet = oAlphabet->getAlphabetRec();

    alphabetMap = oAlphabet->getAlphabetMap();
    // This has to be set before a space is prepended
    alphabetSize = alphabetMap.size();

    // Place a space at the start of the string so that pin
    // numbers need not be zero based.
    alphabetMap.prepend(" ");
    alphabetName = oAlphabet->getAlphabetName();

}


Steckerboard::~Steckerboard()
{

}


bool Steckerboard::addStecker(QString from, QString to)
{
    bool result = true;

    if (from == to)
    {
        result = false;
        qDebug("Cannot add stecker [%s, %s] - Characters are the same",
                from.toStdString().data(),
                to.toStdString().data());
    }

    bool fromInUse = isCharInUse(from);
    bool toInUse = isCharInUse(to);

    if (fromInUse || toInUse)
    {
        result = false;
        qDebug("Cannot add stecker [%s, %s] %s %s",
                from.toStdString().data(),
                to.toStdString().data(),
                fromInUse ? QString("[%1] in use").arg(from).toStdString().data() : "",
                toInUse ? QString("[%1] in use").arg(to).toStdString().data() : "");
    }
    else
    {
        map.insert(from, to);
    }

    return result;
}


bool Steckerboard::delStecker(QString steckerChar)
{
    if (! isValidChar(steckerChar))
    {
        return false;
    }

    QString value =  map.value(steckerChar, "NOT_FOUND");
    if (value != "NOT_FOUND")
    {
        map.remove(steckerChar);
        return true;
    }

    // Make this call second 'cos its slower than map.value
    QString key = map.key(steckerChar, "NOT_FOUND");
    if (key != "NOT_FOUND")
    {
        map.remove(key);
        return true;
    }


    return false;
}


QString Steckerboard::mapStecker(QString charIn)
{
    QString charOut = QString("[%1] not found - Steckerboard charOut not assigned").
                            arg(charIn);


    if (! isValidChar(charIn))
    {
        qDebug("[%s] is not in alphabet [%s]",
                charIn.toStdString().data(),
                alphabetName.toStdString().data());

        return "";
    }

    QString value =  map.value(charIn, "NOT_FOUND");
    if (value != "NOT_FOUND")
    {
        return value;
    }

    // Make this call second 'cos its slower than map.value
    QString key = map.key(charIn, "NOT_FOUND");
    if (key != "NOT_FOUND")
    {
        return key;
    }

    // No stecker mapping found - return input key
    charOut = charIn;

    return charOut;
}


bool Steckerboard::isValidChar(QString keyIn)
{
    if (keyIn.size() != 1)
    {
        qDebug("Input string must be a single char - passed [%s]",
                keyIn.toStdString().data());

        return false;
    }

    if (alphabetMap.indexOf(keyIn, 0, Qt::CaseSensitive) == -1)
    {
        qDebug("Input key [%s] not found in alphabet [%s]",
                keyIn.toStdString().data(),
                alphabetName.toStdString().data());
        return false;
    }

    return true;
}


bool Steckerboard::isCharInUse(QString keyIn)
{
    bool inUse = false;

    if (isValidChar(keyIn))
    {
        if (! (map.value(keyIn, "NOT_FOUND") == "NOT_FOUND"))
        {
            inUse = true;
        }
        else if (! (map.key(keyIn, "NOT_FOUND") == "NOT_FOUND"))
        {
            inUse = true;
        }
    }

    return inUse;
}



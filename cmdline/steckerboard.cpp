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

#include "steckerboard.h"

Steckerboard::Steckerboard(QString alphabetName, QObject *parent) :
    QObject(parent)
{
    edb = EnigmaDatabase::getInstance();

    map.clear();

    recAlphabet = edb->getAlphabet(alphabetName);

    alphabetMap = recAlphabet.value("alphabet").toString();
    // This has to be set before a space is prepended
    alphabetSize = alphabetMap.size();

    // Place a space at the start of the string so that pin
    // numbers need not be zero based.
    alphabetMap.prepend(" ");
    alphabetName = recAlphabet.value("name").toString();

}


Steckerboard::~Steckerboard()
{

}


bool Steckerboard::addStecker(QString from, QString to)
{
    qDebug("Steckerboard::addStecker(QString from, QString to)");
    bool result = true;

    if (from == to)
    {
        result = false;
        QString msg = QString("Cannot add stecker [%1, %2] - Characters are the same").
                        arg(from).
                        arg(to);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"
        throw EnigmaException(msg.toAscii().data(), __FILE__, __LINE__);
#pragma GCC diagnostic pop
    }

    bool fromInUse = isCharInUse(from);
    bool toInUse = isCharInUse(to);

    if (fromInUse || toInUse)
    {
        result = false;
        QString msg = QString("Cannot add stecker [%1, %2] %3 %4").
                        arg(from).
                        arg(to).
                        arg(fromInUse ? QString("[%1] in use").arg(from) : "").
                        arg(toInUse ? QString("[%1] in use").arg(to) : "");
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"
        throw EnigmaException(msg.toAscii().data(), __FILE__, __LINE__);
#pragma GCC diagnostic pop
    }
    else
    {
        map.insert(from, to);
    }

    return result;
}


bool Steckerboard::delStecker(QString steckerChar)
{
    qDebug("Steckerboard::delStecker(QString steckerChar)");

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
    qDebug("Steckerboard::map(QString charIn)");
    QString charOut = QString("[%1] not found - Steckerboard charOut not assigned").
                            arg(charIn);


    if (! isValidChar(charIn))
    {
        QString msg = QString("[%1] is not in alphabet [%2]").
                        arg(charIn).
                        arg(alphabetName);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"
        throw EnigmaException(msg.toAscii().data(), __FILE__, __LINE__);
#pragma GCC diagnostic pop

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
    qDebug("Steckerboard::isValidChar(QString char)");

    if (keyIn.size() != 1)
    {
        QString msg = QString("Input string must be a single char - passed [%1]").
                arg(keyIn);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"
        throw EnigmaException(msg.toAscii().data(), __FILE__, __LINE__);
#pragma GCC diagnostic pop

        return false;
    }

    if (alphabetMap.indexOf(keyIn, 0, Qt::CaseSensitive) == -1)
    {
        QString msg = QString("Input key [%1] not found in alphabet [%2]").
                arg(keyIn).
                arg(alphabetName);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"
        throw EnigmaException(msg.toAscii().data(), __FILE__, __LINE__);
#pragma GCC diagnostic pop

        return false;
    }

    return true;
}


bool Steckerboard::isCharInUse(QString keyIn)
{
    qDebug("Steckerboard::isCharInUse(QString char)");
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



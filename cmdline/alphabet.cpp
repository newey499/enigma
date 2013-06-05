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

#include "alphabet.h"

Alphabet::Alphabet(QObject *parent) :
    ComponentBase(parent)
{
    commonConstructor(AlphabetData(this).getEmptyAlphabet());
}


Alphabet::Alphabet(QString alphabetName, QObject *parent) :
    ComponentBase(parent)
{
    commonConstructor(AlphabetData(this).getAlphabet(alphabetName));
}


Alphabet::Alphabet(int id, QObject *parent) :
    ComponentBase(parent)
{
    commonConstructor(AlphabetData(this).getAlphabet(id));
}


Alphabet::~Alphabet()
{

}


void Alphabet::commonConstructor(QSqlRecord recAlphabet)
{
    id = recAlphabet.value("id").toInt();
    alphabetName = recAlphabet.value("name").toString();
    alphabetMap = recAlphabet.value("alphabet").toString();
    alphabetSize = alphabetMap.size();
    this->recAlphabet = recAlphabet;
}

int Alphabet::getId()
{
    return id;
}

QString Alphabet::getAlphabetName()
{
    return alphabetName;
}

QString Alphabet::getAlphabetMap()
{
    return alphabetMap;
}

int Alphabet::getAlphabetSize()
{
    return alphabetSize;
}

QSqlRecord Alphabet::getAlphabetRec()
{
    return recAlphabet;
}

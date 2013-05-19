/************************************************************************
Copyright Chris Newey 2013

enigmasim@hotmail.com

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

#include "rotor.h"

Rotor::Rotor(QObject *parent) :
    QObject(parent)
{

    edb = EnigmaDatabase::getInstance();

    recRotor = edb->getRotor("NOMAP");

    recAlphabet = edb->getAlphabet(recRotor.value("alphabetid").toInt());

    qDebug("rotor [%s] alphabet [%s]",
           recRotor.value("name").toString().toAscii().data(),
           recAlphabet.value("name").toString().toAscii().data());

    sanityCheck();

}


Rotor::~Rotor()
{

}


bool Rotor::sanityCheck()
{
    bool result = true;

    QString alphabet = recAlphabet.value("alphabet").toString();
    QString rotor = recRotor.value("pinright").toString();

// Disable deprecated conversion from string constant to char *
// when instantiating EnigmaException object
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"

    if (alphabet.size() != rotor.size())
    {
        QString tmp = QString("Rotor: alphabet lengths do not match alphabet [%1] rotor [%2]").
                                arg(recAlphabet.value("name").toString()).
                                arg(recRotor.value("name").toString());
        result = false;
        throw EnigmaException(tmp.toAscii().data(), __FILE__ , __LINE__);
    }

    for (int i = 0; i < alphabet.count(); i++)
    {
        if (! rotor.contains(alphabet.at(i), Qt::CaseSensitive))
        {

            QString tmp = QString("Alphabet character [%1] not found in rotor definition [%2]").
                                    arg(alphabet.at(i)).
                                    arg(recRotor.value("name").toString());
            result = false;
            throw EnigmaException(tmp.toAscii().data(), __FILE__ , __LINE__);
        }
    }

    for (int i = 0; i < rotor.count(); i++)
    {
        if (! alphabet.contains(rotor.at(i), Qt::CaseSensitive))
        {

            QString tmp = QString("Rotor character [%1] not found in Alphabet definition [%2]").
                                    arg(rotor.at(i)).
                                    arg(recAlphabet.value("name").toString());
            result = false;
            throw EnigmaException(tmp.toAscii().data(), __FILE__ , __LINE__);
        }
    }

#pragma GCC diagnostic pop

    return result;
}

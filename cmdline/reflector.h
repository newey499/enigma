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

#ifndef REFLECTOR_H
#define REFLECTOR_H


#include <QObject>
#include <QPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

#include "globals.h"
#include "genlib.h"
#include "enigmaexception.h"
#include "enigmadatabase.h"
#include "alphabet.h"
#include "reflectordata.h"

class Reflector : public QObject
{
    Q_OBJECT

public:

    explicit Reflector(QString reflectorName, QObject *parent = 0);
    ~Reflector();

    virtual int map(int pinIn);

signals:


public slots:



protected:

    QPointer<Alphabet> oAlphabet;

    QSqlRecord recReflector;
    QSqlRecord recAlphabet;

    int alphabetSize;

    QString alphabetMap;
    QString alphabetName;
    QString reflectorMap;
    QString reflectorName;

    virtual bool sanityCheck();
    virtual bool isValidPinNo(int pinNo);
    virtual int getAlphabetSize();

private:

};

#endif // REFLECTOR_H

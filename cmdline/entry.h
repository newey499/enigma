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


#ifndef ENTRY_H
#define ENTRY_H

#include <QMap>
#include <QObject>
#include <QPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

#include "componentbase.h"
#include "globals.h"
#include "genlib.h"
#include "enigmaexception.h"
#include "enigmadatabase.h"
#include "alphabet.h"
#include "entrydata.h"

class Entry : public ComponentBase
{
    Q_OBJECT

public:

    explicit Entry(QString entryName, QObject *parent = 0);
    explicit Entry(int entryId, QObject *parent = 0);

    ~Entry();

    virtual int mapCharToPin(QString keyIn);
    virtual QString mapPinToChar(int pinIn);

    virtual QString getId();

signals:

public slots:


protected:

    QPointer<Alphabet> oAlphabet;

    QSqlRecord recEntry;
    QSqlRecord recAlphabet;

    int alphabetSize;

    QString alphabetMap;
    QString alphabetName;
    QString entryMap;
    QString entryName;

    virtual void commonConstructor();

    virtual bool sanityCheck();
    virtual bool isValidPinNo(int pinNo);
    virtual bool isValidKey(QString keyIn);

    virtual int getAlphabetSize();

private:



};

#endif // ENTRY_H

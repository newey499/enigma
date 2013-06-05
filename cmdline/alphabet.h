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

#ifndef ALPHABET_H
#define ALPHABET_H

#include <QObject>
#include <QPointer>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QStringList>
#include <QVariant>

#include "enigmaexception.h"
#include "globals.h"
#include "genlib.h"
#include "componentbase.h"
#include "alphabetdata.h"

class Alphabet : public ComponentBase
{
    Q_OBJECT

public:

    explicit Alphabet(QObject *parent = 0);
    explicit Alphabet(QString alphabetName, QObject *parent = 0);
    explicit Alphabet(int id, QObject *parent = 0);

    ~Alphabet();

    virtual int getId();
    virtual QString getAlphabetName();
    virtual QString getAlphabetMap();
    virtual int getAlphabetSize();

signals:

public slots:


protected:

    QSqlRecord recAlphabet;

    int id;
    QString alphabetName;
    QString alphabetMap;
    int alphabetSize;

    virtual void commonConstructor(QSqlRecord recAlphabet);

private:


};

#endif // ALPHABET_H

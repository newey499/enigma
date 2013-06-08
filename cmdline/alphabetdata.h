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

#ifndef ALPHABETDATA_H
#define ALPHABETDATA_H

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QVariant>

#include "genlib.h"
#include "globals.h"
#include "componentbase.h"
#include "enigmadatabase.h"
#include "enigmaexception.h"

class AlphabetData : public ComponentBase
{
    Q_OBJECT

public:

    const static int MIN_ALPHABET_LENGTH;
    const static int MIN_ALPHABET_NAME_LENGTH;

    explicit AlphabetData(QObject *parent = 0);
    ~AlphabetData();

    virtual bool setId(int id);
    virtual bool setName(QString name);
    virtual bool setAlphabet(QString alphabet);

    virtual QSqlRecord getEmptyAlphabet();
    virtual QSqlRecord getAlphabet();
    virtual QSqlRecord getAlphabet(QString alphabetName);
    virtual QSqlRecord getAlphabet(int id);
    virtual bool validateAlphabet(Globals::EDIT_MODE mode);

    virtual bool isUniqueAlphabetName(QSqlQuery qry, QString errMsg);
    virtual bool isAlphabetNameMinLengthOk(QString name);
    virtual bool isAlphabetMinLengthOk(QString alphabet);
    virtual bool isAlphabetInUse();
    virtual bool hasDuplicateChars(QString alphabet);

    virtual void displayRec();

    virtual bool writeRec(Globals::EDIT_MODE mode);

signals:

public slots:


protected:

    QSqlRecord rec;


private:

};

#endif // ALPHABETDATA_H

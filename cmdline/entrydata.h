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

#ifndef ENTRYDATA_H
#define ENTRYDATA_H

#include <QString>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QVariant>

#include "globals.h"
#include "genlib.h"
#include "componentbase.h"
#include "enigmadatabase.h"
#include "enigmaexception.h"
#include "wheellist.h"
#include "mysql.h"
#include "wheelbasedata.h"

class EntryData : public WheelBaseData
{
    Q_OBJECT

public:

    explicit EntryData(QObject *parent = 0);
    ~EntryData();

    // The id is the primary key and maintained internally
    //virtual bool setId(int id);
    virtual bool setName(QString name);
    virtual bool setAlphabetId(int id);
    virtual bool setType(QString type);
    virtual bool setPinRight(QString pinRight);
    // An entry wheel does not have notches
    //virtual bool setNotches(QString notches);

    virtual QSqlRecord getEmptyEntry();
    virtual QSqlRecord getEntry();
    virtual QSqlRecord getEntry(int id);
    virtual QSqlRecord getEntry(const QString &rotorName);
    virtual bool validateEntry(Globals::EDIT_MODE mode);

    virtual bool alphabetIdExists(int id);

    virtual bool writeRec(Globals::EDIT_MODE mode);

signals:

public slots:


protected:


private:

};

#endif // ENTRYDATA_H

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

#ifndef ROTORDATA_H
#define ROTORDATA_H

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QVariant>

#include "globals.h"
#include "componentbase.h"
#include "enigmadatabase.h"
#include "enigmaexception.h"
#include "wheelbasedata.h"

class RotorData : public WheelBaseData
{
    Q_OBJECT

public:

    explicit RotorData(QObject *parent = 0);
    ~RotorData();

    // The id is the primary key and maintained internally
    //virtual bool setId(int id);
    virtual bool setName(QString name);
    virtual bool setAlphabetId(int id);
    virtual bool setType(QString type);
    virtual bool setPinRight(QString pinRight);
    virtual bool setNotches(QString notches);

    virtual QSqlRecord getEmptyRotor();
    virtual QSqlRecord getRotor();
    virtual QSqlRecord getRotor(int id);
    virtual QSqlRecord getRotor(const QString &rotorName);
    virtual bool validateRotor(Globals::EDIT_MODE mode);

    virtual bool writeRec(Globals::EDIT_MODE mode);

signals:

public slots:


protected:


private:


};

#endif // ROTORDATA_H

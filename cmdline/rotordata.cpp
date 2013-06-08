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

#include "rotordata.h"

RotorData::RotorData(QObject *parent) :
    ComponentBase(parent)
{
    WheelBaseData::WHEEL_TYPE = "ROTOR";
}


RotorData::~RotorData()
{
}




QSqlRecord RotorData::getRotor(const QString &rotorName)
{
    QSqlRecord rec = EnigmaDatabase::getWheel(EnigmaDatabase::WHEEL_ROTOR, rotorName);

    return rec;
}


QSqlRecord RotorData::getRotor(int id)
{
    QSqlRecord rec = EnigmaDatabase::getWheel(id);

    return rec;
}


bool RotorData::validateRotor(Globals::EDIT_MODE mode, QSqlRecord rec)
{
    bool result = true;
    QSqlQuery qry;
    clearError();

    rec = rec;  // TODO debug temporary - remove copiler warning

    switch (mode)
    {
    case Globals::ROW_ADD :
        break;

    case Globals::ROW_EDIT :
        break;

    case Globals::ROW_DEL :
        break;

    default :
        result = false;
        QString msg = QString("");
        addError(msg);
        qDebug("[%d] is not an expected edit mode %s %d",
               mode,
               __FILE__,
               __LINE__);
        break;
    }

    return result;
}




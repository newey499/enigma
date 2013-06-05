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

#include "machinedata.h"

MachineData::MachineData(QObject *parent) :
    ComponentBase(parent)
{
}


MachineData::~MachineData()
{
}



QSqlRecord MachineData::getMachine(const QString &machineName)
{
    QSqlQuery qry;
    QSqlRecord rec;

    try
    {
        qry.prepare("SELECT id, name, steckerboard, "
                    "       rotorcount, entrylist, rotorlist, "
                    "       reflectorlist, alphabetid "
                    "FROM machine "
                    "WHERE name = :name");

        qry.bindValue(":name", machineName);

        rec = _getMachine(qry);

    }
    catch (EnigmaException &e)
    {
        QString msg = qry.lastError().text();
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"
        throw EnigmaException(msg.toAscii().data(),__FILE__, __LINE__);
#pragma GCC diagnostic pop
    }

    return rec;
}

QSqlRecord MachineData::getMachine(int id)
{
    QSqlQuery qry;
    QSqlRecord rec;

    try
    {
        qry.prepare("SELECT id, name, steckerboard, "
                    "       rotorcount, entrylist, rotorlist, "
                    "       reflectorlist, alphabetid "
                    "FROM machine "
                    "WHERE id = :id");

        qry.bindValue(":id", id);

        rec = _getMachine(qry);

    }
    catch (EnigmaException &e)
    {
        QString msg = qry.lastError().text();
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"
        throw EnigmaException(msg.toAscii().data(),__FILE__, __LINE__);
#pragma GCC diagnostic pop
    }

    return rec;
}



QSqlRecord MachineData::_getMachine(QSqlQuery qry)
{
    bool result = true;
    QSqlRecord rec;

    if (qry.exec())
    {
        if (qry.first())
        {
            rec = qry.record();
        }
        else
        {
            result = false;
        }
    }
    else
    {
        result = false;
    }

    if (! result)
    {
        QString msg = qry.lastError().text();
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wwrite-strings"
        throw EnigmaException(msg.toAscii().data(),__FILE__, __LINE__);
#pragma GCC diagnostic pop
    }

    return rec;
}



bool MachineData::validateMachine(Globals::EDIT_MODE mode, QSqlRecord rec)
{
    bool result = true;
    QSqlQuery qry;
    clearError();

    rec = rec;  // TODO debug temporariliy suppress unused parameter warning

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






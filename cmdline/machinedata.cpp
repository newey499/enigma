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
    steckerboardEnum << MySql::getEnum("enigma", "machine", "steckerboard");
    rec = getEmptyMachine();
}


MachineData::MachineData(int id, QObject *parent) :
    ComponentBase(parent)
{
    steckerboardEnum << MySql::getEnum("enigma", "machine", "steckerboard");
    rec = getMachine(id);
}

MachineData::MachineData(QString machineName, QObject *parent) :
    ComponentBase(parent)
{
    steckerboardEnum << MySql::getEnum("enigma", "machine", "steckerboard");
    rec = getMachine(machineName);
}


MachineData::~MachineData()
{
}


QSqlRecord MachineData::getEmptyMachine()
{
    rec.clear();

    rec.append(QSqlField("id", QVariant::Int));
    rec.append(QSqlField("name", QVariant::String));
    rec.append(QSqlField("steckerboard", QVariant::String));
    rec.append(QSqlField("rotorcount", QVariant::Int));
    rec.append(QSqlField("entrylist", QVariant::String));
    rec.append(QSqlField("rotorlist", QVariant::String));
    rec.append(QSqlField("reflectorlist", QVariant::String));
    rec.append(QSqlField("alphabetid", QVariant::Int));

    rec.setValue("id", Globals::NEW_ID);
    rec.setValue("name", "");
    rec.setValue("steckerboard", "");
    rec.setValue("rotorcount", -1);
    rec.setValue("entrylist", "");
    rec.setValue("rotorlist", "");
    rec.setValue("reflectorlist", "");
    rec.setValue("alphabetid", Globals::NEW_ID);

    return rec;
}


QSqlRecord MachineData::getMachine()
{
    return rec;
}


QSqlRecord MachineData::getMachine(int id)
{
    QSqlQuery qry;

    qry.prepare("SELECT id, name, steckerboard, "
                "       rotorcount, entrylist, rotorlist, "
                "       reflectorlist, alphabetid "
                "FROM machine "
                "WHERE id = :id");

    qry.bindValue(":id", id);

    if (GenLib::execQry(qry, true))
    {
        rec =  qry.record();
    }
    else
    {
        rec = getEmptyMachine();
    }

    return rec;
}



QSqlRecord MachineData::getMachine(const QString &machineName)
{
    QSqlQuery qry;

    qry.prepare("SELECT id, name, steckerboard, "
                "       rotorcount, entrylist, rotorlist, "
                "       reflectorlist, alphabetid "
                "FROM machine "
                "WHERE name = :name");

    qry.bindValue(":name", machineName);


    if (GenLib::execQry(qry, true))
    {
        rec = qry.record();
    }
    else
    {
        rec = getEmptyMachine();
    }

    return rec;
}



bool MachineData::isUniqueName(QSqlQuery qry, QString errMsg)
{
    bool result = true;

    if (GenLib::execQry(qry, true))
    {
        if (qry.record().value("recCount").toInt() == 0)
        {
            result = true;
        }
        else
        {
            result = false;
            addError(errMsg);
        }
    }
    else
    {
        result = false;
        addError(qry.lastError().text());
    }

    return result;
}


bool MachineData::isNameMinLengthOk(QString name)
{
    bool result = true;


    if (name.length() < AlphabetData::MIN_ALPHABET_NAME_LENGTH)
    {
        QString msg = QString("Name must contain at least %1 characters").
                        arg(AlphabetData::MIN_ALPHABET_NAME_LENGTH);
        //qDebug("%s", msg.toStdString().data());
        addError(msg);
        result = false;
    }

    return result;
}



bool MachineData::writeRec(Globals::EDIT_MODE mode)
{
    bool result = false;

    qDebug("MachineData::writeRec(Globals::EDIT_MODE mode)");
    mode = mode;  // remove compiler warning

    return result;
}


bool MachineData::setName(QString name)
{
    bool result = true;

    rec.setValue("name", name);

    return result;
}

bool MachineData::setAlphabetId(int id)
{
    bool result = true;

    rec.setValue("alphabetid", id);

    return result;
}


bool MachineData::setSteckerboard(QString steckerboard)
{
    bool result = true;

    rec.setValue("steckerboard", steckerboard);

    return result;
}


bool MachineData::setRotorCount(int rotorCount)
{
    bool result = true;

    rec.setValue("rotorcount", rotorCount);

    return result;
}



bool MachineData::validateMachine(Globals::EDIT_MODE mode)
{
    bool result = true;
    QSqlQuery qry;
    QString msg;
    clearError();

    qDebug("MachineData::validateMachine(Globals::EDIT_MODE mode)");

    switch (mode)
    {
    case Globals::ROW_ADD :

        // id must be -999
        // Must be a new record id
        if (rec.value("id").toInt() != Globals::NEW_ID)
        {
            msg = QString("Id must be [%1] not [%2] for a new record").
                            arg(Globals::NEW_ID).
                            arg(rec.value("id").toInt());
            addError(msg);
            result = false;
        }


        // name must not exist and may not be empty
        qry.prepare("select count(*) AS recCount "
                    "from rotor "
                    "where upper(name) = upper(:name)");
        qry.bindValue(":name", rec.value("name").toString());
        msg = QString("Name [%1] already exists").arg(rec.value("name").toString());
        if (! isUniqueName(qry, msg))
        {
            addError("isUniqueName returned false - name already exists");
            result = false;
        }

        // Name must have minimum length
        if (! isNameMinLengthOk(rec.value("name").toString()))
        {
            result = false;
        }

        // alphabet id must exist on alphabet table
        // alphabetid must not be a new record id
        if (rec.value("alphabetid").toInt() == Globals::NEW_ID)
        {
            msg = QString("Alphabet Id must not be a new record id [%1]").
                            arg(Globals::NEW_ID);
            addError(msg);
            result = false;
        }
        else
        {
            // alphabetid must exist on the alphabet table
            qry.prepare("select count(*) as countTot from alphabet where id = :id");
            qry.bindValue(":id", rec.value("alphabetid").toInt());
            if (GenLib::execQry(qry, true))
            {
                if (qry.record().value("countTot").toInt() == 0)
                {
                    msg = QString("Alphabet Id [%1] not found on alphabet table").
                                    arg(rec.value("alphabetid").toInt());
                    addError(msg);
                    result = false;
                }
            }
            else
            {
                addError(qry.lastError().text());
                result = false;
            }
        }

        // steckerboard enum values obtained from mysql information_schema
        if (! steckerboardEnum.contains(rec.value("steckerboard").toString(), Qt::CaseSensitive))
        {
            msg = QString("Stecker board must contain [%1] - current value [%2]").
                          arg(steckerboardEnum.join()).
                          arg(rec.value("steckerboard").toString());
            addError(msg);
            result = false;
        }

        // rotor count >= 0 - this emulation permits enigma configuration s with zero rotors
        if (rec.value("rotorcount").toInt() < 0)
        {
            msg = QString("Rotor Count must be >= 0 - current value [%1]").
                        arg(rec.value("rotorcount").toInt());
            addError(msg);
            result = false;
        }

        // entrylist must contain at least one valid entry wheel. Each
        // entry wheel in the list must be a valid entry wheel with the required alphabet id

        // rotorlist must contain at least as many entries as the rotor count. Each
        // rotor in the list must be a valid rotor with the required alphabet id

        // reflectorlist must contain at least one valid reflector wheel with the required
        // alphabet id

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



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
    WheelBaseData(parent)
{
    WheelBaseData::WHEEL_TYPE = "ROTOR";
    rec = getEmptyRotor();
}


RotorData::~RotorData()
{
}


QSqlRecord RotorData::getEmptyRotor()
{
    rec.clear();

    rec.append(QSqlField("id", QVariant::Int));
    rec.append(QSqlField("name", QVariant::String));
    rec.append(QSqlField("alphabetid", QVariant::Int));
    rec.append(QSqlField("type", QVariant::String));
    rec.append(QSqlField("pinright", QVariant::String));
    rec.append(QSqlField("notches", QVariant::String));

    rec.setValue("id", Globals::NEW_ID);
    rec.setValue("name", "");
    rec.setValue("alphabetid", Globals::NEW_ID);
    rec.setValue("type", "ROTOR");
    rec.setValue("pinright", "");
    rec.setValue("notches", "");

    return rec;
}


QSqlRecord RotorData::getRotor()
{
    return rec;
}


QSqlRecord RotorData::getRotor(const QString &rotorName)
{
    rec = EnigmaDatabase::getWheel(rotorName);

    return rec;
}


QSqlRecord RotorData::getRotor(int id)
{
    rec = EnigmaDatabase::getWheel(id);

    return rec;
}



/***************
// Id is primary key and maintained inside the object
bool RotorData::setId(int id)
{
    bool result = true;
    clearError();

    rec.setValue("id", id);

    return result;
}
*********************/

bool RotorData::setName(QString name)
{
    bool result = true;
    clearError();

    if (name.isEmpty())
    {
        addError("Cannot set name to empty string");
        result = false;
    }
    else
    {
        rec.setValue("name", name);
    }

    return result;
}


bool RotorData::setAlphabetId(int id)
{
    bool result = false;
    clearError();

    rec.setValue("alphabetid", id);
    result = true;

    /****************
    if (alphabetIdExists(id))
    {
        rec.setValue("alphabetid", id);
        result = true;
    }
    else
    {
        QString msg =
                QString("alphabet id [%1] not added - the alphabet id does not exist on the alphabet table").
                        arg(id);
        addError(msg);
        result = false;
    }
    ********************************/

    return result;
}



bool RotorData::setType(QString type)
{
    bool result = true;
    clearError();

    // Should always be "ROTOR"
    // rec.setValue("type", type);
    type = "ROTOR";
    rec.setValue("type", type);

    return result;
}


bool RotorData::setPinRight(QString pinRight)
{
    bool result = true;
    clearError();

    rec.setValue("pinright", pinRight);

    return result;
}


bool RotorData::setNotches(QString notches)
{
    bool result = true;
    clearError();

    rec.setValue("notches", notches);

    return result;
}


bool RotorData::validateRotor(Globals::EDIT_MODE mode)
{
    bool result = true;
    QString msg;
    QSqlQuery qry;
    clearError();

    switch (mode)
    {
    case Globals::ROW_ADD :

        // Type must be "ROTOR"
        if (rec.value("type").toString().compare("ROTOR") != 0)
        {
            msg = QString("type must be \"ROTOR\" not [%1]").
                            arg(rec.value("type").toString());
            addError(msg);
            result = false;
        }

        // Must be a new record id
        if (rec.value("id").toInt() != Globals::NEW_ID)
        {
            msg = QString("Id must be [%1] not [%2] for a new record").
                            arg(Globals::NEW_ID).
                            arg(rec.value("id").toInt());
            addError(msg);
            result = false;
        }

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

        if (! alphabetsSanityCheck())
        {
            result = false;
        }

        // Name must not exist
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

        // pinRight must have minimum length
        if (! isMinLengthOk(rec.value("pinright").toString(), "Rotor pinright"))
        {
            result = false;
        }

        // No Duplicate chars permitted
        if (hasDuplicateChars(rec.value("pinright").toString()))
        {
            result = false;
        }


        // Alphabet lengths must match
        if (! equalAlphabetLengths(rec.value("alphabetid").toInt(),
                                   rec.value("pinright").toString()))
        {
            result = false;
        }

        // Validate Notches - Rotor Wheels may have a notch
        if (! notchesCheck("ROTOR",
                           rec.value("notches").toString(),
                           rec.value("alphabetid").toInt()))
        {
            result = false;
        }
        else
        {
            // write cleaned up version of notches if
            // the notches passed validation
            WheelList wl("ROTOR", rec.value("notches").toString());
            setNotches(wl.join());
        }

        break;

    case Globals::ROW_EDIT :

        // Type must be "ROTOR"
        if (rec.value("type").toString().compare("ROTOR") != 0)
        {
            msg = QString("type must be \"ROTOR\" not [%1]").
                    arg(rec.value("type").toString());
            addError(msg);
            result = false;
        }

        // Must be an existing record id
        qry.prepare("select count(*) as recCount "
                    "from rotor "
                    "where id = :id");
        qry.bindValue(":id", rec.value("id").toInt());
        if (GenLib::execQry(qry, true))
        {
            if (qry.record().value("recCount").toInt() != 1)
            {
                msg = QString("[%1] occurences of id [%2] on rotor table").
                        arg(qry.record().value("recCount").toInt()).
                        arg(rec.value("id").toInt());
                result = false;
            }
        }
        else
        {
            addError(qry.lastError().text());
            result = false;
        }

        // alphabetid must not be a new record id
        if (rec.value("alphabetid").toInt() == Globals::NEW_ID)
        {
            msg = QString("Rotor Id must not be a new record id [%1]").
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

        if (! alphabetsSanityCheck())
        {
            result = false;
        }

        // Name must not exist except as for this id
        qry.prepare("select count(*) AS recCount "
                    "from rotor "
                    "where upper(name) = upper(:name) "
                    "and id <> :id");
        qry.bindValue(":name", rec.value("name").toString());
        qry.bindValue(":id", rec.value("id").toInt());
        msg = QString("Name [%1] already exists - id = [%2]").
                    arg(rec.value("name").toString()).
                    arg(rec.value("id").toInt());
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

        // pinRight must have minimum length
        if (! isMinLengthOk(rec.value("pinright").toString(), "Rotor pinright"))
        {
            result = false;
        }

        // Alphabet lengths must match
        if (! equalAlphabetLengths(rec.value("alphabetid").toInt(),
                                   rec.value("pinright").toString()))
        {
            result = false;
        }

        // No Duplicate chars permitted
        if (hasDuplicateChars(rec.value("pinright").toString()))
        {
            result = false;
        }

        // Validate Notches - Rotor Wheels may have a notch
        if (! notchesCheck("ROTOR",
                           rec.value("notches").toString(),
                           rec.value("alphabetid").toInt()))
        {
            result = false;
        }
        else
        {
            // write cleaned up version of notches if
            // the notches passed validation
            WheelList wl("ROTOR", rec.value("notches").toString());
            setNotches(wl.join());
        }

        break;

    case Globals::ROW_DEL :

        // Must be an existing record id
        qry.prepare("select count(*) as recCount "
                    "from rotor "
                    "where id = :id");
        qry.bindValue(":id", rec.value("id").toInt());
        if (GenLib::execQry(qry, true))
        {
            if (qry.record().value("recCount").toInt() != 1)
            {
                msg = QString("[%1] occurences of id [%2] on rotor table").
                        arg(qry.record().value("recCount").toInt()).
                        arg(rec.value("id").toInt());
                result = false;
            }
        }
        else
        {
            addError(qry.lastError().text());
            result = false;
        }

        // Item may not be in use ie it can't be in machine.entrylist,
        // machine.rotorlist or machine.reflectorlist
        if (isInUse(rec.value("id").toInt()))
        {
            msg = QString("cannot delete - Rotor Wheel [%1] is in use").
                    arg(rec.value("id").toInt());
            addError(msg);
            result = false;
        }

        if (result)
        {
            msg = QString("Deletion validation for Rotor wheel row id [%1] passed").
                                arg(rec.value("id").toInt());
            addError(msg);
        }
        else
        {
            msg = QString("Deletion validation for Rotor wheel row id [%1] failed").
                                arg(rec.value("id").toInt());
            addError(msg);
        }

        break;

    default :
        result = false;
        msg = QString("");
        addError(msg);
        qDebug("[%d] is not an expected edit mode %s %d",
               mode,
               __FILE__,
               __LINE__);
        break;
    }

    return result;
}



bool RotorData::writeRec(Globals::EDIT_MODE mode)
{
    bool result = true;
    QSqlQuery qry;
    QString msg;

    if (! validateRotor(mode))
    {
        // Don't touch the database if the validation fails
        addError("Validation failed - no changes made to database");
        result = false;
        return result;
    }

    //addError("Validation passed - Database writes disabled during validation testing");
    //return true;
    addError("Validation passed");

    switch (mode)
    {
        case Globals::ROW_ADD :
            qry.prepare("insert into rotor "
                        "(name, alphabetid, type, pinright, notches) "
                        "values "
                        "(:name, :alphabetid, :type, :pinright, :notches)");
            qry.bindValue(":name", rec.value("name").toString());
            qry.bindValue(":alphabetid", rec.value("alphabetid").toInt());
            qry.bindValue(":type", rec.value("type").toString());
            qry.bindValue(":pinright", rec.value("pinright").toString());
            qry.bindValue(":notches", rec.value("notches").toString());
            result = GenLib::execQry(qry, false);
            if (result)
            {
                qry.prepare("select LAST_INSERT_ID() as new_id");
                result = GenLib::execQry(qry, true);
                if (result)
                {
                    rec.setValue("id", qry.record().value("new_id").toInt());
                    msg = QString("rotor table row added - ROTOR wheel id = [%1]").
                            arg(rec.value("id").toInt());
                    addError(msg);
                    result = true;
                }
                else
                {
                    // The row has been written although for some
                    // reason we cannot get the new id
                    addError(qry.lastError().text());
                    result = true;
                }
            }
            else
            {
                addError(qry.lastError().text());
                result = false;
            }

            break;

        case Globals::ROW_EDIT :
            qry.prepare("update rotor "
                        "set "
                        "name = :name, "
                        "alphabetid = :alphabetid, "
                        "type = :type, "
                        "pinright = :pinright, "
                        "notches = notches "
                        "where id = :id");
            qry.bindValue(":name", rec.value("name").toString());
            qry.bindValue(":alphabetid", rec.value("alphabetid").toInt());
            qry.bindValue(":type", rec.value("type").toString());
            qry.bindValue(":pinright", rec.value("pinright").toString());
            qry.bindValue(":notches", rec.value("notches").toString());
            qry.bindValue(":id", rec.value("id").toInt());
            if ((result = GenLib::execQry(qry, false)))
            {
                msg = QString("rotor table row updated - ROTOR wheel id = [%1]").
                        arg(rec.value("id").toInt());
                addError(msg);
                result = true;
            }
            else
            {
                addError(qry.lastError().text());
                result = false;
            }
            break;


        case Globals::ROW_DEL :

            qry.prepare("delete from rotor "
                        "where id = :id");
            qry.bindValue(":id", rec.value("id"));
            if (GenLib::execQry(qry, false))
            {
                msg = QString("Deleting Rotor Wheel id = [%1]").
                        arg(rec.value("id").toInt());
                addError(msg);
                result = true;
            }
            else
            {
                addError(qry.lastError().text());
                result = false;
            }
            break;

        default :
            result = false;
            msg = QString("");
            addError(msg);
            qDebug("[%d] is not an expected edit mode %s %d",
                   mode,
                   __FILE__,
                   __LINE__);
            break;
    }

    return result;
}



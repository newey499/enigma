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

#include "alphabetdata.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

const int AlphabetData::MIN_ALPHABET_LENGTH = 3;  // Encrypt Morse ?? dot dash and a space <g>
const int AlphabetData::MIN_ALPHABET_NAME_LENGTH = 4;

AlphabetData::AlphabetData(QObject *parent) :
    ComponentBase(parent)
{
    getEmptyAlphabet();
}


AlphabetData::~AlphabetData()
{
}


QSqlRecord AlphabetData::getEmptyAlphabet()
{
    rec.clear();
    rec.insert(0, QSqlField("id", QVariant::Int));
    rec.insert(1, QSqlField("name", QVariant::String));
    rec.insert(2, QSqlField("alphabet", QVariant::String));

    rec.setValue("id", Globals::NEW_ID);
    rec.setValue("name", "");
    rec.setValue("alphabet", "");

    return rec;
}

QSqlRecord  AlphabetData::getAlphabet()
{
    return rec;
}

QSqlRecord AlphabetData::getAlphabet(QString alphabetName)
{
    QSqlQuery qry;

    qry.prepare("select "
                "id, name, alphabet "
                "from alphabet "
                "where name = :name");

    qry.bindValue(":name", alphabetName);

    if (qry.exec())
    {
        if (qry.first())
        {
            rec = qry.record();
        }
    }

    return rec;
}


QSqlRecord AlphabetData::getAlphabet(int id)
{
    QSqlQuery qry;

    qry.prepare("select "
                "id, name, alphabet "
                "from alphabet "
                "where id = :id");

    qry.bindValue(":id", id);

    if (qry.exec())
    {
        if (qry.first())
        {
            rec = qry.record();
        }
    }

    return rec;
}


bool AlphabetData::isUniqueAlphabetName(QSqlQuery qry, QString errMsg)
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


bool AlphabetData::isAlphabetMinLengthOk(QString alphabet)
{
    bool result = true;

    // alphabet must contain at least three characters
    if (alphabet.length() < AlphabetData::MIN_ALPHABET_LENGTH)
    {
        QString msg = QString("Alphabet must contain at least %1 characters").
                        arg(AlphabetData::MIN_ALPHABET_LENGTH);
        addError(msg);
        result = false;
    }

    return result;
}


bool AlphabetData::isAlphabetNameMinLengthOk(QString name)
{
    bool result = true;


    if (name.length() < AlphabetData::MIN_ALPHABET_NAME_LENGTH)
    {
        QString msg = QString("Alphabet Name must contain at least %1 characters").
                        arg(AlphabetData::MIN_ALPHABET_NAME_LENGTH);
        qDebug("alphabet name [%s] len %d min len %d",
               name.toAscii().data(),
               name.length(),
               AlphabetData::MIN_ALPHABET_NAME_LENGTH);
        addError(msg);
        result = false;
    }

    return result;
}

bool AlphabetData::hasDuplicateChars(QString alphabet)
{
    bool result = true;

    // the same character may not appear more than once in the alphabet
    if (GenLib::hasDuplicateChars(alphabet))
    {
        addError("Alphabet has duplicate characters");
        result = false;
    }

    return result;
}


bool AlphabetData::isAlphabetInUse()
{
    bool result = false;
    QSqlQuery qry;

    // Check machine table
    qry.prepare("select count(*) as recCount "
                "from machine "
                "where alphabetid = :alphabetid");
    qry.bindValue(":alphabetid", rec.value("id").toInt());
    if (GenLib::execQry(qry, true))
    {
        if (qry.record().value("recCount").toInt() > 0)
        {
            addError("Alphabet in use on machine table");
            result = true;
        }
    }
    else
    {
        // report sql error as result = true to prevent row deletion
        addError(qry.lastError().text());
        result = true;
    }

    // Check rotor table
    qry.prepare("select count(*) as recCount "
                "from rotor "
                "where alphabetid = :alphabetid");
    qry.bindValue(":alphabetid", rec.value("id").toInt());
    if (GenLib::execQry(qry, true))
    {
        if (qry.record().value("recCount").toInt() > 0)
        {
            addError("Alphabet in use on rotor table");
            result = true;
        }
    }
    else
    {
        // report sql error as result = true to prevent row deletion
        addError(qry.lastError().text());
        result = true;
    }

    // Can't delete the record if it doesn't exist
    qry.prepare("select count(*) as recCount "
                "from alphabet "
                "where id = :id");
    qry.bindValue(":id", rec.value("id").toInt());
    if (GenLib::execQry(qry, true))
    {
        if (qry.record().value("recCount").toInt() <= 0)
        {
            addError("Alphabet does not exist on alphabet table");
            result = true;
        }
    }
    else
    {
        // report sql error as result = true to prevent row deletion
        addError(qry.lastError().text());
        result = true;
    }

    return result;
}


void AlphabetData::displayRec()
{
    qDebug("id [%d]\nname [%s]\nalphabet [%s]",
           rec.value("id").toInt(),
           rec.value("name").toString().toAscii().data(),
           rec.value("alphabet").toString().toAscii().data());
}


bool AlphabetData::validateAlphabet(Globals::EDIT_MODE mode)
{
    bool result = true;
    QSqlQuery qry;
    QString msg;
    QString errMsg;
    clearError();

    switch (mode)
    {
    case Globals::ROW_ADD :

        // Must have a magic id indicating new row
        if (rec.value("id").toInt() != Globals::NEW_ID)
        {
            msg = QString("Attempt to Insert an existing row id [%1]").
                          arg(rec.value("id").toInt());
            addError(msg);
            result = false;
        }

        // name must be unique
        qry.prepare("select count(*) AS recCount "
                    "from alphabet "
                    "where upper(name) = upper(:name)");
        qry.bindValue(":name", rec.value("name").toString());
        errMsg = QString("Alphabet Name [%1] already exists").arg(rec.value("name").toString());
        result = isUniqueAlphabetName(qry, errMsg);

        if (! isAlphabetNameMinLengthOk(rec.value("name").toString()))
        {
            result = false;
        }

        if (! isAlphabetMinLengthOk(rec.value("alphabet").toString()))
        {
            result = false;
        }

        if (hasDuplicateChars(rec.value("alphabet").toString()))
        {
            result = false;
        }
        break;

    case Globals::ROW_EDIT :

        // Must not have a magic id indicating new row
        if (rec.value("id").toInt() == Globals::NEW_ID)
        {
            msg = QString("Attempt to Update a row id which has a marker for a new row[%1]").
                          arg(rec.value("id").toInt());
            addError(msg);
            result = false;
        }

        // name must be unique - for an edit this means the row can exist but not
        //                       with a different id primary key
        qry.prepare("select count(*) AS recCount "
                    "from alphabet "
                    "where upper(name) = upper(:name) and id <> :id");
        qry.bindValue(":name", rec.value("name").toString());
        qry.bindValue(":id", rec.value("id").toInt());
        errMsg = QString("Alphabet Name [%1] already exists").arg(rec.value("name").toString());
        result = isUniqueAlphabetName(qry, errMsg);

        if (! isAlphabetNameMinLengthOk(rec.value("name").toString()))
        {
            result = false;
        }

        if (! isAlphabetMinLengthOk(rec.value("alphabet").toString()))
        {
            result = false;
        }

        if (hasDuplicateChars(rec.value("alphabet").toString()))
        {
            result = false;
        }

        // Cannot change the alphabet if it is in use
        qry.prepare("select alphabet from alphabet where id = :id");
        qry.bindValue(":id", rec.value("id").toInt());
        if (GenLib::execQry(qry, true))
        {
            QString currentAlphabet = qry.record().value("alphabet").toString();
            QString newAlphabet = rec.value("alphabet").toString();
            bool alphabetChange = currentAlphabet.compare(newAlphabet, Qt::CaseSensitive) == 0;
            if (isAlphabetInUse() && alphabetChange)
            {
                msg = QString("Cannot change alphabet because it is in use");
                addError(msg);
                result = false;
            }
        }

        break;

    case Globals::ROW_DEL :

        // can't delete if the alphabet is in use
        if (isAlphabetInUse())
        {
            msg = QString("Cannot delete an alphabetrow which is in use id [%1]").
                    arg(rec.value("id").toInt());
            addError(msg);
            result = false;
        }

        // Must not have a magic id indicating new row
        if (rec.value("id").toInt() == Globals::NEW_ID)
        {
            msg = QString("Attempt to Delete a row which has a marker for a new row[%1]").
                                arg(rec.value("id").toInt());
            addError(msg);
            result = false;
        }

        if (result)
        {
            msg = QString("Deletion validation for alphabet row id [%1] passed").
                                arg(rec.value("id").toInt());
            addError(msg);
        }
        else
        {
            msg = QString("Deletion validation for alphabet row id [%1] failed").
                                arg(rec.value("id").toInt());
            addError(msg);
        }

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

    msg = lastError("\n");
    qDebug("Validation result [%s]\n%s",
           result ? "TRUE" : "FALSE",
           msg.toAscii().data());

    return result;
}


bool AlphabetData::writeRec(Globals::EDIT_MODE mode)
{
    qDebug("AlphabetData::writeRec");
    QString msg;
    bool result = false;
    QSqlQuery qry;

    displayRec();

    if (! validateAlphabet(mode))
    {
        // Don't touch the database if the validation fails
        return false;
    }

    switch (mode)
    {
    case Globals::ROW_ADD :
        qry.prepare("insert into alphabet(name, alphabet) "
                    "VALUES "
                    "(:name, :alphabet)");

        qry.bindValue(":name", rec.value("name").toString());
        qry.bindValue(":alphabet", rec.value("alphabet").toString());
        result = GenLib::execQry(qry, false);
        if (result)
        {
            qry.prepare("select LAST_INSERT_ID() as new_id");
            result = GenLib::execQry(qry, true);
            if (result)
            {
                int id = qry.record().value("new_id").toInt();
                rec.setValue("id", id);
                msg = QString("New Alphabet added id [%1]").arg(id);
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
        qry.prepare("update alphabet "
                    "SET "
                    "name = :name, "
                    "alphabet = :alphabet "
                    "WHERE id = :id");
        qry.bindValue(":id", rec.value("id"));
        qry.bindValue(":name", rec.value("name"));
        qry.bindValue(":alphabet", rec.value("alphabet"));
        if (GenLib::execQry(qry, false))
        {
            msg = QString("alphabet table row updated - id = [%1]").
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

        qry.prepare("delete from alphabet "
                    "where id = :id");
        qry.bindValue(":id", rec.value("id"));
        if (GenLib::execQry(qry, false))
        {
            msg = QString("Deleting Alphabet id = [%1]").
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
        QString msg = QString("");
        addError(msg);
        qDebug("[%d] is not an expected edit mode %s %d",
               mode,
               __FILE__,
               __LINE__);
        break;

    }

    this->displayRec();

    return result;
}


bool AlphabetData::setId(int id)
{
    bool result = true;

    rec.setValue("id", id);

    return result;
}

bool AlphabetData::setName(QString name)
{
    bool result = true;

    rec.setValue("name", name);

    return result;
}

bool AlphabetData::setAlphabet(QString alphabet)
{
    bool result = true;

    rec.setValue("alphabet", alphabet);

    return result;
}


#pragma GCC diagnostic pop

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

const int AlphabetData::MIN_ALPHABET_LENGTH = 4;

AlphabetData::AlphabetData(QObject *parent) :
    ComponentBase(parent)
{
}


AlphabetData::~AlphabetData()
{
}



QSqlRecord AlphabetData::getAlphabet(QString alphabetName)
{
    QSqlQuery qry;
    QSqlRecord rec;

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
    QSqlRecord rec;

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


bool AlphabetData::isAlphabetInUse(QSqlRecord rec)
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




bool AlphabetData::validateAlphabet(Globals::EDIT_MODE mode, QSqlRecord rec)
{
    bool result = true;
    QSqlQuery qry;
    QString errMsg;
    clearError();

    switch (mode)
    {
    case Globals::ROW_ADD :
        // name must be unique
        qry.prepare("select count(*) AS recCount "
                    "from alphabet "
                    "where upper(name) = upper(:name)");
        qry.bindValue(":name", rec.value("name").toString());
        errMsg = QString("Alphabet Name [%1] already exists").arg(rec.value("name").toString());
        result = isUniqueAlphabetName(qry, errMsg);

        if (! isAlphabetMinLengthOk(rec.value("alphabet").toString()))
        {
            result = false;
        }

        if (! hasDuplicateChars(rec.value("alphabet").toString()))
        {
            result = false;
        }
        break;

    case Globals::ROW_EDIT :
        // name must be unique - for an edit this means the row can exist but not
        //                       with a different id primary key
        qry.prepare("select count(*) AS recCount "
                    "from alphabet "
                    "where upper(name) = upper(:name) and id <> :id");
        qry.bindValue(":name", rec.value("name").toString());
        qry.bindValue(":id", rec.value("id").toInt());
        errMsg = QString("Alphabet Name [%1] already exists").arg(rec.value("name").toString());
        result = isUniqueAlphabetName(qry, errMsg);

        if (! isAlphabetMinLengthOk(rec.value("alphabet").toString()))
        {
            result = false;
        }

        if (! hasDuplicateChars(rec.value("alphabet").toString()))
        {
            result = false;
        }


        break;

    case Globals::ROW_DEL :
        // can't delete if the alphabet is in use
        result = isAlphabetInUse(rec);

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

    QString msg = lastError("\n");
    qDebug("Validation result [%s]\n%s",
           result ? "TRUE" : "FALSE",
           msg.toAscii().data());

    return result;
}

#pragma GCC diagnostic pop

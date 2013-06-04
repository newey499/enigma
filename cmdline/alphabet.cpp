#include "alphabet.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

Alphabet::Alphabet(QObject *parent) :
    ComponentBase(parent)
{
}


Alphabet::~Alphabet()
{

}


QSqlRecord Alphabet::getAlphabet(const QString &alphabetName)
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


QSqlRecord Alphabet::getAlphabet(int id)
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


bool Alphabet::validateAlphabetName(QSqlQuery &qry, QString name, QString msg)
{
    bool result = true;

    if (qry.exec())
    {
        if (qry.first())
        {
            if (qry.record().value("recCount").toInt() == 0)
            {
                result = true;
            }
            else
            {
                result = false;
                addError(
                    QString("Alphabet [%1] already exists").arg(name));
            }

        }
        else
        {
            result = false;
            addError(qry.lastError().text());
        }
    }
    else
    {
        result = false;
        addError(qry.lastError().text());
    }

    return result;
}



bool Alphabet::validateAlphabet(EDIT_MODE mode, QSqlRecord rec)
{
    bool result = true;
    QSqlQuery qry;
    clearError();

    switch (mode)
    {
    case ROW_ADD :
        // name must be unique
        qry.prepare("select count(*) AS recCount "
                    "from alphabet "
                    "where upper(name) = upper(:name)");
        qry.bindValue(":name", rec.value("name").toString());
        result = validateAlphabetName(qry,
                                      rec.value("name").toString(),
                                      "Name already exists");

        // alphabet must contain at least three characters
        if (rec.value("alphabet").toString().length() <= 3)
        {
            addError("Alphabet must contain at least three characters");
            result = false;
        }
        // the same character may not appear more than once in the alphabet
        if (GenLib::hasDuplicateChars(rec.value("alphabet").toString()))
        {
            addError("Alphabet has duplicate characters");
            result = false;
        }

        break;

    case ROW_EDIT :
        // name must be unique
        qry.prepare("select count(*) AS recCount "
                    "from alphabet "
                    "where upper(name) = upper(:name) and id <> :id");
        qry.bindValue(":name", rec.value("name").toString());
        qry.bindValue(":id", rec.value("id").toInt());
        result = validateAlphabetName(qry,
                                      rec.value("name").toString(),
                                      "Name already exists");
        // alphabet must contain at least three characters
        if (rec.value("alphabet").toString().length() <= 3)
        {
            addError("Alphabet must contain at least three characters");
            result = false;
        }

        // the same character may not appear more than once in the alphabet
        if (GenLib::hasDuplicateChars(rec.value("alphabet").toString()))
        {
            addError("Alphabet has duplicate characters");
            result = false;
        }

        break;

    case ROW_DEL :
        // can't delete if the alphabet is in use

        // Check machine table
        qry.prepare("select count(*) as recCount "
                    "from machine "
                    "where alphabetid = :alphabetid");
        qry.bindValue(":alphabetid", rec.value("id").toInt());
        if (qry.exec())
        {
            if (qry.first())
            {
                if (qry.record().value("recCount").toInt() > 0)
                {
                    addError("Alphabet in use on machine table");
                    result = false;
                }

            }
            else
            {
                addError(qry.lastError().text());
                result = false;
            }
        }
        else
        {
            addError(qry.lastError().text());
            result = false;
        }

        // Check rotor table
        qry.prepare("select count(*) as recCount "
                    "from rotor "
                    "where alphabetid = :alphabetid");
        qry.bindValue(":alphabetid", rec.value("id").toInt());
        if (qry.exec())
        {
            if (qry.first())
            {
                if (qry.record().value("recCount").toInt() > 0)
                {
                    addError("Alphabet in use on rotor table");
                    result = false;
                }

            }
            else
            {
                addError(qry.lastError().text());
                result = false;
            }
        }
        else
        {
            addError(qry.lastError().text());
            result = false;
        }


        // Can't delete the record if it doesn't exist
        qry.prepare("select count(*) as recCount "
                    "from alphabet "
                    "where id = :id");
        qry.bindValue(":id", rec.value("id").toInt());
        if (qry.exec())
        {
            if (qry.first())
            {
                if (qry.record().value("recCount").toInt() <= 0)
                {
                    addError("Alphabet row does not exist");
                    result = false;
                }

            }
            else
            {
                addError(qry.lastError().text());
                result = false;
            }
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

    QString msg = lastError("\n");
    qDebug("Validation result [%s]\n%s",
           result ? "TRUE" : "FALSE",
           msg.toAscii().data());

    return result;
}

#pragma GCC diagnostic pop

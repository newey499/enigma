#include "wheelbasedata.h"

QString WheelBaseData::WHEEL_TYPE = "";


WheelBaseData::WheelBaseData(QObject *parent) :
    ComponentBase(parent)
{
}


bool WheelBaseData::isUniqueName(QSqlQuery qry, QString errMsg)
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


bool WheelBaseData::isMinLengthOk(QString alphabet, QString name)
{
    bool result = true;

    // alphabet must contain at least three characters
    if (alphabet.length() < AlphabetData::MIN_ALPHABET_LENGTH)
    {
        QString msg = QString("%1 must contain at least %2 characters").
                        arg(name).
                        arg(AlphabetData::MIN_ALPHABET_LENGTH);
        addError(msg);
        result = false;
    }

    return result;
}


bool WheelBaseData::isNameMinLengthOk(QString name)
{
    bool result = true;


    if (name.length() < AlphabetData::MIN_ALPHABET_NAME_LENGTH)
    {
        QString msg = QString("Name must contain at least %1 characters").
                        arg(AlphabetData::MIN_ALPHABET_NAME_LENGTH);
        qDebug("%s", msg.toAscii().data());
        addError(msg);
        result = false;
    }

    return result;
}

bool WheelBaseData::hasDuplicateChars(QString alphabet)
{
    bool result = false;
    QString msg;

    // the same character may not appear more than once in the alphabet
    if (GenLib::hasDuplicateChars(alphabet))
    {
        msg = QString("[%1] has duplicate characters").arg(alphabet);
        addError(msg);
        result = true;
    }

    return result;
}


bool WheelBaseData::isInUse(int id)
{
    bool result = false;
    QString msg;
    QSqlQuery qry;

    qry.prepare("select "
                "id, name, steckerboard, rotorcount, "
                "entrylist, rotorlist, reflectorlist, alphabetid "
                "from machine ");
    if (! qry.exec())
    {
        return true;  // fake a problem even though the query has failed
    }

    QStringList lst;
    QString strId = QString("%1").arg(id);
    while (qry.next())
    {
        lst.clear();
        lst.append(qry.record().value("entrylist").toString().split(WheelList::SEPERATOR));
        if (checkIsInUse(qry.record().value("name").toString(), lst, "entrylist", strId))
        {
            result = true;
        }
        lst.clear();
        lst.append(qry.record().value("rotorlist").toString().split(WheelList::SEPERATOR));
        if (checkIsInUse(qry.record().value("name").toString(), lst, "rotorlist", strId))
        {
            result = true;
        }
        lst.clear();
        lst.append(qry.record().value("reflectorlist").toString().split(WheelList::SEPERATOR));
        if (checkIsInUse(qry.record().value("name").toString(), lst, "reflectorlist", strId))
        {
            result = true;
        }

    }
    /**************************
      TODO Debug need check that the current id in't in use in a
      entry list, rotor list or reflector list in the machine table
      ********************************/
    // Check machine table


    return result;
}

bool WheelBaseData::checkIsInUse(QString machineName, QStringList lst, QString colName, QString strId)
{
    bool result = false;
    QString msg;

    for (int i = 0; i < lst.count(); i++)
    {
        if (lst.at(i).compare(strId) == 0)
        {
            msg = QString("id [%1] is in use in %2 of machine [%3]").
                    arg(strId).
                    arg(colName).
                    arg(machineName);
            addError(msg);
            result = true;
        }
    }
    return result;
}


bool WheelBaseData::alphabetsSanityCheck()
{
    bool result = true;
    QSqlQuery qry;

    addError("bool WheelBaseData::alphabetsSanityCheck()");

    qry.prepare("select name, alphabet "
                "from alphabet "
                "where id = :id");
    qry.bindValue(":id", rec.value("alphabetid").toInt());

    if (GenLib::execQry(qry, true))
    {
        QString alphabetName = qry.record().value("name").toString();
        QString alphabet = qry.record().value("alphabet").toString();

        qDebug("[%s] [%s] [%s] [%s]",
               alphabetName.toAscii().data(),
               alphabet.toAscii().data(),
               rec.value("name").toString().toAscii().data(),
               rec.value("pinright").toString().toAscii().data());
        if (! alphabetSanityCheck(alphabetName, alphabet,
                                  rec.value("name").toString(),
                                  rec.value("pinright").toString()))
        {
            //addError("alphabets do not match");
            result = false;
        }

    }
    else
    {
        addError(qry.lastError().text());
        result = false;
    }

    return result;
}


bool WheelBaseData::alphabetDuplicateCheck(QString alphabetName, QString alphabet)
{
    bool result = true;

    for (int i = 0; i < alphabet.count(); i++)
    {
        if (alphabet.count(alphabet.at(i), Qt::CaseSensitive ) != 1)
        {
            QString tmp = QString("character [%1] found [%2] time(s) in definition [%3] - should only be one").
                            arg(alphabet.at(i)).
                            arg(alphabet.count(alphabet.at(i), Qt::CaseSensitive )).
                            arg(alphabetName);
            addError(tmp);
            result = false;
        }
    }

    return result;
}



bool WheelBaseData::alphabetSanityCheck(QString alphabetName, QString alphabet,
                                 QString mappingName, QString mapping)
{
    bool result = true;
    QString msg;

    if (! alphabetDuplicateCheck(alphabetName, alphabet))
    {
        result = false;
    }
    if (! alphabetDuplicateCheck(mappingName, mapping))
    {
        result = false;
    }

    msg = QString("alphabetSanityCheck length check [%1] [%2] [%3] [%4]").
            arg(alphabetName).
            arg(alphabet.length()).
            arg(mappingName).
            arg(mapping.length());
    if (alphabet.size() != mapping.size())
    {
        QString tmp = QString("mapping: alphabet lengths do not match alphabet [%1] mapping [%2]").
                                arg(alphabetName).
                                arg(mappingName);
        addError(tmp);
        result = false;
    }

    for (int i = 0; i < alphabet.count(); i++)
    {
        if (! mapping.contains(alphabet.at(i), Qt::CaseSensitive))
        {

            QString tmp = QString("Alphabet character [%1] not found in mapping definition [%2]").
                                    arg(alphabet.at(i)).
                                    arg(mappingName);
            addError(tmp);
            result = false;
        }
    }

    for (int i = 0; i < mapping.count(); i++)
    {
        if (! alphabet.contains(mapping.at(i), Qt::CaseSensitive))
        {

            QString tmp = QString("mapping character [%1] not found in Alphabet definition [%2]").
                                    arg(mapping.at(i)).
                                    arg(alphabetName);
            addError(tmp);
            result = false;
        }
    }

    return result;
}


// Alphabet lengths must match
bool WheelBaseData::equalAlphabetLengths(int alphabetId, QString pinRight)
{
    bool result = false;
    QSqlQuery qry;
    QString msg;

    qry.prepare("select alphabet from alphabet where id = :id");
    qry.bindValue(":id", alphabetId);

    if (GenLib::execQry(qry, true))
    {
        QString alphabet = qry.record().value("alphabet").toString();
        if (alphabet.length() == pinRight.length())
        {
            result = true;
        }
        else
        {
            msg = QString("alphabet lengths do not match [%1] alphabet id [%2]").
                    arg(pinRight).
                    arg(alphabetId);
            addError(msg);
            result = false;
        }
    }
    else
    {
        addError(qry.lastError().text());
        result = false;
    }

    return result;
}



bool WheelBaseData::notchesCheck(QString notches, int alphabetId)
{
    bool result = true;
    QSqlQuery qry;
    QString msg;
    QString name, alphabet;

    addError("WheelBaseData::notchesCheck");

    if (notches.isEmpty())
    {
        //addError("No notches to check");
        return true;
    }

    qry.prepare("select name, alphabet from alphabet where id = :id");
    qry.bindValue(":id", alphabetId);

    if (GenLib::execQry(qry, true))
    {
        name = qry.record().value("name").toString();
        alphabet = qry.record().value("alphabet").toString();
        WheelList wl(notches);
        msg = QString("Notches [%1]").arg(notches);
        addError(msg);
        for (int i = 0; i < wl.count(); i++)
        {
            if (wl.at(i).length() != 1)
            {
                msg = QString("Each notch setting must be one char only [%1] is invalid").
                        arg(wl.at(i));
                addError(msg);
                result = false;
            }
            else
            {
                if (! alphabet.contains(wl.at(i), Qt::CaseSensitive))
                {
                    msg = QString("Notch char [%1] is not in alphabet [%2] [%3]").
                            arg(wl.at(i)).
                            arg(name).
                            arg(alphabet);
                    addError(msg);
                    result = false;
                }
            }
        }

    }
    else
    {
        addError(qry.lastError().text());
        result = false;
    }


    return result;
}

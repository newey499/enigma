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

#include "enigmadatabase.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

bool EnigmaDatabase::instanceFlag = false;
QPointer<EnigmaDatabase> EnigmaDatabase::singleton = NULL;

const char * EnigmaDatabase::WHEEL_ROTOR     = "ROTOR";
const char * EnigmaDatabase::WHEEL_ENTRY     = "ENTRY";
const char * EnigmaDatabase::WHEEL_REFLECTOR = "REFLECTOR";


EnigmaDatabase::EnigmaDatabase(QObject *parent) :
    QObject(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");
    db.setDatabaseName("enigma");
    db.setUserName("cdn");
    db.setPassword("charlton");

    db.open();

    bool ok = db.open();

    // Check driver opens database
    qDebug("enigma database driver [%s] opened [%s]",
                 db.driverName().toAscii().data(),
                 (ok ? "Yes": "No") );

}


EnigmaDatabase::~EnigmaDatabase()
{
    instanceFlag = false;
}


EnigmaDatabase * EnigmaDatabase::getInstance()
{
    if(! instanceFlag)
    {
        singleton = new EnigmaDatabase();
        instanceFlag = true;
    }

    return singleton;
}


QSqlRecord EnigmaDatabase::getRotor(const QString &rotorName)
{
    QSqlRecord rec = getWheel(EnigmaDatabase::WHEEL_ROTOR, rotorName);

    return rec;
}


QSqlRecord EnigmaDatabase::getRotor(int id)
{
    QSqlRecord rec = getWheel(id);

    return rec;
}


QSqlRecord EnigmaDatabase::getEntry(const QString &rotorName)
{
    QSqlRecord rec = getWheel(EnigmaDatabase::WHEEL_ENTRY, rotorName);

    return rec;
}


QSqlRecord EnigmaDatabase::getEntry(int id)
{
    QSqlRecord rec = getWheel(id);

    return rec;
}


QSqlRecord EnigmaDatabase::getReflector(const QString &rotorName)
{
    QSqlRecord rec = getWheel(EnigmaDatabase::WHEEL_REFLECTOR, rotorName);

    return rec;
}


QSqlRecord EnigmaDatabase::getReflector(int id)
{
    QSqlRecord rec = getWheel(id);

    return rec;
}


QSqlRecord EnigmaDatabase::getAlphabet(const QString &alphabetName)
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


QSqlRecord EnigmaDatabase::getAlphabet(int id)
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

QSqlRecord EnigmaDatabase::getWheel(QString type, QString name)
{
    QSqlQuery qry;
    QSqlRecord rec;
    bool result = true;

    qry.prepare("select "
                "id, name, alphabetid, type, pinright, notches "
                "from rotor "
                "where type = :type and name = :name");

    qry.bindValue(":type", type);
    qry.bindValue(":name", name);

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

QSqlRecord EnigmaDatabase::getWheel(int id)
{
    QSqlQuery qry;
    QSqlRecord rec;
    bool result = true;

    qry.prepare("select "
                "id, name, alphabetid, type, pinright, notches "
                "from rotor "
                "where id = :id");

    qry.bindValue(":id", id);

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



QSqlRecord EnigmaDatabase::getMachine(const QString &machineName)
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

QSqlRecord EnigmaDatabase::getMachine(int id)
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



QSqlRecord EnigmaDatabase::_getMachine(QSqlQuery qry)
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


void EnigmaDatabase::addValidationError(QString err)
{
    validErrorList.append(err);
}


void EnigmaDatabase::addValidationError(QStringList err)
{
    for (int i = 0; i < err.count(); i++)
    {
        addValidationError(err.at(i));
    }
}


QStringList EnigmaDatabase::lastValidationError()
{
    return validErrorList;
}


bool EnigmaDatabase::validateEntry(EDIT_MODE mode, QSqlRecord rec)
{
    bool result = true;
    validErrorList.clear();

    switch (mode)
    {
    case ROW_ADD :
        break;

    case ROW_EDIT :
        break;

    case ROW_DEL :
        break;

    default :
        result = false;
        QString msg = QString("");
        validErrorList.append(msg);
        qDebug("[%d] is not an expected edit mode %s %d",
               mode,
               __FILE__,
               __LINE__);
        break;
    }

    return result;
}


bool EnigmaDatabase::validateRotor(EDIT_MODE mode, QSqlRecord rec)
{
    bool result = true;
    validErrorList.clear();

    switch (mode)
    {
    case ROW_ADD :
        break;

    case ROW_EDIT :
        break;

    case ROW_DEL :
        break;

    default :
        result = false;
        QString msg = QString("");
        validErrorList.append(msg);
        qDebug("[%d] is not an expected edit mode %s %d",
               mode,
               __FILE__,
               __LINE__);
        break;
    }

    return result;
}


bool EnigmaDatabase::validateReflector(EDIT_MODE mode, QSqlRecord rec)
{
    bool result = true;
    validErrorList.clear();

    switch (mode)
    {
    case ROW_ADD :
        break;

    case ROW_EDIT :
        break;

    case ROW_DEL :
        break;

    default :
        result = false;
        QString msg = QString("");
        validErrorList.append(msg);
        qDebug("[%d] is not an expected edit mode %s %d",
               mode,
               __FILE__,
               __LINE__);
        break;
    }

    return result;
}


bool EnigmaDatabase::validateAlphabet(EDIT_MODE mode, QSqlRecord rec)
{
    bool result = true;
    validErrorList.clear();

    switch (mode)
    {
    case ROW_ADD :
        // name must be unique
        // alphabet must contain at least three characters
        // the same character may not appear more than once in the alphabet
        break;

    case ROW_EDIT :
        // name must be unique
        // alphabet must contain at least three characters
        // the same character may not appear more than once in the alphabet
        break;

    case ROW_DEL :
        // can't delete if the alphabet is in use
        break;

    default :
        result = false;
        QString msg = QString("");
        validErrorList.append(msg);
        qDebug("[%d] is not an expected edit mode %s %d",
               mode,
               __FILE__,
               __LINE__);
        break;
    }

    return result;
}


bool EnigmaDatabase::validateMachine(EDIT_MODE mode, QSqlRecord rec)
{
    bool result = true;
    validErrorList.clear();

    switch (mode)
    {
    case ROW_ADD :
        break;

    case ROW_EDIT :
        break;

    case ROW_DEL :
        break;

    default :
        result = false;
        QString msg = QString("");
        validErrorList.append(msg);
        qDebug("[%d] is not an expected edit mode %s %d",
               mode,
               __FILE__,
               __LINE__);
        break;
    }

    return result;
}



#pragma GCC diagnostic pop


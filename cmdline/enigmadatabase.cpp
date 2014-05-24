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
    ComponentBase(parent)
{

    globals = Globals::getInstance();

    //QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db = QSqlDatabase::addDatabase(globals->db_driver());

    // hostname not needed for ODBC
    db.setHostName("127.0.0.1");
    db.setDatabaseName(globals->db_databasename());
    db.setUserName(globals->db_username());
    db.setPassword(globals->db_password());

    db.open();

    bool ok = db.open();

    // Check driver opens database
    qDebug("enigma database driver [%s] opened [%s]",
                 db.driverName().toStdString().data(),
                 (ok ? "Yes": "No") );

    globals->display();
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


QSqlRecord EnigmaDatabase::getWheel(QString name)
{
    QSqlQuery qry;
    QSqlRecord rec;
    bool result = true;

    qry.prepare("select "
                "id, name, alphabetid, type, pinright, notches "
                "from rotor "
                "where name = :name");

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
        throw EnigmaException(msg.toStdString(),__FILE__, __LINE__);
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
        throw EnigmaException(msg.toStdString().data(),__FILE__, __LINE__);
#pragma GCC diagnostic pop
    }

    return rec;
}

QStringList EnigmaDatabase::getDriverList()
{
    return QSqlDatabase::drivers();
}


#pragma GCC diagnostic pop


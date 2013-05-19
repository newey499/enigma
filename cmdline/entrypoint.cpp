/************************************************************************
Copyright Chris Newey 2013

enigmasim@hotmail.com

This file is part of enigma.

Enigma is distributed under the terms of the GNU General Public License

Enigma is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Qiptables is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Qiptables.  If not, see <http://www.gnu.org/licenses/>.

***************************************************************************/

#include "entrypoint.h"

EntryPoint::EntryPoint(QObject *parent) :
    QObject(parent)
{
}


int EntryPoint::exec()
{
    int result = 0;

    qDebug("EntryPoint::exec()");

    try
    {
        edb = EnigmaDatabase::getInstance();

        QSqlQuery qry("select * from rotor");
        QSqlRecord rec;

        while (qry.next())
        {
            rec = qry.record();
            qDebug("%s", rec.value("name").toString().toAscii().data());
        }

        Rotor rotor;

    }
    catch (EnigmaException &e)
    {
        qDebug("\n%s", e.what().toAscii().data());
        qApp->exit(1); // exit with error exit code
    }

    return result;
}

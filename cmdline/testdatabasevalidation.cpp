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

#include "testdatabasevalidation.h"

TestDatabaseValidation::TestDatabaseValidation(QObject *parent) :
    QObject(parent)
{
    edb = EnigmaDatabase::getInstance();
    qDebug("TestDatabaseValidation::TestDatabaseValidation(QObject *parent)");
}




QString TestDatabaseValidation::displayTestRec(QString msg, QSqlRecord rec)
{


    msg = msg.prepend("\n===================================\n");
    //qDebug("%s", msg.toAscii().data());
    for (int i = 0; i < rec.count(); i++)
    {
        msg = msg.append("\n%1 : %2").
                arg(rec.fieldName(i).toAscii().data()).
                arg(rec.value(i).toString().toAscii().data());
    }

    qDebug("%s", msg.toAscii().data());

    return msg;
}


void TestDatabaseValidation::testAlphabetValidation()
{
    qDebug("TestDatabaseValidation::testAlphabetValidation()");
    QSqlRecord rec;
    QSqlField fld;

    rec.append(QSqlField("id", QVariant::Int));
    rec.append(QSqlField("name", QVariant::String));
    rec.append(QSqlField("alphabet", QVariant::String));

    // Base record values
    rec.setValue("id", 1);
    rec.setValue("name", "default");
    rec.setValue("alphabet", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    displayTestRec("SUCCESS: Expected fail Add alphabet Rec name exists", rec);
    AlphabetData().validateAlphabet(Globals::ROW_ADD, rec);

    rec.setValue("alphabet", "AABCDEFGHIJKLMNOPQRSTUVWXYZ");
    displayTestRec("SUCCESS: Expected fail Add alphabet duplicate char(s) in alphabet", rec);
    AlphabetData().validateAlphabet(Globals::ROW_ADD, rec);

    rec.setValue("alphabet", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    displayTestRec("SUCCESS: Expected validation pass Edit alphabet ", rec);
    AlphabetData().validateAlphabet(Globals::ROW_EDIT, rec);

    rec.setValue("id", 3);
    displayTestRec("SUCCESS: Expected fail Edit alphabet alphabet name already exists", rec);
    AlphabetData().validateAlphabet(Globals::ROW_EDIT, rec);


    rec.setValue("id", 1);
    displayTestRec("SUCCESS: Expected fail Delete alphabet alphabet in use", rec);
    AlphabetData().validateAlphabet(Globals::ROW_DEL, rec);

}



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
    //qDebug("%s", msg.toStdString().data());
    for (int i = 0; i < rec.count(); i++)
    {
        msg = msg.append("\n%1 : %2").
                arg(rec.fieldName(i).toStdString().data()).
                arg(rec.value(i).toString().toStdString().data());
    }

    qDebug("%s", msg.toStdString().data());

    return msg;
}


void TestDatabaseValidation::testAlphabetValidation()
{
    qDebug("TestDatabaseValidation::testAlphabetValidation()");
    AlphabetData ad(this);


    // Base record values
    ad.setId(1);
    ad.setName("default");
    ad.setAlphabet("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    displayTestRec("SUCCESS: Expected fail Add alphabet Rec name exists", ad.getAlphabet());
    ad.validateAlphabet(Globals::ROW_ADD);

    ad.setAlphabet("AAAAAABCDEFGHIJKLMNOPQRSTUVWXYZ");
    displayTestRec("SUCCESS: Expected fail Add alphabet duplicate char(s) in alphabet", ad.getAlphabet());
    ad.validateAlphabet(Globals::ROW_ADD);

    ad.setAlphabet("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    displayTestRec("SUCCESS: Expected validation pass Edit alphabet ", ad.getAlphabet());
    ad.validateAlphabet(Globals::ROW_EDIT);

    ad.setId(3);
    displayTestRec("SUCCESS: Expected fail Edit alphabet alphabet name already exists", ad.getAlphabet());
    ad.validateAlphabet(Globals::ROW_EDIT);


    ad.setId(1);
    displayTestRec("SUCCESS: Expected fail Delete alphabet alphabet in use", ad.getAlphabet());
    ad.validateAlphabet(Globals::ROW_DEL);

}



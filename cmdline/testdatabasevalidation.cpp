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
    edb->validateAlphabet(EnigmaDatabase::ROW_ADD, rec);

    rec.setValue("alphabet", "AABCDEFGHIJKLMNOPQRSTUVWXYZ");
    displayTestRec("SUCCESS: Expected fail Add alphabet duplicate char(s) in alphabet", rec);
    edb->validateAlphabet(EnigmaDatabase::ROW_ADD, rec);

    rec.setValue("alphabet", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    displayTestRec("SUCCESS: Expected validation pass Edit alphabet ", rec);
    edb->validateAlphabet(EnigmaDatabase::ROW_EDIT, rec);

    rec.setValue("id", 3);
    displayTestRec("SUCCESS: Expected fail Edit alphabet alphabet name already exists", rec);
    edb->validateAlphabet(EnigmaDatabase::ROW_EDIT, rec);


    rec.setValue("id", 1);
    displayTestRec("SUCCESS: Expected fail Delete alphabet alphabet in use", rec);
    edb->validateAlphabet(EnigmaDatabase::ROW_DEL, rec);

}



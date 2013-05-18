#include "enigmadatabase.h"


bool EnigmaDatabase::instanceFlag = false;
QPointer<EnigmaDatabase> EnigmaDatabase::singleton = NULL;


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
    QSqlQuery qry;
    QSqlRecord rec;

    qry.prepare("select "
                "id, name, alphabetid, type, pinright, notches "
                "from rotor "
                "where name = :name");

    qry.bindValue(":name", rotorName);

    if (qry.exec())
    {
        if (qry.first())
        {
            rec = qry.record();
        }
    }

    return rec;
}


QSqlRecord EnigmaDatabase::getRotor(int id)
{
    QSqlQuery qry;
    QSqlRecord rec;

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
    }

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


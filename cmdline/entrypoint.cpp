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

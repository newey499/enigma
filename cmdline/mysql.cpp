#include "mysql.h"

MySql::MySql(QObject *parent) :
    QObject(parent)
{
}


QStringList MySql::getEnum(QString databaseName, QString tableName, QString columnName)
{
    QSqlQuery qry;
    QStringList result;

    qry.prepare("SELECT SUBSTRING(COLUMN_TYPE,5) AS enumField "
                "FROM information_schema.COLUMNS "
                "WHERE TABLE_SCHEMA  = :databaseName "
                "    AND TABLE_NAME  = :tableName "
                "    AND COLUMN_NAME = :colName ");

    qry.bindValue(":databaseName", databaseName);
    qry.bindValue(":tableName",    tableName);
    qry.bindValue(":columnName",   columnName);

    if (GenLib::execQry(qry, true))
    {
        QString res = qry.record().value("enumField").toString();
        res = res.replace("(", "", Qt::CaseSensitive);
        res = res.replace(")", "", Qt::CaseSensitive);
        result = res.split(",");
    }

    return result;
}

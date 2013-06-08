#ifndef MYSQL_H
#define MYSQL_H

#include <QObject>
#include <QString>
#include <QStringList>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>

#include "genlib.h"

class MySql : public QObject
{
    Q_OBJECT
public:

    explicit MySql(QObject *parent = 0);

    static QStringList getEnum(QString databaseName, QString tableName, QString colName);

signals:

public slots:

};

#endif // MYSQL_H

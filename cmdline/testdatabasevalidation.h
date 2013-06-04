#ifndef TESTDATABASEVALIDATION_H
#define TESTDATABASEVALIDATION_H

#include "globals.h"
#include "enigmadatabase.h"
#include "alphabet.h"

class TestDatabaseValidation : public QObject
{
    Q_OBJECT

public:

    explicit TestDatabaseValidation(QObject *parent = 0);

    void testAlphabetValidation();

signals:


public slots:


protected:

    QPointer<EnigmaDatabase> edb;


    virtual QString displayTestRec(QString msg, QSqlRecord rec);


};

#endif // TESTDATABASEVALIDATION_H

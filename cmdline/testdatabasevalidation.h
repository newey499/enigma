#ifndef TESTDATABASEVALIDATION_H
#define TESTDATABASEVALIDATION_H

#include "enigmadatabase.h"

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

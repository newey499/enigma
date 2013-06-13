#ifndef WHEELBASE_H
#define WHEELBASE_H

#include <QString>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QVariant>

#include "componentbase.h"
#include "alphabetdata.h"
#include "wheellist.h"

class WheelBaseData : public ComponentBase
{
    Q_OBJECT

public:

    static QString WHEEL_TYPE;

    explicit WheelBaseData(QObject *parent = 0);

    virtual bool isUniqueName(QSqlQuery qry, QString errMsg);
    virtual bool isNameMinLengthOk(QString name);
    virtual bool isMinLengthOk(QString alphabet, QString name);
    virtual bool isInUse(int id);
    virtual bool hasDuplicateChars(QString alphabet);
    virtual bool alphabetsSanityCheck();
    virtual bool equalAlphabetLengths(int alphabetId, QString pinRight);

    virtual bool alphabetSanityCheck(QString alphabetName, QString alphabet,
                                     QString mappingName, QString mapping);
    virtual bool alphabetDuplicateCheck(QString alphabetName, QString alphabet);
    virtual bool notchesCheck(QString notches, int alphabetId);


signals:


public slots:


protected:

    bool checkIsInUse(QString machineName, QStringList lst, QString colName, QString strId);


private:



};

#endif // WHEELBASE_H

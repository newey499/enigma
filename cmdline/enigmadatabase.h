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

#ifndef ENIGMADATABASE_H
#define ENIGMADATABASE_H

#include <QPointer>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QStringList>
#include <QVariant>

#include "enigmaexception.h"

class EnigmaDatabase : public QObject
{
    Q_OBJECT

public:

    typedef enum
    {
        ROW_ADD, ROW_EDIT, ROW_DEL
    }
    EDIT_MODE;

    static const char * WHEEL_ROTOR;
    static const char * WHEEL_ENTRY;
    static const char * WHEEL_REFLECTOR;

    static EnigmaDatabase *getInstance();

    ~EnigmaDatabase();

    virtual QSqlRecord getRotor(int id);
    virtual QSqlRecord getRotor(const QString &rotorName);
    virtual bool validateRotor(EDIT_MODE mode, QSqlRecord rec);

    virtual QSqlRecord getEntry(int id);
    virtual QSqlRecord getEntry(const QString &rotorName);
    virtual bool validateEntry(EDIT_MODE mode, QSqlRecord rec);

    virtual QSqlRecord getReflector(int id);
    virtual QSqlRecord getReflector(const QString &rotorName);
    virtual bool validateReflector(EDIT_MODE mode, QSqlRecord rec);

    virtual QSqlRecord getAlphabet(const QString &alphabetName);
    virtual QSqlRecord getAlphabet(int id);
    virtual bool validateAlphabet(EDIT_MODE mode, QSqlRecord rec);

    virtual QSqlRecord getMachine(const QString &machineName);
    virtual QSqlRecord getMachine(int id);
    virtual bool validateMachine(EDIT_MODE mode, QSqlRecord rec);

    virtual QStringList lastValidationError();

signals:

public slots:


protected:

    QSqlDatabase db;
    QStringList validErrorList;

    QSqlRecord getWheel(QString type, QString name);
    QSqlRecord getWheel(int id);

    virtual bool hasDuplicateChars(QString str);

    virtual QSqlRecord _getMachine(QSqlQuery qry);

    virtual void addValidationError(QString err);
    virtual void addValidationError(QStringList err);


    bool validateAlphabetName(QSqlQuery &qry, QString name, QString msg);

private:

    static bool instanceFlag;
    static QPointer<EnigmaDatabase> singleton;

    explicit EnigmaDatabase(QObject *parent = 0);


};

#endif // ENIGMADATABASE_H

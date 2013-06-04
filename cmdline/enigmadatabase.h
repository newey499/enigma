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
#include "globals.h"
#include "componentbase.h"

class EnigmaDatabase : public ComponentBase
{
    Q_OBJECT

public:

    static const char * WHEEL_ROTOR;
    static const char * WHEEL_ENTRY;
    static const char * WHEEL_REFLECTOR;

    static EnigmaDatabase *getInstance();
    ~EnigmaDatabase();

    static QSqlRecord getWheel(QString type, QString name);
    static QSqlRecord getWheel(int id);


signals:

public slots:


protected:

    QSqlDatabase db;


private:

    static bool instanceFlag;
    static QPointer<EnigmaDatabase> singleton;

    explicit EnigmaDatabase(QObject *parent = 0);


};

#endif // ENIGMADATABASE_H

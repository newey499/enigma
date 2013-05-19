/************************************************************************
Copyright Chris Newey 2013

enigmasim@hotmail.com

This file is part of enigma.

Enigma is distributed under the terms of the GNU General Public License

Enigma is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Qiptables is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Qiptables.  If not, see <http://www.gnu.org/licenses/>.

***************************************************************************/

#ifndef ENIGMADATABASE_H
#define ENIGMADATABASE_H

#include <QPointer>
#include <QSqlDatabase>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QVariant>



class EnigmaDatabase : public QObject
{
    Q_OBJECT

public:

    static EnigmaDatabase *getInstance();

    ~EnigmaDatabase();

    QSqlRecord getRotor(const QString &rotorName);
    QSqlRecord getRotor(int id);

    QSqlRecord getAlphabet(const QString &alphabetName);
    QSqlRecord getAlphabet(int id);

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

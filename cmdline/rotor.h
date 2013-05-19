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

#ifndef ROTOR_H
#define ROTOR_H

#include <QHash>
#include <QObject>
#include <QPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

#include "enigmaexception.h"
#include "enigmadatabase.h"

class Rotor : public QObject
{
    Q_OBJECT

public:

    explicit Rotor(QObject *parent = 0);

    ~Rotor();

signals:

public slots:

protected:

    QPointer<EnigmaDatabase> edb;

    QSqlRecord recRotor;
    QSqlRecord recAlphabet;
    QHash<QString, QString> map;

    bool sanityCheck();

private:

};

#endif // ROTOR_H

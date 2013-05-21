/************************************************************************
Copyright Chris Newey 2013

enigmasim@outlook.com

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

#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include <QCoreApplication>

#include <QObject>
#include <QPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>


#include "enigmadatabase.h"
#include "entry.h"
#include "rotor.h"
#include "reflector.h"
#include "keyboard.h"
#include "steckerboard.h"

class EntryPoint : public QObject
{
    Q_OBJECT

public:

    explicit EntryPoint(QObject *parent = 0);

    virtual int exec();

    virtual void testMapping();
    virtual void testReflector();
    virtual void testEntry();
    virtual void testKeyboard();
    virtual void testSteckerboard();

signals:

public slots:


protected:

    QPointer<EnigmaDatabase> edb;

private:


};

#endif // ENTRYPOINT_H

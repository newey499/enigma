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

#ifndef REFLECTORDATA_H
#define REFLECTORDATA_H

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QVariant>

#include "globals.h"
#include "componentbase.h"
#include "enigmadatabase.h"
#include "enigmaexception.h"

class ReflectorData : public ComponentBase
{
    Q_OBJECT

public:

    explicit ReflectorData(QObject *parent = 0);
    ~ReflectorData();

    virtual QSqlRecord getReflector(int id);
    virtual QSqlRecord getReflector(const QString &rotorName);
    virtual bool validateReflector(Globals::EDIT_MODE mode, QSqlRecord rec);

signals:

public slots:


protected:


private:


};

#endif // REFLECTORDATA_H

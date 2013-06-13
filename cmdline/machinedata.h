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

#ifndef MACHINEDATA_H
#define MACHINEDATA_H

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QVariant>

#include "genlib.h"
#include "globals.h"
#include "componentbase.h"
#include "enigmadatabase.h"
#include "enigmaexception.h"
#include "mysql.h"
#include "alphabetdata.h"
#include "wheellist.h"

class MachineData : public ComponentBase
{
    Q_OBJECT

public:

    explicit MachineData(QObject *parent = 0);
    ~MachineData();

    virtual bool setName(QString name);
    virtual bool setAlphabetId(int id);
    virtual bool setSteckerboard(QString steckerboard);
    virtual bool setRotorCount(int rotorCount);

    virtual bool isUniqueName(QSqlQuery qry, QString errMsg);
    virtual bool isNameMinLengthOk(QString name);

    virtual QSqlRecord getEmptyMachine();
    virtual QSqlRecord getMachine();
    virtual QSqlRecord getMachine(int id);
    virtual QSqlRecord getMachine(const QString &machineName);
    virtual bool validateMachine(Globals::EDIT_MODE mode);

    virtual bool writeRec(Globals::EDIT_MODE mode);

signals:

public slots:


protected:

    WheelList steckerboardEnum;


private:


};

#endif // MACHINEDATA_H

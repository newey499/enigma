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


#include "componentbase.h"

ComponentBase::ComponentBase(QObject *parent) :
    QObject(parent)
{
}


ComponentBase::~ComponentBase()
{
}


void ComponentBase::addError(QString err)
{
    errorList.append(err);
}


void ComponentBase::addError(QStringList err)
{
    for (int i = 0; i < err.count(); i++)
    {
        addError(err.at(i));
    }
}

QStringList ComponentBase::lastError()
{
    return errorList;
}

QString ComponentBase::lastError(QString seperator)
{
    return errorList.join(seperator);
}

void ComponentBase::clearError()
{
    errorList.clear();
}

QString ComponentBase::dispError(QString seperator)
{
    QString output = errorList.join(seperator);

    qDebug("%s", output.toStdString().data());
    return output;
}


void ComponentBase::dispRec()
{
    //QSqlRecord rec;
    qDebug("START:: WheelBaseData::dispRec()");
    for (int i = 0; i < rec.count(); i++)
    {
        qDebug("%s [%s]",
               rec.field(i).name().toStdString().data(),
               rec.field(i).value().toString().toStdString().data());
    }
    qDebug("FINISH:: WheelBaseData::dispRec()");
}

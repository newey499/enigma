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


#ifndef COMPONENTBASE_H
#define COMPONENTBASE_H

#include <QObject>
#include <QString>
#include <QStringList>

class ComponentBase : public QObject
{
    Q_OBJECT

public:

    explicit ComponentBase(QObject *parent = 0);
    ~ComponentBase();

    virtual QStringList lastError();
    virtual QString lastError(QString seperator = " ");
    virtual void addError(QString err);
    virtual void addError(QStringList err);
    virtual void clearError();

signals:

public slots:


protected:

    QStringList errorList;

private:


};

#endif // COMPONENTBASE_H

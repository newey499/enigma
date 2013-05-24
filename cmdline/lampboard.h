#ifndef LAMPBOARD_H
#define LAMPBOARD_H

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

#include <QMap>
#include <QObject>
#include <QPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

#include "genlib.h"
#include "enigmaexception.h"
#include "enigmadatabase.h"


class Lampboard : public QObject
{
    Q_OBJECT
public:

    explicit Lampboard(QString alphabetName, QObject *parent = 0);
    explicit Lampboard(int alphabetId, QObject *parent = 0);
    ~Lampboard();


    virtual void illuminate(QString charIn);

signals:

public slots:


protected:

    QPointer<EnigmaDatabase> edb;

    QSqlRecord recAlphabet;

    QString alphabetMap;
    QString alphabetName;
    int alphabetSize;

private:

};

#endif // LAMPBOARD_H

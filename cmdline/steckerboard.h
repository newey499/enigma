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

#ifndef STECKERBOARD_H
#define STECKERBOARD_H

#include <QMap>
#include <QObject>
#include <QPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

#include "genlib.h"
#include "enigmaexception.h"
#include "enigmadatabase.h"

class Steckerboard : public QObject
{
    Q_OBJECT
public:

    explicit Steckerboard(QString alphabetName, QObject *parent = 0);
    ~Steckerboard();

signals:

public slots:

    virtual bool addStecker(QString from, QString to);
    virtual bool delStecker(QString steckerChar);
    virtual QString mapStecker(QString charIn);


protected:

    QPointer<EnigmaDatabase> edb;

    QSqlRecord recAlphabet;

    int alphabetSize;

    QString alphabetMap;
    QString alphabetName;

    QMap<QString, QString> map;

    bool isValidChar(QString keyIn);
    bool isCharInUse(QString keyIn);

private:

};

#endif // STECKERBOARD_H

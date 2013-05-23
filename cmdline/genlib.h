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

#ifndef GENLIB_H
#define GENLIB_H

#include <QtDebug>
#include <QFile>
#include <QTextStream>

#include <QObject>
#include <QString>

#include "enigmaexception.h"

class GenLib : public QObject
{
    Q_OBJECT

public:

    explicit GenLib(QObject *parent = 0);
    ~GenLib();

    static bool alphabetSanityCheck(QString alphabetName, QString alphabet,
                                    QString mappingName, QString mapping);

    static bool alphabetDuplicateCheck(QString alphabetName, QString alphabet);

signals:


public slots:


protected:


private:


};

#endif // GENLIB_H

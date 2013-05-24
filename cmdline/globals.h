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

#ifndef GLOBALS_H
#define GLOBALS_H

#include <QObject>
#include <QString>

class Globals : public QObject
{
    Q_OBJECT
public:

    static const QString ORGANIZATION_NAME;
    static const QString APPLICATION_NAME;
    static const QString APPLICATION_VERSION;

    static const QString DB_DRIVER;
    static const QString DB_HOSTNAME;
    static const QString DB_DATABASENAME;
    static const QString DB_USERNAME;
    static const QString DB_PASSWORD;

    explicit Globals(QObject *parent = 0);

signals:

public slots:

};

#endif // GLOBALS_H

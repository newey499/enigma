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

#ifndef GENLIB_H
#define GENLIB_H

#ifdef BUILD_GUI
    #include <QApplication>
    #include <QWidget>
#else
    #include <QtCore/QCoreApplication>
#endif
#include <QtDebug>
#include <QFile>
#include <QTextStream>

#include <QObject>
#include <QString>
#include <QSqlQuery>


#include "globals.h"
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

    static bool hasDuplicateChars(QString str);

    static bool execQry(QSqlQuery &qry, bool moveFirst = false);

#ifdef BUILD_GUI
    /**
    \brief get pointer to top level widget using widget instance name

    The return pointer (if not null) has to be cast to the required widget type

    \return pointer to QWidget or 0 if not found.
      *****************************/
    static QWidget * getWidgetPointer(QString widgetObjectName);
#endif

signals:


public slots:


protected:


private:


};

#endif // GENLIB_H

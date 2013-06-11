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

#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QtDebug>
#include <QFile>
#include <QObject>
#include <QString>
#include <QTextStream>


class MessageHandler : public QObject
{
    Q_OBJECT
public:


    static QString logFile;
    static bool delLog;
    static bool writeLog;

    // The message handler has to be static to provide an address that QT can work with
    static void messageHandler(QtMsgType type, const char *msg);

    explicit MessageHandler(QString logFile, bool writeLogFile = true, QObject *parent = 0);

    bool deleteLogFile();

signals:

    void debugMsg(QString msg);

public slots:


protected:


private:

};

#endif // MESSAGEHANDLER_H

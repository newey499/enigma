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

#include "messagehandler.h"

QString MessageHandler::logFile = "qtlog.txt";
bool MessageHandler::delLog     = true;
bool MessageHandler::writeLog   = true;

MessageHandler::MessageHandler(QString logFileName, bool writeLogFile, QObject *parent) :
    QObject(parent)
{
    MessageHandler::logFile  = logFileName;
    MessageHandler::writeLog = writeLogFile;
}


bool MessageHandler::deleteLogFile()
{
    return QFile::remove(MessageHandler::logFile);
}


void MessageHandler::messageHandler(QtMsgType type, const char *msg)
{
    QString txt;
    switch (type)
    {
        case QtDebugMsg:
            txt = QString(msg).isEmpty() ? "" : QString("Debug: %1").arg(msg);
            break;
        case QtWarningMsg:
            txt = QString(msg).isEmpty() ? "" : QString("Warning: %1").arg(msg);
            break;
        case QtCriticalMsg:
            txt = QString(msg).isEmpty() ? "" : QString("Critical: %1").arg(msg);
            break;
        case QtFatalMsg:
            txt = QString(msg).isEmpty() ? "" : QString("Fatal: %1").arg(msg);
            break;
    }

    QString tmp = QString(msg);
    if (! tmp.isEmpty())
    {
        //emit debugMsg(tmp);
    }

    if (! txt.isEmpty())
    {
        if (MessageHandler::writeLog)
        {
            QFile outFile(MessageHandler::logFile);
            outFile.open(QIODevice::WriteOnly | QIODevice::Append);
            QTextStream ts(&outFile);
            ts << txt << endl;
        }
        fprintf(stdout, txt.append("\n").toStdString().data());
    }
}

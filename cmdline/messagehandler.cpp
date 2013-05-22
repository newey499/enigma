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
    QFile::remove(MessageHandler::logFile);
}


void MessageHandler::messageHandler(QtMsgType type, const char *msg)
{
    QString txt;
    switch (type) {
    case QtDebugMsg:
        txt = QString("Debug: %1").arg(msg);
        break;
    case QtWarningMsg:
        txt = QString("Warning: %1").arg(msg);
    break;
    case QtCriticalMsg:
        txt = QString("Critical: %1").arg(msg);
    break;
    case QtFatalMsg:
        txt = QString("Fatal: %1").arg(msg);
    break;
    }
    if (MessageHandler::writeLog)
    {
        QFile outFile(MessageHandler::logFile);
        outFile.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream ts(&outFile);
        ts << txt << endl;
    }
    fprintf(stdout, txt.append("\n").toAscii().data());
}

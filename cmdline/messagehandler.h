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

public slots:


protected:


private:

};

#endif // MESSAGEHANDLER_H

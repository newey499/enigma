#ifndef GUIMESSAGEHANDLER_H
#define GUIMESSAGEHANDLER_H

#include <qapplication.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <QObject>

#include "genlib.h"
#include "emitstring.h"

class GuiMessageHandler : public QObject
{
    Q_OBJECT
public:

    static QObject *formPtr;

    explicit GuiMessageHandler(QObject *parent = 0);

    static void guiMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

signals:

public slots:

};

#endif // GUIMESSAGEHANDLER_H

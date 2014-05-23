#include "guimessagehandler.h"

QObject * GuiMessageHandler::formPtr = 0;

GuiMessageHandler::GuiMessageHandler(QObject *parent) :
    QObject(parent)
{
    GuiMessageHandler::formPtr = parent;
}



void GuiMessageHandler::guiMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    EmitString es(GuiMessageHandler::formPtr);
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        es.slotEmitStr(QString("%1").arg(msg));
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        es.slotEmitStr(QString("%1").arg(msg));
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        es.slotEmitStr(QString("%1").arg(msg));
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        es.slotEmitStr(QString("%1").arg(msg));
        abort();
    }
}


#include "guimessagehandler.h"

QObject * GuiMessageHandler::formPtr = 0;

GuiMessageHandler::GuiMessageHandler(QObject *parent) :
    QObject(parent)
{
    GuiMessageHandler::formPtr = parent;
}



void GuiMessageHandler::guiMessageOutput(QtMsgType type, const char *msg)
{
    EmitString es(GuiMessageHandler::formPtr);

    es.slotEmitStr(QString("%1%2").arg(msg).arg("\n"));
    std::cerr << msg << std::endl;
}

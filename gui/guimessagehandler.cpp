#include "guimessagehandler.h"

QObject * GuiMessageHandler::formPtr = 0;

GuiMessageHandler::GuiMessageHandler(QObject *parent) :
    QObject(parent)
{
    GuiMessageHandler::formPtr = parent;
}


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void GuiMessageHandler::guiMessageOutput(QtMsgType type, const char *msg)
{
    EmitString es(GuiMessageHandler::formPtr);

    //es.slotEmitStr(QString("%1%2").arg(msg).arg("\n"));
    es.slotEmitStr(QString("%1").arg(msg));
    std::cerr << msg << std::endl;
}
#pragma GCC diagnostic pop

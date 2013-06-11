#include "emitstring.h"

EmitString::EmitString(QObject * formPtr, QObject *parent) :
    QObject(parent)
{
    this->formPtr = formPtr;
}


void EmitString::slotEmitStr(QString str)
{
    connect(this, SIGNAL(emitStr(QString)),
            formPtr, SLOT(slotAppendString(QString)));
    emit emitStr(str);
}


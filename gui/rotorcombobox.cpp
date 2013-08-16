#include "rotorcombobox.h"


RotorComboBox::RotorComboBox(int rotorPosition, QWidget *parent) :
    QComboBox(parent)
{
    this->rotorPosition = rotorPosition;
    connect(this, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(slotEmitRotorChanged()));
}

int RotorComboBox::getRotorPosition()
{
    return rotorPosition;
}


void RotorComboBox::contextMenuEvent(QContextMenuEvent *e)
{

    qDebug("RotorComboBox::contextMenuEvent(QContextMenuEvent *e)");
    if (e->reason() == QContextMenuEvent::Mouse)
    {

        e->accept();
    }
    else
    {
        e->ignore();
    }
}


void RotorComboBox::slotEmitRotorChanged()
{
    emit rotorChanged(this);
}

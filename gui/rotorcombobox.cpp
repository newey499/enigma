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

    RotorSetupDialog *dialog = new RotorSetupDialog(oRotor, getRotorPosition(), this);
    if (e->reason() == QContextMenuEvent::Mouse)
    {
        e->accept();
        dialog->exec();
    }
    else
    {
        e->ignore();
    }
    delete dialog;
}


void RotorComboBox::slotEmitRotorChanged()
{
    emit rotorChanged(this);
}


Rotor * RotorComboBox::getRotor()
{
    return oRotor;
}

void RotorComboBox::setRotor(Rotor *rotor)
{
    oRotor = rotor;
}

#ifndef ROTORCOMBOBOX_H
#define ROTORCOMBOBOX_H

#include <QComboBox>
#include <QContextMenuEvent>
#include "rotor.h"
#include "rotorsetupdialog.h"

class RotorComboBox : public QComboBox
{
    Q_OBJECT
public:


    explicit RotorComboBox(int rotorPosition, QWidget *parent = 0);

    int getRotorPosition();
    virtual Rotor * getRotor();
    virtual void setRotor(Rotor *rotor);


signals:

    void rotorChanged(RotorComboBox *);

public slots:

    virtual void slotEmitRotorChanged();

protected:

    int rotorPosition;
    Rotor *oRotor;

    virtual void contextMenuEvent(QContextMenuEvent *e);

private:

};

#endif // ROTORCOMBOBOX_H

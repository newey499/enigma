#ifndef ROTORSETUPDIALOG_H
#define ROTORSETUPDIALOG_H

#include <QDialog>
#include "rotor.h"

namespace Ui {
class RotorSetupDialog;
}

class RotorSetupDialog : public QDialog
{
    Q_OBJECT

public:

    explicit RotorSetupDialog(Rotor *oRotor, int rotorPosition, QWidget *parent = 0);
    ~RotorSetupDialog();

public slots:

    virtual void slotAccept();

protected:

    Rotor *oRotor;
    int rotorPosition;

    virtual void commonConstructor();

private:
    Ui::RotorSetupDialog *ui;
};

#endif // ROTORSETUPDIALOG_H

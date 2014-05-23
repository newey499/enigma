#ifndef FORMMACHINE_H
#define FORMMACHINE_H

#include "machine.h"
#include <QComboBox>
#include <QContextMenuEvent>
#include <QLabel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QWidget>

#include "genlib.h"
#include "rotorcombobox.h"
#include "entry.h"
#include "rotor.h"
#include "reflector.h"
#include "rotorsetupdialog.h"

namespace Ui {
class FormMachine;
}

class FormMachine : public QWidget
{
    Q_OBJECT

public:
    explicit FormMachine(int machineId, QWidget *parent = 0);
    ~FormMachine();

    virtual void setUpRotors();

public slots:

    virtual void slotAddEntry(QString name);
    virtual void slotAddRotor(RotorComboBox *oCbxRotor);
    virtual void slotAddReflector(QString name);

protected:

    int machineId;
    Machine *oMachine;

    virtual void fillComboBox(QComboBox *cbx, QString list);

private:
    Ui::FormMachine *ui;
};

#endif // FORMMACHINE_H

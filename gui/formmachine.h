#ifndef FORMMACHINE_H
#define FORMMACHINE_H

#include <QWidget>

namespace Ui {
class FormMachine;
}

class FormMachine : public QWidget
{
    Q_OBJECT

public:
    explicit FormMachine(int machineId, QWidget *parent = 0);
    ~FormMachine();

protected:

    int machineId;


private:
    Ui::FormMachine *ui;
};

#endif // FORMMACHINE_H

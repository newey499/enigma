#include "formmachine.h"
#include "ui_formmachine.h"

FormMachine::FormMachine(int machineId, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMachine)
{
    ui->setupUi(this);

    this->machineId = machineId;

    QString tmp = QString("Machine Id [%1]").arg(machineId);
    ui->lblMachineName->setText(tmp);

}

FormMachine::~FormMachine()
{
    delete ui;
    deleteLater();
}

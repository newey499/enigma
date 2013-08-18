#include "rotorsetupdialog.h"
#include "ui_rotorsetupdialog.h"


RotorSetupDialog::RotorSetupDialog(Rotor *oRotor, int rotorPosition, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RotorSetupDialog)
{
    this->oRotor = oRotor;
    this->rotorPosition = rotorPosition;
    commonConstructor();
}

void RotorSetupDialog::commonConstructor()
{
    int index;
    ui->setupUi(this);

    setWindowTitle("Rotor Setup");
    ui->edtRotorName->setText(oRotor->getRotorName());
    ui->edtRotorName->setReadOnly(true);
    ui->edtRotorPosition->setText(QString("%1").arg(rotorPosition));
    ui->edtRotorPosition->setReadOnly(true);

    ui->cbxWindowChar->clear();
    QString am = oRotor->getAlphabetMap();
    for (int i = 1; i < am.count(); i++)
    {
        ui->cbxWindowChar->addItem(am.at(i));
    }
    index = ui->cbxWindowChar->findText(oRotor->getLetterSetting());
    ui->cbxWindowChar->setCurrentIndex(index);
    qDebug("window char [%s]", oRotor->getLetterSetting().toAscii().data());

    ui->cbxRingSetting->clear();
    for (int i = 1; i <= oRotor->getAlphabetSize(); i++)
    {
        ui->cbxRingSetting->addItem(QString("%1").arg(i));
    }
    QString ringSetting = QString("%1").arg(oRotor->getRingSetting());
    index = ui->cbxRingSetting->findText(ringSetting);
    ui->cbxRingSetting->setCurrentIndex(index);
    qDebug("ring setting [%s]", ringSetting.toAscii().data());





}

RotorSetupDialog::~RotorSetupDialog()
{
    delete ui;
}


void RotorSetupDialog::slotAccept()
{
    int ringSetting = ui->cbxRingSetting->currentText().toInt();
    qDebug("RotorSetupDialog::slotAccept()");
    oRotor->setLetterSetting(ui->cbxWindowChar->currentText());
    oRotor->setRingSetting(ringSetting);

    qDebug("rotor letter [%s] ring [%s]",
           ui->cbxWindowChar->currentText().toAscii().data(),
           ui->cbxRingSetting->currentText().toAscii().data()
           );
    accept();
}

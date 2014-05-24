#include "formsettings.h"
#include "ui_formsettings.h"

FormSettings::FormSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSettings)
{
    ui->setupUi(this);
    globals = Globals::getInstance();
    database = EnigmaDatabase::getInstance();

    initUi();
}

FormSettings::~FormSettings()
{
    delete ui;
}

void FormSettings::initUi()
{
    ui->cbxDriver->addItems(database->getDriverList());

    ui->cbxDriver->setCurrentText(globals->db_driver());

    ui->txtDatabasename->setText(globals->db_databasename());
    ui->txtHostname->setText(globals->db_hostname());
    ui->txtUsername->setText(globals->db_username());
    ui->txtPassword->setText(globals->db_password());

    /****
    cerr << "cbx index [" << ui->cbxDriver->currentIndex() <<
            "] text [" << ui->cbxDriver->currentText().toStdString() <<
            "] globals driver [" << globals->db_driver().toStdString() <<
            "]" << endl;
    *****************/
    ui->cbxDriver->setCurrentText(globals->db_driver());
    isOdbcDriver(ui->cbxDriver->currentText());
    connect(ui->cbxDriver, SIGNAL(currentTextChanged(QString)),
            this, SLOT(slotDriverChanged(QString)) );
}

void FormSettings::slotSaveSettings()
{
    //qDebug("FormSettings::slotSaveSettings()");
    globals->save();
}

bool FormSettings::isOdbcDriver(QString driverName)
{
    bool odbcDriver = (driverName.compare("QODBC", Qt::CaseSensitive) == 0) ||
                      (driverName.compare("QODBC3", Qt::CaseSensitive) == 0);

    if (odbcDriver)
    {
        ui->txtHostname->setEnabled(false);
    }
    else
    {
        ui->txtHostname->setEnabled(true);
    }

    return odbcDriver;
}

void FormSettings::slotDriverChanged(QString newDriver)
{
    //qDebug("void FormSettings::slotDriverChanged(QString newDriver) [%s]", newDriver.toStdString().data());
    isOdbcDriver(newDriver);
    //cout << "newDriver [" << newDriver.toStdString() << "]" << endl;
    globals->setDb_driver(newDriver);
}

void FormSettings::slotTestConn()
{
    qDebug("FormSettings::slotTestConn()");
    database->testConnection(
                                ui->cbxDriver->currentText(),
                                ui->txtHostname->text(),
                                ui->txtDatabasename->text(),
                                ui->txtUsername->text(),
                                ui->txtPassword->text()
                            );
}

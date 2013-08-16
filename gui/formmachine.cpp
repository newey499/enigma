#include "formmachine.h"
#include "ui_formmachine.h"

FormMachine::FormMachine(int machineId, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMachine)
{
    ui->setupUi(this);

    this->machineId = machineId;
    oMachine = new Machine(machineId, this);

    ui->edtMachineId->setText(QString("%1").arg(machineId));
    ui->edtMachineName->setText(oMachine->getRecMachine().value("name").toString());

    setUpRotors();
}

FormMachine::~FormMachine()
{
    delete ui;
    deleteLater();
}


void FormMachine::setUpRotors()
{
    QString listIds;
    QLabel *lbl;
    QComboBox *cbx;

    QHBoxLayout *layout = ui->machineDefinitionLayout;

    // Reflector
    lbl = new QLabel("Reflector", this);
    cbx = new QComboBox(this);
    connect(cbx, SIGNAL(currentIndexChanged(const QString)),
            this, SLOT(slotAddReflector(QString)));
    listIds = oMachine->getRecMachine().value("reflectorlist").toString();
    fillComboBox(cbx, listIds);



    layout->addWidget(lbl);
    layout->addWidget(cbx);

    // rotors
    lbl = new QLabel("Rotors", this);
    layout->addWidget(lbl);
    int rotorCount = oMachine->getRecMachine().value("rotorcount").toInt();
    for (int i = 1; i <= rotorCount; i++)
    {
         cbx = new RotorComboBox(i, this);

         connect(cbx, SIGNAL(rotorChanged(RotorComboBox *)),
                 this, SLOT(slotAddRotor(RotorComboBox *)));
         cbx->setToolTip("Right Click to configure Rotor");
         listIds = oMachine->getRecMachine().value("rotorlist").toString();
         fillComboBox(cbx, listIds);
         layout->addWidget(cbx);
    }


    // Entry
    lbl = new QLabel("Entry", this);
    cbx = new QComboBox(this);
    connect(cbx, SIGNAL(currentIndexChanged(const QString)),
            this, SLOT(slotAddEntry(QString)));
    listIds = oMachine->getRecMachine().value("entrylist").toString();
    fillComboBox(cbx, listIds);

    layout->addWidget(lbl);
    layout->addWidget(cbx);



}


void FormMachine::fillComboBox(QComboBox *cbx, QString list)
{
    QSqlQuery qry;
    QStringList sl = list.split(",");

    qry.prepare("select * from rotor where id = :id order by name");


    for (int i = 0; i < sl.count(); i++ )
    {
        qry.bindValue(":id", sl.at(i));

        if (! GenLib::execQry(qry, true))
        {
            qDebug("Query Failed");
            qDebug("%s", qry.lastError().text().toAscii().data());
        }
        else
        {
            qDebug("List [%s]", qry.record().value("name").toString().toAscii().data());
            cbx->addItem(qry.record().value("name").toString(), qry.record().value("id").toInt());
        }
    }
}


void FormMachine::slotAddEntry(QString name)
{
    qDebug("FormMachine::slotAddEntry() [%s]", name.toAscii().data());
    Entry *oEntry = new Entry(name, this);
    oMachine->addEntry(oEntry);
}

void FormMachine::slotAddRotor(RotorComboBox *oCbxRotor)
{

    qDebug("FormMachine::slotAddRotor() [%s]", oCbxRotor->currentText().toAscii().data());
    oMachine->addRotor(oCbxRotor->getRotorPosition(),
                       oMachine->rotorFactory(oCbxRotor->currentText(), 1,
                       QString(oMachine->getAlphabet()->getAlphabetMap().at(0)).toAscii().data()));
}

void FormMachine::slotAddReflector(QString name)
{
    qDebug("FormMachine::slotAddReflector() [%s]", name.toAscii().data());
    Reflector *oReflector = new Reflector(name, this);
    oMachine->addReflector(oReflector);
}

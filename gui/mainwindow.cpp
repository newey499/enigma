/************************************************************************
Copyright Chris Newey 2013

enigmasim@outlook.com

This file is part of enigma.

Enigma is distributed under the terms of the GNU General Public License

Enigma is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Enigma is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Enigma.  If not, see <http://www.gnu.org/licenses/>.

***************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSettings settings(Globals::ORGANIZATION_NAME, Globals::APPLICATION_NAME);
    restoreGeometry(settings.value("geometry").toByteArray());

    globals = Globals::getInstance();

    buildMenusAndForms();

    slotFormTestComponents();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::saveSettings()
{
    QSettings settings(Globals::ORGANIZATION_NAME, Globals::APPLICATION_NAME);

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int ret = quitYesNo();

    if (ret == QMessageBox::Yes)
    {
        saveSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

int MainWindow::quitYesNo()
{
    QString exit = QString("Exit ");
    QString appName = Globals::APPLICATION_NAME;

    exit = exit.append(appName);

    int ret = QMessageBox::question(this,
                                    tr(appName.toStdString().data()),
                                    tr(exit.toStdString().data()),
                                    QMessageBox::Yes | QMessageBox::No,
                                    QMessageBox::Yes);

    return ret;
}


void MainWindow::quitApplication()
{
    int ret = quitYesNo();
    if (ret == QMessageBox::Yes)
    {
        saveSettings();
        qApp->quit();
    }
}


void MainWindow::buildMenusAndForms()
{
    QMenu *fileMenu     = new QMenu("&File", this);
        connect(addMenuItem(fileMenu, "E&xit"), SIGNAL(triggered()),
                this, SLOT(quitApplication()));

    QMenu *machineMenu     = new QMenu("&Machines", this);
        createMachineMenuItems(machineMenu);

    QMenu *testMenu     = new QMenu("&Test", this);
        connect(addMenuItem(testMenu, "Test &Components"), SIGNAL(triggered()),
                this, SLOT(slotFormTestComponents()));

    QMenu *settingsMenu = new QMenu("&Settings", this);
        connect(addMenuItem(settingsMenu, "&Settings"), SIGNAL(triggered()),
            this, SLOT(slotFormSettings()));

    QMenu *helpMenu     = new QMenu("&Help", this);
        connect(addMenuItem(helpMenu, "About &Enigma"), SIGNAL(triggered()),
                this, SLOT(aboutEnigma()));
        connect(addMenuItem(helpMenu, "About &Qt"), SIGNAL(triggered()),
                this, SLOT(aboutQt()));


    /**************
    QAction *actAboutQt = new QAction(tr("About &Qt"), this);
    actAboutQt->setStatusTip(tr("About Qt"));
    connect(actAboutQt, SIGNAL(triggered()),
            this, SLOT(aboutQt()));
    helpMenu->addAction(actAboutQt);
    *********************/

    menuBar()->clear();
    this->menuBar()->addMenu(fileMenu);
    this->menuBar()->addMenu(machineMenu);
    this->menuBar()->addMenu(testMenu);
    this->menuBar()->addMenu(settingsMenu);
    this->menuBar()->addMenu(helpMenu);
}

void MainWindow::createMachineMenuItems(QMenu *menu)
{
    QSqlQuery qry;

    qry.prepare("select id, name, steckerboard, "
                "rotorcount, entrylist, rotorlist, "
                "reflectorlist, alphabetid "
                "from machine");
    GenLib::execQry(qry, false);
    while (qry.next())
    {
        QString title = qry.record().value("name").toString();
        EnigmaAction *action = addMenuItem(menu, title);
        action->setData(qry.record().value("id").toInt());
        connect(action, SIGNAL(signalTriggered(EnigmaAction *)),
                this, SLOT(slotMachine(EnigmaAction *)));
    }
}

EnigmaAction * MainWindow::addMenuItem(QMenu *menu, QString title)
{
    EnigmaAction *action = new EnigmaAction(tr(title.toStdString().data()), this);
    action->setStatusTip(tr(title.replace("&", "").toStdString().data()));
    menu->addAction(action);

    return action;
}


void MainWindow::aboutEnigma()
{
    QString title = QString("%1 %2 %3").arg(Globals::APPLICATION_NAME).
                                        arg(" version: ").
                                        arg(Globals::APPLICATION_VERSION);
    QString text("Enigma cypher machine emulation\n\n"
                 "Copyright Chris Newey 2013\n"
                 "Enigma is distributed under the terms of the GNU General Public License");
    QMessageBox::about(this, title, text);
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this, "Enigma");
}

void MainWindow::slotFormTestAlphabet()
{
    qDebug("void MainWindow::slotFormTestAlphabet()");
}


void MainWindow::slotMachine(EnigmaAction *action)
{
    int machineId = action->data().toInt();
    // QMainWindow takes ownership and deletes the object from the heap
    // when it finished with
    setCentralWidget(new FormMachine(machineId, this));
}


void MainWindow::slotFormTestComponents()
{
    // QMainWindow takes ownership and deletes the object from the heap
    // when it finished with
    setCentralWidget(new FormTestComponents(this));
}


void MainWindow::slotFormSettings()
{
    // QMainWindow takes ownership and deletes the object from the heap
    // when it finished with
    setCentralWidget(new FormSettings(this));
}

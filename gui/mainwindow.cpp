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

    globals = new Globals(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::exec()
{
    qDebug("EntryPoint::exec()");

    try
    {
        QSqlQuery qry("select * from rotor");
        QSqlRecord rec;

        while (qry.next())
        {
            rec = qry.record();
            qDebug("%s", rec.value("name").toString().toAscii().data());
        }

    }
    catch (EnigmaException &e)
    {
        qDebug("%s", e.what().toAscii().data());
        this->close();
        // TODO Display a message box displaying the exception
        qApp->exit(1);
    }

}

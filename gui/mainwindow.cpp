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

    QSqlQuery qry("select * from rotor");
    QSqlRecord rec;

    while (qry.next())
    {
        rec = qry.record();
        qDebug("%s", rec.value("name").toString().toAscii().data());
    }
}

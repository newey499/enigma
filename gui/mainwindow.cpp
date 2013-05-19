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

        // Test exception handling

        // throw EnigmaException("gui exception",__FILE__, __LINE__);
    }
    catch (EnigmaException &e)
    {
        qDebug("%s", e.what().toAscii().data());
        this->close();
        // TODO Display a message box displaying the exception
        qApp->exit(1);
    }

}

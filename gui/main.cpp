#include <QtGui/QApplication>
#include <QString>

#include "mainwindow.h"
#include "enigmadatabase.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
    EnigmaDatabase *edb = EnigmaDatabase::getInstance();
#pragma GCC diagnostic pop


    MainWindow w;
    w.show();

    w.exec();

    return a.exec();
}

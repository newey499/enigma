#include <QtGui/QApplication>
#include "mainwindow.h"
#include "enigmadatabase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    EnigmaDatabase *edb = EnigmaDatabase::getInstance();

    MainWindow w;
    w.show();
    w.exec();

    return a.exec();
}

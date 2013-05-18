#include <QtCore/QCoreApplication>

#include <QPointer>

#include <iostream>
using namespace std;

#include "globals.h"
#include "entrypoint.h"

int main(int argc, char *argv[])
{
    int result = 0;
    QCoreApplication a(argc, argv);

    cout << "Hello world" << endl;

    QPointer<Globals> globals = new Globals();
    QPointer<EntryPoint> entryPoint = new EntryPoint();


    result = entryPoint->exec();

    if (entryPoint)
    {
        delete entryPoint;
    }

    if (globals)
    {
        delete globals;
    }

    //return a.exec();
    QCoreApplication::exit(result);
}

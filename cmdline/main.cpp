#include <QtCore/QCoreApplication>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << " hello world" << endl;

    //return a.exec();
    QCoreApplication::exit(0);
}

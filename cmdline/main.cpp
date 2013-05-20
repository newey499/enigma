/************************************************************************
Copyright Chris Newey 2013

enigmasim@outlook.com

This file is part of enigma.

Enigma is distributed under the terms of the GNU General Public License

Enigma is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Qiptables is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Qiptables.  If not, see <http://www.gnu.org/licenses/>.

***************************************************************************/

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

    // Don't need an event loop for the command line app
    // result = a.exec();

    return result;
}

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

#include <stdio.h>
#include <stdlib.h>

#include "mainwindow.h"
#include <QApplication>
#include <QString>

#include "enigmadatabase.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    EnigmaDatabase *edb = EnigmaDatabase::getInstance();

    MainWindow w;
    w.show();

    return a.exec();

    edb->disconnect();

    return 0;
}

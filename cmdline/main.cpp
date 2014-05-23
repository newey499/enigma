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

#include <QtCore/QCoreApplication>

#include <QtDebug>
#include <QFile>
#include <QTextStream>

#include <QPointer>

#include <iostream>
using namespace std;

#include "globals.h"
#include "testharness.h"
#include "genlib.h"

#include "messagehandler.h"

// TODO Write unit tests


int main(int argc, char *argv[])
{
    int result = 0;
    QCoreApplication a(argc, argv);

    if (argc == 2)
    {
        QString arg(argv[1]);

        arg = arg.toUpper();

        if ( (arg.compare("--HELP") == 0) || (arg.compare("-H") == 0) )
        {
            cout << "Usage:" << endl;
            cout << "\tcmdline <name of log file>" << endl;
            cout << "\tcmdline -h display this help" << endl;
            cout << "\tcmdline --help display this help" << endl;
            exit(0);
        }
        else
        {
            MessageHandler mh(argv[1], true, 0);
            mh.deleteLogFile(); // Start a fresh log file each time the application runs
        }
    }
    /********
    else
    {
        MessageHandler mh("qtlog.txt", true, 0);
        mh.deleteLogFile();
    }
    ******************/

    // MessageHandler::messageHandler is a public static function
    //qInstallMsgHandler(MessageHandler::messageHandler);

    QPointer<Globals> globals = new Globals();
    QPointer<TestHarness> testHarness = new TestHarness();


    testHarness->getPerform()->setEnabled(TestHash::TEST_VALIDATE_MACHINE_CONFIG, true);
    //testHarness->getPerform()->setEnabled(TestHash::TEST_MACHINE, true);
    //testHarness->getPerform()->setEnabled(TestHash::TEST_DOUBLE_STEP, true);
    //testHarness->getPerform()->setEnabled(TestHash::TEST_TURNOVER, true);

    result = testHarness->exec();

    // Clean up heap
    if (testHarness)
    {
        delete testHarness;
    }
    // Clean up heap
    if (globals)
    {
        delete globals;
    }

    // Don't need an event loop for the command line app
    //result = a.exec();

    return result;
}

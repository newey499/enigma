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

#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include <QCoreApplication>

#include <QHash>
#include <QObject>
#include <QPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

#include "globals.h"
#include "enigmadatabase.h"
#include "alphabet.h"
#include "alphabetdata.h"
#include "entry.h"
#include "rotor.h"
#include "reflector.h"
#include "keyboard.h"
#include "steckerboard.h"
#include "enigmaexception.h"
#include "machine.h"

#include "testdatabasevalidation.h"

class TestHarness : public QObject
{
    Q_OBJECT

public:


    typedef enum
    {
       TEST_KEYBOARD,
       TEST_STECKERBOARD,
       TEST_ENTRY,
       TEST_ROTOR,
       TEST_RINGSETTING,
       TEST_REFLECTOR,
       TEST_LAMPBOARD,
       TEST_TURNOVER,
       TEST_MACHINE,
       TEST_DOUBLE_STEP,
       TEST_VALIDATION,
       TEST_ADD_AMEND_DELETE
    } TESTS;

    const static char *MSG_FAIL;
    const static char *MSG_FAIL_NO_EXCEPTION;
    const static char *MSG_OK;
    const static char *MSG_OK_FAIL;

    explicit TestHarness(QObject *parent = 0);

    virtual int exec();
    virtual int execValidationTest();
    virtual int execAddAmendDelTest();

    virtual void testKeyboard();
    virtual void testSteckerboard();
    virtual void testEntry();
    virtual void testRotor();
    virtual void testReflector();
    virtual void testMachine();
    virtual void testTurnover();
    virtual void testDoubleStep();
    virtual void testLampboard();



signals:

public slots:


protected:

    QHash<TESTS, bool> perform;

    QPointer<EnigmaDatabase> edb;
    QPointer<TestDatabaseValidation> tdv;

    QString debugHeader(QString component);
    QString debugFooter(QString component);

    virtual void testRepeatRotate(Rotor &rotor, int repeat, int pinIn, QString letter);
    virtual int testRepeatMapLeftToRight(Rotor &rotor, int repeat, int pinIn, QString letter);
    virtual int testRepeatMapRightToLeft(Rotor &rotor, int repeat, int pinIn, QString letter);
    virtual void testReverseMapping(Rotor &rotor, int keyIn, QString windowChar);
    virtual void testInvalidRingSetting(Rotor &rotor, int ringSetting);

    virtual void createTestHash();

private:


};

#endif // ENTRYPOINT_H
